/**
* @file Form_Item.cpp
*
* Implementation of AppItem operations
*
* @author James Hung-Kuo Chu
*/

#include "StdAfx.h"
#include "Form1.h"
#include "AppUtils.h"

using namespace AppFrame;
using namespace DevComponents::DotNetBar;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::Form1

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                       AppItem operations                            */
/// Initialize the application item
void Form1::AppItem_Init(HKCAppItem^ _appItem)
{
	if(!_appItem) return;	

	/////////////////////////////////////////////////
	/// Initialize application properties
	/////////////////////////////////////////////////
	HKCAppProp^	appProp	= _appItem->Prop;	

	/////////////////////////////////////////////////
	/// Initialize application parameters
	/////////////////////////////////////////////////
	HKCAppParam^ appParam = _appItem->Param;		

	HKCQRCParam^ qrcParam = appParam->QRCode;
	qrcParam->PropertyChanged += gcnew ParamEventHandler(this, &Form1::QRCParam_PropertyValueChanged);
	qrcParam->Text = "";
	qrcParam->Version = 5;
	qrcParam->ECLvl = HKEECL::ECL_H;
	qrcParam->Da = 3;
	qrcParam->Wa = 9;	

	HKCWordArtParam^ wortartParam = appParam->WordArt;
	wortartParam->PropertyChanged += gcnew ParamEventHandler(this, &Form1::QRCParam_PropertyValueChanged);
	wortartParam->Boundary_Repela=1;
	wortartParam->Line_Repela=1.6;
	wortartParam->Boundary_Repelb=2.5;
	wortartParam->Line_Repelb=0.5;
	wortartParam->RangeSize=6;
	wortartParam->SmallRangeSize=4;
	wortartParam->LineSpace=0.5;
	wortartParam->SmallRangeRatio=10;
	wortartParam->TextType=1;
	wortartParam->ColorAdjustW=0.3;
	wortartParam->ColorAdjustAlgo=2;
}

/// Active the application item
void Form1::AppItem_Activate(HKCAppItem^ _appItem)
{
	if(!_appItem) return;	

	/// Build layers
	mp_AppLayerMgr->Build(this->LayerTree, _appItem);	

	mp_AppLayerMgr->Build(this->LayerTree, _appItem);	

	/// Update tools
	mp_AppToolMgr->Update(mp_AppItem, this);	

	/// set property grids
	this->ParamGrid->SelectedObject	= _appItem->Param;
	this->PropGrid->SelectedObject	= _appItem->Prop;
	this->Refresh();
}