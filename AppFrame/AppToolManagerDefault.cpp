/**
* @file AppToolManagerDefault.cpp
*
* Implementation of the class methods for default tool manager
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "Form1.h"

using namespace AppFrame;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::HKCToolMgrDef

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCToolMgrDef::HKCToolMgrDef(void) 
{	
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCToolMgrDef::~HKCToolMgrDef(void)
{		
}

/*---------------------------------------------------------------------*/
/*                             Operations                              */
/// Toggle tool
void HKCToolMgrDef::Toggle(System::String^ _label, bool _flag, HKCAppItem^ _appItem, Form1^ _form)
{
	/// Deactivate non used tools
	for each(HKCAppTool^ tool in mp_Tools)
	{
		if(System::String::Compare(tool->Label, _label) != 0)
			tool->DeActivate(_appItem);		
	}

	/// Toggle target tool
	for each(HKCAppTool^ tool in mp_Tools)
	{		
		if(System::String::Compare(tool->Label, _label) == 0)
		{			
			if(_flag) tool->Activate(_appItem);
			else tool->DeActivate(_appItem);
		}		
	}
}

/// Perform tool's action
void HKCToolMgrDef::Action(System::String^ _label, System::String^ _action, HKCAppItem^ _appItem, Form1^ _form)
{
	HKCAppTool^ tool = Find(_label);
	if(!tool) return;

	/// Perform tool's action
	tool->Action(_action, _appItem);
}

/// Update tool's property
void HKCToolMgrDef::Update(HKCAppItem^ _appItem, Form1^ _form)
{	
	if(!_appItem->Item) return;

	/// Get the selected media item
	HKCMediaItem^ item = _appItem->Item;
	HKCMedia* media = item->Media;

	/// Update media player's properties
	HKCAppTool^ mplayer = Find(AppGlobal::g_MPlyrLabel);
	if(mplayer)
	{
		HKCMPlyrProp^ prop = dynamic_cast<HKCMPlyrProp^>(mplayer->Prop);
		prop->FPS = media->FPS();
		_form->PlayerFrameSliderMaximum = (int)(media->Frame_Count()-1);
		_form->PlayerSpeedSliderValue = 0;
		_form->PlayerSpeedSliderValue = 50;
	}
}
