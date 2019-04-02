/**
* @file AppStatePaint.cpp
*
* Implementation of the class methods for painting state
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

/*! \class AppFrame::HKCStatePaint

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
template<> HKCStatePaint*	HKCSingleton<HKCStatePaint>::mp_Instance = NULL;

/*---------------------------------------------------------------------*/
/*                            Constructor                              */
/// Constructor
HKCStatePaint::HKCStatePaint(void)
{
	m_State = HKEPaintS::IDLE;	
}

/*---------------------------------------------------------------------*/
/*                             Operations                              */
/// Panel mouse down event
void HKCStatePaint::Panel_MouseDown(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	HKCAppState::Panel_MouseDown(_form, _panel, _e);	
		
	switch(_e->Button)
	{
	case Windows::Forms::MouseButtons::Left:
		{
			m_State = HKEPaintS::PAINTING;	
			_panel->Invalidate();
		}															 											 						 
		break;
	}
}

/// Panel mouse move event
void HKCStatePaint::Panel_MouseMove(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	cv::Point2i preMouse = MousePos;
	HKCAppState::Panel_MouseMove(_form, _panel, _e);	

	HKCPainter^ painter = (HKCPainter^)(_form->ToolManager->Find(AppGlobal::g_PntrLabel));
	if(!painter) return;
	painter->Cursor = &CoordCvt_Scr2Wrd(MousePos);

	switch(m_State)
	{
	case HKEPaintS::PAINTING:
		{			
			HKCMediaItem^ cnvsItem = _form->AppItem->Find("Painter Canvas");
			if(cnvsItem)
			{
				cv::Point2i curMouse = MousePos;
				cv::Point2d prePnt, curPnt;			

				cv::Mat* canvas = (cv::Mat*)(cnvsItem->Media->Data());
				cv::Size cnvsSize = canvas->size();
				cv::Rect cnvsRect(0, 0, cnvsSize.width, cnvsSize.height);

				cnvsItem->glContext->Make_Current();
				prePnt = CoordCvt_Scr2Img(preMouse, cnvsRect);
				curPnt = CoordCvt_Scr2Img(curMouse, cnvsRect);

				painter->Paint((*canvas), prePnt, curPnt);
				
				cnvsItem->Update(UPDATE_TEXOBJ);
			}			
		}
		break;
	}		

	_panel->Invalidate();
}

/// Panel mouse up event
void HKCStatePaint::Panel_MouseUp(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	HKCAppState::Panel_MouseUp(_form, _panel, _e);	

	switch(_e->Button)
	{
	case Windows::Forms::MouseButtons::Left:
		{
			m_State = HKEPaintS::IDLE;		
			_panel->Invalidate();
		}		
		break;
	}
}

/// Panel mouse wheel event
void HKCStatePaint::Panel_MouseWheel(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	HKCAppState::Panel_MouseWheel(_form, _panel, _e);

	HKCPainter^ painter = (HKCPainter^)(_form->ToolManager->Find(AppGlobal::g_PntrLabel));
	if(!painter) return;
	painter->Cursor = &CoordCvt_Scr2Wrd(MousePos);

	_panel->Invalidate();
}