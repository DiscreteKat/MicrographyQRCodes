#pragma once

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"

#include "AppAlgoProbabilityModule.h"
#include "AppAlgoProbabilityModel.h"

#include "QRWordArt/QRPattern.h"

namespace AppFrame 
{
	public class AppAlgoModuleBlending
	{
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		
		AppAlgoModuleBlending(){}
		~AppAlgoModuleBlending(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Algorithm Operations						   */
		/*! \{                                                                 */	

		/// Perform 
		bool Execute(HKCAppItem^ _appItem);
	private:
		void Begin(HKCAppItem^ _appItem);
		void End(HKCAppItem^ _appItem);
	private:
		///
		int m_Count;
		//QRcode Data
		HKCQRCData*	m_QRCData;
		cv::Mat*	m_QRImg;
		int	m_Wa;
		int	m_da;

		//Image Data
		cv::Mat*	m_SrcImg;
		cv::Mat*	m_SegImg;
		cv::Mat*	m_ModuleColor;

		int	m_QRWidth;
		int	m_QRHeight;
		cv::Point2d *m_QROffset;
		
		AppAlgoProbabilityModule*  m_ProbMoudle;
		AppAlgoProbabilityModel*   m_ProbModel;

		int			    m_BG_Color;
		cv::Mat*		m_Foreground_Modules;
		cv::Mat*		m_Background_Modules;
		cv::Mat*		m_WordMap;//RGBA

		//Output
		cv::Mat*				m_NaiveCombine;
		cv::Mat*				m_NaiveBlending;
		QRWordArt::QRPatterns*  m_PatternBlending;
	private:
		bool RecoverCW(HKCAppItem^ _appItem);
		void RecoverCW(int rs_id,int cw_idx,int wa, int da, std::vector<double>* energy,std::vector<std::vector<double>>* cw_prob, int* num0, int* num1);
		void RecoverInf(HKCAppItem^ _appItem);
		//Sort Module w/ Em
		std::vector<int> SortModule(std::vector<int>& module_idx,std::vector<double>& module_energy);
		//Update Probability
		void Update(int rs_id,int cw_id,
			std::vector<double>* dst_energy,                  //output
			std::vector<std::vector<double>>* dst_cw_prob);   //output
	private://Blending Methods
		void NaiveCombination(cv::Point& posn,double wa,double da,cv::Mat* dst);
		void NaiveBlending(cv::Point& posn,double wa,double da,cv::Mat* dst);
		int PatternBlending(int module_idx,double wa,double da);
	private://Luminance Adjustment
		int   ModuleLuminanceOptimize(int module_idx, double init_delta,double step,int *out_R,int *out_G,int* out_B);//³æ¤@delta¡ASA
		static double LuminanceAdjustment( int q, double delta,int *r,int *g,int* b);
		double ModuleLuminanceError(cv::Point& point,int da,cv::Mat& src);
		double LuminanceError(int pixel_idx,int r,int g,int b);
	private://Color Space Transfer
		static void RGB2HSL(int r,int g,int b,double* h,double* s,double* l);
		static void HSL2RGB(double h,double s,double l,int* r,int* g,int* b);
	};
}