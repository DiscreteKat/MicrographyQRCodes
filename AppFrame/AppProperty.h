/**
* @file AppProperty.h
*
* Classes for application properties
*
* @author James Hung-Kuo Chu
*/

#pragma once

namespace AppFrame {

	using namespace System;	
	using namespace System::ComponentModel;	
	using namespace System::Collections;
	using namespace System::IO;

	/**
	*	@brief Enumeration for the painting states
	*/
	public enum class HKEPaintS
	{
		IDLE, PAINTING
	};

	/**
	*	@brief Enumeration for the transformation states
	*/
	public enum class HKEXFormS
	{
		IDLE=0, MOVING=1, SCALING=2, ROTATING=3
	};

	/**
	*	@brief Enumeration of property event arguments
	*/
	public enum class HKEPropArg
	{		
		STROKE_SIZE, STROKE_COLOR, STROKE_ALPHA,
	};

	/**
	*	@brief Event arguments of property changed event
	*/	
	public ref class HKCPropEventArgs : public EventArgs
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */
		
		HKCPropEventArgs(HKEPropArg _prop) : m_Prop(_prop) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Access functions                              */
		/*! \{                                                                 */

		property HKEPropArg Property
		{
			HKEPropArg get(void) { return m_Prop; }			
		}		

		/*! \}                                                                 */
		/*==========================  PRIVATE  ================================*/
	private:
		/*---------------------------------------------------------------------*/
		/*! \name					   Data 	                               */
		/*! \{                                                                 */
		
		HKEPropArg m_Prop;	/// Changed property		

		/*! \}                                                                 */	
	};

	/**
	*	@brief Delegate for property event handler
	*/	
	public delegate void PropEventHandler(Object^ sender, HKCPropEventArgs^ e);

	/**
	*	@brief Interface class for the tool property
	*/
	[TypeConverter(HKMedia::SimpleTypeConverter::typeid)]
	public interface class HKCToolProp
	{			
		/*---------------------------------------------------------------------*/
		/*! \name                  Event handlers                              */
		/*! \{                                                                 */

		event PropEventHandler^ PropertyChanged;		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Design time properties                       */
		/*! \{                                                                 */

		property bool Enabled;		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
	};

	/**
	*	@brief Class for the painting properties
	*/
	[TypeConverter(HKMedia::SimpleTypeConverter::typeid)]
	public ref class HKCPntrProp : public HKCToolProp
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCPntrProp(void) 
		{			
			Enabled		= false;
			Cursor		= false;
			m_Size		= 0;
			m_Color		= Drawing::Color::Red;
			m_Alpha		= 255;
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~HKCPntrProp(void) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Event handlers                              */
		/*! \{                                                                 */

		[Browsable(FALSE)]
		virtual event PropEventHandler^ PropertyChanged;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */
		
		[Category("Painter Properties"), ReadOnly(TRUE)]
		virtual property bool Enabled;		
		[Category("Painter Properties"), ReadOnly(TRUE)]
		property bool Cursor;		
		[Category("Painter Properties")]
		property int Size
		{
			int get(void) { return m_Size; }
			void set(int value) 
			{ 
				if(value != m_Size)
				{
					m_Size = value; 
					PropertyChanged(this, gcnew HKCPropEventArgs(HKEPropArg::STROKE_SIZE));
				}				
			}
		}		
		[Category("Painter Properties")]
		virtual property Drawing::Color Color
		{
			Drawing::Color get(void) { return m_Color; }
			void set(Drawing::Color value) 
			{ 
				if(value != m_Color)
				{
					m_Color = value; 
					PropertyChanged(this, gcnew HKCPropEventArgs(HKEPropArg::STROKE_COLOR));
				}				
			}
		}
		[Category("Painter Properties")]
		property uchar Alpha
		{
			uchar get(void) { return m_Alpha; }
			void set(uchar value) 
			{ 
				if(value != m_Alpha)
				{
					m_Alpha = value; 
					PropertyChanged(this, gcnew HKCPropEventArgs(HKEPropArg::STROKE_ALPHA));
				}				
			}
		}
		virtual System::String^ ToString() override
		{
			return "Painter Properties";
		}

		/*! \}                                                                 */
		/*==========================  Protected ===============================*/
	protected:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */

		int				m_Size;
		Drawing::Color	m_Color;
		uchar			m_Alpha;

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the GrabCut properties
	*/
	[TypeConverter(HKMedia::SimpleTypeConverter::typeid)]
	public ref class HKCGCProp : public HKCPntrProp
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCGCProp(void) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~HKCGCProp(void) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */
				
		[Category("GrabCut Properties"), ReadOnly(TRUE)]
		virtual property Drawing::Color Color 
		{
			Drawing::Color get(void) override { return m_Color; }
			void set(Drawing::Color value) override
			{ 
				if(value != m_Color)
				{
					m_Color = value; 
					PropertyChanged(this, gcnew HKCPropEventArgs(HKEPropArg::STROKE_COLOR));
				}				
			}
		}
		virtual System::String^ ToString() override
		{
			return "GrabCut Properties";
		}

		/*! \}                                                                 */
		/*==========================  PRIVATE  ================================*/
	private:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */		
		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the media player properties
	*/
	[TypeConverter(HKMedia::SimpleTypeConverter::typeid)]
	public ref class HKCMPlyrProp : public HKCToolProp, public HKMedia::HKCPlayrProp
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCMPlyrProp(void) 
		{			
			Enabled	= false;			
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~HKCMPlyrProp(void) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Event handlers                              */
		/*! \{                                                                 */

		[Browsable(FALSE)]
		virtual event PropEventHandler^ PropertyChanged;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */

		[Category("Playback Properties"), ReadOnly(TRUE)]
		virtual property bool Enabled;
		[Category("Playback Control"), Description("Enable repeating?")]
		property bool Repeat
		{
			bool get(void) { return HKCPlayrProp::Repeat; }
			void set(bool value) { HKCPlayrProp::Repeat = value; }
		}
		[Category("Playback Control"), Description("Playback speed")]
		property double Speed
		{
			double get(void) { return HKCPlayrProp::Speed; }
			void set(double value) { HKCPlayrProp::Speed = value; }
		}
		[Category("Playback Control"), Description("Current frame")]
		property double Frame
		{
			double get(void) { return HKCPlayrProp::Frame; }
			void set(double value) { HKCPlayrProp::Frame = value; }
		}
		[Category("Playback Control"), Description("Enable synchronizing?")]
		property bool Sync
		{
			bool get(void) { return HKCPlayrProp::Sync; }
			void set(bool value) { HKCPlayrProp::Sync = value; }
		}
		[Category("Playback Control"), Description("FPS"), ReadOnly(TRUE)]
		property double FPS
		{
			double get(void) { return HKCPlayrProp::FPS; }
			void set(double value) { HKCPlayrProp::FPS = value; }
		}
		[Browsable(FALSE)]
		virtual property HKCPlayrParam* Param
		{
			HKCPlayrParam* get(void) { return HKCPlayrProp::Param; }
		}
		virtual System::String^ ToString() override
		{
			return "Media Player Properties";
		}

		/*! \}                                                                 */
		/*==========================  Protected ===============================*/
	protected:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */
		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the transformation properties
	*/
	[TypeConverter(HKMedia::SimpleTypeConverter::typeid)]
	public ref class HKCXFormProp : public HKCToolProp
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCXFormProp(void) 
		{		
			mp_MovRes = gcnew cli::array<double>(2){0.0, 0.0};
			mp_SclRes = gcnew cli::array<double>(2){0.0, 0.0};
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~HKCXFormProp(void) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Event handlers                              */
		/*! \{                                                                 */

		[Browsable(FALSE)]
		virtual event PropEventHandler^ PropertyChanged;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */
		
		[Category("XForm Properties"), ReadOnly(TRUE)]
		virtual property bool Enabled;					
		[Category("XForm Properties")]
		property cli::array<double>^ MoveRes
		{
			cli::array<double>^ get(void) { return mp_MovRes; }
			void set(cli::array<double>^ value) { mp_MovRes = value; }			
		}
		[Category("XForm Properties")]
		property cli::array<double>^ ScaleRes
		{
			cli::array<double>^ get(void) { return mp_SclRes; }
			void set(cli::array<double>^ value) { mp_SclRes = value; }			
		}
		[Category("XForm Properties")]
		property double RotateRes
		{
			double get(void) { return m_RotRes; }
			void set(double value) { m_RotRes = value; }			
		}
		virtual System::String^ ToString() override
		{
			return "Transformation Properties";
		}

		/*! \}                                                                 */
		/*==========================  Protected ===============================*/
	protected:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */
					
		cli::array<double>^	mp_MovRes;
		cli::array<double>^	mp_SclRes;
		double				m_RotRes;		

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the application properties
	*/	
	public ref class HKCAppProp
	{	
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppProp(void) 
		{
			mp_Media = nullptr;
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~HKCAppProp(void)
		{
		}
		
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Event handlers                              */
		/*! \{                                                                 */

		[Browsable(false)]
		event PropEventHandler^ PropertyChanged;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */

		[Category("Media Properties")]
		property HKCMediaProp^ Media
		{
			HKCMediaProp^ get(void) { return mp_Media; }
			void set(HKCMediaProp^ value) { mp_Media = value; }
		}
		virtual System::String^ ToString() override
		{
			return "Application Properties";
		}

		/*! \}                                                                 */
		/*==========================  PRIVATE  ================================*/
	private:		
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */

		HKCMediaProp^	mp_Media;	///< Media's property object

		/*! \}                                                                 */
	};	
}
