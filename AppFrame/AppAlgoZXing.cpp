#include "StdAfx.h"
#include "AppAlgoZXing.h"

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppItem.h"

using namespace zxing;
using namespace zxing::qrcode;

AppAlgoZXing::AppAlgoZXing(void)
{
}


AppAlgoZXing::~AppAlgoZXing(void)
{
}

bool AppAlgoZXing::Execute_Detect_H( HKCAppItem^ item,cv::Mat src)
{
	zxing::ArrayRef<char> image;
	image = zxing::ArrayRef<char>((char*)src.data,src.rows*src.cols*src.channels());
	Ref<LuminanceSource> source = Ref<LuminanceSource>(new ImageSource(image,src.cols,src.rows,src.channels()));

	int hresult = read_image(source, true);
	
	cv::Mat h_samplegrid;
	bool flag = GetSampleGrid(h_samplegrid);

	if (flag)
	{
		if (h_samplegrid.size !=item->Data->QRCData.QRCode.size )return false;
		CalErrorInfo( item->Data->QRCData, h_samplegrid);
		return true;
	}else{
		return false;
	}
}

bool AppAlgoZXing::Execute_Detect_G( HKCAppItem^ item,cv::Mat src)
{
	zxing::ArrayRef<char> image;
	image = zxing::ArrayRef<char>((char*)src.data,src.rows*src.cols*src.channels());
	Ref<LuminanceSource> source = Ref<LuminanceSource>(new ImageSource(image,src.rows,src.cols,src.channels()));

	int gresult = read_image(source, false);

	cv::Mat g_samplegrid;
	bool flag = GetSampleGrid(g_samplegrid);


	if (flag)
	{
		if (g_samplegrid.size !=item->Data->QRCData.QRCode.size )return false;
		CalErrorInfo( item->Data->QRCData, g_samplegrid);
		return true;
	}else{
		return false;
	}
}

std::vector<zxing::Ref<zxing::Result> > AppAlgoZXing::decode( zxing::Ref<zxing::BinaryBitmap> image, zxing::DecodeHints hints )
{
	Ref<Reader> reader(new MultiFormatReader);
	return std::vector<Ref<Result> >(1, reader->decode(image, hints));
}

int AppAlgoZXing::read_image( zxing::Ref<zxing::LuminanceSource> source, bool hybrid /*= true*/ )
{
	//std::cout <<"ZXing"<< (hybrid ? "Hybrid" : "Global")<< std::endl;

	std::vector<Ref<Result> > results;
	std::string cell_result;
	int res = -1;

	try {
		Ref<Binarizer> binarizer;
		if (hybrid) {
			binarizer = new HybridBinarizer(source);
		} else {
			binarizer = new GlobalHistogramBinarizer(source);
		}
		DecodeHints hints(DecodeHints::DEFAULT_HINT);
		//hints.setTryHarder(true);
		Ref<BinaryBitmap> binary(new BinaryBitmap(binarizer));
		results = decode(binary, hints);
		res = 0;
	} catch (const ReaderException& e) {
		m_Message = "zxing::ReaderException: " + std::string(e.what());
		res = -2;
	} catch (const zxing::IllegalArgumentException& e) {
		m_Message = "zxing::IllegalArgumentException: " + std::string(e.what());
		res = -3;
	} catch (const zxing::Exception& e) {
		m_Message = "zxing::Exception: " + std::string(e.what());
		res = -4;
	} catch (const std::exception& e) {
		m_Message = "std::exception: " + std::string(e.what());
		res = -5;
	}

	m_QR_Content.clear();
	if (res == 0)
	{
		for (size_t i = 0; i < results.size(); i++)
		{
			m_QR_Content.push_back(results[i]->getText()->getText());
		}
	}
	return res;
}

bool AppAlgoZXing::GetSampleGrid( cv::Mat& samplegrid )
{
	FILE *fp = NULL;
	fp = fopen("zing_grid_sample.txt","r");
	if (fp != NULL)
	{
		int w,h;
		fscanf (fp,"%d,%d \n",&w,&h);

		if (w==0 || h==0){return false;}

		samplegrid.create(w,h,CV_8UC1);
		for (int i=0;i<h;i++)
		{
			for (int j=0;j<w;j++)
			{
				int bit;
				fscanf (fp,"%d ",&bit);
				samplegrid.data[i*w+j]=(bit==1)?0:255;
			}
			fscanf (fp,"\n");
		}
		fclose(fp);
		system("del zing_grid_sample.txt");
		return true;
	}else{
		return false;
	}
}

void AppAlgoZXing::CalErrorInfo( HKCQRCData& qrcData, cv::Mat& samplegrid)
{
	m_CW_Error.clear();
	for (int i=0;i<qrcData.CWData.size();i++)
	{
		std::vector<bool> err;
		err.resize(qrcData.CWData[i].size(),false);
		m_CW_Error.push_back(err);
	}

	m_Module_Error.clear();
	m_Module_Error.resize(qrcData.Modules.size(),false);

	m_Num_Error_Module = 0;
	m_ErrorImg = cv::Mat(qrcData.QRCode.cols, qrcData.QRCode.rows, CV_8UC1, cv::Scalar(0));
	for(int i=0;i<qrcData.QRCode.cols*qrcData.QRCode.rows;i++)
	{
		if (qrcData.Modules[i]->Type<2 && samplegrid.data[i]!=qrcData.QRCode.data[i])
		{
			m_ErrorImg.data[i] = 255;
			m_Module_Error[i] = true;
			m_Num_Error_Module ++;

			if (qrcData.Modules[i]->Type==0)
			{
				int cw_id = qrcData.Modules[i]->CWID;
				int rs_id = qrcData.Modules[i]->RSID;
				m_CW_Error[rs_id-1][cw_id-1] = true;
			}
		}
	}
	cv::Size size = cv::Size(qrcData.QRCImg.cols,qrcData.QRCImg.rows);
	cv::resize(m_ErrorImg,m_ErrorImg,size, 0, 0, cv::INTER_NEAREST);

	m_Num_Error_CW.clear();
	for (int i=0;i<qrcData.CWData.size();i++)
	{
		int t=0;
		for (int j=0;j<qrcData.CWData[i].size();j++)
		{
			if (m_CW_Error[i][j]){t++;}
		}
		m_Num_Error_CW.push_back(t);
	}
}
