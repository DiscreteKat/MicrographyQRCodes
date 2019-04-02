/**
* @file AppRender.h
*
* Classes for application render
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

namespace AppFrame 
{
	using namespace HKOGLPanel;

	/**
	*	@brief Base class for the application render
	*/
	public ref class HKCAppRender abstract
	{
		/*==========================  PUBLIC  =================================*/
	public:					
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppRender(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                   Render Methods                             */
		/*! \{                                                                 */
		
		/// Render interface
		virtual void Render(HKCAppItem^, HKOGLPanelControl^) = 0;	

		/// Render interface
		virtual void Render(HKCAppToolMgr^, HKOGLPanelControl^) = 0;
		
		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppRender(void) {}						

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the default application render
	*/
	public ref class HKCRenderDef : public HKCAppRender
	{	
		/*==========================  PUBLIC  =================================*/
	public:	
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCRenderDef(void) {}						

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCRenderDef(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                   Render Methods                             */
		/*! \{                                                                 */

		/// Render application item
		virtual void Render(HKCAppItem^, HKOGLPanelControl^) override;

		/// Render application tool
		virtual void Render(HKCAppToolMgr^, HKOGLPanelControl^) override;

		/*! \}                                                                 */			
	};	
}