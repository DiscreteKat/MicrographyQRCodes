/**
* @file AppTool.h
*
* Base class for application tool
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

namespace AppFrame 
{	
	/**
	*	@brief Base class for the application tool
	*/
	public ref class HKCAppTool abstract
	{
		/*==========================  PUBLIC  =================================*/
	public:					
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppTool(void) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                       Render                                 */
		/*! \{                                                                 */

		virtual void Render(void)  {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */	

		/// Activate the tool
		virtual bool Activate(HKCAppItem^) { return true; }

		/// Deactivate the tool
		virtual bool DeActivate(HKCAppItem^) { return true; }

		/// Tool action
		virtual bool Action(System::String^, HKCAppItem^) { return true; }		

		/*! \}                                                                 */		
		/*---------------------------------------------------------------------*/		
		/*! \name                Access data members                           */
		/*! \{                                                                 */

		property System::String^ Label
		{
			System::String^ get(void) { return m_Label; }					
		}
		property HKCToolProp^ Prop
		{
			HKCToolProp^ get(void) { return mp_Prop; }		
		}
		virtual System::String^ ToString() override
		{
			return L"Application Tool";
		}

		/*! \}                                                                 */		
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppTool(System::String^ _label, HKCToolProp^ _prop) 
		{ 
			m_Label = _label;
			mp_Prop = _prop;			
		}

		/*! \}                                                                 */		
		/*---------------------------------------------------------------------*/
		/*! \name                        Data								   */
		/*! \{                                                                 */
		
		System::String^	m_Label;	///< Tool label
		HKCToolProp^	mp_Prop;	///< Tool property object

		/*! \}                                                                 */
	};	
}