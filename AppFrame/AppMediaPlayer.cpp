/**
* @file AppMediaPlayer.cpp
*
* Implementation of the class methods for media player tool
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "AppProperty.h"
#include "AppItem.h"
#include "AppTool.h"
#include "AppMediaPlayer.h"

using namespace AppFrame;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::HKCMPlayer

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
/// Constructor
HKCMPlayer::HKCMPlayer(System::String^ _label) : HKCAppTool(_label, gcnew HKCMPlyrProp)
{		
	mp_MPlyrProp = dynamic_cast<HKCMPlyrProp^>(mp_Prop);
}

HKCMPlayer::HKCMPlayer(System::String^ _label, HKCToolProp^ _prop) : HKCAppTool(_label, _prop)
{	
	mp_MPlyrProp = dynamic_cast<HKCMPlyrProp^>(mp_Prop);
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
/// Destructor
HKCMPlayer::~HKCMPlayer(void)
{	
}

/*---------------------------------------------------------------------*/
/*                          Tool Operations                            */
/// Activate media player
bool HKCMPlayer::Activate(HKCAppItem^ _appItem)
{			
	/// Enable the tool
	mp_MPlyrProp->Enabled = true;	

	return true;
}

/// Deactivate media player
bool HKCMPlayer::DeActivate(HKCAppItem^ _appItem)
{	
	/// Disable the tool
	mp_MPlyrProp->Enabled = false;	

	return true;
}

/// Media player's action
bool HKCMPlayer::Action(System::String^ _act, HKCAppItem^ _appItem)
{
	if(!_appItem || !_appItem->Item) return false;
	
	/// Get the selected media item
	HKCMediaItem^ item = _appItem->Item;
	HKCMedia* media = item->Media;
	if(media->Type() != VIDEO) return false;

	string act = MarshalString(_act);
	bool flag;

	item->glContext->Make_Current();

	if(System::String::Compare(_act, L"GOTO") == 0)
		flag = media->Goto_Frame(mp_MPlyrProp->Frame);
	else
	{
		flag = media->Playback(act, *(mp_MPlyrProp->Param));		
		if(!flag)
		{
			if(mp_MPlyrProp->Repeat)
				flag = media->Playback("START", *(mp_MPlyrProp->Param));
			else
				mp_MPlyrProp->Enabled = false;
		}		
	}

	item->glContext->Invalidate();

	/// Update media player's properties
	mp_MPlyrProp->Frame = (int)media->Frame_Index();	
	

	return true;
}