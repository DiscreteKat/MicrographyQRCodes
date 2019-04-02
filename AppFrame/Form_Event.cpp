/**
* @file Form_Event.cpp
*
* Implementation of Property value changed events
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "StdAfx.h"
#include "Form1.h"
#include "AppUtils.h"

using namespace AppFrame;
using namespace DevComponents::DotNetBar;
using namespace DevComponents::Editors;
using namespace HKOGLPanel;
using namespace HKCV;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::Form1

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                   Property value changed events                     */
/// Property value changed event of application properties
System::Void Form1::PropGrid_PropertyValueChanged(System::Object^ s, System::Windows::Forms::PropertyValueChangedEventArgs^ e) 
{	
	if(!mp_AppItem) return;	

	/// Update layers
	this->mp_AppLayerMgr->Update(this->LayerTree, mp_AppItem);
	this->mp_AppLayerMgr->UpdateCandidate(this->CandidateLayer, mp_AppItem);
	this->mp_AppLayerMgr->UpdateWordArtLayer(this->CandidateLayer, mp_AppItem);
	/// Refresh GLPanels
	this->GLPanel_Refresh();
}

/// Property value changed event of application parameters
System::Void Form1::ParamGrid_PropertyValueChanged(System::Object^ s, System::Windows::Forms::PropertyValueChangedEventArgs^ e) 
{	
	if(!mp_AppItem) return;
}

/// Property value changed event of tool properties
System::Void Form1::ToolGrid_PropertyValueChanged(System::Object^  s, System::Windows::Forms::PropertyValueChangedEventArgs^  e) 
{
	if(!mp_AppItem) return;
}

/// Property value changed event of painter property
System::Void Form1::PntrProp_PropertyValueChanged(System::Object^ s, HKCPropEventArgs^ e)
{
	HKCPntrProp^ pntrProp = dynamic_cast<HKCPntrProp^>(s);

	switch(e->Property)
	{
	case HKEPropArg::STROKE_SIZE:
		m_StrokeSizeSliderSuspend = true;
		PntrMStrkSize->Value = pntrProp->Size;
		m_StrokeSizeSliderSuspend = false;		
		break;	
	}	
}

/// Property value changed event of GrabCut property
System::Void Form1::GCProp_PropertyValueChanged(System::Object^ s, HKCPropEventArgs^ e)
{
	HKCPntrProp^ pntrProp = dynamic_cast<HKCPntrProp^>(s);
	
	switch(e->Property)
	{
	case HKEPropArg::STROKE_SIZE:
		m_StrokeSizeSliderSuspend = true;
		GCMStrkSize->Value = pntrProp->Size;
		m_StrokeSizeSliderSuspend = false;		
		break;	
	}	
}

/// Property value changed event of QR code parameters
System::Void Form1::QRCParam_PropertyValueChanged(System::Object^ s, HKCParamEventArgs^ e)
{
	HKCQRCParam^ qrcParam = dynamic_cast<HKCQRCParam^>(s);
	switch(e->Param)
	{
	case HKEParamArg::QRC_TEXT:
		QRCText->Text = qrcParam->Text;
		break;	
	case HKEParamArg::QRC_VERSION:
		{
			ComboItem^ selItem = nullptr;
			for each(ComboItem^ item in QRCVerCombo->Items)
			{
				if(System::String::Compare(item->Text, Int32(qrcParam->Version).ToString()) == 0)
				{
					selItem = item;				
					break;
				}
			}			
			if(selItem) QRCVerCombo->SelectedItem = selItem;
			else qrcParam->Version = 5;

			int qrSpec[6];
			QRspec_getEccSpec(qrcParam->Version, (QRecLevel)(int(qrcParam->ECLvl)), qrSpec);
			qrcParam->RSNum = QRspec_rsBlockNum(qrSpec);
			qrcParam->ECCap = QRspec_rsEcCapacity(qrSpec);			
		}		
		break;
	case HKEParamArg::QRC_ECLEVEL:
		{
			QRCECLCombo->SelectedIndex = (int)qrcParam->ECLvl;
			
			int qrSpec[6];
			QRspec_getEccSpec(qrcParam->Version, (QRecLevel)(int(qrcParam->ECLvl)), qrSpec);
			qrcParam->RSNum = QRspec_rsBlockNum(qrSpec);
			qrcParam->ECCap = QRspec_rsEcCapacity(qrSpec);			
		}
		break;	
	case HKEParamArg::QRC_WA:
		{
			System::String^ pSize = Int32(qrcParam->Wa).ToString() + "X" + Int32(qrcParam->Wa).ToString();
			PDBSizeLabel->Text = L"Module Size: " + pSize;			
		}				
		break;
	case HKEParamArg::QRC_COLOR:
		{
			mp_AppItem->Data->CurrentWordArtID=0;
			QRWordArt::QRStringLines& splines=mp_AppItem->Data->WordArtData[0].splines;
			AppAlgoTextColor	text_color(mp_AppItem);
			text_color.Enable((int)mp_AppItem->Param->WordArt->ColorMode);
			for (int i=0;i<splines.size();i++){text_color.Execute(*splines[i]);}
			UpdateMQRCLayers(false);
		}				
		break;
	case HKEParamArg::QRC_BACKGROUND_STYLE:
		{
			mp_AppItem->Data->WordArtEvi.background_style = (int)mp_AppItem->Param->WordArt->BGStyle;
			MQRC_Action("SUPERIMPOSING");
			UpdateMQRCLayers(false);
		}				
		break;
	case HKEParamArg::QRC_BACKGROUND_COLOR:
	{
		switch (mp_AppItem->Param->WordArt->BGColor) {
		case BG_COLOR::AUTO:
			mp_AppItem->Data->WordArtEvi.background_color = -1;
		case BG_COLOR::BLACK:
			mp_AppItem->Data->WordArtEvi.background_color = 0;
		case BG_COLOR::WHITE:
			mp_AppItem->Data->WordArtEvi.background_color = 255;
		}
		MQRC_Action("BACKGROUNDCOLOR");
		UpdateMQRCLayers(true);
	}
	break;
	}

	this->ParamGrid->Refresh();
}