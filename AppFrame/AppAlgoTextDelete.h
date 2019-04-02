#pragma once

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"

#include <map>
#include "QRWordARt/QRCharacter.h"
#include "QRWordARt/QRStringLine.h"
#include "QRWordArt/QRCharFBO.h"

//Error Correction 
namespace AppFrame 
{
	public ref class AppAlgoTextDelete : public HKCAlgorithm
	{
	public:
		static double DPercent = 0;
		typedef std::map<QRWordArt::QRCharacter::Char*,std::vector<int>> CQRMap;
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		
		AppAlgoTextDelete(void){}
		virtual ~AppAlgoTextDelete(void){}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Algorithm Operations						   */
		/*! \{                                                                 */	
		virtual bool Execute(HKCAppItem^ _appItem) override;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Access Methods                              */
		/*! \{                                                                 */

		virtual property System::String^ Abbrev
		{
			System::String^ get(void) override { return "Spline Width Adjustment"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"Spline Width Adjustment";
		}	
	};
}