/**
* @file AppStateXForm.cpp
*
* Implementation of the class methods for transformation state
*
* @author James Hung-Kuo Chu (2013/01/07)
*/

#include "stdafx.h"
#include "Form1.h"
#include "AppUtils.h"
#include "AppState.h"

using namespace AppFrame;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/*! \class AppFrame::HKCStateMove

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
template<> HKCStateMove*	HKCSingleton<HKCStateMove>::mp_Instance = NULL;

/*---------------------------------------------------------------------*/
/*                            Constructor                              */
/// Constructor
HKCStateMove::HKCStateMove(void)
{
	m_State = HKEXFormS::IDLE;	
}

/*---------------------------------------------------------------------*/
/*                             Operations                              */
/// Panel mouse down event
void HKCStateMove::Panel_MouseDown(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	HKCAppState::Panel_MouseDown(_form, _panel, _e);	
		
	switch(_e->Button)
	{
	case Windows::Forms::MouseButtons::Left:
		{
			m_State = HKEXFormS::MOVING;	
			
			HKCMediaItem^ refItem = _form->AppItem->Find("Source");	
			if(refItem)
			{				
				HKCXForm* refXform = refItem->XForm;	
				refXform->State = (int)m_State;
			}			
			
			_panel->Invalidate();
		}															 											 						 
		break;
	}
}

/// Panel mouse move event
void HKCStateMove::Panel_MouseMove(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	cv::Point2i preMouse = MousePos;
	HKCAppState::Panel_MouseMove(_form, _panel, _e);	

	CoordCvt_Scr2Wrd(MousePos); /// Null operation...

	switch(m_State)
	{
	case HKEXFormS::MOVING:
		{						
			HKCMediaItem^ refItem = _form->AppItem->Find("Source");			
			if(refItem)
			{				
				cv::Point2d prePnt = CoordCvt_Scr2Wrd(preMouse);
				cv::Point2d curPnt = CoordCvt_Scr2Wrd(MousePos);

				HKCXForm* refXform = refItem->XForm;				
				refXform->Move += cv::Vec2d(curPnt.x-prePnt.x, curPnt.y-prePnt.y);				
				refXform->Update();				
			}			
		}
		break;
	}		

	_panel->Invalidate();	
}

/// Panel mouse up event
void HKCStateMove::Panel_MouseUp(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	HKCAppState::Panel_MouseUp(_form, _panel, _e);	

	switch(_e->Button)
	{
	case Windows::Forms::MouseButtons::Left:
		{
			m_State = HKEXFormS::IDLE;	
			
			HKCMediaItem^ refItem = _form->AppItem->Find("Source");	
			if(refItem)
			{				
				HKCXForm* refXform = refItem->XForm;	
				refXform->State = (int)m_State;		
			}			

			_panel->Invalidate();
		}		
		break;
	}
}

/// Panel key down event
void HKCStateMove::Panel_KeyDown(Form1^ _form, HKOGLPanelControl^ _panel, KeyEventArgs^ _e)
{
	HKCAppState::Panel_KeyDown(_form, _panel, _e);	
	
	HKCXFormer^ xformer = (HKCXFormer^)(_form->ToolManager->Find(AppGlobal::g_XFormLabel));
	HKCXFormProp^ xformProp = xformer->XFormProp;
	HKCMediaItem^ refItem = _form->AppItem->Find("Source");	
	if(refItem)
	{
		m_State = HKEXFormS::IDLE;
		cv::Vec2d offset(0.0,0.0);

		switch(_e->KeyCode)
		{
		case Keys::W:
			m_State = HKEXFormS::MOVING;
			offset = cv::Vec2d(0.0, xformProp->MoveRes[1]);			
			break;
		case Keys::S:
			m_State = HKEXFormS::MOVING;
			offset = cv::Vec2d(0.0, -xformProp->MoveRes[1]);			
			break;
		case Keys::A:
			m_State = HKEXFormS::MOVING;
			offset = cv::Vec2d(-xformProp->MoveRes[0], 0.0);			
			break;
		case Keys::D:
			m_State = HKEXFormS::MOVING;
			offset = cv::Vec2d(xformProp->MoveRes[0], 0.0);			
			break;		
		}

		if(m_State == HKEXFormS::MOVING)
		{		
			HKCXForm* refXform = refItem->XForm;	
			refXform->Move += offset;			
			refXform->State = (int)m_State;	
			refXform->Update();	

			_panel->Invalidate();
		}		
	}	
}

/// Panel key up event
void HKCStateMove::Panel_KeyUp(Form1^ _form, HKOGLPanelControl^ _panel, KeyEventArgs^ _e)
{
	HKCAppState::Panel_KeyUp(_form, _panel, _e);	
	
	HKCMediaItem^ refItem = _form->AppItem->Find("Source");	
	if(refItem)
	{				
		m_State = HKEXFormS::IDLE;	

		HKCXForm* refXform = refItem->XForm;	
		refXform->State = (int)m_State;

		_panel->Invalidate();
	}	
}

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/*! \class AppFrame::HKCStateRotate

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
template<> HKCStateRotate*	HKCSingleton<HKCStateRotate>::mp_Instance = NULL;

/*---------------------------------------------------------------------*/
/*                            Constructor                              */
/// Constructor
HKCStateRotate::HKCStateRotate(void)
{
	m_State = HKEXFormS::IDLE;	
}

/*---------------------------------------------------------------------*/
/*                             Operations                              */
/// Panel mouse down event
void HKCStateRotate::Panel_MouseDown(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	HKCAppState::Panel_MouseDown(_form, _panel, _e);	
		
	switch(_e->Button)
	{
	case Windows::Forms::MouseButtons::Left:
		{
			m_State = HKEXFormS::ROTATING;	

			HKCMediaItem^ refItem = _form->AppItem->Find("Source");	
			if(refItem)
			{				
				HKCXForm* refXform = refItem->XForm;	
				refXform->State = (int)m_State;
			}			

			_panel->Invalidate();
		}															 											 						 
		break;
	}	
}

/// Panel mouse move event
void HKCStateRotate::Panel_MouseMove(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	cv::Point2i preMouse = MousePos;
	HKCAppState::Panel_MouseMove(_form, _panel, _e);	
	
	CoordCvt_Scr2Wrd(MousePos); /// Null operation...

	switch(m_State)
	{
	case HKEXFormS::ROTATING:
		{						
			HKCMediaItem^ refItem = _form->AppItem->Find("Source");			
			if(refItem)
			{															
				_panel->Make_Current();
				cv::Point2d prePnt = CoordCvt_Scr2Wrd(preMouse);
				cv::Point2d curPnt = CoordCvt_Scr2Wrd(MousePos);

				HKCXForm* refXform = refItem->XForm;									
				cv::Point3d refCntr = cv::Point3d(refXform->Move[0]+refXform->Center.x, refXform->Move[1]+refXform->Center.y, 0.0);
				cv::Point3d pnt2cntr = cv::Point3d(prePnt.x-refCntr.x, prePnt.y-refCntr.y, 0.0);
				cv::Point3d mouseVec = cv::Point3d(curPnt.x-prePnt.x, curPnt.y-prePnt.y, 0.0);
				cv::Point3d crossVec = pnt2cntr.cross(mouseVec);

				double angle = cv::norm(mouseVec);
				if(crossVec.z > 0)
					refXform->Angle += angle;
				else
					refXform->Angle -= angle;

				refXform->Update();				
			}			
		}
		break;
	}			

	_panel->Invalidate();
}

/// Panel mouse up event
void HKCStateRotate::Panel_MouseUp(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	HKCAppState::Panel_MouseUp(_form, _panel, _e);		

	switch(_e->Button)
	{
	case Windows::Forms::MouseButtons::Left:
		{
			m_State = HKEXFormS::IDLE;	

			HKCMediaItem^ refItem = _form->AppItem->Find("Source");	
			if(refItem)
			{				
				HKCXForm* refXform = refItem->XForm;	
				refXform->State = (int)m_State;		
			}			

			_panel->Invalidate();
		}		
		break;
	}
}

/// Panel key down event
void HKCStateRotate::Panel_KeyDown(Form1^ _form, HKOGLPanelControl^ _panel, KeyEventArgs^ _e)
{
	HKCAppState::Panel_KeyDown(_form, _panel, _e);	

	HKCXFormer^ xformer = (HKCXFormer^)(_form->ToolManager->Find(AppGlobal::g_XFormLabel));
	HKCXFormProp^ xformProp = xformer->XFormProp;
	HKCMediaItem^ refItem = _form->AppItem->Find("Source");	
	if(refItem)
	{
		m_State = HKEXFormS::IDLE;
		double angle = xformProp->RotateRes;

		switch(_e->KeyCode)
		{
		case Keys::Add:
			m_State = HKEXFormS::ROTATING;
			angle *= 1.0;			
			break;
		case Keys::Subtract:
			m_State = HKEXFormS::ROTATING;
			angle *= -1.0;	
			break;		
		}

		if(m_State == HKEXFormS::ROTATING)
		{						
			HKCXForm* refXform = refItem->XForm;				
			refXform->Angle += angle;				
			refXform->State = (int)m_State;	
			refXform->Update();

			_panel->Invalidate();
		}		
	}	
}

/// Panel key up event
void HKCStateRotate::Panel_KeyUp(Form1^ _form, HKOGLPanelControl^ _panel, KeyEventArgs^ _e)
{
	HKCAppState::Panel_KeyUp(_form, _panel, _e);	

	HKCMediaItem^ refItem = _form->AppItem->Find("Source");	
	if(refItem)
	{				
		m_State = HKEXFormS::IDLE;	

		HKCXForm* refXform = refItem->XForm;	
		refXform->State = (int)m_State;		

		_panel->Invalidate();
	}	
}

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/*! \class AppFrame::HKCStateScale

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
template<> HKCStateScale*	HKCSingleton<HKCStateScale>::mp_Instance = NULL;

/*---------------------------------------------------------------------*/
/*                            Constructor                              */
/// Constructor
HKCStateScale::HKCStateScale(void)
{
	m_State = HKEXFormS::IDLE;	
}

/*---------------------------------------------------------------------*/
/*                             Operations                              */
/// Panel mouse down event
void HKCStateScale::Panel_MouseDown(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	HKCAppState::Panel_MouseDown(_form, _panel, _e);	
		
	switch(_e->Button)
	{
	case Windows::Forms::MouseButtons::Left:
		{
			m_State = HKEXFormS::SCALING;	

			HKCMediaItem^ refItem = _form->AppItem->Find("Source");	
			if(refItem)
			{				
				HKCXForm* refXform = refItem->XForm;	
				refXform->State = (int)m_State;
				refXform->Mouse = CoordCvt_Scr2Wrd(MousePos);
			}			

			_panel->Invalidate();
		}															 											 						 
		break;
	}	
}

/// Panel mouse move event
void HKCStateScale::Panel_MouseMove(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	cv::Point2i preMouse = MousePos;
	HKCAppState::Panel_MouseMove(_form, _panel, _e);

	CoordCvt_Scr2Wrd(MousePos); /// Null operation...

	switch(m_State)
	{
	case HKEXFormS::SCALING:
		{						
			HKCMediaItem^ refItem = _form->AppItem->Find("Source");			
			if(refItem)
			{															
				_panel->Make_Current();
				cv::Point2d prePnt = CoordCvt_Scr2Wrd(preMouse);
				cv::Point2d curPnt = CoordCvt_Scr2Wrd(MousePos);
				
				HKCXForm* refXform = refItem->XForm;									
				cv::Point2d refCntr = cv::Point2d(refXform->Move[0]+refXform->Center.x, refXform->Move[1]+refXform->Center.y);
				cv::Point2d mouse2cntr = refXform->Mouse - refCntr;			
				cv::Point2d mouseVec = curPnt - prePnt;				

				double scale = cv::norm(mouseVec);
				if(mouseVec.ddot(mouse2cntr) < 0.0)
					scale *= -1;

				refXform->Scale += cv::Vec2d(scale, scale)*0.01;				
				refXform->Update();				
			}			
		}
		break;
	}			

	_panel->Invalidate();
}

/// Panel mouse up event
void HKCStateScale::Panel_MouseUp(Form1^ _form, HKOGLPanelControl^ _panel, MouseEventArgs^ _e)
{
	HKCAppState::Panel_MouseUp(_form, _panel, _e);

	switch(_e->Button)
	{
	case Windows::Forms::MouseButtons::Left:
		{
			m_State = HKEXFormS::IDLE;	

			HKCMediaItem^ refItem = _form->AppItem->Find("Source");	
			if(refItem)
			{				
				HKCXForm* refXform = refItem->XForm;	
				refXform->State = (int)m_State;
			}			

			_panel->Invalidate();
		}		
		break;
	}
}

/// Panel key down event
void HKCStateScale::Panel_KeyDown(Form1^ _form, HKOGLPanelControl^ _panel, KeyEventArgs^ _e)
{
	HKCAppState::Panel_KeyDown(_form, _panel, _e);	

	HKCXFormer^ xformer = (HKCXFormer^)(_form->ToolManager->Find(AppGlobal::g_XFormLabel));
	HKCXFormProp^ xformProp = xformer->XFormProp;
	HKCMediaItem^ refItem = _form->AppItem->Find("Source");	
	if(refItem)
	{
		m_State = HKEXFormS::IDLE;
		cv::Vec2d scale = cv::Vec2d(xformProp->ScaleRes[0], xformProp->ScaleRes[1]);		

		switch(_e->KeyCode)
		{
		case Keys::Add:
			m_State = HKEXFormS::SCALING;
			scale *= 1.0;			
			break;
		case Keys::Subtract:
			m_State = HKEXFormS::SCALING;
			scale *= -1.0;	
			break;		
		}

		if(m_State == HKEXFormS::SCALING)
		{						
			HKCXForm* refXform = refItem->XForm;								
			refXform->Scale += scale;				
			refXform->State = (int)m_State;	
			refXform->Update();

			_panel->Invalidate();
		}		
	}	
}

/// Panel key up event
void HKCStateScale::Panel_KeyUp(Form1^ _form, HKOGLPanelControl^ _panel, KeyEventArgs^ _e)
{
	HKCAppState::Panel_KeyUp(_form, _panel, _e);	

	HKCMediaItem^ refItem = _form->AppItem->Find("Source");	
	if(refItem)
	{				
		m_State = HKEXFormS::IDLE;	

		HKCXForm* refXform = refItem->XForm;	
		refXform->State = (int)m_State;

		_panel->Invalidate();
	}
}