#pragma once
#include "StdAfx.h"

class AlgoAppImageColor
{
public:
	AlgoAppImageColor(void);
	~AlgoAppImageColor(void);
public:
	void BrightnessAndContrast(cv::Mat* src,cv::Mat* dst,double brightness,double contrast);
};

