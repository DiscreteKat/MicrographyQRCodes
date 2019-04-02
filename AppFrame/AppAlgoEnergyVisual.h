#pragma once
#include "stdafx.h"
#include "AppAlgoEnergyTextSpace.h"

public class AppAlgoEnergyVisual
{
		public:				
			AppAlgoEnergyVisual(HKCAppItem^ _appitem) {initial(_appitem); }
			~AppAlgoEnergyVisual() {}		
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Algorithm Operations						   */
		/*! \{                                                                 */	

		/// Perform visual quality energy evaluate
		bool initial(HKCAppItem^ _appItem);
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Access Methods                              */
		/*! \{       */
		double getEs(){return m_Es;}
		double getEc(){return m_Ec;}
		double getEss(){return m_Ess;}
		double getEt(){return m_Et;}
		double getEws(){return m_Ews;}
		double getEls(){return m_Els;}
		double getEcs(){return m_Ecs;}
		double getEca(){return m_Eca;}
	public:
		double EvaluateVisualEnergy(HKCWordArtData& word_art);
		double EvaluateLocalVisualEnergy(QRWordArt::QRStringLine& spline,QRWordArt::QRStringLine::QRSample& qr_sample);

		double EvaluateSplineEnergy(QRWordArt::QRStringLines& spline);

		double EvaluateLineSpace(QRWordArt::QRStringLines& splines);
		double EvaluateSingleLineSpace(QRWordArt::QRStringLines& splines,QRWordArt::QRStringLine* spline);

		double EvaluateFittingEdge(QRWordArt::QRStringLines& splines);
		double EvaluateFittingEdge(QRWordArt::QRStringLines& splines,int region_id);

		double EvaluateTextEnergy(QRWordArt::QRStringLines& splines,double _sigma=0.5);
		double EvaluateTextEnergy(QRWordArt::QRStringLine& spline,double _sigma=0.5);
		double EvaluateLetterSpace(QRWordArt::QRStringLines& splines);
		double EvaluateWordSpace(QRWordArt::QRStringLines& splines);

		double EvaluateCharStructure(QRWordArt::QRStringLines& splines);
		double EvaluateCharStructure(QRWordArt::QRCharacter::Char* qr_char, HSSSpline::Scale3& size);
		double EvaluateCharArea(QRWordArt::QRStringLines& splines);
		double EvaluateCharArea(QRWordArt::QRCharacter::Char* qr_char, HSSSpline::Scale3& size);
	private:
		vector<double> findnearest(HSSSpline::PathPoint<2>& ori_p,HSSSpline::PathPoint<2>& normal, cv::Mat& nearlinemap,double step);

	private:
		double m_Es;
		double m_Ec,m_Ess;

		double m_Et;
		double m_Ews,m_Els;

		double m_Ecs;
		double m_Eca;

		AppAlgoEnergyTextSpace   m_TextEnergy;
		
		int img_height;
		int img_width;
		QRWordArt::QRStringLines*				edge_splines;
		cv::Mat									segment_img_RGB;
		cv::Mat									total_segment;
		std::vector<cv::Mat>					region_segs;
		std::vector<std::vector<cv::Point2i>>	region_points;
};