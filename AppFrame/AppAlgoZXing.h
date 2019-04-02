#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <opencv\cv.h>
#include <opencv\highgui.h>

#include <zxing/Binarizer.h>
#include <zxing/BinaryBitmap.h>
#include <zxing/MultiFormatReader.h>

#include <zxing/DecodeHints.h>
#include <zxing/qrcode/QRCodeReader.h>

#include <zxing/Result.h>

#include <exception>
#include <zxing/Exception.h>
#include <zxing/ReaderException.h>
#include <zxing/common/IllegalArgumentException.h>

#include <zxing/common/Counted.h>
#include <zxing/common/HybridBinarizer.h>
#include <zxing/common/GlobalHistogramBinarizer.h>

#include "AppData.h"
#include "ZXing/ImageSource.h"

class AppAlgoZXing
{
private:
	cv::Mat           m_ErrorImg;
	std::vector<bool> m_Module_Error;
	std::vector<std::vector<bool>> m_CW_Error;

	int              m_Num_Error_Module;
	std::vector<int> m_Num_Error_CW;

	std::vector<std::string> m_QR_Content;

	std::string m_Message;
public:
	AppAlgoZXing(void);
	~AppAlgoZXing(void);

	//Hybrid
	bool Execute_Detect_H( HKCAppItem^ item,cv::Mat src);
	//Global
	bool Execute_Detect_G( HKCAppItem^ item,cv::Mat src);

	cv::Mat GetErrorImg(){return m_ErrorImg;}
	std::vector<bool> GetMError(){return m_Module_Error;}
	std::vector<std::vector<bool>> GetCWError(){return m_CW_Error;}

	int N_ErrorModule(){return m_Num_Error_Module;};
	std::vector<int> N_ErrorCW(){return m_Num_Error_CW;}

	std::vector<std::string>& QRContent(){return m_QR_Content;}
	std::string Message(){return m_Message;}
private:
	std::vector<zxing::Ref<zxing::Result> > decode(zxing::Ref<zxing::BinaryBitmap> image, zxing::DecodeHints hints);

	int read_image(zxing::Ref<zxing::LuminanceSource> source, bool hybrid = true);

	bool GetSampleGrid(cv::Mat& samplegrid);
	void CalErrorInfo(HKCQRCData& qrcData,cv::Mat& samplegrid);
};

