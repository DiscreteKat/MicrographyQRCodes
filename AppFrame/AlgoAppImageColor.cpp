#include "StdAfx.h"
#include "AlgoAppImageColor.h"


AlgoAppImageColor::AlgoAppImageColor(void)
{
}


AlgoAppImageColor::~AlgoAppImageColor(void)
{
}

void AlgoAppImageColor::BrightnessAndContrast( cv::Mat* src,cv::Mat* dst,double brightness,double contrast )
{
	*dst = src->clone();
	cv::cvtColor(*dst, *dst, CV_RGB2HSV);
	for (int i=0;i<src->rows*src->cols;++i)
	{
		int value = (int)dst->data[i*3+2];
		int saturation = (int)dst->data[i*3+1];

		value = (double)value * (1+brightness);
		if (value>255){value=255;}
		if (value<0){value=0;}

		saturation = (double)saturation * (1+contrast);
		if (saturation>255){saturation=255;}
		if (saturation<0){saturation=0;}

		dst->data[i*3+2] = value;
		dst->data[i*3+1] = saturation;
	}
	cv::cvtColor(*dst, *dst, CV_HSV2RGB);
}
