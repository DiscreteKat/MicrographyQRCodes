#pragma once

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"
#include <map>

public class AppAlgoQRCodeEvaluation
{
private:
	bool m_EnableScanner;//開啟Zbar & ZXing
	bool m_EnableVisualEnergy;

	double m_QRCQ;
	double m_MGVQ;

	double m_High_Energy;
	double m_Low_Energy;

	double m_NumModule;
	double m_NumIsland;
	double m_Island_F;
	double m_Es;
	double m_Et;
	double m_Ecs;
	double m_Eca;

	bool m_DecodeSF;// 解讀成功/失敗
public:	
	bool Zbar_Correct;
	bool Zxing_Correct;

	AppAlgoQRCodeEvaluation(void):m_EnableScanner(false),m_EnableVisualEnergy(false){Init();}	

	void Init(){
		m_MGVQ = 0;
		m_QRCQ = 0;

		m_High_Energy = 0;
		m_Low_Energy  = 0;

		m_NumModule	= 0;
		m_NumIsland	= 0;

		m_Es	=	0;
		m_Et	=	0;
		m_Ecs	=	0;
		m_Eca	=	0;
	}

	void EnableScanner(bool enable){m_EnableScanner=enable;}
	void EnableVisualEnergy(bool enable){m_EnableVisualEnergy=enable;}

	bool Execute(HKCAppItem^ _appItem);
	bool Execute(HKCAppItem^ _appItem,std::vector<int>& module_idx);
	bool Execute(HKCAppItem^ _appItem,cv::Mat& src);
	bool Execute(HKCAppItem^ _appItem,std::vector<int>& module_idx,cv::Mat& src);

	//Output
	std::vector<std::vector<double>>& CW_Prob(){return m_AlgoProb;}
	std::vector<int>& ZbarCWErr() {return m_Zbar_Block_Err_CW;}
	std::vector<int>& ZXingCWErr(){return m_ZXing_Block_Err_CW;}

	std::vector<int>& CW_Err(){return m_CW_Err;}
	std::vector<int>& ZbarErrPid(){ return zbar_err_pids;}
	std::vector<int>& ZxingErrPid(){return zxing_h_err_pids;}

	double VisuleQuality(){return m_MGVQ;}
	double QRcodeQuality(){return m_QRCQ;}
	double IslandRatio(){return (m_NumIsland+m_Island_F)/m_NumModule;}

	void SaveFile(char* filename);
private:
	std::vector<int> zbar_err_pids;
	std::vector<int> zxing_h_err_pids;

	std::vector<std::vector<double>> m_AlgoProb;
	std::vector<int> m_CW_Err;

	std::vector<int> m_Zbar_Block_Err_CW;
	std::vector<int> m_ZXing_Block_Err_CW;

	//計算錯誤module，energy分布
	void CalDistribution(std::vector<double>& energy,int slice,std::vector<int>& distribution);
	void CalDistribution(std::vector<double>& energy,std::vector<int>& module_pid,int slice,std::vector<int>& distribution);
};