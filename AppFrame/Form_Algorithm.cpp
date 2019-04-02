/**
* @file Form_Algorithm.cpp
*
* Implementation of algorithm functions
*
* @author James Hung-Kuo Chu
*/

#include "StdAfx.h"
#include "Form1.h"

using namespace AppFrame;
using namespace DevComponents::DotNetBar;
using namespace HKOGLPanel;
using namespace System::Collections::Generic;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::Form1

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                        Algorithm functions                          */
/// Algorithm process
void Form1::Process(System::String^ _action)
{
	if(!mp_AppItem) return;
	
// 	HKCAppParam^ appParam = mp_AppItem->Param;	
// 	
// 	/// Collect all algorithm objects
// 	List<HKCAlgorithm^>^ algoObjs = gcnew List<HKCAlgorithm^>;
// 
// 	/// Data initialization
// 	algoObjs->Add(gcnew HKCDataInit1);
// 
// 	/// Feature map
// 	HKCFetrParam^ fetrMap = appParam->FetrMap;
// 	switch(fetrMap->Method)
// 	{
// 	case HKEFetrM::FDOG_EDGE:
// 		algoObjs->Add(gcnew HKCFDoGFetr);
// 		break;
// 	/*case HKEFetrM::CANNY_EDGE:
// 		algoObjs->Add(gcnew HKCFetrImp);
// 		break;*/
// 	}	
// 
// 	/// Importance map
// 	HKCImpParam^ impMap = appParam->ImpMap;
// 	switch(impMap->Method)
// 	{
// 	case HKEImpM::UNITY:
// 		algoObjs->Add(gcnew HKCUnityImp);
// 		break;
// 	case HKEImpM::FEATURE_BASED:
// 		algoObjs->Add(gcnew HKCFetrImp);
// 		break;
// 	}
// 
// 	/// Image halftoning
// 	HKCHftnParam^ halftone = appParam->Halftone;
// 	switch(halftone->Method)
// 	{
// 	case HKEHftnM::SIMPLE_ED:
// 		algoObjs->Add(gcnew HKCVCEDHftn);
// 		break;
// 	case HKEHftnM::STRUCT_AWARE_ED:
// 		algoObjs->Add(gcnew HKCSAEDHftn);
// 		break;
// 	}		
// 
// 	/// Optimization
// 	HKCOptmParam^ optimz = appParam->Optimize;
// 	switch(optimz->Method)
// 	{
// 	case HKEOptmM::NN1:
// 		algoObjs->Add(gcnew HKCNNOptmzr);
// 		break;
// 	case HKEOptmM::NN2:
// 		algoObjs->Add(gcnew HKCNN2Optmzr);
// 		break;
// 	case HKEOptmM::UGC:
// 		algoObjs->Add(gcnew HKCUGCOptmzr);
// 		break;
// 	case HKEOptmM::CGC:
// 		algoObjs->Add(gcnew HKCCGCOptmzr);
// 		break;
// 	case HKEOptmM::ICGC:
// 		algoObjs->Add(gcnew HKCICGCOptmzr);
// 		break;
// 	case HKEOptmM::TEST:
// 		algoObjs->Add(gcnew HKCTestOptmzr);
// 		break;
// 	}	
// 
// 	/// Image composition
// 	algoObjs->Add(gcnew HKCDefComposr);
// 
// 	/// Add ZBar verification
// 	HKCZBarParam^ zBar = appParam->ZBar;
// 	if(zBar->Enabled) algoObjs->Add(gcnew HKCZBarVerify);	
// 
// 	HKCTimer* timer	= HKCTimer::InstancePtr();
// 	timer->Clear();
// 	timer->Enabled() = true;
// 	timer->Start("Total");
// 	
// 	/// Go through each object and execute the algorithm
// 	for each(HKCAlgorithm^ algoObj in algoObjs)
// 	{
// 		timer->Start(MarshalString(algoObj->ToString()));
// 		if(!algoObj->Execute(mp_AppItem))
// 		{
// 			Console::WriteLine(algoObj->Abbrev + ": Failed!");
// 			break;
// 		}
// 		timer->End(MarshalString(algoObj->ToString()));
// 	}
// 
// 	timer->End("Total");	
// 	timer->ShowAll();
// 
// 	/// Debugging
// 	if(AppGlobal::g_Debug)
// 	{
// 		HKCAlgorithm^ debugObj = gcnew HKCDebugger;	
// 		debugObj->Execute(mp_AppItem);
// 	}
// 
// 	/// Rebuild layers
// 	mp_AppLayerMgr->Build(this->LayerTree, mp_AppItem);	
}
