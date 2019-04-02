/**
* @file AppXForm.h
*
* Class for application transformation tool
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

namespace AppFrame 
{
	/**
	*	@brief Class for the transformation tool
	*/
	public ref class HKCXFormer : public HKCAppTool
	{		
		/*==========================  PUBLIC  =================================*/
	public:	
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCXFormer(System::String^);

		HKCXFormer(System::String^, HKCToolProp^);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCXFormer(void);		

		/*! \}                                                                 */					
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */				

		/// Activate xform
		virtual bool Activate(HKCAppItem^) override;

		/// Deactivate xform
		virtual bool DeActivate(HKCAppItem^) override;
		
		/**
		* @brief XForm's action.
		*
		* @param _act Label of action.
		*			  1. "UNDO" : Restore the transformation		
		*
		* @param _appItem Application item
		*/
		virtual bool Action(System::String^, HKCAppItem^) override;		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                Access data members                           */
		/*! \{                                                                 */		

		/// Access to xform's property object
		property HKCXFormProp^ XFormProp
		{
			HKCXFormProp^ get(void) { return mp_XFormProp; }		
		}

		virtual System::String^ ToString() override
		{
			return L"Application Transformation Tool";
		}

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:								
		/*---------------------------------------------------------------------*/
		/*! \name                       Data                                   */
		/*! \{                                                                 */
		
		HKCXFormProp^	mp_XFormProp;	///< XForm's property object

		/*! \}                                                                 */
	};
}