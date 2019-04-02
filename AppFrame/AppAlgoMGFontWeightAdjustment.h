/**
* @file AppAlgoCharWrapping.h
*
* Classes for Bold Deformation
*
* @author 
*/
#pragma once

#include "AppData.h"
#include "AppAlgoMGWarpingOperator.h"
#include "AppAlgoProbabilityModule.h"
#include "AppAlgoEnergyVisual.h"

public class AppAlgoFontWeightAdjustment: public AppAlgoWarpingOperator
{
	private:
		int m_ImgW;
		int m_ImgH;
		HKCQRCData*	    m_QRCData;
		HKCWordArtData* m_WordArt;
		cv::Rect m_Clipping_Window;
		QRWordArt::QRCharacter::CharFBO m_FBO;
		AppAlgoProbabilityModule m_ModuleEnergy;
		AppAlgoEnergyVisual m_VisualEnergy;
	public:				                                                            	
		AppAlgoFontWeightAdjustment(HKCAppItem^ _appItem);
		~AppAlgoFontWeightAdjustment(void){}		

		//²Ê²Ó¿ï¾Ü
		double Targeting(double scale,QRWordArt::QRCharacter::Char* qr_char,std::vector<int>& module_idxs);
		virtual void Execute(double scale,QRWordArt::QRCharacter::Char* qr_char);
};