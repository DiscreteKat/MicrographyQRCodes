/**
* @file AppToolManager.cpp
*
* Implementation of the class methods for application tool manager
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "AppProperty.h"
#include "AppTool.h"
#include "AppToolManager.h"

using namespace AppFrame;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::HKCAppToolMgr

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCAppToolMgr::HKCAppToolMgr(void) 
{	
	mp_Tools = gcnew List<HKCAppTool^>;
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCAppToolMgr::~HKCAppToolMgr(void)
{	
	for each(HKCAppTool^ tool in mp_Tools)	
		delete tool;	
	mp_Tools->Clear();
}

/*---------------------------------------------------------------------*/
/*                             Operations                              */
/// Add a new tool
bool HKCAppToolMgr::Add(HKCAppTool^ _tool)
{
	if(!_tool) return false;
	mp_Tools->Add(_tool);
	return true;
}

/// Find tool with specific label
HKCAppTool^ HKCAppToolMgr::Find(System::String^ _label)
{
	for each(HKCAppTool^ tool in mp_Tools)
	{
		if(System::String::Compare(_label, tool->Label)==0)
			return tool;
	}
	return nullptr;
}

/// Delete tool at specific index
bool HKCAppToolMgr::Delete(int _idx)
{
	if(_idx < 0 || _idx >= mp_Tools->Count) return false;	
	delete mp_Tools[_idx];
	mp_Tools->RemoveAt(_idx);
	return true;
}

/// Delete tool with specific label
bool HKCAppToolMgr::Delete(System::String^ _label)
{
	HKCAppTool^ tool = Find(_label);
	if(!tool) return false;
	int idx = mp_Tools->IndexOf(tool);
	return Delete(idx);	
}