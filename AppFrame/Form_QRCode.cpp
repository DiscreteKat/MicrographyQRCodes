/**
* @file Form_QRCode.cpp
*
* Implementation of QR code generator's functions
*
* @author James Hung-Kuo Chu
*/

#include "StdAfx.h"
#include "Form1.h"
using namespace AppFrame;
using namespace DevComponents::DotNetBar;
using namespace DevComponents::Editors;
using namespace HKOGLPanel;
using namespace System::Collections::Generic;

#include "AppAlgoQRCodeRenderer.h"

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::Form1

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                         QR code functions                           */
/// QR code generator's action
void Form1::QRC_Action(System::String^ _action)
{
	if(!mp_AppItem) return;

	HKCQRCParam^ qrcParam = mp_AppItem->Param->QRCode;
	if(System::String::Compare("ModuleSize", _action) == 0)
	{
		HKCQRCParam^ qrParam = mp_AppItem->Param->QRCode;
		ComboItem^ item = (ComboItem^)PDBFileCombo->SelectedItem;
		cli::array<System::Char>^ chars = {'X'};
		cli::array<System::String^>^ split = item->Text->Split(chars);
		int pSize = System::Convert::ToInt32(split[0]);
		qrParam->Wa = pSize;
	}
	else if(System::String::Compare("TEXT", _action) == 0)
	{
		qrcParam->Text = QRCText->Text;		
		this->ParamGrid->Refresh();
	}
	else if(System::String::Compare("VERSION", _action) == 0)
	{		
		ComboItem^ item = (ComboItem^)QRCVerCombo->SelectedItem;
		if(item) qrcParam->Version = System::Convert::ToInt32(item->Text);		
		this->ParamGrid->Refresh();
	}
	else if(System::String::Compare("ECL", _action) == 0)
	{		
		int idx = QRCECLCombo->SelectedIndex;		
		if(idx != -1) qrcParam->ECLvl = HKEECL(idx);		
		this->ParamGrid->Refresh();
	}	
	else if(System::String::Compare("GENERATE", _action) == 0)
	{
		std::cout<<"Generate QRCode"<<std::endl;
		HKCAlgorithm^ qrcObject = gcnew HKCQRCGen;
		if(!qrcObject->Execute(mp_AppItem))
		{
			Console::WriteLine(qrcObject->Abbrev + ": Failed!");	
			return;
		}
		std::cout<<" QR Size: "<<mp_AppItem->Data->QRCData.QRCImg.cols<<std::endl;
		std::cout<<" Wa: "<<mp_AppItem->Data->QRCData.module_size<<std::endl;
		std::cout<<" Da: "<<mp_AppItem->Data->QRCData.center_size<<std::endl;

		HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
		cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());

		cv::Point2d offset = mp_AppItem->Data->QRCData.offset;
		cv::Mat&    qrcimg =mp_AppItem->Data->QRCData.QRCImg;
		cv::Rect    clipping(offset.x,offset.y,qrcimg.cols,qrcimg.rows);
		{/// Update the QR code image
			if(mp_AppItem->Find("QRCode")) mp_AppItem->Delete("QRCode");
			cv::Mat map(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0));
			cv::Mat temp;
			cv::cvtColor(mp_AppItem->Data->QRCData.QRCImg,temp,CV_GRAY2BGRA);
			temp.copyTo(map(clipping));	
			HKCMediaItem^ qrcItem = mp_AppItem->New(map, "QRCode", mp_GLPanel);
			HKCImageProp^ qrcProp = (HKCImageProp^)qrcItem->Prop;
			qrcProp->Texture->MAG_Filter = HKETexFltr::Nearest;
			qrcProp->Texture->MIN_Filter = HKETexFltr::Nearest;
			mp_AppItem->MoveTo("QRCode", 1); /// Move the layer to top2
		}

		{//Quite Zone
 			int wa = mp_AppItem->Data->QRCData.module_size;
// 			cv::Mat quiet(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)) ;
// 			int border_minX = max(offset.x-wa,0);
// 			int border_minY = max(offset.y-wa,0);
// 			int border_maxX = min(offset.x+clipping.width +wa,srcImg->cols);
// 			int border_maxY = min(offset.y+clipping.height+wa,srcImg->rows);
// 			cv::Rect border(border_minX,border_minY,border_maxX-border_minX,border_maxY-border_minY);
// 			quiet(border).setTo(cv::Scalar(255,255,255,250));
// 			quiet(clipping).setTo(cv::Scalar(0,0,0,0));

 			cv::Mat quiet(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)) ;
  			int border_minX = offset.x-mp_AppItem->Data->QRCData.module_size*0.5-0.5;
  			int border_minY = offset.y-mp_AppItem->Data->QRCData.module_size*0.5-0.5;
 	 		int border_maxX = offset.x+clipping.width +mp_AppItem->Data->QRCData.module_size*0.5-0.5;
 	 		int border_maxY = offset.y+clipping.height+mp_AppItem->Data->QRCData.module_size*0.5-0.5;
 	

 			AppAlgoQRCodeRenderer::DrawModule4( cv::Point(border_minX,border_minY), 255,255,255,220, wa,&quiet);
 			for (int i=1;i<9;i++)
 			{
 				AppAlgoQRCodeRenderer::DrawModule4( cv::Point(border_minX+i*wa,border_minY     ), 255,255,255,220, wa,&quiet);
 				AppAlgoQRCodeRenderer::DrawModule4( cv::Point(border_minX     ,border_minY+i*wa), 255,255,255,220, wa,&quiet);
 			}
 
 			AppAlgoQRCodeRenderer::DrawModule4( cv::Point(border_maxX,border_minY), 255,255,255,220, wa,&quiet);
  			for (int i=1;i<9;i++)
  			{
 				AppAlgoQRCodeRenderer::DrawModule4( cv::Point(border_maxX-i*wa,border_minY     ), 255,255,255,220, wa,&quiet);
 				AppAlgoQRCodeRenderer::DrawModule4( cv::Point(border_maxX     ,border_minY+i*wa), 255,255,255,220, wa,&quiet);
  			}
 
 			AppAlgoQRCodeRenderer::DrawModule4( cv::Point(border_minX,border_maxY), 255,255,255,220, wa,&quiet);
 			for (int i=1;i<9;i++)
 			{
 				AppAlgoQRCodeRenderer::DrawModule4( cv::Point(border_minX+i*wa,border_maxY     ), 255,255,255,220, wa,&quiet);
 				AppAlgoQRCodeRenderer::DrawModule4( cv::Point(border_minX     ,border_maxY-i*wa), 255,255,255,220, wa,&quiet);
 			}
			mp_AppItem->Data->QRCData.QuietZone = quiet.clone();
		}
		
		mp_GLPanel->Invalidate();

		/// Rebuild layers
		mp_AppLayerMgr->Build(this->LayerTree, mp_AppItem);
		this->ParamGrid->Refresh();

		//Centerize the media
		GLPanel_Focus(mp_AppItem);
		this->GLPanel_Focus(mp_AppItem);

		/*HSS* Store QR code
 		cv::Size size(880,880);
 		cv::Mat output = mp_AppItem->Data->QRCData.QRCImg.clone();
 		cv::resize(output,output,size,0,0,cv::INTER_NEAREST);
 		cv::imwrite("QR.png",output);
		//**/
		MQRC_Action("PRE_PROCESS");
	}
	
}
void Form1::QRCInf_Action(DevComponents::DotNetBar::LabelItem^ Label,AppAlgoQRCodeEvaluation QRevaluation)
{
	Label->Text="";
	double Avg= Math::Round(QRevaluation.QRcodeQuality() * 100000.0) / 100000.0;
	Label->Text+="Avg  Energy: "+Avg+"\n";

	Label->Text+=" Energy M: "+QRevaluation.ZbarErrPid().size() + "\n" ;
	Label->Text+=" CW Error: ";
	
	for (int i = 0 ; i <QRevaluation.CW_Err().size();i++)
	{
		Label->Text+=QRevaluation.CW_Err()[i];
		if (i!=QRevaluation.CW_Err().size()-1)
			Label->Text+=",";
	}
	Label->Text+=" \n";
	Label->Text+="Zbar "+QRevaluation.Zbar_Correct+"\n";
	Label->Text+="ZXing "+QRevaluation.Zxing_Correct+"\n";
}