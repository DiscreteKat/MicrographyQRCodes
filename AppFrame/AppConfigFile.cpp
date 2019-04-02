/**
* @file AppConfigFile.cpp
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
/*! \class AppFrame::HKCAppCfgFile

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCAppCfgFile::HKCAppCfgFile(void) 
{		
	mp_Section = nullptr;
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCAppCfgFile::~HKCAppCfgFile(void)
{	
	if(mp_Section) delete mp_Section;
}

/*---------------------------------------------------------------------*/
/*                               IO                                    */
/// Read file
bool HKCAppCfgFile::Read(System::String^ _file, Form1^ _form, HKOGLPanelControl^ _glPanel)
{			
	StreamReader^ file_sr = gcnew StreamReader(_file);
	System::String^	file_dir = Path::GetDirectoryName(_file);
	System::String^	line_input;

	AppGlobal::g_CfgDir = file_dir + L"\\";
	AppGlobal::g_CfgParentDir = Path::GetDirectoryName(file_dir) + L"\\";
	AppGlobal::g_CfgName = Path::GetFileNameWithoutExtension(_file);

	List<System::String^>^ cfgSections = gcnew List<System::String^>();
	cfgSections->Add(L"[Version]");			const int verName	= 0;
	cfgSections->Add(L"[Source]");			const int srcName	= 1;
	cfgSections->Add(L"[QRCode]");			const int qrcName	= 2;
	cfgSections->Add(L"[WordArt]");			const int wadName	= 3;
	cfgSections->Add(L"[VectorField]");		const int vfbName	= 4;
	cfgSections->Add(L"[Region Param]");    const int regpName	= 5;
	while((line_input = file_sr->ReadLine()) != nullptr)
	{
		int firstP = line_input->IndexOf('[');
		int lastP = line_input->LastIndexOf(']');
		int secName = -1;		
		if(firstP != -1 && lastP != -1 && firstP < lastP)
		{
			System::String^ subStr = line_input->Substring(firstP, lastP+1);
			secName = cfgSections->IndexOf(subStr);
		}

		if(secName == -1)
		{
			if(mp_Section) 
				mp_Section->Parse(_file, line_input, _form, _glPanel);
		}
		else
		{
			if(mp_Section) mp_Section->End(_file, line_input, _form, _glPanel);
			switch(secName)
			{
			case verName:
				Section = gcnew HKCAppCfgVer;
				break;
			case srcName:
				Section = gcnew HKCAppCfgSrc;
				break;
			case qrcName:
				Section = gcnew HKCAppCfgQRC;
				break;
			case wadName:
				Section = gcnew HKCAppCfgWordArt;
				break;
			case vfbName:
				Section = gcnew HKCAppCfgVFB;
				break;
			case regpName:
				Section = gcnew HKCAppCfgREGP;
				break;
			default:
				Section = nullptr;
			}
			if(mp_Section) mp_Section->Begin(_file, line_input, _form, _glPanel);
		}
	}

	if(mp_Section) mp_Section->End(_file, line_input, _form, _glPanel);
	file_sr->Close();
	return true;
}

/// Write
bool HKCAppCfgFile::Write(System::String^ _file, Form1^ _form, HKOGLPanelControl^ _glPanel)
{	
	StreamWriter^	file_sw = gcnew StreamWriter(_file);
	System::String^	file_dir = Path::GetDirectoryName(_file);
	System::String^	file_name = Path::GetFileNameWithoutExtension(_file);
	System::String^	file_ext = Path::GetExtension(_file);	
	System::String^	full_path;

	System::String^ aux_file;
	HKCAppItem^		appItem = _form->AppItem;		
	HKCAppParam^	appParam = appItem->Param;	

	AppGlobal::g_CfgDir = file_dir + L"\\";
	AppGlobal::g_CfgParentDir = Path::GetDirectoryName(file_dir) + L"\\";
	AppGlobal::g_CfgName = Path::GetFileNameWithoutExtension(_file);

	

	/////////////////////////////////////////////////
	/// Source
	/////////////////////////////////////////////////
	HKCMediaItem^ srcItem = appItem->Find("Source");	
	if(srcItem)
	{		
		file_sw->WriteLine(L"[Source]");
		file_sw->WriteLine(L"Image=" + srcItem->Prop->FileName);	
	}	

	/////////////////////////////////////////////////
	/// Config Version
	/////////////////////////////////////////////////
	file_sw->WriteLine(L"[Version]");
	file_sw->WriteLine(L"Version=3");

	/////////////////////////////////////////////////
	/// Write QR code data
	/////////////////////////////////////////////////
	HKCQRCData& qrcData = appItem->Data->QRCData;
	HKCQRCParam^ qrcParam = appItem->Param->QRCode;
	file_sw->WriteLine(L"[QRCode]");
	file_sw->WriteLine(L"Text=" + qrcParam->Text);		
	file_sw->WriteLine(L"Version=" + Int32(qrcParam->Version).ToString());
	file_sw->WriteLine(L"ECLLevel=" + Int32(qrcParam->ECLvl).ToString());	
	file_sw->WriteLine(L"PSize=" + Int32(appItem->Data->QRCData.module_size).ToString());
	//Ver2
	file_sw->WriteLine(L"Da=" + Int32(appItem->Data->QRCData.center_size).ToString());
	//Ver3
	file_sw->WriteLine(L"Offset=" + Int32(appItem->Data->QRCData.offset.x).ToString()+L" "+Int32(appItem->Data->QRCData.offset.y).ToString());
	/////////////////////////////////////////////////
	/// Write Word Art data
	/////////////////////////////////////////////////
 	file_sw->WriteLine(L"[WordArt]");
	String^ seg_file = gcnew String(_form->AppItem->Data->IO_Handle.seg_filename.c_str());
	file_sw->WriteLine(L"Segment=" +  Path::GetFileName(seg_file));	
	if (_form->AppItem->Data->IO_Handle.gap_filename!="")
	{
		String^ gap_file = gcnew String(_form->AppItem->Data->IO_Handle.gap_filename.c_str());
		file_sw->WriteLine(L"Gap=" +  Path::GetFileName(gap_file));	
	}
 	file_sw->WriteLine(L"Strings=" + appParam->WordArt->strings);
	//Ver2
	int color_mode = (int)appParam->WordArt->ColorMode;
	file_sw->WriteLine(L"Color Mode=" + color_mode);
	file_sw->WriteLine(L"Range Size=" + appParam->WordArt->RangeSize);
	file_sw->WriteLine(L"Boundary Repela=" + appParam->WordArt->Boundary_Repela);
	file_sw->WriteLine(L"Line Repela=" + appParam->WordArt->Line_Repela);
	file_sw->WriteLine(L"Boundary Repelb=" + appParam->WordArt->Boundary_Repelb);
	file_sw->WriteLine(L"Line Repelb=" + appParam->WordArt->Line_Repelb);
	/////////////////////////////////////////////////
	/// Write Vector Field data
	/////////////////////////////////////////////////
	if (_form->AppItem->Data->IO_Handle.vbf_filename!="")
	{
		file_sw->WriteLine(L"[VectorField]");
		String^ vfb_file = gcnew String(_form->AppItem->Data->IO_Handle.vbf_filename.c_str());
		file_sw->WriteLine(L"Field=" + Path::GetFileName(vfb_file));	
	}
	/////////////////////////////////////////////////
	/// Write Region Param data
	/////////////////////////////////////////////////
	file_sw->WriteLine(L"[Region Param]");
	vector<RegionParam>& region_params=_form->AppItem->Data->WordArtEvi.region_params;
	file_sw->WriteLine(L"Size="+region_params.size());
	file_sw->Write(L"Param=");
	for (int r =0 ; r <region_params.size();r++)
	{
		if (r!=0)
		{
			file_sw->Write(L" ");
		}
		file_sw->Write(region_params[r].smallregion+L" "+region_params[r].RangeSize+L" "+region_params[r].Boundary_Repela+L" "+region_params[r].Line_Repela+L" "+region_params[r].Boundary_Repelb+L" "+region_params[r].Line_Repelb);
	}
	file_sw->Close();
	return true;
}
