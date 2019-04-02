/**
* @file AppState.h
*
* Classes for application state machine
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#ifndef _APPSTATE_H_
#define _APPSTATE_H_

namespace AppFrame 
{
	using namespace System::Windows::Forms;
	using namespace HKOGLPanel;

	/**
	*	@brief Base class for the application state
	*/
	class HKCAppState
	{
		/*==========================  PUBLIC  =================================*/
	public:					
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppState(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */		

		/// Panel mouse down event
		virtual void Panel_MouseDown(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse move event
		virtual void Panel_MouseMove(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse up event
		virtual void Panel_MouseUp(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse wheel event
		virtual void Panel_MouseWheel(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel key down event
		virtual void Panel_KeyDown(Form1^, HKOGLPanelControl^, KeyEventArgs^);

		/// Panel key up event
		virtual void Panel_KeyUp(Form1^, HKOGLPanelControl^, KeyEventArgs^);

		/*! \}                                                                 */	
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppState(void) { KeyDown = false;}						

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                       Data                                   */
		/*! \{                                                                 */

		static cv::Point2i	MousePos;
		bool KeyDown;
		Keys KeyCode;	
		Keys KeyMod;

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the Idle State
	*/
	class HKCStateIdle : public HKCAppState, public HKCSingleton<HKCStateIdle>
	{
		friend class HKCSingleton<HKCStateIdle>;

		/*==========================  PUBLIC  =================================*/
	public:			
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCStateIdle(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */			

		/// Panel mouse down event
		virtual void Panel_MouseDown(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel key down event
		virtual void Panel_KeyDown(Form1^, HKOGLPanelControl^, KeyEventArgs^);

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCStateIdle(void) {}						

		/*! \}                                                                 */
	};		

	/**
	*	@brief Class for the Painting State
	*/
	class HKCStatePaint : public HKCAppState, public HKCSingleton<HKCStatePaint>
	{
		friend class HKCSingleton<HKCStatePaint>;

		/*==========================  PUBLIC  =================================*/
	public:			
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCStatePaint(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */			

		/// Panel mouse down event
		virtual void Panel_MouseDown(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse move event
		virtual void Panel_MouseMove(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse up event
		virtual void Panel_MouseUp(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse wheel event
		virtual void Panel_MouseWheel(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCStatePaint(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                       Data                                   */
		/*! \{                                                                 */

		HKEPaintS	m_State;

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the GrabCut State
	*/
	class HKCStateGC : public HKCAppState, public HKCSingleton<HKCStateGC>
	{
		friend class HKCSingleton<HKCStateGC>;

		/*==========================  PUBLIC  =================================*/
	public:			
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCStateGC(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */			

		/// Panel mouse down event
		virtual void Panel_MouseDown(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse move event
		virtual void Panel_MouseMove(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse up event
		virtual void Panel_MouseUp(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse wheel event
		virtual void Panel_MouseWheel(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCStateGC(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                       Data                                   */
		/*! \{                                                                 */

		HKEPaintS	m_State;

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the Moving State
	*/
	class HKCStateMove : public HKCAppState, public HKCSingleton<HKCStateMove>
	{
		friend class HKCSingleton<HKCStateMove>;

		/*==========================  PUBLIC  =================================*/
	public:			
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCStateMove(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */			

		/// Panel mouse down event
		virtual void Panel_MouseDown(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse move event
		virtual void Panel_MouseMove(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse up event
		virtual void Panel_MouseUp(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel key down event
		virtual void Panel_KeyDown(Form1^, HKOGLPanelControl^, KeyEventArgs^);

		/// Panel key up event
		virtual void Panel_KeyUp(Form1^, HKOGLPanelControl^, KeyEventArgs^);

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCStateMove(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                       Data                                   */
		/*! \{                                                                 */

		HKEXFormS	m_State;

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the Rotating State
	*/
	class HKCStateRotate : public HKCAppState, public HKCSingleton<HKCStateRotate>
	{
		friend class HKCSingleton<HKCStateRotate>;

		/*==========================  PUBLIC  =================================*/
	public:			
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCStateRotate(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */			

		/// Panel mouse down event
		virtual void Panel_MouseDown(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse move event
		virtual void Panel_MouseMove(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse up event
		virtual void Panel_MouseUp(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel key down event
		virtual void Panel_KeyDown(Form1^, HKOGLPanelControl^, KeyEventArgs^);

		/// Panel key up event
		virtual void Panel_KeyUp(Form1^, HKOGLPanelControl^, KeyEventArgs^);	

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCStateRotate(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                       Data                                   */
		/*! \{                                                                 */

		HKEXFormS	m_State;

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the Scaling State
	*/
	class HKCStateScale : public HKCAppState, public HKCSingleton<HKCStateScale>
	{
		friend class HKCSingleton<HKCStateScale>;

		/*==========================  PUBLIC  =================================*/
	public:			
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCStateScale(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */			

		/// Panel mouse down event
		virtual void Panel_MouseDown(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse move event
		virtual void Panel_MouseMove(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel mouse up event
		virtual void Panel_MouseUp(Form1^, HKOGLPanelControl^, MouseEventArgs^);

		/// Panel key down event
		virtual void Panel_KeyDown(Form1^, HKOGLPanelControl^, KeyEventArgs^);

		/// Panel key up event
		virtual void Panel_KeyUp(Form1^, HKOGLPanelControl^, KeyEventArgs^);	

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCStateScale(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                       Data                                   */
		/*! \{                                                                 */

		HKEXFormS	m_State;

		/*! \}                                                                 */
	};
}

#endif