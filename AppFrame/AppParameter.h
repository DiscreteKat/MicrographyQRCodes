/**
* @file AppParameter.h
*
* Classes for application parameters
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

namespace AppFrame {

	using namespace System;	
	using namespace System::ComponentModel;	
	using namespace System::Collections;
	using namespace System::IO;	

	/**
	*	@brief Enumeration of QR code error correction level
	*/
	public enum class HKEECL
	{		
		ECL_L=0, ECL_M, ECL_Q, ECL_H 
	};	

	/**
	*	@brief Enumeration of QR code error correction level
	*/
	public enum class WORDART_COLOR
	{		
		PER_WORD=0,PER_CHAR=1,ALPHA=2,SENTENCE=3
	};

	/**
	*	@brief Enumeration of BG_COLOR
	*/
	public enum class BG_COLOR
	{
		AUTO = 1, BLACK = 2, WHITE = 3
	};

	/**
	*	@brief Enumeration of BG_STYLE
	*/
	public enum class BG_STYLE
	{	
		QRCODE=1,BLEND=2,MODULE=4,WORDART=5
	};

	/**
	*	@brief Enumeration of parameter event arguments
	*/
	public enum class HKEParamArg
	{		
		QRC_TEXT, QRC_VERSION, QRC_ECLEVEL, QRC_WA, QRC_COLOR, QRC_BACKGROUND_STYLE, QRC_BACKGROUND_COLOR
	};
	/**
	*	@brief Event arguments of parameter changed event
	*/	
	public ref class HKCParamEventArgs : public EventArgs
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */
		
		HKCParamEventArgs(HKEParamArg _param) : m_Param(_param) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Access functions                              */
		/*! \{                                                                 */

		property HKEParamArg Param
		{
			HKEParamArg get(void) { return m_Param; }			
		}		

		/*! \}                                                                 */
		/*==========================  PRIVATE  ================================*/
	private:
		/*---------------------------------------------------------------------*/
		/*! \name					   Data 	                               */
		/*! \{                                                                 */
		
		HKEParamArg m_Param;	/// Changed parameter	
		/*! \}                                                                 */	
	};
	
	/**
	*	@brief Delegate for parameter event handler
	*/	
	public delegate void ParamEventHandler(Object^ sender, HKCParamEventArgs^ e);
	

	/**
	*	@brief Class for the QR code parameters
	*/
	[TypeConverter(HKMedia::SimpleTypeConverter::typeid)]	
	public ref class HKCQRCParam
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCQRCParam(void)
		{		
			m_Ver = 0;
			m_ECL = HKEECL::ECL_L;
			m_Wa  = 0;
			m_Da  = 0;
			m_offsetX = 0;
			m_offsetY = 0;
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~HKCQRCParam(void) 
		{
		}	
		
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Event handlers                              */
		/*! \{                                                                 */

		[Browsable(false)]
		event ParamEventHandler^ PropertyChanged;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */		

		[Category("QR code generator")]
		property System::String^ Text
		{
			System::String^ get(void) { return m_Text; }
			void set(System::String^ value) 
			{ 
				if(System::String::Compare(m_Text, value) != 0)
				{
					m_Text = value;
					PropertyChanged(this, gcnew HKCParamEventArgs(HKEParamArg::QRC_TEXT));
				}				
			}
		}
		[Category("QR code generator"), Description("QR code version")]
		property int Version
		{
			int get(void) { return m_Ver; }
			void set(int value) 
			{ 
				if(m_Ver != value)
				{
					m_Ver = value;
					PropertyChanged(this, gcnew HKCParamEventArgs(HKEParamArg::QRC_VERSION));	
				}				
			}
		}
		[Category("QR code generator"), Description("QR code error correction level")]
		property HKEECL ECLvl
		{
			HKEECL get(void) { return m_ECL; }
			void set(HKEECL value) 
			{ 
				if(m_ECL != value)
				{
					m_ECL = value;
					PropertyChanged(this, gcnew HKCParamEventArgs(HKEParamArg::QRC_ECLEVEL));	
				}				
			}
		}

		[Category("QR code generator"), Description("QR code number of RS blocks"), ReadOnly(TRUE)]
		property int RSNum;		
		[Category("QR code generator"), Description("QR code error correction capacity"), ReadOnly(TRUE)]
		property int ECCap;				
		[Category("QR code generator"), Description("Size of QR code"), ReadOnly(TRUE)]
		property System::Drawing::Size QRSize;
		[Category("QR code generator"), Description("Size of QR code image"), ReadOnly(TRUE)]
		property System::Drawing::Size ImgSize;

		virtual System::String^ ToString() override
		{
			return "QR Code Parameters";
		}

		[Category("QR code generator"), Description("QR code Size")]
		property int Wa
		{
			int get(void) { return m_Wa; }
			void set(int value) 
			{ 
				if(m_Wa != value)
				{
					m_Wa = value;
					PropertyChanged(this, gcnew HKCParamEventArgs(HKEParamArg::QRC_WA));	
				}				
			}
		}
		[Category("QR code generator"), Description("QR code Center Size")]
		property int Da
		{
			int get(void) { return m_Da; }
			void set(int value) 
			{ 
				if(m_Da != value){m_Da = value;}				
			}
		}
		[Category("QR code generator"), Description("QR code offsetX")]
		property double offsetX
		{
			double get(void) { return m_offsetX; }
			void set(double value) 
			{ 
				if(m_offsetX != value){m_offsetX = value;}				
			}
		}
		[Category("QR code generator"), Description("QR code offsetY")]
		property double offsetY
		{
			double get(void) { return m_offsetY; }
			void set(double value) 
			{ 
				if(m_offsetY != value){m_offsetY = value;}				
			}
		}
		/*! \}                                                                 */
		/*==========================  PRIVATE  ================================*/
	private:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */	

		System::String^	m_Text;				///< QR code text
		int				m_Ver;				///< QR code version
		HKEECL			m_ECL;				///< QR code error correction level	
		int				m_Wa;				///< QR code Wa
		int				m_Da;				///< QR code Da
		double          m_offsetX;
		double          m_offsetY;
		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the EC parameters
	*/
	[TypeConverter(HKMedia::SimpleTypeConverter::typeid)]	
	public ref class OptimizationParam
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		OptimizationParam(void)
		{
			rs_binary_threshold = 0.6;
			//spline_curve_warping_level = 0.5;
			lambda = 20.0;
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~OptimizationParam(void) 
		{
		}	
		
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Event handlers                              */
		/*! \{                                                                 */

		[Browsable(false)]
		event ParamEventHandler^ PropertyChanged;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */		
		[Category("RS_Binary_Thershold")]
		[Description("Binary Threshold for RS Modification")]
		property double RS_Binary_Threshold{
			double get(){
				return rs_binary_threshold;
			}
			void set(double sm){
				rs_binary_threshold = sm;
			}
		}

// 		[Category("SCWarping_Level")]
// 		[Description("Level of Deformation for Spline Curve Warping")]
// 		property double SCWarping_Level{
// 			double get(){
// 				return spline_curve_warping_level;
// 			}
// 			void set(double sm){
// 				spline_curve_warping_level = sm;
// 			}
// 		}

		[Category("Lambda")]
		[Description("Level of Deformation for Warping")]
		property double Lambda{
			double get(){
				return lambda;
			}
			void set(double sm){
				lambda = sm;
			}
		}
		
		virtual System::String^ ToString() override
		{
			return "Optimaization Parameters";
		}

		/*! \}                                                                 */
		/*==========================  PRIVATE  ================================*/
	private:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */
		/*! \}                                                                 */
		double rs_binary_threshold;
		//double spline_curve_warping_level;
		double lambda;
	};
	/**
	*	@brief Class for the WordArt parameters
	*/	
	[TypeConverter(HKMedia::SimpleTypeConverter::typeid)]
	public ref class HKCWordArtParam
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCWordArtParam(void)
		{		
			bg_style = BG_STYLE::MODULE;
			bg_color = BG_COLOR::AUTO;
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~HKCWordArtParam(void) 
		{
		}	
		
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Event handlers                              */
		/*! \{                                                                 */

		[Browsable(false)]
		event ParamEventHandler^ PropertyChanged;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */		

		virtual System::String^ ToString() override
		{
			return "WordArtParam Parameters";
		}
		[Description("Text")]
		property System::String^ strings;
		[Category("Boundary Repel Parameter a")]
		[Description("The ratio value of the boundary repel a in line tracing.")]
		property double Boundary_Repela;
		[Category("Line Repel Parameter")]
		[Description("The ratio value of the line repel a in line tracing.")]
		property double Line_Repela;
		[Category("Boundary Repel Parameter a")]
		[Description("The ratio value of the boundary repel b in line tracing.")]
		property double Boundary_Repelb;
		[Category("Line Repel Parameter")]
		[Description("The ratio value of the line repel b in line tracing.")]
		property double Line_Repelb;
		[Category("Line range size")]
		[Description("The range size of line.")]
		property int RangeSize;
		[Category("Small region range size")]
		[Description("The range size of line in small region.")]
		property int SmallRangeSize;
		
		[Category("string line preserve space")]
		[Description("0: Word \n1: Char")]
		property double LineSpace;
		[Category("WidthAdjust")]
		property double SmallRangeRatio;
		[Category("Text Generate Type")]
		property int	TextType;
		[Category("Text Color Adjust Weight")]
		property double	ColorAdjustW;
		[Category("Text Color Adjust Algo")]
		[Description("Text Color Adjust Algo (0:greedy 1:simplex 2:golden)")]
		property int	ColorAdjustAlgo;



		[Category("Color Mode")]
		[Description("Word Art Color Sampling Mode")]
		property WORDART_COLOR ColorMode
		{
			WORDART_COLOR get(void) { return word_art_color; }
			void set(WORDART_COLOR value) 
			{ 
				if(word_art_color != value)
				{
					word_art_color = value;
					PropertyChanged(this, gcnew HKCParamEventArgs(HKEParamArg::QRC_COLOR));	
				}				
			}
		}

		[Category("BG Style")]
		[Description("Background Style")]
		property BG_STYLE BGStyle
		{
			BG_STYLE get(void) { return bg_style; }
			void set(BG_STYLE value) 
			{ 
				if(bg_style != value)
				{
					bg_style = value;
					PropertyChanged(this, gcnew HKCParamEventArgs(HKEParamArg::QRC_BACKGROUND_STYLE));	
				}				
			}
		}

		[Category("BG Style")]
		[Description("Background Color")]
		property BG_COLOR BGColor
		{
			BG_COLOR get(void) { return bg_color; }
			void set(BG_COLOR value)
			{
				if (bg_color != value)
				{
					bg_color = value;
					PropertyChanged(this, gcnew HKCParamEventArgs(HKEParamArg::QRC_BACKGROUND_COLOR));
				}
			}
		}
		/*! \}                                                                 */
		/*==========================  PRIVATE  ================================*/
	private:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */
		WORDART_COLOR word_art_color;
		BG_STYLE      bg_style;
		BG_COLOR      bg_color;
		/*! \}                                                                 */
	};
	/**
	*	@brief Class for the application parameters
	*/
	public ref class HKCAppParam
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppParam(void) 
		{			
			mp_QRC		= gcnew HKCQRCParam;	
			mp_EC		= gcnew OptimizationParam;
			mp_WordArt	= gcnew HKCWordArtParam;
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~HKCAppParam(void) 
		{			
			delete mp_QRC;
			mp_QRC = nullptr;
		
			delete mp_EC;
			mp_EC = nullptr;		

			delete mp_WordArt;
			mp_WordArt=nullptr;			
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */
		[Category("QR Code Parameters")]
		property HKCQRCParam^ QRCode
		{
			HKCQRCParam^ get(void) { return mp_QRC; }
		}
		[Category("EC Parameters")]
		property OptimizationParam^ Optimization
		{
			OptimizationParam^ get(void) { return mp_EC; }
		}
		[Category("WordArt Parameters")]
		property HKCWordArtParam^ WordArt
		{
			HKCWordArtParam^ get(void) { return mp_WordArt; }
		}


		virtual System::String^ ToString() override
		{
			return "Application Parameters";
		}
		
		/*! \}                                                                 */
		/*==========================  PRIVATE  ================================*/
	private:	
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */
		
		HKCQRCParam^				mp_QRC;
		OptimizationParam^	mp_EC;
		HKCWordArtParam^			mp_WordArt;
		/*! \}                                                                 */
	};
}
