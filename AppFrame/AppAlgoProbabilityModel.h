#pragma once

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgoProbabilityModule.h"

class AppAlgoProbabilityModel
{
protected:
	HKCQRCData*	   m_QRcode;

	double         m_Confidence;
	double		   m_Threshold;
	double		   m_Threshold_STD;
	double		   m_LowerBound;
	
	double m_ModuleThrehold;
	AppAlgoProbabilityModule*		m_Em;
public:
	AppAlgoProbabilityModel(HKCAppItem^ _appItem);
	~AppAlgoProbabilityModel(void);
public:
	std::vector<std::vector<double>> CodewordsErrProbability(cv::Mat& src);
	std::vector<std::vector<double>> CodewordsErrProbability(std::vector<double>& module_energy);
	double CodewordErrProbability(QRCW& cw_data,std::vector<double>& module_energy);

	void SetConfidence(double c){m_Confidence=c;}

	bool IsErrorCodeword(double cw_prob);
	bool IsErrorModule(double module_prob);
	bool IsErrorQRcode(std::vector<std::vector<double>> cw_prob);
	bool IsErrorQRcode(int rs_id,std::vector<double> cw_prob);

	int ErrorCodewordNum(int rs_id, std::vector<double> cw_prob);
	std::vector<int> ErrorCodewordNum(std::vector<std::vector<double>> cw_prob);
protected:
	double CalProbability(std::vector<double>& pm);
};