/**
* @file AppGlobal.h
*
* Application global variables
*
* @author James Hung-Kuo Chu
*/

#ifndef _APPGLOBAL_H_
#define _APPGLOBAL_H_

using namespace AppFrame;
using namespace System;
using namespace System::IO;

/// Global macros
//#define RAND_SCALE (rand()/(RAND_MAX*1.f))
extern cv::RNG g_RNG;

/**
*	@brief Class for storing static global variables
*/
public ref class AppGlobal abstract sealed
{
public:	
	static Form1^			g_Form = nullptr;		///< Global pointer to the application form		

	static System::String^	g_PntrLabel;			///< Label for painter tool
	static System::String^	g_GCLabel;				///< Label for GrabCut tool
	static System::String^	g_MPlyrLabel;			///< Label for media player tool
	static System::String^	g_XFormLabel;			///< Label for transformation tool

	static bool				g_Debug = true;			///< Flag of debug mode
	static bool				g_Dump = true;			///< Flag of dump debug information to file

	/// I/O information
	static StreamWriter^	g_StrmWriter = nullptr;	///< Global stream writer object (for debuging)
	static System::String^	g_AppDir;				///< Folder of the application executable
	static System::String^	g_PrjDir;				///< Folder of the project
	static System::String^  g_DebugDir;				///< Folder of the debug file
	static System::String^  g_CfgDir;				///< Folder of the configuration file
	static System::String^  g_CfgParentDir;			///< Parent folder of the configuration file
	static System::String^  g_CfgName;				///< Name of the configuration file
	static System::String^  g_TempStr;				///< Temporary string
};

#endif
