/**
* @file AppIOManagerDefault.cpp
*
* Implementation of the class methods for default I/O manager
*
* @author James Hung-Kuo Chu
*/

#include "stdafx.h"
#include "Form1.h"
#include "QRWordArt/QRWordArtIO.h"
#include "AppAlgoQRCodeRenderer.h"

using namespace System;
using namespace AppFrame;
using namespace System::Runtime::InteropServices;		
/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::HKCIOMgrDef

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCIOMgrDef::HKCIOMgrDef(void) 
{	
	m_ImageExts = "Windows bitmaps (*.bmp)|*.bmp|JPEG files (*.jpeg;*.jpg;*.jpe)|*.jpeg;*.jpg;*.jpe|PNG files (*.png)|*.png|TIFF files (*.tif)|*.tif";
	m_VideoExts = "AVI files (*.avi)|*.avi|WMV files (*.wmv)|*.wmv";
	m_AuxExts = "Config files (*.qrca)|*.qrca|Word Art files (*.wc)|*.wc|Result (*.png)|*.png";
	m_FlowExts ="Flow files (*.vfb)|*.vfb";
	m_LineExts ="Lines data files (*.wa;*.wc)|*.wa;*.wc";
	m_ArticleExts = "String data files (*.txt)|*.txt";
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCIOMgrDef::~HKCIOMgrDef(void)
{		
}

/*---------------------------------------------------------------------*/
/*                               IO                                    */
/// Read file
bool HKCIOMgrDef::Read(System::String^ _file, Form1^ _form, HKOGLPanelControl^ _glPanel)
{		
	System::String^ fileExt = Path::GetExtension(_file);
	if(m_AuxExts->Contains(fileExt))
	{
		if(System::String::Compare(fileExt, ".qrca") == 0)
		{
			if(!Read_Config(_file, _form, _glPanel))	
			{			
				Console::WriteLine("HKCIOMgrDef::Read() : Open config file failed");
				return false;				
			}		
		}
	}
	else
	{		
		/// Remove unnecessary layers
		if(_form->AppItem) _form->AppItem->DeleteEx(gcnew cli::array<System::String^>(1) {"QRCode"});
		return Read(_file, "Source", _form, _glPanel);
	}	

	return true;
}

/// Read a media item from file and assign it a specified label
bool HKCIOMgrDef::Read(System::String^ _file, System::String^ _label, Form1^ _form, HKOGLPanelControl^ _glPanel)
{
	_glPanel->Make_Current();

	HKCMedia* media = NULL;	
	System::String^ fileExt = Path::GetExtension(_file);
	if(m_ImageExts->Contains(fileExt))
	{	
		media = Read_Image(_file);
		if(!media) 
		{
			Console::WriteLine("HKCIOMgrDef::Read() : Open image failed");						
			return false;
		}		
	}
	else if(m_VideoExts->Contains(fileExt))
	{
		media = Read_Video(_file);
		if(!media) 
		{
			Console::WriteLine("HKCIOMgrDef::Read() : Open video failed");			
			return false;
		}		
	}	
	else
	{
		Console::WriteLine("HKCIOMgrDef::Read() : File format is not supported");		
		return false;
	}		
	
	if(!_form->AppItem)
	{
		/// Create a new application item if there is no existing one
		_form->AppItem = gcnew HKCAppItem;

		/// Initialize the application item
		_form->AppItem_Init(_form->AppItem);
	}

	HKCAppItem^ appItem = _form->AppItem;	

	/// If the layer is already there, delete it
	if(appItem->Find(_label)) appItem->Delete(_label);		

	/// Create a new media item	with specified layer label		
	appItem->Item = appItem->New(media, _label, _glPanel);			

	/// Activate the application item
	_form->AppItem_Activate(appItem);

	/// Focus on the application item
	_form->GLPanel_Focus(appItem);

	return true;
}

/// Write
bool HKCIOMgrDef::Write(System::String^ _file, Form1^ _form, HKOGLPanelControl^ _glPanel)
{
	if(!_form->AppItem) return false;

	System::String^ fileExt = Path::GetExtension(_file);
	if(m_AuxExts->Contains(fileExt))
	{
		if(System::String::Compare(fileExt, ".qrca") == 0)
		{
			if(!Write_Config(_file, _form, _glPanel))	
			{			
				Console::WriteLine("HKCIOMgrDef::Write() : Write config file failed");
				return false;			
			}		
		}
		else if(System::String::Compare(fileExt, ".wc") == 0)
		{
			HKCAppItem^	appItem = _form->AppItem;
			int id =    appItem->Data->CurrentWordArtID;
			if (!appItem->Data->WordArtData[id].splines.empty())
			{						
				QRWordArt::IO::SaveWordArt(appItem->Data->WordArtData[id].splines,(const char*)(Marshal::StringToHGlobalAnsi(_file)).ToPointer());
				_form->AppItem->Data->IO_Handle.wordart_filename = std::string((const char*)(Marshal::StringToHGlobalAnsi(_file)).ToPointer());
			}
		}
		else if(System::String::Compare(fileExt, ".png") == 0)
		{
			HKCAppItem^	appItem = _form->AppItem;
			cv::Mat result;
			AppAlgoQRCodeRenderer::GenResult(appItem,&result);
			AppAlgoQRCodeRenderer::AddQuietZone(result,&result);
			using namespace System::Runtime::InteropServices;
			cv::imwrite((const char*)(Marshal::StringToHGlobalAnsi(_file)).ToPointer(),result);
		}
	}

	return true;
}

/// Write a media item with specified label to file
bool HKCIOMgrDef::Write(System::String^ _file, System::String^ _label, Form1^ _form, HKOGLPanelControl^ _glPanel)
{
	if(!_form->AppItem) return false;
	HKCAppItem^ appItem = _form->AppItem;

	HKCMediaItem^ mediaItem = appItem->Find(_label);	
	if(!mediaItem)
	{
		Console::WriteLine("HKCIOMgrDef::Write() : Invalid media item");
		return false;
	}

	System::String^ fileExt = Path::GetExtension(_file);
	if(m_ImageExts->Contains(fileExt))
	{			
		/// IO Property					 
		if(mp_Prop) delete mp_Prop;
		mp_Prop = gcnew HKCIIOProp;	

		return mediaItem->Media->Write(MarshalString(_file), *(mp_Prop->Param));
	}
	else if(m_VideoExts->Contains(fileExt))
	{		
		return false;
	}	
	else
	{
		Console::WriteLine("HKCIOMgrDef::Write() : File format is not supported");		
		return false;
	}	
}

/// Read image file
HKCMedia* HKCIOMgrDef::Read_Image(System::String^ _file)
{
	/// IO Property					 
	if(mp_Prop) delete mp_Prop;
	mp_Prop = gcnew HKCIIOProp;	
	
	/*InputForm^ input_form = Create_InputForm(mp_IOProp, Drawing::Size(280, 360), L"Image I/O Options");
	input_form->StartPosition = FormStartPosition::CenterParent;				 
	if(input_form->ShowDialog() == Windows::Forms::DialogResult::OK)*/
	HKCIIOProp^ ioProp = (HKCIIOProp^)mp_Prop;
	ioProp->Color_Type = HKEColorT::UNCHANGE;

	/// read image from file
	HKCMedia* media = new HKCImage;					 	
	if(!media->Read(MarshalString(_file), *(mp_Prop->Param)))
	{
		Console::WriteLine("HKCIOMgrDef::Read_Image() : Read image failed");	
		delete media;
		return NULL;
	}

	/// return the new media
	return media;
}

/// Read video file
HKCMedia* HKCIOMgrDef::Read_Video(System::String^ _file)
{
	/// IO Property					 
	if(mp_Prop) delete mp_Prop;
	mp_Prop = gcnew HKCVIOProp;	

	/*InputForm^ input_form = Create_InputForm(mp_IOProp, Drawing::Size(280, 360), L"Image I/O Options");
	input_form->StartPosition = FormStartPosition::CenterParent;				 
	if(input_form->ShowDialog() == Windows::Forms::DialogResult::OK)*/

	/// read video from file
	HKCMedia* media = new HKCVideo;					 	
	if(!media->Read(MarshalString(_file), *(mp_Prop->Param)))
	{
		Console::WriteLine("HKCIOMgrDef::Read_Video() : Read video failed");	
		delete media;
		return NULL;
	}

	/// return the new media
	return media;
}

/// Read configuration file
bool HKCIOMgrDef::Read_Config(System::String^ _file, Form1^ _form, HKOGLPanelControl^ _glPanel)
{
	HKCAppCfgFile^ cfgFile = gcnew HKCAppCfgFile;
	return cfgFile->Read(_file, _form, _glPanel);
}

/// Write configuration file
bool HKCIOMgrDef::Write_Config(System::String^ _file, Form1^ _form, HKOGLPanelControl^ _glPanel)
{	
	HKCAppCfgFile^ cfgFile = gcnew HKCAppCfgFile;
	return cfgFile->Write(_file, _form, _glPanel);
}

/// Read pattern database file
bool HKCIOMgrDef::Read_PatternDB(System::String^ _file, Form1^ _form, HKOGLPanelControl^ _glPanel)
{	
// 	if(!_form->AppItem)
// 	{
// 		/// Create a new application item if there is no existing one
// 		_form->AppItem = gcnew HKCAppItem;
// 
// 		/// Initialize the application item
// 		_form->AppItem_Init(_form->AppItem);
// 	}
// 	HKCAppItem^ appItem = _form->AppItem;	
// 
// 	StreamReader^ file_sr = gcnew StreamReader(_file);
// 	System::String^	file_dir = Path::GetDirectoryName(_file);
// 	System::String^	line_input;
// 
// 	/// Get data ready
// 	HKCPDBParam^ pdbParam = appItem->Param->PDB;
// 	HKCPDBData& pdbData = appItem->Data->PDBData;	
// 	pdbData.Clear(); /// Clear old data	
// 
// 	/// Get the size of pattern
// 	line_input = file_sr->ReadLine();
// 	cli::array<System::Char>^ chars = {' ',','};
// 	cli::array<System::String^>^ split = line_input->Split(chars);
// 	int pSize = System::Convert::ToInt32(split[0]);
// 	if(pSize != 3) 
// 	{
// 		Console::WriteLine("HKCIOMgrDef::Read_PatternDB() : Invalid size of pattern!");
// 		file_sr->Close();	
// 		return false;
// 	}
// 	pdbParam->PSize = pSize;
// 	pdbData.PSize = pSize;
// 
// 
// 	/// Read pattern data
// 	int pNum = (int)Math::Pow(2, pSize*pSize);	
// 	VecPtrn& patterns = pdbData.Patterns;
// 	patterns.resize(pNum, NULL);
// 	for(int i = 0; i < pNum; ++i)
// 	{
// 		line_input = file_sr->ReadLine();
// 		cli::array<System::Char>^ chars = {' ',','};
// 		cli::array<System::String^>^ split = line_input->Split(chars);
// 
// 		HKCPattern* ptrnPtr = new HKCPattern;
// 		ptrnPtr->ID = System::Convert::ToInt32(split[0]);
// 		ptrnPtr->RVal = System::Convert::ToDouble(split[1]);
// 		ptrnPtr->RVal2 = ptrnPtr->RVal;
// 		patterns[ptrnPtr->ID] = ptrnPtr;		
// 	}
// 
// 	file_sr->Close();
// 
// 	/// Process the database
// 	HKCAlgorithm^ pdbObject = gcnew HKCPDBProc1;
// 	if(!pdbObject->Execute(appItem))
// 	{
// 		Console::WriteLine(pdbObject->Abbrev + ": Failed!");	
// 		return false;
// 	}

	return true;
}