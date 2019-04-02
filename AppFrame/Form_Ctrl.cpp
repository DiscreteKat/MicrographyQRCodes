/**
* @file Form_Ctrl.cpp
*
* Implementation of form control functions
*
* @author James Hung-Kuo Chu
*/

#include "StdAfx.h"
#include "Form1.h"

#include "QRWordArt/QRCharacterIO.h"
#include "AppAlgoProbabilityModel.h"

using namespace AppFrame;
using namespace DevComponents::DotNetBar;
using namespace HKOGLPanel;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::Form1

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                      Form control functions                         */
/// Customize ui of the form
void Form1::Init_GUI(void)
{		
	/////////////////////////////////////////////////
	/// Initialize GLPanel control
	/////////////////////////////////////////////////	
	HKOGLPanel1->Look_At(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	

	/////////////////////////////////////////////////
	/// Initialize QR Code generator
	/////////////////////////////////////////////////
	QRCVerCombo->SelectedIndex = 0;

	/////////////////////////////////////////////////
	/// Initialize debug zone button
	/////////////////////////////////////////////////	
	this->AppDebugBtn->Checked = true;
	this->AppDumpBtn->Checked = true;	
}

/// Initialize data of the form
void Form1::Init_Data(void)
{	
	/////////////////////////////////////////////////
	/// Initialize global variables
	/////////////////////////////////////////////////
	/// support Chinese text format
	std::locale::global(locale(""));

	/// Random number generator
	g_RNG = cv::RNG(0xffffffff);	

	/// Enable/Disable console debug
	AppGlobal::g_Debug = this->AppDebugBtn->Checked;
	AppGlobal::g_Dump = this->AppDumpBtn->Checked;

	/// Initialize pointer to the application form
	AppGlobal::g_Form = this;	

	/// Initialize I/O information	
	AppGlobal::g_AppDir	= Application::StartupPath;
	DirectoryInfo^ appDir = gcnew DirectoryInfo(Application::StartupPath);
	AppGlobal::g_PrjDir = appDir->Parent->FullName;
	AppGlobal::g_DebugDir = AppGlobal::g_PrjDir + L"\\Temp\\";		

	/////////////////////////////////////////////////
	/// Initialize tool control variables
	/////////////////////////////////////////////////
	m_PlayerFrameSliderSuspend = false;
	m_StrokeSizeSliderSuspend = false;

	/////////////////////////////////////////////////
	/// Initialize GLPanel control variables
	/////////////////////////////////////////////////
	mp_GLPanels = gcnew List<HKOGLPanelControl^>;
	mp_GLPanels->Add(HKOGLPanel1);
	mp_GLPanel = HKOGLPanel1;	

	/////////////////////////////////////////////////
	/// Initialize application variables
	/////////////////////////////////////////////////
	mp_AppState		= HKCStateIdle::InstancePtr();
	mp_AppItem		= nullptr;	
	mp_AppRendr		= gcnew HKCRenderDef;
	mp_AppIOMgr		= gcnew HKCIOMgrDef;
	mp_AppLayerMgr	= gcnew HKCLayerMgrDef;	
	mp_AppToolMgr	= gcnew HKCToolMgrDef;		

	/////////////////////////////////////////////////
	/// Initialize application tools
	/////////////////////////////////////////////////
	/// Add painter tool
	AppGlobal::g_PntrLabel = AppPaintBtn->CommandParameter->ToString();
	HKCAppTool^ painter = gcnew HKCPainter(AppGlobal::g_PntrLabel);	
	HKCPntrProp^ prop = dynamic_cast<HKCPntrProp^>(painter->Prop);
	prop->PropertyChanged += gcnew PropEventHandler(this, &Form1::PntrProp_PropertyValueChanged);
	prop->Size = 10;
	prop->Color = Drawing::Color::Red;	
	mp_AppToolMgr->Add(painter);

	/// Add GrabCut tool
	AppGlobal::g_GCLabel = AppGCBtn->CommandParameter->ToString();
	HKCAppTool^ grabcutr = gcnew HKCGrabCutr(AppGlobal::g_GCLabel);
	prop = dynamic_cast<HKCPntrProp^>(grabcutr->Prop);
	prop->PropertyChanged += gcnew PropEventHandler(this, &Form1::GCProp_PropertyValueChanged);
	prop->Size = 10;	
	mp_AppToolMgr->Add(grabcutr);

	/// Add media player
	/*AppGlobal::g_MPlyrLabel = "Media Player";
	HKCAppTool^ mplayer = gcnew HKCMPlayer(AppGlobal::g_MPlyrLabel);
	mplayer->Activate(nullptr);
	mp_AppToolMgr->Add(mplayer);*/

	/// Add transformation tool
	AppGlobal::g_XFormLabel = "XForm Tool";
	HKCAppTool^ xformer = gcnew HKCXFormer(AppGlobal::g_XFormLabel);
	HKCXFormProp^ xformProp = dynamic_cast<HKCXFormProp^>(xformer->Prop);	
	xformProp->MoveRes = gcnew cli::array<double>(2) {1.0, 1.0};	
	xformProp->ScaleRes = gcnew cli::array<double>(2) {0.01, 0.01};	
	xformProp->RotateRes = 1.0;
	mp_AppToolMgr->Add(xformer);

	/// Set tool property grid	
	//ToolGrid->SelectedObject = gcnew cli::array< HKCToolProp^ >(3) {painter->Prop, grabcutr->Prop, mplayer->Prop};	
	//ToolGrid->SelectedObject = gcnew cli::array< HKCToolProp^ >(2) {painter->Prop, grabcutr->Prop};	
	ToolGrid->SelectedObject = gcnew cli::array< HKCToolProp^ >(3) {painter->Prop, grabcutr->Prop, xformer->Prop};	

	/////////////////////////////////////////////////
	/// Temporary codes
	/////////////////////////////////////////////////
	//this->PDBFileCombo->SelectedIndex = 0;
	//mp_AppIOMgr->Read("C:\\Working Projects\\Halftone QR codes\\Data\\Examples\\Candidates\\Barack Obama\\V5_3X3\\obama2.qrca", this, mp_GLPanel);

	/////////////////////////////////////////////////
	/// Read Text Font
	/////////////////////////////////////////////////
	QRWordArt::QRCharacter::IO::Load("skeleton");
	QRWordArt::QRCharacter::QRSkeleton::LoadStrokeTexture();
	QRWordArt::QRPattern::LoadPattern();
}

/// Release data of the form
void Form1::Release(void)
{	
	mp_GLPanels->Clear();
	delete mp_GLPanels;
	mp_GLPanels = nullptr;	

	delete mp_AppItem;
	mp_AppItem = nullptr;

	delete mp_AppRendr;
	mp_AppRendr = nullptr;

	delete mp_AppIOMgr;
	mp_AppIOMgr = nullptr;

	delete mp_AppLayerMgr;
	mp_AppLayerMgr = nullptr;	

	delete mp_AppToolMgr;
	mp_AppToolMgr = nullptr;

	/// release OpenCV resources
	cv::destroyAllWindows();		
}

/// Refresh all property grids
void Form1::PropertyGrid_Refresh(void)
{
	this->PropGrid->Refresh();
	this->ParamGrid->Refresh();
}