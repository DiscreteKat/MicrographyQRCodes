/**
* @file AppStateGrabCut.cpp
*
* Implementation of the class methods for GrabCut state
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

/*! \class AppFrame::HKCStateGC

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
template<> HKCStateGC*	HKCSingleton<HKCStateGC>::mp_Instance = NULL;

/*---------------------------------------------------------------------*/
/*                            Constructor                              */
/// Constructor
HKCStateGC::HKCStateGC(void)
{
	m_State = HKEPaintS::IDLE;	
}

/*---------------------------------------------------------------------*/
/*                             Operations                              */
/// Panel mouse down event
void HKCStateGC::Panel_MouseDown(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
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
void HKCStateGC::Panel_MouseMove(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	cv::Point2i preMouse = MousePos;
	HKCAppState::Panel_MouseMove(_form, _panel, _e);

	HKCGrabCutr^ grabcutr = (HKCGrabCutr^)(_form->ToolManager->Find(AppGlobal::g_GCLabel));
	if(!grabcutr) return;
	grabcutr->Cursor = &CoordCvt_Scr2Wrd(MousePos);	

	switch(m_State)
	{
	case HKEPaintS::PAINTING:
		{
			HKCGrabCut* grabcut = grabcutr->GrabCut;			
			HKCMediaItem^ cnvsItem = _form->AppItem->Find("GrabCut Canvas");
			if(cnvsItem && grabcut)
			{
				cv::Point2i curMouse = MousePos;
				cv::Point2d prePnt, curPnt;

				cv::Mat& gcMask = grabcut->Mask();	
				cv::Mat& gcBmask = grabcut->BinMask();

				cv::Mat* canvas = (cv::Mat*)(cnvsItem->Media->Data());
				cv::Size cnvsSize = canvas->size();
				cv::Rect cnvsRect(0, 0, cnvsSize.width, cnvsSize.height);

				cnvsItem->glContext->Make_Current();
				prePnt = CoordCvt_Scr2Img(preMouse, cnvsRect);
				curPnt = CoordCvt_Scr2Img(curMouse, cnvsRect);

				/// Get GrabCut's property object
				HKCPntrProp^ prop = grabcutr->PainterProp;

				/// Painting on the canvas
				grabcutr->Paint((*canvas), prePnt, curPnt);

				/// Painting labels on the mask
				grabcutr->Paint(gcMask, prePnt, curPnt, cv::Scalar::all(grabcut->MaskVal()), prop->Size);

				/// Painting on the binary mask
				if(!gcBmask.empty() && (grabcut->Stroke() == HKCGrabCut::STROKE_MSKB || grabcut->Stroke() == HKCGrabCut::STROKE_MSKW))
					grabcutr->Paint(gcBmask, prePnt, curPnt);					

				cnvsItem->Update(UPDATE_TEXOBJ);
			}			
		}
		break;
	}

	_panel->Invalidate();
}

/// Panel mouse up event
void HKCStateGC::Panel_MouseUp(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	HKCAppState::Panel_MouseUp(_form, _panel, _e);		

	switch(_e->Button)
	{
	case Windows::Forms::MouseButtons::Left:
		{
			m_State = HKEPaintS::IDLE;
		}		
		break;
	}
}

/// Panel mouse wheel event
void HKCStateGC::Panel_MouseWheel(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	HKCAppState::Panel_MouseWheel(_form, _panel, _e);

	HKCGrabCutr^ grabcutr = (HKCGrabCutr^)(_form->ToolManager->Find(AppGlobal::g_GCLabel));
	if(!grabcutr) return;
	grabcutr->Cursor = &CoordCvt_Scr2Wrd(MousePos);

	_panel->Invalidate();
}