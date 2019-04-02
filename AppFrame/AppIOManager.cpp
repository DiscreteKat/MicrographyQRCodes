/**
* @file AppIOManager.cpp
*
* Implementation of the class methods for application I/O manager
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "AppIOManager.h"

using namespace AppFrame;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::HKCAppIOMgr

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCAppIOMgr::HKCAppIOMgr(void) 
{
	mp_Prop = nullptr;
	m_ImageExts = "";
	m_FlowExts ="";
	m_VideoExts = "";
	m_AuxExts = "";
	m_LineExts = "";
	m_ArticleExts ="";
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCAppIOMgr::~HKCAppIOMgr(void)
{	
	delete mp_Prop;
	mp_Prop = nullptr;	
}