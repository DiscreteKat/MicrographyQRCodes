/**
* @file Form1.h
*
* Class for windows form application
*
* @author James Hung-Kuo Chu
*/

#pragma once
#include <iostream>
#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"
#include "AppAlgoQRC.h"

#include "AppAlgoQRCodeEvaluation.h"
#include "AppAlgoEnergyVisual.h"
#include "AppAlgoEnergyTextSpace.h"
#include "AppAlgoZBar.h"
#include "AppAlgoTextGeneration.h"
#include "AppAlgoTextTyping.h"
#include "AppAlgoTextAlign.h"
#include "AppAlgoQRCodeSegmentation.h"
#include "AppAlgoTextColor.h"
#include "AppTool.h"
#include "AppPainter.h"
#include "AppGrabCut.h"
#include "AppMediaPlayer.h"
#include "AppXForm.h"
#include "AppToolManager.h"
#include "AppIOManager.h"
#include "AppLayerManager.h"
#include "AppRender.h"
#include "AppUtils.h"
#include "AppState.h"
#include "AppConfigFile.h"

#include "YJPSNRSSIM.h"

#include "QRWordArt/QRCharFBO.h"
#include "QRWordArt/QRStringLine.h"
#include "QRWordArt/QRSplineFBO.h"
#include "QRWordArt/QRCharacterIO.h"
#include <cstdlib>
#include <time.h>
namespace AppFrame {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;	
	using namespace System::IO;
	using namespace System::Threading;
	using namespace System::Collections::Generic;
	using namespace DevComponents::DotNetBar;
	using namespace DevComponents::DotNetBar::Rendering;
	using namespace DevComponents::AdvTree;
	using namespace HKOGLPanel;
	/// <summary>
	/// Summary for Form1dotnetbar
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public DevComponents::DotNetBar::Office2007RibbonForm		
	{
	public: 













	private: DevComponents::DotNetBar::ItemContainer^  itemContainer25;






	private: DevComponents::DotNetBar::CheckBoxItem^  WarpCheckBox;
	private: DevComponents::DotNetBar::RibbonBar^  RegPRibnBar;
	private: DevComponents::DotNetBar::ItemContainer^  itemContainer26;
	private: DevComponents::DotNetBar::CheckBoxItem^  smallregioncheckbox;
	private: DevComponents::DotNetBar::LabelItem^  BoundaryAlabel;
	private: DevComponents::DotNetBar::TextBoxItem^  BoundaryA;


	private: DevComponents::DotNetBar::LabelItem^  BoundaryBlabel;
	private: DevComponents::DotNetBar::TextBoxItem^  BoundaryB;


	private: DevComponents::DotNetBar::ItemContainer^  itemContainer27;
	private: DevComponents::DotNetBar::LabelItem^  RangeSizelabel;
	private: DevComponents::DotNetBar::TextBoxItem^  Rangesize;


	private: DevComponents::DotNetBar::LabelItem^  LineAlabel;
	private: DevComponents::DotNetBar::TextBoxItem^  LineA;


	private: DevComponents::DotNetBar::LabelItem^  LineBlabel;
	private: DevComponents::DotNetBar::TextBoxItem^  LineB;
	private: DevComponents::DotNetBar::ButtonItem^  TextOrderBtn;
	private: DevComponents::DotNetBar::ButtonItem^  TextOrienBtn;




	private: DevComponents::DotNetBar::ItemContainer^  itemContainer28;
	private: DevComponents::DotNetBar::ItemContainer^  itemContainer29;








	private: DevComponents::DotNetBar::ButtonItem^  TextBaseBtn;





	private: DevComponents::DotNetBar::ButtonItem^  OpnArticleBtn;






	private: DevComponents::DotNetBar::RibbonBar^  ribbonBar6;
	private: DevComponents::DotNetBar::ItemContainer^  itemContainer33;
	private: DevComponents::DotNetBar::ColorPickerDropDown^  TextcolorPick;
	private: DevComponents::DotNetBar::ComboBoxItem^  LevelBox;
	private: DevComponents::Editors::ComboItem^  comboItem9;
	private: DevComponents::Editors::ComboItem^  comboItem10;
	private: DevComponents::Editors::ComboItem^  comboItem11;
	private: DevComponents::DotNetBar::RibbonBar^  ribbonBar5;
	private: DevComponents::DotNetBar::ItemContainer^  itemContainer32;
	private: DevComponents::DotNetBar::CheckBoxItem^  SoftAdjust;

	private: DevComponents::DotNetBar::ButtonItem^  StringLineEdittingToolBtn;
	private: DevComponents::DotNetBar::RibbonBar^  ribbonBar4;
	private: DevComponents::DotNetBar::ItemContainer^  itemContainer31;
	private: DevComponents::DotNetBar::CheckBoxItem^  SeeLevelCheck1;
	private: DevComponents::DotNetBar::CheckBoxItem^  SeeLevelCheck2;
	private: DevComponents::DotNetBar::CheckBoxItem^  SeeLevelCheck3;



	private: DevComponents::DotNetBar::SliderItem^  ScaleSlider;
	private: DevComponents::DotNetBar::RibbonBar^  ribbonBar3;
	private: System::Windows::Forms::Label^  label1;
	private: DevComponents::DotNetBar::Controls::ProgressBarX^  VisualQualitybar;
	private: System::Windows::Forms::Label^  label2;
	private: DevComponents::DotNetBar::Controls::ProgressBarX^  QRenergyBar;
	private: DevComponents::DotNetBar::ItemContainer^  itemContainer30;
	private: DevComponents::DotNetBar::ControlContainerItem^  controlContainerItem1;
	private: DevComponents::DotNetBar::ControlContainerItem^  controlContainerItem2;
	private: DevComponents::DotNetBar::ControlContainerItem^  controlContainerItem3;
	private: DevComponents::DotNetBar::ControlContainerItem^  controlContainerItem4;
	private: DevComponents::DotNetBar::RibbonBar^  ribbonBar2;
	private: DevComponents::DotNetBar::LabelItem^  QRcodeLabel;
	private: DevComponents::DotNetBar::RibbonBar^  ScalingToolsRibnBar;
	private: DevComponents::DotNetBar::ButtonItem^  ScalingToolBtn;
	private: DevComponents::DotNetBar::ButtonItem^  ScalingToolUndoBtn;
private: DevComponents::DotNetBar::RibbonBar^  TestRibnBar;
private: DevComponents::DotNetBar::ButtonItem^  AppTestBtn;
private: DevComponents::DotNetBar::ItemContainer^  itemContainer19;
private: DevComponents::DotNetBar::ButtonItem^  AppDebugBtn;
private: DevComponents::DotNetBar::ButtonItem^  AppDumpBtn;
private: DevComponents::DotNetBar::RibbonBar^  QRRecRibnBar;
private: DevComponents::DotNetBar::ItemContainer^  itemContainer22;
private: DevComponents::DotNetBar::LabelItem^  QRReclabel;
private: DevComponents::DotNetBar::TextBoxItem^  QRRecTextBox;
private: DevComponents::DotNetBar::ButtonItem^  QRRecBtn;
private: DevComponents::DotNetBar::ButtonItem^  ErrorCorrectionBtn;
private: DevComponents::DotNetBar::ItemContainer^  itemContainer36;
private: DevComponents::DotNetBar::CheckBoxItem^  RSModCheckBox;
private: DevComponents::DotNetBar::CheckBoxItem^  CurveWarpCheckBox;
private: DevComponents::DotNetBar::CheckBoxItem^  CharWarpCheckBox;
private: DevComponents::DotNetBar::CheckBoxItem^  IslandModuleCheckBox;

private: DevComponents::DotNetBar::ItemContainer^  itemContainer34;
private: DevComponents::DotNetBar::SliderItem^  sliderItem1;
private: DevComponents::DotNetBar::SliderItem^  sliderItem2;
private: DevComponents::DotNetBar::CheckBoxItem^  checkBoxItem1;
private: DevComponents::DotNetBar::ButtonItem^  OpnGapBtn;











	public: 










			 
		Form1(void)
		{
			InitializeComponent();
//			srand(100);
			/// Initialize GUI
			Init_GUI();		
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}

			/// release data
			Release();
		}
	private: System::Windows::Forms::OpenFileDialog^  OpenFileDialog;
	protected: 
	private: System::Windows::Forms::SaveFileDialog^  SaveFileDialog;
	private: System::Windows::Forms::Timer^  PlayerTimer;

	private: DevComponents::DotNetBar::DotNetBarManager^  DotNetBarManager;
	private: DevComponents::DotNetBar::DockSite^  dockSite4;
	private: DevComponents::DotNetBar::DockSite^  dockSite1;
	private: DevComponents::DotNetBar::DockSite^  dockSite2;
	private: DevComponents::DotNetBar::DockSite^  dockSite3;
	private: DevComponents::DotNetBar::DockSite^  dockSite5;
	private: DevComponents::DotNetBar::DockSite^  dockSite6;
	private: DevComponents::DotNetBar::DockSite^  dockSite7;
	private: DevComponents::DotNetBar::DockSite^  dockSite8;	
	private: DevComponents::DotNetBar::RibbonControl^  RibbonControl;
	private: DevComponents::DotNetBar::RibbonPanel^  RibbonToolPanel;






	private: DevComponents::DotNetBar::RibbonTabItem^  RibbonToolTab;





	private: DevComponents::DotNetBar::Office2007StartButton^  office2007StartButton1;
	private: DevComponents::DotNetBar::ItemContainer^  itemContainer1;
	private: DevComponents::DotNetBar::ItemContainer^  itemContainer2;
	private: DevComponents::DotNetBar::ItemContainer^  itemContainer3;
	private: DevComponents::DotNetBar::ButtonItem^  AppOpnBtn;
	private: DevComponents::DotNetBar::ButtonItem^  AppSavBtn;
	private: DevComponents::DotNetBar::ItemContainer^  itemContainer4;
	private: DevComponents::DotNetBar::ButtonItem^  buttonItem13;
	private: DevComponents::DotNetBar::ButtonItem^  buttonItem14;
	private: DevComponents::DotNetBar::ButtonItem^  QickOpnBtn;
	private: DevComponents::DotNetBar::QatCustomizeItem^  qatCustomizeItem1;
	private: DevComponents::DotNetBar::ButtonItem^  QickSavBtn;
	private: DevComponents::DotNetBar::Command^  AppOpnCmd;



	private: DevComponents::DotNetBar::Command^  FormThemeCmd;

	private: DevComponents::DotNetBar::DockSite^  dockSite9;
	private: DevComponents::DotNetBar::PanelDockContainer^  DockCntrPanel1;



	private: DevComponents::DotNetBar::DockContainerItem^  DockCntrItem1;	



	private: DevComponents::DotNetBar::Bar^  bar3;
	private: DevComponents::DotNetBar::PanelDockContainer^  ParamDockCntrPanel;
	private: DevComponents::DotNetBar::DockContainerItem^  ParamDockCntrItem;
	private: DevComponents::DotNetBar::PanelDockContainer^  PropDockCntrPanel;
	private: DevComponents::DotNetBar::DockContainerItem^  PropDockCntrItem;
	private: System::Windows::Forms::PropertyGrid^  ParamGrid;

	private: System::Windows::Forms::PropertyGrid^  PropGrid;

	private: DevComponents::DotNetBar::RibbonBar^  MPlayerRibnBar;




	private: DevComponents::DotNetBar::ItemContainer^  PlayerItemCntr;
	private: DevComponents::DotNetBar::ItemContainer^  PlayerBtnCntr;
	private: DevComponents::DotNetBar::ButtonItem^  PlayerStartBtn;
	private: DevComponents::DotNetBar::ButtonItem^  PlayerRewindBtn;
	private: DevComponents::DotNetBar::ButtonItem^  PlayerPlayBtn;
	private: DevComponents::DotNetBar::ButtonItem^  PlayerForwardBtn;
	private: DevComponents::DotNetBar::ButtonItem^  PlayerEndBtn;

	private: DevComponents::DotNetBar::SliderItem^  PlayerFrameSlider;
	private: DevComponents::DotNetBar::Command^  AppDesignCmd;
	private: DevComponents::DotNetBar::RibbonBar^  DsgnRibnBar;


	private: DevComponents::DotNetBar::ButtonItem^  AppCenterBtn;


	private: DevComponents::DotNetBar::Command^  AppPlayerCmd;
	private: DevComponents::DotNetBar::ItemContainer^  itemContainer5;


	private: DevComponents::Editors::ComboItem^  comboItem1;
	private: DevComponents::DotNetBar::SliderItem^  PlayerSpeedSlider;
	private: DevComponents::DotNetBar::ItemContainer^  DesignVertCntr;
	private: DevComponents::DotNetBar::ItemContainer^  DesignHorzCntr1;
	private: DevComponents::DotNetBar::ItemContainer^  DesignHorzCntr2;
	private: DevComponents::DotNetBar::ButtonItem^  AppSyncBtn;
	private: DevComponents::DotNetBar::Bar^  bar2;
	private: HKOGLPanel::HKOGLPanelControl^  HKOGLPanel1;

	private: DevComponents::DotNetBar::RibbonBar^  PaintRibnBar;


	private: DevComponents::DotNetBar::ItemContainer^  itemContainer6;
	private: DevComponents::DotNetBar::ItemContainer^  itemContainer7;
	private: DevComponents::DotNetBar::ButtonItem^  AppPaintBtn;
	private: DevComponents::DotNetBar::ButtonItem^  PlayerReptBtn;
	private: DevComponents::DotNetBar::ButtonItem^  PlayerSyncBtn;
	private: DevComponents::DotNetBar::Command^  AppPaintCmd;
	private: DevComponents::DotNetBar::ButtonItem^  PntrBrshBtn;

	private: DevComponents::DotNetBar::ItemContainer^  itemContainer8;
	private: DevComponents::DotNetBar::ButtonItem^  PntrErasBtn;
	private: DevComponents::DotNetBar::ButtonItem^  PntrCleanBtn;








	private: DevComponents::DotNetBar::PanelDockContainer^  LayrDockCntrPanel;

	private: DevComponents::DotNetBar::DockContainerItem^  LayrDockCntrItem;
	private: DevComponents::AdvTree::AdvTree^  LayerTree;
	private: DevComponents::AdvTree::AdvTree^  CandidateLayer;
	private: DevComponents::AdvTree::AdvTree^  WordArtLayer;
	private: DevComponents::AdvTree::NodeConnector^  nodeConnector1;
	private: DevComponents::DotNetBar::ElementStyle^  elementStyle1;




	private: DevComponents::DotNetBar::ContextMenuBar^  AppCntxMenuBar;
	private: DevComponents::DotNetBar::ButtonItem^  PntrCntxMenu;
	private: DevComponents::DotNetBar::SliderItem^  PntrMStrkSize;
	private: DevComponents::DotNetBar::RibbonBar^  GrabCutRibnBar;

	private: DevComponents::DotNetBar::Command^  AppGrabCutCmd;

	private: DevComponents::DotNetBar::ItemContainer^  itemContainer9;
	private: DevComponents::DotNetBar::ItemContainer^  itemContainer10;
	private: DevComponents::DotNetBar::ButtonItem^  AppGCBtn;

	private: DevComponents::DotNetBar::ItemContainer^  itemContainer11;
	private: DevComponents::DotNetBar::ButtonItem^  GCCntxMenu;
	private: DevComponents::DotNetBar::ButtonItem^  GCCutBtn;
	private: DevComponents::DotNetBar::ButtonItem^  GCResetBtn;









	private: DevComponents::DotNetBar::ButtonItem^  GCMFGDBtn;
	private: DevComponents::DotNetBar::ButtonItem^  GCMBGDBtn;
	private: DevComponents::DotNetBar::ButtonItem^  GCMPRFGDBtn;
	private: DevComponents::DotNetBar::ButtonItem^  GCMPRBGDBtn;










	private: DevComponents::DotNetBar::ButtonItem^  GCMCutBtn;
	private: DevComponents::DotNetBar::ButtonItem^  GCMResetBtn;


	private: DevComponents::DotNetBar::ButtonItem^  GCAddBtn;
	private: DevComponents::DotNetBar::ButtonItem^  GCMAddBtn;
	private: DevComponents::DotNetBar::ButtonItem^  PntrMBrshBtn;
	private: DevComponents::DotNetBar::ButtonItem^  PntrMErasBtn;
	private: DevComponents::DotNetBar::ButtonItem^  PntrMCleanBtn;
	private: DevComponents::DotNetBar::SliderItem^  GCMStrkSize;

	private: DevComponents::DotNetBar::ButtonItem^  GCMErasBtn;


	private: DevComponents::DotNetBar::ButtonItem^  GCMMskBBtn;
	private: DevComponents::DotNetBar::ButtonItem^  GCMMskWBtn;
	private: DevComponents::DotNetBar::ButtonItem^  LayerCntxMenu;
	private: DevComponents::DotNetBar::ButtonItem^  LayrMDelBtn;

	private: DevComponents::DotNetBar::Command^  AppLayerCmd;
	private: DevComponents::DotNetBar::ButtonItem^  LayrMShowBtn;
	private: DevComponents::DotNetBar::ButtonItem^  SavConfigBtn;
	private: DevComponents::DotNetBar::Command^  AppSavCmd;
	private: DevComponents::DotNetBar::ButtonItem^  OpnMedaBtn;
	private: DevComponents::DotNetBar::ButtonItem^  OpnConfigBtn;
	private: DevComponents::DotNetBar::ButtonItem^  OpnSegFlowBtn;
	private: DevComponents::DotNetBar::ButtonItem^  OpnLineDataBtn;
	private: DevComponents::DotNetBar::ButtonItem^  GCErasBtn;
	private: DevComponents::DotNetBar::ButtonItem^  GCBrshBtn;
	private: DevComponents::DotNetBar::ButtonItem^  GCFGDBtn;
private: DevComponents::DotNetBar::ButtonItem^  GCBGDBtn;

	private: DevComponents::DotNetBar::ButtonItem^  GCPRFGDBtn;
	private: DevComponents::DotNetBar::ButtonItem^  GCPRBGDBtn;
	private: DevComponents::DotNetBar::ButtonItem^  GCMskBBtn;
	private: DevComponents::DotNetBar::ButtonItem^  GCMskWBtn;
	private: DevComponents::DotNetBar::ColorPickerDropDown^  PntrBrushColor;
private: DevComponents::DotNetBar::StyleManager^  StyleManager;
private: DevComponents::DotNetBar::RibbonPanel^  RibbonAppPanel;

private: DevComponents::DotNetBar::RibbonTabItem^  RibbonAppTab;


private: DevComponents::Editors::ComboItem^  comboItem2;
private: DevComponents::DotNetBar::RibbonBar^  RibbonThemeBar;
private: DevComponents::DotNetBar::ButtonItem^  FormThemeBtn;
private: DevComponents::DotNetBar::ButtonItem^  FormThemePicker;
private: DevComponents::DotNetBar::ButtonItem^  FormTheme1Btn;
private: DevComponents::DotNetBar::ButtonItem^  FormTheme2Btn;
private: DevComponents::DotNetBar::ButtonItem^  FormTheme3Btn;
private: DevComponents::DotNetBar::ButtonItem^  FormTheme4Btn;
private: DevComponents::DotNetBar::ButtonItem^  FormTheme5Btn;
private: DevComponents::DotNetBar::ButtonItem^  FormTheme6Btn;
private: DevComponents::DotNetBar::ButtonItem^  FormTheme7Btn;
private: DevComponents::DotNetBar::ButtonItem^  FormTheme10Btn;
private: DevComponents::DotNetBar::ButtonItem^  FormTheme9Btn;
private: DevComponents::DotNetBar::ButtonItem^  FormTheme8Btn;

private: DevComponents::DotNetBar::ColorPickerDropDown^  FormColorPicker;






private: DevComponents::DotNetBar::PanelDockContainer^  ToolDockCntrPanel;
private: System::Windows::Forms::PropertyGrid^  ToolGrid;
private: DevComponents::DotNetBar::DockContainerItem^  ToolDockCntrItem;

private: DevComponents::DotNetBar::Command^  AppTestCmd;


private: DevComponents::DotNetBar::RibbonBar^  XFormRibnBar;
private: DevComponents::DotNetBar::ItemContainer^  itemContainer12;
private: DevComponents::DotNetBar::ItemContainer^  itemContainer13;
private: DevComponents::DotNetBar::ButtonItem^  XFormCropBtn;

private: DevComponents::DotNetBar::ButtonItem^  XFormMirBtn;
private: DevComponents::DotNetBar::ItemContainer^  itemContainer14;
private: DevComponents::DotNetBar::ButtonItem^  XFormMovBtn;
private: DevComponents::DotNetBar::ButtonItem^  XFormRotBtn;
private: DevComponents::DotNetBar::ButtonItem^  XFormScalBtn;
private: DevComponents::DotNetBar::Command^  AppXFormCmd;
private: DevComponents::DotNetBar::RibbonBar^  QRRibnBar;
private: DevComponents::DotNetBar::ItemContainer^  itemContainer15;
private: DevComponents::DotNetBar::ButtonItem^  QRCGenBtn;




private: DevComponents::DotNetBar::ItemContainer^  itemContainer16;
private: DevComponents::DotNetBar::ItemContainer^  itemContainer17;
private: DevComponents::DotNetBar::ComboBoxItem^  QRCVerCombo;





private: DevComponents::DotNetBar::TextBoxItem^  QRCText;



private: DevComponents::Editors::ComboItem^  QRCVer5;
private: DevComponents::Editors::ComboItem^  QRCVer10;


private: DevComponents::DotNetBar::Command^  AppQRCCmd;
private: DevComponents::DotNetBar::ButtonItem^  AppPinBtn;
private: DevComponents::DotNetBar::ButtonItem^  XFormUndoBtn;
private: DevComponents::DotNetBar::RibbonBar^  ProcessRibnBar;
 private: DevComponents::DotNetBar::RibbonBar^  ErrorCorrectionRibnBar;
 private: DevComponents::DotNetBar::RibbonBar^  StringLineToolsRibnBar;
private: DevComponents::DotNetBar::ButtonItem^  ProcessAllBtn;

private: DevComponents::DotNetBar::Command^  AppErrorCorrectCmd;
private: DevComponents::DotNetBar::Command^  AppProcessCmd;
private: DevComponents::DotNetBar::Command^  AppBuildBigScaleCmd;
private: DevComponents::Editors::ComboItem^  QRCVer6;
private: DevComponents::Editors::ComboItem^  QRCVer7;
private: DevComponents::Editors::ComboItem^  QRCVer8;
private: DevComponents::Editors::ComboItem^  QRCVer9;
private: DevComponents::Editors::ComboItem^  QRCVer3;
private: DevComponents::Editors::ComboItem^  QRCVer4;
private: DevComponents::DotNetBar::ComboBoxItem^  QRCECLCombo;
private: DevComponents::Editors::ComboItem^  QRCECLL;
private: DevComponents::Editors::ComboItem^  QRCECLM;
private: DevComponents::Editors::ComboItem^  QRCECLQ;
private: DevComponents::Editors::ComboItem^  QRCECLH;
private: DevComponents::DotNetBar::RibbonBar^  PDBRibnBar;

private: DevComponents::Editors::ComboItem^  QRCPSize3;
private: DevComponents::DotNetBar::ComboBoxItem^  PDBFileCombo;

private: DevComponents::Editors::ComboItem^  comboItem3;
private: DevComponents::Editors::ComboItem^  comboItem5;
private: DevComponents::Editors::ComboItem^  comboItem6;
private: DevComponents::Editors::ComboItem^  comboItem7;
private: DevComponents::Editors::ComboItem^  comboItem8;
private: DevComponents::DotNetBar::ItemContainer^  itemContainer18;
private: DevComponents::DotNetBar::LabelItem^  PDBSizeLabel;
private: DevComponents::DotNetBar::Command^  AppPDBCmd;



private: DevComponents::DotNetBar::RibbonBar^  FilterRibnBar;

private: DevComponents::DotNetBar::ItemContainer^  itemContainer20;
private: DevComponents::DotNetBar::ButtonItem^  FltrContrastBtn;
private: DevComponents::DotNetBar::SliderItem^  FltrContrastSlider;
private: DevComponents::DotNetBar::ItemContainer^  itemContainer21;
private: DevComponents::DotNetBar::ButtonItem^  FltrSharpenBtn;
private: DevComponents::DotNetBar::SliderItem^  FltrUSMASlider;

private: DevComponents::DotNetBar::SliderItem^  FltrUSMRSlider;

private: DevComponents::DotNetBar::SliderItem^  FltrUSMTSlider;
private: DevComponents::DotNetBar::Command^  AppFilterCmd;
private: DevComponents::DotNetBar::ButtonItem^  FltrFlowAbsBtn;



private: DevComponents::Editors::ComboItem^  comboItem4;
private: DevComponents::Editors::ComboItem^  QRCVer1;
private: DevComponents::Editors::ComboItem^  QRCVer2;
private: DevComponents::Editors::ComboItem^  QRCVer11;
private: DevComponents::Editors::ComboItem^  QRCVer12;
private: DevComponents::Editors::ComboItem^  QRCVer13;
private: DevComponents::Editors::ComboItem^  QRCVer14;
private: DevComponents::Editors::ComboItem^  QRCVer15;
private: DevComponents::Editors::ComboItem^  QRCVer16;
private: DevComponents::Editors::ComboItem^  QRCVer17;
private: DevComponents::Editors::ComboItem^  QRCVer18;
private: DevComponents::Editors::ComboItem^  QRCVer19;
private: DevComponents::Editors::ComboItem^  QRCVer20;
private: DevComponents::DotNetBar::RibbonPanel^  ribbonPanel1;
private: DevComponents::DotNetBar::RibbonPanel^  ErrorCorrectionPanel;
private: DevComponents::DotNetBar::RibbonPanel^  EditingToolsPanel;
private: DevComponents::DotNetBar::RibbonBar^  ribbonBar1;
private: DevComponents::DotNetBar::ButtonItem^  CameraImgGDBtn;
private: DevComponents::DotNetBar::RibbonTabItem^  Debug;
private: DevComponents::DotNetBar::RibbonBar^  WordArtRibnBar;




private: DevComponents::DotNetBar::ItemContainer^  itemContainer23;
private: DevComponents::DotNetBar::LabelItem^  StringData;
private: DevComponents::DotNetBar::ButtonItem^  OpnSegBtn;
private: DevComponents::DotNetBar::ItemContainer^  itemContainer24;
private: DevComponents::DotNetBar::LabelItem^  WordArtStringLabel2;
private: DevComponents::DotNetBar::TextBoxItem^  WordArtText2;

private: DevComponents::DotNetBar::PanelDockContainer^  CandidateDockCntrPanel;
private: DevComponents::DotNetBar::PanelDockContainer^ WordArtLayerCntrPanel;
private: DevComponents::DotNetBar::DockContainerItem^  CandidateItem;




private: DevComponents::DotNetBar::DockContainerItem^  WordArtItem;
private: DevComponents::DotNetBar::RibbonTabItem^  ErrorCorrection;
private: DevComponents::DotNetBar::ButtonItem^  ScalingBtn;
private: DevComponents::DotNetBar::RibbonTabItem^  EditingTools;


private: DevComponents::DotNetBar::Command^  AppScalingToolUndoCmd;











	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			HKOGLPanel::HKCCameraProp^  hkcCameraProp1 = (gcnew HKOGLPanel::HKCCameraProp());
			HKOGLPanel::HKCDisplayProp^  hkcDisplayProp1 = (gcnew HKOGLPanel::HKCDisplayProp());
			HKOGLPanel::HKCPixelFormat^  hkcPixelFormat1 = (gcnew HKOGLPanel::HKCPixelFormat());
			HKOGLPanel::HKCTrackballProp^  hkcTrackballProp1 = (gcnew HKOGLPanel::HKCTrackballProp());
			HKOGLPanel::HKCTrackballTrig^  hkcTrackballTrig1 = (gcnew HKOGLPanel::HKCTrackballTrig());
			HKOGLPanel::HKCTrackballTrig^  hkcTrackballTrig2 = (gcnew HKOGLPanel::HKCTrackballTrig());
			HKOGLPanel::HKCTrackballTrig^  hkcTrackballTrig3 = (gcnew HKOGLPanel::HKCTrackballTrig());
			this->OpenFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->SaveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->PlayerTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->DotNetBarManager = (gcnew DevComponents::DotNetBar::DotNetBarManager(this->components));
			this->dockSite4 = (gcnew DevComponents::DotNetBar::DockSite());
			this->dockSite9 = (gcnew DevComponents::DotNetBar::DockSite());
			this->bar2 = (gcnew DevComponents::DotNetBar::Bar());
			this->DockCntrPanel1 = (gcnew DevComponents::DotNetBar::PanelDockContainer());
			this->AppCntxMenuBar = (gcnew DevComponents::DotNetBar::ContextMenuBar());
			this->PntrCntxMenu = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->PntrMStrkSize = (gcnew DevComponents::DotNetBar::SliderItem());
			this->PntrMBrshBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppPaintCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->PntrMErasBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->PntrMCleanBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCCntxMenu = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCMStrkSize = (gcnew DevComponents::DotNetBar::SliderItem());
			this->GCMFGDBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppGrabCutCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->GCMBGDBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCMPRFGDBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCMPRBGDBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCMMskBBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCMMskWBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCMErasBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCMCutBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCMResetBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCMAddBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->LayerCntxMenu = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->LayrMDelBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppLayerCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->LayrMShowBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->LayerTree = (gcnew DevComponents::AdvTree::AdvTree());
			this->nodeConnector1 = (gcnew DevComponents::AdvTree::NodeConnector());
			this->elementStyle1 = (gcnew DevComponents::DotNetBar::ElementStyle());
			this->CandidateLayer = (gcnew DevComponents::AdvTree::AdvTree());
			this->WordArtLayer = (gcnew DevComponents::AdvTree::AdvTree());
			this->HKOGLPanel1 = (gcnew HKOGLPanel::HKOGLPanelControl());
			this->DockCntrItem1 = (gcnew DevComponents::DotNetBar::DockContainerItem());
			this->dockSite1 = (gcnew DevComponents::DotNetBar::DockSite());
			this->dockSite2 = (gcnew DevComponents::DotNetBar::DockSite());
			this->bar3 = (gcnew DevComponents::DotNetBar::Bar());
			this->LayrDockCntrPanel = (gcnew DevComponents::DotNetBar::PanelDockContainer());
			this->WordArtLayerCntrPanel = (gcnew DevComponents::DotNetBar::PanelDockContainer());
			this->PropDockCntrPanel = (gcnew DevComponents::DotNetBar::PanelDockContainer());
			this->PropGrid = (gcnew System::Windows::Forms::PropertyGrid());
			this->ParamDockCntrPanel = (gcnew DevComponents::DotNetBar::PanelDockContainer());
			this->ParamGrid = (gcnew System::Windows::Forms::PropertyGrid());
			this->ToolDockCntrPanel = (gcnew DevComponents::DotNetBar::PanelDockContainer());
			this->ToolGrid = (gcnew System::Windows::Forms::PropertyGrid());
			this->CandidateDockCntrPanel = (gcnew DevComponents::DotNetBar::PanelDockContainer());
			this->LayrDockCntrItem = (gcnew DevComponents::DotNetBar::DockContainerItem());
			this->WordArtItem = (gcnew DevComponents::DotNetBar::DockContainerItem());
			this->PropDockCntrItem = (gcnew DevComponents::DotNetBar::DockContainerItem());
			this->ParamDockCntrItem = (gcnew DevComponents::DotNetBar::DockContainerItem());
			this->ToolDockCntrItem = (gcnew DevComponents::DotNetBar::DockContainerItem());
			this->CandidateItem = (gcnew DevComponents::DotNetBar::DockContainerItem());
			this->dockSite8 = (gcnew DevComponents::DotNetBar::DockSite());
			this->dockSite5 = (gcnew DevComponents::DotNetBar::DockSite());
			this->dockSite6 = (gcnew DevComponents::DotNetBar::DockSite());
			this->dockSite7 = (gcnew DevComponents::DotNetBar::DockSite());
			this->dockSite3 = (gcnew DevComponents::DotNetBar::DockSite());
			this->RibbonControl = (gcnew DevComponents::DotNetBar::RibbonControl());
			this->EditingToolsPanel = (gcnew DevComponents::DotNetBar::RibbonPanel());
			this->ribbonBar3 = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->VisualQualitybar = (gcnew DevComponents::DotNetBar::Controls::ProgressBarX());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->QRenergyBar = (gcnew DevComponents::DotNetBar::Controls::ProgressBarX());
			this->itemContainer30 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->controlContainerItem1 = (gcnew DevComponents::DotNetBar::ControlContainerItem());
			this->controlContainerItem2 = (gcnew DevComponents::DotNetBar::ControlContainerItem());
			this->controlContainerItem3 = (gcnew DevComponents::DotNetBar::ControlContainerItem());
			this->controlContainerItem4 = (gcnew DevComponents::DotNetBar::ControlContainerItem());
			this->ribbonBar2 = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->QRcodeLabel = (gcnew DevComponents::DotNetBar::LabelItem());
			this->ScalingToolsRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->ScalingToolBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ScalingToolUndoBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppScalingToolUndoCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->ribbonBar5 = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->itemContainer32 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->SoftAdjust = (gcnew DevComponents::DotNetBar::CheckBoxItem());
			this->ScaleSlider = (gcnew DevComponents::DotNetBar::SliderItem());
			this->ribbonBar6 = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->itemContainer33 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->TextcolorPick = (gcnew DevComponents::DotNetBar::ColorPickerDropDown());
			this->LevelBox = (gcnew DevComponents::DotNetBar::ComboBoxItem());
			this->comboItem9 = (gcnew DevComponents::Editors::ComboItem());
			this->comboItem10 = (gcnew DevComponents::Editors::ComboItem());
			this->comboItem11 = (gcnew DevComponents::Editors::ComboItem());
			this->itemContainer34 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->checkBoxItem1 = (gcnew DevComponents::DotNetBar::CheckBoxItem());
			this->sliderItem1 = (gcnew DevComponents::DotNetBar::SliderItem());
			this->sliderItem2 = (gcnew DevComponents::DotNetBar::SliderItem());
			this->StringLineToolsRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->itemContainer25 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->itemContainer29 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->StringLineEdittingToolBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->TextBaseBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->itemContainer28 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->TextOrderBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->TextOrienBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->RibbonAppPanel = (gcnew DevComponents::DotNetBar::RibbonPanel());
			this->ribbonBar4 = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->itemContainer31 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->SeeLevelCheck1 = (gcnew DevComponents::DotNetBar::CheckBoxItem());
			this->SeeLevelCheck2 = (gcnew DevComponents::DotNetBar::CheckBoxItem());
			this->SeeLevelCheck3 = (gcnew DevComponents::DotNetBar::CheckBoxItem());
			this->RegPRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->itemContainer26 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->smallregioncheckbox = (gcnew DevComponents::DotNetBar::CheckBoxItem());
			this->BoundaryAlabel = (gcnew DevComponents::DotNetBar::LabelItem());
			this->BoundaryA = (gcnew DevComponents::DotNetBar::TextBoxItem());
			this->BoundaryBlabel = (gcnew DevComponents::DotNetBar::LabelItem());
			this->BoundaryB = (gcnew DevComponents::DotNetBar::TextBoxItem());
			this->itemContainer27 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->RangeSizelabel = (gcnew DevComponents::DotNetBar::LabelItem());
			this->Rangesize = (gcnew DevComponents::DotNetBar::TextBoxItem());
			this->LineAlabel = (gcnew DevComponents::DotNetBar::LabelItem());
			this->LineA = (gcnew DevComponents::DotNetBar::TextBoxItem());
			this->LineBlabel = (gcnew DevComponents::DotNetBar::LabelItem());
			this->LineB = (gcnew DevComponents::DotNetBar::TextBoxItem());
			this->ProcessRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->ProcessAllBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppProcessCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->WarpCheckBox = (gcnew DevComponents::DotNetBar::CheckBoxItem());
			this->ScalingBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppBuildBigScaleCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->WordArtRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->itemContainer23 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->StringData = (gcnew DevComponents::DotNetBar::LabelItem());
			this->PDBRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->itemContainer18 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->PDBSizeLabel = (gcnew DevComponents::DotNetBar::LabelItem());
			this->PDBFileCombo = (gcnew DevComponents::DotNetBar::ComboBoxItem());
			this->AppQRCCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->comboItem3 = (gcnew DevComponents::Editors::ComboItem());
			this->comboItem5 = (gcnew DevComponents::Editors::ComboItem());
			this->comboItem6 = (gcnew DevComponents::Editors::ComboItem());
			this->comboItem7 = (gcnew DevComponents::Editors::ComboItem());
			this->comboItem8 = (gcnew DevComponents::Editors::ComboItem());
			this->itemContainer24 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->WordArtStringLabel2 = (gcnew DevComponents::DotNetBar::LabelItem());
			this->WordArtText2 = (gcnew DevComponents::DotNetBar::TextBoxItem());
			this->QRRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->itemContainer15 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->itemContainer16 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->itemContainer17 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->QRCVerCombo = (gcnew DevComponents::DotNetBar::ComboBoxItem());
			this->QRCVer1 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer2 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer3 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer4 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer5 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer6 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer7 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer8 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer9 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer10 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer11 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer12 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer13 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer14 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer15 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer16 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer17 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer18 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer19 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCVer20 = (gcnew DevComponents::Editors::ComboItem());
			this->QRCECLCombo = (gcnew DevComponents::DotNetBar::ComboBoxItem());
			this->QRCECLL = (gcnew DevComponents::Editors::ComboItem());
			this->QRCECLM = (gcnew DevComponents::Editors::ComboItem());
			this->QRCECLQ = (gcnew DevComponents::Editors::ComboItem());
			this->QRCECLH = (gcnew DevComponents::Editors::ComboItem());
			this->QRCGenBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->QRCText = (gcnew DevComponents::DotNetBar::TextBoxItem());
			this->ErrorCorrectionPanel = (gcnew DevComponents::DotNetBar::RibbonPanel());
			this->TestRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->AppTestBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppTestCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->itemContainer19 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->AppDebugBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppDumpBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->QRRecRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->itemContainer22 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->QRReclabel = (gcnew DevComponents::DotNetBar::LabelItem());
			this->QRRecTextBox = (gcnew DevComponents::DotNetBar::TextBoxItem());
			this->QRRecBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ErrorCorrectionRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->ErrorCorrectionBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppErrorCorrectCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->itemContainer36 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->RSModCheckBox = (gcnew DevComponents::DotNetBar::CheckBoxItem());
			this->CurveWarpCheckBox = (gcnew DevComponents::DotNetBar::CheckBoxItem());
			this->CharWarpCheckBox = (gcnew DevComponents::DotNetBar::CheckBoxItem());
			this->IslandModuleCheckBox = (gcnew DevComponents::DotNetBar::CheckBoxItem());
			this->RibbonToolPanel = (gcnew DevComponents::DotNetBar::RibbonPanel());
			this->MPlayerRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->PlayerItemCntr = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->PlayerBtnCntr = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->PlayerStartBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppPlayerCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->PlayerRewindBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->PlayerPlayBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->PlayerForwardBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->PlayerEndBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->PlayerFrameSlider = (gcnew DevComponents::DotNetBar::SliderItem());
			this->PlayerSpeedSlider = (gcnew DevComponents::DotNetBar::SliderItem());
			this->itemContainer5 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->PlayerReptBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->PlayerSyncBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->RibbonThemeBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->FormThemeBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FormThemeCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->FormThemePicker = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FormTheme1Btn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FormTheme2Btn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FormTheme3Btn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FormTheme4Btn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FormTheme5Btn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FormTheme6Btn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FormTheme7Btn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FormTheme10Btn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FormTheme9Btn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FormTheme8Btn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FormColorPicker = (gcnew DevComponents::DotNetBar::ColorPickerDropDown());
			this->DsgnRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->DesignVertCntr = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->DesignHorzCntr1 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->AppCenterBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppDesignCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->AppPinBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->DesignHorzCntr2 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->AppSyncBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->PaintRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->itemContainer6 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->itemContainer7 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->AppPaintBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->PntrBrshBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->PntrBrushColor = (gcnew DevComponents::DotNetBar::ColorPickerDropDown());
			this->itemContainer8 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->PntrCleanBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->PntrErasBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GrabCutRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->itemContainer9 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->itemContainer10 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->AppGCBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCErasBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCBrshBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCFGDBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCBGDBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCPRFGDBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCPRBGDBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCMskBBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCMskWBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->itemContainer11 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->GCCutBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCAddBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->GCResetBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FilterRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->itemContainer20 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->FltrContrastBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppFilterCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->FltrContrastSlider = (gcnew DevComponents::DotNetBar::SliderItem());
			this->itemContainer21 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->FltrSharpenBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->FltrUSMASlider = (gcnew DevComponents::DotNetBar::SliderItem());
			this->FltrUSMRSlider = (gcnew DevComponents::DotNetBar::SliderItem());
			this->FltrUSMTSlider = (gcnew DevComponents::DotNetBar::SliderItem());
			this->FltrFlowAbsBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->XFormRibnBar = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->itemContainer12 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->itemContainer13 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->XFormCropBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppXFormCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->XFormMirBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->XFormUndoBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->itemContainer14 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->XFormMovBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->XFormRotBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->XFormScalBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->ribbonPanel1 = (gcnew DevComponents::DotNetBar::RibbonPanel());
			this->ribbonBar1 = (gcnew DevComponents::DotNetBar::RibbonBar());
			this->CameraImgGDBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->office2007StartButton1 = (gcnew DevComponents::DotNetBar::Office2007StartButton());
			this->itemContainer1 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->itemContainer2 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->itemContainer3 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->AppOpnBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->OpnConfigBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppOpnCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->OpnMedaBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->OpnSegBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->OpnGapBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->OpnSegFlowBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->OpnLineDataBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->OpnArticleBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppSavBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->SavConfigBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->AppSavCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->itemContainer4 = (gcnew DevComponents::DotNetBar::ItemContainer());
			this->buttonItem13 = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->buttonItem14 = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->RibbonAppTab = (gcnew DevComponents::DotNetBar::RibbonTabItem());
			this->EditingTools = (gcnew DevComponents::DotNetBar::RibbonTabItem());
			this->ErrorCorrection = (gcnew DevComponents::DotNetBar::RibbonTabItem());
			this->RibbonToolTab = (gcnew DevComponents::DotNetBar::RibbonTabItem());
			this->Debug = (gcnew DevComponents::DotNetBar::RibbonTabItem());
			this->QickOpnBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->QickSavBtn = (gcnew DevComponents::DotNetBar::ButtonItem());
			this->qatCustomizeItem1 = (gcnew DevComponents::DotNetBar::QatCustomizeItem());
			this->AppPDBCmd = (gcnew DevComponents::DotNetBar::Command(this->components));
			this->QRCPSize3 = (gcnew DevComponents::Editors::ComboItem());
			this->comboItem1 = (gcnew DevComponents::Editors::ComboItem());
			this->StyleManager = (gcnew DevComponents::DotNetBar::StyleManager(this->components));
			this->comboItem2 = (gcnew DevComponents::Editors::ComboItem());
			this->comboItem4 = (gcnew DevComponents::Editors::ComboItem());
			this->dockSite9->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bar2))->BeginInit();
			this->bar2->SuspendLayout();
			this->DockCntrPanel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->AppCntxMenuBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->LayerTree))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->CandidateLayer))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->WordArtLayer))->BeginInit();
			this->dockSite2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bar3))->BeginInit();
			this->bar3->SuspendLayout();
			this->LayrDockCntrPanel->SuspendLayout();
			this->WordArtLayerCntrPanel->SuspendLayout();
			this->PropDockCntrPanel->SuspendLayout();
			this->ParamDockCntrPanel->SuspendLayout();
			this->ToolDockCntrPanel->SuspendLayout();
			this->CandidateDockCntrPanel->SuspendLayout();
			this->RibbonControl->SuspendLayout();
			this->EditingToolsPanel->SuspendLayout();
			this->ribbonBar3->SuspendLayout();
			this->RibbonAppPanel->SuspendLayout();
			this->ErrorCorrectionPanel->SuspendLayout();
			this->RibbonToolPanel->SuspendLayout();
			this->ribbonPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// OpenFileDialog
			// 
			this->OpenFileDialog->FileName = L"OpenFileDialog";
			// 
			// PlayerTimer
			// 
			this->PlayerTimer->Interval = 1000;
			this->PlayerTimer->Tick += gcnew System::EventHandler(this, &Form1::PlayerTimer_Tick);
			// 
			// DotNetBarManager
			// 
			this->DotNetBarManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::F1);
			this->DotNetBarManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::CtrlC);
			this->DotNetBarManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::CtrlA);
			this->DotNetBarManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::CtrlV);
			this->DotNetBarManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::CtrlX);
			this->DotNetBarManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::CtrlZ);
			this->DotNetBarManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::CtrlY);
			this->DotNetBarManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::Del);
			this->DotNetBarManager->AutoDispatchShortcuts->Add(DevComponents::DotNetBar::eShortcut::Ins);
			this->DotNetBarManager->BottomDockSite = this->dockSite4;
			this->DotNetBarManager->EnableFullSizeDock = false;
			this->DotNetBarManager->FillDockSite = this->dockSite9;
			this->DotNetBarManager->LeftDockSite = this->dockSite1;
			this->DotNetBarManager->ParentForm = this;
			this->DotNetBarManager->RightDockSite = this->dockSite2;
			this->DotNetBarManager->Style = DevComponents::DotNetBar::eDotNetBarStyle::Windows7;
			this->DotNetBarManager->ToolbarBottomDockSite = this->dockSite8;
			this->DotNetBarManager->ToolbarLeftDockSite = this->dockSite5;
			this->DotNetBarManager->ToolbarRightDockSite = this->dockSite6;
			this->DotNetBarManager->ToolbarTopDockSite = this->dockSite7;
			this->DotNetBarManager->TopDockSite = this->dockSite3;
			// 
			// dockSite4
			// 
			this->dockSite4->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->dockSite4->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->dockSite4->DocumentDockContainer = (gcnew DevComponents::DotNetBar::DocumentDockContainer());
			this->dockSite4->Location = System::Drawing::Point(5, 568);
			this->dockSite4->Name = L"dockSite4";
			this->dockSite4->Size = System::Drawing::Size(1113, 0);
			this->dockSite4->TabIndex = 3;
			this->dockSite4->TabStop = false;
			// 
			// dockSite9
			// 
			this->dockSite9->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->dockSite9->Controls->Add(this->bar2);
			this->dockSite9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dockSite9->DocumentDockContainer = (gcnew DevComponents::DotNetBar::DocumentDockContainer(gcnew cli::array< DevComponents::DotNetBar::DocumentBaseContainer^  >(1) {(cli::safe_cast<DevComponents::DotNetBar::DocumentBaseContainer^  >((gcnew DevComponents::DotNetBar::DocumentBarContainer(this->bar2, 
				749, 392))))}, DevComponents::DotNetBar::eOrientation::Horizontal));
			this->dockSite9->Location = System::Drawing::Point(5, 176);
			this->dockSite9->Name = L"dockSite9";
			this->dockSite9->Size = System::Drawing::Size(749, 392);
			this->dockSite9->TabIndex = 9;
			this->dockSite9->TabStop = false;
			// 
			// bar2
			// 
			this->bar2->AccessibleDescription = L"DotNetBar Bar (bar2)";
			this->bar2->AccessibleName = L"DotNetBar Bar";
			this->bar2->AccessibleRole = System::Windows::Forms::AccessibleRole::ToolBar;
			this->bar2->AlwaysDisplayDockTab = true;
			this->bar2->CanDockBottom = false;
			this->bar2->CanDockDocument = true;
			this->bar2->CanDockLeft = false;
			this->bar2->CanDockRight = false;
			this->bar2->CanDockTop = false;
			this->bar2->CanUndock = false;
			this->bar2->Controls->Add(this->DockCntrPanel1);
			this->bar2->DockTabAlignment = DevComponents::DotNetBar::eTabStripAlignment::Top;
			this->bar2->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->bar2->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->DockCntrItem1});
			this->bar2->LayoutType = DevComponents::DotNetBar::eLayoutType::DockContainer;
			this->bar2->Location = System::Drawing::Point(0, 0);
			this->bar2->Name = L"bar2";
			this->bar2->SelectedDockTab = 0;
			this->bar2->Size = System::Drawing::Size(749, 392);
			this->bar2->Stretch = true;
			this->bar2->Style = DevComponents::DotNetBar::eDotNetBarStyle::Windows7;
			this->bar2->TabIndex = 1;
			this->bar2->TabStop = false;
			// 
			// DockCntrPanel1
			// 
			this->DockCntrPanel1->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::Windows7;
			this->DockCntrPanel1->Controls->Add(this->AppCntxMenuBar);
			this->DockCntrPanel1->Controls->Add(this->HKOGLPanel1);
			this->DockCntrPanel1->Location = System::Drawing::Point(3, 28);
			this->DockCntrPanel1->Name = L"DockCntrPanel1";
			this->DockCntrPanel1->Size = System::Drawing::Size(743, 361);
			this->DockCntrPanel1->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->DockCntrPanel1->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
			this->DockCntrPanel1->Style->BackColor2->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground2;
			this->DockCntrPanel1->Style->BorderColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarDockedBorder;
			this->DockCntrPanel1->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->DockCntrPanel1->Style->GradientAngle = 90;
			this->DockCntrPanel1->TabIndex = 0;
			// 
			// AppCntxMenuBar
			// 
			this->AppCntxMenuBar->AntiAlias = true;
			this->AppCntxMenuBar->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 9));
			this->AppCntxMenuBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(3) {this->PntrCntxMenu, this->GCCntxMenu, 
				this->LayerCntxMenu});
			this->AppCntxMenuBar->Location = System::Drawing::Point(541, 3);
			this->AppCntxMenuBar->Name = L"AppCntxMenuBar";
			this->AppCntxMenuBar->Size = System::Drawing::Size(182, 75);
			this->AppCntxMenuBar->Stretch = true;
			this->AppCntxMenuBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->AppCntxMenuBar->TabIndex = 1;
			this->AppCntxMenuBar->TabStop = false;
			this->AppCntxMenuBar->Text = L"contextMenuBar1";
			// 
			// PntrCntxMenu
			// 
			this->PntrCntxMenu->AutoExpandOnClick = true;
			this->PntrCntxMenu->Name = L"PntrCntxMenu";
			this->PntrCntxMenu->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(4) {this->PntrMStrkSize, 
				this->PntrMBrshBtn, this->PntrMErasBtn, this->PntrMCleanBtn});
			this->PntrCntxMenu->Text = L"Painter Context Menu";
			// 
			// PntrMStrkSize
			// 
			this->PntrMStrkSize->Name = L"PntrMStrkSize";
			this->PntrMStrkSize->Text = L"px";
			this->PntrMStrkSize->TextColor = System::Drawing::Color::Black;
			this->PntrMStrkSize->Value = 0;
			this->PntrMStrkSize->ValueChanged += gcnew System::EventHandler(this, &Form1::StrokeSize_ValueChanged);
			// 
			// PntrMBrshBtn
			// 
			this->PntrMBrshBtn->Command = this->AppPaintCmd;
			this->PntrMBrshBtn->CommandParameter = L"STROKE_BRUSH";
			this->PntrMBrshBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"PntrMBrshBtn.Icon")));
			this->PntrMBrshBtn->Name = L"PntrMBrshBtn";
			this->PntrMBrshBtn->Text = L"Brush Stroke";
			this->PntrMBrshBtn->Tooltip = L"Painting using brush stroke";
			// 
			// AppPaintCmd
			// 
			this->AppPaintCmd->Name = L"AppPaintCmd";
			this->AppPaintCmd->Executed += gcnew System::EventHandler(this, &Form1::AppPaintCmd_Executed);
			// 
			// PntrMErasBtn
			// 
			this->PntrMErasBtn->Command = this->AppPaintCmd;
			this->PntrMErasBtn->CommandParameter = L"STROKE_ERASE";
			this->PntrMErasBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"PntrMErasBtn.Icon")));
			this->PntrMErasBtn->Name = L"PntrMErasBtn";
			this->PntrMErasBtn->Text = L"Erase Stroke";
			this->PntrMErasBtn->Tooltip = L"Painting using erase stroke";
			// 
			// PntrMCleanBtn
			// 
			this->PntrMCleanBtn->Command = this->AppPaintCmd;
			this->PntrMCleanBtn->CommandParameter = L"CLEAN";
			this->PntrMCleanBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"PntrMCleanBtn.Icon")));
			this->PntrMCleanBtn->Name = L"PntrMCleanBtn";
			this->PntrMCleanBtn->Text = L"Clean canvas";
			this->PntrMCleanBtn->Tooltip = L"Clean the canvas";
			// 
			// GCCntxMenu
			// 
			this->GCCntxMenu->AutoExpandOnClick = true;
			this->GCCntxMenu->Name = L"GCCntxMenu";
			this->GCCntxMenu->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(11) {this->GCMStrkSize, this->GCMFGDBtn, 
				this->GCMBGDBtn, this->GCMPRFGDBtn, this->GCMPRBGDBtn, this->GCMMskBBtn, this->GCMMskWBtn, this->GCMErasBtn, this->GCMCutBtn, 
				this->GCMResetBtn, this->GCMAddBtn});
			this->GCCntxMenu->Text = L"GrabCut Context Menu";
			// 
			// GCMStrkSize
			// 
			this->GCMStrkSize->Name = L"GCMStrkSize";
			this->GCMStrkSize->Text = L"px";
			this->GCMStrkSize->TextColor = System::Drawing::Color::Black;
			this->GCMStrkSize->Value = 0;
			this->GCMStrkSize->ValueChanged += gcnew System::EventHandler(this, &Form1::StrokeSize_ValueChanged);
			// 
			// GCMFGDBtn
			// 
			this->GCMFGDBtn->Command = this->AppGrabCutCmd;
			this->GCMFGDBtn->CommandParameter = L"STROKE_FGD";
			this->GCMFGDBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"GCMFGDBtn.Icon")));
			this->GCMFGDBtn->Name = L"GCMFGDBtn";
			this->GCMFGDBtn->Tag = L"GrabCut Stroke";
			this->GCMFGDBtn->Text = L"Foreground Stroke";
			this->GCMFGDBtn->Tooltip = L"Painting using foreground stroke";
			// 
			// AppGrabCutCmd
			// 
			this->AppGrabCutCmd->Name = L"AppGrabCutCmd";
			this->AppGrabCutCmd->Executed += gcnew System::EventHandler(this, &Form1::AppGrabCutCmd_Executed);
			// 
			// GCMBGDBtn
			// 
			this->GCMBGDBtn->Command = this->AppGrabCutCmd;
			this->GCMBGDBtn->CommandParameter = L"STROKE_BGD";
			this->GCMBGDBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"GCMBGDBtn.Icon")));
			this->GCMBGDBtn->Name = L"GCMBGDBtn";
			this->GCMBGDBtn->Tag = L"GrabCut Stroke";
			this->GCMBGDBtn->Text = L"Background Stroke";
			this->GCMBGDBtn->Tooltip = L"Painting using background stroke";
			// 
			// GCMPRFGDBtn
			// 
			this->GCMPRFGDBtn->Command = this->AppGrabCutCmd;
			this->GCMPRFGDBtn->CommandParameter = L"STROKE_PRFGD";
			this->GCMPRFGDBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"GCMPRFGDBtn.Icon")));
			this->GCMPRFGDBtn->Name = L"GCMPRFGDBtn";
			this->GCMPRFGDBtn->Tag = L"GrabCut Stroke";
			this->GCMPRFGDBtn->Text = L"Possible Foreground Stroke";
			this->GCMPRFGDBtn->Tooltip = L"Painting using possible foreground stroke";
			// 
			// GCMPRBGDBtn
			// 
			this->GCMPRBGDBtn->Command = this->AppGrabCutCmd;
			this->GCMPRBGDBtn->CommandParameter = L"STROKE_PRBGD";
			this->GCMPRBGDBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"GCMPRBGDBtn.Icon")));
			this->GCMPRBGDBtn->Name = L"GCMPRBGDBtn";
			this->GCMPRBGDBtn->Tag = L"GrabCut Stroke";
			this->GCMPRBGDBtn->Text = L"Possible Background Stroke";
			this->GCMPRBGDBtn->Tooltip = L"Painting using possible background stroke";
			// 
			// GCMMskBBtn
			// 
			this->GCMMskBBtn->Command = this->AppGrabCutCmd;
			this->GCMMskBBtn->CommandParameter = L"STROKE_MSKB";
			this->GCMMskBBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"GCMMskBBtn.Icon")));
			this->GCMMskBBtn->Name = L"GCMMskBBtn";
			this->GCMMskBBtn->Tag = L"GrabCut Stroke";
			this->GCMMskBBtn->Text = L"Background Mask Stroke";
			this->GCMMskBBtn->Tooltip = L"Painting using background mask stroke";
			// 
			// GCMMskWBtn
			// 
			this->GCMMskWBtn->Command = this->AppGrabCutCmd;
			this->GCMMskWBtn->CommandParameter = L"STROKE_MSKW";
			this->GCMMskWBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"GCMMskWBtn.Icon")));
			this->GCMMskWBtn->Name = L"GCMMskWBtn";
			this->GCMMskWBtn->Tag = L"GrabCut Stroke";
			this->GCMMskWBtn->Text = L"Foreground Mask Stroke";
			this->GCMMskWBtn->Tooltip = L"Painting using foreground mask stroke";
			// 
			// GCMErasBtn
			// 
			this->GCMErasBtn->Command = this->AppGrabCutCmd;
			this->GCMErasBtn->CommandParameter = L"STROKE_ERASE";
			this->GCMErasBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"GCMErasBtn.Icon")));
			this->GCMErasBtn->Name = L"GCMErasBtn";
			this->GCMErasBtn->Tag = L"GrabCut Stroke";
			this->GCMErasBtn->Text = L"GrabCut Stroke";
			this->GCMErasBtn->Tooltip = L"Painting using erase stroke";
			// 
			// GCMCutBtn
			// 
			this->GCMCutBtn->Command = this->AppGrabCutCmd;
			this->GCMCutBtn->CommandParameter = L"CUT";
			this->GCMCutBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"GCMCutBtn.Icon")));
			this->GCMCutBtn->Name = L"GCMCutBtn";
			this->GCMCutBtn->Text = L"Cut region";
			this->GCMCutBtn->Tooltip = L"Perform GrabCut";
			// 
			// GCMResetBtn
			// 
			this->GCMResetBtn->Command = this->AppGrabCutCmd;
			this->GCMResetBtn->CommandParameter = L"RESET";
			this->GCMResetBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"GCMResetBtn.Icon")));
			this->GCMResetBtn->Name = L"GCMResetBtn";
			this->GCMResetBtn->Text = L"Reset GC";
			this->GCMResetBtn->Tooltip = L"Reset GrabCut";
			// 
			// GCMAddBtn
			// 
			this->GCMAddBtn->Command = this->AppGrabCutCmd;
			this->GCMAddBtn->CommandParameter = L"ADD";
			this->GCMAddBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"GCMAddBtn.Icon")));
			this->GCMAddBtn->Name = L"GCMAddBtn";
			this->GCMAddBtn->Text = L"Add region";
			this->GCMAddBtn->Tooltip = L"Add cutted region";
			// 
			// LayerCntxMenu
			// 
			this->LayerCntxMenu->AutoExpandOnClick = true;
			this->LayerCntxMenu->Name = L"LayerCntxMenu";
			this->LayerCntxMenu->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->LayrMDelBtn, this->LayrMShowBtn});
			this->LayerCntxMenu->Text = L"Layer Context Menu";
			// 
			// LayrMDelBtn
			// 
			this->LayrMDelBtn->Command = this->AppLayerCmd;
			this->LayrMDelBtn->CommandParameter = L"DELETE";
			this->LayrMDelBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"LayrMDelBtn.Icon")));
			this->LayrMDelBtn->Name = L"LayrMDelBtn";
			this->LayrMDelBtn->Text = L"Delete";
			// 
			// AppLayerCmd
			// 
			this->AppLayerCmd->Name = L"AppLayerCmd";
			this->AppLayerCmd->Executed += gcnew System::EventHandler(this, &Form1::AppLayerCmd_Executed);
			// 
			// LayrMShowBtn
			// 
			this->LayrMShowBtn->Command = this->AppLayerCmd;
			this->LayrMShowBtn->CommandParameter = L"SHOW";
			this->LayrMShowBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"LayrMShowBtn.Icon")));
			this->LayrMShowBtn->Name = L"LayrMShowBtn";
			this->LayrMShowBtn->Text = L"Show";
			this->LayrMShowBtn->Tooltip = L"Show all detail images ";
			// 
			// LayerTree
			// 
			this->LayerTree->AccessibleRole = System::Windows::Forms::AccessibleRole::Outline;
			this->LayerTree->AllowDrop = true;
			this->LayerTree->BackColor = System::Drawing::SystemColors::Window;
			// 
			// 
			// 
			this->LayerTree->BackgroundStyle->Class = L"TreeBorderKey";
			this->LayerTree->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->LayerTree->CheckBoxImageChecked = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"LayerTree.CheckBoxImageChecked")));
			this->LayerTree->CheckBoxImageUnChecked = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"LayerTree.CheckBoxImageUnChecked")));
			this->AppCntxMenuBar->SetContextMenuEx(this->LayerTree, this->LayerCntxMenu);
			this->LayerTree->Dock = System::Windows::Forms::DockStyle::Fill;
			this->LayerTree->GridLinesColor = System::Drawing::Color::Black;
			this->LayerTree->GridRowLines = true;
			this->LayerTree->HotTracking = true;
			this->LayerTree->Location = System::Drawing::Point(0, 0);
			this->LayerTree->Name = L"LayerTree";
			this->LayerTree->NodesConnector = this->nodeConnector1;
			this->LayerTree->NodeStyle = this->elementStyle1;
			this->LayerTree->PathSeparator = L";";
			this->LayerTree->SelectionBoxStyle = DevComponents::AdvTree::eSelectionStyle::FullRowSelect;
			this->LayerTree->Size = System::Drawing::Size(355, 341);
			this->LayerTree->TabIndex = 0;
			this->LayerTree->Text = L"advTree1";
			this->LayerTree->AfterCheck += gcnew DevComponents::AdvTree::AdvTreeCellEventHandler(this, &Form1::LayerTree_AfterCheck);
			this->LayerTree->AfterNodeSelect += gcnew DevComponents::AdvTree::AdvTreeNodeEventHandler(this, &Form1::LayerTree_AfterNodeSelect);
			this->LayerTree->NodeDoubleClick += gcnew DevComponents::AdvTree::TreeNodeMouseEventHandler(this, &Form1::LayerTree_NodeDoubleClick);
			// 
			// nodeConnector1
			// 
			this->nodeConnector1->LineColor = System::Drawing::SystemColors::ControlText;
			// 
			// elementStyle1
			// 
			this->elementStyle1->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->elementStyle1->Name = L"elementStyle1";
			this->elementStyle1->TextColor = System::Drawing::SystemColors::ControlText;
			// 
			// CandidateLayer
			// 
			this->CandidateLayer->AccessibleRole = System::Windows::Forms::AccessibleRole::Outline;
			this->CandidateLayer->AllowDrop = true;
			this->CandidateLayer->BackColor = System::Drawing::SystemColors::Window;
			// 
			// 
			// 
			this->CandidateLayer->BackgroundStyle->Class = L"TreeBorderKey";
			this->CandidateLayer->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->AppCntxMenuBar->SetContextMenuEx(this->CandidateLayer, this->LayerCntxMenu);
			this->CandidateLayer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->CandidateLayer->GridLinesColor = System::Drawing::Color::Black;
			this->CandidateLayer->GridRowLines = true;
			this->CandidateLayer->HotTracking = true;
			this->CandidateLayer->Location = System::Drawing::Point(0, 0);
			this->CandidateLayer->Name = L"CandidateLayer";
			this->CandidateLayer->NodesConnector = this->nodeConnector1;
			this->CandidateLayer->NodeStyle = this->elementStyle1;
			this->CandidateLayer->PathSeparator = L";";
			this->CandidateLayer->SelectionBoxStyle = DevComponents::AdvTree::eSelectionStyle::FullRowSelect;
			this->CandidateLayer->Size = System::Drawing::Size(355, 341);
			this->CandidateLayer->TabIndex = 0;
			this->CandidateLayer->Text = L"CandidateTree";
			this->CandidateLayer->AfterCheck += gcnew DevComponents::AdvTree::AdvTreeCellEventHandler(this, &Form1::CandidateLayer_AfterCheck);
			this->CandidateLayer->AfterNodeSelect += gcnew DevComponents::AdvTree::AdvTreeNodeEventHandler(this, &Form1::CandidateLayer_AfterNodeSelect);
			this->CandidateLayer->NodeDoubleClick += gcnew DevComponents::AdvTree::TreeNodeMouseEventHandler(this, &Form1::CandidateLayer_NodeDoubleClick);
			// 
			// WordArtLayer
			// 
			this->WordArtLayer->AccessibleRole = System::Windows::Forms::AccessibleRole::Outline;
			this->WordArtLayer->AllowDrop = true;
			this->WordArtLayer->BackColor = System::Drawing::SystemColors::Window;
			// 
			// 
			// 
			this->WordArtLayer->BackgroundStyle->Class = L"TreeBorderKey";
			this->WordArtLayer->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->AppCntxMenuBar->SetContextMenuEx(this->WordArtLayer, this->LayerCntxMenu);
			this->WordArtLayer->Dock = System::Windows::Forms::DockStyle::Fill;
			this->WordArtLayer->GridLinesColor = System::Drawing::Color::Black;
			this->WordArtLayer->GridRowLines = true;
			this->WordArtLayer->HotTracking = true;
			this->WordArtLayer->Location = System::Drawing::Point(0, 0);
			this->WordArtLayer->Name = L"WordArtLayer";
			this->WordArtLayer->NodesConnector = this->nodeConnector1;
			this->WordArtLayer->NodeStyle = this->elementStyle1;
			this->WordArtLayer->PathSeparator = L";";
			this->WordArtLayer->SelectionBoxStyle = DevComponents::AdvTree::eSelectionStyle::FullRowSelect;
			this->WordArtLayer->Size = System::Drawing::Size(355, 341);
			this->WordArtLayer->Styles->Add(this->elementStyle1);
			this->WordArtLayer->TabIndex = 0;
			this->WordArtLayer->Text = L"WordArtLayer ";
			this->WordArtLayer->AfterCheck += gcnew DevComponents::AdvTree::AdvTreeCellEventHandler(this, &Form1::WordArtLayer_aftercheck);
			this->WordArtLayer->AfterNodeSelect += gcnew DevComponents::AdvTree::AdvTreeNodeEventHandler(this, &Form1::WordArtLayer_AfterNodeSelect);
			this->WordArtLayer->NodeDoubleClick += gcnew DevComponents::AdvTree::TreeNodeMouseEventHandler(this, &Form1::WordArtLayer_NodeDoubleClick);
			// 
			// HKOGLPanel1
			// 
			this->HKOGLPanel1->AllowDrop = true;
			hkcCameraProp1->Enabled = true;
			hkcCameraProp1->Far = 1000;
			hkcCameraProp1->Fov = 45;
			hkcCameraProp1->Near = -1000;
			hkcCameraProp1->Type = HKOGLPanel::HKCCameraProp::CAMERATYPE::ORTHOGRAPHIC;
			hkcCameraProp1->Zoom = 1;
			this->HKOGLPanel1->Camera_Property = hkcCameraProp1;
			hkcDisplayProp1->Back_Color = System::Drawing::Color::White;
			hkcDisplayProp1->Grid_Axis = System::Drawing::Color::Black;
			hkcDisplayProp1->Grid_Draw = false;
			hkcDisplayProp1->Grid_Line = System::Drawing::Color::DimGray;
			this->HKOGLPanel1->Display_Property = hkcDisplayProp1;
			this->HKOGLPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->HKOGLPanel1->Empty_Panel = false;
			this->HKOGLPanel1->Location = System::Drawing::Point(0, 0);
			this->HKOGLPanel1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->HKOGLPanel1->Name = L"HKOGLPanel1";
			hkcPixelFormat1->Accumu_Buffer_Bits = HKOGLPanel::HKCPixelFormat::PIXELBITS::BITS_0;
			hkcPixelFormat1->Alpha_Buffer_Bits = HKOGLPanel::HKCPixelFormat::PIXELBITS::BITS_32;
			hkcPixelFormat1->Stencil_Buffer_Bits = HKOGLPanel::HKCPixelFormat::PIXELBITS::BITS_0;
			this->HKOGLPanel1->Pixel_Format = hkcPixelFormat1;
			this->HKOGLPanel1->Size = System::Drawing::Size(743, 361);
			this->HKOGLPanel1->TabIndex = 0;
			hkcTrackballProp1->Const_Res = false;
			hkcTrackballProp1->Delta_Res = 200;
			hkcTrackballProp1->Enabled = true;
			hkcTrackballProp1->Move_Res = 100;
			hkcTrackballTrig1->Key_Down = false;
			hkcTrackballTrig1->Keyboard = System::Windows::Forms::Keys::None;
			hkcTrackballTrig1->Mouse = System::Windows::Forms::MouseButtons::Right;
			hkcTrackballTrig1->Mouse_Down = false;
			hkcTrackballProp1->Move_Trigger = hkcTrackballTrig1;
			hkcTrackballTrig2->Key_Down = false;
			hkcTrackballTrig2->Keyboard = System::Windows::Forms::Keys::None;
			hkcTrackballTrig2->Mouse = System::Windows::Forms::MouseButtons::None;
			hkcTrackballTrig2->Mouse_Down = false;
			hkcTrackballProp1->Rotate_Trigger = hkcTrackballTrig2;
			hkcTrackballProp1->Zoom_Res = 100;
			hkcTrackballTrig3->Key_Down = false;
			hkcTrackballTrig3->Keyboard = System::Windows::Forms::Keys::None;
			hkcTrackballTrig3->Mouse = System::Windows::Forms::MouseButtons::None;
			hkcTrackballTrig3->Mouse_Down = false;
			hkcTrackballProp1->Zoom_Trigger = hkcTrackballTrig3;
			this->HKOGLPanel1->Trackball_Property = hkcTrackballProp1;
			this->HKOGLPanel1->Load += gcnew System::EventHandler(this, &Form1::OGLPanel_Load);
			this->HKOGLPanel1->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::OGLPanel_DragDrop);
			this->HKOGLPanel1->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::OGLPanel_DragEnter);
			this->HKOGLPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::OGLPanel_Paint);
			this->HKOGLPanel1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Editting_KeyDown);
			this->HKOGLPanel1->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::OGLPanel_KeyUp);
			this->HKOGLPanel1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Region_Click);
			this->HKOGLPanel1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Editting_MouseDown);
			this->HKOGLPanel1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Editting_MouseMove);
			this->HKOGLPanel1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Editting_MouseUp);
			this->HKOGLPanel1->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Editting_MouseWheel);
			this->HKOGLPanel1->Resize += gcnew System::EventHandler(this, &Form1::OGLPanel_Resize);
			// 
			// DockCntrItem1
			// 
			this->DockCntrItem1->Control = this->DockCntrPanel1;
			this->DockCntrItem1->Name = L"DockCntrItem1";
			this->DockCntrItem1->Text = L"Display 1";
			// 
			// dockSite1
			// 
			this->dockSite1->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->dockSite1->Dock = System::Windows::Forms::DockStyle::Left;
			this->dockSite1->DocumentDockContainer = (gcnew DevComponents::DotNetBar::DocumentDockContainer());
			this->dockSite1->Location = System::Drawing::Point(5, 176);
			this->dockSite1->Name = L"dockSite1";
			this->dockSite1->Size = System::Drawing::Size(0, 392);
			this->dockSite1->TabIndex = 0;
			this->dockSite1->TabStop = false;
			// 
			// dockSite2
			// 
			this->dockSite2->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->dockSite2->Controls->Add(this->bar3);
			this->dockSite2->Dock = System::Windows::Forms::DockStyle::Right;
			this->dockSite2->DocumentDockContainer = (gcnew DevComponents::DotNetBar::DocumentDockContainer(gcnew cli::array< DevComponents::DotNetBar::DocumentBaseContainer^  >(1) {(cli::safe_cast<DevComponents::DotNetBar::DocumentBaseContainer^  >((gcnew DevComponents::DotNetBar::DocumentBarContainer(this->bar3, 
				361, 392))))}, DevComponents::DotNetBar::eOrientation::Horizontal));
			this->dockSite2->Location = System::Drawing::Point(754, 176);
			this->dockSite2->Name = L"dockSite2";
			this->dockSite2->Size = System::Drawing::Size(364, 392);
			this->dockSite2->TabIndex = 1;
			this->dockSite2->TabStop = false;
			// 
			// bar3
			// 
			this->bar3->AccessibleDescription = L"DotNetBar Bar (bar3)";
			this->bar3->AccessibleName = L"DotNetBar Bar";
			this->bar3->AccessibleRole = System::Windows::Forms::AccessibleRole::ToolBar;
			this->bar3->AutoSyncBarCaption = true;
			this->bar3->CloseSingleTab = true;
			this->bar3->Controls->Add(this->LayrDockCntrPanel);
			this->bar3->Controls->Add(this->WordArtLayerCntrPanel);
			this->bar3->Controls->Add(this->PropDockCntrPanel);
			this->bar3->Controls->Add(this->ParamDockCntrPanel);
			this->bar3->Controls->Add(this->ToolDockCntrPanel);
			this->bar3->Controls->Add(this->CandidateDockCntrPanel);
			this->bar3->Font = (gcnew System::Drawing::Font(L"新細明體", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->bar3->GrabHandleStyle = DevComponents::DotNetBar::eGrabHandleStyle::Caption;
			this->bar3->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(6) {this->LayrDockCntrItem, this->WordArtItem, 
				this->PropDockCntrItem, this->ParamDockCntrItem, this->ToolDockCntrItem, this->CandidateItem});
			this->bar3->LayoutType = DevComponents::DotNetBar::eLayoutType::DockContainer;
			this->bar3->Location = System::Drawing::Point(3, 0);
			this->bar3->Name = L"bar3";
			this->bar3->SelectedDockTab = 0;
			this->bar3->Size = System::Drawing::Size(361, 392);
			this->bar3->Stretch = true;
			this->bar3->Style = DevComponents::DotNetBar::eDotNetBarStyle::Windows7;
			this->bar3->TabIndex = 0;
			this->bar3->TabStop = false;
			this->bar3->Text = L"Layers";
			// 
			// LayrDockCntrPanel
			// 
			this->LayrDockCntrPanel->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::Windows7;
			this->LayrDockCntrPanel->Controls->Add(this->LayerTree);
			this->LayrDockCntrPanel->Location = System::Drawing::Point(3, 23);
			this->LayrDockCntrPanel->Name = L"LayrDockCntrPanel";
			this->LayrDockCntrPanel->Size = System::Drawing::Size(355, 341);
			this->LayrDockCntrPanel->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->LayrDockCntrPanel->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
			this->LayrDockCntrPanel->Style->BorderColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarDockedBorder;
			this->LayrDockCntrPanel->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->LayrDockCntrPanel->Style->GradientAngle = 90;
			this->LayrDockCntrPanel->TabIndex = 4;
			// 
			// WordArtLayerCntrPanel
			// 
			this->WordArtLayerCntrPanel->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::Windows7;
			this->WordArtLayerCntrPanel->Controls->Add(this->WordArtLayer);
			this->WordArtLayerCntrPanel->Location = System::Drawing::Point(3, 23);
			this->WordArtLayerCntrPanel->Name = L"WordArtLayerCntrPanel";
			this->WordArtLayerCntrPanel->Size = System::Drawing::Size(355, 341);
			this->WordArtLayerCntrPanel->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->WordArtLayerCntrPanel->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
			this->WordArtLayerCntrPanel->Style->BorderColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarDockedBorder;
			this->WordArtLayerCntrPanel->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->WordArtLayerCntrPanel->Style->GradientAngle = 90;
			this->WordArtLayerCntrPanel->TabIndex = 8;
			// 
			// PropDockCntrPanel
			// 
			this->PropDockCntrPanel->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::Windows7;
			this->PropDockCntrPanel->Controls->Add(this->PropGrid);
			this->PropDockCntrPanel->Location = System::Drawing::Point(3, 23);
			this->PropDockCntrPanel->Name = L"PropDockCntrPanel";
			this->PropDockCntrPanel->Size = System::Drawing::Size(355, 341);
			this->PropDockCntrPanel->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->PropDockCntrPanel->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
			this->PropDockCntrPanel->Style->BackColor2->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground2;
			this->PropDockCntrPanel->Style->BorderColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarDockedBorder;
			this->PropDockCntrPanel->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->PropDockCntrPanel->Style->GradientAngle = 90;
			this->PropDockCntrPanel->TabIndex = 2;
			// 
			// PropGrid
			// 
			this->PropGrid->CategoryForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->PropGrid->Dock = System::Windows::Forms::DockStyle::Fill;
			this->PropGrid->Location = System::Drawing::Point(0, 0);
			this->PropGrid->Name = L"PropGrid";
			this->PropGrid->Size = System::Drawing::Size(355, 341);
			this->PropGrid->TabIndex = 1;
			this->PropGrid->ToolbarVisible = false;
			this->PropGrid->PropertyValueChanged += gcnew System::Windows::Forms::PropertyValueChangedEventHandler(this, &Form1::PropGrid_PropertyValueChanged);
			// 
			// ParamDockCntrPanel
			// 
			this->ParamDockCntrPanel->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::Windows7;
			this->ParamDockCntrPanel->Controls->Add(this->ParamGrid);
			this->ParamDockCntrPanel->Location = System::Drawing::Point(3, 23);
			this->ParamDockCntrPanel->Name = L"ParamDockCntrPanel";
			this->ParamDockCntrPanel->Size = System::Drawing::Size(355, 341);
			this->ParamDockCntrPanel->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->ParamDockCntrPanel->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
			this->ParamDockCntrPanel->Style->BackColor2->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground2;
			this->ParamDockCntrPanel->Style->BorderColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarDockedBorder;
			this->ParamDockCntrPanel->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->ParamDockCntrPanel->Style->GradientAngle = 90;
			this->ParamDockCntrPanel->TabIndex = 0;
			// 
			// ParamGrid
			// 
			this->ParamGrid->CategoryForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->ParamGrid->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ParamGrid->Location = System::Drawing::Point(0, 0);
			this->ParamGrid->Name = L"ParamGrid";
			this->ParamGrid->Size = System::Drawing::Size(355, 341);
			this->ParamGrid->TabIndex = 0;
			this->ParamGrid->ToolbarVisible = false;
			this->ParamGrid->PropertyValueChanged += gcnew System::Windows::Forms::PropertyValueChangedEventHandler(this, &Form1::ParamGrid_PropertyValueChanged);
			// 
			// ToolDockCntrPanel
			// 
			this->ToolDockCntrPanel->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::Windows7;
			this->ToolDockCntrPanel->Controls->Add(this->ToolGrid);
			this->ToolDockCntrPanel->Location = System::Drawing::Point(3, 23);
			this->ToolDockCntrPanel->Name = L"ToolDockCntrPanel";
			this->ToolDockCntrPanel->Size = System::Drawing::Size(355, 341);
			this->ToolDockCntrPanel->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->ToolDockCntrPanel->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
			this->ToolDockCntrPanel->Style->BorderColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarDockedBorder;
			this->ToolDockCntrPanel->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->ToolDockCntrPanel->Style->GradientAngle = 90;
			this->ToolDockCntrPanel->TabIndex = 6;
			// 
			// ToolGrid
			// 
			this->ToolGrid->CategoryForeColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->ToolGrid->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ToolGrid->Location = System::Drawing::Point(0, 0);
			this->ToolGrid->Name = L"ToolGrid";
			this->ToolGrid->PropertySort = System::Windows::Forms::PropertySort::NoSort;
			this->ToolGrid->Size = System::Drawing::Size(355, 341);
			this->ToolGrid->TabIndex = 1;
			this->ToolGrid->ToolbarVisible = false;
			this->ToolGrid->PropertyValueChanged += gcnew System::Windows::Forms::PropertyValueChangedEventHandler(this, &Form1::ToolGrid_PropertyValueChanged);
			// 
			// CandidateDockCntrPanel
			// 
			this->CandidateDockCntrPanel->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::Windows7;
			this->CandidateDockCntrPanel->Controls->Add(this->CandidateLayer);
			this->CandidateDockCntrPanel->Location = System::Drawing::Point(3, 23);
			this->CandidateDockCntrPanel->Name = L"CandidateDockCntrPanel";
			this->CandidateDockCntrPanel->Size = System::Drawing::Size(355, 341);
			this->CandidateDockCntrPanel->Style->Alignment = System::Drawing::StringAlignment::Center;
			this->CandidateDockCntrPanel->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
			this->CandidateDockCntrPanel->Style->BorderColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarDockedBorder;
			this->CandidateDockCntrPanel->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
			this->CandidateDockCntrPanel->Style->GradientAngle = 90;
			this->CandidateDockCntrPanel->TabIndex = 8;
			// 
			// LayrDockCntrItem
			// 
			this->LayrDockCntrItem->Control = this->LayrDockCntrPanel;
			this->LayrDockCntrItem->DefaultFloatingSize = System::Drawing::Size(200, 400);
			this->LayrDockCntrItem->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"LayrDockCntrItem.Icon")));
			this->LayrDockCntrItem->Name = L"LayrDockCntrItem";
			this->LayrDockCntrItem->Text = L"Layers";
			// 
			// WordArtItem
			// 
			this->WordArtItem->Control = this->WordArtLayerCntrPanel;
			this->WordArtItem->DefaultFloatingSize = System::Drawing::Size(200, 400);
			this->WordArtItem->Name = L"WordArtItem";
			this->WordArtItem->Text = L"WordArtItem";
			// 
			// PropDockCntrItem
			// 
			this->PropDockCntrItem->Control = this->PropDockCntrPanel;
			this->PropDockCntrItem->DefaultFloatingSize = System::Drawing::Size(200, 400);
			this->PropDockCntrItem->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"PropDockCntrItem.Icon")));
			this->PropDockCntrItem->Name = L"PropDockCntrItem";
			this->PropDockCntrItem->Text = L"Property";
			// 
			// ParamDockCntrItem
			// 
			this->ParamDockCntrItem->Control = this->ParamDockCntrPanel;
			this->ParamDockCntrItem->DefaultFloatingSize = System::Drawing::Size(200, 400);
			this->ParamDockCntrItem->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"ParamDockCntrItem.Icon")));
			this->ParamDockCntrItem->Name = L"ParamDockCntrItem";
			this->ParamDockCntrItem->Text = L"Parameter";
			// 
			// ToolDockCntrItem
			// 
			this->ToolDockCntrItem->Control = this->ToolDockCntrPanel;
			this->ToolDockCntrItem->DefaultFloatingSize = System::Drawing::Size(200, 400);
			this->ToolDockCntrItem->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"ToolDockCntrItem.Icon")));
			this->ToolDockCntrItem->Name = L"ToolDockCntrItem";
			this->ToolDockCntrItem->Text = L"Tool";
			// 
			// CandidateItem
			// 
			this->CandidateItem->Control = this->CandidateDockCntrPanel;
			this->CandidateItem->DefaultFloatingSize = System::Drawing::Size(200, 400);
			this->CandidateItem->Name = L"CandidateItem";
			this->CandidateItem->Text = L"Candidates";
			// 
			// dockSite8
			// 
			this->dockSite8->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->dockSite8->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->dockSite8->Location = System::Drawing::Point(5, 568);
			this->dockSite8->Name = L"dockSite8";
			this->dockSite8->Size = System::Drawing::Size(1113, 0);
			this->dockSite8->TabIndex = 7;
			this->dockSite8->TabStop = false;
			// 
			// dockSite5
			// 
			this->dockSite5->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->dockSite5->Dock = System::Windows::Forms::DockStyle::Left;
			this->dockSite5->Location = System::Drawing::Point(5, 176);
			this->dockSite5->Name = L"dockSite5";
			this->dockSite5->Size = System::Drawing::Size(0, 392);
			this->dockSite5->TabIndex = 4;
			this->dockSite5->TabStop = false;
			// 
			// dockSite6
			// 
			this->dockSite6->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->dockSite6->Dock = System::Windows::Forms::DockStyle::Right;
			this->dockSite6->Location = System::Drawing::Point(1118, 176);
			this->dockSite6->Name = L"dockSite6";
			this->dockSite6->Size = System::Drawing::Size(0, 392);
			this->dockSite6->TabIndex = 5;
			this->dockSite6->TabStop = false;
			// 
			// dockSite7
			// 
			this->dockSite7->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->dockSite7->Dock = System::Windows::Forms::DockStyle::Top;
			this->dockSite7->Location = System::Drawing::Point(5, 176);
			this->dockSite7->Name = L"dockSite7";
			this->dockSite7->Size = System::Drawing::Size(1113, 0);
			this->dockSite7->TabIndex = 6;
			this->dockSite7->TabStop = false;
			// 
			// dockSite3
			// 
			this->dockSite3->AccessibleRole = System::Windows::Forms::AccessibleRole::Window;
			this->dockSite3->Dock = System::Windows::Forms::DockStyle::Top;
			this->dockSite3->DocumentDockContainer = (gcnew DevComponents::DotNetBar::DocumentDockContainer());
			this->dockSite3->Location = System::Drawing::Point(5, 176);
			this->dockSite3->Name = L"dockSite3";
			this->dockSite3->Size = System::Drawing::Size(1113, 0);
			this->dockSite3->TabIndex = 2;
			this->dockSite3->TabStop = false;
			// 
			// RibbonControl
			// 
			// 
			// 
			// 
			this->RibbonControl->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->RibbonControl->CaptionVisible = true;
			this->RibbonControl->Controls->Add(this->ErrorCorrectionPanel);
			this->RibbonControl->Controls->Add(this->EditingToolsPanel);
			this->RibbonControl->Controls->Add(this->RibbonAppPanel);
			this->RibbonControl->Controls->Add(this->RibbonToolPanel);
			this->RibbonControl->Controls->Add(this->ribbonPanel1);
			this->RibbonControl->Dock = System::Windows::Forms::DockStyle::Top;
			this->RibbonControl->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(6) {this->office2007StartButton1, 
				this->RibbonAppTab, this->EditingTools, this->ErrorCorrection, this->RibbonToolTab, this->Debug});
			this->RibbonControl->KeyTipsFont = (gcnew System::Drawing::Font(L"Tahoma", 7));
			this->RibbonControl->Location = System::Drawing::Point(5, 1);
			this->RibbonControl->Name = L"RibbonControl";
			this->RibbonControl->Padding = System::Windows::Forms::Padding(0, 0, 0, 2);
			this->RibbonControl->QuickToolbarItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(3) {this->QickOpnBtn, 
				this->QickSavBtn, this->qatCustomizeItem1});
			this->RibbonControl->Size = System::Drawing::Size(1113, 175);
			this->RibbonControl->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->RibbonControl->SystemText->MaximizeRibbonText = L"&Maximize the Ribbon";
			this->RibbonControl->SystemText->MinimizeRibbonText = L"Mi&nimize the Ribbon";
			this->RibbonControl->SystemText->QatAddItemText = L"&Add to Quick Access Toolbar";
			this->RibbonControl->SystemText->QatCustomizeMenuLabel = L"<b>Customize Quick Access Toolbar</b>";
			this->RibbonControl->SystemText->QatCustomizeText = L"&Customize Quick Access Toolbar...";
			this->RibbonControl->SystemText->QatDialogAddButton = L"&Add >>";
			this->RibbonControl->SystemText->QatDialogCancelButton = L"Cancel";
			this->RibbonControl->SystemText->QatDialogCaption = L"Customize Quick Access Toolbar";
			this->RibbonControl->SystemText->QatDialogCategoriesLabel = L"&Choose commands from:";
			this->RibbonControl->SystemText->QatDialogOkButton = L"OK";
			this->RibbonControl->SystemText->QatDialogPlacementCheckbox = L"&Place Quick Access Toolbar below the Ribbon";
			this->RibbonControl->SystemText->QatDialogRemoveButton = L"&Remove";
			this->RibbonControl->SystemText->QatPlaceAboveRibbonText = L"&Place Quick Access Toolbar above the Ribbon";
			this->RibbonControl->SystemText->QatPlaceBelowRibbonText = L"&Place Quick Access Toolbar below the Ribbon";
			this->RibbonControl->SystemText->QatRemoveItemText = L"&Remove from Quick Access Toolbar";
			this->RibbonControl->TabGroupHeight = 14;
			this->RibbonControl->TabIndex = 8;
			this->RibbonControl->Text = L"RibbonControl";
			this->RibbonControl->TitleText = L"Application";
			// 
			// EditingToolsPanel
			// 
			this->EditingToolsPanel->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->EditingToolsPanel->Controls->Add(this->ribbonBar3);
			this->EditingToolsPanel->Controls->Add(this->ribbonBar2);
			this->EditingToolsPanel->Controls->Add(this->ScalingToolsRibnBar);
			this->EditingToolsPanel->Controls->Add(this->ribbonBar5);
			this->EditingToolsPanel->Controls->Add(this->ribbonBar6);
			this->EditingToolsPanel->Controls->Add(this->StringLineToolsRibnBar);
			this->EditingToolsPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->EditingToolsPanel->Location = System::Drawing::Point(0, 53);
			this->EditingToolsPanel->Name = L"EditingToolsPanel";
			this->EditingToolsPanel->Padding = System::Windows::Forms::Padding(3, 0, 3, 3);
			this->EditingToolsPanel->Size = System::Drawing::Size(1113, 120);
			// 
			// 
			// 
			this->EditingToolsPanel->Style->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->EditingToolsPanel->StyleMouseDown->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->EditingToolsPanel->StyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->EditingToolsPanel->TabIndex = 1;
			this->EditingToolsPanel->Visible = false;
			// 
			// ribbonBar3
			// 
			this->ribbonBar3->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->ribbonBar3->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonBar3->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->ribbonBar3->ContainerControlProcessDialogKey = true;
			this->ribbonBar3->Controls->Add(this->label1);
			this->ribbonBar3->Controls->Add(this->VisualQualitybar);
			this->ribbonBar3->Controls->Add(this->label2);
			this->ribbonBar3->Controls->Add(this->QRenergyBar);
			this->ribbonBar3->Dock = System::Windows::Forms::DockStyle::Left;
			this->ribbonBar3->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->itemContainer30});
			this->ribbonBar3->Location = System::Drawing::Point(905, 0);
			this->ribbonBar3->Name = L"ribbonBar3";
			this->ribbonBar3->ResizeOrderIndex = 2;
			this->ribbonBar3->Size = System::Drawing::Size(149, 117);
			this->ribbonBar3->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->ribbonBar3->TabIndex = 9;
			this->ribbonBar3->Text = L"ribbonBar3";
			// 
			// 
			// 
			this->ribbonBar3->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonBar3->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(35, 6);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(77, 12);
			this->label1->TabIndex = 33;
			this->label1->Text = L"Visual Quality :";
			// 
			// VisualQualitybar
			// 
			// 
			// 
			// 
			this->VisualQualitybar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->VisualQualitybar->ChunkColor = System::Drawing::Color::Lime;
			this->VisualQualitybar->Location = System::Drawing::Point(4, 24);
			this->VisualQualitybar->Maximum = 1000;
			this->VisualQualitybar->Name = L"VisualQualitybar";
			this->VisualQualitybar->Size = System::Drawing::Size(139, 23);
			this->VisualQualitybar->Style = DevComponents::DotNetBar::eDotNetBarStyle::Office2000;
			this->VisualQualitybar->TabIndex = 35;
			this->VisualQualitybar->Text = L"VisualQualitybar";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(42, 53);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(62, 12);
			this->label2->TabIndex = 34;
			this->label2->Text = L"QR energy :";
			// 
			// QRenergyBar
			// 
			// 
			// 
			// 
			this->QRenergyBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->QRenergyBar->ChunkColor = System::Drawing::Color::Lime;
			this->QRenergyBar->Location = System::Drawing::Point(4, 71);
			this->QRenergyBar->Maximum = 1000;
			this->QRenergyBar->Name = L"QRenergyBar";
			this->QRenergyBar->Size = System::Drawing::Size(139, 23);
			this->QRenergyBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::Office2000;
			this->QRenergyBar->TabIndex = 36;
			this->QRenergyBar->Text = L"QR";
			// 
			// itemContainer30
			// 
			// 
			// 
			// 
			this->itemContainer30->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer30->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer30->Name = L"itemContainer30";
			this->itemContainer30->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(4) {this->controlContainerItem1, 
				this->controlContainerItem2, this->controlContainerItem3, this->controlContainerItem4});
			// 
			// controlContainerItem1
			// 
			this->controlContainerItem1->AllowItemResize = false;
			this->controlContainerItem1->Control = this->label1;
			this->controlContainerItem1->MenuVisibility = DevComponents::DotNetBar::eMenuVisibility::VisibleAlways;
			this->controlContainerItem1->Name = L"controlContainerItem1";
			// 
			// controlContainerItem2
			// 
			this->controlContainerItem2->AllowItemResize = false;
			this->controlContainerItem2->Control = this->VisualQualitybar;
			this->controlContainerItem2->MenuVisibility = DevComponents::DotNetBar::eMenuVisibility::VisibleAlways;
			this->controlContainerItem2->Name = L"controlContainerItem2";
			// 
			// controlContainerItem3
			// 
			this->controlContainerItem3->AllowItemResize = false;
			this->controlContainerItem3->Control = this->label2;
			this->controlContainerItem3->MenuVisibility = DevComponents::DotNetBar::eMenuVisibility::VisibleAlways;
			this->controlContainerItem3->Name = L"controlContainerItem3";
			// 
			// controlContainerItem4
			// 
			this->controlContainerItem4->AllowItemResize = false;
			this->controlContainerItem4->Control = this->QRenergyBar;
			this->controlContainerItem4->MenuVisibility = DevComponents::DotNetBar::eMenuVisibility::VisibleAlways;
			this->controlContainerItem4->Name = L"controlContainerItem4";
			// 
			// ribbonBar2
			// 
			this->ribbonBar2->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->ribbonBar2->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonBar2->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->ribbonBar2->ContainerControlProcessDialogKey = true;
			this->ribbonBar2->Dock = System::Windows::Forms::DockStyle::Left;
			this->ribbonBar2->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->QRcodeLabel});
			this->ribbonBar2->Location = System::Drawing::Point(722, 0);
			this->ribbonBar2->Name = L"ribbonBar2";
			this->ribbonBar2->ResizeOrderIndex = 2;
			this->ribbonBar2->Size = System::Drawing::Size(183, 117);
			this->ribbonBar2->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->ribbonBar2->TabIndex = 8;
			this->ribbonBar2->Text = L"QR inf.";
			// 
			// 
			// 
			this->ribbonBar2->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonBar2->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// QRcodeLabel
			// 
			this->QRcodeLabel->BackColor = System::Drawing::Color::LightGray;
			this->QRcodeLabel->Height = 100;
			this->QRcodeLabel->Name = L"QRcodeLabel";
			this->QRcodeLabel->SingleLineColor = System::Drawing::Color::Empty;
			this->QRcodeLabel->TextLineAlignment = System::Drawing::StringAlignment::Near;
			this->QRcodeLabel->Width = 180;
			// 
			// ScalingToolsRibnBar
			// 
			this->ScalingToolsRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->ScalingToolsRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ScalingToolsRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->ScalingToolsRibnBar->ContainerControlProcessDialogKey = true;
			this->ScalingToolsRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->ScalingToolsRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->ScalingToolBtn, 
				this->ScalingToolUndoBtn});
			this->ScalingToolsRibnBar->Location = System::Drawing::Point(533, 0);
			this->ScalingToolsRibnBar->Name = L"ScalingToolsRibnBar";
			this->ScalingToolsRibnBar->ResizeOrderIndex = 2;
			this->ScalingToolsRibnBar->Size = System::Drawing::Size(189, 117);
			this->ScalingToolsRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->ScalingToolsRibnBar->TabIndex = 7;
			this->ScalingToolsRibnBar->Text = L"Scaling Editing Tools";
			// 
			// 
			// 
			this->ScalingToolsRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ScalingToolsRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// ScalingToolBtn
			// 
			this->ScalingToolBtn->AutoCheckOnClick = true;
			this->ScalingToolBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"ScalingToolBtn.Image")));
			this->ScalingToolBtn->ImageFixedSize = System::Drawing::Size(80, 80);
			this->ScalingToolBtn->Name = L"ScalingToolBtn";
			this->ScalingToolBtn->SubItemsExpandWidth = 14;
			this->ScalingToolBtn->Text = L"ScalingToolBtn";
			this->ScalingToolBtn->CheckedChanged += gcnew System::EventHandler(this, &Form1::ScalingToolBtn_CheckedChanged);
			// 
			// ScalingToolUndoBtn
			// 
			this->ScalingToolUndoBtn->Command = this->AppScalingToolUndoCmd;
			this->ScalingToolUndoBtn->CommandParameter = L"Undo";
			this->ScalingToolUndoBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"ScalingToolUndoBtn.Image")));
			this->ScalingToolUndoBtn->ImageFixedSize = System::Drawing::Size(80, 80);
			this->ScalingToolUndoBtn->Name = L"ScalingToolUndoBtn";
			this->ScalingToolUndoBtn->SubItemsExpandWidth = 14;
			this->ScalingToolUndoBtn->Text = L"ScalingToolUndoBtn";
			// 
			// AppScalingToolUndoCmd
			// 
			this->AppScalingToolUndoCmd->Name = L"AppScalingToolUndoCmd";
			this->AppScalingToolUndoCmd->Executed += gcnew System::EventHandler(this, &Form1::AppScalingToolUndoCmd_Executed);
			// 
			// ribbonBar5
			// 
			this->ribbonBar5->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->ribbonBar5->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonBar5->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->ribbonBar5->ContainerControlProcessDialogKey = true;
			this->ribbonBar5->Dock = System::Windows::Forms::DockStyle::Left;
			this->ribbonBar5->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->itemContainer32});
			this->ribbonBar5->Location = System::Drawing::Point(394, 0);
			this->ribbonBar5->Name = L"ribbonBar5";
			this->ribbonBar5->ResizeOrderIndex = 1;
			this->ribbonBar5->Size = System::Drawing::Size(139, 117);
			this->ribbonBar5->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->ribbonBar5->TabIndex = 2;
			this->ribbonBar5->Text = L"StringLineEditRibn";
			// 
			// 
			// 
			this->ribbonBar5->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonBar5->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->ribbonBar5->Visible = false;
			// 
			// itemContainer32
			// 
			// 
			// 
			// 
			this->itemContainer32->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer32->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer32->Name = L"itemContainer32";
			this->itemContainer32->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->SoftAdjust, 
				this->ScaleSlider});
			this->itemContainer32->VerticalItemAlignment = DevComponents::DotNetBar::eVerticalItemsAlignment::Middle;
			// 
			// SoftAdjust
			// 
			this->SoftAdjust->Name = L"SoftAdjust";
			this->SoftAdjust->Text = L"SoftAdjust";
			// 
			// ScaleSlider
			// 
			this->ScaleSlider->LabelWidth = 32;
			this->ScaleSlider->Maximum = 10;
			this->ScaleSlider->Name = L"ScaleSlider";
			this->ScaleSlider->Value = 4;
			this->ScaleSlider->Width = 100;
			this->ScaleSlider->ValueChanged += gcnew System::EventHandler(this, &Form1::ScaleSlider_ValueChanged);
			// 
			// ribbonBar6
			// 
			this->ribbonBar6->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->ribbonBar6->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonBar6->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->ribbonBar6->ContainerControlProcessDialogKey = true;
			this->ribbonBar6->Dock = System::Windows::Forms::DockStyle::Left;
			this->ribbonBar6->HorizontalItemAlignment = DevComponents::DotNetBar::eHorizontalItemsAlignment::Center;
			this->ribbonBar6->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->itemContainer33, this->itemContainer34});
			this->ribbonBar6->Location = System::Drawing::Point(143, 0);
			this->ribbonBar6->Name = L"ribbonBar6";
			this->ribbonBar6->ResizeOrderIndex = 1;
			this->ribbonBar6->Size = System::Drawing::Size(251, 117);
			this->ribbonBar6->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->ribbonBar6->TabIndex = 3;
			this->ribbonBar6->Text = L"TextEditRibn";
			// 
			// 
			// 
			this->ribbonBar6->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonBar6->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->ribbonBar6->Visible = false;
			// 
			// itemContainer33
			// 
			// 
			// 
			// 
			this->itemContainer33->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer33->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer33->MinimumSize = System::Drawing::Size(80, 0);
			this->itemContainer33->Name = L"itemContainer33";
			this->itemContainer33->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->TextcolorPick, 
				this->LevelBox});
			// 
			// TextcolorPick
			// 
			this->TextcolorPick->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"TextcolorPick.Image")));
			this->TextcolorPick->ImageFixedSize = System::Drawing::Size(40, 40);
			this->TextcolorPick->Name = L"TextcolorPick";
			this->TextcolorPick->Text = L"Textcolor";
			this->TextcolorPick->SelectedColorChanged += gcnew System::EventHandler(this, &Form1::TextcolorPick_SelectedColorChanged);
			// 
			// LevelBox
			// 
			this->LevelBox->ComboWidth = 30;
			this->LevelBox->DropDownHeight = 105;
			this->LevelBox->ItemHeight = 16;
			this->LevelBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) {this->comboItem9, this->comboItem10, this->comboItem11});
			this->LevelBox->Name = L"LevelBox";
			this->LevelBox->Text = L"comboBoxItem1";
			// 
			// comboItem9
			// 
			this->comboItem9->Text = L"LineLevel";
			// 
			// comboItem10
			// 
			this->comboItem10->Text = L"WordLevel";
			// 
			// comboItem11
			// 
			this->comboItem11->Text = L"CharLevel";
			// 
			// itemContainer34
			// 
			// 
			// 
			// 
			this->itemContainer34->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer34->HorizontalItemAlignment = DevComponents::DotNetBar::eHorizontalItemsAlignment::Center;
			this->itemContainer34->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer34->Name = L"itemContainer34";
			this->itemContainer34->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(3) {this->checkBoxItem1, 
				this->sliderItem1, this->sliderItem2});
			this->itemContainer34->VerticalItemAlignment = DevComponents::DotNetBar::eVerticalItemsAlignment::Middle;
			// 
			// checkBoxItem1
			// 
			this->checkBoxItem1->Name = L"checkBoxItem1";
			this->checkBoxItem1->Text = L"checkBoxItem1";
			// 
			// sliderItem1
			// 
			this->sliderItem1->Maximum = 20;
			this->sliderItem1->Name = L"sliderItem1";
			this->sliderItem1->Text = L"1";
			this->sliderItem1->Value = 10;
			this->sliderItem1->Width = 100;
			this->sliderItem1->ValueChanged += gcnew System::EventHandler(this, &Form1::sliderItem1_ValueChanged);
			// 
			// sliderItem2
			// 
			this->sliderItem2->Maximum = 255;
			this->sliderItem2->Minimum = -255;
			this->sliderItem2->Name = L"sliderItem2";
			this->sliderItem2->Step = 5;
			this->sliderItem2->Text = L"0";
			this->sliderItem2->Value = 0;
			this->sliderItem2->Width = 100;
			this->sliderItem2->ValueChanged += gcnew System::EventHandler(this, &Form1::sliderItem2_ValueChanged);
			// 
			// StringLineToolsRibnBar
			// 
			this->StringLineToolsRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->StringLineToolsRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->StringLineToolsRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->StringLineToolsRibnBar->ContainerControlProcessDialogKey = true;
			this->StringLineToolsRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->StringLineToolsRibnBar->HorizontalItemAlignment = DevComponents::DotNetBar::eHorizontalItemsAlignment::Center;
			this->StringLineToolsRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->itemContainer25});
			this->StringLineToolsRibnBar->Location = System::Drawing::Point(3, 0);
			this->StringLineToolsRibnBar->Name = L"StringLineToolsRibnBar";
			this->StringLineToolsRibnBar->Size = System::Drawing::Size(140, 117);
			this->StringLineToolsRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->StringLineToolsRibnBar->TabIndex = 1;
			this->StringLineToolsRibnBar->Text = L"String Line Editing Tools";
			// 
			// 
			// 
			this->StringLineToolsRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->StringLineToolsRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// itemContainer25
			// 
			// 
			// 
			// 
			this->itemContainer25->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer25->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer25->Name = L"itemContainer25";
			this->itemContainer25->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->itemContainer29, 
				this->itemContainer28});
			// 
			// itemContainer29
			// 
			// 
			// 
			// 
			this->itemContainer29->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer29->Name = L"itemContainer29";
			this->itemContainer29->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->StringLineEdittingToolBtn, 
				this->TextBaseBtn});
			// 
			// StringLineEdittingToolBtn
			// 
			this->StringLineEdittingToolBtn->AutoCheckOnClick = true;
			this->StringLineEdittingToolBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"StringLineEdittingToolBtn.Image")));
			this->StringLineEdittingToolBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->StringLineEdittingToolBtn->Name = L"StringLineEdittingToolBtn";
			this->StringLineEdittingToolBtn->SubItemsExpandWidth = 14;
			this->StringLineEdittingToolBtn->Text = L"StringLineEdittingToolBtn";
			this->StringLineEdittingToolBtn->Click += gcnew System::EventHandler(this, &Form1::AppStringLineEdittingToolBtnCmd);
			// 
			// TextBaseBtn
			// 
			this->TextBaseBtn->AutoCheckOnClick = true;
			this->TextBaseBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"TextBaseBtn.Image")));
			this->TextBaseBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->TextBaseBtn->Name = L"TextBaseBtn";
			this->TextBaseBtn->Text = L"TextBaseBtn";
			this->TextBaseBtn->Click += gcnew System::EventHandler(this, &Form1::TextBaseBtn_Click);
			// 
			// itemContainer28
			// 
			// 
			// 
			// 
			this->itemContainer28->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer28->Name = L"itemContainer28";
			this->itemContainer28->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->TextOrderBtn, 
				this->TextOrienBtn});
			// 
			// TextOrderBtn
			// 
			this->TextOrderBtn->AutoCheckOnClick = true;
			this->TextOrderBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"TextOrderBtn.Image")));
			this->TextOrderBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->TextOrderBtn->Name = L"TextOrderBtn";
			this->TextOrderBtn->Text = L"TextOrderBtn";
			this->TextOrderBtn->Click += gcnew System::EventHandler(this, &Form1::TextOrderBtn_Click);
			// 
			// TextOrienBtn
			// 
			this->TextOrienBtn->AutoCheckOnClick = true;
			this->TextOrienBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"TextOrienBtn.Image")));
			this->TextOrienBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->TextOrienBtn->Name = L"TextOrienBtn";
			this->TextOrienBtn->Text = L"TextOrienBtn";
			this->TextOrienBtn->Click += gcnew System::EventHandler(this, &Form1::TextOrienBtn_Click);
			// 
			// RibbonAppPanel
			// 
			this->RibbonAppPanel->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->RibbonAppPanel->Controls->Add(this->ribbonBar4);
			this->RibbonAppPanel->Controls->Add(this->RegPRibnBar);
			this->RibbonAppPanel->Controls->Add(this->ProcessRibnBar);
			this->RibbonAppPanel->Controls->Add(this->WordArtRibnBar);
			this->RibbonAppPanel->Controls->Add(this->PDBRibnBar);
			this->RibbonAppPanel->Controls->Add(this->QRRibnBar);
			this->RibbonAppPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->RibbonAppPanel->Location = System::Drawing::Point(0, 53);
			this->RibbonAppPanel->Name = L"RibbonAppPanel";
			this->RibbonAppPanel->Padding = System::Windows::Forms::Padding(3, 0, 3, 3);
			this->RibbonAppPanel->Size = System::Drawing::Size(1113, 120);
			// 
			// 
			// 
			this->RibbonAppPanel->Style->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->RibbonAppPanel->StyleMouseDown->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->RibbonAppPanel->StyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->RibbonAppPanel->TabIndex = 3;
			this->RibbonAppPanel->Visible = false;
			// 
			// ribbonBar4
			// 
			this->ribbonBar4->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->ribbonBar4->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonBar4->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->ribbonBar4->ContainerControlProcessDialogKey = true;
			this->ribbonBar4->Dock = System::Windows::Forms::DockStyle::Left;
			this->ribbonBar4->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->itemContainer31});
			this->ribbonBar4->Location = System::Drawing::Point(914, 0);
			this->ribbonBar4->Name = L"ribbonBar4";
			this->ribbonBar4->Size = System::Drawing::Size(114, 117);
			this->ribbonBar4->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->ribbonBar4->TabIndex = 30;
			this->ribbonBar4->Text = L"ribbonBar4";
			// 
			// 
			// 
			this->ribbonBar4->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonBar4->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// itemContainer31
			// 
			// 
			// 
			// 
			this->itemContainer31->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer31->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer31->Name = L"itemContainer31";
			this->itemContainer31->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(3) {this->SeeLevelCheck1, 
				this->SeeLevelCheck2, this->SeeLevelCheck3});
			this->itemContainer31->VerticalItemAlignment = DevComponents::DotNetBar::eVerticalItemsAlignment::Middle;
			// 
			// SeeLevelCheck1
			// 
			this->SeeLevelCheck1->Name = L"SeeLevelCheck1";
			this->SeeLevelCheck1->Text = L"QRcode";
			this->SeeLevelCheck1->Click += gcnew System::EventHandler(this, &Form1::SeeLevelCheck_Check);
			// 
			// SeeLevelCheck2
			// 
			this->SeeLevelCheck2->Name = L"SeeLevelCheck2";
			this->SeeLevelCheck2->Text = L"WordArt";
			this->SeeLevelCheck2->Click += gcnew System::EventHandler(this, &Form1::SeeLevelCheck_Check);
			// 
			// SeeLevelCheck3
			// 
			this->SeeLevelCheck3->Name = L"SeeLevelCheck3";
			this->SeeLevelCheck3->Text = L"Energy";
			this->SeeLevelCheck3->Click += gcnew System::EventHandler(this, &Form1::SeeLevelCheck_Check);
			// 
			// RegPRibnBar
			// 
			this->RegPRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->RegPRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->RegPRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->RegPRibnBar->ContainerControlProcessDialogKey = true;
			this->RegPRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->RegPRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->itemContainer26, this->itemContainer27});
			this->RegPRibnBar->Location = System::Drawing::Point(755, 0);
			this->RegPRibnBar->Name = L"RegPRibnBar";
			this->RegPRibnBar->Size = System::Drawing::Size(159, 117);
			this->RegPRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->RegPRibnBar->TabIndex = 29;
			// 
			// 
			// 
			this->RegPRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->RegPRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// itemContainer26
			// 
			// 
			// 
			// 
			this->itemContainer26->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer26->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer26->Name = L"itemContainer26";
			this->itemContainer26->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(5) {this->smallregioncheckbox, 
				this->BoundaryAlabel, this->BoundaryA, this->BoundaryBlabel, this->BoundaryB});
			// 
			// smallregioncheckbox
			// 
			this->smallregioncheckbox->Name = L"smallregioncheckbox";
			this->smallregioncheckbox->Text = L"smallregion";
			this->smallregioncheckbox->CheckedChanged += gcnew DevComponents::DotNetBar::CheckBoxChangeEventHandler(this, &Form1::RegionSmallRegionCheck);
			// 
			// BoundaryAlabel
			// 
			this->BoundaryAlabel->Name = L"BoundaryAlabel";
			this->BoundaryAlabel->Text = L"Ba";
			// 
			// BoundaryA
			// 
			this->BoundaryA->Name = L"BoundaryA";
			this->BoundaryA->WatermarkColor = System::Drawing::SystemColors::GrayText;
			this->BoundaryA->TextChanged += gcnew System::EventHandler(this, &Form1::RegionParamChanged);
			// 
			// BoundaryBlabel
			// 
			this->BoundaryBlabel->Name = L"BoundaryBlabel";
			this->BoundaryBlabel->Text = L"Bb";
			// 
			// BoundaryB
			// 
			this->BoundaryB->Name = L"BoundaryB";
			this->BoundaryB->WatermarkColor = System::Drawing::SystemColors::GrayText;
			this->BoundaryB->TextChanged += gcnew System::EventHandler(this, &Form1::RegionParamChanged);
			// 
			// itemContainer27
			// 
			// 
			// 
			// 
			this->itemContainer27->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer27->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer27->Name = L"itemContainer27";
			this->itemContainer27->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(6) {this->RangeSizelabel, 
				this->Rangesize, this->LineAlabel, this->LineA, this->LineBlabel, this->LineB});
			// 
			// RangeSizelabel
			// 
			this->RangeSizelabel->Name = L"RangeSizelabel";
			this->RangeSizelabel->Text = L"RangeSize";
			// 
			// Rangesize
			// 
			this->Rangesize->Name = L"Rangesize";
			this->Rangesize->WatermarkColor = System::Drawing::SystemColors::GrayText;
			this->Rangesize->TextChanged += gcnew System::EventHandler(this, &Form1::RegionParamChanged);
			// 
			// LineAlabel
			// 
			this->LineAlabel->Name = L"LineAlabel";
			this->LineAlabel->Text = L"La";
			// 
			// LineA
			// 
			this->LineA->Name = L"LineA";
			this->LineA->WatermarkColor = System::Drawing::SystemColors::GrayText;
			this->LineA->TextChanged += gcnew System::EventHandler(this, &Form1::RegionParamChanged);
			// 
			// LineBlabel
			// 
			this->LineBlabel->Name = L"LineBlabel";
			this->LineBlabel->Text = L"Lb";
			// 
			// LineB
			// 
			this->LineB->Name = L"LineB";
			this->LineB->WatermarkColor = System::Drawing::SystemColors::GrayText;
			this->LineB->TextChanged += gcnew System::EventHandler(this, &Form1::RegionParamChanged);
			// 
			// ProcessRibnBar
			// 
			this->ProcessRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->ProcessRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ProcessRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->ProcessRibnBar->ContainerControlProcessDialogKey = true;
			this->ProcessRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->ProcessRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(3) {this->ProcessAllBtn, this->WarpCheckBox, 
				this->ScalingBtn});
			this->ProcessRibnBar->Location = System::Drawing::Point(535, 0);
			this->ProcessRibnBar->Name = L"ProcessRibnBar";
			this->ProcessRibnBar->Size = System::Drawing::Size(220, 117);
			this->ProcessRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->ProcessRibnBar->TabIndex = 3;
			this->ProcessRibnBar->Text = L"Process";
			// 
			// 
			// 
			this->ProcessRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ProcessRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// ProcessAllBtn
			// 
			this->ProcessAllBtn->Command = this->AppProcessCmd;
			this->ProcessAllBtn->CommandParameter = L"PROCESSALL";
			this->ProcessAllBtn->FixedSize = System::Drawing::Size(80, 80);
			this->ProcessAllBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"ProcessAllBtn.Image")));
			this->ProcessAllBtn->ImageFixedSize = System::Drawing::Size(80, 80);
			this->ProcessAllBtn->Name = L"ProcessAllBtn";
			this->ProcessAllBtn->SubItemsExpandWidth = 14;
			this->ProcessAllBtn->Text = L"Process All";
			this->ProcessAllBtn->Tooltip = L"Process all algorithm steps";
			// 
			// AppProcessCmd
			// 
			this->AppProcessCmd->Name = L"AppProcessCmd";
			this->AppProcessCmd->Executed += gcnew System::EventHandler(this, &Form1::AppProcessCmd_Executed);
			// 
			// WarpCheckBox
			// 
			this->WarpCheckBox->Name = L"WarpCheckBox";
			this->WarpCheckBox->Text = L"Warp";
			// 
			// ScalingBtn
			// 
			this->ScalingBtn->Command = this->AppBuildBigScaleCmd;
			this->ScalingBtn->CommandParameter = L"SCALING";
			this->ScalingBtn->FixedSize = System::Drawing::Size(80, 80);
			this->ScalingBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"ScalingBtn.Image")));
			this->ScalingBtn->ImageFixedSize = System::Drawing::Size(80, 80);
			this->ScalingBtn->Name = L"ScalingBtn";
			this->ScalingBtn->SubItemsExpandWidth = 14;
			this->ScalingBtn->Text = L"BuildBigScale";
			this->ScalingBtn->Tooltip = L"Generate scaling candidates steps";
			this->ScalingBtn->Visible = false;
			// 
			// AppBuildBigScaleCmd
			// 
			this->AppBuildBigScaleCmd->Name = L"AppBuildBigScaleCmd";
			this->AppBuildBigScaleCmd->Executed += gcnew System::EventHandler(this, &Form1::AppBuildBigScaleCmd_Executed);
			// 
			// WordArtRibnBar
			// 
			this->WordArtRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->WordArtRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->WordArtRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->WordArtRibnBar->ContainerControlProcessDialogKey = true;
			this->WordArtRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->WordArtRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->itemContainer23});
			this->WordArtRibnBar->Location = System::Drawing::Point(376, 0);
			this->WordArtRibnBar->Name = L"WordArtRibnBar";
			this->WordArtRibnBar->Size = System::Drawing::Size(159, 117);
			this->WordArtRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->WordArtRibnBar->TabIndex = 6;
			this->WordArtRibnBar->Text = L"Word Art Strings";
			// 
			// 
			// 
			this->WordArtRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->WordArtRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// itemContainer23
			// 
			// 
			// 
			// 
			this->itemContainer23->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer23->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer23->MinimumSize = System::Drawing::Size(150, 30);
			this->itemContainer23->Name = L"itemContainer23";
			this->itemContainer23->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->StringData});
			// 
			// StringData
			// 
			this->StringData->BackColor = System::Drawing::Color::LightGray;
			this->StringData->Height = 100;
			this->StringData->Name = L"StringData";
			this->StringData->SingleLineColor = System::Drawing::Color::Empty;
			this->StringData->TextLineAlignment = System::Drawing::StringAlignment::Near;
			this->StringData->Width = 100;
			// 
			// PDBRibnBar
			// 
			this->PDBRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->PDBRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->PDBRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->PDBRibnBar->ContainerControlProcessDialogKey = true;
			this->PDBRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->PDBRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(4) {this->itemContainer18, this->PDBFileCombo, 
				this->itemContainer24, this->WordArtText2});
			this->PDBRibnBar->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->PDBRibnBar->Location = System::Drawing::Point(207, 0);
			this->PDBRibnBar->Name = L"PDBRibnBar";
			this->PDBRibnBar->Size = System::Drawing::Size(169, 117);
			this->PDBRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->PDBRibnBar->TabIndex = 4;
			this->PDBRibnBar->Text = L"Database";
			// 
			// 
			// 
			this->PDBRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->PDBRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// itemContainer18
			// 
			// 
			// 
			// 
			this->itemContainer18->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer18->Name = L"itemContainer18";
			this->itemContainer18->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->PDBSizeLabel});
			// 
			// PDBSizeLabel
			// 
			this->PDBSizeLabel->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->PDBSizeLabel->Name = L"PDBSizeLabel";
			this->PDBSizeLabel->Text = L"Module Size:";
			// 
			// PDBFileCombo
			// 
			this->PDBFileCombo->AlwaysShowCaption = true;
			this->PDBFileCombo->Caption = L"Database: ";
			this->PDBFileCombo->ComboWidth = 100;
			this->PDBFileCombo->Command = this->AppQRCCmd;
			this->PDBFileCombo->CommandParameter = L"ModuleSize";
			this->PDBFileCombo->DropDownHeight = 106;
			this->PDBFileCombo->DropDownWidth = 256;
			this->PDBFileCombo->ItemHeight = 17;
			this->PDBFileCombo->Items->AddRange(gcnew cli::array< System::Object^  >(5) {this->comboItem3, this->comboItem5, this->comboItem6, 
				this->comboItem7, this->comboItem8});
			this->PDBFileCombo->Name = L"PDBFileCombo";
			// 
			// AppQRCCmd
			// 
			this->AppQRCCmd->Name = L"AppQRCCmd";
			this->AppQRCCmd->Executed += gcnew System::EventHandler(this, &Form1::AppQRCCmd_Executed);
			// 
			// comboItem3
			// 
			this->comboItem3->Text = L"3X3_default";
			// 
			// comboItem5
			// 
			this->comboItem5->Text = L"5X5_default";
			// 
			// comboItem6
			// 
			this->comboItem6->Text = L"9X9_default";
			// 
			// comboItem7
			// 
			this->comboItem7->Text = L"11X11_default";
			// 
			// comboItem8
			// 
			this->comboItem8->Text = L"13X13_default";
			// 
			// itemContainer24
			// 
			// 
			// 
			// 
			this->itemContainer24->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer24->Name = L"itemContainer24";
			this->itemContainer24->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->WordArtStringLabel2});
			// 
			// WordArtStringLabel2
			// 
			this->WordArtStringLabel2->Font = (gcnew System::Drawing::Font(L"微軟正黑體", 12));
			this->WordArtStringLabel2->Name = L"WordArtStringLabel2";
			this->WordArtStringLabel2->Text = L"Strings:";
			// 
			// WordArtText2
			// 
			this->WordArtText2->Name = L"WordArtText2";
			this->WordArtText2->WatermarkColor = System::Drawing::SystemColors::GrayText;
			this->WordArtText2->TextChanged += gcnew System::EventHandler(this, &Form1::WordArtText_TextChanged);
			// 
			// QRRibnBar
			// 
			this->QRRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->QRRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->QRRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->QRRibnBar->ContainerControlProcessDialogKey = true;
			this->QRRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->QRRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->itemContainer15});
			this->QRRibnBar->Location = System::Drawing::Point(3, 0);
			this->QRRibnBar->Name = L"QRRibnBar";
			this->QRRibnBar->Size = System::Drawing::Size(204, 117);
			this->QRRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->QRRibnBar->TabIndex = 2;
			this->QRRibnBar->Text = L"QR Code Generator";
			// 
			// 
			// 
			this->QRRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->QRRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// itemContainer15
			// 
			// 
			// 
			// 
			this->itemContainer15->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer15->ItemSpacing = 5;
			this->itemContainer15->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer15->MultiLine = true;
			this->itemContainer15->Name = L"itemContainer15";
			this->itemContainer15->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->itemContainer16, 
				this->QRCText});
			// 
			// itemContainer16
			// 
			// 
			// 
			// 
			this->itemContainer16->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer16->Name = L"itemContainer16";
			this->itemContainer16->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->itemContainer17, 
				this->QRCGenBtn});
			// 
			// itemContainer17
			// 
			// 
			// 
			// 
			this->itemContainer17->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer17->HorizontalItemAlignment = DevComponents::DotNetBar::eHorizontalItemsAlignment::Right;
			this->itemContainer17->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer17->Name = L"itemContainer17";
			this->itemContainer17->ResizeItemsToFit = false;
			this->itemContainer17->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->QRCVerCombo, 
				this->QRCECLCombo});
			// 
			// QRCVerCombo
			// 
			this->QRCVerCombo->AlwaysShowCaption = true;
			this->QRCVerCombo->Caption = L"Version:";
			this->QRCVerCombo->Command = this->AppQRCCmd;
			this->QRCVerCombo->CommandParameter = L"VERSION";
			this->QRCVerCombo->DropDownHeight = 106;
			this->QRCVerCombo->ItemHeight = 17;
			this->QRCVerCombo->Items->AddRange(gcnew cli::array< System::Object^  >(20) {this->QRCVer1, this->QRCVer2, this->QRCVer3, 
				this->QRCVer4, this->QRCVer5, this->QRCVer6, this->QRCVer7, this->QRCVer8, this->QRCVer9, this->QRCVer10, this->QRCVer11, this->QRCVer12, 
				this->QRCVer13, this->QRCVer14, this->QRCVer15, this->QRCVer16, this->QRCVer17, this->QRCVer18, this->QRCVer19, this->QRCVer20});
			this->QRCVerCombo->Name = L"QRCVerCombo";
			this->QRCVerCombo->Text = L"QR Code Version";
			// 
			// QRCVer1
			// 
			this->QRCVer1->Text = L"1";
			// 
			// QRCVer2
			// 
			this->QRCVer2->Text = L"2";
			// 
			// QRCVer3
			// 
			this->QRCVer3->Text = L"3";
			// 
			// QRCVer4
			// 
			this->QRCVer4->Text = L"4";
			// 
			// QRCVer5
			// 
			this->QRCVer5->Text = L"5";
			// 
			// QRCVer6
			// 
			this->QRCVer6->Text = L"6";
			// 
			// QRCVer7
			// 
			this->QRCVer7->Text = L"7";
			// 
			// QRCVer8
			// 
			this->QRCVer8->Text = L"8";
			// 
			// QRCVer9
			// 
			this->QRCVer9->Text = L"9";
			// 
			// QRCVer10
			// 
			this->QRCVer10->Text = L"10";
			// 
			// QRCVer11
			// 
			this->QRCVer11->Text = L"11";
			// 
			// QRCVer12
			// 
			this->QRCVer12->Text = L"12";
			// 
			// QRCVer13
			// 
			this->QRCVer13->Text = L"13";
			// 
			// QRCVer14
			// 
			this->QRCVer14->Text = L"14";
			// 
			// QRCVer15
			// 
			this->QRCVer15->Text = L"15";
			// 
			// QRCVer16
			// 
			this->QRCVer16->Text = L"16";
			// 
			// QRCVer17
			// 
			this->QRCVer17->Text = L"17";
			// 
			// QRCVer18
			// 
			this->QRCVer18->Text = L"18";
			// 
			// QRCVer19
			// 
			this->QRCVer19->Text = L"19";
			// 
			// QRCVer20
			// 
			this->QRCVer20->Text = L"20";
			// 
			// QRCECLCombo
			// 
			this->QRCECLCombo->AlwaysShowCaption = true;
			this->QRCECLCombo->Caption = L"EC Level:";
			this->QRCECLCombo->Command = this->AppQRCCmd;
			this->QRCECLCombo->CommandParameter = L"ECL";
			this->QRCECLCombo->DropDownHeight = 106;
			this->QRCECLCombo->ItemHeight = 17;
			this->QRCECLCombo->Items->AddRange(gcnew cli::array< System::Object^  >(4) {this->QRCECLL, this->QRCECLM, this->QRCECLQ, 
				this->QRCECLH});
			this->QRCECLCombo->Name = L"QRCECLCombo";
			this->QRCECLCombo->Text = L"QR Code Error Correction Level";
			// 
			// QRCECLL
			// 
			this->QRCECLL->Text = L"L";
			// 
			// QRCECLM
			// 
			this->QRCECLM->Text = L"M";
			// 
			// QRCECLQ
			// 
			this->QRCECLQ->Text = L"Q";
			// 
			// QRCECLH
			// 
			this->QRCECLH->Text = L"H";
			// 
			// QRCGenBtn
			// 
			this->QRCGenBtn->Command = this->AppQRCCmd;
			this->QRCGenBtn->CommandParameter = L"GENERATE";
			this->QRCGenBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"QRCGenBtn.Image")));
			this->QRCGenBtn->ImageFixedSize = System::Drawing::Size(60, 60);
			this->QRCGenBtn->Name = L"QRCGenBtn";
			this->QRCGenBtn->SubItemsExpandWidth = 14;
			this->QRCGenBtn->Text = L"QR Code";
			this->QRCGenBtn->Tooltip = L"Generate QR code";
			// 
			// QRCText
			// 
			this->QRCText->Command = this->AppQRCCmd;
			this->QRCText->CommandParameter = L"TEXT";
			this->QRCText->Name = L"QRCText";
			this->QRCText->TextBoxWidth = 180;
			this->QRCText->WatermarkColor = System::Drawing::SystemColors::GrayText;
			this->QRCText->TextChanged += gcnew System::EventHandler(this, &Form1::QRCText_TextChanged);
			// 
			// ErrorCorrectionPanel
			// 
			this->ErrorCorrectionPanel->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->ErrorCorrectionPanel->Controls->Add(this->TestRibnBar);
			this->ErrorCorrectionPanel->Controls->Add(this->QRRecRibnBar);
			this->ErrorCorrectionPanel->Controls->Add(this->ErrorCorrectionRibnBar);
			this->ErrorCorrectionPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ErrorCorrectionPanel->Location = System::Drawing::Point(0, 53);
			this->ErrorCorrectionPanel->Name = L"ErrorCorrectionPanel";
			this->ErrorCorrectionPanel->Padding = System::Windows::Forms::Padding(3, 0, 3, 3);
			this->ErrorCorrectionPanel->Size = System::Drawing::Size(1113, 120);
			// 
			// 
			// 
			this->ErrorCorrectionPanel->Style->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ErrorCorrectionPanel->StyleMouseDown->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ErrorCorrectionPanel->StyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->ErrorCorrectionPanel->TabIndex = 4;
			// 
			// TestRibnBar
			// 
			this->TestRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->TestRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->TestRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->TestRibnBar->ContainerControlProcessDialogKey = true;
			this->TestRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->TestRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->AppTestBtn, this->itemContainer19});
			this->TestRibnBar->Location = System::Drawing::Point(437, 0);
			this->TestRibnBar->Name = L"TestRibnBar";
			this->TestRibnBar->Size = System::Drawing::Size(124, 117);
			this->TestRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->TestRibnBar->TabIndex = 19;
			this->TestRibnBar->Text = L"Debug Zone";
			// 
			// 
			// 
			this->TestRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->TestRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// AppTestBtn
			// 
			this->AppTestBtn->Command = this->AppTestCmd;
			this->AppTestBtn->CommandParameter = L"TEST";
			this->AppTestBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"AppTestBtn.Image")));
			this->AppTestBtn->ImageFixedSize = System::Drawing::Size(60, 60);
			this->AppTestBtn->Name = L"AppTestBtn";
			this->AppTestBtn->SubItemsExpandWidth = 14;
			this->AppTestBtn->Text = L"buttonItem3";
			// 
			// AppTestCmd
			// 
			this->AppTestCmd->Name = L"AppTestCmd";
			this->AppTestCmd->Executed += gcnew System::EventHandler(this, &Form1::AppTestCmd_Executed);
			// 
			// itemContainer19
			// 
			// 
			// 
			// 
			this->itemContainer19->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer19->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer19->Name = L"itemContainer19";
			this->itemContainer19->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->AppDebugBtn, 
				this->AppDumpBtn});
			// 
			// AppDebugBtn
			// 
			this->AppDebugBtn->AutoCheckOnClick = true;
			this->AppDebugBtn->Command = this->AppTestCmd;
			this->AppDebugBtn->CommandParameter = L"DEBUG";
			this->AppDebugBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"AppDebugBtn.Image")));
			this->AppDebugBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->AppDebugBtn->Name = L"AppDebugBtn";
			this->AppDebugBtn->Text = L"Show Debug";
			this->AppDebugBtn->Tooltip = L"Show debugging information";
			// 
			// AppDumpBtn
			// 
			this->AppDumpBtn->Command = this->AppTestCmd;
			this->AppDumpBtn->CommandParameter = L"DUMP";
			this->AppDumpBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"AppDumpBtn.Image")));
			this->AppDumpBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->AppDumpBtn->Name = L"AppDumpBtn";
			this->AppDumpBtn->Text = L"Dump Debug";
			this->AppDumpBtn->Tooltip = L"Dump debugging information to files";
			// 
			// QRRecRibnBar
			// 
			this->QRRecRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->QRRecRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->QRRecRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->QRRecRibnBar->ContainerControlProcessDialogKey = true;
			this->QRRecRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->QRRecRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->itemContainer22, this->QRRecBtn});
			this->QRRecRibnBar->Location = System::Drawing::Point(201, 0);
			this->QRRecRibnBar->Name = L"QRRecRibnBar";
			this->QRRecRibnBar->Size = System::Drawing::Size(236, 117);
			this->QRRecRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->QRRecRibnBar->TabIndex = 18;
			this->QRRecRibnBar->Text = L"QRCode Recovering";
			// 
			// 
			// 
			this->QRRecRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->QRRecRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->QRRecRibnBar->VerticalItemAlignment = DevComponents::DotNetBar::eVerticalItemsAlignment::Middle;
			// 
			// itemContainer22
			// 
			// 
			// 
			// 
			this->itemContainer22->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer22->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer22->Name = L"itemContainer22";
			this->itemContainer22->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->QRReclabel, 
				this->QRRecTextBox});
			this->itemContainer22->VerticalItemAlignment = DevComponents::DotNetBar::eVerticalItemsAlignment::Middle;
			// 
			// QRReclabel
			// 
			this->QRReclabel->Font = (gcnew System::Drawing::Font(L"新細明體", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(136)));
			this->QRReclabel->Name = L"QRReclabel";
			this->QRReclabel->Text = L"Confidence:";
			// 
			// QRRecTextBox
			// 
			this->QRRecTextBox->Name = L"QRRecTextBox";
			this->QRRecTextBox->TextBoxWidth = 128;
			this->QRRecTextBox->WatermarkColor = System::Drawing::SystemColors::GrayText;
			// 
			// QRRecBtn
			// 
			this->QRRecBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"QRRecBtn.Image")));
			this->QRRecBtn->ImageFixedSize = System::Drawing::Size(80, 80);
			this->QRRecBtn->Name = L"QRRecBtn";
			this->QRRecBtn->SubItemsExpandWidth = 14;
			this->QRRecBtn->Text = L"QRRecBtn";
			// 
			// ErrorCorrectionRibnBar
			// 
			this->ErrorCorrectionRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->ErrorCorrectionRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ErrorCorrectionRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->ErrorCorrectionRibnBar->ContainerControlProcessDialogKey = true;
			this->ErrorCorrectionRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->ErrorCorrectionRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->ErrorCorrectionBtn, 
				this->itemContainer36});
			this->ErrorCorrectionRibnBar->Location = System::Drawing::Point(3, 0);
			this->ErrorCorrectionRibnBar->Name = L"ErrorCorrectionRibnBar";
			this->ErrorCorrectionRibnBar->Size = System::Drawing::Size(198, 117);
			this->ErrorCorrectionRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->ErrorCorrectionRibnBar->TabIndex = 3;
			this->ErrorCorrectionRibnBar->Text = L"Error Correction";
			// 
			// 
			// 
			this->ErrorCorrectionRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ErrorCorrectionRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// ErrorCorrectionBtn
			// 
			this->ErrorCorrectionBtn->Command = this->AppErrorCorrectCmd;
			this->ErrorCorrectionBtn->CommandParameter = L"PROCESSALL";
			this->ErrorCorrectionBtn->FixedSize = System::Drawing::Size(80, 80);
			this->ErrorCorrectionBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"ErrorCorrectionBtn.Image")));
			this->ErrorCorrectionBtn->ImageFixedSize = System::Drawing::Size(80, 80);
			this->ErrorCorrectionBtn->Name = L"ErrorCorrectionBtn";
			this->ErrorCorrectionBtn->SubItemsExpandWidth = 14;
			this->ErrorCorrectionBtn->Text = L"Process All";
			this->ErrorCorrectionBtn->Tooltip = L"Process all algorithm steps";
			// 
			// AppErrorCorrectCmd
			// 
			this->AppErrorCorrectCmd->Name = L"AppErrorCorrectCmd";
			this->AppErrorCorrectCmd->Executed += gcnew System::EventHandler(this, &Form1::AppErrorCorrectCmd_Executed);
			// 
			// itemContainer36
			// 
			// 
			// 
			// 
			this->itemContainer36->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer36->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer36->Name = L"itemContainer36";
			this->itemContainer36->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(4) {this->RSModCheckBox, 
				this->CurveWarpCheckBox, this->CharWarpCheckBox, this->IslandModuleCheckBox});
			// 
			// RSModCheckBox
			// 
			this->RSModCheckBox->Checked = true;
			this->RSModCheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->RSModCheckBox->Name = L"RSModCheckBox";
			this->RSModCheckBox->Text = L"RS Modification";
			this->RSModCheckBox->CheckedChanged += gcnew DevComponents::DotNetBar::CheckBoxChangeEventHandler(this, &Form1::RSModCheckBox_CheckedChanged);
			// 
			// CurveWarpCheckBox
			// 
			this->CurveWarpCheckBox->Name = L"CurveWarpCheckBox";
			this->CurveWarpCheckBox->Text = L"Curve Warping";
			this->CurveWarpCheckBox->CheckedChanged += gcnew DevComponents::DotNetBar::CheckBoxChangeEventHandler(this, &Form1::CurveWarpCheckBox_CheckedChanged);
			// 
			// CharWarpCheckBox
			// 
			this->CharWarpCheckBox->Checked = true;
			this->CharWarpCheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->CharWarpCheckBox->Name = L"CharWarpCheckBox";
			this->CharWarpCheckBox->Text = L"Char Warping";
			this->CharWarpCheckBox->CheckedChanged += gcnew DevComponents::DotNetBar::CheckBoxChangeEventHandler(this, &Form1::CharWarpCheckBox_CheckedChanged);
			// 
			// IslandModuleCheckBox
			// 
			this->IslandModuleCheckBox->Checked = true;
			this->IslandModuleCheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->IslandModuleCheckBox->Name = L"IslandModuleCheckBox";
			this->IslandModuleCheckBox->Text = L"Island Modules";
			this->IslandModuleCheckBox->CheckedChanged += gcnew DevComponents::DotNetBar::CheckBoxChangeEventHandler(this, &Form1::IslandModuleCheckBox_CheckedChanged);
			// 
			// RibbonToolPanel
			// 
			this->RibbonToolPanel->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->RibbonToolPanel->Controls->Add(this->MPlayerRibnBar);
			this->RibbonToolPanel->Controls->Add(this->RibbonThemeBar);
			this->RibbonToolPanel->Controls->Add(this->DsgnRibnBar);
			this->RibbonToolPanel->Controls->Add(this->PaintRibnBar);
			this->RibbonToolPanel->Controls->Add(this->GrabCutRibnBar);
			this->RibbonToolPanel->Controls->Add(this->FilterRibnBar);
			this->RibbonToolPanel->Controls->Add(this->XFormRibnBar);
			this->RibbonToolPanel->Dock = System::Windows::Forms::DockStyle::Fill;
			this->RibbonToolPanel->Location = System::Drawing::Point(0, 53);
			this->RibbonToolPanel->Name = L"RibbonToolPanel";
			this->RibbonToolPanel->Padding = System::Windows::Forms::Padding(3, 0, 3, 3);
			this->RibbonToolPanel->Size = System::Drawing::Size(1113, 120);
			// 
			// 
			// 
			this->RibbonToolPanel->Style->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->RibbonToolPanel->StyleMouseDown->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->RibbonToolPanel->StyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->RibbonToolPanel->TabIndex = 1;
			this->RibbonToolPanel->Visible = false;
			// 
			// MPlayerRibnBar
			// 
			this->MPlayerRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->MPlayerRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->MPlayerRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->MPlayerRibnBar->ContainerControlProcessDialogKey = true;
			this->MPlayerRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->MPlayerRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->PlayerItemCntr, 
				this->itemContainer5});
			this->MPlayerRibnBar->Location = System::Drawing::Point(749, 0);
			this->MPlayerRibnBar->Name = L"MPlayerRibnBar";
			this->MPlayerRibnBar->ResizeItemsToFit = false;
			this->MPlayerRibnBar->Size = System::Drawing::Size(302, 117);
			this->MPlayerRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->MPlayerRibnBar->TabIndex = 1;
			this->MPlayerRibnBar->Text = L"Media Player";
			// 
			// 
			// 
			this->MPlayerRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->MPlayerRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->MPlayerRibnBar->Visible = false;
			// 
			// PlayerItemCntr
			// 
			// 
			// 
			// 
			this->PlayerItemCntr->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->PlayerItemCntr->ItemSpacing = 3;
			this->PlayerItemCntr->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->PlayerItemCntr->Name = L"PlayerItemCntr";
			this->PlayerItemCntr->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(3) {this->PlayerBtnCntr, 
				this->PlayerFrameSlider, this->PlayerSpeedSlider});
			// 
			// PlayerBtnCntr
			// 
			// 
			// 
			// 
			this->PlayerBtnCntr->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->PlayerBtnCntr->Name = L"PlayerBtnCntr";
			this->PlayerBtnCntr->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(5) {this->PlayerStartBtn, 
				this->PlayerRewindBtn, this->PlayerPlayBtn, this->PlayerForwardBtn, this->PlayerEndBtn});
			// 
			// PlayerStartBtn
			// 
			this->PlayerStartBtn->Command = this->AppPlayerCmd;
			this->PlayerStartBtn->CommandParameter = L"START";
			this->PlayerStartBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"PlayerStartBtn.Image")));
			this->PlayerStartBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->PlayerStartBtn->Name = L"PlayerStartBtn";
			this->PlayerStartBtn->Text = L"buttonItem2";
			// 
			// AppPlayerCmd
			// 
			this->AppPlayerCmd->Name = L"AppPlayerCmd";
			this->AppPlayerCmd->Executed += gcnew System::EventHandler(this, &Form1::AppPlayerCmd_Executed);
			// 
			// PlayerRewindBtn
			// 
			this->PlayerRewindBtn->Command = this->AppPlayerCmd;
			this->PlayerRewindBtn->CommandParameter = L"RWD";
			this->PlayerRewindBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"PlayerRewindBtn.Image")));
			this->PlayerRewindBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->PlayerRewindBtn->Name = L"PlayerRewindBtn";
			this->PlayerRewindBtn->Text = L"buttonItem3";
			// 
			// PlayerPlayBtn
			// 
			this->PlayerPlayBtn->Command = this->AppPlayerCmd;
			this->PlayerPlayBtn->CommandParameter = L"PLAY";
			this->PlayerPlayBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"PlayerPlayBtn.Image")));
			this->PlayerPlayBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->PlayerPlayBtn->Name = L"PlayerPlayBtn";
			this->PlayerPlayBtn->Text = L"buttonItem4";
			// 
			// PlayerForwardBtn
			// 
			this->PlayerForwardBtn->Command = this->AppPlayerCmd;
			this->PlayerForwardBtn->CommandParameter = L"FWD";
			this->PlayerForwardBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"PlayerForwardBtn.Image")));
			this->PlayerForwardBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->PlayerForwardBtn->Name = L"PlayerForwardBtn";
			this->PlayerForwardBtn->Text = L"buttonItem5";
			// 
			// PlayerEndBtn
			// 
			this->PlayerEndBtn->Command = this->AppPlayerCmd;
			this->PlayerEndBtn->CommandParameter = L"END";
			this->PlayerEndBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"PlayerEndBtn.Image")));
			this->PlayerEndBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->PlayerEndBtn->Name = L"PlayerEndBtn";
			this->PlayerEndBtn->Text = L"buttonItem6";
			// 
			// PlayerFrameSlider
			// 
			this->PlayerFrameSlider->Name = L"PlayerFrameSlider";
			this->PlayerFrameSlider->Text = L"<b><font color=\"Black\">Frame</font></b>";
			this->PlayerFrameSlider->Value = 0;
			this->PlayerFrameSlider->ValueChanged += gcnew System::EventHandler(this, &Form1::PlayerFrameSlider_ValueChanged);
			// 
			// PlayerSpeedSlider
			// 
			this->PlayerSpeedSlider->Name = L"PlayerSpeedSlider";
			this->PlayerSpeedSlider->Text = L"<b><font color=\"Black\">Speed</font></b>";
			this->PlayerSpeedSlider->Value = 0;
			this->PlayerSpeedSlider->ValueChanged += gcnew System::EventHandler(this, &Form1::PlayerSpeedSlider_ValueChanged);
			// 
			// itemContainer5
			// 
			// 
			// 
			// 
			this->itemContainer5->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer5->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer5->Name = L"itemContainer5";
			this->itemContainer5->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->PlayerReptBtn, 
				this->PlayerSyncBtn});
			// 
			// PlayerReptBtn
			// 
			this->PlayerReptBtn->AutoCheckOnClick = true;
			this->PlayerReptBtn->Checked = true;
			this->PlayerReptBtn->Command = this->AppPlayerCmd;
			this->PlayerReptBtn->CommandParameter = L"REPEAT";
			this->PlayerReptBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"PlayerReptBtn.Image")));
			this->PlayerReptBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->PlayerReptBtn->Name = L"PlayerReptBtn";
			this->PlayerReptBtn->Text = L"Repeat";
			this->PlayerReptBtn->Tooltip = L"Play the video in repeat mode";
			// 
			// PlayerSyncBtn
			// 
			this->PlayerSyncBtn->AutoCheckOnClick = true;
			this->PlayerSyncBtn->Command = this->AppPlayerCmd;
			this->PlayerSyncBtn->CommandParameter = L"SYNC";
			this->PlayerSyncBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"PlayerSyncBtn.Image")));
			this->PlayerSyncBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->PlayerSyncBtn->Name = L"PlayerSyncBtn";
			this->PlayerSyncBtn->Text = L"Synchronization";
			this->PlayerSyncBtn->Tooltip = L"Synchronize the video";
			// 
			// RibbonThemeBar
			// 
			this->RibbonThemeBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->RibbonThemeBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->RibbonThemeBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->RibbonThemeBar->ContainerControlProcessDialogKey = true;
			this->RibbonThemeBar->DialogLauncherVisible = true;
			this->RibbonThemeBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->RibbonThemeBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->FormThemeBtn});
			this->RibbonThemeBar->Location = System::Drawing::Point(677, 0);
			this->RibbonThemeBar->Name = L"RibbonThemeBar";
			this->RibbonThemeBar->Size = System::Drawing::Size(72, 117);
			this->RibbonThemeBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->RibbonThemeBar->TabIndex = 6;
			this->RibbonThemeBar->Text = L"Theme";
			// 
			// 
			// 
			this->RibbonThemeBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->RibbonThemeBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// FormThemeBtn
			// 
			this->FormThemeBtn->Command = this->FormThemeCmd;
			this->FormThemeBtn->CommandParameter = L"Metro";
			this->FormThemeBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"FormThemeBtn.Image")));
			this->FormThemeBtn->ImageFixedSize = System::Drawing::Size(50, 50);
			this->FormThemeBtn->ImagePosition = DevComponents::DotNetBar::eImagePosition::Bottom;
			this->FormThemeBtn->Name = L"FormThemeBtn";
			this->FormThemeBtn->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->FormThemePicker, 
				this->FormColorPicker});
			this->FormThemeBtn->SubItemsExpandWidth = 14;
			// 
			// FormThemeCmd
			// 
			this->FormThemeCmd->Name = L"FormThemeCmd";
			this->FormThemeCmd->Executed += gcnew System::EventHandler(this, &Form1::FormThemeCmd_Executed);
			// 
			// FormThemePicker
			// 
			this->FormThemePicker->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"FormThemePicker.Image")));
			this->FormThemePicker->ImageFixedSize = System::Drawing::Size(40, 40);
			this->FormThemePicker->Name = L"FormThemePicker";
			this->FormThemePicker->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(10) {this->FormTheme1Btn, 
				this->FormTheme2Btn, this->FormTheme3Btn, this->FormTheme4Btn, this->FormTheme5Btn, this->FormTheme6Btn, this->FormTheme7Btn, 
				this->FormTheme10Btn, this->FormTheme9Btn, this->FormTheme8Btn});
			this->FormThemePicker->Text = L"Theme Picker";
			// 
			// FormTheme1Btn
			// 
			this->FormTheme1Btn->Command = this->FormThemeCmd;
			this->FormTheme1Btn->CommandParameter = L"Office2007Blue";
			this->FormTheme1Btn->Name = L"FormTheme1Btn";
			this->FormTheme1Btn->Text = L"Office2007Blue";
			// 
			// FormTheme2Btn
			// 
			this->FormTheme2Btn->Command = this->FormThemeCmd;
			this->FormTheme2Btn->CommandParameter = L"Office2007Silver";
			this->FormTheme2Btn->Name = L"FormTheme2Btn";
			this->FormTheme2Btn->Text = L"Office2007Silver";
			// 
			// FormTheme3Btn
			// 
			this->FormTheme3Btn->Command = this->FormThemeCmd;
			this->FormTheme3Btn->CommandParameter = L"Office2007Black";
			this->FormTheme3Btn->Name = L"FormTheme3Btn";
			this->FormTheme3Btn->Text = L"Office2007Black";
			// 
			// FormTheme4Btn
			// 
			this->FormTheme4Btn->Command = this->FormThemeCmd;
			this->FormTheme4Btn->CommandParameter = L"Office2007VistaGlass";
			this->FormTheme4Btn->Name = L"FormTheme4Btn";
			this->FormTheme4Btn->Text = L"Office2007VistaGlass";
			// 
			// FormTheme5Btn
			// 
			this->FormTheme5Btn->Command = this->FormThemeCmd;
			this->FormTheme5Btn->CommandParameter = L"Office2010Silver";
			this->FormTheme5Btn->Name = L"FormTheme5Btn";
			this->FormTheme5Btn->Text = L"Office2010Silver";
			// 
			// FormTheme6Btn
			// 
			this->FormTheme6Btn->Command = this->FormThemeCmd;
			this->FormTheme6Btn->CommandParameter = L"Office2010Blue";
			this->FormTheme6Btn->Name = L"FormTheme6Btn";
			this->FormTheme6Btn->Text = L"Office2010Blue";
			// 
			// FormTheme7Btn
			// 
			this->FormTheme7Btn->Command = this->FormThemeCmd;
			this->FormTheme7Btn->CommandParameter = L"Office2010Black";
			this->FormTheme7Btn->Name = L"FormTheme7Btn";
			this->FormTheme7Btn->Text = L"Office2010Black";
			// 
			// FormTheme10Btn
			// 
			this->FormTheme10Btn->Command = this->FormThemeCmd;
			this->FormTheme10Btn->CommandParameter = L"Windows7Blue";
			this->FormTheme10Btn->Name = L"FormTheme10Btn";
			this->FormTheme10Btn->Text = L"Windows7Blue";
			// 
			// FormTheme9Btn
			// 
			this->FormTheme9Btn->Command = this->FormThemeCmd;
			this->FormTheme9Btn->CommandParameter = L"VisualStudio2010Blue";
			this->FormTheme9Btn->Name = L"FormTheme9Btn";
			this->FormTheme9Btn->Text = L"VisualStudio2010Blue";
			// 
			// FormTheme8Btn
			// 
			this->FormTheme8Btn->Command = this->FormThemeCmd;
			this->FormTheme8Btn->CommandParameter = L"Metro";
			this->FormTheme8Btn->Name = L"FormTheme8Btn";
			this->FormTheme8Btn->Text = L"Metro";
			// 
			// FormColorPicker
			// 
			this->FormColorPicker->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"FormColorPicker.Image")));
			this->FormColorPicker->ImageFixedSize = System::Drawing::Size(40, 40);
			this->FormColorPicker->Name = L"FormColorPicker";
			this->FormColorPicker->Text = L"Color Picker";
			this->FormColorPicker->SelectedColorChanged += gcnew System::EventHandler(this, &Form1::FormThemeColorPicker_SelectedColorChanged);
			this->FormColorPicker->ColorPreview += gcnew DevComponents::DotNetBar::ColorPreviewEventHandler(this, &Form1::FormThemeColorPicker_ColorPreview);
			this->FormColorPicker->EnabledChanged += gcnew System::EventHandler(this, &Form1::FormThemeColorPicker_ExpandChange);
			// 
			// DsgnRibnBar
			// 
			this->DsgnRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->DsgnRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->DsgnRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->DsgnRibnBar->ContainerControlProcessDialogKey = true;
			this->DsgnRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->DsgnRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->DesignVertCntr});
			this->DsgnRibnBar->Location = System::Drawing::Point(562, 0);
			this->DsgnRibnBar->Name = L"DsgnRibnBar";
			this->DsgnRibnBar->ResizeItemsToFit = false;
			this->DsgnRibnBar->Size = System::Drawing::Size(115, 117);
			this->DsgnRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->DsgnRibnBar->TabIndex = 2;
			this->DsgnRibnBar->Text = L"Design";
			// 
			// 
			// 
			this->DsgnRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->DsgnRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// DesignVertCntr
			// 
			// 
			// 
			// 
			this->DesignVertCntr->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->DesignVertCntr->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->DesignVertCntr->Name = L"DesignVertCntr";
			this->DesignVertCntr->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->DesignHorzCntr1, 
				this->DesignHorzCntr2});
			// 
			// DesignHorzCntr1
			// 
			// 
			// 
			// 
			this->DesignHorzCntr1->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->DesignHorzCntr1->Name = L"DesignHorzCntr1";
			this->DesignHorzCntr1->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->AppCenterBtn, 
				this->AppPinBtn});
			// 
			// AppCenterBtn
			// 
			this->AppCenterBtn->Command = this->AppDesignCmd;
			this->AppCenterBtn->CommandParameter = L"CENTER";
			this->AppCenterBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"AppCenterBtn.Image")));
			this->AppCenterBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->AppCenterBtn->Name = L"AppCenterBtn";
			this->AppCenterBtn->SubItemsExpandWidth = 14;
			this->AppCenterBtn->Text = L"Center Media";
			this->AppCenterBtn->Tooltip = L"Centerize the media";
			// 
			// AppDesignCmd
			// 
			this->AppDesignCmd->Name = L"AppDesignCmd";
			this->AppDesignCmd->Executed += gcnew System::EventHandler(this, &Form1::AppDesignCmd_Executed);
			// 
			// AppPinBtn
			// 
			this->AppPinBtn->AutoCheckOnClick = true;
			this->AppPinBtn->Command = this->AppDesignCmd;
			this->AppPinBtn->CommandParameter = L"PING";
			this->AppPinBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"AppPinBtn.Image")));
			this->AppPinBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->AppPinBtn->Name = L"AppPinBtn";
			this->AppPinBtn->Text = L"buttonItem3";
			// 
			// DesignHorzCntr2
			// 
			// 
			// 
			// 
			this->DesignHorzCntr2->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->DesignHorzCntr2->Name = L"DesignHorzCntr2";
			this->DesignHorzCntr2->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->AppSyncBtn});
			// 
			// AppSyncBtn
			// 
			this->AppSyncBtn->AutoCheckOnClick = true;
			this->AppSyncBtn->Command = this->AppDesignCmd;
			this->AppSyncBtn->CommandParameter = L"SYNC";
			this->AppSyncBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"AppSyncBtn.Image")));
			this->AppSyncBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->AppSyncBtn->Name = L"AppSyncBtn";
			this->AppSyncBtn->Text = L"Sync GLPanel";
			this->AppSyncBtn->Tooltip = L"Synchronize GLPanels";
			// 
			// PaintRibnBar
			// 
			this->PaintRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->PaintRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->PaintRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->PaintRibnBar->ContainerControlProcessDialogKey = true;
			this->PaintRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->PaintRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->itemContainer6});
			this->PaintRibnBar->Location = System::Drawing::Point(443, 0);
			this->PaintRibnBar->Name = L"PaintRibnBar";
			this->PaintRibnBar->Size = System::Drawing::Size(119, 117);
			this->PaintRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->PaintRibnBar->TabIndex = 4;
			this->PaintRibnBar->Text = L"Painter";
			// 
			// 
			// 
			this->PaintRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->PaintRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// itemContainer6
			// 
			// 
			// 
			// 
			this->itemContainer6->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer6->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer6->Name = L"itemContainer6";
			this->itemContainer6->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->itemContainer7, 
				this->itemContainer8});
			// 
			// itemContainer7
			// 
			// 
			// 
			// 
			this->itemContainer7->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer7->Name = L"itemContainer7";
			this->itemContainer7->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->AppPaintBtn, 
				this->PntrBrshBtn});
			// 
			// AppPaintBtn
			// 
			this->AppPaintBtn->AutoCheckOnClick = true;
			this->AppPaintBtn->Command = this->AppPaintCmd;
			this->AppPaintBtn->CommandParameter = L"PAINTER";
			this->AppPaintBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"AppPaintBtn.Image")));
			this->AppPaintBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->AppPaintBtn->Name = L"AppPaintBtn";
			this->AppPaintBtn->Text = L"Paint";
			this->AppPaintBtn->Tooltip = L"Enter painting mode";
			// 
			// PntrBrshBtn
			// 
			this->PntrBrshBtn->Command = this->AppPaintCmd;
			this->PntrBrshBtn->CommandParameter = L"STROKE_BRUSH";
			this->PntrBrshBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"PntrBrshBtn.Image")));
			this->PntrBrshBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->PntrBrshBtn->Name = L"PntrBrshBtn";
			this->PntrBrshBtn->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->PntrBrushColor});
			this->PntrBrshBtn->Text = L"Brush stroke";
			this->PntrBrshBtn->Tooltip = L"Painting using brush stroke";
			// 
			// PntrBrushColor
			// 
			this->PntrBrushColor->FontBold = true;
			this->PntrBrushColor->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"PntrBrushColor.Icon")));
			this->PntrBrushColor->Name = L"PntrBrushColor";
			this->PntrBrushColor->Text = L"Brush Color";
			this->PntrBrushColor->SelectedColorChanged += gcnew System::EventHandler(this, &Form1::PntrBrushColor_SelectedColorChanged);
			// 
			// itemContainer8
			// 
			// 
			// 
			// 
			this->itemContainer8->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer8->Name = L"itemContainer8";
			this->itemContainer8->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->PntrCleanBtn, 
				this->PntrErasBtn});
			// 
			// PntrCleanBtn
			// 
			this->PntrCleanBtn->Command = this->AppPaintCmd;
			this->PntrCleanBtn->CommandParameter = L"CLEAN";
			this->PntrCleanBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"PntrCleanBtn.Image")));
			this->PntrCleanBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->PntrCleanBtn->Name = L"PntrCleanBtn";
			this->PntrCleanBtn->Text = L"Clean";
			this->PntrCleanBtn->Tooltip = L"Clean the canvas";
			// 
			// PntrErasBtn
			// 
			this->PntrErasBtn->Command = this->AppPaintCmd;
			this->PntrErasBtn->CommandParameter = L"STROKE_ERASE";
			this->PntrErasBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"PntrErasBtn.Image")));
			this->PntrErasBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->PntrErasBtn->Name = L"PntrErasBtn";
			this->PntrErasBtn->Text = L"Erase stroke";
			this->PntrErasBtn->Tooltip = L"Painting using erase stroke";
			// 
			// GrabCutRibnBar
			// 
			this->GrabCutRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->GrabCutRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->GrabCutRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->GrabCutRibnBar->ContainerControlProcessDialogKey = true;
			this->GrabCutRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->GrabCutRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->itemContainer9});
			this->GrabCutRibnBar->Location = System::Drawing::Point(273, 0);
			this->GrabCutRibnBar->Name = L"GrabCutRibnBar";
			this->GrabCutRibnBar->Size = System::Drawing::Size(170, 117);
			this->GrabCutRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->GrabCutRibnBar->TabIndex = 5;
			this->GrabCutRibnBar->Text = L"GrabCut";
			// 
			// 
			// 
			this->GrabCutRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->GrabCutRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// itemContainer9
			// 
			// 
			// 
			// 
			this->itemContainer9->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer9->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer9->Name = L"itemContainer9";
			this->itemContainer9->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->itemContainer10, 
				this->itemContainer11});
			// 
			// itemContainer10
			// 
			// 
			// 
			// 
			this->itemContainer10->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer10->Name = L"itemContainer10";
			this->itemContainer10->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(3) {this->AppGCBtn, this->GCErasBtn, 
				this->GCBrshBtn});
			// 
			// AppGCBtn
			// 
			this->AppGCBtn->AutoCheckOnClick = true;
			this->AppGCBtn->Command = this->AppGrabCutCmd;
			this->AppGCBtn->CommandParameter = L"GRABCUT";
			this->AppGCBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"AppGCBtn.Image")));
			this->AppGCBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->AppGCBtn->Name = L"AppGCBtn";
			this->AppGCBtn->Text = L"Grab Cut";
			this->AppGCBtn->Tooltip = L"Enter GrabCut mode";
			// 
			// GCErasBtn
			// 
			this->GCErasBtn->Command = this->AppGrabCutCmd;
			this->GCErasBtn->CommandParameter = L"STROKE_ERASE";
			this->GCErasBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"GCErasBtn.Image")));
			this->GCErasBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->GCErasBtn->Name = L"GCErasBtn";
			this->GCErasBtn->Tag = L"GrabCut Stroke";
			this->GCErasBtn->Text = L"Erase Stroke";
			this->GCErasBtn->Tooltip = L"Painting using erase stroke";
			// 
			// GCBrshBtn
			// 
			this->GCBrshBtn->Command = this->AppGrabCutCmd;
			this->GCBrshBtn->CommandParameter = L"STROKE_BRUSH";
			this->GCBrshBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"GCBrshBtn.Image")));
			this->GCBrshBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->GCBrshBtn->Name = L"GCBrshBtn";
			this->GCBrshBtn->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(6) {this->GCFGDBtn, this->GCBGDBtn, 
				this->GCPRFGDBtn, this->GCPRBGDBtn, this->GCMskBBtn, this->GCMskWBtn});
			this->GCBrshBtn->Tag = L"GrabCut Stroke";
			this->GCBrshBtn->Text = L"GrabCut Stroke";
			this->GCBrshBtn->Tooltip = L"GrabCut Stroke";
			// 
			// GCFGDBtn
			// 
			this->GCFGDBtn->Command = this->AppGrabCutCmd;
			this->GCFGDBtn->CommandParameter = L"STROKE_FGD";
			this->GCFGDBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"GCFGDBtn.Image")));
			this->GCFGDBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->GCFGDBtn->Name = L"GCFGDBtn";
			this->GCFGDBtn->Tag = L"GrabCut Stroke";
			this->GCFGDBtn->Text = L"Foreground Stroke";
			this->GCFGDBtn->Tooltip = L"Painting using foreground stroke";
			// 
			// GCBGDBtn
			// 
			this->GCBGDBtn->Command = this->AppGrabCutCmd;
			this->GCBGDBtn->CommandParameter = L"STROKE_BGD";
			this->GCBGDBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"GCBGDBtn.Image")));
			this->GCBGDBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->GCBGDBtn->Name = L"GCBGDBtn";
			this->GCBGDBtn->Tag = L"GrabCut Stroke";
			this->GCBGDBtn->Text = L"Background Stroke";
			this->GCBGDBtn->Tooltip = L"Painting using background stroke";
			// 
			// GCPRFGDBtn
			// 
			this->GCPRFGDBtn->Command = this->AppGrabCutCmd;
			this->GCPRFGDBtn->CommandParameter = L"STROKE_PRFGD";
			this->GCPRFGDBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"GCPRFGDBtn.Image")));
			this->GCPRFGDBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->GCPRFGDBtn->Name = L"GCPRFGDBtn";
			this->GCPRFGDBtn->Tag = L"GrabCut Stroke";
			this->GCPRFGDBtn->Text = L"Possible Foreground Stroke";
			this->GCPRFGDBtn->Tooltip = L"Painting using possible foreground stroke";
			// 
			// GCPRBGDBtn
			// 
			this->GCPRBGDBtn->Command = this->AppGrabCutCmd;
			this->GCPRBGDBtn->CommandParameter = L"STROKE_PRBGD";
			this->GCPRBGDBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"GCPRBGDBtn.Image")));
			this->GCPRBGDBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->GCPRBGDBtn->Name = L"GCPRBGDBtn";
			this->GCPRBGDBtn->Tag = L"GrabCut Stroke";
			this->GCPRBGDBtn->Text = L"Possible Background Stroke";
			this->GCPRBGDBtn->Tooltip = L"Painting using possible background stroke";
			// 
			// GCMskBBtn
			// 
			this->GCMskBBtn->Command = this->AppGrabCutCmd;
			this->GCMskBBtn->CommandParameter = L"STROKE_MSKB";
			this->GCMskBBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"GCMskBBtn.Image")));
			this->GCMskBBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->GCMskBBtn->Name = L"GCMskBBtn";
			this->GCMskBBtn->Tag = L"GrabCut Stroke";
			this->GCMskBBtn->Text = L"Background Mask Stroke";
			this->GCMskBBtn->Tooltip = L"Painting using background mask stroke";
			// 
			// GCMskWBtn
			// 
			this->GCMskWBtn->Command = this->AppGrabCutCmd;
			this->GCMskWBtn->CommandParameter = L"STROKE_MSKW";
			this->GCMskWBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"GCMskWBtn.Image")));
			this->GCMskWBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->GCMskWBtn->Name = L"GCMskWBtn";
			this->GCMskWBtn->Tag = L"GrabCut Stroke";
			this->GCMskWBtn->Text = L"Foreground Mask Stroke";
			this->GCMskWBtn->Tooltip = L"Painting using foreground mask stroke";
			// 
			// itemContainer11
			// 
			// 
			// 
			// 
			this->itemContainer11->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer11->Name = L"itemContainer11";
			this->itemContainer11->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(3) {this->GCCutBtn, this->GCAddBtn, 
				this->GCResetBtn});
			// 
			// GCCutBtn
			// 
			this->GCCutBtn->Command = this->AppGrabCutCmd;
			this->GCCutBtn->CommandParameter = L"CUT";
			this->GCCutBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"GCCutBtn.Image")));
			this->GCCutBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->GCCutBtn->Name = L"GCCutBtn";
			this->GCCutBtn->Text = L"GC Cut";
			this->GCCutBtn->Tooltip = L"Perform GrabCut";
			// 
			// GCAddBtn
			// 
			this->GCAddBtn->Command = this->AppGrabCutCmd;
			this->GCAddBtn->CommandParameter = L"ADD";
			this->GCAddBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"GCAddBtn.Image")));
			this->GCAddBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->GCAddBtn->Name = L"GCAddBtn";
			this->GCAddBtn->Text = L"GC Add";
			this->GCAddBtn->Tooltip = L"Add cutted region";
			// 
			// GCResetBtn
			// 
			this->GCResetBtn->Command = this->AppGrabCutCmd;
			this->GCResetBtn->CommandParameter = L"RESET";
			this->GCResetBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"GCResetBtn.Image")));
			this->GCResetBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->GCResetBtn->Name = L"GCResetBtn";
			this->GCResetBtn->Text = L"GC Reset";
			this->GCResetBtn->Tooltip = L"Reset GrabCut";
			// 
			// FilterRibnBar
			// 
			this->FilterRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->FilterRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->FilterRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->FilterRibnBar->ContainerControlProcessDialogKey = true;
			this->FilterRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->FilterRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->itemContainer20, 
				this->itemContainer21});
			this->FilterRibnBar->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->FilterRibnBar->Location = System::Drawing::Point(155, 0);
			this->FilterRibnBar->Name = L"FilterRibnBar";
			this->FilterRibnBar->Size = System::Drawing::Size(118, 117);
			this->FilterRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->FilterRibnBar->TabIndex = 8;
			this->FilterRibnBar->Text = L"Filter";
			// 
			// 
			// 
			this->FilterRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->FilterRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// itemContainer20
			// 
			// 
			// 
			// 
			this->itemContainer20->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer20->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer20->Name = L"itemContainer20";
			this->itemContainer20->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->FltrContrastBtn});
			// 
			// FltrContrastBtn
			// 
			this->FltrContrastBtn->AutoCheckOnClick = true;
			this->FltrContrastBtn->Command = this->AppFilterCmd;
			this->FltrContrastBtn->CommandParameter = L"CONTRAST";
			this->FltrContrastBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"FltrContrastBtn.Image")));
			this->FltrContrastBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->FltrContrastBtn->Name = L"FltrContrastBtn";
			this->FltrContrastBtn->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->FltrContrastSlider});
			this->FltrContrastBtn->Text = L"Image Contrast";
			this->FltrContrastBtn->Tooltip = L"Image Contrast";
			// 
			// AppFilterCmd
			// 
			this->AppFilterCmd->Name = L"AppFilterCmd";
			this->AppFilterCmd->Executed += gcnew System::EventHandler(this, &Form1::AppFilterCmd_Executed);
			// 
			// FltrContrastSlider
			// 
			this->FltrContrastSlider->Command = this->AppFilterCmd;
			this->FltrContrastSlider->CommandParameter = L"CONTRAST_VAL";
			this->FltrContrastSlider->LabelWidth = 50;
			this->FltrContrastSlider->Name = L"FltrContrastSlider";
			this->FltrContrastSlider->Value = 50;
			// 
			// itemContainer21
			// 
			// 
			// 
			// 
			this->itemContainer21->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer21->Name = L"itemContainer21";
			this->itemContainer21->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->FltrSharpenBtn, 
				this->FltrFlowAbsBtn});
			// 
			// FltrSharpenBtn
			// 
			this->FltrSharpenBtn->AutoCheckOnClick = true;
			this->FltrSharpenBtn->Command = this->AppFilterCmd;
			this->FltrSharpenBtn->CommandParameter = L"UNSHARPMASK";
			this->FltrSharpenBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"FltrSharpenBtn.Image")));
			this->FltrSharpenBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->FltrSharpenBtn->Name = L"FltrSharpenBtn";
			this->FltrSharpenBtn->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(3) {this->FltrUSMASlider, 
				this->FltrUSMRSlider, this->FltrUSMTSlider});
			this->FltrSharpenBtn->Text = L"Image Sharpening";
			this->FltrSharpenBtn->Tooltip = L"UnSharp Mask";
			// 
			// FltrUSMASlider
			// 
			this->FltrUSMASlider->Command = this->AppFilterCmd;
			this->FltrUSMASlider->CommandParameter = L"USM_AMOUNT";
			this->FltrUSMASlider->LabelWidth = 50;
			this->FltrUSMASlider->Maximum = 200;
			this->FltrUSMASlider->Name = L"FltrUSMASlider";
			this->FltrUSMASlider->Tooltip = L"UnSharp Mask Amount";
			this->FltrUSMASlider->Value = 50;
			// 
			// FltrUSMRSlider
			// 
			this->FltrUSMRSlider->Command = this->AppFilterCmd;
			this->FltrUSMRSlider->CommandParameter = L"USM_RADIUS";
			this->FltrUSMRSlider->LabelWidth = 50;
			this->FltrUSMRSlider->Maximum = 200;
			this->FltrUSMRSlider->Name = L"FltrUSMRSlider";
			this->FltrUSMRSlider->Tooltip = L"UnSharp Mask Radius";
			this->FltrUSMRSlider->Value = 0;
			// 
			// FltrUSMTSlider
			// 
			this->FltrUSMTSlider->Command = this->AppFilterCmd;
			this->FltrUSMTSlider->CommandParameter = L"USM_THRESH";
			this->FltrUSMTSlider->LabelWidth = 50;
			this->FltrUSMTSlider->Maximum = 255;
			this->FltrUSMTSlider->Name = L"FltrUSMTSlider";
			this->FltrUSMTSlider->Tooltip = L"UnSharp Mask Thresh";
			this->FltrUSMTSlider->Value = 0;
			// 
			// FltrFlowAbsBtn
			// 
			this->FltrFlowAbsBtn->AutoCheckOnClick = true;
			this->FltrFlowAbsBtn->Command = this->AppFilterCmd;
			this->FltrFlowAbsBtn->CommandParameter = L"FLOWABS";
			this->FltrFlowAbsBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"FltrFlowAbsBtn.Image")));
			this->FltrFlowAbsBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->FltrFlowAbsBtn->Name = L"FltrFlowAbsBtn";
			this->FltrFlowAbsBtn->Text = L"Image Abstraction";
			this->FltrFlowAbsBtn->Tooltip = L"Flow-based Abstraction";
			// 
			// XFormRibnBar
			// 
			this->XFormRibnBar->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->XFormRibnBar->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->XFormRibnBar->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->XFormRibnBar->ContainerControlProcessDialogKey = true;
			this->XFormRibnBar->Dock = System::Windows::Forms::DockStyle::Left;
			this->XFormRibnBar->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->itemContainer12});
			this->XFormRibnBar->Location = System::Drawing::Point(3, 0);
			this->XFormRibnBar->Name = L"XFormRibnBar";
			this->XFormRibnBar->Size = System::Drawing::Size(152, 117);
			this->XFormRibnBar->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->XFormRibnBar->TabIndex = 7;
			this->XFormRibnBar->Text = L"XForm";
			// 
			// 
			// 
			this->XFormRibnBar->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->XFormRibnBar->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// itemContainer12
			// 
			// 
			// 
			// 
			this->itemContainer12->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer12->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer12->Name = L"itemContainer12";
			this->itemContainer12->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->itemContainer13, 
				this->itemContainer14});
			// 
			// itemContainer13
			// 
			// 
			// 
			// 
			this->itemContainer13->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer13->Name = L"itemContainer13";
			this->itemContainer13->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(3) {this->XFormCropBtn, 
				this->XFormMirBtn, this->XFormUndoBtn});
			// 
			// XFormCropBtn
			// 
			this->XFormCropBtn->Command = this->AppXFormCmd;
			this->XFormCropBtn->CommandParameter = L"CROP";
			this->XFormCropBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"XFormCropBtn.Image")));
			this->XFormCropBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->XFormCropBtn->Name = L"XFormCropBtn";
			this->XFormCropBtn->Text = L"Figure Mode";
			this->XFormCropBtn->Tooltip = L"Apply the transformation";
			// 
			// AppXFormCmd
			// 
			this->AppXFormCmd->Name = L"AppXFormCmd";
			this->AppXFormCmd->Executed += gcnew System::EventHandler(this, &Form1::AppXFormCmd_Executed);
			// 
			// XFormMirBtn
			// 
			this->XFormMirBtn->AutoCheckOnClick = true;
			this->XFormMirBtn->Command = this->AppXFormCmd;
			this->XFormMirBtn->CommandParameter = L"MIRROR";
			this->XFormMirBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"XFormMirBtn.Image")));
			this->XFormMirBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->XFormMirBtn->Name = L"XFormMirBtn";
			this->XFormMirBtn->Text = L"Mirror Mode";
			this->XFormMirBtn->Tooltip = L"Mirror mode";
			// 
			// XFormUndoBtn
			// 
			this->XFormUndoBtn->Command = this->AppXFormCmd;
			this->XFormUndoBtn->CommandParameter = L"UNDO";
			this->XFormUndoBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"XFormUndoBtn.Image")));
			this->XFormUndoBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->XFormUndoBtn->Name = L"XFormUndoBtn";
			this->XFormUndoBtn->Text = L"Undo Mode";
			this->XFormUndoBtn->Tooltip = L"Undo mode";
			// 
			// itemContainer14
			// 
			// 
			// 
			// 
			this->itemContainer14->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer14->Name = L"itemContainer14";
			this->itemContainer14->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(3) {this->XFormMovBtn, 
				this->XFormRotBtn, this->XFormScalBtn});
			// 
			// XFormMovBtn
			// 
			this->XFormMovBtn->Command = this->AppXFormCmd;
			this->XFormMovBtn->CommandParameter = L"MOVE";
			this->XFormMovBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"XFormMovBtn.Image")));
			this->XFormMovBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->XFormMovBtn->Name = L"XFormMovBtn";
			this->XFormMovBtn->Text = L"Move Mode";
			this->XFormMovBtn->Tooltip = L"Translation mode";
			// 
			// XFormRotBtn
			// 
			this->XFormRotBtn->Command = this->AppXFormCmd;
			this->XFormRotBtn->CommandParameter = L"ROTATE";
			this->XFormRotBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"XFormRotBtn.Image")));
			this->XFormRotBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->XFormRotBtn->Name = L"XFormRotBtn";
			this->XFormRotBtn->Text = L"Rotate Mode";
			this->XFormRotBtn->Tooltip = L"Rotation mode";
			// 
			// XFormScalBtn
			// 
			this->XFormScalBtn->Command = this->AppXFormCmd;
			this->XFormScalBtn->CommandParameter = L"SCALE";
			this->XFormScalBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"XFormScalBtn.Image")));
			this->XFormScalBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->XFormScalBtn->Name = L"XFormScalBtn";
			this->XFormScalBtn->Text = L"Scale Mode";
			this->XFormScalBtn->Tooltip = L"Scale mode";
			// 
			// ribbonPanel1
			// 
			this->ribbonPanel1->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->ribbonPanel1->Controls->Add(this->ribbonBar1);
			this->ribbonPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->ribbonPanel1->Location = System::Drawing::Point(0, 53);
			this->ribbonPanel1->Name = L"ribbonPanel1";
			this->ribbonPanel1->Padding = System::Windows::Forms::Padding(3, 0, 3, 3);
			this->ribbonPanel1->Size = System::Drawing::Size(1113, 120);
			// 
			// 
			// 
			this->ribbonPanel1->Style->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonPanel1->StyleMouseDown->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonPanel1->StyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->ribbonPanel1->TabIndex = 4;
			this->ribbonPanel1->Visible = false;
			// 
			// ribbonBar1
			// 
			this->ribbonBar1->AutoOverflowEnabled = true;
			// 
			// 
			// 
			this->ribbonBar1->BackgroundMouseOverStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonBar1->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->ribbonBar1->ContainerControlProcessDialogKey = true;
			this->ribbonBar1->Dock = System::Windows::Forms::DockStyle::Left;
			this->ribbonBar1->Items->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->CameraImgGDBtn});
			this->ribbonBar1->Location = System::Drawing::Point(3, 0);
			this->ribbonBar1->Name = L"ribbonBar1";
			this->ribbonBar1->Size = System::Drawing::Size(264, 117);
			this->ribbonBar1->Style = DevComponents::DotNetBar::eDotNetBarStyle::StyleManagerControlled;
			this->ribbonBar1->TabIndex = 0;
			this->ribbonBar1->Text = L"camera image";
			// 
			// 
			// 
			this->ribbonBar1->TitleStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// 
			// 
			this->ribbonBar1->TitleStyleMouseOver->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			// 
			// CameraImgGDBtn
			// 
			this->CameraImgGDBtn->Command = this->AppTestCmd;
			this->CameraImgGDBtn->CommandParameter = L"GENERATE";
			this->CameraImgGDBtn->ImageFixedSize = System::Drawing::Size(60, 60);
			this->CameraImgGDBtn->Name = L"CameraImgGDBtn";
			this->CameraImgGDBtn->SubItemsExpandWidth = 14;
			this->CameraImgGDBtn->Text = L"grid sampling";
			this->CameraImgGDBtn->Tooltip = L"Generate camera img grid sample";
			// 
			// office2007StartButton1
			// 
			this->office2007StartButton1->AutoExpandOnClick = true;
			this->office2007StartButton1->CanCustomize = false;
			this->office2007StartButton1->HotTrackingStyle = DevComponents::DotNetBar::eHotTrackingStyle::Image;
			this->office2007StartButton1->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"office2007StartButton1.Icon")));
			this->office2007StartButton1->ImageFixedSize = System::Drawing::Size(16, 16);
			this->office2007StartButton1->ImagePaddingHorizontal = 0;
			this->office2007StartButton1->ImagePaddingVertical = 0;
			this->office2007StartButton1->Name = L"office2007StartButton1";
			this->office2007StartButton1->ShowSubItems = false;
			this->office2007StartButton1->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->itemContainer1});
			this->office2007StartButton1->Text = L"&File";
			// 
			// itemContainer1
			// 
			// 
			// 
			// 
			this->itemContainer1->BackgroundStyle->Class = L"RibbonFileMenuContainer";
			this->itemContainer1->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer1->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer1->Name = L"itemContainer1";
			this->itemContainer1->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->itemContainer2, 
				this->itemContainer4});
			// 
			// itemContainer2
			// 
			// 
			// 
			// 
			this->itemContainer2->BackgroundStyle->Class = L"RibbonFileMenuTwoColumnContainer";
			this->itemContainer2->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer2->ItemSpacing = 0;
			this->itemContainer2->Name = L"itemContainer2";
			this->itemContainer2->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->itemContainer3});
			// 
			// itemContainer3
			// 
			// 
			// 
			// 
			this->itemContainer3->BackgroundStyle->Class = L"RibbonFileMenuColumnOneContainer";
			this->itemContainer3->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer3->LayoutOrientation = DevComponents::DotNetBar::eOrientation::Vertical;
			this->itemContainer3->MinimumSize = System::Drawing::Size(120, 0);
			this->itemContainer3->Name = L"itemContainer3";
			this->itemContainer3->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->AppOpnBtn, this->AppSavBtn});
			// 
			// AppOpnBtn
			// 
			this->AppOpnBtn->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::ImageAndText;
			this->AppOpnBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"AppOpnBtn.Image")));
			this->AppOpnBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->AppOpnBtn->Name = L"AppOpnBtn";
			this->AppOpnBtn->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(7) {this->OpnConfigBtn, this->OpnMedaBtn, 
				this->OpnSegBtn, this->OpnGapBtn, this->OpnSegFlowBtn, this->OpnLineDataBtn, this->OpnArticleBtn});
			this->AppOpnBtn->SubItemsExpandWidth = 24;
			this->AppOpnBtn->Text = L"&Open...";
			// 
			// OpnConfigBtn
			// 
			this->OpnConfigBtn->Command = this->AppOpnCmd;
			this->OpnConfigBtn->CommandParameter = L"CONFIG";
			this->OpnConfigBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"OpnConfigBtn.Icon")));
			this->OpnConfigBtn->Name = L"OpnConfigBtn";
			this->OpnConfigBtn->Text = L"Config File";
			this->OpnConfigBtn->Tooltip = L"Open configuration file";
			// 
			// AppOpnCmd
			// 
			this->AppOpnCmd->Name = L"AppOpnCmd";
			this->AppOpnCmd->Executed += gcnew System::EventHandler(this, &Form1::AppOpnCmd_Executed);
			// 
			// OpnMedaBtn
			// 
			this->OpnMedaBtn->Command = this->AppOpnCmd;
			this->OpnMedaBtn->CommandParameter = L"MEDIA";
			this->OpnMedaBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"OpnMedaBtn.Icon")));
			this->OpnMedaBtn->Name = L"OpnMedaBtn";
			this->OpnMedaBtn->Text = L"Media File";
			this->OpnMedaBtn->Tooltip = L"Open media file";
			// 
			// OpnSegBtn
			// 
			this->OpnSegBtn->Command = this->AppOpnCmd;
			this->OpnSegBtn->CommandParameter = L"SEGMENT";
			this->OpnSegBtn->Name = L"OpnSegBtn";
			this->OpnSegBtn->Text = L"Segment File";
			this->OpnSegBtn->Tooltip = L"Open segment file";
			// 
			// OpnGapBtn
			// 
			this->OpnGapBtn->Command = this->AppOpnCmd;
			this->OpnGapBtn->CommandParameter = L"GAP";
			this->OpnGapBtn->Name = L"OpnGapBtn";
			this->OpnGapBtn->Text = L"Gap File";
			// 
			// OpnSegFlowBtn
			// 
			this->OpnSegFlowBtn->Command = this->AppOpnCmd;
			this->OpnSegFlowBtn->CommandParameter = L"FLOW";
			this->OpnSegFlowBtn->Name = L"OpnSegFlowBtn";
			this->OpnSegFlowBtn->Text = L"Flow File";
			this->OpnSegFlowBtn->Tooltip = L"Open flow file";
			// 
			// OpnLineDataBtn
			// 
			this->OpnLineDataBtn->Command = this->AppOpnCmd;
			this->OpnLineDataBtn->CommandParameter = L"Word Art";
			this->OpnLineDataBtn->Name = L"OpnLineDataBtn";
			this->OpnLineDataBtn->Text = L"Word Art";
			this->OpnLineDataBtn->Tooltip = L"Open Word Art";
			// 
			// OpnArticleBtn
			// 
			this->OpnArticleBtn->Command = this->AppOpnCmd;
			this->OpnArticleBtn->CommandParameter = L"STRING";
			this->OpnArticleBtn->Name = L"OpnArticleBtn";
			this->OpnArticleBtn->Text = L"String File";
			this->OpnArticleBtn->Tooltip = L"Open String File";
			// 
			// AppSavBtn
			// 
			this->AppSavBtn->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::ImageAndText;
			this->AppSavBtn->CommandParameter = L"";
			this->AppSavBtn->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"AppSavBtn.Image")));
			this->AppSavBtn->ImageFixedSize = System::Drawing::Size(40, 40);
			this->AppSavBtn->Name = L"AppSavBtn";
			this->AppSavBtn->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(1) {this->SavConfigBtn});
			this->AppSavBtn->SubItemsExpandWidth = 24;
			this->AppSavBtn->Text = L"&Save...";
			// 
			// SavConfigBtn
			// 
			this->SavConfigBtn->Command = this->AppSavCmd;
			this->SavConfigBtn->CommandParameter = L"CONFIG";
			this->SavConfigBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"SavConfigBtn.Icon")));
			this->SavConfigBtn->Name = L"SavConfigBtn";
			this->SavConfigBtn->Text = L"Config File";
			this->SavConfigBtn->Tooltip = L"save configuration file";
			// 
			// AppSavCmd
			// 
			this->AppSavCmd->Name = L"AppSavCmd";
			this->AppSavCmd->Executed += gcnew System::EventHandler(this, &Form1::AppSavCmd_Executed);
			// 
			// itemContainer4
			// 
			// 
			// 
			// 
			this->itemContainer4->BackgroundStyle->Class = L"RibbonFileMenuBottomContainer";
			this->itemContainer4->BackgroundStyle->CornerType = DevComponents::DotNetBar::eCornerType::Square;
			this->itemContainer4->HorizontalItemAlignment = DevComponents::DotNetBar::eHorizontalItemsAlignment::Right;
			this->itemContainer4->Name = L"itemContainer4";
			this->itemContainer4->SubItems->AddRange(gcnew cli::array< DevComponents::DotNetBar::BaseItem^  >(2) {this->buttonItem13, 
				this->buttonItem14});
			// 
			// buttonItem13
			// 
			this->buttonItem13->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::ImageAndText;
			this->buttonItem13->ColorTable = DevComponents::DotNetBar::eButtonColor::OrangeWithBackground;
			this->buttonItem13->Name = L"buttonItem13";
			this->buttonItem13->SubItemsExpandWidth = 24;
			this->buttonItem13->Text = L"Opt&ions";
			// 
			// buttonItem14
			// 
			this->buttonItem14->ButtonStyle = DevComponents::DotNetBar::eButtonStyle::ImageAndText;
			this->buttonItem14->ColorTable = DevComponents::DotNetBar::eButtonColor::OrangeWithBackground;
			this->buttonItem14->Name = L"buttonItem14";
			this->buttonItem14->SubItemsExpandWidth = 24;
			this->buttonItem14->Text = L"E&xit";
			// 
			// RibbonAppTab
			// 
			this->RibbonAppTab->Name = L"RibbonAppTab";
			this->RibbonAppTab->Panel = this->RibbonAppPanel;
			this->RibbonAppTab->Text = L"Algorithm";
			// 
			// EditingTools
			// 
			this->EditingTools->Name = L"EditingTools";
			this->EditingTools->Panel = this->EditingToolsPanel;
			this->EditingTools->Text = L"EditingTools";
			// 
			// ErrorCorrection
			// 
			this->ErrorCorrection->Checked = true;
			this->ErrorCorrection->Name = L"ErrorCorrection";
			this->ErrorCorrection->Panel = this->ErrorCorrectionPanel;
			this->ErrorCorrection->Text = L"ErrorCorrect";
			// 
			// RibbonToolTab
			// 
			this->RibbonToolTab->Name = L"RibbonToolTab";
			this->RibbonToolTab->Panel = this->RibbonToolPanel;
			this->RibbonToolTab->Text = L"Tools";
			// 
			// Debug
			// 
			this->Debug->Name = L"Debug";
			this->Debug->Panel = this->ribbonPanel1;
			this->Debug->Text = L"Debug";
			// 
			// QickOpnBtn
			// 
			this->QickOpnBtn->Command = this->AppOpnCmd;
			this->QickOpnBtn->CommandParameter = L"MEDIA";
			this->QickOpnBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"QickOpnBtn.Icon")));
			this->QickOpnBtn->Name = L"QickOpnBtn";
			this->QickOpnBtn->Text = L"Open...";
			// 
			// QickSavBtn
			// 
			this->QickSavBtn->Command = this->AppSavCmd;
			this->QickSavBtn->CommandParameter = L"CONFIG";
			this->QickSavBtn->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"QickSavBtn.Icon")));
			this->QickSavBtn->Name = L"QickSavBtn";
			this->QickSavBtn->Text = L"Save...";
			// 
			// qatCustomizeItem1
			// 
			this->qatCustomizeItem1->Name = L"qatCustomizeItem1";
			// 
			// AppPDBCmd
			// 
			this->AppPDBCmd->Name = L"AppPDBCmd";
			this->AppPDBCmd->Executed += gcnew System::EventHandler(this, &Form1::AppPDBCmd_Executed);
			// 
			// QRCPSize3
			// 
			this->QRCPSize3->Text = L"3X3";
			// 
			// comboItem1
			// 
			this->comboItem1->Text = L"0.1X";
			// 
			// StyleManager
			// 
			this->StyleManager->ManagerColorTint = System::Drawing::Color::White;
			this->StyleManager->ManagerStyle = DevComponents::DotNetBar::eStyle::Office2010Black;
			this->StyleManager->MetroColorParameters = DevComponents::DotNetBar::Metro::ColorTables::MetroColorGeneratorParameters(System::Drawing::Color::White, 
				System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(163)), 
				static_cast<System::Int32>(static_cast<System::Byte>(26))));
			// 
			// comboItem2
			// 
			this->comboItem2->Text = L"Office2007Blue";
			// 
			// comboItem4
			// 
			this->comboItem4->Text = L"DB_3X3_default.pdb";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1123, 570);
			this->Controls->Add(this->dockSite9);
			this->Controls->Add(this->dockSite2);
			this->Controls->Add(this->dockSite1);
			this->Controls->Add(this->dockSite3);
			this->Controls->Add(this->dockSite4);
			this->Controls->Add(this->dockSite5);
			this->Controls->Add(this->dockSite6);
			this->Controls->Add(this->dockSite7);
			this->Controls->Add(this->dockSite8);
			this->Controls->Add(this->RibbonControl);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->Text = L"Application";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->dockSite9->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bar2))->EndInit();
			this->bar2->ResumeLayout(false);
			this->DockCntrPanel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->AppCntxMenuBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->LayerTree))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->CandidateLayer))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->WordArtLayer))->EndInit();
			this->dockSite2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bar3))->EndInit();
			this->bar3->ResumeLayout(false);
			this->LayrDockCntrPanel->ResumeLayout(false);
			this->WordArtLayerCntrPanel->ResumeLayout(false);
			this->PropDockCntrPanel->ResumeLayout(false);
			this->ParamDockCntrPanel->ResumeLayout(false);
			this->ToolDockCntrPanel->ResumeLayout(false);
			this->CandidateDockCntrPanel->ResumeLayout(false);
			this->RibbonControl->ResumeLayout(false);
			this->RibbonControl->PerformLayout();
			this->EditingToolsPanel->ResumeLayout(false);
			this->ribbonBar3->ResumeLayout(false);
			this->ribbonBar3->PerformLayout();
			this->RibbonAppPanel->ResumeLayout(false);
			this->ErrorCorrectionPanel->ResumeLayout(false);
			this->RibbonToolPanel->ResumeLayout(false);
			this->ribbonPanel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion

#pragma region Application variables
		/*---------------------------------------------------------------------*/
		/*! \name                     Theme variables                          */
		/*! \{                                                                 */

		bool						m_ColorSelected;
		Drawing::Color				m_OriginalColor;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Tool control variables                      */
		/*! \{                                                                 */
		
		bool						m_PlayerFrameSliderSuspend;
		bool						m_StrokeSizeSliderSuspend;	
		
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 GLPanel control variables                    */
		/*! \{                                                                 */
		
		HKOGLPanelControl^			mp_GLPanel;		///< Selected OpenGL panel 
		List<HKOGLPanelControl^>^	mp_GLPanels;	///< List of OpenGL panels	

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Application variables                       */
		/*! \{                                                                 */		

		HKCAppItem^					mp_AppItem;		///< Application item
		HKCAppState*				mp_AppState;	///< Application state
		HKCAppRender^				mp_AppRendr;	///< Application render
		HKCAppIOMgr^				mp_AppIOMgr;	///< Application I/O manager	
		HKCAppToolMgr^				mp_AppToolMgr;	///< Application tool manager
		HKCAppLayerMgr^				mp_AppLayerMgr;	///< Application layer manager	

		/*! \}                                                                 */		
#pragma endregion
#pragma region Application functions
		/*---------------------------------------------------------------------*/
		/*! \name                     Access variables                         */
		/*! \{                                                                 */
	public:			
		/// Access to selected GLPanel control
		property HKOGLPanelControl^ GLPanel
		{
			HKOGLPanelControl^ get(void) { return mp_GLPanel; }			
		}	
		/// Access to current application state
		property HKCAppState* AppState
		{
			HKCAppState* get(void) { return mp_AppState; }	
			void set(HKCAppState* value) { mp_AppState = value; }
		}	
		/// Access to selected application item
		property HKCAppItem^ AppItem
		{
			HKCAppItem^ get(void) { return mp_AppItem; }	
			void set(HKCAppItem^ value)
			{
				if(mp_AppItem == value) return;
				delete mp_AppItem;
				mp_AppItem = value;
			}
		}
		/// Access to selected application I/O manager
		property HKCAppIOMgr^ IOManager
		{
			HKCAppIOMgr^ get(void) { return mp_AppIOMgr; }			
		}
		/// Access to selected application tool manager
		property HKCAppToolMgr^ ToolManager
		{
			HKCAppToolMgr^ get(void) { return mp_AppToolMgr; }			
		}
		/// Access to selected application layer manager
		property HKCAppLayerMgr^ LayerManager
		{
			HKCAppLayerMgr^ get(void) { return mp_AppLayerMgr; }			
		}
		/// Access to AppSyncBtn->Checked
		property bool has_Sync
		{
			bool get(void) { return AppSyncBtn->Checked; }			
		}
		/// Access to PlayerFrameSlider's value
		property int PlayerFrameSliderValue
		{
			int get(void) { return PlayerFrameSlider->Value; }	
			void set(int value) 
			{
				m_PlayerFrameSliderSuspend = true;
				PlayerFrameSlider->Value = value; 
				m_PlayerFrameSliderSuspend = false;
			}	
		}
		/// Access to PlayerFrameSlider's maximum value
		property int PlayerFrameSliderMaximum
		{
			int get(void) { return PlayerFrameSlider->Maximum; }	
			void set(int value) { PlayerFrameSlider->Maximum = value; }	
		}
		/// Access to PlayerSpeedSlider's value
		property int PlayerSpeedSliderValue
		{
			int get(void) { return PlayerSpeedSlider->Value; }	
			void set(int value) { PlayerSpeedSlider->Value = value; }	
		}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Form control functions                      */
		/*! \{                                                                 */	
	public:
		/// Customize ui of the form
		void Init_GUI(void);

		/// Initialize data of the form
		void Init_Data(void);

		/// Release data of the form
		void Release(void);	

		/// Refresh all property grids
		void PropertyGrid_Refresh(void);		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                   Tool control functions                     */
		/*! \{                                                                 */
	public:				
		/// Toggle tool
		void Tool_Toggle(System::String^);		

		/// Tool's action
		void Tool_Action(System::String^, System::String^);		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  GLPanel control functions                   */
		/*! \{                                                                 */
	public:		
		/// Activate GLPanel control
		void GLPanel_Activate(HKOGLPanelControl^);

		/// Focus on a application item
		void GLPanel_Focus(HKCAppItem^);

		/// Synchronize GLPanels
		void GLPanel_Sync(HKOGLPanelControl^);

		/// Refresh all GLPanels
		void GLPanel_Refresh(void);

		/// Add new GLPanel control
		HKOGLPanelControl^ GLPanel_Add(void);

		/*! \}                                                                 */	
		/*---------------------------------------------------------------------*/
		/*! \name                   AppItem operations                         */
		/*! \{                                                                 */
	public:		
		/// Initialize the application item
		void AppItem_Init(HKCAppItem^);	

		/// Active the application item
		void AppItem_Activate(HKCAppItem^);		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name              Property value changed events                   */
		/*! \{                                                                 */
	private:
		/// Property value changed event of application properties
		System::Void PropGrid_PropertyValueChanged(System::Object^, System::Windows::Forms::PropertyValueChangedEventArgs^);

		/// Property value changed event of application parameters
		System::Void ParamGrid_PropertyValueChanged(System::Object^, System::Windows::Forms::PropertyValueChangedEventArgs^);

		/// Property value changed event of tool properties
		System::Void ToolGrid_PropertyValueChanged(System::Object^, System::Windows::Forms::PropertyValueChangedEventArgs^);

		/// Property value changed event of painter properties
		System::Void PntrProp_PropertyValueChanged(System::Object^, HKCPropEventArgs^);

		/// Property value changed event of GrabCut properties
		System::Void GCProp_PropertyValueChanged(System::Object^, HKCPropEventArgs^);

		/// Property value changed event of QR code parameters
		System::Void QRCParam_PropertyValueChanged(System::Object^, HKCParamEventArgs^);

		void ReadWordArt(System::String^ file);
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    QR code functions                         */
		/*! \{                                                                 */	
	public:
		/// QR code generator's action
		void QRC_Action(System::String^);	
		void QRCInf_Action(DevComponents::DotNetBar::LabelItem^ Label,AppAlgoQRCodeEvaluation QRevaluation);
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Word Art functions                         */
		/*! \{                                                                 */	
	public:
		/// Word Art generator's action
		void WordArt_Action(System::String^);
		void ScalingTool_Action(System::String^,cv::Point2i);
		void TextOrderOrien_Action(System::String^,cv::Point2i);
		void TextChange_Action(System::String^ _action,int lineid,int charid,char c);
		void MQRC_Action(System::String^);

		void SeeLevelChange(int type,bool enable);	

		void UpdateQRCode();
		void UpdateMQRCLayers(bool all);
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                   Algorithm functions                        */
		/*! \{                                                                 */	
	public:
		/// Algorithm process
		void Process(System::String^);

		/*! \}                                                                 */
#pragma endregion
	private: System::Void FormThemeCmd_Executed(System::Object^  sender, System::EventArgs^  e) {

				 ICommandSource^ cmdSrc = (ICommandSource^)sender;
				 if(cmdSrc->CommandParameter->GetType() == System::String::typeid)
				 {
					 DevComponents::DotNetBar::eStyle style = (DevComponents::DotNetBar::eStyle)Enum::Parse(DevComponents::DotNetBar::eStyle::typeid, cmdSrc->CommandParameter->ToString());
					 StyleManager->ManagerStyle = style;
				 }					
				 this->Invalidate();
			 }
	private: System::Void FormThemeColorPicker_ColorPreview(System::Object^  sender, DevComponents::DotNetBar::ColorPreviewEventArgs^  e) {

				 /// Apply the changed color 
				 StyleManager->ManagerColorTint = e->Color;				 
			 }
	private: System::Void FormThemeColorPicker_ExpandChange(System::Object^  sender, System::EventArgs^  e) {

				 if (this->FormColorPicker->Expanded)
				 {
					 // Remember the starting color scheme to apply if no color is selected during live-preview
					 m_ColorSelected = false;
					 m_OriginalColor = StyleManager->ColorTint;					 
				 }
				 else
				 {
					 if (!m_ColorSelected)
						 StyleManager->ColorTint = m_OriginalColor;	
				 }
			 }
	private: System::Void FormThemeColorPicker_SelectedColorChanged(System::Object^  sender, System::EventArgs^  e) {

				 // Indicate that color was selected 
				 m_ColorSelected = true; 
			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 
				 /// Initialize variables
				 Init_Data();				 
			 }
	private: System::Void AppOpnCmd_Executed(System::Object^  sender, System::EventArgs^  e) {		

				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();
				 System::String^ title;				 
				 System::String^ filter;

				 if(System::String::Compare(action, L"MEDIA") == 0){
					 title  = "Open Media File";					 
					 filter = mp_AppIOMgr->Image_Exts;
				 }else if(System::String::Compare(action, L"CONFIG") == 0){
					 title  = "Open Config File";
					 filter = mp_AppIOMgr->Aux_Exts;
				 }else if(System::String::Compare(action, L"SEGMENT") == 0){
					 title  = "Open Segment File";
					 filter = mp_AppIOMgr->Image_Exts;
				 }else if(System::String::Compare(action, L"FLOW") == 0){
					 title  = "Open Flow File";
					 filter = mp_AppIOMgr->Flow_Exts;
				 }else if(System::String::Compare(action,L"Word Art")==0) {
					 title  = "Open Word Art";
					 filter =  mp_AppIOMgr->Line_Exts;
				 }else if (System::String::Compare(action,L"STRING")==0){
					 title  = "Open Articale File";
					 filter =  mp_AppIOMgr->Article_Exts;
				 }else if (System::String::Compare(action,L"GAP")==0){
					 title  = "Open GAP File";
					 filter =  mp_AppIOMgr->Image_Exts;
				 }
				 OpenFileDialog->Title = title;
				 OpenFileDialog->Filter = filter;
				 OpenFileDialog->FilterIndex = 1;
				 OpenFileDialog->FileName = "";
				 OpenFileDialog->Multiselect = false;
				 OpenFileDialog->CheckFileExists = true;
				 if(OpenFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 if(System::String::Compare(action, L"SEGMENT") == 0)
					 {
						mp_AppItem->Data->IO_Handle.seg_filename = MarshalString(OpenFileDialog->FileName);
						this->WordArt_Action("LOADSEG");
					 }else if(System::String::Compare(action, L"FLOW") == 0){
						 mp_AppItem->Data->IO_Handle.vbf_filename = MarshalString(OpenFileDialog->FileName);
						 this->WordArt_Action("LOADVFB");
					 }else if(System::String::Compare(action,L"Word Art")==0){
						  ReadWordArt(OpenFileDialog->FileName);
					 }else if(System::String::Compare(action, L"STRING") == 0){					
						 mp_AppItem->Data->IO_Handle.art_filename = MarshalString(OpenFileDialog->FileName);
						 std::cout<<"Load String...";
						 this->WordArt_Action("LOADARTICLE");
						 std::cout<<"Done"<<std::endl;
					 }else if(System::String::Compare(action, L"GAP") == 0){	
						 cv::Mat& gap_img = mp_AppItem->Data->WordArtEvi.gap_img;
						 mp_AppItem->Data->IO_Handle.gap_filename = MarshalString(OpenFileDialog->FileName);
						 std::cout<<"Load Gap...";
						 gap_img = cv::imread( mp_AppItem->Data->IO_Handle.gap_filename, CV_LOAD_IMAGE_GRAYSCALE);
						 MQRC_Action("PRE_PROCESS");
						 std::cout<<"Done"<<std::endl;
					 }else{
						 if(!mp_AppIOMgr->Read(OpenFileDialog->FileName, this, mp_GLPanel))	{Console::WriteLine("Form1::AppOpnCmd_Executed() : Open file failed");}
					 }
				 }
			 }
	private: System::Void AppSavCmd_Executed(System::Object^  sender, System::EventArgs^  e) {		

				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();
				 System::String^ title;				 
				 System::String^ filter;		 
				 
				 if(System::String::Compare(action, L"CONFIG") == 0)
				 {
					 HKCMediaItem^ item = mp_AppItem->Item;
					 if(item->Media && item->glContext)
					 {
						 vector<cv::Point3d> aabb = item->Media->AABB();
						 int _w=(int)(aabb[1].x - aabb[0].x);
						 int _h=(int)(aabb[1].y - aabb[0].y);
						 int panel_w= this->DockCntrPanel1->Size.Width;
						 int panel_h= this->DockCntrPanel1->Size.Height;

						 item->glContext->Make_Current();		
						 item->glContext->Focus(aabb[0].x-(panel_w-_w)/2, aabb[0].y-(panel_h-_h)/2, aabb[0].z, aabb[1].x+(panel_w-_w)/2, aabb[1].y+(panel_h-_h)/2, aabb[1].z);
						 item->glContext->Refresh();
					 }

					 title  = "Save Config File";
					 filter = mp_AppIOMgr->Aux_Exts;
				 }
				 SaveFileDialog->Title = title;
				 SaveFileDialog->Filter	= filter;
				 SaveFileDialog->FilterIndex	= 1;
				 SaveFileDialog->FileName = "";
				 if(SaveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 {
					 if(!mp_AppIOMgr->Write(SaveFileDialog->FileName, this, mp_GLPanel))	
						 Console::WriteLine("Form1::AppSavCmd_Executed() : Save file failed");						 
				 }
			 }
	private: System::Void OGLPanel_DragEnter(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {

				 if (e->Data->GetDataPresent(DataFormats::FileDrop))
				 {				 
					 e->Effect = DragDropEffects::All;
				 }
			 }
	private: System::Void OGLPanel_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {

				 if(e->Data->GetDataPresent(DataFormats::FileDrop))
				 {
					 cli::array<System::String^>^ files = dynamic_cast< cli::array<System::String^>^ >(e->Data->GetData(DataFormats::FileDrop));	
					 if(!mp_AppIOMgr->Read(files[0], this, (HKOGLPanelControl^)sender))					 
						 Console::WriteLine("Form1::OGLPanel_DragDrop() : Open file failed");
				 }				 
			 }
	private: System::Void OGLPanel_Load(System::Object^  sender, System::EventArgs^  e) {
				 glewInit();
			 }
	private: System::Void OGLPanel_Resize(System::Object^  sender, System::EventArgs^  e) {				 
			 }
	private: System::Void OGLPanel_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {	

				 if(!mp_AppRendr) return;			

				 HKOGLPanelControl^ glPanel = (HKOGLPanelControl^)sender;					 
				 mp_AppRendr->Render(mp_AppItem, glPanel);					 				 
				 mp_AppRendr->Render(mp_AppToolMgr, glPanel);		
			 }

	 private: System::Void Region_Click(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {	
					if(!this->mp_AppItem) return;	
				 	if(this->StringLineEdittingToolBtn->Checked) return;
					if(this->mp_AppItem->Data->WordArtEvi.region_segs.empty()) return;
					if(this->TextOrderBtn->Checked) return;
					
					HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
					cv::Size cnvsSize = ((cv::Mat*)srcItem->Media->Data())->size();
					cv::Rect cnvsRect(0, 0, cnvsSize.width, cnvsSize.height);
					srcItem->glContext->Make_Current();
					cv::Point2d imgpos= CoordCvt_Scr2Img(cv::Point2f(e->X,e->Y),cnvsRect);

					mp_AppItem->Data->WordArtEdt.ClearSelect();

					this->sliderItem2->Value=0;
					this->sliderItem1->Value=10;
					if (e->Button==System::Windows::Forms::MouseButtons::Left)
					{
						if(this->ScalingToolBtn->Checked){
							//cout<<e->X<<" "<<e->Y<<endl;
							this->ScalingTool_Action("click",cv::Point2f(e->X,e->Y));
						}else if (this->TextOrienBtn->Checked){
							this->TextOrderOrien_Action("OrienClick",imgpos);
						}else if (this->TextBaseBtn->Checked){			
							cout<<mp_AppItem->Data->WordArtData[0].splines.size()<<endl;
							double min_Cdis=9999999;
							for (int i=0;i<mp_AppItem->Data->WordArtData[0].splines.size();++i)
							{				 
								int cp=-1;							
								double dis = mp_AppItem->Data->WordArtData[0].splines[i]->SelectChar(imgpos.x,imgpos.y,&cp);
								if (cp!=-1 && dis<min_Cdis)
								{
									min_Cdis = dis;
									mp_AppItem->Data->WordArtEdt.select      = i;
									mp_AppItem->Data->WordArtEdt.select_char = cp;
								}							
							}

							if (mp_AppItem->Data->WordArtEdt.select==-1)return;
							if (mp_AppItem->Data->WordArtEdt.select_char!=-1)
							{
								mp_AppItem->Data->WordArtEdt.select_word=mp_AppItem->Data->WordArtData[0].splines[mp_AppItem->Data->WordArtEdt.select]->CharIDtoWordID(mp_AppItem->Data->WordArtEdt.select_char);
							}

							cout<<this->LevelBox->SelectedIndex<<endl;
							if (this->LevelBox->SelectedIndex==0)
							{
								mp_AppItem->Data->WordArtEdt.select_char=-1;
								mp_AppItem->Data->WordArtEdt.select_word=-1;
							}
							else if (this->LevelBox->SelectedIndex==1)
							{
								mp_AppItem->Data->WordArtEdt.select_char=-1;
							}

							if (mp_AppItem->Data->WordArtEdt.select_word!=-1)
							{
								std::cout<<mp_AppItem->Data->WordArtEdt.select<<","<<mp_AppItem->Data->WordArtEdt.select_word<<","<<mp_AppItem->Data->WordArtData[0].splines[mp_AppItem->Data->WordArtEdt.select]->GetWords()[mp_AppItem->Data->WordArtEdt.select_word]<<"\n";
							}

							if (mp_AppItem->Data->WordArtEdt.select_char!=-1)
							{
								double r,g,b;
								mp_AppItem->Data->WordArtData[0].splines[mp_AppItem->Data->WordArtEdt.select]->GetQRSamples()[mp_AppItem->Data->WordArtEdt.select_char]->qr_char->GetColor(&r,&g,&b);
								mp_AppItem->Data->WordArtEdt.selectcolor=cv::Point3d(r,g,b);
								std::cout<<mp_AppItem->Data->WordArtEdt.select<<","<<mp_AppItem->Data->WordArtEdt.select_char<<","<<mp_AppItem->Data->WordArtData[0].splines[mp_AppItem->Data->WordArtEdt.select]->GetQRSamples()[mp_AppItem->Data->WordArtEdt.select_char]->_char<<"\n";
							}
						}else{
							vector<cv::Mat>&     region_segs  =this->mp_AppItem->Data->WordArtEvi.region_segs;
							vector<RegionParam>& region_params = this->mp_AppItem->Data->WordArtEvi.region_params;

							for (int r = 0 ; r <region_segs.size();r++)
							{
								if (region_segs[r].data[(int)(cnvsSize.height-imgpos.y)* cnvsSize.height +(int)imgpos.x]!=0)
								{
									this->AppItem->Data->WordArtEdt.select_region=r;
									this->smallregioncheckbox->Checked=this->AppItem->Data->WordArtEvi.region_params[r].smallregion;
									this->Rangesize->Text=L""+this->AppItem->Data->WordArtEvi.region_params[r].RangeSize;
									this->BoundaryA->Text=L""+this->AppItem->Data->WordArtEvi.region_params[r].Boundary_Repela;
									this->BoundaryB->Text=L""+this->AppItem->Data->WordArtEvi.region_params[r].Boundary_Repelb;
									this->LineA->Text=L""+this->AppItem->Data->WordArtEvi.region_params[r].Line_Repela;
									this->LineB->Text=L""+this->AppItem->Data->WordArtEvi.region_params[r].Line_Repelb;
									cout<<r<<endl;
									break;
								}
							}
						}
					}
					mp_GLPanel->Invalidate();
					return;
			 }
			 //TODO:: EditingTool	
	private: System::Void Editting_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if(!this->mp_AppItem) return;	
				if (this->StringLineEdittingToolBtn->Checked==false&&this->TextOrderBtn->Checked==false&&this->ScalingToolBtn->Checked==false) return;
				HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
				cv::Size cnvsSize = ((cv::Mat*)srcItem->Media->Data())->size();
				cv::Rect cnvsRect(0, 0, cnvsSize.width, cnvsSize.height);
				srcItem->glContext->Make_Current();
				cv::Point2d imgpos= CoordCvt_Scr2Img(cv::Point2f(e->X,e->Y),cnvsRect);				
				 if(e->Button==System::Windows::Forms::MouseButtons::Middle)//move the control point
				 {
					cout<<"middle mouse move"<<endl;
					if (this->StringLineEdittingToolBtn->Checked==true&&mp_AppItem->Data->WordArtEdt.select != -1)
					{
						int select           = mp_AppItem->Data->WordArtEdt.select;
						int select_ctrlpoint = mp_AppItem->Data->WordArtEdt.select_ctrlpoint;
						mp_AppItem->Data->WordArtData[0].splines[select]->EditCtrlPoint(select_ctrlpoint,HSSSpline::Vector2(imgpos.x,imgpos.y));			
					}

					if (this->TextOrderBtn->Checked==true && mp_AppItem->Data->WordArtEdt.select_record != -1)
					{
						double min_dis=9999999;
						mp_AppItem->Data->WordArtEdt.select = -1;
						mp_AppItem->Data->WordArtEdt.select_ctrlpoint = -1;
						for (int i=0;i<mp_AppItem->Data->WordArtData[0].splines.size();++i)
						{				 
							int cp=-1;
							double dis = mp_AppItem->Data->WordArtData[0].splines[i]->SelectCtrlPoint(imgpos.x,imgpos.y,&cp);
							if (cp!=-1 && dis<min_dis)
							{
								min_dis = dis;
								mp_AppItem->Data->WordArtEdt.select = i;
								mp_AppItem->Data->WordArtEdt.select_ctrlpoint = cp;
							}
						}
						cout<<mp_AppItem->Data->WordArtEdt.select<<endl;
					}
					cout<<imgpos<<endl;	
				 }
				 else if(e->Button==System::Windows::Forms::MouseButtons::Left)
				 {
					 if(this->StringLineEdittingToolBtn->Checked==true)
					 {
						 double value=(double)this->ScaleSlider->Value*40/100.0f;
						 cout<<"left mouse move"<<endl;
						 mp_AppItem->Data->WordArtEdt.points().push_back(HSSSpline::PathPoint<5>(imgpos.x,imgpos.y,value*2,value,value));
					 }
					cout<<imgpos<<endl;	
				 }
				 else if(e->Button==System::Windows::Forms::MouseButtons::Right)
				 {
					 if(this->StringLineEdittingToolBtn->Checked==true)
					 {
						 cv::Point2d pt=mp_AppItem->Data->WordArtEdt.point_record;
						 cout<<"middle mouse move"<<endl;
						 if (mp_AppItem->Data->WordArtEdt.select != -1&&pt.x!=-1&&pt.y!=-1)
						 {
							 int select=mp_AppItem->Data->WordArtEdt.select;						 
							 mp_AppItem->Data->WordArtData[0].splines[select]->EditAllPointPosition(HSSSpline::Vector2(imgpos.x-pt.x,imgpos.y-pt.y));
						 }
						 mp_AppItem->Data->WordArtEdt.point_record=imgpos;
					 }
					 cout<<imgpos<<endl;
				 }
				 else if (this->ScalingToolBtn->Checked==true)
				 {
					 double min_dis=9999999;
					 mp_AppItem->Data->WordArtEdt.select = -1;
					 mp_AppItem->Data->WordArtEdt.select_word = -1;
					 for (int i=0;i<mp_AppItem->Data->WordArtData[0].splines.size();++i){				 
						 int cp=-1;
						 double dis = mp_AppItem->Data->WordArtData[0].splines[i]->SelectWord(imgpos.x,imgpos.y,&cp);
						 if (cp!=-1 && dis<min_dis){
							 min_dis = dis;
							 mp_AppItem->Data->WordArtEdt.select = i;
							 mp_AppItem->Data->WordArtEdt.select_word = cp;
						 }
					 }
				 }
				mp_GLPanel->Invalidate();
	 }
	private: System::Void Editting_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {			
			if(!this->mp_AppItem) return;	
			if (this->StringLineEdittingToolBtn->Checked==true && mp_AppItem->Data->WordArtEdt.select!=-1)
			{
				int select = mp_AppItem->Data->WordArtEdt.select;
				int select_ctrl_point = mp_AppItem->Data->WordArtEdt.select_ctrlpoint;

				if (e->Delta >0){
					cout<<"add"<<endl;
					mp_AppItem->Data->WordArtData[0].splines[select]->EditAllPointSize(true);
					//mp_AppItem->Data->WordArtEvi.adjustspline_id.push_back(mp_AppItem->Data->WordArtEvi.m_Select);
				}else if (e->Delta <0){
					cout<<"Subtract"<<endl;
					mp_AppItem->Data->WordArtData[0].splines[select]->EditAllPointSize(false);
					//mp_AppItem->Data->WordArtEvi.adjustspline_id.push_back(mp_AppItem->Data->WordArtEvi.m_Select);
				}
			}
			mp_GLPanel->Invalidate();
		 }
	private: System::Void Editting_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		 if(!this->mp_AppItem) return;	

		 HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
		 cv::Size cnvsSize = ((cv::Mat*)srcItem->Media->Data())->size();
		 cv::Rect cnvsRect(0, 0, cnvsSize.width, cnvsSize.height);
		 srcItem->glContext->Make_Current();
		 cv::Point2d imgpos= CoordCvt_Scr2Img(cv::Point2f(e->X,e->Y),cnvsRect);

		 if(e->Button==System::Windows::Forms::MouseButtons::Right)
		 {
			 if (this->StringLineEdittingToolBtn->Checked==false) return;
			 cout<<"right mouse down"<<endl;
			 cout<<imgpos<<endl;	
			 double min_dis=9999999;
			 mp_AppItem->Data->WordArtEdt.select = -1;
			 mp_AppItem->Data->WordArtEdt.select_ctrlpoint = -1;
			 for (int i=0;i<mp_AppItem->Data->WordArtData[0].splines.size();++i)
			 {				 
				 int cp=-1;
				 double dis = mp_AppItem->Data->WordArtData[0].splines[i]->SelectCtrlPoint(imgpos.x,imgpos.y,&cp);
				 if (cp!=-1 && dis<min_dis)
				 {
					 min_dis = dis;
					 mp_AppItem->Data->WordArtEdt.select = i;
					 mp_AppItem->Data->WordArtEdt.select_ctrlpoint = cp;
				 }
			 }
			 if (mp_AppItem->Data->WordArtEdt.select!=-1 && mp_AppItem->Data->WordArtEdt.select_ctrlpoint!=-1)
			 {
				 mp_AppItem->Data->WordArtEdt.point_record = imgpos;
				 HSSSpline::PathPoint<5> p_info =  mp_AppItem->Data->WordArtData[0].splines[mp_AppItem->Data->WordArtEdt.select]->GetCtrlPoint(mp_AppItem->Data->WordArtEdt.select_ctrlpoint);
				 std::cout<<p_info[0]<<","<<p_info[1]<<","<<p_info[2]<<","<<p_info[3]<<"\n";
			 }
		 }else if(e->Button==System::Windows::Forms::MouseButtons::Left)
		 { 
			 if (this->StringLineEdittingToolBtn->Checked==false) return;
			 cout<<"left mouse down"<<endl;
			 double value=(double)this->ScaleSlider->Value*40/100.0f;
			 mp_AppItem->Data->WordArtEdt.points.clear();
			 mp_AppItem->Data->WordArtEdt.points().push_back(HSSSpline::PathPoint<5>(imgpos.x,imgpos.y,value*2,value,value));
			 cout<<value<<endl;
			 cout<<imgpos<<endl;				
		 }else if(e->Button==System::Windows::Forms::MouseButtons::Middle)//select ctrl point
		 {
			if (this->StringLineEdittingToolBtn->Checked==false&&this->TextOrderBtn->Checked==false) return;
			 cout<<"middle mouse down"<<endl;
			 cout<<imgpos<<endl;	
			
			 double min_dis=9999999;
			 mp_AppItem->Data->WordArtEdt.select = -1;
			 mp_AppItem->Data->WordArtEdt.select_ctrlpoint = -1;
			 cout<<mp_AppItem->Data->WordArtData[0].splines.size()<<endl;
			 for (int i=0;i<mp_AppItem->Data->WordArtData[0].splines.size();++i)
			 {				 
				 int cp=-1;
				 double dis = mp_AppItem->Data->WordArtData[0].splines[i]->SelectCtrlPoint(imgpos.x,imgpos.y,&cp);
				 if (cp!=-1 && dis<min_dis)
				 {
					 min_dis = dis;
					 mp_AppItem->Data->WordArtEdt.select = i;
					 mp_AppItem->Data->WordArtEdt.select_ctrlpoint = cp;
				 }
			 }
			 if (mp_AppItem->Data->WordArtEdt.select!=-1 && mp_AppItem->Data->WordArtEdt.select_ctrlpoint!=-1)
			 {
				 mp_AppItem->Data->WordArtEdt.select_record = mp_AppItem->Data->WordArtEdt.select;
				 HSSSpline::PathPoint<5> p_info =  mp_AppItem->Data->WordArtData[0].splines[mp_AppItem->Data->WordArtEdt.select]->GetCtrlPoint(mp_AppItem->Data->WordArtEdt.select_ctrlpoint);
				 std::cout<<p_info[0]<<","<<p_info[1]<<","<<p_info[2]<<","<<p_info[3]<<"\n";
			 }
			 
		 }
		 mp_GLPanel->Invalidate();
	 }
	private: System::Void Editting_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				if(!this->mp_AppItem) return;	

				 HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
				 srcItem->Prop->Render->Visible=false;
				 cv::Size cnvsSize = ((cv::Mat*)srcItem->Media->Data())->size();
				 cv::Rect cnvsRect(0, 0, cnvsSize.width, cnvsSize.height);
				 srcItem->glContext->Make_Current();
				 cv::Point2d imgpos= CoordCvt_Scr2Img(cv::Point2f(e->X,e->Y),cnvsRect);
			  if(e->Button==System::Windows::Forms::MouseButtons::Left)
			  { 
				  if (this->StringLineEdittingToolBtn->Checked==false){return;}
				  int order=0;
				  AppAlgoTextAlign	text_align;
				  AppAlgoTextColor	text_color(mp_AppItem);
				  text_color.Enable(((int)mp_AppItem->Param->WordArt->ColorMode));
				  AppAlgoTextTyping	text_typing;
				  cout<<"left mouse up"<<endl;	
				  QRWordArt::QRStringLine* spline = new  QRWordArt::QRStringLine;
				  spline->AssignPoints(mp_AppItem->Data->WordArtEdt.points);
				  spline->FittingCurve(0.1,true);
				  //spline->RefittingCurve(0.05);
				  text_typing.Typing_Order(mp_AppItem->Data->WordArtEvi.candidate_strings,*spline,order);
				  text_typing.Typing_Fitting(mp_AppItem->Data->WordArtEvi.candidate_strings,*spline);
				  text_align.Justify(*spline);
				  text_color.Execute(*spline);
				  mp_AppItem->Data->WordArtData[0].splines.push_back(spline);
				  mp_AppItem->Data->WordArtEdt.user_splines.push_back(spline);
				  mp_AppItem->Data->WordArtEdt.points.clear();
				  cout<<imgpos<<endl;	
			  }
			  if(e->Button==System::Windows::Forms::MouseButtons::Middle)
			  {
				  if (this->StringLineEdittingToolBtn->Checked==true) 
				  {
// 					  if (is_editting == true)
// 					  {
// 						  cout<<"here"<<endl;
// 						  //mp_AppItem->Data->WordArtEvi.adjustspline_id.push_back(mp_AppItem->Data->WordArtEvi.m_Select);
// 						  is_editting=false;					 
// 					  }
					  ShowSingleLineEnergy();
				  }

				  if (this->TextOrderBtn->Checked==true)
				  {
					  cout<<"middle mouse down"<<endl;
					  cout<<imgpos<<endl;	

					  double min_dis=9999999;
					  int s=  mp_AppItem->Data->WordArtEdt.select_record;
					  mp_AppItem->Data->WordArtEdt.select = -1;
					  mp_AppItem->Data->WordArtEdt.select_ctrlpoint = -1;
					  cout<<mp_AppItem->Data->WordArtData[0].splines.size()<<endl;
					  for (int i=0;i<mp_AppItem->Data->WordArtData[0].splines.size();++i)
					  {				 
						  int cp=-1;
						  double dis = mp_AppItem->Data->WordArtData[0].splines[i]->SelectCtrlPoint(imgpos.x,imgpos.y,&cp);
						  if (cp!=-1 && dis<min_dis)
						  {
							  min_dis = dis;
							  mp_AppItem->Data->WordArtEdt.select = i;
							  mp_AppItem->Data->WordArtEdt.select_ctrlpoint = cp;
						  }
					  }
					  if (mp_AppItem->Data->WordArtEdt.select!=-1 && mp_AppItem->Data->WordArtEdt.select_ctrlpoint!=-1)
					  {
						  HSSSpline::PathPoint<5> p_info =  mp_AppItem->Data->WordArtData[0].splines[mp_AppItem->Data->WordArtEdt.select]->GetCtrlPoint(mp_AppItem->Data->WordArtEdt.select_ctrlpoint);
						  std::cout<<p_info[0]<<","<<p_info[1]<<","<<p_info[2]<<","<<p_info[3]<<"\n";
					  }

					  if (s!=-1&& mp_AppItem->Data->WordArtEdt.select != -1 && mp_AppItem->Data->WordArtEdt.select !=s)
					  {
						  //insert mode
						  cout<<"insert"<<endl;
						  QRWordArt::QRStringLine* spline =mp_AppItem->Data->WordArtData[0].splines[mp_AppItem->Data->WordArtEdt.select];
						  mp_AppItem->Data->WordArtData[0].splines.erase(mp_AppItem->Data->WordArtData[0].splines.begin()+mp_AppItem->Data->WordArtEdt.select);
						  if (s<mp_AppItem->Data->WordArtEdt.select )
							  s+=1;
						  mp_AppItem->Data->WordArtData[0].splines.insert(mp_AppItem->Data->WordArtData[0].splines.begin()+s,spline);

						  mp_AppItem->Data->WordArtEdt.select_record=-1;
						  mp_AppItem->Data->WordArtEdt.select=-1;
					  }

				  }
			  }
			  mp_GLPanel->Invalidate();
		  }
	private: System::Void Editting_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 if(!this->mp_AppItem) return;	

				 if(this->TextBaseBtn->Checked==true&&mp_AppItem->Data->WordArtEdt.select!=-1)
				 {
					 int select = mp_AppItem->Data->WordArtEdt.select;
					 int select_char = mp_AppItem->Data->WordArtEdt.select_char;
					 int select_word = mp_AppItem->Data->WordArtEdt.select_word;
					if(mp_AppItem->Data->WordArtEdt.select_char!=-1)
					 {
						 vector<HSSSpline::Scale3> bold_data = mp_AppItem->Data->WordArtData[0].splines[select]->GetQRSamples()[select_char]->qr_char->GetAllFontWeight();
						 
						 if (e->Control&&e->KeyCode == Keys::Z)
						 {
							 for (int i = 0 ; i <bold_data.size(); i++)
							 {
								 bold_data[i][0]*=0.9;
								 bold_data[i][1]*=0.9;
								 bold_data[i][2]*=0.9;
							 }
							mp_AppItem->Data->WordArtData[0].splines[select]->GetQRSamples()[select_char]->qr_char->SetAllFontWeight(bold_data);
						 }
						 else if (e->Control&&e->KeyCode == Keys::X)
						 {
							 for (int i = 0 ; i <bold_data.size(); i++)
							 {
								 bold_data[i][0]*=1.1;
								 bold_data[i][1]*=1.1;
								 bold_data[i][2]*=1.1;
							 }
							 mp_AppItem->Data->WordArtData[0].splines[select]->GetQRSamples()[select_char]->qr_char->SetAllFontWeight(bold_data);
						 }						 
						 else if (!e->Control)
						 {
							 KeysConverter kc;
							 char c=MarshalString(kc.ConvertToString(e->KeyCode))[0];
							 this->TextChange_Action("TextChange",mp_AppItem->Data->WordArtEdt.select,mp_AppItem->Data->WordArtEdt.select_char,c);
						 }
					}
					 mp_GLPanel->Invalidate();
					 return;
				 }
				 
				 if (e->KeyCode == Keys::A)
				 {
					 int select = mp_AppItem->Data->WordArtEdt.select;
					 if (select!=-1)
					 {
						 mp_AppItem->Data->WordArtData[0].splines[select]->Release();
						 std::vector<int> regen_id;
						 regen_id.push_back(select);
						 AppAlgoTextGeneration^ algoObj_TextGeneration = gcnew AppAlgoTextGeneration;
						 algoObj_TextGeneration->TypeSet(mp_AppItem->Param->WordArt->TextType);
						 algoObj_TextGeneration->TextGeneration(mp_AppItem,regen_id,mp_AppItem->Data->WordArtEvi.candidate_strings);
					 }
					 if (e->Control)
					 {
						 std::vector<int> regen_id;
						 for (int i = 0 ; i <mp_AppItem->Data->WordArtData[0].splines.size();i++)
						 {
							 mp_AppItem->Data->WordArtData[0].splines[i]->Release();							 
							 regen_id.push_back(i);							
						 }
						 AppAlgoTextGeneration^ algoObj_TextGeneration = gcnew AppAlgoTextGeneration;
						 algoObj_TextGeneration->TypeSet(mp_AppItem->Param->WordArt->TextType);
						 algoObj_TextGeneration->TextGeneration(mp_AppItem,regen_id,mp_AppItem->Data->WordArtEvi.candidate_strings);
						
					 }
				 }

				 if (e->KeyCode == Keys::L)
				 {
					 int select = mp_AppItem->Data->WordArtEdt.select;
					 if (select!=-1)
					 {
						 mp_AppItem->Data->WordArtData[0].splines[select]->RefittingCurve(0.2);
					 }
				 }
				
				/*int move=-1;
				if (e->Control&&e->KeyCode == Keys::Up)
				{
					cout<<"Up"<<endl;
					move= 0;
				}
				else  if (e->Control&&e->KeyCode == Keys::Down)
				{
					cout<<"Down"<<endl;
					move= 1;
				}
				else if (e->Control&&e->KeyCode == Keys::Left)
				{
					cout<<"Left"<<endl;
					move= 3;
				}
				else if (e->Control&&e->KeyCode == Keys::Right)
				{
					cout<<"Right"<<endl;
					move= 2;
				}				 
				for (int i =0 ;i< mp_AppItem->Data->WordArtData[mp_AppItem->Data->CurrentWordArtID].splines.size();i++)
				{
					mp_AppItem->Data->WordArtData[mp_AppItem->Data->CurrentWordArtID].splines[i]->EditAllPointPosition(move,3);

					mp_AppItem->Data->WordArtData[mp_AppItem->Data->CurrentWordArtID].splines[i]->Update();
				}*/
				

				 if (this->StringLineEdittingToolBtn->Checked==true && mp_AppItem->Data->WordArtEdt.select!=-1)
				 {

					 int select            = mp_AppItem->Data->WordArtEdt.select;
					 int select_ctrl_point = mp_AppItem->Data->WordArtEdt.select_ctrlpoint;
					 
					 if (e->KeyCode == Keys::Add)
					 {
						 cout<<"add"<<endl;
						 mp_AppItem->Data->WordArtData[0].splines[select]->EditAllPointSize(true);
						 //mp_AppItem->Data->WordArtEvi.adjustspline_id.push_back(mp_AppItem->Data->WordArtEditing.m_Select);
					 }
					 else if (e->KeyCode == Keys::Subtract)
					 {
						 cout<<"Subtract"<<endl;
						 mp_AppItem->Data->WordArtData[0].splines[select]->EditAllPointSize(false);
						 //mp_AppItem->Data->WordArtEditing.adjustspline_id.push_back(mp_AppItem->Data->WordArtEditing.m_Select);
					 }
					 else  if (e->KeyCode == Keys::Up)
					 {
						 cout<<"Up"<<endl;
						 mp_AppItem->Data->WordArtData[0].splines[select]->EditAllPointPosition(0);
					 }
					 else  if (e->KeyCode == Keys::Down)
					 {
						 cout<<"Down"<<endl;
						 mp_AppItem->Data->WordArtData[0].splines[select]->EditAllPointPosition(1);
					 }
					 else if (e->KeyCode == Keys::Left)
					 {
						 cout<<"Left"<<endl;
						 mp_AppItem->Data->WordArtData[0].splines[select]->EditAllPointPosition(3);
					 }
					 else if (e->KeyCode == Keys::Right)
					 {
						 cout<<"Right"<<endl;
						 mp_AppItem->Data->WordArtData[0].splines[select]->EditAllPointPosition(2);
					 }				 
					 else if (e->KeyCode == Keys::Z)
					 {
						cout<<"z click"<<endl;
						HSSSpline::PathPoint<5> p_info =  mp_AppItem->Data->WordArtData[0].splines[select]->GetCtrlPoint(select_ctrl_point);
						if (this->SoftAdjust->Checked)
							mp_AppItem->Data->WordArtData[0].splines[select]->SoftEditCtrlPointSize(select_ctrl_point,HSSSpline::Scale3(p_info[2]-0.2,p_info[3]-0.1,p_info[4]-0.1));
						else
							mp_AppItem->Data->WordArtData[0].splines[select]->EditCtrlPointSize(select_ctrl_point,HSSSpline::Scale3(p_info[2]-0.2,p_info[3]-0.1,p_info[4]-0.1));
						//mp_AppItem->Data->WordArtEvi.adjustspline_id.push_back(m_Select);
						ShowSingleLineEnergy();
					 }else if (e->KeyCode == Keys::X)
					 {
						cout<<"x click"<<endl;
						HSSSpline::PathPoint<5> p_info =  mp_AppItem->Data->WordArtData[0].splines[select]->GetCtrlPoint(select_ctrl_point);
						if (this->SoftAdjust->Checked)
							 mp_AppItem->Data->WordArtData[0].splines[select]->SoftEditCtrlPointSize(select_ctrl_point,HSSSpline::Scale3(p_info[2]+0.2,p_info[3]+0.1,p_info[4]+0.1));
						else
							 mp_AppItem->Data->WordArtData[0].splines[select]->EditCtrlPointSize(select_ctrl_point,HSSSpline::Scale3(p_info[2]+0.2,p_info[3]+0.1,p_info[4]+0.1));
						//mp_AppItem->Data->WordArtEvi.adjustspline_id.push_back(m_Select);
						ShowSingleLineEnergy();
					 }else if(e->KeyCode ==  Keys::D)
					 {
						cout<<"d click"<<endl;
						mp_AppItem->Data->WordArtData[0].splines[select]->Release();
						mp_AppItem->Data->WordArtData[0].splines.erase(mp_AppItem->Data->WordArtData[0].splines.begin()+select);

						mp_AppItem->Data->WordArtEdt.select=-1;
						mp_AppItem->Data->WordArtEdt.select_ctrlpoint=-1;
					 }	
				 }
				 // 切換Data
				 if		(e->KeyCode == Keys::D0){mp_AppItem->Data->CurrentWordArtID=0;UpdateMQRCLayers(false);}
				 else if(e->KeyCode == Keys::D1){mp_AppItem->Data->CurrentWordArtID=1;UpdateMQRCLayers(false);}
				 else if(e->KeyCode == Keys::D2){mp_AppItem->Data->CurrentWordArtID=2;UpdateMQRCLayers(false);}
				 else if(e->KeyCode == Keys::D3){mp_AppItem->Data->CurrentWordArtID=3;UpdateMQRCLayers(false);}
				 mp_GLPanel->Invalidate();
			}

	private: System::Void OGLPanel_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {	
				  if(mp_AppState)
					 mp_AppState->Panel_MouseDown(this, static_cast<HKOGLPanelControl^>(sender), e);
			 }
	private: System::Void OGLPanel_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
				 if(mp_AppState)
					 mp_AppState->Panel_MouseMove(this, static_cast<HKOGLPanelControl^>(sender), e);
			 }
	private: System::Void OGLPanel_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {	
				 if(mp_AppState)
					 mp_AppState->Panel_MouseUp(this, static_cast<HKOGLPanelControl^>(sender), e);
			 }
	private: System::Void OGLPanel_MouseWheel(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {	
				 if(mp_AppState)
					 mp_AppState->Panel_MouseWheel(this, static_cast<HKOGLPanelControl^>(sender), e);
			 }
	private: System::Void OGLPanel_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {		
				 if(mp_AppState)
					 mp_AppState->Panel_KeyDown(this, static_cast<HKOGLPanelControl^>(sender), e);
			 }
	private: System::Void OGLPanel_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {	
				 if(mp_AppState)
					 mp_AppState->Panel_KeyUp(this, static_cast<HKOGLPanelControl^>(sender), e);	
			 }
	private: System::Void AppDesignCmd_Executed(System::Object^  sender, System::EventArgs^  e) {

				 if(!mp_AppItem) return;			 

				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();

				 if(System::String::Compare(action, L"CENTER") == 0)
				 {
					 this->GLPanel_Focus(mp_AppItem);
					 if(AppSyncBtn->Checked)
						 GLPanel_Sync(mp_GLPanel);
				 }
				 else if(System::String::Compare(action, L"SYNC") == 0)
				 {					
					 if(AppSyncBtn->Checked)
						 GLPanel_Sync(mp_GLPanel);
				 }
			 }
	private: System::Void AppLayerCmd_Executed(System::Object^  sender, System::EventArgs^  e) {
				 
				 if(!mp_AppItem || !LayerTree->SelectedNode) return;

				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();

				 Node^ node	= LayerTree->SelectedNode;
				 int nodeIdx = LayerTree->Nodes->IndexOf(node);
				 if(System::String::Compare(action, L"DELETE") == 0)
				 {			
					 /// Delete the corresponding media item
					 mp_AppItem->Delete(nodeIdx);

					 /// Rebuild layers
					 mp_AppLayerMgr->Build(this->LayerTree, mp_AppItem);

					 /// Update tools
					 mp_AppToolMgr->Update(mp_AppItem, this);					 

					 /// Refresh all GLPanels
					 this->GLPanel_Refresh();			 				 
				 }
				 else if(System::String::Compare(action, L"SHOW") == 0)
				 {
					 mp_AppItem->Show(nodeIdx);					 
				 }
			 }
	private: System::Void LayerTree_NodeDoubleClick(System::Object^  sender, DevComponents::AdvTree::TreeNodeMouseEventArgs^  e) {
				 
				 if(!mp_AppItem) return;

				 Node^ node = e->Node;
				 if(LayerTree->Nodes->Contains(node))
				 {		
					 /// Focus on the selected media item
					 this->GLPanel_Focus(mp_AppItem);
					 if(AppSyncBtn->Checked)
						 GLPanel_Sync(mp_GLPanel);
				 }		
			 }
	private: System::Void WordArtLayer_NodeDoubleClick(System::Object^  sender, DevComponents::AdvTree::TreeNodeMouseEventArgs^  e) {

				 if(!mp_AppItem) return;

				 Node^ node = e->Node;
				 if(WordArtLayer->Nodes->Contains(node))
				 {		
					 /// Focus on the selected media item
					 this->GLPanel_Focus(mp_AppItem);
					 if(AppSyncBtn->Checked)
						 GLPanel_Sync(mp_GLPanel);
				 }		
			 }
	private: System::Void CandidateLayer_NodeDoubleClick(System::Object^  sender, DevComponents::AdvTree::TreeNodeMouseEventArgs^  e) {

				 if(!mp_AppItem) return;

				 Node^ node = e->Node;
				 if(CandidateLayer->Nodes->Contains(node))
				 {		
					 /// Focus on the selected media item
					 this->GLPanel_Focus(mp_AppItem);
					 if(AppSyncBtn->Checked)
						 GLPanel_Sync(mp_GLPanel);
				 }		
			 }
	private: System::Void LayerTree_AfterNodeSelect(System::Object^  sender, DevComponents::AdvTree::AdvTreeNodeEventArgs^  e) {
				 
				 if(!mp_AppItem) return;

				 Node^ node = e->Node;
				 if(LayerTree->Nodes->Contains(node))
				 {		
					 /// Update the selected media item
					 mp_AppItem->Select(LayerTree->Nodes->IndexOf(node));
					 
					 /// Update tools
					 mp_AppToolMgr->Update(mp_AppItem, this);
					 
					 /// Refresh all property grids
					 this->PropertyGrid_Refresh();
					 					 
				 }				 
			 }
	private: System::Void CandidateLayer_AfterNodeSelect(System::Object^  sender, DevComponents::AdvTree::AdvTreeNodeEventArgs^  e) {

				 if(!mp_AppItem) return;

				 Node^ node = e->Node;
				 if(CandidateLayer->Nodes->Contains(node))
				 {		
					 /// Update the selected media item
					 mp_AppItem->Select(CandidateLayer->Nodes->IndexOf(node));

					 /// Update tools
					 mp_AppToolMgr->Update(mp_AppItem, this);

					 /// Refresh all property grids
					 this->PropertyGrid_Refresh();

				 }				 
			 }
	private: System::Void WordArtLayer_AfterNodeSelect(System::Object^  sender, DevComponents::AdvTree::AdvTreeNodeEventArgs^  e) {

				 if(!mp_AppItem) return;

				 Node^ node = e->Node;
				 if(WordArtLayer->Nodes->Contains(node))
				 {		
					 /// Update the selected media item
					 mp_AppItem->Select(WordArtLayer->Nodes->IndexOf(node));

					 /// Update tools
					 mp_AppToolMgr->Update(mp_AppItem, this);

					 /// Refresh all property grids
					 this->PropertyGrid_Refresh();

				 }				 
			 }
	private: System::Void LayerTree_AfterCheck(System::Object^  sender, DevComponents::AdvTree::AdvTreeCellEventArgs^  e) {
				 
				 if(!mp_AppItem) return;	

				 /// The code only executes if the user caused the checked state to change.
				 if ( e->Action == DevComponents::AdvTree::eTreeAction::Mouse )
				 {				 
					 if ( e->Cell->Parent->Nodes->Count > 0 )
					 {
						 /* Calls the CheckAllChildNodes method, passing in the current
						 Checked value of the TreeNode whose checked state changed. */
						 this->Check_ChildNodes( e->Cell->Parent, e->Cell->Checked );
					 }
				 }		

				 for each(Node^ node in LayerTree->Nodes)
				 {

					 int nodeIdx = LayerTree->Nodes->IndexOf(node);
					 mp_AppItem->Items[nodeIdx]->Prop->Render->Visible = node->Checked;
					 	 
				 }			

				 this->GLPanel_Refresh();
			 }
	private: System::Void CandidateLayer_AfterCheck(System::Object^  sender, DevComponents::AdvTree::AdvTreeCellEventArgs^  e) {
				 std::cout<<"A";
				 if(!mp_AppItem) return;	
				 /// The code only executes if the user caused the checked state to change.
				 if ( e->Action == DevComponents::AdvTree::eTreeAction::Mouse )
				 {				 
					 if (e->Cell->Checked==true)
					 {
						 for each(Node^ node in CandidateLayer->Nodes)
						 {
							 int nodeIdx = CandidateLayer->Nodes->IndexOf(node);
							 node->Checked=false;
							 this->Check_ChildNodes( node, false );						 

						 }	
						  e->Cell->Checked=true;
					 }
					
					 if ( e->Cell->Parent->Nodes->Count > 0 )
					 {
						 /* Calls the CheckAllChildNodes method, passing in the current
						 Checked value of the TreeNode whose checked state changed. */
						 this->Check_ChildNodes( e->Cell->Parent, e->Cell->Checked );
					 }
					 
				 }		
				 mp_AppItem->Data->WordArtEdt.is_scaling=false;
				 mp_AppItem->Data->WordArtData[0].splines.clear();
				 for each(Node^ node in CandidateLayer->Nodes)
				 {
					 int nodeIdx = CandidateLayer->Nodes->IndexOf(node);
					 mp_AppItem->Candidates[nodeIdx]->Prop->Render->Visible = node->Checked;
					 
					 if (node->Checked==true)
					 {
						  mp_AppItem->Data->WordArtEdt.is_scaling=true;
						 if (System::String::Compare(node->Name,"user define")==0)
						 {
							 mp_AppItem->Data->WordArtData[0].splines.insert(mp_AppItem->Data->WordArtData[0].splines.end(),mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.begin(),mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.end());
						 }
						 else
						 {
							// cout<<MarshalString(node->Name)<<endl;
							  mp_AppItem->Data->WordArtData[0].splines.insert(mp_AppItem->Data->WordArtData[0].splines.end(),mp_AppItem->Data->WordArtEdt.CanData.candidates[stoi(MarshalString(node->Name))].splines.begin(),mp_AppItem->Data->WordArtEdt.CanData.candidates[stoi(MarshalString(node->Name))].splines.end());
						}
						
					 }
				 }		
				 if (! mp_AppItem->Data->WordArtEdt.is_scaling)
				 {
					 for each(Node^ R in WordArtLayer->Nodes)
					 {
						 int region = WordArtLayer->Nodes->IndexOf(R);
						 mp_AppItem->WordArtLayers[region]->Prop->Render->Visible = R->Checked;
						 if (R->Checked==true)
						 {
							 mp_AppItem->Data->WordArtData[0].splines.insert(mp_AppItem->Data->WordArtData[0].splines.end(),mp_AppItem->Data->WordArtEvi.region_splines[region].splines.begin(),mp_AppItem->Data->WordArtEvi.region_splines[region].splines.end());
						 }
					 }	
					 if(mp_AppItem->Data->WordArtEdt.user_splines.size()!=0)
 						 mp_AppItem->Data->WordArtData[0].splines.insert(mp_AppItem->Data->WordArtData[0].splines.end(),mp_AppItem->Data->WordArtEdt.user_splines.begin(),mp_AppItem->Data->WordArtEdt.user_splines.end());
				 }
				 
				 this->GLPanel_Refresh();
			 }
	 private: System::Void WordArtLayer_aftercheck(System::Object^  sender, DevComponents::AdvTree::AdvTreeCellEventArgs^  e) {
				 
				 if(!mp_AppItem) return;	

				
				 /// The code only executes if the user caused the checked state to change.
				 if ( e->Action == DevComponents::AdvTree::eTreeAction::Mouse )
				 {				 
					 if ( e->Cell->Parent->Nodes->Count > 0 )
					 {
						 /* Calls the CheckAllChildNodes method, passing in the current
						 Checked value of the TreeNode whose checked state changed. */
						 this->Check_ChildNodes( e->Cell->Parent, e->Cell->Checked );
					 }
				 }		
				double visualenergy=0;
				double QRenergy=0;
				double count=0;
				
				if (! mp_AppItem->Data->WordArtEdt.is_scaling)
				{
					mp_AppItem->Data->WordArtData[0].splines.clear();
					for each(Node^ R in WordArtLayer->Nodes)
					{
						int region = WordArtLayer->Nodes->IndexOf(R);
						mp_AppItem->WordArtLayers[region]->Prop->Render->Visible = R->Checked;
						if (R->Checked==true)
						{
							mp_AppItem->Data->WordArtData[0].splines.insert(mp_AppItem->Data->WordArtData[0].splines.end(),mp_AppItem->Data->WordArtEvi.region_splines[region].splines.begin(),mp_AppItem->Data->WordArtEvi.region_splines[region].splines.end());
							count++;
						}
					}	

					if(mp_AppItem->Data->WordArtEdt.user_splines.size()!=0)
						mp_AppItem->Data->WordArtData[0].splines.insert(mp_AppItem->Data->WordArtData[0].splines.end(),mp_AppItem->Data->WordArtEdt.user_splines.begin(),mp_AppItem->Data->WordArtEdt.user_splines.end());
				}
				this->GLPanel_Refresh();
			}
	private: System::Void Check_ChildNodes(DevComponents::AdvTree::Node^ _tree_node, bool _checked ) {		
				 
				 for each(DevComponents::AdvTree::Node^ node in _tree_node->Nodes)
				 {
					 node->Checked = _checked;
					 if(node->Nodes->Count > 0)
					 {
						 // If the current node has child nodes, call the CheckAllChildsNodes method recursively.
						 Check_ChildNodes(node, _checked);
					 }
				 }
			 }
	private: System::Void PlayerTimer_Tick(System::Object^  sender, System::EventArgs^  e) {

				 if(!mp_AppItem) return;
				 
				 /// Find the media player
				 HKCAppTool^ tool = mp_AppToolMgr->Find(AppGlobal::g_MPlyrLabel);
				 if(!tool) return;

				 tool->Action("FWD", mp_AppItem);
				 				 
				 /// Change the button image
				 System::ComponentModel::ComponentResourceManager^  resMgr = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
				 if(PlayerTimer->Enabled != tool->Prop->Enabled && PlayerTimer->Enabled)
					 PlayerPlayBtn->Image = (cli::safe_cast<System::Drawing::Image^>(resMgr->GetObject(L"PlayerPlayBtn.Image")));				 
				 
				 PlayerTimer->Enabled = tool->Prop->Enabled;

				 HKCMPlyrProp^ prop = dynamic_cast<HKCMPlyrProp^>(tool->Prop);
				 PlayerFrameSliderValue = (int)prop->Frame;
			 }
	private: System::Void PlayerFrameSlider_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

				 if(!mp_AppItem) return;

				 PlayerFrameSlider->Refresh();
				 PlayerFrameSlider->Text = System::String::Concat(L"<b><font color=\"Black\">", PlayerFrameSlider->Value.ToString(), L"</font></b>");			 
				 if(m_PlayerFrameSliderSuspend) return;
				 
				 HKCAppTool^ tool = mp_AppToolMgr->Find(AppGlobal::g_MPlyrLabel);
				 if(!tool) return;

				 HKCMPlyrProp^ prop = dynamic_cast<HKCMPlyrProp^>(tool->Prop);
				 prop->Frame = PlayerFrameSlider->Value;
				 tool->Action("GOTO", mp_AppItem);				 
			 }
	private: System::Void PlayerSpeedSlider_ValueChanged(System::Object^  sender, System::EventArgs^  e) {

				 if(!mp_AppItem) return;			 

				 Int32 value = PlayerSpeedSlider->Value;
				 Double speed = (value < 50) ? 0.2+((double)value*0.8*0.02) : 1.0+((double)value-50.0)*4*0.02;			 			 

				 PlayerSpeedSlider->Refresh();
				 PlayerSpeedSlider->Text = System::String::Concat(L"<b><font color=\"Black\">", speed.ToString(), L"X", L"</font></b>");

				 HKCAppTool^ tool = mp_AppToolMgr->Find(AppGlobal::g_MPlyrLabel);
				 if(!tool) return;

				 HKCMPlyrProp^ prop = dynamic_cast<HKCMPlyrProp^>(tool->Prop);
				 prop->Speed = speed;
				 PlayerTimer->Interval = (int)Math::Round(1000.0 / (prop->FPS*prop->Speed));
			 }
	private: System::Void AppPlayerCmd_Executed(System::Object^  sender, System::EventArgs^  e) {
				 if(!mp_AppItem) return;

				 /// Find the media player
				 HKCAppTool^ tool = mp_AppToolMgr->Find(AppGlobal::g_MPlyrLabel);
				 if(!tool) return;				 

				 HKCMPlyrProp^ prop = dynamic_cast<HKCMPlyrProp^>(tool->Prop);
				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();				 				 

				 if(System::String::Compare(action, L"REPEAT") == 0)
				 {					 
					 prop->Repeat = PlayerReptBtn->Checked;
				 }
				 else if(System::String::Compare(action, L"SYNC") == 0)
				 {					 
					 prop->Sync = PlayerSyncBtn->Checked;
					 Console::WriteLine("Form1::AppPlayerCmd_Executed() : Synchronization is not implemented yet!");
				 }
				 else if(System::String::Compare(action, L"PLAY") == 0)
				 {
					 PlayerTimer->Enabled = !PlayerTimer->Enabled;
					 tool->Prop->Enabled = PlayerTimer->Enabled;
					 		
					 /// Change the button image
					 if(PlayerTimer->Enabled)
					 {
						 /// Get the resource manager
						 System::Reflection::Assembly^ assembly = System::Reflection::Assembly::GetExecutingAssembly();
						 System::Reflection::AssemblyName^ assemblyName = assembly->GetName();	
						 System::Resources::ResourceManager^ resMgr = gcnew System::Resources::ResourceManager(assemblyName->Name+".AppRes", assembly);
						 PlayerPlayBtn->Image = cli::safe_cast<System::Drawing::Image^>(resMgr->GetObject(L"PlayerPauseBtn.Image"));
					 }
					 else
					 {
						 System::ComponentModel::ComponentResourceManager^  resMgr = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
						 PlayerPlayBtn->Image = cli::safe_cast<System::Drawing::Image^>(resMgr->GetObject(L"PlayerPlayBtn.Image"));
					 }						 					 
				 }
				 else
				 {
					 tool->Action(action, mp_AppItem);	
					 PlayerFrameSliderValue = (int)prop->Frame;
				 }
			 }			
	private: System::Void StrokeSize_ValueChanged(System::Object^  sender, System::EventArgs^  e) {	

				 SliderItem^ slider = (SliderItem^)sender;
				 slider->Text = slider->Value.ToString() + L" px";	

				 HKCAppTool^ tool = nullptr;
				 if(slider == GCMStrkSize)
				 {
					 tool = mp_AppToolMgr->Find(AppGlobal::g_GCLabel);					 
				 }
				 else if(slider == PntrMStrkSize)
				 {
					 tool = mp_AppToolMgr->Find(AppGlobal::g_PntrLabel);					 
				 }	

				 if(!tool || m_StrokeSizeSliderSuspend) return;	
				 
				 HKCPntrProp^ prop = dynamic_cast<HKCPntrProp^>(tool->Prop);
				 prop->Size = slider->Value;		
			 }
	private: System::Void PntrBrushColor_SelectedColorChanged(System::Object^  sender, System::EventArgs^  e) {	

				 PntrBrushColor->ForeColor = PntrBrushColor->SelectedColor;
				 
				 HKCAppTool^ tool = mp_AppToolMgr->Find(AppGlobal::g_PntrLabel);
				 if(!tool) return;
				 
				 HKCPntrProp^ prop = dynamic_cast<HKCPntrProp^>(tool->Prop);
				 prop->Color = PntrBrushColor->SelectedColor;								 
			 }
	private: System::Void AppPaintCmd_Executed(System::Object^  sender, System::EventArgs^  e) {				 

				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();				 
				 
				 this->Tool_Action(AppGlobal::g_PntrLabel, action);
			 }
	private: System::Void AppGrabCutCmd_Executed(System::Object^  sender, System::EventArgs^  e) {	
				
				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();
				 
				 this->Tool_Action(AppGlobal::g_GCLabel, action);
			 }
	private: System::Void AppXFormCmd_Executed(System::Object^  sender, System::EventArgs^  e) {

				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();
				 
				 this->Tool_Action(AppGlobal::g_XFormLabel, action);
			 }	
	private: System::Void AppQRCCmd_Executed(System::Object^  sender, System::EventArgs^  e) {

				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();

				 this->QRC_Action(action);
			 }
	private: System::Void QRCText_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				 
				 this->QRC_Action("TEXT");
			 }
	private: System::Void WordArtText_TextChanged(System::Object^  sender, System::EventArgs^  e){

			if (WordArtText2->Text!=mp_AppItem->Param->WordArt->strings)
			{
				mp_AppItem->Param->WordArt->strings = WordArtText2->Text;
				this->WordArt_Action("Strings");
			}
	}

	private: System::Void AppPDBCmd_Executed(System::Object^  sender, System::EventArgs^  e) {

				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();

				 //this->PDB_Action(action);
			 }
	private: System::Void AppStringLineEdittingToolBtnCmd(System::Object^  sender, System::EventArgs^  e) {

						 if (this->StringLineEdittingToolBtn->Checked)
						 {
							 if (TextBaseBtn->Checked==true||TextOrderBtn->Checked==true||TextOrienBtn->Checked==true)
							 {
								 StringLineEdittingToolBtn->Checked=false;
								 return;
							 }
							 this->ribbonBar5->Visible=true;
							  SeeLevelChange(4,true);
							 this->ribbonBar5->Location.X=149;
							 cout<< this->ribbonBar5->Location.X<<endl;
							 mp_AppItem->Data->WordArtEdt.StringLineEditingMode=true;
							 this->HKOGLPanel1->Trackball_Property->Move_Trigger->Mouse= System::Windows::Forms::MouseButtons::None;
							 this->HKOGLPanel1->Trackball_Property->Delta_Res=DBL_MAX;
						 }
						 else
						 {	
							 SeeLevelChange(2,true);
							 this->ribbonBar5->Visible=false;
							 mp_AppItem->Data->WordArtEdt.StringLineEditingMode=false;
							 mp_AppItem->Data->WordArtEdt.select=-1;
							 mp_AppItem->Data->WordArtEdt.select_word=-1;
							 mp_AppItem->Data->WordArtEdt.select_char=-1;
							 mp_AppItem->Data->WordArtEdt.select_record=-1;
							 /*
							 if (mp_AppItem->Data->WordArtEvi.adjustspline_id.size()!=0)
							 {
								 for (int i = 0 ; i<mp_AppItem->Data->WordArtEvi.adjustspline_id.size(); i++)
								 {
									 int id = mp_AppItem->Data->WordArtEvi.adjustspline_id[i];
									 for (int j = i+1 ; j<mp_AppItem->Data->WordArtEvi.adjustspline_id.size();j++)
									 {
										if( mp_AppItem->Data->WordArtEvi.adjustspline_id[j]==mp_AppItem->Data->WordArtEvi.adjustspline_id[i])
										{
											mp_AppItem->Data->WordArtEvi.adjustspline_id.erase(mp_AppItem->Data->WordArtEvi.adjustspline_id.begin()+j);
										}
									 }
									 mp_AppItem->Data->WordArtData[0].splines[id]->Release();
								 }
								 AppAlgoTextGeneration^ algoObj_TextGeneration = gcnew AppAlgoTextGeneration;
								 AppAlgoEvaluation EnergyEvaluate;
								 algoObj_TextGeneration->TypeSet(mp_AppItem->Param->WordArt->TextType);
								 algoObj_TextGeneration->ReTextGen(true);
								 algoObj_TextGeneration->Execute(mp_AppItem);
								 EnergyEvaluate.Execute(mp_AppItem);
								 QRCInf_Action(QRcodeLabel,EnergyEvaluate);
								 QRenergyBar->Value=1000*(EnergyEvaluate.Em());
								 this->label2->Text=L"QR energy : 0."+ this->QRenergyBar->Value.ToString();
								 if(mp_AppItem->Find("Energy"))
								 {
									 HKCMediaItem^ wordartItem=mp_AppItem->Find("Energy");
									 HKCImageProp^ wordartProp;
									 HKCMedia* media = new HKCImage(mp_AppItem->Data->WordArtEvi.module_energy_map);	
									 //wordartItem = mp_AppItem->New(mp_AppItem->Data->WordArtEvi.module_energy_map, "Energy", mp_GLPanel);//Evaluation [Debug Use]
									 wordartItem->Update(media);
									 wordartProp = (HKCImageProp^)wordartItem->Prop;
									 wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
									 wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
									 wordartProp->Render->Visible = false;
								 }
							 }
							 */
							 
							 this->HKOGLPanel1->Trackball_Property->Move_Trigger->Mouse= System::Windows::Forms::MouseButtons::Right;
							 this->HKOGLPanel1->Trackball_Property->Delta_Res=200;
						 }

						 mp_GLPanel->Invalidate();
					  }
			 
	private: System::Void AppProcessCmd_Executed(System::Object^  sender, System::EventArgs^  e) {

				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();

				 if(System::String::Compare(action, L"PROCESSALL") == 0)
				 {
					  this->WordArt_Action("PROCESSALL");
				 }
			 }
	private: System::Void AppScalingToolUndoCmd_Executed(System::Object^  sender, System::EventArgs^  e) {

				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();

				 if(System::String::Compare(action, L"Undo") == 0&&mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.size()!=0)
				 {	
					 AppAlgoTextTyping	text_typing;
					 for (int i = 0 ; i < mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.size(); i++)
					 {
						mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines[i]->Release();
					 }
					 mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.clear();
					 QRWordArt::QRStringLines& splines = mp_AppItem->Data->WordArtEdt.temp_splines;
					 if (mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.size()==0)
					 {
						 AppAlgoTextColor	text_color(mp_AppItem);
						 AppAlgoTextAlign   text_align;
						 text_color.Enable((int)mp_AppItem->Param->WordArt->ColorMode);	
						 for (int i = 0 ; i <splines.size(); i ++)
						 {
							 QRWordArt::QRStringLine* newspline=new QRWordArt::QRStringLine;	
							 splines[i]->Duplicate(HSSSpline::Sample(0,0),HSSSpline::Sample(splines[i]->n_segs()-1,1),newspline);
							 newspline->Region()=splines[i]->Region();
							 HSSSpline::Sample cursor(0,0);
							 HSSSpline::Sample end(newspline->n_segs()-1,1);
							 for(int j  = 0 ; j <splines[i]->GetWords().size(); j++)
							 { 
								 if (text_typing.Typing(splines[i]->GetWords()[j],*newspline,cursor,end,&cursor,true))
								 {
									 text_typing. Typing_Space(*newspline,cursor,end,&cursor);
								 }
								 else
								 {
									 cout<<"fail"<<endl;
								 }								
								
							 }
							 mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.push_back(newspline);
							 if (i!=0)
							 {
								 newspline->LastLine(mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines[i-1]);
								 mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines[i-1]->NextLine(newspline);
							 }
							 text_align.Justify(*mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines[i]);
							 text_color.Execute(*mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines[i]);
						 }
						 mp_AppItem->Data->WordArtEdt.CanData.user_candidate.scaling_number=0;
					 }

					 mp_AppItem->Data->WordArtEdt.is_scaling=false;
					 mp_AppItem->Data->WordArtData[0].splines.clear();
					 for each(Node^ node in CandidateLayer->Nodes)
					 {
						 int nodeIdx = CandidateLayer->Nodes->IndexOf(node);
						 mp_AppItem->Candidates[nodeIdx]->Prop->Render->Visible = node->Checked;

						 if (node->Checked==true)
						 {
							 mp_AppItem->Data->WordArtEdt.is_scaling=true;
							 if (System::String::Compare(node->Name,"user define")==0)
							 {
								 mp_AppItem->Data->WordArtData[0].splines.insert(mp_AppItem->Data->WordArtData[0].splines.end(),mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.begin(),mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.end());
							 }
							 else
							 {
								 mp_AppItem->Data->WordArtData[0].splines.insert(mp_AppItem->Data->WordArtData[0].splines.end(),mp_AppItem->Data->WordArtEdt.CanData.candidates[stoi(MarshalString(node->Name))].splines.begin(),mp_AppItem->Data->WordArtEdt.CanData.candidates[stoi(MarshalString(node->Name))].splines.end());
							 }
						 }
					 }		
					 this->GLPanel_Refresh();
				 }
			 }
	private: System::Void AppBuildBigScaleCmd_Executed(System::Object^  sender, System::EventArgs^  e) {

				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();

				 if(System::String::Compare(action, L"SCALING") == 0)
				 {
					 this->WordArt_Action("SCALING");
				 }
			 }
	 private: System::Void AppErrorCorrectCmd_Executed(System::Object^  sender, System::EventArgs^  e) {

				  ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				  System::String^ action = cmdSrc->CommandParameter->ToString();

				  if(System::String::Compare(action, L"PROCESSALL") == 0)
				  {
					  this->MQRC_Action("PROCESSALL");
				  }
			  }
	private: System::Void AppFilterCmd_Executed(System::Object^  sender, System::EventArgs^  e) {

				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();

				 //this->Filter_Action(action);
			 }
	private: System::Void AppTestCmd_Executed(System::Object^  sender, System::EventArgs^  e) {

				 ICommandSource^ cmdSrc = static_cast<ICommandSource^>(sender);
				 System::String^ action = cmdSrc->CommandParameter->ToString();

				 if(System::String::Compare(action, L"TEST") == 0)
				 {
					this->MQRC_Action("BATCH");
				 }
				 else if(System::String::Compare(action, L"DEBUG") == 0)
				 {
					 this->MQRC_Action("TEST");
				 }
				 else if(System::String::Compare(action, L"DUMP") == 0)
				 {
					 this->MQRC_Action("EVALUATION");
				 }
				 else if(System::String::Compare(action, L"GENERATE") == 0)
				 {
					 
				 }
			 }	
private: System::Void QRRecBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			 this->MQRC_Action("RECOVER");
		 }

private: System::Void QRRecTextBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (QRRecTextBox->Text->Length!=0)
			 {
				 double confidence = (double)atof(MarshalString( QRRecTextBox->Text).c_str());
				 mp_AppItem->Data->QRCData.cw_error_thershold_confidence = confidence;
			 }
			
		 }
private: System::Void ScaleSlider_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 this->ScaleSlider->Text=L""+this->ScaleSlider->Value;
		 }
		 private:	System::Void ShowSingleLineEnergy()
					{
						int _select=mp_AppItem->Data->WordArtEdt.select;
						int _selectctrl=mp_AppItem->Data->WordArtEdt.select_ctrlpoint;
						QRWordArt::QRStringLines& splines = mp_AppItem->Data->WordArtData[0].splines;
						if (_select!=-1&&_selectctrl!=-1)
						{
// 							QRWordArt::QRStringLine* spline =splines[_select];
// 							AppAlgoVisaulEnergy visualenergy(mp_AppItem);
// 							AppAlgoTextEnergy   text_energy;
// 							double Es=visualenergy.EvaluateSingleLineSpace(splines,splines[_select]);
// 							double Ec=visualenergy.EvaluateFittingEdge(splines,-1);
// 							//double Et=text_energy.TextEnergy(*spline,0.5);
// 							cout<<"Es "<<Es<<" Ec "<<Ec<<endl;
// 							this->VisualQualitybar->Value=1000*(Es+Ec)/2;
// 							int int_value = (Es+Ec)/2*1000;
// 							double double_value = (double)int_value/1000;
// 							this->label1->Text=L"Visual Quality : "+ double_value;
						}
						else
						{
							this->VisualQualitybar->Value=0;
							this->label1->Text=L"Visual Quality : 0";
						}
					}
private: System::Void RegionParamChanged(System::Object^  sender, System::EventArgs^  e) {

			 if (this->AppItem->Data->WordArtEdt.select_region!=-1&&mp_AppItem->Data->WordArtEvi.region_params.size()!=0)
			 {
				 
				 BaseItem^  cmdSrc = static_cast<BaseItem^> (sender);
				 System::String^ name = cmdSrc->Name;
				 vector<RegionParam> & region_params = mp_AppItem->Data->WordArtEvi.region_params;
				 int region_select = this->AppItem->Data->WordArtEdt.select_region;
				 if (System::String::Compare(name, L"Rangesize") == 0)
				 {
					  region_params[region_select].RangeSize = System::Convert::ToDouble(sender->ToString());
				 }
				 else if (System::String::Compare(name, L"BoundaryA") == 0)
				 {
					 region_params[region_select].Boundary_Repela = System::Convert::ToDouble(sender->ToString());
				 }
				 else if(System::String::Compare(name, L"BoundaryB") == 0)
				 {
					  region_params[region_select].Boundary_Repelb = System::Convert::ToDouble(sender->ToString());
				 }
				 else if (System::String::Compare(name, L"LineA") == 0)
				 {
					  region_params[region_select].Line_Repela = System::Convert::ToDouble(sender->ToString());
				 }
				 else if (System::String::Compare(name, L"LineB") == 0)
				 {
					  region_params[region_select].Line_Repelb = System::Convert::ToDouble(sender->ToString());
				 }
			 }
		 }
private: System::Void RegionSmallRegionCheck(System::Object^  sender, DevComponents::DotNetBar::CheckBoxChangeEventArgs^  e) {
			 CheckBoxItem^  cmdSrc = static_cast<CheckBoxItem^> (sender);
			 System::String^ name = cmdSrc->Name;
			 vector<RegionParam> & region_params = mp_AppItem->Data->WordArtEvi.region_params;
			 if (this->AppItem->Data->WordArtEdt.select_region!=-1&&mp_AppItem->Data->WordArtEvi.region_params.size()!=0)
			 {
				 if(System::String::Compare(name, L"smallregioncheckbox") == 0)
				 {
					 region_params[this->AppItem->Data->WordArtEdt.select_region].smallregion =  cmdSrc->Checked;
				 }
			 }
		 }
private: System::Void TextOrderBtn_Click(System::Object^  sender, System::EventArgs^  e) {
			 if (TextOrderBtn->Checked==false)
			 {
				 //Release
				 mp_AppItem->Data->WordArtEdt.select=-1;
				 mp_AppItem->Data->WordArtEdt.select_word=-1;
				 mp_AppItem->Data->WordArtEdt.select_char=-1;
				 mp_AppItem->Data->WordArtEdt.select_record=-1;
				 mp_AppItem->Data->WordArtEdt.OrdEditingMode=false;

				 SeeLevelChange(2,true);
				 if(mp_AppItem->Data->IO_Handle.article_loaded)
				 {
					 for(int i = 0 ; i<mp_AppItem->Data->WordArtData[0].splines.size();i++)
					 {
						 mp_AppItem->Data->WordArtData[0].splines[i]->Release();
					 }
					 AppAlgoTextGeneration::Text_Record_Order = 0;
					 AppAlgoTextGeneration^ algoObj_TextGeneration = gcnew AppAlgoTextGeneration;
					 AppAlgoQRCodeEvaluation EnergyEvaluate;
					 algoObj_TextGeneration->TypeSet(mp_AppItem->Param->WordArt->TextType);
					 algoObj_TextGeneration->Execute(mp_AppItem);
					 EnergyEvaluate.Execute(mp_AppItem);
					 QRCInf_Action(QRcodeLabel,EnergyEvaluate);
					 QRenergyBar->Value=1000*(EnergyEvaluate.QRcodeQuality());
					 this->label2->Text=L"QR energy : 0."+ this->QRenergyBar->Value.ToString();
					 if(mp_AppItem->Find("Energy"))
					 {
						 HKCMediaItem^ wordartItem=mp_AppItem->Find("Energy");
						 HKCImageProp^ wordartProp;
						 HKCMedia* media = new HKCImage(mp_AppItem->Data->WordArtEvi.module_energy_map);	
						 //wordartItem = mp_AppItem->New(mp_AppItem->Data->WordArtEvi.module_energy_map, "Energy", mp_GLPanel);//Evaluation [Debug Use]
						 wordartItem->Update(media);
						 wordartProp = (HKCImageProp^)wordartItem->Prop;
						 wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
						 wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
						 wordartProp->Render->Visible = false;
					 }
				 }
			 }
			 else if (TextOrderBtn->Checked==true)
			 {
				 if (StringLineEdittingToolBtn->Checked==true||TextOrienBtn->Checked==true||TextBaseBtn->Checked==true)
				 {
					 TextOrderBtn->Checked=false;
					return;
				 }
				 mp_AppItem->Data->WordArtEdt.OrdEditingMode=true;
				 SeeLevelChange(5,true);
			 }
			 this->GLPanel_Refresh();
		 }
private: System::Void TextOrienBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		mp_AppItem->Data->WordArtEdt.ClearSelect();
		if (TextOrienBtn->Checked==false)
		{
			AppAlgoQRCodeEvaluation EnergyEvaluate;				 
			EnergyEvaluate.Execute(mp_AppItem);
			QRCInf_Action(QRcodeLabel,EnergyEvaluate);
			QRenergyBar->Value=1000*(EnergyEvaluate.QRcodeQuality());
			this->label2->Text=L"QR energy : 0."+ this->QRenergyBar->Value.ToString();
			if(mp_AppItem->Find("Energy"))
			{
				HKCMediaItem^ wordartItem=mp_AppItem->Find("Energy");
				HKCImageProp^ wordartProp;
				HKCMedia* media = new HKCImage(mp_AppItem->Data->WordArtEvi.module_energy_map);	
				//wordartItem = mp_AppItem->New(mp_AppItem->Data->WordArtEvi.module_energy_map, "Energy", mp_GLPanel);//Evaluation [Debug Use]
				wordartItem->Update(media);
				wordartProp = (HKCImageProp^)wordartItem->Prop;
				wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
				wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
				wordartProp->Render->Visible = false;
			}
		}
		else if (TextOrienBtn->Checked==true)
		{
			if (StringLineEdittingToolBtn->Checked==true||TextOrderBtn->Checked==true||TextBaseBtn->Checked==true)
			{
				TextOrienBtn->Checked=false;
				return;
			}
		}
		this->GLPanel_Refresh();
	}
private: System::Void TextBaseBtn_Click(System::Object^  sender, System::EventArgs^  e) {
		 if (TextBaseBtn->Checked==false)
		 {		 	
			 //Release
			 mp_AppItem->Data->WordArtEdt.ClearSelect();
			 mp_AppItem->Data->WordArtEdt.TextbaseEditingMode=false;

			 SeeLevelChange(2,true);
			 this->ribbonBar6->Visible=false;
			 if (mp_AppItem->Data->WordArtEdt.adjust_spline_id.size()!=0)
			 {
				 std::vector<int>& spline_idx = mp_AppItem->Data->WordArtEdt.adjust_spline_id;
				 for ( std::vector<int>::iterator it_1 = spline_idx.begin(); it_1!=spline_idx.end(); it_1++)
				 {
					 for (std::vector<int>::iterator it_2 = it_1+1; it_2!=spline_idx.end();)
					 {
						 if(*it_1 == *it_2){it_2 = spline_idx.erase(it_2);}
						 else{it_2++;}
					 }
				 }

				 AppAlgoTextGeneration^ algoObj_TextGeneration = gcnew AppAlgoTextGeneration;
				 AppAlgoQRCodeEvaluation EnergyEvaluate;
				 algoObj_TextGeneration->TypeSet(mp_AppItem->Param->WordArt->TextType);
				 algoObj_TextGeneration->TextGeneration(mp_AppItem,spline_idx,mp_AppItem->Data->WordArtEvi.candidate_strings);

				 EnergyEvaluate.Execute(mp_AppItem);
				 QRCInf_Action(QRcodeLabel,EnergyEvaluate);
				 QRenergyBar->Value=1000*(EnergyEvaluate.QRcodeQuality());
				 this->label2->Text=L"QR energy : 0."+ this->QRenergyBar->Value.ToString();
			 }			
		 }
		 else if (TextBaseBtn->Checked==true)
		 {
			 if (StringLineEdittingToolBtn->Checked==true||TextOrderBtn->Checked==true||TextOrienBtn->Checked==true)
			 {
				 TextBaseBtn->Checked=false;
				 return;
			 }
			 SeeLevelChange(4,true);
			 this->ribbonBar6->Visible=true;
			 this->ribbonBar6->Location.X=294;
			 mp_AppItem->Data->WordArtEdt.TextbaseEditingMode=true;
		 }
		 this->GLPanel_Refresh();
	}

private: System::Void TextcolorPick_SelectedColorChanged(System::Object^  sender, System::EventArgs^  e) {
			 int select = mp_AppItem->Data->WordArtEdt.select;
			 if ((StringLineEdittingToolBtn->Checked==false&&TextBaseBtn->Checked==false)||select==-1)return ;
			 
			 TextcolorPick->ForeColor = TextcolorPick->SelectedColor;
			  
			 int select_char = mp_AppItem->Data->WordArtEdt.select_char;
			 int select_word = mp_AppItem->Data->WordArtEdt.select_word;
			 if (select_char!=-1)
			 {
				 mp_AppItem->Data->WordArtData[0].splines[select]->GetQRSamples()[select_char]->qr_char->SetColor((double)TextcolorPick->ForeColor.R/(double)Byte::MaxValue,(double)TextcolorPick->ForeColor.G/(double)Byte::MaxValue,(double)TextcolorPick->ForeColor.B/(double)Byte::MaxValue);
			 }
			 else if (select_word!=-1)
			 {
				 for (int i  = 0 ;  i <mp_AppItem->Data->WordArtData[0].splines[select]->GetWordSamples()[select_word].size(); i++)
				 {
					 mp_AppItem->Data->WordArtData[0].splines[select]->GetWordSamples()[select_word][i]->qr_char->SetColor((double)TextcolorPick->ForeColor.R/(double)Byte::MaxValue,(double)TextcolorPick->ForeColor.G/(double)Byte::MaxValue,(double)TextcolorPick->ForeColor.B/(double)Byte::MaxValue);
				 }
			 }
			 else
			 {
				 for (int i  = 0;  i <mp_AppItem->Data->WordArtData[0].splines[select]->GetQRSamples().size(); i++)
				 {
					 mp_AppItem->Data->WordArtData[0].splines[select]->GetQRSamples()[i]->qr_char->SetColor((double)TextcolorPick->ForeColor.R/(double)Byte::MaxValue,(double)TextcolorPick->ForeColor.G/(double)Byte::MaxValue,(double)TextcolorPick->ForeColor.B/(double)Byte::MaxValue);
				 }
			 }
			 this->GLPanel_Refresh();
		 }
private: System::Void SeeLevelCheck_Check(System::Object^  sender, System::EventArgs^  e) {
			if (System::String::Compare(sender->ToString(), L"QRcode") == 0){
				SeeLevelChange(1,SeeLevelCheck1->Checked);
			}else if (System::String::Compare(sender->ToString(), L"WordArt") == 0){
				SeeLevelChange(2,SeeLevelCheck2->Checked);
			}else if (System::String::Compare(sender->ToString(), L"Energy") == 0){
				SeeLevelChange(3,SeeLevelCheck3->Checked);
			}else{
				SeeLevelChange(2,true);
			}
		 }
private: System::Void ScalingToolBtn_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 mp_AppItem->Data->WordArtEdt.ScalingEditingMode = this->ScalingToolBtn->Checked;
		 }
private: System::Void RSModCheckBox_CheckedChanged(System::Object^  sender, DevComponents::DotNetBar::CheckBoxChangeEventArgs^  e) {
			 mp_AppItem->Data->IO_Handle.rs_control = RSModCheckBox->Checked;
		 }
private: System::Void CurveWarpCheckBox_CheckedChanged(System::Object^  sender, DevComponents::DotNetBar::CheckBoxChangeEventArgs^  e) {
			 mp_AppItem->Data->IO_Handle.sw_control = CurveWarpCheckBox->Checked;
		 }
private: System::Void CharWarpCheckBox_CheckedChanged(System::Object^  sender, DevComponents::DotNetBar::CheckBoxChangeEventArgs^  e) {
			 mp_AppItem->Data->IO_Handle.cw_control = CharWarpCheckBox->Checked;
		 }
private: System::Void IslandModuleCheckBox_CheckedChanged(System::Object^  sender, DevComponents::DotNetBar::CheckBoxChangeEventArgs^  e) {
			 mp_AppItem->Data->IO_Handle.im_control = IslandModuleCheckBox->Checked;
		 }
private: System::Void BoldDeformCheckBox_CheckedChanged(System::Object^  sender, DevComponents::DotNetBar::CheckBoxChangeEventArgs^  e) {
		 }
private: System::Void sliderItem1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			
			 int select = mp_AppItem->Data->WordArtEdt.select;
			 int select_char = mp_AppItem->Data->WordArtEdt.select_char;
			  this->sliderItem1->Text=L""+(double)(this->sliderItem2->Value)/10;
			 if (select_char==-1)
			 {
				 return;
			 }
			
			 double r,g,b;
			 //mp_AppItem->Data->WordArtData[0].splines[select]->GetQRSamples()[select_char]->qr_char->GetColor(&r,&g,&b);
			 cv::Point3d rgb= mp_AppItem->Data->WordArtEdt.selectcolor;
			 r=rgb.x;
			 g=rgb.y;
			 b=rgb.z;
			 cv::Mat m = cv::Mat(1,1,CV_8UC3,cv::Scalar(r*255,g*255,b*255));
			 cv::cvtColor(m,m,CV_RGB2Lab);
			 double le,lb;
			 le=(double)this->sliderItem1->Value/10;lb=(double)this->sliderItem2->Value;
			 cv::Vec3d s=m.at<cv::Vec3b>(0,0);
			 s[0]=s[0]*le+lb;
			 //s[0]=100<s[0]?100:s[0];
			 s[0]=0>s[0]?0:s[0];
			 m.at<cv::Vec3b>(0,0)=s;
			 cout<<(int)m.data[0]<<endl;
			 cv::cvtColor(m,m,CV_Lab2RGB);
			 r=(double)m.data[0]/255;
			 g=(double)m.data[1]/255;
			 b=(double)m.data[2]/255;
			 mp_AppItem->Data->WordArtData[0].splines[select]->GetQRSamples()[select_char]->qr_char->SetColor(r,g,b);
			 mp_GLPanel->Invalidate();
		 }
private: System::Void sliderItem2_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 int select = mp_AppItem->Data->WordArtEdt.select;
			 int select_char = mp_AppItem->Data->WordArtEdt.select_char;
			  this->sliderItem2->Text=L""+this->sliderItem2->Value;
			 if (select_char==-1)
			 {
				 return;
			 }
			
			 double r,g,b;
			 //mp_AppItem->Data->WordArtData[0].splines[select]->GetQRSamples()[select_char]->qr_char->GetColor(&r,&g,&b);
			 cv::Point3d rgb= mp_AppItem->Data->WordArtEdt.selectcolor;
			 r=rgb.x;
			 g=rgb.y;
			 b=rgb.z;
			 cv::Mat m = cv::Mat(1,1,CV_8UC3,cv::Scalar(r*255,g*255,b*255));
			 cv::cvtColor(m,m,CV_RGB2Lab);
			 double le,lb;
			 le=(double)this->sliderItem1->Value/10;lb=this->sliderItem2->Value;
			 cv::Vec3d s=m.at<cv::Vec3b>(0,0);
			 s[0]=s[0]*le+lb;
			 //s[0]=100<s[0]?100:s[0];
			 s[0]=0>s[0]?0:s[0];
			 m.at<cv::Vec3b>(0,0)=s;
			 cout<<(int)m.data[0]<<endl;
			 cv::cvtColor(m,m,CV_Lab2RGB);
			 r=(double)m.data[0]/255;
			 g=(double)m.data[1]/255;
			 b=(double)m.data[2]/255;
			 mp_AppItem->Data->WordArtData[0].splines[select]->GetQRSamples()[select_char]->qr_char->SetColor(r,g,b);
			 mp_GLPanel->Invalidate();
		 }
};
}