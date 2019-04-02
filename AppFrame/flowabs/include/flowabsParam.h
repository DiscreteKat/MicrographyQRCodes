#pragma once

namespace flowabs
{
	/**
	*	@brief Enumeration for the Image Cache Type
	*/
	enum ECacheT
	{
		SOURCE=0x0001, 
		RESULT=0x0002, 
		TANGENT_FLOW=0x0004, 
		FLOW_FIELD=0x0008,
		BILATERAL1=0x0010,
		BILATERAL2=0x0020, 
		DIFFERENCE_OF_GAUSSIAN=0x0040, 
		COLOR_QUANTIZE=0x0080,
		CACHE_ALL=0x0100 
	};

	/**
	*	@brief Class for the Smoothed Structure Tensor Parameters
	*/
	class CSSTParam
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		CSSTParam(void)
		{
			m_Sigma	= 2.0f;
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		~CSSTParam(void) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Operator & Access                            */
		/*! \{                                                                 */				

		/// operator "="
		CSSTParam& operator=(const CSSTParam &_rhs)
		{
			if(this == &_rhs) return *this;

			m_Sigma = _rhs.m_Sigma;
			
			return *this;
		}

		float& Sigma(void) { return m_Sigma; }
		const float& Sigma(void) const { return m_Sigma; }

		/*! \}                                                                 */
		/*==========================  PROTECTED  ==============================*/
	protected:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */

		float m_Sigma; 

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the Orientation aligned Bilateral Filter Parameters
	*/
	class COBFParam
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		COBFParam(void)
		{
			m_nIter		= 1;
			m_SigmaD	= 3.0f;
			m_SigmaR	= 0.0425f;
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		~COBFParam(void) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Operator & Access                            */
		/*! \{                                                                 */				

		/// operator "="
		COBFParam& operator=(const COBFParam &_rhs)
		{
			if(this == &_rhs) return *this;

			m_nIter		= _rhs.m_nIter;
			m_SigmaD	= _rhs.m_SigmaD;
			m_SigmaR	= _rhs.m_SigmaR;
			
			return *this;
		}

		int& nIter(void) { return m_nIter; }
		const int& nIter(void) const { return m_nIter; }

		float& SigmaD(void) { return m_SigmaD; }
		const float& SigmaD(void) const { return m_SigmaD; }

		float& SigmaR(void) { return m_SigmaR; }
		const float& SigmaR(void) const { return m_SigmaR; }

		/*! \}                                                                 */
		/*==========================  PROTECTED  ==============================*/
	protected:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */

		int     m_nIter;
		float   m_SigmaD;     
		float   m_SigmaR;

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the Flow-based Difference of Gaussian Filter Parameters
	*/
	class CFDoGParam
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		CFDoGParam(void)
		{
			m_nIter		= 1;
			m_SigmaE	= 1.0f;
			m_SigmaR	= 1.6f;
			m_SigmaM	= 3.0f;
			m_Tau		= 0.99f;
			m_Phi		= 2.0f;
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		~CFDoGParam(void) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Operator & Access                            */
		/*! \{                                                                 */				

		/// operator "="
		CFDoGParam& operator=(const CFDoGParam &_rhs)
		{
			if(this == &_rhs) return *this;

			m_nIter		= _rhs.m_nIter;
			m_SigmaE	= _rhs.m_SigmaE;
			m_SigmaR	= _rhs.m_SigmaR;
			m_SigmaM	= _rhs.m_SigmaM;
			m_Tau		= _rhs.m_Tau;
			m_Phi		= _rhs.m_Phi;
			
			return *this;
		}

		int& nIter(void) { return m_nIter; }
		const int& nIter(void) const { return m_nIter; }

		float& SigmaE(void) { return m_SigmaE; }
		const float& SigmaE(void) const { return m_SigmaE; }

		float& SigmaR(void) { return m_SigmaR; }
		const float& SigmaR(void) const { return m_SigmaR; }

		float& SigmaM(void) { return m_SigmaM; }
		const float& SigmaM(void) const { return m_SigmaM; }

		float& Tau(void) { return m_Tau; }
		const float& Tau(void) const { return m_Tau; }

		float& Phi(void) { return m_Phi; }
		const float& Phi(void) const { return m_Phi; }

		/*! \}                                                                 */
		/*==========================  PROTECTED  ==============================*/
	protected:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */

		int     m_nIter;
		float   m_SigmaE;     
		float   m_SigmaR;     
		float   m_SigmaM;
		float   m_Tau;         
		float   m_Phi;

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the Color Quantization Parameters
	*/
	class CCQParam
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		CCQParam(void)
		{
			m_nBins		= 8;
			m_PhiQ		= 3.40f;
			m_Filter	= 1;
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		~CCQParam(void) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Operator & Access                            */
		/*! \{                                                                 */				

		/// operator "="
		CCQParam& operator=(const CCQParam &_rhs)
		{
			if(this == &_rhs) return *this;

			m_nBins		= _rhs.m_nBins;
			m_PhiQ		= _rhs.m_PhiQ;
			m_Filter	= _rhs.m_Filter;
			
			return *this;
		}

		int& nBins(void) { return m_nBins; }
		const int& nBins(void) const { return m_nBins; }

		float& PhiQ(void) { return m_PhiQ; }
		const float& PhiQ(void) const { return m_PhiQ; }

		int& Filter(void) { return m_Filter; }
		const int& Filter(void) const { return m_Filter; }

		/*! \}                                                                 */
		/*==========================  PROTECTED  ==============================*/
	protected:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */

		int     m_nBins;       
		float   m_PhiQ;       
		int     m_Filter;	/// 0:NONE, 1:3X3, 2:5X5

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the Flow-based Abstraction Parameters
	*/
	class CFAbsParam
	{
		/*==========================  PUBLIC  =================================*/
	public:
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		CFAbsParam(void)
		{
			m_SST.Sigma() = 2.0f;
			m_Ne = 1;
			m_Na = 4;
			m_OBF.nIter() = m_Ne;
			m_OBF.SigmaD() = 3.0f;
			m_OBF.SigmaR() = 4.25f / 100.0f;
			m_DoGT = 0;
			m_FDoG.nIter() = 1;
			m_FDoG.SigmaE() = 1.0f;
			m_FDoG.SigmaR() = 1.6f;
			m_FDoG.SigmaM() = 3.0f;
			m_FDoG.Tau() = 0.99f;
			m_FDoG.Phi() = 2.0f;
			m_EColor[0] = 0.f; m_EColor[1] = 0.f; m_EColor[2] = 0.f;
			m_CQ.nBins() = 8;
			m_CQ.PhiQ() = 3.4f;
			m_CQ.Filter() = 1;
			m_Filter = 1;
			m_Sigma = 1.0f;
		}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                    Destructor                                */
		/*! \{                                                                 */

		~CFAbsParam(void) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Operator & Access                            */
		/*! \{                                                                 */				

		/// operator "="
		CFAbsParam& operator=(const CFAbsParam &_rhs)
		{
			if(this == &_rhs) return *this;

			m_SST	= _rhs.m_SST;		
			m_Ne	= _rhs.m_Ne;		
			m_Na	= _rhs.m_Na;		
			m_OBF	= _rhs.m_OBF;		
			m_DoGT	= _rhs.m_DoGT;		
			m_FDoG	= _rhs.m_FDoG;		
			m_CQ	= _rhs.m_CQ;		
			m_Filter= _rhs.m_Filter;	
			m_Sigma	= _rhs.m_Sigma;
			memcpy(m_EColor, _rhs.m_EColor, 3*sizeof(float));
			
			return *this;
		}

		CSSTParam& SST(void) { return m_SST; }
		const CSSTParam& SST(void) const { return m_SST; }

		int& Ne(void) { return m_Ne; }
		const int& Ne(void) const { return m_Ne; }

		int& Na(void) { return m_Na; }
		const int& Na(void) const { return m_Na; }

		COBFParam& OBF(void) { return m_OBF; }
		const COBFParam& OBF(void) const { return m_OBF; }

		int& DoGT(void) { return m_DoGT; }
		const int& DoGT(void) const { return m_DoGT; }

		CFDoGParam& FDoG(void) { return m_FDoG; }
		const CFDoGParam& FDoG(void) const { return m_FDoG; }

		const float* EdgeColor(void) const { return m_EColor; }
		void EdgeColor(float _r, float _g, float _b) { m_EColor[0]=_r; m_EColor[1]=_g; m_EColor[2]=_b; }

		CCQParam& CQ(void) { return m_CQ; }
		const CCQParam& CQ(void) const { return m_CQ; }

		int& Filter(void) { return m_Filter; }
		const int& Filter(void) const { return m_Filter; }

		float& Sigma(void) { return m_Sigma; }
		const float& Sigma(void) const { return m_Sigma; }

		/*! \}                                                                 */
		/*==========================  PROTECTED  ==============================*/
	protected:
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */

		CSSTParam	m_SST;			/// Smoothed Structure Tensor parameters
		int			m_Ne;			/// Orientation aligned Bilateral Filter parameters : Number of iteration for edge map         
		int			m_Na;			/// Orientation aligned Bilateral Filter parameters : Number of iteration for color map 
		COBFParam	m_OBF;			/// Orientation aligned Bilateral Filter parameters 
		int			m_DoGT;			/// 0:FDoG, 1:DoG 
		CFDoGParam	m_FDoG;			/// Flow-based Difference of Gaussian Filter parameters
		float		m_EColor[3];	/// Edge Color
		CCQParam	m_CQ;			/// Color Quantization parameters
		int			m_Filter;		/// Smooth filter kernel, 0:NONE, 1:3X3, 2:5X5, 3:Flow Smooth
		float		m_Sigma;		/// Sigma of smooth filter

		/*! \}                                                                 */
	};
}
