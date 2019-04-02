/**
* @file AppAlgoZBar.cpp
*
* Implementation of the class methods for ZBar verification
*
* @author James Hung-Kuo Chu
*/

#include "stdafx.h"
#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"
#include "AppAlgoZBar.h"
#include "zbar\qrdetector.h"
#include "QRWordArt\QRCharFBO.h"

using namespace AppFrame;
using namespace HKCV;
using namespace HKUtils;
using namespace cv;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/*! \class AppFrame::HKCZBarGridSampling

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
bool AppFrame::HKCZBarGridSampling::Execute_Detect( HKCAppItem^ _appItem,cv::Mat src)
{
	//std:cout<<"ZBar"<<std::endl;
	if(src.channels()>1)cvtColor(src, src, CV_BGR2GRAY);

	int pSize = _appItem->Data->QRCData.module_size;

	HKCQRCData& qrcData = _appItem->Data->QRCData;

	int dim=qrcData.Ver*4+17;	/// QR codeªºªø¼e

	int _dim;
	initialize_zbar_qrdetect();

	zbar_qrdetect_results res;		
	res = singleimage_zbar_qrdetect( (uchar *)src.data, src.cols, src.rows);

	int *data_bit = GridSampling_result(&_dim);
	if (data_bit==NULL || _dim!=dim){
		free_zbar_qrdetect_result(res);
		return false;
	}else{
		system("del getbit.txt");
	}
	
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
	m_ErrorImg= cv::Mat(qrcData.QRCode.cols, qrcData.QRCode.rows, CV_8UC1, Scalar(0));
	for(int i=0;i<qrcData.Modules.size();i++)
	{
		if (qrcData.Modules[i]->Type<2 && data_bit[i] != qrcData.Modules[i]->QRC)
		{
			m_ErrorImg.data[i] = 255;
			m_Module_Error[i] = true;

			if (qrcData.Modules[i]->Type==0)
			{
				int cw_id = qrcData.Modules[i]->CWID;
				int rs_id = qrcData.Modules[i]->RSID;
				m_CW_Error[rs_id-1][cw_id-1] = true;
			}
			
			m_Num_Error_Module++;
		}
	}

	Size dsize2 = Size(qrcData.QRCImg.cols,qrcData.QRCImg.rows);
	resize(m_ErrorImg,m_ErrorImg,dsize2, 0, 0, INTER_NEAREST);

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

	m_QR_Content.clear();
	if (res.num_detected!=0)
	{	
		for (int i=0;i<res.num_detected;i++)
		{
			std::string str = res.result[i].qr_content;
			m_QR_Content.push_back(str);
		}
	}

	free_zbar_qrdetect_result(res);//free the result
	destroy_zbar_qrdetect();       //destroy the zbar QR detector

	return true;
}