/**
* @file AppGrabCut.h
*
* Class for application GrabCut tool
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

namespace AppFrame 
{
	/**
	*	@brief Class for the application GrabCut tool
	*/
	public ref class HKCGrabCutr : public HKCPainter
	{		
		/*==========================  PUBLIC  =================================*/
	public:	
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCGrabCutr(System::String^);

		HKCGrabCutr(System::String^, HKCToolProp^);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCGrabCutr(void);		

		/*! \}                                                                 */					
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */			

		/// Activate GrabCut
		virtual bool Activate(HKCAppItem^) override;

		/// Deactivate GrabCut
		virtual bool DeActivate(HKCAppItem^) override;

		/**
		* @brief GrabCut's action.
		*
		* @param _act Label of action.
		*			  1. "STROKE_Name", Name = {FGD, BGD, PRFGD, PRBGD, MSKB, MSKW, ERASE} : Different strokes.
		*			  2. "CUT" : Perform GrabCut. 
		*             3. "ADD" : Add cut result. 
		*			  4. "RESET" : Reset everything. 	
		*
		* @param _appItem Application item
		*/
		virtual bool Action(System::String^, HKCAppItem^) override;		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                Access data members                           */
		/*! \{                                                                 */

		/// Access to the GrabCut object
		property HKCV::HKCGrabCut* GrabCut
		{
			HKCV::HKCGrabCut* get(void) { return mp_GrabCut; }
			void set(HKCV::HKCGrabCut* value) 
			{ 
				if(mp_GrabCut == value) return;	
				if(mp_GrabCut) delete mp_GrabCut;
				mp_GrabCut = value;										
			}	
		}

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:								
		/*---------------------------------------------------------------------*/
		/*! \name                       Data                                   */
		/*! \{                                                                 */

		HKCV::HKCGrabCut* mp_GrabCut;

		/*! \}                                                                 */
	};
}