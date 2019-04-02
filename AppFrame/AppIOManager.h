/**
* @file AppIOManager.h
*
* Classes for application I/O manager
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

namespace AppFrame 
{	
	using namespace System::Windows::Forms;
	using namespace HKOGLPanel;

	/**
	*	@brief Base class for the application IO manager
	*/
	public ref class HKCAppIOMgr abstract
	{
		/*==========================  PUBLIC  =================================*/
	public:					
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppIOMgr(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                         IO                                   */
		/*! \{                                                                 */
		
		/// Read file
		virtual bool Read(System::String^, Form1^, HKOGLPanelControl^) = 0;

		/// Read a media item from file and assign it a specified label
		virtual bool Read(System::String^, System::String^, Form1^, HKOGLPanelControl^) = 0;

		/// Write file
		virtual bool Write(System::String^, Form1^, HKOGLPanelControl^) = 0;		

		/// Write a media item with specified label to file
		virtual bool Write(System::String^, System::String^, Form1^, HKOGLPanelControl^) = 0;	
		
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                Access data members                           */
		/*! \{                                                                 */		

		/// Access to I/O property object
		property HKCIOProp^ Prop
		{
			HKCIOProp^ get(void) { return mp_Prop; }				
		}

		/// Access to supported image file extensions
		property System::String^ Image_Exts
		{
			System::String^ get(void) { return m_ImageExts; }				
		}
		/// Access to supported flow file extensions
		property System::String^ Flow_Exts
		{
			System::String^ get(void) { return m_FlowExts; }				
		}
		// Access to supported Article file extensions
		property System::String^ Article_Exts
		{
			System::String^ get(void) { return m_ArticleExts; }				
		}
		/// Access to supported video file extensions
		property System::String^ Video_Exts
		{
			System::String^ get(void) { return m_VideoExts; }				
		}

		/// Access to supported auxiliary file extensions
		property System::String^ Aux_Exts
		{
			System::String^ get(void) { return m_AuxExts; }				
		}
		property System::String^ Line_Exts
		{
			System::String^ get(void) { return m_LineExts; }				
		}

		/// Access to supported media(image+video) file extensions
		property System::String^ Media_Exts
		{
			System::String^ get(void) { return System::String::Concat(m_ImageExts, "|", m_VideoExts); }				
		}

		/// Access to all supported file extensions
		property System::String^ Supported_Exts
		{
			System::String^ get(void) { return System::String::Concat(m_ImageExts, "|", m_VideoExts, "|", m_AuxExts); }				
		}
		virtual System::String^ ToString() override
		{
			return L"Application IO Manager";
		}

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppIOMgr(void);						

		/*! \}                                                                 */	
		/*---------------------------------------------------------------------*/
		/*! \name                        Data								   */
		/*! \{                                                                 */

		HKCIOProp^		mp_Prop;		///< I/O property object
		System::String^	m_ImageExts;	///< Supported image file extensions
		System::String^	m_VideoExts;	///< Supported video file extensions		
		System::String^	m_AuxExts;		///< Supported auxiliary file extensions
		System::String^ m_FlowExts;     ///< Supported flow file extensions
		System::String^ m_LineExts;
		System::String^ m_ArticleExts;
		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the default I/O manager
	*/
	public ref class HKCIOMgrDef : public HKCAppIOMgr
	{		
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCIOMgrDef(void);					

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCIOMgrDef(void);	

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name						  IO                                   */
		/*! \{                                                                 */

		/// Read file
		virtual bool Read(System::String^, Form1^, HKOGLPanelControl^) override;		

		/// Read a media item from file and assign it a specified label
		virtual bool Read(System::String^, System::String^, Form1^, HKOGLPanelControl^) override;

		/// Write file
		virtual bool Write(System::String^, Form1^, HKOGLPanelControl^) override;

		/// Write a media item with specified label to file
		virtual bool Write(System::String^, System::String^, Form1^, HKOGLPanelControl^) override;	

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name						  IO                                   */
		/*! \{                                                                 */

		/// Read image file
		virtual HKCMedia* Read_Image(System::String^);		

		/// Read video file
		virtual HKCMedia* Read_Video(System::String^);

		/// Read configuration file
		virtual bool Read_Config(System::String^, Form1^, HKOGLPanelControl^);

		/// Write configuration file
		virtual bool Write_Config(System::String^, Form1^, HKOGLPanelControl^);

		/// Read pattern database file
		virtual bool Read_PatternDB(System::String^, Form1^, HKOGLPanelControl^);

		/*! \}                                                                 */
		
	};	
}