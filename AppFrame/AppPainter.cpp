/**
* @file AppPainter.cpp
*
* Implementation of the class methods for painter tool
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "AppProperty.h"
#include "AppItem.h"
#include "AppTool.h"
#include "AppPainter.h"

using namespace AppFrame;
using namespace HKCV;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/*! \class AppFrame::HKCPainter

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
/// Constructor
HKCPainter::HKCPainter(System::String^ _label) : HKCAppTool(_label, gcnew HKCPntrProp)
{	
	mp_Stroke = nullptr;
	mp_Cursor = new cv::Point2d(0.0, 0.0);
	mp_PntrProp = dynamic_cast<HKCPntrProp^>(mp_Prop);
}

HKCPainter::HKCPainter(System::String^ _label, HKCToolProp^ _prop) : HKCAppTool(_label, _prop)
{
	mp_Stroke = nullptr;
	mp_Cursor = new cv::Point2d(0.0, 0.0);
	mp_PntrProp = dynamic_cast<HKCPntrProp^>(mp_Prop);
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
/// Destructor
HKCPainter::~HKCPainter(void)
{
	delete mp_Stroke;
	mp_Stroke = nullptr;

	delete mp_Cursor;
	mp_Cursor = NULL;
}

/*---------------------------------------------------------------------*/
/*                              Painting                               */
/// Painting on an image
void HKCPainter::Paint(cv::Mat& _img, cv::Point2d& _pnt1, cv::Point2d& _pnt2)
{
	if(!mp_Stroke) return;

	cv::Scalar color = cv::Scalar(mp_PntrProp->Color.B, mp_PntrProp->Color.G, mp_PntrProp->Color.R, mp_PntrProp->Alpha);
	mp_Stroke->Paint(_img, _pnt1, _pnt2, color, mp_PntrProp->Size);
}

/// Painting on an image
void HKCPainter::Paint(cv::Mat& _img, cv::Point2d& _pnt1, cv::Point2d& _pnt2, cv::Scalar _color, int _size)
{
	if(!mp_Stroke) return;

	mp_Stroke->Paint(_img, _pnt1, _pnt2, _color, _size);
}

/*---------------------------------------------------------------------*/
/*                               Render                                */
void HKCPainter::Render(void)
{
	if(!mp_PntrProp->Enabled) return;	

	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT | GL_LIGHTING_BIT | GL_LINE_BIT | GL_POINT_BIT);
	if(mp_PntrProp->Cursor)
	{
		double scale = mp_PntrProp->Size*0.5;
		glEnable(GL_BLEND);
		glDisable(GL_LIGHTING);
		glLineWidth(1.5);
		glColor4f(1.0f,0.0f,1.0f,0.7f);
		glBegin(GL_LINE_LOOP);	
		for(float i = 0.f; i <= 2.0 * M_PI + 0.1; i += 0.1f)
			glVertex2d( mp_Cursor->x + sin(i)*scale, mp_Cursor->y + cos(i)*scale );
		glEnd();		
	}
	glPopAttrib();
}

/*---------------------------------------------------------------------*/
/*                             Operations                              */
/// Activate painter
bool HKCPainter::Activate(HKCAppItem^ _appItem)
{	
	if(!_appItem || !_appItem->Item)
	{
		Console::WriteLine("HKCPainter::Activate() : No valid source item is found!");
		return false;
	}
	
	/// Use the selected media item as reference
	HKCMediaItem^ refItem = _appItem->Item;

	/// Request a canvas	
	if(!_appItem->Find("Painter Canvas"))
	{		
		cv::Mat canvs = cv::Mat::zeros(refItem->Media->Size(), CV_8UC4);		
		HKCMediaItem^ cnvsItem = _appItem->New(canvs, "Painter Canvas", refItem->glContext);		
	}	

	/// Enable the tool
	mp_PntrProp->Enabled = true;

	/// Enable cursor rendering
	mp_PntrProp->Cursor = true;		

	/// Set initial stroke to brush
	Action("STROKE_BRUSH", _appItem);

	return true;
}

/// Deactivate painter
bool HKCPainter::DeActivate(HKCAppItem^ _appItem)
{	
	/// Disable the tool
	mp_PntrProp->Enabled = false;

	/// Disable cursor rendering 
	mp_PntrProp->Cursor = false;

	return true;
}

/// Painter's action
bool HKCPainter::Action(System::String^ _act, HKCAppItem^ _appItem)
{
	if(!mp_PntrProp->Enabled) return false;

	if(_act->Contains("Stroke") || _act->Contains("STROKE"))
	{	
		if(System::String::Compare(_act, L"STROKE_BRUSH") == 0)
		{		
			Stroke = gcnew HKCStrkBrush;			
		}
		else if(System::String::Compare(_act, L"STROKE_ERASE") == 0)
		{	
			Stroke = gcnew HKCStrkErase;			
		}		
		else
			Stroke = nullptr;
	}
	else
	{
		if(System::String::Compare(_act, L"CLEAN") == 0)
		{			
			/// Get painter's canvas
			HKCMediaItem^ cnvsItem = _appItem->Find("Painter Canvas");
			if(!cnvsItem)
			{
				Console::WriteLine("HKCPainter::Action() : \"Painter Canvas\" is not found!");
				return false;
			}

			/// Clean canvas		
			cv::Mat* canvas = (cv::Mat*)(cnvsItem->Media->Data());
			(*canvas) = cv::Mat::zeros(canvas->size(), canvas->type());
			cnvsItem->Update();
		}
	}

	return true;
}