/**
* @file AppGrabCut.cpp
*
* Implementation of the class methods for GrabCut tool
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "AppProperty.h"
#include "AppItem.h"
#include "AppTool.h"
#include "AppPainter.h"
#include "AppGrabCut.h"

using namespace AppFrame;
using namespace HKCV;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/*! \class AppFrame::HKCGrabCutr

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
/// Constructor
HKCGrabCutr::HKCGrabCutr(System::String^ _label) : HKCPainter(_label, gcnew HKCGCProp)
{		
	mp_GrabCut = NULL;
}

HKCGrabCutr::HKCGrabCutr(System::String^ _label, HKCToolProp^ _prop) : HKCPainter(_label, _prop)
{	
	mp_GrabCut = NULL;
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
/// Destructor
HKCGrabCutr::~HKCGrabCutr(void)
{	
	delete mp_GrabCut;
	mp_GrabCut = NULL;
}

/*---------------------------------------------------------------------*/
/*                          Tool Operations                            */
/// Activate GrabCut
bool HKCGrabCutr::Activate(HKCAppItem^ _appItem)
{			
	if(!_appItem || !_appItem->Item)
	{
		Console::WriteLine("HKCGrabCutr::Activate() : No valid source item is found!");
		return false;
	}
	
	/// Use the selected media item as reference
	HKCMediaItem^ refItem = _appItem->Item;

	/// Request a canvas	
	if(!_appItem->Find("GrabCut Canvas"))
	{
		cv::Mat canvs = cv::Mat::zeros(refItem->Media->Size(), CV_8UC4);		
		HKCMediaItem^ cnvsItem = _appItem->New(canvs, "GrabCut Canvas", refItem->glContext);		
	}

	/// Request a GrabCut object
	cv::Mat* refImg = (cv::Mat*)refItem->Media->Data();
	int refDim = refImg->channels();
	if(refDim == 2 || refDim == 4)
	{
		VecMat channels;
		cv::split((*refImg), channels);
		if(refDim == 2) (*refImg) = channels[0].clone();
		else cv::merge(&(channels[0]), 3, (*refImg));
		refItem->Update();
	}
	GrabCut = new HKCGrabCut(*refImg);

	/// Enable the tool
	mp_PntrProp->Enabled = true;

	/// Enable cursor rendering
	mp_PntrProp->Cursor = true;		

	/// Set initial stroke to foreground stroke
	Action("STROKE_FGD", _appItem);

	return true;
}

/// Deactivate GrabCut
bool HKCGrabCutr::DeActivate(HKCAppItem^ _appItem)
{
	/// Release GrabCut object
	GrabCut = NULL;	

	/// Remove the canvas
	_appItem->Delete("GrabCut Canvas");

	/// Disable the tool
	mp_PntrProp->Enabled = false;

	/// Disable cursor rendering 
	mp_PntrProp->Cursor = false;

	return true;
}

/// GrabCut's action
bool HKCGrabCutr::Action(System::String^ _act, HKCAppItem^ _appItem)
{
	if(!mp_PntrProp->Enabled) return false;

	if(_act->Contains("Stroke") || _act->Contains("STROKE"))
	{	
		if(System::String::Compare(_act, L"STROKE_FGD") == 0)
		{					
			Stroke = gcnew HKCStrkBrush;	
			mp_PntrProp->Color = Drawing::Color::Red;
			mp_PntrProp->Alpha = 255;
			mp_GrabCut->MaskVal() = cv::GC_FGD;	
			mp_GrabCut->Stroke() = HKCGrabCut::STROKE_FGD;
		}
		else if(System::String::Compare(_act, L"STROKE_BGD") == 0)
		{
			Stroke = gcnew HKCStrkBrush;	
			mp_PntrProp->Color = Drawing::Color::Blue;	
			mp_PntrProp->Alpha = 255;
			mp_GrabCut->MaskVal() = cv::GC_BGD;	
			mp_GrabCut->Stroke() = HKCGrabCut::STROKE_BGD;
		}	
		else if(System::String::Compare(_act, L"STROKE_PRFGD") == 0)
		{						
			Stroke = gcnew HKCStrkBrush;	
			mp_PntrProp->Color = Drawing::Color::Pink;
			mp_PntrProp->Alpha = 255;
			mp_GrabCut->MaskVal() = cv::GC_PR_FGD;	
			mp_GrabCut->Stroke() = HKCGrabCut::STROKE_PRFGD;
		}
		else if(System::String::Compare(_act, L"STROKE_PRBGD") == 0)
		{			
			Stroke = gcnew HKCStrkBrush;	
			mp_PntrProp->Color = Drawing::Color::LightBlue;
			mp_PntrProp->Alpha = 255;
			mp_GrabCut->MaskVal() = cv::GC_PR_BGD;	
			mp_GrabCut->Stroke() = HKCGrabCut::STROKE_PRBGD;
		}
		else if(System::String::Compare(_act, L"STROKE_MSKB") == 0)
		{
			Stroke = gcnew HKCStrkBrush;	
			mp_PntrProp->Color = Drawing::Color::Black;
			mp_PntrProp->Alpha = 200;
			mp_GrabCut->MaskVal() = cv::GC_BGD;		
			mp_GrabCut->Stroke() = HKCGrabCut::STROKE_MSKB;
		}
		else if(System::String::Compare(_act, L"STROKE_MSKW") == 0)
		{
			Stroke = gcnew HKCStrkBrush;	
			mp_PntrProp->Color = Drawing::Color::White;
			mp_PntrProp->Alpha = 0;
			mp_GrabCut->MaskVal() = cv::GC_FGD;		
			mp_GrabCut->Stroke() = HKCGrabCut::STROKE_MSKW;
		}
		else if(System::String::Compare(_act, L"STROKE_ERASE") == 0)
		{
			Stroke = gcnew HKCStrkBrush;
			mp_PntrProp->Color = Drawing::Color::White;
			mp_PntrProp->Alpha = 0;
			mp_GrabCut->MaskVal() = cv::GC_PR_FGD;
			mp_GrabCut->Stroke() = HKCGrabCut::STROKE_ERASE;
		}
		else
		{
			Stroke = nullptr;	
			mp_GrabCut->MaskVal() = 0;	
			mp_GrabCut->Stroke() = -1;
		}
	}
	else
	{	
		if(System::String::Compare(_act, L"CUT") == 0)
		{			
			/// Get the GrabCut's canvas
			HKCMediaItem^ cnvsItem = _appItem->Find("GrabCut Canvas");
			if(!cnvsItem)
			{
				Console::WriteLine("HKCGrabCutr::Action() : \"GrabCut Canvas\" is not found!");
				return false;
			}

			/// Perform GrabCut
			mp_GrabCut->Cut();
			cv::Mat& gcBmask = mp_GrabCut->BinMask();						

			/// Copy binary mask to canvas
			cv::Mat* canvas = (cv::Mat*)(cnvsItem->Media->Data());
			canvas->setTo(cv::Scalar(0,0,0,200));
			canvas->setTo(cv::Scalar(255,255,255,0), gcBmask);
			cnvsItem->Update();				
		}
		else if(System::String::Compare(_act, L"ADD") == 0)
		{		
			/// Use the selected media item as reference
			HKCMediaItem^ refItem = _appItem->Item;
			
			/// Get the binary mask
			cv::Mat& binMask = mp_GrabCut->BinMask();
			
			/// Set mask to the media
			if(refItem->Update(binMask))
			{
				/// Reset the GrabCut
				Action("RESET", _appItem);
			}
		}
		else if(System::String::Compare(_act, L"RESET") == 0)
		{								
			/// Get GrabCut's canvas
			HKCMediaItem^ cnvsItem = _appItem->Find("GrabCut Canvas");
			if(!cnvsItem)
			{
				Console::WriteLine("HKCGrabCutr::Action() : \"GrabCut Canvas\" is not found!");
				return false;
			}

			/// Clean canvas			
			cv::Mat* canvas = (cv::Mat*)(cnvsItem->Media->Data());
			(*canvas) = cv::Mat::zeros(canvas->size(), canvas->type());
			cnvsItem->Update();	

			/// Reset GrabCut
			mp_GrabCut->Reset();	

			/// Set initial stroke to foreground stroke
			Action("STROKE_FGD", _appItem);
		}
		else
		{
			Console::WriteLine("HKCGrabCutr::Action() : Unrecognized action!");
			return false;
		}
	}

	return true;
}