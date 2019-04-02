#include "StdAfx.h"
#include "AppAlgoBinarization.h"
#include <omp.h>

AppAlgoBinarization::AppAlgoBinarization( cv::Mat& src )
{
	m_Src = src.clone();
	if (m_Src.channels() > 1)cvtColor(m_Src, m_Src, CV_BGR2GRAY);

	int  logwindw,logwindh;
	for(logwindw=4;logwindw<8 && (1<<logwindw)<(src.cols+7>>3);logwindw++);
	for(logwindh=4;logwindh<8 && (1<<logwindh)<(src.rows+7>>3);logwindh++);

	m_ZBar_Window_W = 1<<logwindw;
	m_ZBar_Window_H = 1<<logwindh;

	Cal_Cumulation(m_Src);
}


void AppAlgoBinarization::ZBar_Binarization(cv::Mat* dst )
{
	dst->create(m_Src.cols,m_Src.rows,CV_8UC1);
	for (int i=0; i<m_Src.rows; i++){
		for (int j=0; j<m_Src.cols; j++){
			int idx = i*m_Src.cols+j;
			dst->data[idx] = ZBar_Binarization(j,i);
		}	
	}
}

int AppAlgoBinarization::ZBar_Binarization(int x, int y)
{
	int idx = y*m_Src.cols+x;
	double threshold = Cal_ZBar_Threshold(x,y);
	return (m_Src.data[idx]>threshold)?255:0;
}

double AppAlgoBinarization::Cal_ZBar_Threshold(int x,int y)
{
	int min_x = (int)std::max( x-m_ZBar_Window_W*0.5 , 0.0 );
	int max_x = (int)std::min( x+m_ZBar_Window_W*0.5 , (double)m_Src.cols-1);

	int min_y = (int)std::max( y-m_ZBar_Window_H*0.5 , 0.0 );
	int max_y = (int)std::min( y+m_ZBar_Window_H*0.5 , (double)m_Src.rows-1);

	double m = 0;
	int    k = (max_x-min_x+1)*(max_y-min_y+1);
	for (int i=min_y; i<=max_y; i++)
	{
		if (min_x==0){m +=m_Cumulation[i][max_x];}
		else{m += m_Cumulation[i][max_x] - m_Cumulation[i][min_x-1];}
	}

	double threshold = m/k-3;
	if (threshold<0)threshold=0;
	return threshold;
}

void AppAlgoBinarization::Cal_Cumulation( cv::Mat& src )
{
	m_Cumulation.resize(src.rows);
	for (int i=0; i<src.rows; i++)
	{
		m_Cumulation[i].resize(src.cols,0);
		for (int j=0; j<src.cols; j++)
		{
			double val = src.data[i*src.cols+j];
			if (j==0){m_Cumulation[i][j] = val;}
			else m_Cumulation[i][j] = m_Cumulation[i][j-1]+val;
		}	
	}
}

void AppAlgoBinarization::Global_Binarization( cv::Mat* dst )
{
	dst->create(m_Src.cols,m_Src.rows,CV_8UC1);
	for (int i=0; i<m_Src.rows*m_Src.cols; i++)
	{
		if (m_Src.data[i]<100){dst->data[i]=0;}
		else{dst->data[i]=255;}
	}	
}
