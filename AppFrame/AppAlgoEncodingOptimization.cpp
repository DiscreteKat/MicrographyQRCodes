#include "StdAfx.h"
#include "AppAlgoEncodingOptimization.h"
#include "AppAlgoColorMapping.h"
#include "AppAlgoQRCodeRenderer.h"
#include "AppAlgoProbabilityModule.h"
#include "AppAlgoQRCodeRenderer.h"

bool AppFrame::AppAlgoEncodingOptimization::Execute( HKCAppItem^ _appItem )
{
	std::cout<<"RS Modification..."<<std::endl;
	double bin_threshold = _appItem->Param->Optimization->RS_Binary_Threshold;
	std::cout<<" threshold: "<<bin_threshold<<std::endl;

	HKCQRCData& qrcData = _appItem->Data->QRCData;
	int wa = _appItem->Data->QRCData.module_size;
	
	cv::Mat src;
	AppAlgoQRCodeRenderer::GenResult(_appItem,&src);
	//cv::imshow("src",src);cv::waitKey();
	AppAlgoProbabilityModule app_Em(_appItem);
	std::vector<double> module_energy = app_Em.Execute(src,qrcData.QRCImg);

	AppAlgoRSModify app_rsmodify;
	app_rsmodify.JHinitial(qrcData);

//#define RS_DEBUG
#ifdef RS_DEBUG
	//Debug
	BitFlagImg(qrcData,app_rsmodify);
#endif
	//Gen Mask
	cv::Mat mask = cv::Mat(qrcData.QRCImg.rows,qrcData.QRCImg.cols,CV_8UC1,cv::Scalar(255));
	std::vector<int> seg_idx = _appItem->Data->WordArtEvi.seg_pids;
	for (int i=0;i<seg_idx.size();i++)
	{
		int p_id = seg_idx[i];
		cv::Point posn = qrcData.Patches[p_id]->grid_sample_Pos;
		AppAlgoQRCodeRenderer::DrawModule1(posn,0,wa,&mask);
	}

	cv::Mat& gap = _appItem->Data->WordArtEvi.gap_img;
	if (!gap.empty()){
		for (int i=0;i<mask.rows*mask.cols;i++){
			if (gap.data[i]!=255){mask.data[i]=0;}
		}
	}
	/////Binarization
	std::vector<int> bImg_bit;// 1-black; 0-white
	bImg_bit.resize(qrcData.Patches.size(),-1);
	int background_bit = (_appItem->Data->WordArtEvi.background_color==0)?1:0;
	for (int pid=0;pid<qrcData.Patches.size();pid++)
	{
		double energy = module_energy[pid];
		int qr_color  = (qrcData.Patches[pid]->qr_color==0)?1:0;
		if (energy<=bin_threshold){bImg_bit[pid] = qr_color;}
		else{bImg_bit[pid] = 1-qr_color;}
	}

#ifdef RS_DEBUG
	//Debug
	cv::Mat bImg(qrcData.QRCImg.rows,qrcData.QRCImg.cols,CV_8UC1,cv::Scalar(150));
	for (int i=0;i<qrcData.Patches.size();i++)
	{
		cv::Point posn = qrcData.Patches[i]->grid_sample_Pos;
		if (bImg_bit[i]==1){AppAlgoQRCodeRenderer::DrawModule1(posn,200,wa,&bImg);}
		else{AppAlgoQRCodeRenderer::DrawModule1(posn,100,wa,&bImg);}
	}
	for (int i=0;i<seg_idx.size();i++)
	{
		int pid = seg_idx[i];
		cv::Point posn = qrcData.Patches[pid]->grid_sample_Pos;
		if (bImg_bit[pid]==1){AppAlgoQRCodeRenderer::DrawModule1(posn,0,wa,&bImg);}
		else{AppAlgoQRCodeRenderer::DrawModule1(posn,255,wa,&bImg);}
	}
	cv::imwrite("bImg.png",bImg);
	cv::imshow ("bImg.png",bImg);
#endif
	
	QRCodeMasking(qrcData,mask,bImg_bit);
	app_rsmodify.SetSampleImageBits(bImg_bit);
	/////Select Codewords
	std::vector<int> select_modules = SelectModules(mask,qrcData,module_energy,app_rsmodify);
	app_rsmodify.SetPaddingLocation(select_modules);
	/////RS Modification
	app_rsmodify.Excute();
	/////Modify QRCdata
	for(int k=0; k<qrcData.QRCBitData.JHbitsStreamTotalLength;k++)
	{
		int idx = qrcData.QRCBitData.JHbitsStreamLocation[k];
		int qrVal = app_rsmodify.m_BitsStream[k];
		qrcData.Modules[idx]->QRC  =  qrVal;
		qrcData.QRCode.data[idx]   = (qrVal) ? 0 : 255;
		qrcData.Patches[idx]->qr_color = (qrVal)? 0 : 255;
	}
	cv::Size newSize = qrcData.QRCImg.size();
	qrcData.QRCImg.release();
	qrcData.QRCImg = qrcData.QRCode.clone();
 	cv::resize(qrcData.QRCImg, qrcData.QRCImg, newSize, 0, 0, cv::INTER_NEAREST);

#ifdef RS_DEBUG
	//Debug
	BitFlagImg2(qrcData,app_rsmodify,select_modules,module_energy);
#endif
	return true;
}

std::vector<int> AppFrame::AppAlgoEncodingOptimization::SelectModules( cv::Mat& mask,HKCQRCData& qrcData,std::vector<double>& module_energy,AppAlgoRSModify& app_rsmodify )
{
	std::vector<int> select_modules;
	select_modules.resize(qrcData.Patches.size(),0);

	//targets[RS]
	std::vector<std::vector<int>> targets; 
	targets.resize(qrcData.CWData.size());
	std::vector<int> padding_count;
	padding_count.resize(qrcData.CWData.size(),0);

	for(int bit_idx=0; bit_idx< qrcData.QRCBitData.JHbitsStreamTotalLength; bit_idx++)
	{
		int module_idx = qrcData.QRCBitData.JHbitsStreamLocation[bit_idx];
		if (qrcData.Modules[module_idx]->Type!=0)continue;

		int rs_idx = qrcData.Modules[module_idx]->RSID-1;
		cv::Point module_posn = qrcData.Patches[module_idx]->grid_sample_Pos;
		int pixel_idx = (module_posn.y)*mask.rows+(module_posn.x);
		if (!app_rsmodify.JHisEssentialInform(bit_idx) && mask.data[pixel_idx] != 255){targets[rs_idx].push_back(module_idx);}
		if (app_rsmodify.JHisPadding(bit_idx)){padding_count[rs_idx]++;}
	}

	for (int rs_idx = 0; rs_idx<targets.size(); rs_idx++)
	{
		std::cout<<" RS"<<rs_idx+1<<": "<<(double)padding_count[rs_idx]/(double)targets[rs_idx].size()*100.0 <<"% ("<<padding_count[rs_idx]<<"/"<<targets[rs_idx].size() <<")" <<std::endl;
		if (padding_count[rs_idx]==0)continue;
		SortModules(module_energy,targets[rs_idx]);
		for (int i=0;i<padding_count[rs_idx]&&i<targets[rs_idx].size();i++)
		{
			int module_idx = targets[rs_idx][i];
			select_modules[module_idx] = 1;
			//std::cout<<module_energy[module_idx]<<std::endl;
		}

		//¼Æ¶q¦h¾l
		int remain = padding_count[rs_idx]-targets[rs_idx].size();
		if (remain>0)
		{
			std::cout<<" Add Remain Padding"<<std::endl;
			int num=0;
			for(int bit_idx=0; bit_idx< qrcData.QRCBitData.JHbitsStreamTotalLength && num<remain; bit_idx++)
			{
				int module_idx = qrcData.QRCBitData.JHbitsStreamLocation[bit_idx];
				if (rs_idx!=qrcData.Modules[module_idx]->RSID-1)continue;
				
				if (!app_rsmodify.JHisEssentialInform(bit_idx) && select_modules[module_idx]==0)
				{
					select_modules[module_idx] = 1;
					num++;
				}
			}
		}
	}

	return select_modules;
}

void AppFrame::AppAlgoEncodingOptimization::SortModules( std::vector<double>& module_energy,std::vector<int>& targets/*Output*/ )
{
	std::vector<double> energy;
	energy.resize(targets.size());
	for (int i=0;i<targets.size();i++)
	{
		int module_idx = targets[i];
		energy[i] = abs(module_energy[module_idx]-0.5)*2;
	}

	for (int i=0;i<targets.size()-1;i++)
	{
		for(int j=i+1;j<targets.size();j++)
		{
			if (energy[i]<energy[j])
			{
				int temp_m = targets[i];
				targets[i] = targets[j];
				targets[j] = temp_m;

				double temp_e = energy[i];
				energy[i] = energy[j];
				energy[j] = temp_e;
			}
		}
	}
}

void AppFrame::AppAlgoEncodingOptimization::QRCodeMasking( HKCQRCData& qrcData,cv::Mat& mask,std::vector<int>& bit_img )
{
	for(int k=0; k<bit_img.size();k++){
		cv::Point posn = qrcData.Patches[k]->grid_sample_Pos;
		int pixel_idx = posn.x + posn.y * mask.rows;
		if (mask.data[pixel_idx]==255){bit_img[k] = qrcData.Modules[k]->QRC;}
	}
}

void AppFrame::AppAlgoEncodingOptimization::BitFlagImg( HKCQRCData& qrcData, AppAlgoRSModify& app_rsmodify)
{
	int wa = qrcData.module_size;
	cv::Mat bit_color_map(qrcData.QRCImg.rows,qrcData.QRCImg.cols,CV_8UC4,cv::Scalar(150,150,150,0));
	for(int k=0; k<g_QRBitData.JHbitsStreamTotalLength;k++)
	{
		int module_idx = qrcData.QRCBitData.JHbitsStreamLocation[k];
		int rs_idx = qrcData.Modules[module_idx]->RSID-1;

		cv::Point posn = qrcData.Patches[module_idx]->grid_sample_Pos;
		if (app_rsmodify.JHisEssentialInform(k)){AppAlgoQRCodeRenderer::DrawModule4(posn,0,0,255,128,wa,&bit_color_map);}
		else if (app_rsmodify.JHisPadding(k))   {AppAlgoQRCodeRenderer::DrawModule4(posn,0,255,0,128,wa,&bit_color_map);}
		else                                    {AppAlgoQRCodeRenderer::DrawModule4(posn,255,0,0,128,wa,&bit_color_map);}
	}

	for (int i=0;i<bit_color_map.rows*bit_color_map.cols;i++)
	{
		bit_color_map.data[i*4+0] = bit_color_map.data[i*4+3]*bit_color_map.data[i*4+0] + (1-bit_color_map.data[i*4+3])*qrcData.QRCImg.data[i];
		bit_color_map.data[i*4+1] = bit_color_map.data[i*4+3]*bit_color_map.data[i*4+1] + (1-bit_color_map.data[i*4+3])*qrcData.QRCImg.data[i];
		bit_color_map.data[i*4+2] = bit_color_map.data[i*4+3]*bit_color_map.data[i*4+2] + (1-bit_color_map.data[i*4+3])*qrcData.QRCImg.data[i];
		bit_color_map.data[i*4+3] = 255;
	}
	cv::imwrite("bit_color_map.png",bit_color_map);
}

void AppFrame::AppAlgoEncodingOptimization::BitFlagImg2( HKCQRCData& qrcData, AppAlgoRSModify& app_rsmodify,std::vector<int> select_modules,std::vector<double>& module_energy )
{
	int wa = qrcData.module_size;
	std::vector<int> padding_count;
	padding_count.resize(qrcData.CWData.size(),0);

	for(int bit_idx=0; bit_idx< qrcData.QRCBitData.JHbitsStreamTotalLength; bit_idx++)
	{
		int module_idx = qrcData.QRCBitData.JHbitsStreamLocation[bit_idx];
		int rs_idx = qrcData.Modules[module_idx]->RSID-1;
		if (app_rsmodify.JHisPadding(bit_idx)){padding_count[rs_idx]++;}
	}

	cv::Mat bit_color_map2(qrcData.QRCImg.rows,qrcData.QRCImg.cols,CV_8UC4,cv::Scalar(150,150,150,0));
	for (int pid=0;pid<qrcData.Patches.size();pid++)
	{
		cv::Point posn = qrcData.Patches[pid]->grid_sample_Pos;
		if (qrcData.Modules[pid]->Type < 1)
		{
			double energy = module_energy[pid];
			if (energy>0.3 && energy<0.7){AppAlgoQRCodeRenderer::DrawModule4(posn,255,255,255,255,wa,&bit_color_map2);}
		}
	}

	cv::Mat select_map(qrcData.QRCImg.rows,qrcData.QRCImg.cols,CV_8UC4,cv::Scalar(0,0,0,0));
	for(int k=0; k<g_QRBitData.JHbitsStreamTotalLength;k++)
	{
		int module_idx = qrcData.QRCBitData.JHbitsStreamLocation[k];
		int rs_idx = qrcData.Modules[module_idx]->RSID-1;
		cv::Point posn = qrcData.Patches[module_idx]->grid_sample_Pos;
		if (app_rsmodify.JHisEssentialInform(k))
		{
			AppAlgoQRCodeRenderer::DrawModule4(posn,0,0,255,255,wa,&select_map);
		}else if (select_modules[module_idx]==1){
			AppAlgoQRCodeRenderer::DrawModule4(posn,128,255,128,255,wa,&select_map);
		}else{
			AppAlgoQRCodeRenderer::DrawModule4(posn,255,128,128,255,wa,&select_map);
 		}

		if (padding_count[rs_idx]==0 || app_rsmodify.JHisEssentialInform(k) || select_modules[module_idx]!=1){AppAlgoQRCodeRenderer::DrawModule4(posn,255,0,255,255,wa,&bit_color_map2);}
	}

// 	for (int i=0;i<select_map.rows*select_map.cols;i++)
// 	{
// 		if (select_map.data[i*4+1]==255)
// 		{
// 			double alpha = 0.5;
// 			select_map.data[i*4+0] = alpha*select_map.data[i*4+0] + (1-alpha)*qrcData.QRCImg.data[i];
// 			select_map.data[i*4+1] = alpha*select_map.data[i*4+1] + (1-alpha)*qrcData.QRCImg.data[i];
// 			select_map.data[i*4+2] = alpha*select_map.data[i*4+2] + (1-alpha)*qrcData.QRCImg.data[i];
// 			select_map.data[i*4+3] = 255;
// 		}if (select_map.data[i*4+3]==0)
// 		{
// 			select_map.data[i*4+0] = qrcData.QRCImg.data[i];
// 			select_map.data[i*4+1] = qrcData.QRCImg.data[i];
// 			select_map.data[i*4+2] = qrcData.QRCImg.data[i];
// 			select_map.data[i*4+3] = 255;
// 		}
// 	}

	cv::imwrite("select.png",select_map);
	cv::imshow ("select.png",select_map);
	qrcData.RSModify = bit_color_map2;
}
