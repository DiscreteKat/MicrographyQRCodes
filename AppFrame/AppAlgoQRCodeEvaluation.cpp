#include "StdAfx.h"
#include "AppAlgoQRCodeEvaluation.h"

#include "AppAlgoQRCodeRenderer.h"
#include "AppAlgoColorMapping.h"

#include "AppAlgoProbabilityModule.h"
#include "AppAlgoProbabilityModel.h"

#include "AppAlgoEnergyTextSpace.h"
#include "AppAlgoEnergyVisual.h"

#include "AppAlgoZBar.h"
#include "AppAlgoZXing.h"

bool AppAlgoQRCodeEvaluation::Execute( HKCAppItem^ _appItem )
{
	HKCQRCData& qrcode   =  _appItem->Data->QRCData;
	int word_art_idx	 =  _appItem->Data->CurrentWordArtID;
	QRWordArt::QRStringLines& spline = _appItem->Data->WordArtData[word_art_idx].splines;

	cv::Mat result;
	AppAlgoQRCodeRenderer::GenResult(_appItem,&result);

	std::vector<int>& seg_pids = _appItem->Data->WordArtEvi.seg_pids;
	return Execute( _appItem,seg_pids,result );
}

bool AppAlgoQRCodeEvaluation::Execute( HKCAppItem^ _appItem,std::vector<int>& target )
{
	HKCQRCData& qrcode   =  _appItem->Data->QRCData;
	int word_art_idx =  _appItem->Data->CurrentWordArtID;
	QRWordArt::QRStringLines& spline = _appItem->Data->WordArtData[word_art_idx].splines;

	cv::Mat result;
	AppAlgoQRCodeRenderer::GenResult(_appItem,&result);

	return Execute( _appItem,target,result );
}

bool AppAlgoQRCodeEvaluation::Execute( HKCAppItem^ _appItem,cv::Mat& src )
{
	std::vector<int>& seg_pids = _appItem->Data->WordArtEvi.seg_pids;
	return Execute( _appItem,seg_pids,src );
}

bool AppAlgoQRCodeEvaluation::Execute( HKCAppItem^ _appItem,std::vector<int>& target,cv::Mat& src )
{
	Init();
	std::cout<<"=========Evaluation========="<<std::endl;
	HKCQRCData& qrcode  =  _appItem->Data->QRCData;
	int word_art_idx	=  _appItem->Data->CurrentWordArtID;
	QRWordArt::QRStringLines& spline = _appItem->Data->WordArtData[word_art_idx].splines;
	QRWordArt::QRStringLines& edge_spline = _appItem->Data->WordArtEvi.edge_splines;
	//m_NumModule  = _appItem->Data->WordArtEvi.seg_pids.size();
	//m_NumIsland  = _appItem->Data->WordArtData[word_art_idx].back_patterns.size()+_appItem->Data->WordArtData[word_art_idx].front_patterns.size();
	if (m_EnableVisualEnergy)
	{
		AppAlgoEnergyVisual visaul_energy(_appItem);
		m_MGVQ = visaul_energy.EvaluateVisualEnergy(_appItem->Data->WordArtData[word_art_idx]);

		m_Es = visaul_energy.getEs();
		m_Et = visaul_energy.getEt();
		m_Ecs = visaul_energy.getEcs();
		m_Eca = visaul_energy.getEca();
		
		

		std::cout<<"Word Art: " <<m_MGVQ<<std::endl;
		std::cout<<"	Es : " <<m_Es <<std::endl;
		std::cout<<"	Et : " <<m_Et <<std::endl;
		std::cout<<"	Ecs: " <<m_Ecs<<std::endl;
		std::cout<<"	Eca: " <<m_Eca<<std::endl;
	}

	AppAlgoProbabilityModule algo_module_energy(_appItem);
	std::vector<double> module_energy;
	module_energy = algo_module_energy.Execute(src);

	AppAlgoProbabilityModel algo_prob(_appItem);
	m_AlgoProb.clear();
	m_AlgoProb = algo_prob.CodewordsErrProbability(module_energy);

	m_CW_Err.clear();
	m_CW_Err  = algo_prob.ErrorCodewordNum(m_AlgoProb);

	//Draw
	cv::Mat& energy_map = _appItem->Data->WordArtEvi.module_energy_map;
	energy_map.create(qrcode.QRCImg.cols,qrcode.QRCImg.rows,CV_8UC4);
	for (int i=0;i<qrcode.QRCImg.cols*qrcode.QRCImg.rows*4;i++){energy_map.data[i] = 0;}

	double total_energy = 0;

	for (int i=0;i<qrcode.Patches.size();i++)
	{
		cv::Point posn = qrcode.Patches[i]->grid_sample_Pos;
		int idx = posn.y*qrcode.QRCImg.cols+posn.x;

		double energy = module_energy[i];
		char r,g,b;
		AppAlgoColorMapping::Jet(energy,&r,&g,&b);
		AppAlgoQRCodeRenderer::DrawModule4(posn,r,g,b,255,_appItem->Data->QRCData.module_size,&energy_map);
		total_energy+=energy;
	}

	cv::Mat& cw_err_map = _appItem->Data->WordArtEvi.codeword_error_map;
	cw_err_map = cv::Mat::zeros(qrcode.QRCImg.cols,qrcode.QRCImg.rows,CV_8UC4);
	for (int i=0;i<qrcode.CWData.size();i++)
	{
		for (int j=0;j<qrcode.CWData[i].size();j++)
		{
			char r=0,g=0,b=0;
			if (algo_prob.IsErrorCodeword(m_AlgoProb[i][j])){r=255;}
			else{g=255;}
			// 			AppAlgoColorMapping::Jet(m_CW_Prob[i][j],&r,&g,&b);
			// 			for (int k=0;k<qrcode.CWData[i][j].module_idx.size();k++)
			// 			{
			// 				int idx = qrcode.CWData[i][j].module_idx[k];
			// 				DrawModule(qrcode.Patches[idx]->grid_sample_Pos,r,g,b,_appItem->Data->QRCData.module_size,&cw_err_map);
			// 			}
		}
	}

	if (!target.empty())
	{
		m_QRCQ=0;
		int high = 0;
		int low  = 0;
		for (int i=0;i<target.size();i++)
		{
			m_QRCQ+=module_energy[target[i]];

			if (module_energy[target[i]]>0.6)high++;
			else if(module_energy[target[i]]<=0.3)low++;
		}
		m_QRCQ/=(double)target.size();
		m_High_Energy = (double)high/(double)target.size()*100.0;
		m_Low_Energy  = (double)low/(double)target.size()*100.0;

		std::cout<<"Em:";
		std::cout<<m_QRCQ<<std::endl;

		std::cout<<"High Energy:";
		std::cout<<m_High_Energy<<"%";
		std::cout<<" ( "<<high<<"/"<<target.size()<<" )"<<std::endl;

		std::cout<<"Low Energy:";
		std::cout<<m_Low_Energy<<"%";
		std::cout<<" ( "<<low<<"/"<<target.size()<<" )"<<std::endl;
	}

	std::cout<<"CW Error:\n "<<m_CW_Err<<std::endl;
	if (algo_prob.IsErrorQRcode(m_AlgoProb))
	{
		m_DecodeSF = true;
		std::cout<<" Success"<<std::endl;
	}
	else{
		m_DecodeSF = false;
		std::cout<<" Fail"<<std::endl;
	}

	if (m_EnableScanner)
	{
		HKCZBarGridSampling zbar;
		bool zbar_flag = zbar.Execute_Detect(_appItem,src);
		cv::Mat zbar_error = zbar.GetErrorImg();

		AppAlgoZXing zxing;
		bool zxing_h_flag = zxing.Execute_Detect_H(_appItem,src);
		cv::Mat zxing_h_error = zxing.GetErrorImg();

		for (int i=0;i<qrcode.Patches.size();i++)
		{
			cv::Point posn = qrcode.Patches[i]->grid_sample_Pos;
			int idx = posn.y*qrcode.QRCImg.cols+posn.x;

			if (zbar_flag    && zbar_error.data[idx]==255){zbar_err_pids.push_back(i);}
			if (zxing_h_flag && zxing_h_error.data[idx]==255){zxing_h_err_pids.push_back(i);}
		}

		std::cout<<"Zbar"<<std::endl; 
		if (zbar_flag){
			if (zbar.QRContent().empty())std::cout<<" Detect Fail"<<std::endl;
			else{
				std::cout<<" ";
				for (int i=0;i<zbar.QRContent().size();i++)
				{
					std::cout<<zbar.QRContent()[i];
					if (i!=zbar.QRContent().size()-1)std::cout<<",";
				}
				std::cout<<std::endl;
			}

			cv::Mat& zbar_error_map = _appItem->Data->WordArtEvi.zbar_error_map;
			zbar_error_map = cv::Mat::zeros(qrcode.QRCImg.cols,qrcode.QRCImg.rows,CV_8UC4);

			std::vector<std::vector<bool>> zbar_err_cw = zbar.GetCWError();
			m_Zbar_Block_Err_CW.clear();
			m_Zbar_Block_Err_CW.resize(zbar_err_cw.size(),0);
			for (int i=0;i<zbar_err_cw.size();i++)
			{
				for (int j=0;j<zbar_err_cw[i].size();j++)
				{
					if (zbar_err_cw[i][j]){m_Zbar_Block_Err_CW[i]++;}

					char r=0,g=0,b=0;
					if (zbar_err_cw[i][j]){r=255;}
					else{g=255;}
					for (int k=0;k<qrcode.CWData[i][j].module_idx.size();k++)
					{
						int idx = qrcode.CWData[i][j].module_idx[k];
						AppAlgoQRCodeRenderer::DrawModule4(qrcode.Patches[idx]->grid_sample_Pos,r,g,b,255,_appItem->Data->QRCData.module_size,&zbar_error_map);
					}
				}
			}
			std::cout<<" Error CW:\n "<<m_Zbar_Block_Err_CW<<std::endl;
		}
		else std::cout<<" Fail"<<std::endl;

		std::cout<<"ZXing"<<std::endl; 
		if (zxing_h_flag)
		{
			if (zxing.QRContent().empty())std::cout<<" "<<zxing.Message()<<std::endl;
			else{
				std::cout<<" ";
				for (int i=0;i<zxing.QRContent().size();i++)
				{
					std::cout<<zxing.QRContent()[i];
					if (i!=zxing.QRContent().size()-1)std::cout<<",";
				}
				std::cout<<std::endl;
			}

			std::vector<std::vector<bool>> zing_err_cw = zxing.GetCWError();
			m_ZXing_Block_Err_CW.clear();
			m_ZXing_Block_Err_CW.resize(zing_err_cw.size(),0);
			for (int i=0;i<zing_err_cw.size();i++)
			{
				for (int j=0;j<zing_err_cw[i].size();j++)
				{
					if (zing_err_cw[i][j])
					{
						m_ZXing_Block_Err_CW[i]++;
					}
				}
			}
			std::cout<<" Error CW:\n "<<m_ZXing_Block_Err_CW<<std::endl;
		}
		else std::cout<<" Fail"<<std::endl;
	}
	std::cout<<"============================"<<std::endl; 

	return true;
}

void AppAlgoQRCodeEvaluation::CalDistribution( std::vector<double>& energy,int slice,std::vector<int>& distribution )
{
	distribution.resize(slice,0);
	for (int pid=0;pid<energy.size();pid++)
	{
		if (energy[pid]==1)
		{
			distribution.back()++;
		}else{
			int cid = (int)floor(energy[pid]*slice);
			distribution[cid]++;
		}
	}
}

void AppAlgoQRCodeEvaluation::CalDistribution( std::vector<double>& energy,std::vector<int>& module_pid,int slice,std::vector<int>& distribution )
{
	distribution.resize(slice,0);
	for (int i=0;i<module_pid.size();i++)
	{
		int pid = module_pid[i];
		if (energy[pid]==1)
		{
			distribution.back()++;
		}else{
			int cid = (int)floor(energy[pid]*slice);
			distribution[cid]++;
		}
	}
}

void AppAlgoQRCodeEvaluation::SaveFile( char* filename )
{
	ofstream file;
	file.open(filename);

	file<<"Decode"<<"\n";
	if (m_DecodeSF){file<<"Success"<<"\n";}
	else{file<<"Fail"<<"\n";}


	file<<"Visual,QR code"<<"\n";
	file<<m_MGVQ<<","<<m_QRCQ<<"\n";

	file<<"Es,Et,Ecs,Eca"<<"\n";
	file<<m_Es<<","<<m_Et<<","<<m_Ecs<<","<<m_Eca<<"\n";

	file<<"Island Count,Island Ratio"<<"\n";
	file<<m_NumIsland<<","<<m_NumIsland/m_NumModule<<"\n";

	file.close();
}