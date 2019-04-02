/**
* @file AppConfigSection.cpp
*
* Implementation of the class methods for processing application config file
*
* @author James Hung-Kuo Chu
*/

#include "stdafx.h"
#include "Form1.h"

using namespace System;
using namespace AppFrame;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::HKCAppCfgSec

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCAppCfgSec::HKCAppCfgSec(void) 
{		
	mp_Maps = NULL;
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCAppCfgSec::~HKCAppCfgSec(void)
{		
	if(mp_Maps) delete mp_Maps;
}

/*---------------------------------------------------------------------*/
/*                            Operations                               */
/// Actions to do during the course of within a section
bool HKCAppCfgSec::Parse(System::String^ _file, System::String^ _line, Form1^ _form, HKOGLPanelControl^ _glPanel)
{	
	/// Skip empty line or comment (#)
	System::String^ trimLine = _line->Trim();
	if(trimLine->Length == 0 || trimLine[0] == '#') return true;	

	cli::array<System::Char>^ chars = {'='};
	cli::array<System::String^>^ split = _line->Split(chars);
	if(split->Length <= 1) return false;	

	/// Find the first occurence of "="		
	std::string key = MarshalString(split[0]);
	std::string value = MarshalString(_line->Substring(_line->IndexOf('=')+1));

	(*mp_Maps)[key] = value;

	return true;
}

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::HKCAppCfgSrc

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCAppCfgSrc::HKCAppCfgSrc(void) 
{
	mp_Maps = new std::map<std::string, std::string>;
	mp_Maps->insert(std::make_pair("Image",""));
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCAppCfgSrc::~HKCAppCfgSrc(void)
{		
	mp_Maps->clear();
}

/*---------------------------------------------------------------------*/
/*                            Operations                               */
/// Actions to do when a section is ended
bool HKCAppCfgSrc::End(System::String^ _file, System::String^ _line, Form1^ _form, HKOGLPanelControl^ _glPanel)
{
	if(_form->AppItem) _form->AppItem->Clear();

	/// Get file path
	System::String^ file_name = gcnew System::String((*mp_Maps)["Image"].c_str());
	System::String^	file_dir = Path::GetDirectoryName(_file);
	System::String^ file_path = System::String::Concat(file_dir, L"\\", file_name);	

	/// Read file and assign it label "Source"
	if(!_form->IOManager->Read(file_path, "Source", _form, _glPanel))
	{
		Console::WriteLine("HKCAppCfgSrc::End() : Read source image failed!");
		return false;
	}

	return true;
}

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::HKCAppCfgMask

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCAppCfgWordArt::HKCAppCfgWordArt(void) 
{
	mp_Maps = new std::map<std::string, std::string>;
	mp_Maps->insert(std::make_pair("Segment",""));
	mp_Maps->insert(std::make_pair("Strings",""));
	mp_Maps->insert(std::make_pair("Gap",""));
	mp_Maps->insert(std::make_pair("Color Mode",""));
	mp_Maps->insert(std::make_pair("Range Size",""));
	mp_Maps->insert(std::make_pair("Boundary Repel",""));
	mp_Maps->insert(std::make_pair("Line Repel",""));
	mp_Maps->insert(std::make_pair("Scale",""));
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCAppCfgWordArt::~HKCAppCfgWordArt(void)
{		
	mp_Maps->clear();
}

/*---------------------------------------------------------------------*/
/*                            Operations                               */
/// Actions to do when a section is ended
bool HKCAppCfgWordArt::End(System::String^ _file, System::String^ _line, Form1^ _form, HKOGLPanelControl^ _glPanel)
{
	if(!_form->AppItem || !_form->AppItem->Find("Source"))
	{
		Console::WriteLine("HKCAppCfgMask::End() : No source image is found!");		
		return false;
	}
	System::String^	file_name;
	System::String^	file_dir = Path::GetDirectoryName(_file);;
	System::String^	file_path;
	/// Get file path
	file_name = gcnew System::String((*mp_Maps)["Gap"].c_str());
	if (file_name->Length!=0)
	{
		file_path = System::String::Concat(file_dir, L"\\", file_name);
	    _form->AppItem->Data->IO_Handle.gap_filename = MarshalString(file_path);
		_form->AppItem->Data->WordArtEvi.gap_img = cv::imread(MarshalString(file_path),CV_LOAD_IMAGE_GRAYSCALE);
	}

	file_name = gcnew System::String((*mp_Maps)["Segment"].c_str());
	file_path = System::String::Concat(file_dir, L"\\", file_name);	
	
	_form->AppItem->Data->IO_Handle.seg_filename = MarshalString(file_path);
	_form->WordArt_Action("LOADSEG");

	
	
	_form->AppItem->Param->WordArt->strings = gcnew System::String((*mp_Maps)["Strings"].c_str());
	_form->WordArt_Action("Strings");

	HKCWordArtParam^ waParam = _form->AppItem->Param->WordArt;		
	if ( _form->AppItem->Data->IO_Handle.config_ver >=2 )
	{
		waParam->ColorMode = (AppFrame::WORDART_COLOR)System::Convert::ToInt32(gcnew System::String((*mp_Maps)["Color Mode"].c_str())); 
		waParam->Boundary_Repela = System::Convert::ToDouble(gcnew System::String((*mp_Maps)["Boundary Repela"].c_str())); 
		waParam->Line_Repela = System::Convert::ToDouble(gcnew System::String((*mp_Maps)["Line Repela"].c_str())); 
		waParam->Boundary_Repelb = System::Convert::ToDouble(gcnew System::String((*mp_Maps)["Boundary Repelb"].c_str())); 
		waParam->Line_Repelb = System::Convert::ToDouble(gcnew System::String((*mp_Maps)["Line Repelb"].c_str())); 
		waParam->RangeSize = System::Convert::ToDouble(gcnew System::String((*mp_Maps)["Range Size"].c_str())); 
	}
	 

	return true;
}
/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::HKCAppCfgQRC

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCAppCfgQRC::HKCAppCfgQRC(void) 
{
	mp_Maps = new std::map<std::string, std::string>;
	mp_Maps->insert(std::make_pair("Text",""));
	mp_Maps->insert(std::make_pair("Version",""));
	mp_Maps->insert(std::make_pair("ECLLevel",""));
	mp_Maps->insert(std::make_pair("PSize",""));
	mp_Maps->insert(std::make_pair("Da",""));
	mp_Maps->insert(std::make_pair("USEFULLSIZE",""));
	mp_Maps->insert(std::make_pair("Offset",""));
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCAppCfgQRC::~HKCAppCfgQRC(void)
{		
	mp_Maps->clear();
}

/*---------------------------------------------------------------------*/
/*                            Operations                               */
/// Actions to do when a section is ended
bool HKCAppCfgQRC::End(System::String^ _file, System::String^ _line, Form1^ _form, HKOGLPanelControl^ _glPanel)
{
	if(!_form->AppItem)
	{
		Console::WriteLine("HKCAppCfgQRC::End() : No application item is found!");		
		return false;
	}

	HKCQRCParam^ qrcParam = _form->AppItem->Param->QRCode;		

	qrcParam->Text = gcnew System::String((*mp_Maps)["Text"].c_str());
	qrcParam->Version = System::Convert::ToInt32(gcnew System::String((*mp_Maps)["Version"].c_str()));
	qrcParam->ECLvl = HKEECL(System::Convert::ToInt32(gcnew System::String((*mp_Maps)["ECLLevel"].c_str())));
	
	if ( _form->AppItem->Data->IO_Handle.config_ver >=2 )
	{
		qrcParam->Da = System::Convert::ToInt32(gcnew System::String((*mp_Maps)["Da"].c_str())); 
	}

	qrcParam->Wa = System::Convert::ToInt32(gcnew System::String((*mp_Maps)["PSize"].c_str()));

	if (_form->AppItem->Data->IO_Handle.config_ver >=3 )
	{
		System::String^ strings=gcnew System::String((*mp_Maps)["Offset"].c_str());
		cli::array<System::Char>^ chars = {' '};
		cli::array<System::String^>^ split = strings->Split(chars);
		qrcParam->offsetX=System::Convert::ToDouble(split[0]);
		qrcParam->offsetY=System::Convert::ToDouble(split[1]);
	}

	
	/// Generate QR code
	if(qrcParam->Text->Length != 0)	
		_form->QRC_Action("GENERATE");

	return true;
}

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::HKCAppCfgCtrstP

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCAppCfgVFB::HKCAppCfgVFB(void) 
{
	mp_Maps = new std::map<std::string, std::string>;
	mp_Maps->insert(std::make_pair("Field",""));	
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCAppCfgVFB::~HKCAppCfgVFB(void)
{		
	mp_Maps->clear();
}

/*---------------------------------------------------------------------*/
/*                            Operations                               */
/// Actions to do when a section is ended
bool HKCAppCfgVFB::End(System::String^ _file, System::String^ _line, Form1^ _form, HKOGLPanelControl^ _glPanel)
{
	if(!_form->AppItem || !_form->AppItem->Find("Source"))
	{
		Console::WriteLine("HKCAppCfgCtrstP::End() : No source image is found!");		
		return false;
	}

	System::String^ file_name = gcnew System::String((*mp_Maps)["Field"].c_str());
	System::String^	file_dir = Path::GetDirectoryName(_file);
	System::String^ file_path = System::String::Concat(file_dir, L"\\", file_name);	

	_form->AppItem->Data->IO_Handle.vbf_filename = MarshalString(file_path);
	_form->WordArt_Action("LOADVFB");

	return true;
}
/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCAppCfgREGP::HKCAppCfgREGP(void) 
{
	mp_Maps = new std::map<std::string, std::string>;
	mp_Maps->insert(std::make_pair("Size",""));
	mp_Maps->insert(std::make_pair("Param",""));
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCAppCfgREGP::~HKCAppCfgREGP(void)
{		
	mp_Maps->clear();
}

/*---------------------------------------------------------------------*/
/*                            Operations                               */
/// Actions to do when a section is ended
bool HKCAppCfgREGP::End(System::String^ _file, System::String^ _line, Form1^ _form, HKOGLPanelControl^ _glPanel)
{
	if(!_form->AppItem || !_form->AppItem->Find("Source"))
	{
		Console::WriteLine("HKCAppCfgREG::End() : No source image is found!");		
		return false;
	}
	Region_size=System::Convert::ToInt32(gcnew System::String((*mp_Maps)["Size"].c_str()));
	if (_form->AppItem->Data->WordArtEvi.region_segs.size()!=Region_size)
	{
		Console::WriteLine("HKCAppCfgREGp::End() : Error region number!");		
		return false;
	}
	System::String^ strings=gcnew System::String((*mp_Maps)["Param"].c_str());
	cli::array<System::Char>^ chars = {' '};
	cli::array<System::String^>^ split = strings->Split(chars);
	if (split->Length!=6*Region_size)
	{
		Console::WriteLine(split->Length);
		Console::WriteLine("HKCAppCfgREGp::End() : Error region data!");
		return false;
	}
	vector<RegionParam>& region_params = _form->AppItem->Data->WordArtEvi.region_params;
	for (int r =0 ; r<Region_size;r++)
	{	
		region_params[r].smallregion=System::Convert::ToBoolean(split[r*6+0]);
		region_params[r].RangeSize=System::Convert::ToInt32(split[r*6+1]);			
		region_params[r].Boundary_Repela=System::Convert::ToDouble(split[r*6+2]);
		region_params[r].Line_Repela=System::Convert::ToDouble(split[r*6+3]);
		region_params[r].Boundary_Repelb=System::Convert::ToDouble(split[r*6+4]);
		region_params[r].Line_Repelb=System::Convert::ToDouble(split[r*6+5]);		
	}

	return true;
}

AppFrame::HKCAppCfgVer::HKCAppCfgVer( void )
{
	mp_Maps = new std::map<std::string, std::string>;
	mp_Maps->insert(std::make_pair("Version",""));	
}

AppFrame::HKCAppCfgVer::~HKCAppCfgVer( void )
{
	mp_Maps->clear();
}

bool AppFrame::HKCAppCfgVer::End( System::String^ _file, System::String^ _line, Form1^ _form, HKOGLPanelControl^ _glPanel )
{
	int& config_ver = _form->AppItem->Data->IO_Handle.config_ver;
	config_ver = System::Convert::ToInt32(gcnew System::String((*mp_Maps)["Version"].c_str()));
	std::cout<<"Config Version: "<<config_ver<<std::endl;
	return true;
}