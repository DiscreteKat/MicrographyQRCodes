/**
* @file AppAlgoQRC.h
*
* Classes for QR code generator
*
* @author James Hung-Kuo Chu (2013/01/07)
*/

#pragma once

namespace AppFrame 
{
	/**
	*	@brief Class for the default QR code generator
	*/
	public ref class HKCQRCGen : public HKCAlgorithm
	{
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCQRCGen(void) {}						

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCQRCGen(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Algorithm Operations						   */
		/*! \{                                                                 */	

		/// Generate QR code
		virtual bool Execute(HKCAppItem^) override;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Access Methods                              */
		/*! \{                                                                 */

		virtual property System::String^ Abbrev
		{
			System::String^ get(void) override { return "QRCGen1"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"Default QR code generator";
		}		

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:	
		bool GenerateQRcode(HKCQRCData& data);
		void BuildQRImg(HKCQRCData& data);
		//Debug Use
		void DrawCWContour(HKCQRCData& data,cv::Mat* dst);
	};	
}