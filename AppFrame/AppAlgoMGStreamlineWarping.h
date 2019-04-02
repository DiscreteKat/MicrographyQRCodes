#pragma once

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"

#include <map>
#include "QRWordARt/QRCharacter.h"
#include "QRWordARt/QRStringLine.h"
#include "QRWordArt/QRCharFBO.h"

#include "AppAlgoEnergyVisual.h"
#include "AppAlgoProbabilityModule.h"
#include "AppAlgoModuleSelection.h"

//Error Correction 
namespace AppFrame 
{
	struct SplineWarpingTarget{
		double w,move;
		SplineWarpingTarget():w(1.0),move(0){}
		void operator = (const SplineWarpingTarget& input){
			w = input.w;
			move = input.move;
		}
	};
	typedef std::pair<HSSSpline::Sample,SplineWarpingTarget> SplineWarpingSampleTarget;
	typedef std::vector<SplineWarpingSampleTarget> SplineWarpingTargetData;
	
	public ref class AppAlgoStreamlineWarping : public HKCAlgorithm
	{
		typedef std::map<QRWordArt::QRCharacter::Char*,std::vector<int>> CQRMap;
	private:
		int m_Wa;
		int m_ImgW;
		int m_ImgH;
		HKCQRCData*	m_QRCData;

		AppAlgoProbabilityModule*  m_AlgoModuleEnergy;
		//AppAlgoVisaulEnergy*  m_AlgoVisualEnergy;
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		
		AppAlgoStreamlineWarping(void):m_AlgoModuleEnergy(NULL){}
		virtual ~AppAlgoStreamlineWarping(void)
		{
			if (m_AlgoModuleEnergy!=NULL){delete m_AlgoModuleEnergy;}
		}		

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
			System::String^ get(void) override { return "Spline Width Adjustment"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"Spline Width Adjustment";
		}	
		
	private:
		void SplineWarping(QRWordArt::QRStringLine& string,SplineWarpingTargetData& data,double alpaha);

		void   CalTargets(HKCQRCData* qrcode,int bg_color,std::vector<int> p_idx,std::vector<double> energy,const QRWordArt::QRStringLine::QRSample& sample,SplineWarpingTargetData* target_data);
		bool   CalTarget( int type,cv::Point qr_posn,QRWordArt::QRCharacter::QRNode* node, double wa,double da, SplineWarpingSampleTarget* target);
		double CalWeight(double len,double a);
		double NearestNode(QRWordArt::QRCharacter::QRNodes& nodes,cv::Point qr_posn,double threhold,int* index);
	};
}