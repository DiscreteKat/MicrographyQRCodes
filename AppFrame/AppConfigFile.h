/**
* @file AppConfigFile.h
*
* Classes for processing application config file 
*
* @author James Hung-Kuo Chu
*/

#pragma once

namespace AppFrame 
{	
	using namespace System::Windows::Forms;
	using namespace HKOGLPanel;

	/**
	*	@brief Base class for the application config section
	*/
	public ref class HKCAppCfgSec
	{
		/*==========================  PUBLIC  =================================*/
	public:					
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppCfgSec(void);		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */

		/// Actions to do when a section is started
		virtual bool Begin(System::String^, System::String^, Form1^, HKOGLPanelControl^) { return true; }
		
		/// Actions to do during the course of within a section
		virtual bool Parse(System::String^, System::String^, Form1^, HKOGLPanelControl^);
		
		/// Actions to do when a section is ended
		virtual bool End(System::String^, System::String^, Form1^, HKOGLPanelControl^) { return true; }
		
		/*! \}                                                                 */	
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppCfgSec(void);					

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                        Data								   */
		/*! \{                                                                 */

		std::map<std::string, std::string>* mp_Maps;

		/*! \}                                                                 */
	};

	/**
	*	@brief Base class for the application config version [Source]
	*/
	public ref class HKCAppCfgVer : public HKCAppCfgSec
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppCfgVer(void);					

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppCfgVer(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */
		
		/// Actions to do when a section is ended
		virtual bool End(System::String^, System::String^, Form1^, HKOGLPanelControl^) override;
		
		/*! \}                                                                 */
	};

	/**
	*	@brief Base class for the application config section [Source]
	*/
	public ref class HKCAppCfgSrc : public HKCAppCfgSec
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppCfgSrc(void);					

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppCfgSrc(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */
		
		/// Actions to do when a section is ended
		virtual bool End(System::String^, System::String^, Form1^, HKOGLPanelControl^) override;
		
		/*! \}                                                                 */
	};

	/**
	*	@brief Base class for the application config section [Mask]
	*/
	public ref class HKCAppCfgWordArt : public HKCAppCfgSec
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppCfgWordArt(void);					

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppCfgWordArt(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */
		
		/// Actions to do when a section is ended
		virtual bool End(System::String^, System::String^, Form1^, HKOGLPanelControl^) override;
		
		/*! \}                                                                 */
	};
	/**
	*	@brief Base class for the application config section [QRCode]
	*/
	public ref class HKCAppCfgQRC : public HKCAppCfgSec
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppCfgQRC(void);					

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppCfgQRC(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */
		
		/// Actions to do when a section is ended
		virtual bool End(System::String^, System::String^, Form1^, HKOGLPanelControl^) override;
		
		/*! \}                                                                 */
	};

	/**
	*	@brief Base class for the application config section [Vector Field]
	*/
	public ref class HKCAppCfgVFB : public HKCAppCfgSec
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppCfgVFB(void);					

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppCfgVFB(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */
		
		/// Actions to do when a section is ended
		virtual bool End(System::String^, System::String^, Form1^, HKOGLPanelControl^) override;
		
		/*! \}                                                                 */
	};
	/**
	*	@brief Base class for the application config section [Region Param]
	*/
	public ref class HKCAppCfgREGP : public HKCAppCfgSec
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppCfgREGP(void);					

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppCfgREGP(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */
		
		/// Actions to do when a section is ended
		virtual bool End(System::String^, System::String^, Form1^, HKOGLPanelControl^) override;
		/*! \}  */

		int Region_size;
	};
	/**
	*	@brief Base class for processing application config file
	*/
	public ref class HKCAppCfgFile
	{
		/*==========================  PUBLIC  =================================*/
	public:					
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppCfgFile(void);						

		/*! \}                                                                 */	
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppCfgFile(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                         IO                                   */
		/*! \{                                                                 */
		
		/// Read file
		bool Read(System::String^, Form1^, HKOGLPanelControl^);		

		/// Write file
		bool Write(System::String^, Form1^, HKOGLPanelControl^);				
		
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                Access data members                           */
		/*! \{                                                                 */		

		/// Access to Section object
		property HKCAppCfgSec^ Section
		{
			HKCAppCfgSec^ get(void) { return mp_Section; }		
			void set(HKCAppCfgSec^ value)
			{
				if(mp_Section != value)
				{
					if(mp_Section) delete mp_Section;
					mp_Section = value;
				}
			}
		}

		virtual System::String^ ToString() override
		{
			return L"Application Config File Processor";
		}

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:						
		/*---------------------------------------------------------------------*/
		/*! \name                        Data								   */
		/*! \{                                                                 */

		HKCAppCfgSec^ mp_Section;

		/*! \}                                                                 */
	};	
}