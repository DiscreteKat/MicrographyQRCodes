#include "stdafx.h"
#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"
#include "AppUtils.h"

#include "AppAlgoQRCodeSegmentation.h"
#include "AppAlgoQRCodeRenderer.h"

using namespace AppFrame;
bool AppAlgoQRCodeSegmentation::Execute(HKCAppItem^ _appItem)
{
	cv::Mat& qr_background=_appItem->Data->WordArtEvi.qr_background_modules;
	cv::Mat& qr_foreground=_appItem->Data->WordArtEvi.qr_foreground_modules;

	HKCQRCData& qrcData = _appItem->Data->QRCData;
	cv::Mat& qrcode = qrcData.QRCode;
	cv::Mat& qrcode_img = qrcData.QRCImg;

	int wa = _appItem->Data->QRCData.module_size;
	int da = _appItem->Data->QRCData.center_size;

	//Load Data
	HKCMediaItem^ srcItem = _appItem->Find("Source");
	cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());

	cv::Mat& segment_img = _appItem->Data->WordArtEvi.segment_img;
	cv::Point2d offset   = _appItem->Data->QRCData.offset;
	cv::Rect clipping = cv::Rect(offset.x,offset.y,qrcode_img.cols,qrcode_img.rows);
	cv::Mat  clipped_segment;
	segment_img(clipping).copyTo(clipped_segment);
	
	////===============QR code Foreground Moudles=================
	qr_foreground = cv::Mat(qrcode_img.cols,qrcode_img.rows, CV_8UC4,cv::Scalar(0,0,0,0));
	for (int i=0;i<qrcData.Patches.size();i++)
	{
		cv::Point posn = qrcData.Patches[i]->grid_sample_Pos;
		int idx = posn.x + posn.y * srcImg->cols;
		double color = qrcData.Patches[i]->qr_color;
		if ( qrcData.Modules[i]->Type==4 || qrcData.Modules[i]->Type==6){AppAlgoQRCodeRenderer::DrawModule4(posn,color,color,color,250,wa,&qr_foreground);}
		//if ( qrcData.Modules[i]->Type==5){AppAlgoQRCodeRenderer::DrawModule4(posn,color,color,color,70,wa,&qr_foreground);}
	}

	////=================Gap Modules=================
	for (int i=0;i<qrcData.Modules.size();i++){qrcData.Modules[i]->abandon = false;}

	cv::Mat& gap = _appItem->Data->WordArtEvi.gap_img;
	if (!gap.empty()){GapAbandon(gap,_appItem->Data->WordArtEvi.background_color,qrcData);}
	
	////==========QR code Background Moudles============
	std::vector<int>& seg_pids = _appItem->Data->WordArtEvi.seg_pids;
	qr_background = GenBackground(_appItem->Data->WordArtEvi.background_style,clipped_segment,gap,qrcData,wa,da,seg_pids);

	////=================Gap CW Modules=================
	if (!gap.empty()){GapAbandonCW(qrcData);}

	////=================Island Modules=================
	for (int i=0;i<_appItem->Data->WordArtData.size();i++)
	{
		_appItem->Data->WordArtData[i].naive_combine   = cv::Mat(qrcode_img.cols,qrcode_img.rows, CV_8UC4,cv::Scalar(0,0,0,0));
		_appItem->Data->WordArtData[i].naive_blending  = cv::Mat(qrcode_img.cols,qrcode_img.rows, CV_8UC4,cv::Scalar(0,0,0,0));
		_appItem->Data->WordArtData[i].pixel_blending  = cv::Mat(qrcode_img.cols,qrcode_img.rows, CV_8UC4,cv::Scalar(0,0,0,0));
	}

	/*Debug
	cv::Mat& debug_map = _appItem->Data->WordArtEvi.qr_seg_modules;
	debug_map = cv::Mat(srcImg->cols,srcImg->rows, CV_8UC4,cv::Scalar(128,128,128,255));
	for (int i=0;i<qrcData.Patches.size();i++)
	{
		cv::Point posn = qrcData.Patches[i]->grid_sample_Pos;
		int idx = posn.x + posn.y * srcImg->cols;
		double color = qrcData.Patches[i]->qr_color;
		AppAlgoQRCodeRenderer::DrawModule4(posn,color,color,color,255,da,&debug_map);
	}
	*/
	return true;
}

std::vector<int> AppFrame::AppAlgoQRCodeSegmentation::SegmentQRCode( cv::Mat& segment_img,HKCQRCData& qrcData,int module_size )
{
	std::vector<int> seg_pids;
	for (int pid=0;pid<qrcData.Patches.size();pid++)
	{
		cv::Point module_posn = qrcData.Patches[pid]->grid_sample_Pos;
		int count = 0;
		for (int i=-module_size*0.5; i<module_size*0.5; ++i)
		{
			for (int j=-module_size*0.5; j<module_size*0.5; ++j)
			{
				int idx = (module_posn.y+i)*segment_img.rows+(module_posn.x+j);
				if (segment_img.data[idx] != 255){count++;}
			}
		}
		if(count>module_size*module_size*0.25){seg_pids.push_back(pid);}
	}
	return seg_pids;
}

void AppFrame::AppAlgoQRCodeSegmentation::SegmentQRCode( HKCAppItem^ _appItem )
{
	cv::Mat& segment_img = _appItem->Data->WordArtEvi.segment_img;
	int da = _appItem->Data->QRCData.center_size;
	int wa = _appItem->Data->QRCData.module_size;
	cv::Mat& qrcode_img = _appItem->Data->QRCData.QRCImg;

	cv::Point2d offset = _appItem->Data->QRCData.offset;
	cv::Rect clipping  = cv::Rect(offset.x,offset.y,qrcode_img.cols,qrcode_img.rows);
	cv::Mat mask;
	segment_img(clipping).copyTo(mask);

	//cv::imshow("mask",mask); cv::waitKey();
	cv::Mat elem = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(da,da));
	cv::morphologyEx(mask, mask, cv::MORPH_DILATE, elem);
	//cv::imshow("mask",mask); cv::waitKey();

	cv::Mat word_map;
	AppAlgoQRCodeRenderer::GenWordMap(_appItem,&word_map);
	(word_map)(clipping).copyTo(word_map);

	std::vector<int>& seg_pids = _appItem->Data->WordArtEvi.seg_pids;
	seg_pids.clear();

	HKCQRCData& qrcdata = _appItem->Data->QRCData;
	for (int pid=0;pid<qrcdata.Patches.size();pid++)
	{
		cv::Point module_posn = qrcdata.Patches[pid]->grid_sample_Pos;

		bool flag = true;
		//Step1: Mask去掉外圍Modules
		for (int i=-wa*0.5; i<wa*0.5; ++i)
		{
			for (int j=-wa*0.5; j<wa*0.5; ++j)
			{
				int idx = (module_posn.y+i)*mask.rows+(module_posn.x+j);
				if (mask.data[idx] != 0){flag = false;break;}
			}
 		}

		//Step2: 確認是否有字
		if (!flag)
		{
			int len = wa-2;
			for (int i=-len*0.5; i<len*0.5; ++i)
			{
				for (int j=-len*0.5; j<len*0.5; ++j)
				{
					int idx = (module_posn.y+i)*word_map.rows+(module_posn.x+j);
					if (word_map.data[idx*4+3] == 255){flag = true;break;}
				}
			}
		}
		if(flag){seg_pids.push_back(pid);}
	}

	int b_module=0, w_module=0;
	for (int i=0;i<seg_pids.size();i++)
	{
		int pid = seg_pids[i];
		if (qrcdata.Patches[pid]->qr_color==0){b_module++;}
		else{w_module++;}
	}
	std::cout<<" White Module: "<<w_module<<std::endl;
	std::cout<<" Black Module: "<<b_module<<std::endl;
}

cv::Mat AppFrame::AppAlgoQRCodeSegmentation::GenBackground(int style,cv::Mat& segment_img,cv::Mat& gap,HKCQRCData& qrcData, int wa, int da, std::vector<int>& seg_pids)
{
	cv::Mat background(qrcData.QRCImg.cols,qrcData.QRCImg.rows, CV_8UC4, cv::Scalar(0,0,0,0));
	cv::Mat mask = segment_img.clone();

	if (style==BG_STYLE_BLEND || style==BG_STYLE_BLEND_WITH_GAP)
	{
		if (style==BG_STYLE_BLEND_WITH_GAP && !gap.empty())
		{
			for (int i=0;i<qrcData.QRCImg.rows*qrcData.QRCImg.cols;i++)
			{
				if (gap.data[i]==0){mask.data[i]=0;}
			}
		}

		cv::Mat elem = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(wa,wa));
		//cv::morphologyEx(mask, mask, cv::MORPH_DILATE, elem);
		cv::morphologyEx(mask, mask, cv::MORPH_ERODE, elem);
		cv::GaussianBlur(mask,mask,cv::Size(wa,wa),0);
		

		for (int i=0;i<qrcData.QRCImg.rows*qrcData.QRCImg.cols;i++)
		{
			background.data[i*4+0] = qrcData.QRCImg.data[i];
			background.data[i*4+1] = qrcData.QRCImg.data[i];
			background.data[i*4+2] = qrcData.QRCImg.data[i];
			background.data[i*4+3] = mask.data[i];
		}
	}else{		
		for (int i=0;i<qrcData.Patches.size();i++)
		{
			if (qrcData.Modules[i]->abandon){continue;}

			cv::Point posn = qrcData.Patches[i]->grid_sample_Pos;
			int idx = posn.x + posn.y * qrcData.QRCImg.cols;
			double color = qrcData.Patches[i]->qr_color;
			switch(style)
			{
				case BG_STYLE_QRCODE:
				case BG_STYLE_MODULE:
					AppAlgoQRCodeRenderer::DrawModule4(posn,color,color,color,255,wa,&background);
					break;
				case BG_STYLE_WORDART:
					AppAlgoQRCodeRenderer::DrawModule4(posn,color,color,color,255,da,&background);
					break;
			}
		}

		for (int i=0;i<seg_pids.size();i++)
		{
			int pidx = seg_pids[i];
			cv::Point posn = qrcData.Patches[pidx]->grid_sample_Pos;
			int idx = posn.x + posn.y * qrcData.QRCImg.cols;
			AppAlgoQRCodeRenderer::DrawModule4(posn,0,0,0,0,wa,&background);
		}
	}
	
	//Preserve Functional Pattern
	for (int i=0;i<qrcData.Patches.size();i++)
	{
		cv::Point posn = qrcData.Patches[i]->grid_sample_Pos;
		int idx = posn.x + posn.y * qrcData.QRCImg.cols;
		double color = qrcData.Patches[i]->qr_color;
		if ( qrcData.Modules[i]->Type==4 || qrcData.Modules[i]->Type==6 ){AppAlgoQRCodeRenderer::DrawModule4(posn,color,color,color,255,wa,&background);}
 	}

	return background;
}

void AppFrame::AppAlgoQRCodeSegmentation::GapAbandon( cv::Mat& gap, int bg_color, HKCQRCData& qrcData )
{
	int da = qrcData.center_size;
	for (int i=0;i<qrcData.Patches.size();i++)
	{
		if ( qrcData.Modules[i]->Type==4 || qrcData.Modules[i]->Type==6 ){continue;}

		for (int y=-da*0.5;y<da*0.5;y++)
		{
			for (int x=-da*0.5;x<da*0.5;x++)
			{
				cv::Point posn = qrcData.Patches[i]->grid_sample_Pos;
				int idx = posn.x + x + (posn.y+y) * qrcData.QRCImg.cols;
				if (gap.data[idx]!=255 && qrcData.Patches[i]->qr_color!=bg_color){qrcData.Modules[i]->abandon = true;}
			}
		}
	}
}

void AppFrame::AppAlgoQRCodeSegmentation::GapAbandonCW( HKCQRCData& qrcData )
{
	for (int i=0;i<qrcData.CWData.size();i++)
	{
		for (int j=0;j<qrcData.CWData[i].size();j++)
		{
			bool abandon = false;
			for (int m=0;m<qrcData.CWData[i][j].module_idx.size();m++)
			{
				int module_idx = qrcData.CWData[i][j].module_idx[m];
				if (qrcData.Modules[module_idx]->abandon){abandon = true;}
			}

			if (abandon)
			{
				for (int m=0;m<qrcData.CWData[i][j].module_idx.size();m++)
				{
					int module_idx = qrcData.CWData[i][j].module_idx[m];
					cv::Point posn = qrcData.Modules[module_idx]->abandon = true;
				}
			}
		}
	}
}