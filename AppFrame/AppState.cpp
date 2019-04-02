/**
* @file AppState.cpp
*
* Implementation of the class methods for application state
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "Form1.h"
#include "AppState.h"

using namespace AppFrame;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/*! \class AppFrame::HKCAppState

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
cv::Point2i HKCAppState::MousePos = cv::Point2i(0, 0);

/*---------------------------------------------------------------------*/
/*                             Operations                              */
/// Panel mouse down event
void HKCAppState::Panel_MouseDown(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	MousePos = cv::Point2i(_e->X, _panel->Height-_e->Y);

	/// Activate the selected GLPanel
	_form->GLPanel_Activate(_panel);
}

/// Panel mouse move event
void HKCAppState::Panel_MouseMove(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	if(_panel->is_Moving() || _panel->is_Rotating())
	{
		if(_form->has_Sync)
		{
			/// Synchronize OpenGL panels
			_form->GLPanel_Sync(_panel);		
		}
	}	

	MousePos = cv::Point2i(_e->X, _panel->Height-_e->Y);
}

/// Panel mouse up event
void HKCAppState::Panel_MouseUp(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	MousePos = cv::Point2i(_e->X, _panel->Height-_e->Y);
}

/// Panel mouse wheel event
void HKCAppState::Panel_MouseWheel(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	if(_panel->is_Zooming())
	{		
		if(_form->has_Sync)
		{
			/// Synchronize OpenGL panels
			_form->GLPanel_Sync(_panel);	
		}
	}		
}

/// Panel key down event
void HKCAppState::Panel_KeyDown(Form1^ _form, HKOGLPanelControl^ _panel, KeyEventArgs^ _e)
{	 	
	KeyDown = true;
	KeyCode	= _e->KeyCode;
	KeyMod	= _e->Modifiers;
}

/// Panel key up event
void HKCAppState::Panel_KeyUp(Form1^ _form, HKOGLPanelControl^ _panel, KeyEventArgs^ _e)
{
	KeyDown = false;
}