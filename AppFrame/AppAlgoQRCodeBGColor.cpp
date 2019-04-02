#include "StdAfx.h"
#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppUtils.h"

#include "AppAlgoQRCodeBGColor.h"
#include "AppAlgoBinarization.h"
#include "AppAlgoQRCodeRenderer.h"

#include "HKCV.h"

bool AppFrame::AppAlgoQRCBGColor::Execute( HKCAppItem^ _appItem )
{
	int& background_color = _appItem->Data->WordArtEvi.background_color;
	if ( background_color != -1 )return false;

	HKCMediaItem^ srcItem = _appItem->Find("Source");
	//load data
	cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());
	cv::Mat& segment_img = _appItem->Data->WordArtEvi.segment_img;
	HKCQRCData& qrcData = _appItem->Data->QRCData;
	cv::Mat& qrcode = qrcData.QRCode;
	cv::Mat& qrcode_img = qrcData.QRCImg;
//	cv::imshow("qrcode",qrcode);
//	cv::imshow("qrcode_img",qrcode_img);
	int wa = _appItem->Data->QRCData.module_size;
	int da = _appItem->Data->QRCData.center_size;

	//===============Decide the Background Color===============
	cv::Mat sample_1(srcImg->cols,srcImg->rows,CV_8UC3,cv::Scalar(0,0,0));		//黑色背景
	cv::Mat sample_2(srcImg->cols,srcImg->rows,CV_8UC3,cv::Scalar(255,255,255));//白色背景

	for(int i=0;i<qrcData.Patches.size();i++)
	{
		cv::Point posn = qrcData.Patches[i]->grid_sample_Pos;
		int idx = posn.y*segment_img.rows + posn.x;
		if (segment_img.data[idx]!=255)
		{
			double r = srcImg->data[idx*3+2];
			double g = srcImg->data[idx*3+1];
			double b = srcImg->data[idx*3+0];
			AppAlgoQRCodeRenderer::DrawModule3(posn,r,g,b,da,&sample_1);
			AppAlgoQRCodeRenderer::DrawModule3(posn,r,g,b,da,&sample_2);
		}
	}
	//cv::imshow("sample_1",sample_1);
	AppAlgoBinarization bin_1(sample_1);
	bin_1.ZBar_Binarization(&sample_1);
	//cv::imshow("sample_1_bin",sample_1);

	//cv::imshow("sample_2",sample_2);
	AppAlgoBinarization bin_2(sample_2);
	bin_2.ZBar_Binarization(&sample_2);
	//cv::imshow("sample_2_bin",sample_2);

	int sample_1_err = 0;//黑色背景=>Sample要是白色
	int sample_2_err = 0;//白色背景=>Sample要是黑色
	for(int i=0;i<qrcData.Patches.size();i++)
	{
		cv::Point posn = qrcData.Patches[i]->grid_sample_Pos;
		int idx = posn.y*segment_img.rows + posn.x;
		if (segment_img.data[idx]!=255)
		{
			if (sample_1.data[idx]!=255){sample_1_err++;}
			if (sample_2.data[idx]!=0  ){sample_2_err++;}
		}
	}

	if(sample_1_err>sample_2_err){background_color=255;}
	else{background_color=0;}

	//std::cout<<sample_1_err<<" "<<sample_2_err<<std::endl;
	

// 	if (background_color==0){HKCV::Brightness_Contrast(*srcImg,*srcImg,0.15,0.2);}
//  	else{HKCV::Brightness_Contrast(*srcImg,*srcImg,-0.15,0.1);}
	//cv::waitKey();
	return true;
}