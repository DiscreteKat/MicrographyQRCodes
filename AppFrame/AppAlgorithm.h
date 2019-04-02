/**
* @file AppAlgorithm.h
*
* Base class for algorithm Interface
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

namespace AppFrame 
{
	/**
	*	@brief Base class for the algorithm interface
	*/
	public ref class HKCAlgorithm abstract
	{
		/*==========================  PUBLIC  =================================*/
	public:					
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAlgorithm(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Algorithm Operations						   */
		/*! \{                                                                 */	

		/// Execute the algorithm
		virtual bool Execute(HKCAppItem^) = 0;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Access Methods                              */
		/*! \{                                                                 */

		virtual property System::String^ Abbrev
		{
			System::String^ get(void) { return "Algo"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"Application Algorithm";
		}		

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAlgorithm(void) {}						

		/*! \}                                                                 */
	};	
}