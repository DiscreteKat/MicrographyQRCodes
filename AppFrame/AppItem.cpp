/**
* @file AppItem.cpp
*
* Implementation of the class methods for application item
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"

using namespace AppFrame;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::HKCAppItem

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCAppItem::HKCAppItem(void) 
{
	mp_Items	= gcnew List<HKCMediaItem^>;
	mp_candidates	= gcnew List<HKCMediaItem^>;
	mp_wordarts	= gcnew List<HKCMediaItem^>;
	mp_Prop		= gcnew HKCAppProp;
	mp_Param	= gcnew HKCAppParam;
	mp_Data		= new HKCAppData;
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCAppItem::~HKCAppItem(void)
{	
	for each(HKCMediaItem^ media in mp_Items)	
		delete media;	
	mp_Items->Clear();	

	/*for each(HKCMediaItem^ media in mp_candidates)	
		delete media;	
	mp_candidates->Clear();	*/

	delete mp_Prop;
	mp_Prop = nullptr;

	delete mp_Param;
	mp_Param = nullptr;

	delete mp_Data;
	mp_Data = NULL;
}

/*---------------------------------------------------------------------*/
/*                          Item Operations                            */
/// Clear data
void HKCAppItem::Clear(void)
{
	for each(HKCMediaItem^ media in mp_Items)	
		delete media;	
	mp_Items->Clear();
	mp_Item = nullptr;	

	for each(HKCMediaItem^ media in mp_candidates)	
		delete media;	
	mp_candidates->Clear();
	mp_candidate = nullptr;	
	for each(HKCMediaItem^ Region in mp_wordarts)	
		delete Region;		
	mp_wordarts->Clear();
	mp_wordart=nullptr;
}

/// Add a media item
bool HKCAppItem::Add(HKCMediaItem^ _item)
{
	if(!_item) return false;
	mp_Items->Add(_item);
	return true;
}

bool HKCAppItem::AddCandidate(HKCMediaItem^ _candidate)
{
	if(!_candidate) return false;
	mp_candidates->Add(_candidate);
	return true;
}
bool HKCAppItem::AddWordArt(HKCMediaItem^ _wordart)
{
	if(!_wordart) return false;
	mp_wordarts->Add(_wordart);
	return true;
}
bool HKCAppItem::ClearCandidate()
{
	for each(HKCMediaItem^ media in mp_candidates)	
		delete media;	
	mp_candidates->Clear();
	mp_candidate = nullptr;	
	return true;
}
bool HKCAppItem::ClearWordArt()
{
	for each(HKCMediaItem^ Region in mp_wordarts)	
		delete Region;		
	mp_wordarts->Clear();
	mp_wordart=nullptr;
	return true;
}
/// Find the media item with specific label
HKCMediaItem^ HKCAppItem::Find(System::String^ _label)
{
	for each(HKCMediaItem^ item in mp_Items)
	{
		if(System::String::Compare(_label, item->Label)==0)
			return item;
	}
	return nullptr;
}

HKCMediaItem^ HKCAppItem::FindCandidate(System::String^ _label)
{
	for each(HKCMediaItem^ candidate in mp_candidates)
	{
		if(System::String::Compare(_label, candidate->Label)==0)
			return candidate;
	}
	return nullptr;
}


/// Create a new media item
HKCMediaItem^ HKCAppItem::New(cv::Mat& _mat, System::String^ _label, HKOGLPanelControl^ _glPanel)
{		
	HKCMedia* media = new HKCImage(_mat);	
	return New(media, _label, _glPanel);	
}

/// Create a new media item
HKCMediaItem^ HKCAppItem::New(HKCMedia* _media, System::String^ _label, HKOGLPanelControl^ _glPanel)
{	
	HKCMediaItem^ newItem = gcnew HKCMediaItem(_media, _label, _glPanel);
	Add(newItem);
	return newItem;
}

HKCMediaItem^ HKCAppItem::NewCandidate(cv::Mat& _mat, System::String^ _label, HKOGLPanelControl^ _glPanel)
{		
	HKCMedia* media = new HKCImage(_mat);	
	return NewCandidate(media, _label, _glPanel);	
}

HKCMediaItem^ HKCAppItem::NewCandidate(HKCMedia* _media, System::String^ _label, HKOGLPanelControl^ _glPanel)
{	
	HKCMediaItem^ newItem = gcnew HKCMediaItem(_media, _label, _glPanel);
	AddCandidate(newItem);
	return newItem;
}
HKCMediaItem^ HKCAppItem::NewWordArt(cv::Mat& _mat, System::String^ _label, HKOGLPanelControl^ _glPanel)
{		
	HKCMedia* media = new HKCImage(_mat);	
	return NewWordArt(media, _label, _glPanel);	
}

HKCMediaItem^ HKCAppItem::NewWordArt(HKCMedia* _media, System::String^ _label, HKOGLPanelControl^ _glPanel)
{	
	HKCMediaItem^ newItem = gcnew HKCMediaItem(_media, _label, _glPanel);
	AddWordArt(newItem);
	return newItem;
}

/// Delete media item at specific index
bool HKCAppItem::Delete(int _idx)
{
	if(_idx < 0 || _idx >= mp_Items->Count) return false;
	if(mp_Item == mp_Items[_idx])
	{
		if(mp_Items->Count == 1)
			Item = nullptr;
		else
		{
			int newIdx = (_idx-1 >= 0) ? _idx-1 : _idx+1;
			Item = mp_Items[newIdx];
		}
	}	

	mp_Items->RemoveAt(_idx);
	return true;
}

/// Delete item with specific label
bool HKCAppItem::Delete(System::String^ _label)
{
	HKCMediaItem^ item = Find(_label);
	if(!item) return false;
	int idx = mp_Items->IndexOf(item);
	return Delete(idx);	
}

/// Delete media item with the specified labels
void HKCAppItem::Delete(cli::array<System::String^>^ _labels)
{
	for each(System::String^ label in _labels)	
		Delete(label);	
}

/// Delete media item except the specified labels
void HKCAppItem::DeleteEx(cli::array<System::String^>^ _labels)
{
	List<System::String^>^ candidates = gcnew List<System::String^>;
	for each(HKCMediaItem^ item in mp_Items)	
		if( Array::IndexOf(_labels, item->Label) == -1 )
			candidates->Add(item->Label);	

	for each(System::String^ label in candidates)
		Delete(label);		
}

/// Select media item with specific index
void HKCAppItem::Select(int _idx)
{
	if(_idx < 0 || _idx >= mp_Items->Count) return;
	Item = mp_Items[_idx];	
}

/// Select media item with specific label
void HKCAppItem::Select(System::String^ _label)
{
	HKCMediaItem^ item = Find(_label);
	if(item) Item = item;
}

/// Show media item with specific index
void HKCAppItem::Show(int _idx)
{
	if(_idx < 0 || _idx >= mp_Items->Count) return;
	HKCMediaItem^ item = mp_Items[_idx];
	std::string wndTitle = MarshalString(item->Label);
	switch(item->Media->Type())
	{
	case IMAGE:
	case VIDEO:
		{
			HKCImage* imgPtr = dynamic_cast<HKCImage*>(item->Media);
			cv::namedWindow(wndTitle);
			cv::imshow(wndTitle, imgPtr->Image());
		}
		break;
	default:
		Console::WriteLine("HKCAppItem::Show() : Not implemented!");
	}
}

/// Show media item with specific label
void HKCAppItem::Show(System::String^ _label)
{
	HKCMediaItem^ item = Find(_label);
	if(!item) return;
	int idx = mp_Items->IndexOf(item);
	Show(idx);
}

/// Move the media item to specific location in the list (0:top, -1:bottom)
void HKCAppItem::MoveTo(System::String^ _label, int _loc)
{
	HKCMediaItem^ item = Find(_label);
	if(!item || _loc >= mp_Items->Count) return;
	
	int idx = mp_Items->IndexOf(item);
	int newIdx = (_loc == -1) ? mp_Items->Count-1 : _loc;
	if(newIdx == idx) return;

	List<HKCMediaItem^>^ tmpItems = gcnew List<HKCMediaItem^>(mp_Items);
	for(int i = 0; i < tmpItems->Count; ++i)
	{
		if(i == newIdx) mp_Items[i] = tmpItems[idx];
		else if(i > newIdx && i <= idx) mp_Items[i] = tmpItems[i-1];
	}
}
