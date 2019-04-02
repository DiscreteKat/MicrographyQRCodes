/**
* @file AppAlgoQRC.cpp
*
* Implementation of the class methods for QR code generator
*
* @author James Hung-Kuo Chu
*/

#include "stdafx.h"
#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"
#include "AppAlgoQRC.h"
#include "AppUtils.h"

using namespace AppFrame;
using namespace HKCV;
using namespace HKUtils;
using namespace cv;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/*! \class AppFrame::HKCQRCGen1

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                       Algorithm Operations                          */
/// Generate QR code
bool HKCQRCGen::Execute(HKCAppItem^ _appItem)
{
	if(!_appItem) return false;		

	HKCQRCData& qrcData = _appItem->Data->QRCData;	
	qrcData.Clear(); /// Clear old data

	/// Get data ready
	HKCQRCParam^ qrcParam = _appItem->Param->QRCode;
	qrcData.Text = MarshalString(qrcParam->Text);
	qrcData.Ver = qrcParam->Version;
	qrcData.ECL = (int)qrcParam->ECLvl;	
	qrcData.module_size = qrcParam->Wa;
	qrcData.center_size = qrcParam->Da;//3;//ceil(qrcParam->Wa/3.0);
	
	qrcData.offset = cv::Point2d(qrcParam->offsetX,qrcParam->offsetY);
	/////////////////////////////////////////////////
	/// Generate QR code data
	/////////////////////////////////////////////////
	qrcData.isReady = GenerateQRcode( qrcData );
	if (!qrcData.isReady){return false;}
	
	BuildQRImg(qrcData);

	//resize input Image
	HKCMediaItem^ srcItem = _appItem->Find("Source");
	if(!srcItem) return false;
	Mat* srcImg = (Mat*)(srcItem->Media->Data());
	//cv::Size newSize = qrcData.QRCImg.size();
	//cv::resize(*srcImg, *srcImg, newSize, 0, 0, INTER_CUBIC);
	
	//Debug Using
	DrawCWContour(qrcData,&qrcData.CWContour);

	/// Update parameters
	qrcParam->ECCap   = qrcData.ECC;
	qrcParam->RSNum   = qrcData.RSNum;
	qrcParam->Version = qrcData.Ver;
	qrcParam->QRSize  = System::Drawing::Size(qrcData.QRCode.cols, qrcData.QRCode.rows);
	qrcParam->ImgSize = System::Drawing::Size(qrcData.QRCImg.cols, qrcData.QRCImg.rows);

	srcItem->Update();
	return true;
}

bool AppFrame::HKCQRCGen::GenerateQRcode( HKCQRCData& qrcData )
{
	int QRMask=qrcData.QRMask;					/// Mask預設為-1代表自動找尋	
	
	QRencodeMode qrMode=QR_MODE_8;	/// 輸入字的編碼方式
	QRecLevel QRlv=(QRecLevel)(int(qrcData.ECL));/// QR code 的 error correction level
	char inputStringChar[1024];		/// QR code產生器的輸入字串需要char陣列
	int stringSize=qrcData.Text.length();
	qrcData.Text.copy(inputStringChar,stringSize,0); 
	*(inputStringChar+stringSize)='\0'; 
	//cout<<qrcData.Text.size()<<endl;
	//cout<<qrcData.Text.length()<<endl;
	//cout<<inputStringChar<<endl;
	//cout<<sizeof(inputStringChar)<<endl;
	QRcode *qrcodeB;				/// 用來接收QR code用
	QRcode *qrcodeC;				/// 用來接收RS Block用
	QRcode *qrcodeT;				/// 用來接收code word用
	int QRSize=qrcData.Ver*4+17;	/// QR code的長寬

	/// 更改flag讓QRcode_encodeString是產生QR碼
	changeColorFlag(0); 
	changeCodeWFlag(0);
	changeMaskFlag(-1);
	changeLocateFlag(true);
	/// 產生QR code
	qrcodeB = QRcode_encodeString(inputStringChar,qrcData.Ver,(QRecLevel)QRlv,qrMode,1);
	if(!qrcodeB)
	{
		Console::WriteLine("HKCQRCGen1::Execute() : Generate QR code eed!");
		return false;
	}
	qrcData.QRMask = maskFlag;

	/// Check if the version is changed
	if(qrcData.Ver != qrcodeB->version)
	{
		qrcData.Ver = qrcodeB->version; /// 依照產生的QR碼重新更改version(產生後可能會變大)
		QRSize=qrcData.Ver*4+17;
		Console::WriteLine("HKCQRCGen1::Execute() : The version of QR code is changed to " + Int32(qrcData.Ver).ToString() + "!");
	}

	/// 更改flag讓QRcode_encodeString是產生RS Map (index)
	changeColorFlag(1);
	changeCodeWFlag(0);
	changeMaskFlag(-2);
	changeLocateFlag(false);
	/// 產生RS block index map
	qrcodeC = QRcode_encodeString(inputStringChar,qrcData.Ver,(QRecLevel)QRlv,qrMode,1);
	if(!qrcodeC)
	{
		Console::WriteLine("HKCQRCGen1::Execute() : Generate RS block map failed!");
		free(qrcodeB);
		return false;
	}

	/// 更改flag讓QRcode_encodeString是產生CW Map (index)
	changeColorFlag(1);
	changeCodeWFlag(3);
	changeMaskFlag(-2);
	changeLocateFlag(false);
	/// 產生code word index map
	qrcodeT = QRcode_encodeString(inputStringChar,qrcData.Ver,(QRecLevel)QRlv,qrMode,1);
	if(!qrcodeT)
	{
		Console::WriteLine("HKCQRCGen1::Execute() : Generate code word map failed!");
		free(qrcodeB);
		free(qrcodeC);
		return false;
	}

	/////////////////////////////////////////////////
	/// Compute QR code data
	/////////////////////////////////////////////////
	/// Update the error correction information
	int qrSpec[6];
	QRspec_getEccSpec(qrcData.Ver, QRlv, qrSpec);
	qrcData.ECC = QRspec_rsEcCapacity(qrSpec);	
	qrcData.RSNum = QRspec_rsBlockNum(qrSpec);
	qrcData.RSBNum[0]   = QRspec_rsBlockNum1(qrSpec);
	qrcData.RSBNum[1]   = QRspec_rsBlockNum2(qrSpec);
	qrcData.RSBcwNum[0] = QRspec_rsCodeWords1(qrSpec);
	qrcData.RSBcwNum[1] = QRspec_rsCodeWords2(qrSpec);
	qrcData.RSBdcNum[0] = QRspec_rsDataCodes1(qrSpec);
	qrcData.RSBdcNum[1] = QRspec_rsDataCodes2(qrSpec);
	qrcData.RSBecNum[0] = QRspec_rsEccCodes1(qrSpec);
	qrcData.RSBecNum[1] = QRspec_rsEccCodes2(qrSpec);

	///***Build CWData
	double lower_bound=1;
	QRCWData& all_cw_data = qrcData.CWData;
	all_cw_data.clear();
	for (int k=0;k<2;k++)
	{
		for (int i=0;i<qrcData.RSBNum[k];i++)
		{
			QRRSCode rs_data;
			for (int j=0;j<qrcData.RSBcwNum[k];j++)
			{
				QRCW cw;
				rs_data.cw_data.push_back(cw);
			}
			rs_data.max_error = (int)ceil((double)qrcData.RSBecNum[k]*0.5);
			all_cw_data.push_back(rs_data);
		}
	}

	cv::Mat& qrcode = qrcData.QRCode;
	cv::Mat& qrcRS = qrcData.RSMap;
	cv::Mat& qrcCW = qrcData.CWMap;
	qrcode.create(QRSize,QRSize,CV_8UC1);
	qrcRS.create(QRSize,QRSize,CV_32SC1);
	qrcCW.create(QRSize,QRSize,CV_32SC1);

	VecMdu& qrcModules = qrcData.Modules;
	qrcModules.resize(QRSize*QRSize);

	for(int y = 0; y < QRSize; ++y)
	{
		uchar* qrcPtr = qrcode.ptr<uchar>(y);
		int*   RSPtr  = qrcRS.ptr<int>(y);
		int*   CWPtr  = qrcCW.ptr<int>(y);
		int    yStep = y*QRSize;
		for(int x = 0; x < QRSize; ++x)
		{
			int xStep = yStep + x;
			
			/// Pixel color (Black/White)
			unsigned char qrcVal = (qrcodeB->data[xStep] & 1) ? 0 : 255;
			qrcPtr[x] = qrcVal;			

			/// Type of module
			// if (int)qrcodeC->data[xStep] == 136||(int)qrcodeC->data[xStep] == 137 => version information
			// if (int)qrcodeC->data[xStep] == 132||(int)qrcodeC->data[xStep] == 129 => Format Information
			// if (int)qrcodeC->data[xStep] == 160||(int)qrcodeC->data[xStep] == 161 => Alignment Patterns
			// if (int)qrcodeC->data[xStep] == 144||(int)qrcodeC->data[xStep] == 145 => Timing Patterns
			// if (int)qrcodeC->data[xStep] == 192||(int)qrcodeC->data[xStep] == 193  => Separators Patterns & Position Detection Patterns
			// if (int)qrcodeC->data[xStep] == 82 => Remaining Bits

			int mType = -1;
			int rsVal = (int)qrcodeC->data[xStep];
			if(rsVal > 0 && rsVal < 82)           mType = 0;	/// Data codeword
			else if(rsVal == 82)				  mType = 1;	/// Remaining Bits
			else if(rsVal == 136 || rsVal == 137) mType = 2;	/// Version Information
			else if(rsVal == 132 || rsVal == 129) mType = 3;	/// Format Information
			else if(rsVal == 160 || rsVal == 161) mType = 4;	/// Alignment Patterns
			else if(rsVal == 144 || rsVal == 145) mType = 5;	/// Timing Patterns
			else if(rsVal == 192 || rsVal == 193) mType = 6;	/// Separators Patterns & Position Detection Patterns

			/// Index of RS block
			RSPtr[x] = (mType == 0) ? rsVal : -1;

			/// Index of code word in RS block
			int cwVal = (int)qrcodeT->data[xStep];
			CWPtr[x] = (mType == 0) ? cwVal : -1;			

			/// Get module data
			HKCModule* qrcModule = new HKCModule;
			qrcModule->Type = mType;
			qrcModule->Pos = cv::Point(x,y);		/// Image location
			qrcModule->QRC = (qrcVal) ? 0 : 1;	    /// QR code value(1: Black, 0: white)
			qrcModule->RSID = rsVal;				/// RS block index (1-based index)
			qrcModule->CWID = cwVal;				/// Code word index (1-based index)
			qrcModules[xStep] = qrcModule;

			/// Get RS block and code word data
			if(mType == 0)
			{
				all_cw_data[rsVal-1][cwVal-1].module_idx.push_back(xStep);
			}
		}
	}

	qrcData.QRCBitData = g_QRBitData;

	free(qrcodeB);
	free(qrcodeC);
	free(qrcodeT);
	return true;
}

void AppFrame::HKCQRCGen::BuildQRImg( HKCQRCData& data)
{
	int wa = data.module_size;
	/// Once we have the original QR code image
	Mat& qrcImg = data.QRCImg;

	cv::Size newSize = data.QRCode.size();
	newSize.width  *= wa;
	newSize.height *= wa;
	cv::resize(data.QRCode, qrcImg, newSize, 0, 0, INTER_NEAREST);

	//initial image patch
	VecPatch& qrcPatches = data.Patches;
	qrcPatches.resize(data.Modules.size());
	for(int i=0;i<data.Modules.size();i++)
	{
		HKCPatchData* qrcPatch = new HKCPatchData;
		qrcPatches[i]=qrcPatch;

		int _x=wa*(data.Modules[i]->Pos.x)+wa/2;
		int _y=wa*(data.Modules[i]->Pos.y)+wa/2;

		//calculate patch left top position
		cv::Point& patch_pos=data.Patches[i]->patch_Pos;
		int start=(_x*data.QRCImg.cols+_y)-(data.QRCImg.cols+1)*(wa/2);
		patch_pos.x=start/data.QRCImg.cols;
		patch_pos.y=start%data.QRCImg.cols;

		qrcPatches[i]->grid_sample_Pos = cv::Point(patch_pos.x+wa/2,patch_pos.y+wa/2);
		int idx = qrcPatches[i]->grid_sample_Pos.y*data.QRCImg.cols+qrcPatches[i]->grid_sample_Pos.x;
		qrcPatches[i]->qr_color = (int)data.QRCImg.data[idx];
	}
}

void AppFrame::HKCQRCGen::DrawCWContour( HKCQRCData& data,cv::Mat* dst )
{
	dst->create(data.QRCImg.rows,data.QRCImg.cols,CV_8UC4);

	cv::Mat contour;
	contour = cv::Mat::zeros(data.QRCImg.rows,data.QRCImg.cols, CV_8UC1);
	for (int i=0;i<data.CWData.size();i++)
	{
		for (int j=0;j<data.CWData[i].size();j++)
		{
			cv::Mat edge = cv::Mat::zeros(data.QRCImg.rows,data.QRCImg.cols, CV_8UC1);
			for (int k=0;k<data.CWData[i][j].module_idx.size();k++)
			{
				int m_id = data.CWData[i][j].module_idx[k];
				cv::Point posn = data.Patches[m_id]->patch_Pos;
				for (int y=0;y<data.module_size;y++)
				{
					for (int x=0;x<data.module_size;x++)
					{
						edge.data[(posn.y+y)*data.QRCImg.rows+posn.x+x] = 255;
					}
				}
			}
			cv::Canny(edge,edge,0,0,3);
			contour+=edge;	
		}
	}

	for (int i=0;i<data.QRCImg.rows*data.QRCImg.cols;i++)
	{
		if (contour.data[i]==255)
		{
			dst->data[i*4  ] = 100;
			dst->data[i*4+1] = 100;
			dst->data[i*4+2] = 100;
			dst->data[i*4+3] = 255;
		}else{
			dst->data[i*4  ] = 0;
			dst->data[i*4+1] = 0;
			dst->data[i*4+2] = 0;
			dst->data[i*4+3] = 0;
		}
	}
}