#pragma once

#include "AppAlgorithm.h"

namespace AppFrame 
{
	/**
	*	@brief Class for generating layer images
	*/
	public ref class AppAlgoQRCBGColor : public HKCAlgorithm
	{
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~AppAlgoQRCBGColor(void) {}		

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
			System::String^ get(void) override { return "QRCode Inverse Color"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"generating layer images";
		}
	};
}