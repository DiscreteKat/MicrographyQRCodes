#pragma once

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"
#include "AppAlgoProbabilityModule.h"


public class AppAlgoTextColor
{
#define COLOR_SAMPLE_WORD 0
#define COLOR_SAMPLE_CHAR 1
#define COLOR_ALPHA 2
#define COLOR_SENTENCE 3
#define SAMPLE_MODE 4

#define PERFECT_SAMPLE 4
#define FAST_SAMPLE    5
#define SAMPLE_QUALITY 6

private:
	cv::Mat* m_SrcImg;
	cv::Mat* m_SegImg;
	QRWordArt::QRCharacter::CharFBO m_FBO;

	int m_Color_Mode;
	int m_Sample_Quality;
	/*==========================  PUBLIC  =================================*/
public:					
	AppAlgoTextColor(HKCAppItem^ _appItem);
	AppAlgoTextColor(cv::Mat& src,cv::Mat& seg);
	~AppAlgoTextColor(void){}

	void Execute(QRWordArt::QRStringLine& spline);
	void Enable(int enable);
private:
	void inline AssignColor(QRWordArt::QRStringLine& spline);
	void inline AssignColor_Fast(QRWordArt::QRStringLine& spline);
	void inline AssignColorTable( QRWordArt::QRStringLine& spline );
private:
	int color_id; 
	bool GetMeshColor( cv::Mat& src_img, cv::Mat& seg_img, QRWordArt::QRCharacter::Char* qr_char, cv::Point3f* color);
	bool GetPosnColor( cv::Mat& src_img, cv::Point2f& posn,cv::Mat& seg_img, cv::Point3f* color);
};