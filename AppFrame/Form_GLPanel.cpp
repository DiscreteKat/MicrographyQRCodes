/**
* @file Form_GLPanel.cpp
*
* Implementation of GLPanel control functions
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "StdAfx.h"
#include "Form1.h"

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
/*                    GLPanel control functions                        */
/// Activate GLPanel control
void Form1::GLPanel_Activate(HKOGLPanelControl^ _panel) 
{
	if(!_panel) return;

	/// Check if _panel exists in mp_GLPanels
	if(!mp_GLPanels->Contains(_panel))
	{
		Console::WriteLine("Form1::GLPanel_Activate() : _panel dosen't exist in mp_GLPanels");
		return;
	}

	/// if exist, make it the current GLPanel
	if(mp_GLPanel) mp_GLPanel->Make_NotCurrent();
	mp_GLPanel = _panel;
	mp_GLPanel->Make_Current();
	mp_GLPanel->Invalidate();	
}

/// Focus on a application item
void Form1::GLPanel_Focus(HKCAppItem^ _appItem)
{
	if(!_appItem || AppPinBtn->Checked) return;

	HKCMediaItem^ item = _appItem->Item;
	if(item->Media && item->glContext)
	{
		vector<cv::Point3d> aabb = item->Media->AABB();
		item->glContext->Make_Current();		
		item->glContext->Focus(aabb[0].x, aabb[0].y, aabb[0].z, aabb[1].x, aabb[1].y, aabb[1].z);
		item->glContext->Refresh();
	}	
}

/// Synchronize GLPanel
void Form1::GLPanel_Sync(HKOGLPanelControl^ _panel)
{
	for each(HKOGLPanelControl^ glPanel in mp_GLPanels)
	{		
		if(glPanel != _panel)		
		{
			glPanel->Make_Current();
			glPanel->Synchronize(_panel);		
			glPanel->Invalidate();
		}
	}	
}

/// Refresh all GLPanels
void Form1::GLPanel_Refresh(void)
{
	for each(HKOGLPanelControl^ glPanel in mp_GLPanels)
	{
		glPanel->Refresh();
	}
}

/// Add new GLPanel control
HKOGLPanelControl^ Form1::GLPanel_Add(void) 
{ 
	/// How many GLPanels do we have now?
	Int32 curIdx = mp_GLPanels->Count+1;

	/// Create new instance for GLPanel
	HKCCameraProp^		hkcCameraProp = (gcnew HKOGLPanel::HKCCameraProp());
	HKCDisplayProp^		hkcDisplayProp = (gcnew HKOGLPanel::HKCDisplayProp());
	HKCPixelFormat^		hkcPixelFormat = (gcnew HKOGLPanel::HKCPixelFormat());
	HKCTrackballProp^	hkcTrackballProp = (gcnew HKOGLPanel::HKCTrackballProp());
	HKCTrackballTrig^	hkcTrackballTrig1 = (gcnew HKOGLPanel::HKCTrackballTrig());
	HKCTrackballTrig^	hkcTrackballTrig2 = (gcnew HKOGLPanel::HKCTrackballTrig());
	HKCTrackballTrig^	hkcTrackballTrig3 = (gcnew HKOGLPanel::HKCTrackballTrig());
	HKOGLPanelControl^	newGLPanel = (gcnew HKOGLPanel::HKOGLPanelControl());

	/// Create new instance for DotNetBar
	DockContainerItem^  newDockCntrItem = (gcnew DevComponents::DotNetBar::DockContainerItem());
	PanelDockContainer^	newDockCntrPanel = (gcnew DevComponents::DotNetBar::PanelDockContainer());

	/// Find the dock document
	DockSite^ dockSite = DotNetBarManager->FillDockSite;
	Bar^ dockBar = dynamic_cast<Bar^>(dockSite->Controls[0]);

	dockSite->SuspendLayout();
	dockBar->SuspendLayout();
	newDockCntrPanel->SuspendLayout();
	this->SuspendLayout();

	// 
	// dockBar
	//
	dockBar->Controls->Add(newDockCntrPanel);
	dockBar->Items->Add(newDockCntrItem);

	// 
	// newDockCntrPanel
	// 
	newDockCntrPanel->ColorSchemeStyle = DevComponents::DotNetBar::eDotNetBarStyle::Windows7;
	//newDockCntrPanel->Controls->Add(this->AppCntxMenuBar);
	newDockCntrPanel->Controls->Add(newGLPanel);
	newDockCntrPanel->Location = System::Drawing::Point(3, 28);
	//newDockCntrPanel->Name = L"DockCntrPanel1";
	newDockCntrPanel->Size = System::Drawing::Size(706, 381);
	newDockCntrPanel->Style->Alignment = System::Drawing::StringAlignment::Center;
	newDockCntrPanel->Style->BackColor1->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground;
	newDockCntrPanel->Style->BackColor2->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarBackground2;
	newDockCntrPanel->Style->BorderColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::BarDockedBorder;
	newDockCntrPanel->Style->ForeColor->ColorSchemePart = DevComponents::DotNetBar::eColorSchemePart::ItemText;
	newDockCntrPanel->Style->GradientAngle = 90;
	//newDockCntrPanel->TabIndex = 0;

	// 
	// HKOGLPanel1
	// 
	newGLPanel->AllowDrop = true;
	hkcCameraProp->Enabled = true;
	hkcCameraProp->Far = 1000;
	hkcCameraProp->Fov = 45;
	hkcCameraProp->Near = -1000;
	hkcCameraProp->Type = HKOGLPanel::HKCCameraProp::CAMERATYPE::PERSPECTIVE;
	hkcCameraProp->Zoom = 1;
	newGLPanel->Camera_Property = hkcCameraProp;
	hkcDisplayProp->Back_Color = System::Drawing::Color::White;
	hkcDisplayProp->Grid_Axis = System::Drawing::Color::Black;
	hkcDisplayProp->Grid_Draw = false;
	hkcDisplayProp->Grid_Line = System::Drawing::Color::DimGray;
	newGLPanel->Display_Property = hkcDisplayProp;
	//newGLPanel->Dock = System::Windows::Forms::DockStyle::Fill;
	newGLPanel->Empty_Panel = false;
	newGLPanel->Location = System::Drawing::Point(0, 0);
	newGLPanel->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
	newGLPanel->Name = L"HKOGLPanel"+curIdx.ToString();
	hkcPixelFormat->Accumu_Buffer_Bits = HKOGLPanel::HKCPixelFormat::PIXELBITS::BITS_0;
	hkcPixelFormat->Alpha_Buffer_Bits = HKOGLPanel::HKCPixelFormat::PIXELBITS::BITS_32;
	hkcPixelFormat->Stencil_Buffer_Bits = HKOGLPanel::HKCPixelFormat::PIXELBITS::BITS_0;
	newGLPanel->Pixel_Format = hkcPixelFormat;
	//newGLPanel->Size = System::Drawing::Size(706, 381);
	//newGLPanel->TabIndex = 0;
	hkcTrackballProp->Const_Res = false;
	hkcTrackballProp->Delta_Res = 200;
	hkcTrackballProp->Enabled = true;
	hkcTrackballProp->Move_Res = 100;
	hkcTrackballTrig1->Key_Down = false;
	hkcTrackballTrig1->Keyboard = System::Windows::Forms::Keys::None;
	hkcTrackballTrig1->Mouse = System::Windows::Forms::MouseButtons::Right;
	hkcTrackballTrig1->Mouse_Down = false;
	hkcTrackballProp->Move_Trigger = hkcTrackballTrig1;
	hkcTrackballTrig2->Key_Down = false;
	hkcTrackballTrig2->Keyboard = System::Windows::Forms::Keys::None;
	hkcTrackballTrig2->Mouse = System::Windows::Forms::MouseButtons::None;
	hkcTrackballTrig2->Mouse_Down = false;
	hkcTrackballProp->Rotate_Trigger = hkcTrackballTrig2;
	hkcTrackballProp->Zoom_Res = 100;
	hkcTrackballTrig3->Key_Down = false;
	hkcTrackballTrig3->Keyboard = System::Windows::Forms::Keys::None;
	hkcTrackballTrig3->Mouse = System::Windows::Forms::MouseButtons::Middle;
	hkcTrackballTrig3->Mouse_Down = false;
	hkcTrackballProp->Zoom_Trigger = hkcTrackballTrig3;
	newGLPanel->Trackball_Property = hkcTrackballProp;
	newGLPanel->Load += gcnew System::EventHandler(this, &Form1::OGLPanel_Load);
	newGLPanel->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::OGLPanel_DragDrop);
	newGLPanel->DragEnter += gcnew System::Windows::Forms::DragEventHandler(this, &Form1::OGLPanel_DragEnter);
	newGLPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::OGLPanel_Paint);
	newGLPanel->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::OGLPanel_KeyDown);
	newGLPanel->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::OGLPanel_KeyUp);
	newGLPanel->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::OGLPanel_MouseDown);
	newGLPanel->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::OGLPanel_MouseMove);
	newGLPanel->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::OGLPanel_MouseUp);
	newGLPanel->MouseWheel += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::OGLPanel_MouseWheel);
	newGLPanel->Resize += gcnew System::EventHandler(this, &Form1::OGLPanel_Resize);
	// 
	// DockCntrItem1
	// 
	newDockCntrItem->Control = newDockCntrPanel;
	//newDockCntrItem->Name = L"DockCntrItem1";
	newDockCntrItem->Text = L"Display " + curIdx.ToString();

	dockSite->ResumeLayout(false);
	(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(dockBar))->EndInit();
	dockBar->ResumeLayout(false);
	newDockCntrPanel->ResumeLayout(false);
	this->ResumeLayout(false); 

	/// Add new GLPanel control to list	
	newGLPanel->Make_Current();
	newGLPanel->Camera_Property->Type = HKOGLPanel::HKCCameraProp::CAMERATYPE::ORTHOGRAPHIC;	
	newGLPanel->Look_At(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
//	newGLPanel->Dock = System::Windows::Forms::DockStyle::Fill;	


	mp_GLPanels->Add(newGLPanel);		
	
	return newGLPanel;
}		
