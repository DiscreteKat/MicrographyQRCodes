#pragma once

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"

#include "AppAlgoEnergyVisual.h"
#include "AppAlgoProbabilityModule.h"
#include "AppAlgoProbabilityModel.h"

#include "AppAlgoMGFontWeightAdjustment.h"
#include "AppAlgoMGLetterWarping.h"

#include "GraphCut/GCoptimization.h"
#include <map>

#define GC_LABEL_ALL	0
#define GC_LABEL_S		1
#define GC_LABEL_B		2
//Error Correction 
namespace AppFrame 
{
	struct GCSiteData{
		QRWordArt::QRStringLine* spline;
		QRWordArt::QRStringLine::QRSample* qr_sample;
		std::vector<HSSSpline::Vector2> energy;
	};
	typedef std::vector<GCSiteData> GCSiteDatas;
	typedef HSSSpline::Vector2 GCLabelData; // Label (structure alpha,bold alpha)
	typedef std::vector<GCLabelData> GCLabelDatas;

	public ref class AppAlgoWarpingOptimization : public HKCAlgorithm
	{
	private:
		static int m_LabelSet=0;	//0 - ALL
									//1 - Structure Only
									//2 - Bold Only
		int m_ImgW;
		int m_ImgH;
		int m_BGColor;
		HKCQRCData* m_QRCdata;
		QRWordArt::QRStringLines* m_Strings;
		cv::Rect* m_Clipping_Window;
		QRWordArt::QRCharacter::CharFBO*	m_FBO;
		AppAlgoProbabilityModule*				m_ModuleEnergy;
		AppAlgoEnergyVisual*				m_VisualEnergy;

		typedef std::map<QRWordArt::QRCharacter::Char*,std::vector<int>> CQRMap;
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		
		AppAlgoWarpingOptimization(void){}
		virtual ~AppAlgoWarpingOptimization(void){}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Algorithm Operations						   */
		/*! \{                                                                 */	

		virtual bool Execute(HKCAppItem^ _appItem) override;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Access Methods                              */
		/*! \{                                                                 */

		virtual property System::String^ Abbrev
		{
			System::String^ get(void) override { return "Char Warping Adjustment"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"Char Warping Adjustment";
		}	
	public:
		//0 - ALL
		//1 - Structure Only
		//2 - Bold Only
		static void SetLabelType(int type){m_LabelSet=type;}
	private:
		void GreedyWarping(HKCAppItem^ _appItem,QRWordArt::QRStringLines& string);
		void GraphCutWarping(HKCAppItem^ _appItem,QRWordArt::QRStringLines& string,std::vector<double>& csw_samples,std::vector<double>& cbw_samples,double weight);
	private://GraphCut Setting
		void GC_SetNeighbors(GCoptimizationGeneralGraph* gc, GCSiteDatas& site_datas);
		void GC_SetSoomthPenalty(GCoptimizationGeneralGraph* gc, GCLabelDatas& label_datas);
		void GC_CalEnergy(HKCAppItem^ _appItem,AppAlgoFontWeightAdjustment& bold_warping,AppAlgoLetterWarping& struct_warping,GCLabelDatas& label_datas ,GCSiteDatas* site_datas);
	private:
		void SelectSites(QRWordArt::QRStringLines& strings,double wa,GCSiteDatas* site_datas);
		void Warping(QRWordArt::QRCharacter::Char* qr_char,std::vector<double>& warping_param, std::vector<AppAlgoWarpingOperator*>& warping_op);
		std::vector<double> WarpingEvaluation( QRWordArt::QRStringLine& spline,QRWordArt::QRStringLine::QRSample& qr_sample, std::vector<int>& module_idxs,std::vector<double>& warping_param, std::vector<AppAlgoWarpingOperator*>& warping_op, QRWordArt::QRCharacter::DeformationData* result);

		void OutputEnergy(std::string filename,GCSiteDatas& data,std::vector<double>& csw_samples,std::vector<double>& cbw_samples);
		bool ReadEnergy(std::string filename,GCSiteDatas& data,std::vector<double>& csw_samples,std::vector<double>& cbw_samples);
	};
}