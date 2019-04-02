#pragma once
#include "stdafx.h"

class AppAlgoBinarization
{
private:
	std::vector<std::vector<double>> m_Cumulation;
	cv::Mat m_Src;
	int m_ZBar_Window_W;
	int m_ZBar_Window_H;
public:
	AppAlgoBinarization(cv::Mat& src);
	~AppAlgoBinarization(){};
public:
	void    Global_Binarization(cv::Mat* dst);
	void	ZBar_Binarization(cv::Mat* dst);
	int	    ZBar_Binarization(int x,int y);
private:
	double	Cal_ZBar_Threshold(int x,int y);
	void    Cal_Cumulation(cv::Mat& src);
};

