/**
* @file AppMediaPlayer.h
*
* Class for application media player tool
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

namespace AppFrame 
{	
	/**
	*	@brief Class for the application media player tool
	*/
	public ref class HKCMPlayer : public HKCAppTool
	{		
		/*==========================  PUBLIC  =================================*/
	public:	
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCMPlayer(System::String^);

		HKCMPlayer(System::String^, HKCToolProp^);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCMPlayer(void);		

		/*! \}                                                                 */					
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */						

		/// Activate media player
		virtual bool Activate(HKCAppItem^) override;

		/// Deactivate media player
		virtual bool DeActivate(HKCAppItem^) override;

		/**
		* @brief Media player's action.
		*
		* @param _act Label of action. 
		*			  1. "FWD" : Play forward.
		*			  2. "RWD" : Rewind. 
		*			  3. "START" : Go to the start frame.
		*			  4. "END" : Go to the last frame.
		*			  5. "GOTO" : Go to specific frame.
		*
		* @param _appItem Application item
		*/
		virtual bool Action(System::String^, HKCAppItem^) override;			

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                Access data members                           */
		/*! \{                                                                 */

		/// Access to Media player's property object
		property HKCMPlyrProp^ MPlyrProp
		{
			HKCMPlyrProp^ get(void) { return mp_MPlyrProp; }		
		}

		virtual System::String^ ToString() override
		{
			return L"Application Media Player Tool";
		}

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:								
		/*---------------------------------------------------------------------*/
		/*! \name                       Data                                   */
		/*! \{                                                                 */

		HKCMPlyrProp^	mp_MPlyrProp;	///< Media player's property object

		/*! \}                                                                 */
	};
}