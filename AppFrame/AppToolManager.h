/**
* @file AppToolManager.h
*
* Classes for application tool manager
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

namespace AppFrame 
{	
	using namespace System::Windows::Forms;
	using namespace System::Collections;
	using namespace System::Collections::Generic;	

	/**
	*	@brief Base class for the application tool manager
	*/
	public ref class HKCAppToolMgr abstract
	{
		/*==========================  PUBLIC  =================================*/
	public:					
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppToolMgr(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */	

		/// Toggle tool
		virtual void Toggle(System::String^, bool, HKCAppItem^, Form1^) = 0;

		/// Perform tool's action
		virtual void Action(System::String^, System::String^, HKCAppItem^, Form1^) = 0;

		/// Update tool's property
		virtual void Update(HKCAppItem^, Form1^) = 0;

		/// Add a new tool
		virtual bool Add(HKCAppTool^);

		/// Find tool with specific label
		virtual HKCAppTool^ Find(System::String^);		

		/// Delete tool at specific index
		virtual bool Delete(int);				

		/// Delete tool with specific label
		virtual bool Delete(System::String^);	

		/*! \}                                                                 */	
		/*---------------------------------------------------------------------*/		
		/*! \name                Access data members                           */
		/*! \{                                                                 */	

		/// Access to list of tools
		property List<HKCAppTool^>^ Tools
		{
			List<HKCAppTool^>^ get(void) { return mp_Tools; }			
		}
		virtual System::String^ ToString() override
		{
			return L"Application Tool Manager";
		}

		/*! \}                                                                 */	
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppToolMgr(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                        Data								   */
		/*! \{                                                                 */		

		List<HKCAppTool^>^	mp_Tools;	///< List of tools		

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the default tool manager
	*/
	public ref class HKCToolMgrDef : public HKCAppToolMgr
	{		
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCToolMgrDef(void);					

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCToolMgrDef(void);	

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */		

		/// Toggle tool
		virtual void Toggle(System::String^, bool, HKCAppItem^, Form1^) override;

		/// Perform tool's action
		virtual void Action(System::String^, System::String^, HKCAppItem^, Form1^) override;

		/// Update tool's property
		virtual void Update(HKCAppItem^, Form1^) override;

		/*! \}                                                                 */
	};	
}