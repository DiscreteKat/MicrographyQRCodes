#pragma once
#include "QRWordArt/QRCharFBO.h"
#include "AppData.h"
/**
*	@brief Class for Calculate Module Covery Rate
*/
public class AppAlgoProbabilityModule//Cal Energy of module
{
private:
	QRWordArt::QRCharacter::CharFBO m_CharFBO;
	HKCQRCData*						m_QRcode;
	double							m_Wa;
	double							m_da;
	
	int m_Dim;
	cv::Mat						m_ProbMap;

	HKCWordArtEvi* m_WordArtData;
public:				
	AppAlgoProbabilityModule(HKCAppItem^);					
	~AppAlgoProbabilityModule(void);		

	std::vector<double> Execute(cv::Mat& src);
	std::vector<double> Execute(cv::Mat& src,cv::Mat& qrImg);
	double				Execute_Avg(cv::Mat& src);//¥þ³¡¥­§¡
	
	double				Execute_Module(cv::Mat& src, int pid, bool bin = true);//Single Module

	std::vector<double> Execute_Modules( cv::Mat& src, std::vector<int>& pids );
	double				Execute_Modules_Avg(cv::Mat& src, std::vector<int>& pids);

	cv::Mat				Execute_EnergyMap(cv::Mat& src);
	cv::Mat				Execute_EnergyMap(std::vector<double>& energy);
protected:
	std::vector<double>	BuildSampleProb(int _Wa,int da);
	void    BuildSampleProbMap(int num,int _Wa,int da);

	void	Binarization_Modules(cv::Mat& src,std::vector<int>& pids,cv::Mat* dst);

	double  E_Module(cv::Point module_posn,
		             int _Wa, int da, 
					 cv::Mat& bImg,
					 cv::Mat& qrImg);

	double  E_Berr(int x,int y, cv::Mat& bImg, cv::Mat& qrImg);
	double  E_Derr(cv::Point module_posn,int da,cv::Mat& bImg,cv::Mat& qrImg);
};


