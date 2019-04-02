#include "StdAfx.h"
#include "AppAlgoProbabilityModel.h"
#include "AppAlgoProbabilityModule.h"

AppAlgoProbabilityModel::AppAlgoProbabilityModel( HKCAppItem^ _appItem )
{
	m_QRcode =  &_appItem->Data->QRCData;
	m_Em     = new AppAlgoProbabilityModule(_appItem);

	m_Threshold     = _appItem->Data->QRCData.cw_error_thershold;
	m_Threshold_STD = _appItem->Data->QRCData.cw_error_thershold_std;
	m_Confidence    = _appItem->Data->QRCData.cw_error_thershold_confidence;
	m_QRcode = &_appItem->Data->QRCData;

	m_ModuleThrehold = pow(m_Threshold+m_Confidence*m_Threshold_STD,0.125);
}

AppAlgoProbabilityModel::~AppAlgoProbabilityModel(void)
{
	if (m_Em!=NULL){delete m_Em;}
}

std::vector<std::vector<double>> AppAlgoProbabilityModel::CodewordsErrProbability( cv::Mat& src )
{
	std::vector<double> module_energy;
	module_energy = m_Em->Execute(src);
	return CodewordsErrProbability(module_energy);
}

std::vector<std::vector<double>> AppAlgoProbabilityModel::CodewordsErrProbability( std::vector<double>& module_energy )
{
	std::vector<std::vector<double>> cw_energy;
	for (int i=0;i<m_QRcode->CWData.size();i++)
	{
		std::vector<double> probability;
		for (int j=0;j<m_QRcode->CWData[i].size();j++)
		{
			double p = CodewordErrProbability(m_QRcode->CWData[i][j],module_energy);
			probability.push_back(p);
		}
		cw_energy.push_back(probability);
	}
	return cw_energy;
}

double AppAlgoProbabilityModel::CalProbability( std::vector<double>& p )
{
	double value=1;
	for (int i=0;i<p.size();i++){value*=(1-p[i]);}
	return 1-value;
}

double AppAlgoProbabilityModel::CodewordErrProbability( QRCW& cw_data,std::vector<double>& module_energy )
{
	std::vector<double> vec_mp;
	for (int k=0;k<cw_data.module_idx.size();k++)
	{
		int idx = cw_data.module_idx[k];
		double module_probability = module_energy[idx];
		vec_mp.push_back(module_probability);
	}
	double p = CalProbability(vec_mp);
	return p;
}

bool AppAlgoProbabilityModel::IsErrorQRcode( std::vector<std::vector<double>> cw_prob )
{
	for (int i=0;i<cw_prob.size();i++){ if(!IsErrorQRcode(i,cw_prob[i])){return false;} }
	return true;
}

bool AppAlgoProbabilityModel::IsErrorQRcode( int rs_id,std::vector<double> cw_prob )
{
	int count = ErrorCodewordNum(rs_id,cw_prob);
	return count <= m_QRcode->CWData[rs_id].max_error;
}

std::vector<int> AppAlgoProbabilityModel::ErrorCodewordNum( std::vector<std::vector<double>> cw_prob )
{
	std::vector<int> count;
	count.resize(cw_prob.size(),0);
	for (int i=0;i<cw_prob.size();i++){ count[i] = ErrorCodewordNum(i,cw_prob[i]); }
	return count;
}

int AppAlgoProbabilityModel::ErrorCodewordNum(int rs_id, std::vector<double> cw_prob )
{
	int count=0;
	for (int i=0;i<cw_prob.size();i++){ if (IsErrorCodeword(cw_prob[i]))count++; }
	return count;
}

bool AppAlgoProbabilityModel::IsErrorCodeword(double cw_prob )
{
	double threshold =  m_Threshold+m_Confidence*m_Threshold_STD;
	if (threshold<0)threshold=0;
	return cw_prob >= threshold;
}

bool AppAlgoProbabilityModel::IsErrorModule( double module_prob )
{
	return module_prob>=m_ModuleThrehold;
}