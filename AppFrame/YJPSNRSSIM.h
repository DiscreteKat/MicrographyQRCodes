#pragma once
#include <math.h>
#include <sstream>
#include <stdlib.h>

public class PSNR
{
public:
	PSNR(void){}
	PSNR(cv::Mat A ,cv::Mat B,cv::Mat mask, double* MSE,double* psnr);
	~PSNR(void){}
private:
};
public class SSIM
{
public:
	SSIM(void){}
	SSIM(cv::Mat A ,cv::Mat B , cv::Mat mask, double* mssim,cv::Mat ssim_map);
	~SSIM(void){}
private:
};


