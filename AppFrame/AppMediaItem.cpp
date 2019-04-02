/**
* @file AppMediaItem.cpp
*
* Implementation of the class methods for media item
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "AppMediaItem.h"

using namespace AppFrame;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::HKCMediaItem

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCMediaItem::HKCMediaItem(void)
{		
	mp_Media	= NULL;
	mp_Prop		= nullptr;
	mp_XForm	= NULL;	
	m_Label		= "";
	mp_GLCntxt	= nullptr;
}

HKCMediaItem::HKCMediaItem(HKCMedia* _media, System::String^ _label, HKOGLPanelControl^ _panel)
{	
	m_Label		= _label;
	mp_GLCntxt	= _panel;
	mp_Media	= nullptr;
	Update(_media);
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCMediaItem::~HKCMediaItem(void)
{
	delete mp_Media;
	mp_Media = NULL;	

	delete mp_Prop;
	mp_Prop = nullptr;

	delete mp_XForm;
	mp_XForm = NULL;
}

/*---------------------------------------------------------------------*/
/*                              Update                                 */
/// Update specific data of media 
bool HKCMediaItem::Update(int _flag)
{
	bool flag = false;
	if(mp_Media && mp_GLCntxt)
	{
		mp_GLCntxt->Make_Current();		
		flag = mp_Media->Update(_flag);
		mp_GLCntxt->Invalidate();
	}
	return flag;
}

/// Update media with another input media
bool HKCMediaItem::Update(HKCMedia* _media)
{
	if(mp_Media == _media) return true;

	/// Release old data
	delete mp_Media; mp_Media = NULL;
	delete mp_Prop; mp_Prop = nullptr;
	delete mp_XForm; mp_XForm = NULL;

	/// Set the new media and property object
	mp_Media = _media;
	if(mp_Media)
	{
		switch(mp_Media->Type())
		{
		case IMAGE:			
			mp_Prop = gcnew HKCImageProp(mp_Media->Param());				
			break;
		case VIDEO:			
			mp_Prop = gcnew HKCVideoProp(mp_Media->Param());				
			break;
		default:
			Console::WriteLine("HKCMediaItem::Update() : Improper media type!");	
			return false;
		}
	}

	/// Set the transformation
	mp_XForm = new HKCXForm;
	cv::Size mediaSize = mp_Media->Size();		
	mp_XForm->Center = cv::Point2d(mediaSize.width*0.5, mediaSize.height*0.5);

	/// Set media's default render properties
	HKCIRndrProp^ rndrProp = (HKCIRndrProp^)mp_Prop->Render;
	rndrProp->Blend = true;
	rndrProp->ConstAlpha = 0.85f;

	return true;
}

/// Update the alpha channel of the media
bool HKCMediaItem::Update(cv::Mat& _mask)
{
	if(mp_Media->Size() != _mask.size())
	{
		Console::WriteLine("HKCMediaItem::Update() : Sizes of image and mask do not match!");
		return false;
	}

	cv::Mat* srcImg = (cv::Mat*)(mp_Media->Data());
	HKCV::VecMat channels;
	split((*srcImg), channels);	
	if(channels.size() == 2 || channels.size() == 4)
		_mask.copyTo(channels[channels.size()-1]);
	else if(channels.size() == 1 || channels.size() == 3)
		channels.push_back(_mask);
	else
	{
		Console::WriteLine("HKCMediaItem::Update() : Invalid channel number");
		return false;
	}
	merge(channels, (*srcImg));

	mp_GLCntxt->Make_Current();
	
	mp_Media->Update();	

	mp_GLCntxt->Invalidate();

	return true;
}

/*---------------------------------------------------------------------*/
/*                               Render                                */
/// Render media
void HKCMediaItem::Render(void)
{

	if(mp_Media && mp_Prop->Render->Visible)		
	{		

		HKCIRndrProp^ rndrProp = (HKCIRndrProp^)mp_Prop->Render;		

		glPushAttrib(GL_COLOR_BUFFER_BIT);				

		/// Setup alpha blending mode
		if(mp_XForm->State != 0 && (mp_Media->Dim() == 1 || mp_Media->Dim() == 3))
		{	
			float constAlpha = rndrProp->ConstAlpha;
			glBlendFunc(GL_CONSTANT_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);			
			glBlendColor(constAlpha,constAlpha,constAlpha,constAlpha);			
		}

		/// Enable/disable alpha blending
		(rndrProp->Blend) ? glEnable(GL_BLEND) : glDisable(GL_BLEND);

		glPushMatrix();				
		glMultMatrixd(mp_XForm->XForm);
		mp_Media->Render(*mp_Prop->Render->Param);	
		glPopMatrix();

		glPopAttrib();


	}
	

}