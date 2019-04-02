/**
* @file AppAlgoCharWrapping.h
*
* Classes for Character Wrapping
*
* @author 
*/
#pragma once

#include "AppAlgoMGWarpingOperator.h"
#include "AppAlgoProbabilityModule.h"
#include "AppAlgoEnergyVisual.h"

public class AppAlgoLetterWarping: public AppAlgoWarpingOperator
{
	typedef std::map<QRWordArt::QRCharacter::Char*,QRWordArt::QRCharacter::Node_Targets> TargetMap;
private:
	int		m_ImgW;
	int		m_ImgH;
	double	m_Wa;
	double	m_da;
	int		m_BGColor;
	cv::Rect m_Clipping_Window;
	TargetMap m_TargetMap;
	HKCQRCData*	    m_QRCData;
	HKCWordArtData* m_WordArt;
	QRWordArt::QRCharacter::CharFBO m_FBO;
	AppAlgoProbabilityModule m_ModuleEnergy;
	AppAlgoEnergyVisual m_VisualEnergy;
public:					
	AppAlgoLetterWarping(HKCAppItem^ _appItem);
	~AppAlgoLetterWarping(void){}		

	void Targeting(HKCAppItem^ _appItem);
	virtual void Execute( double alpha,QRWordArt::QRCharacter::Char* qr_char);
private:
	QRWordArt::QRCharacter::Node_Targets CalTargets(HKCQRCData* qrcode,int bg_color,std::vector<int>& p_idx,std::vector<double> energy,const QRWordArt::QRStringLine::QRSample& sample);
	QRWordArt::QRCharacter::Node_Target  CalTarget( int type,cv::Point2d qr_posn,QRWordArt::QRCharacter::QRNode* node, double wa,double da, double weight);
	double CalWeight(double len,double a);
	double NearestNode(QRWordArt::QRCharacter::QRNodes& nodes,cv::Point2d qr_posn,double threhold,int* index);

	bool CheckOffside(QRWordArt::QRCharacter::QRNode* node,QRWordArt::QRCharacter::Node_Target& target,const QRWordArt::QRStringLine::QRSample& sample);
	bool CheckAvoid(QRWordArt::QRCharacter::Node_Target& target,const QRWordArt::QRStringLine::QRSample& sample);

	//補Target在沒有受控制的Skeleton Main Node
	//Skeleton唯一且target只有一個，補端點Target
	void ExtraTarget(QRWordArt::QRCharacter::Node_Targets& targets,QRWordArt::QRCharacter::Char* c);
};