/**
* @file Form_Tool.cpp
*
* Implementation of Tool control functions
*
* @author James Hung-Kuo Chu
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
/*                      Tool control functions                         */
/// Toggle tool's ratio button
void Tool_RatioBtn(cli::array<ButtonItem^>^ _btns, cli::array<System::String^>^ _labels, System::String^ _label, bool _autoCheck)
{	
	if(Array::IndexOf(_labels, _label) == -1) return;
	for each(ButtonItem^ btn in _btns)
	{
		if(System::String::Compare(btn->CommandParameter->ToString(), _label) != 0)
			btn->Checked = false;
		else if(!_autoCheck)
			btn->Checked = true;
	}
}

/// Toggle tool
void Form1::Tool_Toggle(System::String^ _label)
{
	/// Toggle toolbar buttons
	cli::array<ButtonItem^>^ btns = { this->AppPaintBtn, this->AppGCBtn };	
	cli::array<System::String^>^ labels = { AppGlobal::g_PntrLabel, AppGlobal::g_GCLabel, AppGlobal::g_XFormLabel };	
	Tool_RatioBtn(btns, labels, _label, true);

	if(System::String::Compare(_label, AppGlobal::g_PntrLabel) == 0)
	{		
		/// Toggle tool
		mp_AppToolMgr->Toggle(AppGlobal::g_PntrLabel, AppPaintBtn->Checked, mp_AppItem, this);
		
		if(AppPaintBtn->Checked)
		{
			/// Set state to painting state
			this->AppState = HKCStatePaint::InstancePtr();

			/// Set painter's context menu
			for each(HKOGLPanelControl^ glPanel in mp_GLPanels)		
				AppCntxMenuBar->SetContextMenuEx(glPanel, this->PntrCntxMenu);	

			/// Set default stroke
			Tool_Action(AppGlobal::g_PntrLabel, "STROKE_BRUSH");
		}
		else
		{
			// Set state to idle state
			this->AppState = HKCStateIdle::InstancePtr();

			/// Null context menu
			for each(HKOGLPanelControl^ glPanel in mp_GLPanels)		
				AppCntxMenuBar->SetContextMenuEx(glPanel, nullptr);
		}

		/// Rebuild layers
		mp_AppLayerMgr->Build(this->LayerTree, mp_AppItem);
	}
	else if(System::String::Compare(_label, AppGlobal::g_GCLabel) == 0)
	{
		/// Toggle tool
		mp_AppToolMgr->Toggle(AppGlobal::g_GCLabel, AppGCBtn->Checked, mp_AppItem, this);

		if(AppGCBtn->Checked)
		{
			/// Set state to GrabCut state
			this->AppState = HKCStateGC::InstancePtr();

			/// Set GrabCut's context menu
			for each(HKOGLPanelControl^ glPanel in mp_GLPanels)		
				AppCntxMenuBar->SetContextMenuEx(glPanel, this->GCCntxMenu);	

			/// Set default stroke
			Tool_Action(AppGlobal::g_GCLabel, "STROKE_FGD");
		}
		else
		{
			// Set state to idle state
			this->AppState = HKCStateIdle::InstancePtr();

			/// Null context menu
			for each(HKOGLPanelControl^ glPanel in mp_GLPanels)		
				AppCntxMenuBar->SetContextMenuEx(glPanel, nullptr);
		}

		/// Rebuild layers
		mp_AppLayerMgr->Build(this->LayerTree, mp_AppItem);
	}
	else if(System::String::Compare(_label, AppGlobal::g_XFormLabel) == 0)
	{
		/// Toggle tool
		mp_AppToolMgr->Toggle(AppGlobal::g_XFormLabel, true, mp_AppItem, this);	

		/// Rebuild layers
		mp_AppLayerMgr->Build(this->LayerTree, mp_AppItem);
	}	
}

/// Response tool's action
void Form1::Tool_Action(System::String^ _label, System::String^ _action)
{
	if(System::String::Compare(_label, AppGlobal::g_PntrLabel) == 0)
	{
		/// Actions that will activate/deactivate the tool
		cli::array<System::String^>^ triggers = { AppPaintBtn->CommandParameter->ToString() };

		if(Array::IndexOf(triggers, _action) != -1)		
		{
			/// Toggle tool
			this->Tool_Toggle(AppGlobal::g_PntrLabel);
		}
		else
		{
			/// Perform tool's action
			mp_AppToolMgr->Action(_label, _action, mp_AppItem, this);

			/// Toggle toolbar buttons
			cli::array<ButtonItem^>^ btns = { this->PntrErasBtn, this->PntrBrshBtn, this->PntrMErasBtn, this->PntrMBrshBtn };	
			cli::array<System::String^>^ labels = { this->PntrErasBtn->CommandParameter->ToString(), this->PntrBrshBtn->CommandParameter->ToString() };	
			Tool_RatioBtn(btns, labels, _action, false);			
		}
	}
	else if(System::String::Compare(_label, AppGlobal::g_GCLabel) == 0)
	{
		/// Actions that will activate/deactivate the tool
		cli::array<System::String^>^ triggers = { AppGCBtn->CommandParameter->ToString() };

		if(Array::IndexOf(triggers, _action) != -1)		
		{
			/// Toggle tool
			this->Tool_Toggle(AppGlobal::g_GCLabel);
		}
		else
		{
			/// Perform tool's action
			mp_AppToolMgr->Action(_label, _action, mp_AppItem, this);	

			if(System::String::Compare("RESET", _action) == 0)
			{
				this->GCFGDBtn->Checked = true;
				this->GCMFGDBtn->Checked = true;
				this->GCBrshBtn->Image = this->GCFGDBtn->Image;
			}

			/// Toggle toolbar and brush buttons
			cli::array<ButtonItem^>^ tBtns = { this->GCBrshBtn, this->GCErasBtn, this->GCMErasBtn };	
			cli::array<System::String^>^ tLabels = { this->GCBrshBtn->CommandParameter->ToString(), this->GCErasBtn->CommandParameter->ToString() };	
			cli::array<ButtonItem^>^ bBtns = { this->GCFGDBtn, this->GCBGDBtn, this->GCPRFGDBtn, this->GCPRBGDBtn, this->GCMskBBtn, this->GCMskWBtn, 
				this->GCMFGDBtn, this->GCMBGDBtn, this->GCMPRFGDBtn, this->GCMPRBGDBtn, this->GCMMskBBtn, this->GCMMskWBtn };
			cli::array<System::String^>^ bLabels = { this->GCFGDBtn->CommandParameter->ToString(), this->GCBGDBtn->CommandParameter->ToString(), this->GCPRFGDBtn->CommandParameter->ToString(),
				this->GCPRBGDBtn->CommandParameter->ToString(), this->GCMskBBtn->CommandParameter->ToString(), this->GCMskWBtn->CommandParameter->ToString() };
			
			Tool_RatioBtn(tBtns, tLabels, _action, false);
			Tool_RatioBtn(bBtns, bLabels, _action, false);

			for each(ButtonItem^ btn in bBtns)
			{
				if(System::String::Compare(btn->CommandParameter->ToString(), _action) == 0)
				{		
					this->GCBrshBtn->Checked = btn->Checked;					
					this->GCBrshBtn->Image = btn->Image;
					break;
				}					
			}	

			if(System::String::Compare(this->GCBrshBtn->CommandParameter->ToString(), _action) == 0)
			{
				ButtonItem^ brshBtn = nullptr;
				for each(ButtonItem^ btn in bBtns)
					if(btn->Checked) brshBtn = btn;

				if(brshBtn)
					Tool_Action(AppGlobal::g_GCLabel, brshBtn->CommandParameter->ToString());
			}
		}
	}
	else if(System::String::Compare(_label, AppGlobal::g_XFormLabel) == 0)
	{
		/// Actions that will activate/deactivate the tool
		cli::array<System::String^>^ triggers = { XFormCropBtn->CommandParameter->ToString(), XFormMirBtn->CommandParameter->ToString(),
		                                          XFormMovBtn->CommandParameter->ToString(), XFormRotBtn->CommandParameter->ToString(),
		                                          XFormScalBtn->CommandParameter->ToString() };

		int actIdx = Array::IndexOf(triggers, _action);
		if(actIdx != -1)		
		{
			/// Toggle tool
			this->Tool_Toggle(AppGlobal::g_XFormLabel);
		}

		/// Perform tool's action
		mp_AppToolMgr->Action(_label, _action, mp_AppItem, this);				

		switch(actIdx)
		{
		case 0:
			// Set state to idle state
			this->AppState = HKCStateIdle::InstancePtr();
			break;
		case 2:
			// Set state to moving state
			this->AppState = HKCStateMove::InstancePtr();
			break;
		case 3:
			// Set state to rotating state
			this->AppState = HKCStateRotate::InstancePtr();
			break;
		case 4:
			// Set state to scaling state
			this->AppState = HKCStateScale::InstancePtr();
			break;
		}

		if(System::String::Compare(_action, this->XFormCropBtn->CommandParameter->ToString()) != 0)
		{			
			/// Delete unnecessary layers and rebuild the layer
			mp_AppItem->DeleteEx(gcnew cli::array<System::String^>(2) {"QRCode", "Source"});			
			mp_AppLayerMgr->Build(this->LayerTree, mp_AppItem);
			mp_GLPanel->Invalidate();
		}
		else
		{	
			//Filter_Action("");
		}

		/// Null context menu
		for each(HKOGLPanelControl^ glPanel in mp_GLPanels)		
			AppCntxMenuBar->SetContextMenuEx(glPanel, nullptr);

		/// Toggle toolbar buttons		
		cli::array<ButtonItem^>^ btns = { this->XFormMovBtn, this->XFormRotBtn, this->XFormScalBtn };	
		cli::array<System::String^>^ labels = { this->XFormMovBtn->CommandParameter->ToString(), this->XFormRotBtn->CommandParameter->ToString(), this->XFormScalBtn->CommandParameter->ToString() };	
		if(actIdx == 0) for each(ButtonItem^ btn in btns) btn->Checked = false;		
		else Tool_RatioBtn(btns, labels, _action, false);			
	}
}