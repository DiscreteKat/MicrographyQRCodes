#pragma once

#include "flowabsParam.h"

namespace flowabs
{
	using namespace System;	
	using namespace System::ComponentModel;	
	using namespace System::Collections;
	using namespace System::IO;

	/**
	*	@brief Enumeration for the difference of gaussian type
	*/
	public enum class EDoGT
	{
		FDoG=0, DoG=1
	};

	/**
	*	@brief Enumeration for the smoothing kernel type
	*/
	public enum class EFilterT
	{
		NONE=0, K_3X3=1, K_5X5=2
	};

	/**
	*	@brief Enumeration for the smoothing kernel type
	*/
	public enum class EFilter2T
	{
		NONE=0, K_3X3=1, K_5X5=2, FLOW_SMOOTH=3
	};

	/**
	*	@brief Enumeration for the Image Type
	*/
	public enum class EDisplayT
	{
		SOURCE=0x0001, 
		RESULT=0x0002, 
		//TANGENT_FLOW=0x0004, 
		FLOW_FIELD=0x0008,
		BILATERAL1=0x0010,
		BILATERAL2=0x0020, 
		DIFFERENCE_OF_GAUSSIAN=0x0040, 
		COLOR_QUANTIZE=0x0080,
	};

	/// <summary> 
	/// Provides a unified way of converting types of values to other types, 
	/// as well as for accessing standard values and subproperties.
	/// </summary>		
	public ref class SimpleTypeConverter : public ExpandableObjectConverter
	{
	public:
		virtual Object^ ConvertTo(ITypeDescriptorContext^ context, System::Globalization::CultureInfo^ culture, Object^ value, Type^ destinationType) new
		{
			return __super::ConvertTo(context, culture, value, destinationType); 
		}
	};

	/**
	*	@brief Class for the Smoothed Structure Tensor Property
	*/
	[TypeConverter(SimpleTypeConverter::typeid)]
	public ref class CSSTProp
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		CSSTProp(CSSTParam* _param) : mp_Param(_param) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~CSSTProp(void) {}	

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */		
				
		[Description("Sigma for the smoothing kernel, higher the value results smoother image")]
		property float Sigma
		{
			float get(void) { return mp_Param->Sigma(); }
			void set(float value) { mp_Param->Sigma() = value; }
		}		
		[Browsable(FALSE)]
		virtual property CSSTParam* Param
		{
			CSSTParam* get(void) { return mp_Param; }
		}
		virtual System::String^ ToString() override
		{
			return "Smoothed Structure Tensor Properties";
		}

		/*! \}                                                                 */
		/*==========================  PRIVATE  ================================*/
	private:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */

		CSSTParam*	mp_Param;

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the Orientation aligned Bilateral Filter Property
	*/
	[TypeConverter(SimpleTypeConverter::typeid)]
	public ref class COBFProp
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		COBFProp(COBFParam* _param) : mp_Param(_param) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~COBFProp(void) {}	

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */		
			
		property int nIter
		{
			int get(void) { return mp_Param->nIter(); }
			void set(int value) { mp_Param->nIter() = value; }
		}
		[Description("1st sigma of the bilateral filter, higher the value results smoother image (0~10)")]
		property float SigmaD
		{
			float get(void) { return mp_Param->SigmaD(); }
			void set(float value) { mp_Param->SigmaD() = value; }
		}	
		[Description("2nd sigma of the bilateral filter, higher the value results smoother image (0~10)")]
		property float SigmaR
		{
			float get(void) { return mp_Param->SigmaR(); }
			void set(float value) { mp_Param->SigmaR() = value; }
		}
		[Browsable(FALSE)]
		virtual property COBFParam* Param
		{
			COBFParam* get(void) { return mp_Param; }
		}
		virtual System::String^ ToString() override
		{
			return "Orientation aligned Bilateral Filter Properties";
		}

		/*! \}                                                                 */
		/*==========================  PRIVATE  ================================*/
	private:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */

		COBFParam*	mp_Param;

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the Flow-based Difference of Gaussian Filter Property
	*/
	[TypeConverter(SimpleTypeConverter::typeid)]
	public ref class CFDoGProp
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		CFDoGProp(CFDoGParam* _param) : mp_Param(_param) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~CFDoGProp(void) {}	

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */		
			
		[Description("Number of DoG operation, higher the value results thicker edges")]
		property int nIter
		{
			int get(void) { return mp_Param->nIter(); }
			void set(int value) { mp_Param->nIter() = value; }
		}
		[Description("higher the value results shorter edges (>=1)")]
		property float SigmaE
		{
			float get(void) { return mp_Param->SigmaE(); }
			void set(float value) { mp_Param->SigmaE() = value; }
		}	
		[Description("higher the value results longer edges (>=1)")]
		property float SigmaR
		{
			float get(void) { return mp_Param->SigmaR(); }
			void set(float value) { mp_Param->SigmaR() = value; }
		}
		[Description("?")]
		property float SigmaM
		{
			float get(void) { return mp_Param->SigmaM(); }
			void set(float value) { mp_Param->SigmaM() = value; }
		}
		[Description("?")]
		property float Tau
		{
			float get(void) { return mp_Param->Tau(); }
			void set(float value) { mp_Param->Tau() = value; }
		}
		[Description("?")]
		property float Phi
		{
			float get(void) { return mp_Param->Phi(); }
			void set(float value) { mp_Param->Phi() = value; }
		}
		[Browsable(FALSE)]
		virtual property CFDoGParam* Param
		{
			CFDoGParam* get(void) { return mp_Param; }
		}
		virtual System::String^ ToString() override
		{
			return "Flow-based Difference of Gaussian Filter Properties";
		}

		/*! \}                                                                 */
		/*==========================  PRIVATE  ================================*/
	private:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */

		CFDoGParam*	mp_Param;

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the Color Quantization Property
	*/
	[TypeConverter(SimpleTypeConverter::typeid)]
	public ref class CCQProp
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		CCQProp(CCQParam* _param) : mp_Param(_param) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~CCQProp(void) {}	

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */		
			
		property int nBins
		{
			int get(void) { return mp_Param->nBins(); }
			void set(int value) { mp_Param->nBins() = value; }
		}
		property float PhiQ
		{
			float get(void) { return mp_Param->PhiQ(); }
			void set(float value) { mp_Param->PhiQ() = value; }
		}	
		property EFilterT Filter
		{
			EFilterT get(void) { return (EFilterT)(mp_Param->Filter()); }
			void set(EFilterT value) { mp_Param->Filter() = (int)value; }
		}
		[Browsable(FALSE)]
		virtual property CCQParam* Param
		{
			CCQParam* get(void) { return mp_Param; }
		}
		virtual System::String^ ToString() override
		{
			return "Color Quantization Properties";
		}

		/*! \}                                                                 */
		/*==========================  PRIVATE  ================================*/
	private:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */

		CCQParam*	mp_Param;

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the Flow-based Abstraction Property
	*/
	[TypeConverter(SimpleTypeConverter::typeid)]
	public ref class CFlowAbsProp
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		CFlowAbsProp(void)
		{	
			mp_Param = new CFAbsParam;
			mp_SST	 = gcnew CSSTProp(&mp_Param->SST());
			mp_OBF	 = gcnew COBFProp(&mp_Param->OBF());
			mp_FDoG	 = gcnew CFDoGProp(&mp_Param->FDoG());
			mp_CQ	 = gcnew CCQProp(&mp_Param->CQ());
			Display  = EDisplayT::RESULT;
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		virtual ~CFlowAbsProp(void) 
		{			
			delete mp_Param;
			mp_Param = NULL;

			delete mp_SST;
			mp_SST = nullptr;

			delete mp_OBF;
			mp_OBF = nullptr;

			delete mp_FDoG;
			mp_FDoG = nullptr;

			delete mp_CQ;
			mp_CQ = nullptr;
		}	

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                Design time properties                        */
		/*! \{                                                                 */		
			
		[Category("Smoothed Structure Tensor")]
		property CSSTProp^ SST
		{
			CSSTProp^ get(void) { return mp_SST; }
		}
		[Category("Orientation aligned Bilateral Filter"), Description("Number of iteration for edge map")]
		property int Ne
		{
			int get(void) { return mp_Param->Ne(); }
			void set(int value) { mp_Param->Ne() = value; }
		}
		[Category("Orientation aligned Bilateral Filter"), Description("Number of iteration for color map")]
		property int Na
		{
			int get(void) { return mp_Param->Na(); }
			void set(int value) { mp_Param->Na() = value; }
		}
		[Category("Orientation aligned Bilateral Filter")]
		property COBFProp^ OBF
		{
			COBFProp^ get(void) { return mp_OBF; }
		}
		[Category("Difference of Gaussian Filter")]
		property CFDoGProp^ FDoG
		{
			CFDoGProp^ get(void) { return mp_FDoG; }
		}
		[Category("Difference of Gaussian Filter")]
		property EDoGT DoG_Type
		{
			EDoGT get(void) { return (EDoGT)(mp_Param->DoGT()); }
			void set(EDoGT value) { mp_Param->DoGT() = (int)value; }
		}
		[Category("Difference of Gaussian Filter")]
		property Drawing::Color Edge_Color
		{
			Drawing::Color get(void) 
			{
				const float* color = mp_Param->EdgeColor();
				return Drawing::Color::FromArgb(255, (uchar)color[0], (uchar)color[1], (uchar)color[2]); 
			}
			void set(Drawing::Color value) { mp_Param->EdgeColor(value.R, value.G, value.B); }
		}
		[Category("Color Quantization")]
		property CCQProp^ CQ
		{
			CCQProp^ get(void) { return mp_CQ; }
		}
		[Category("Smooth Filter"), Description("Final smooth filter: Size of window kernel")]
		property EFilter2T Filter
		{
			EFilter2T get(void) { return (EFilter2T)(mp_Param->Filter()); }
			void set(EFilter2T value) { mp_Param->Filter() = (int)value; }
		}
		[Category("Smooth Filter"), Description("Final smooth filter: Sigma of Gaussian")]
		property float Sigma
		{
			float get(void) { return mp_Param->Sigma(); }
			void set(float value) { mp_Param->Sigma() = value; }
		}
		[Category("Display")]
		property EDisplayT Display;
		[Category("Enable")]
		property bool Enabled;
		[Browsable(FALSE)]
		virtual property CFAbsParam* Param
		{
			CFAbsParam* get(void) { return mp_Param; }
		}
		virtual System::String^ ToString() override
		{
			return "Flow-based Abstraction Parameters";
		}

		/*! \}                                                                 */
		/*==========================  PRIVATE  ================================*/
	private:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */

		CFAbsParam* mp_Param;
		CSSTProp^	mp_SST;
		COBFProp^	mp_OBF;
		CFDoGProp^	mp_FDoG;
		CCQProp^	mp_CQ;

		/*! \}                                                                 */
	};
}
