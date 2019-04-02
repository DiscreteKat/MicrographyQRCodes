/**
* @file AppXForm.cpp
*
* Implementation of the class methods for transformation tool
*
* @author James Hung-Kuo Chu (2013/01/07)
*/

#include "stdafx.h"
#include "AppProperty.h"
#include "AppItem.h"
#include "AppTool.h"
#include "AppXForm.h"

using namespace AppFrame;
using namespace HKCV;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/*! \class AppFrame::HKCXFormer

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
/// Constructor
HKCXFormer::HKCXFormer(System::String^ _label) : HKCAppTool(_label, gcnew HKCXFormProp)
{		
	mp_XFormProp = dynamic_cast<HKCXFormProp^>(mp_Prop);
}

HKCXFormer::HKCXFormer(System::String^ _label, HKCToolProp^ _prop) : HKCAppTool(_label, _prop)
{	
	mp_XFormProp = dynamic_cast<HKCXFormProp^>(mp_Prop);
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
/// Destructor
HKCXFormer::~HKCXFormer(void)
{	
}

/*---------------------------------------------------------------------*/
/*                             Operations                              */
/// Activate xform
bool HKCXFormer::Activate(HKCAppItem^ _appItem)
{	
	if(!_appItem) return false;

	/// Use the source media item as reference
	HKCMediaItem^ refItem = _appItem->Find("Source");
	if(!refItem)
	{
		Console::WriteLine("HKCXFormer::Activate() : No source image is found!");
		return false;
	}

	/// Enable the tool
	mp_XFormProp->Enabled = true;	

	return true;
}

/// Deactivate xform
bool HKCXFormer::DeActivate(HKCAppItem^ _appItem)
{		
	/*if(mp_XFormProp->Enabled)
	{
		/// Apply the transformation
		Action("CROP", _appItem);
	}*/	

	/// Disable the tool
	mp_XFormProp->Enabled = false;		
	
	return true;
}

/// XForm's action
bool HKCXFormer::Action(System::String^ _act, HKCAppItem^ _appItem)
{
	if(!mp_XFormProp->Enabled) return false;

	/// Use the source media item as reference
	HKCMediaItem^ refItem = _appItem->Find("Source");
	if(!refItem)
	{
		Console::WriteLine("HKCXFormer::Action() : No valid source item is found!");
		return false;
	}

	if(System::String::Compare(_act, L"MIRROR") == 0)
	{
		refItem->glContext->Make_Current();
		refItem->XForm->Mirror = !refItem->XForm->Mirror;
		refItem->XForm->Update();
		refItem->glContext->Invalidate();
	}
	else if(System::String::Compare(_act, L"UNDO") == 0)
	{
		refItem->glContext->Make_Current();
		refItem->XForm->Clear();
		refItem->glContext->Invalidate();
	}	
	else if(System::String::Compare(_act, L"CROP") == 0)
	{		
		/// Apply the image cropping
		System::Windows::Forms::DialogResult result = System::Windows::Forms::MessageBox::Show( "Apply the transformation?", "Leaving XForm", System::Windows::Forms::MessageBoxButtons::YesNo );
		if ( result == System::Windows::Forms::DialogResult::Yes )
		{					
			HKCMediaItem^ srcItem = _appItem->Find("QRCode");
			if(!srcItem)
			{
				Console::WriteLine("HKCXFormer::Action() : No valid QRCode item is found!");
				return false;
			}

			/// Image to be cropped
			cv::Mat* refImg = (cv::Mat*)(refItem->Media->Data());
			cv::Mat tmpImg = refImg->clone();

			HKCXForm* refXForm = refItem->XForm;
			
			/// Apply mirror
			if(refXForm->Mirror)			
				cv::flip(tmpImg, tmpImg, 1);

			/// Apply scale
			cv::Vec2d scale = refXForm->Scale;
			cv::Size refSize = tmpImg.size();
			cv::Size newSize(cvRound(refSize.width*scale[0]), cvRound(refSize.height*scale[1]));
			int iterpMode = (newSize.area() >= refSize.area()) ? CV_INTER_CUBIC : CV_INTER_AREA; 
			cv::resize(tmpImg, tmpImg, newSize, 0, 0, iterpMode);

			/// Apply rotation
			cv::Size tmpSize = tmpImg.size();
			double orgDiagL = CvDiagLength(tmpSize);
			cv::Size expSize(cvRound(orgDiagL), cvRound(orgDiagL));
			cv::Rect expRect(cv::Point2i(0,0),expSize);
			cv::Rect roiRect(cv::Point2i(cvRound((orgDiagL-tmpSize.width)*0.5), cvRound((orgDiagL-tmpSize.height)*0.5)), tmpSize);
			cv::Mat expImg = cv::Mat::zeros(expSize, tmpImg.type());
			tmpImg.copyTo(expImg(roiRect));			
			cv::Point2f rotCntr(float(orgDiagL*0.5), float(orgDiagL*0.5));			
			cv::Mat rotMtx = cv::getRotationMatrix2D(rotCntr, refXForm->Angle, 1.0);									
			cv::warpAffine(expImg, tmpImg, rotMtx, expSize);

			/// Apply cropping			
			cv::Size srcSize = srcItem->Media->Size();
			cv::Point2d expOrg(refXForm->Center.x+refXForm->Move[0]-orgDiagL*0.5, refXForm->Center.y+refXForm->Move[1]+orgDiagL*0.5);
			cv::Point2d srcOrg(0.0, srcSize.height);
			cv::Rect cropRect(cv::Point2i(cvRound(srcOrg.x-expOrg.x),cvRound(expOrg.y-srcOrg.y)), srcSize);						
			cv::Rect roiRect1 = expRect & cropRect;
			cv::Rect roiRect2(roiRect1.x-cropRect.x, roiRect1.y-cropRect.y, roiRect1.width, roiRect1.height);
			cv::Mat rstImg = cv::Mat::zeros(srcItem->Media->Size(), tmpImg.type());
			tmpImg(roiRect1).copyTo(rstImg(roiRect2));

			refItem->glContext->Make_Current();

			/// Change the media accordingly
			refImg->release();
			rstImg.copyTo(*refImg);			
			refItem->Media->Update();
			refItem->XForm->Clear();
			refItem->XForm->Center = cv::Point2d(refImg->size().width*0.5, refImg->size().height*0.5);

			refItem->glContext->Invalidate();
		}		
	}

	return true;
}