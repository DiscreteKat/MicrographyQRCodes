/**
* @file AppStateIdle.cpp
*
* Implementation of the class methods for idle state
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "Form1.h"
#include "AppUtils.h"
#include "AppState.h"

using namespace AppFrame;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/*! \class AppFrame::HKCStateIdle

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
template<> HKCStateIdle*	HKCSingleton<HKCStateIdle>::mp_Instance = NULL;

/*---------------------------------------------------------------------*/
/*                             Operations                              */
/// Panel mouse down event
void HKCStateIdle::Panel_MouseDown(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	/// Call base event
	HKCAppState::Panel_MouseDown(_form, _panel, _e);	
}

/// Panel key down event
void HKCStateIdle::Panel_KeyDown(Form1^ _form, HKOGLPanelControl^ _panel, KeyEventArgs^ _e)
{
	/// Call base event
	HKCAppState::Panel_KeyDown(_form, _panel, _e);		
}