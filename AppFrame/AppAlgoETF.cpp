#include "stdafx.h"
#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"
#include"AppAlgoETF.h"

#include <math.h>

using namespace AppFrame;
using namespace HKCV;
using namespace HKUtils;
using namespace cv;

bool AppAlgoDoETF::Execute(HKCAppItem^ _appItem)
{
	if(!_appItem) return false;
	//edge tangent flow °j°é¼Æ
	int iteration=3;

	/// Get data ready	
	HKCMediaItem^ srcItem = _appItem->Find("Source");
	if(!srcItem) return false;
	Mat* srcImg = (Mat*)(srcItem->Media->Data());
	int img_height=srcImg->rows;
	int img_width=srcImg->cols;
	int size=img_height*img_width;

	HKCWordArtEvi& flowData = _appItem->Data->WordArtEvi;
	vector<cv::Point2f>& flowMap = flowData.flow_map;
	flowMap.resize(size);

	std::vector<float> m_Ix;
	std::vector<float> m_Iy;
	std::vector<float> m_Magnitude;
	std::vector<float> m_Tx;
	std::vector<float> m_Ty;

	m_Ix.resize(size);
	m_Iy.resize(size);
	m_Magnitude.resize(size);
	m_Tx.resize(size);
	m_Ty.resize(size);

	Mat gray; 
	cvtColor(*srcImg, gray, CV_RGB2GRAY);
	gray.convertTo(gray, CV_32FC1, 1.0f/255.0f);

	Mat vcost,hcost;
	float scale = 10/*10.0f*/;
	Sobel(gray,vcost,CV_32FC1, 1, 0,3,scale,0,cv::BORDER_REFLECT);
//	vcost = scale*vcost;
	GaussianBlur(vcost,vcost,Size(21,21),10);
	Sobel(gray,hcost,CV_32FC1, 0, 1,3,scale,0,cv::BORDER_REFLECT);
//	hcost = scale*hcost;
	GaussianBlur(hcost,hcost,Size(21,21),10);
	for (int i=0; i<size; i++)
	{
		m_Ix[i] = ((float*)hcost.data)[i];
		m_Iy[i] = ((float*)vcost.data)[i];
	}

	for (unsigned int i=0;i< size; ++i)
	{
		float normal_m=sqrt(m_Ix[i]*m_Ix[i] + m_Iy[i]*m_Iy[i]);

		m_Magnitude[i]= (normal_m==0)?0:normal_m;

		m_Tx[i] = (m_Magnitude[i]==0)?0:m_Ix[i]/m_Magnitude[i];
		m_Ty[i] = (m_Magnitude[i]==0)?0:m_Iy[i]/m_Magnitude[i];
	}
//	SetTangent(img_height,img_width,m_Tx,m_Ty,m_Ix,m_Iy,m_Magnitude);
	DoETF(iteration,20,img_height,img_width,m_Tx,m_Ty,m_Magnitude);

	//rotate a degree of 90
	for (int i=0; i<size; i++)
	{
		float Tx_temp = m_Tx[i];
		float Ty_temp = m_Ty[i];

		m_Tx[i] = -Ty_temp;
		m_Ty[i] = Tx_temp;
	}
	NormalizVectrs(img_height,img_width,m_Tx,m_Ty);
	//save data
	for (int i=0; i<size; i++)
	{
		if(m_Tx[i]==0 && m_Ty[i]==0)
		{
			flowMap[i].x=0;
			flowMap[i].y=1;
		}
		else
		{
			flowMap[i].x=m_Tx[i];
			flowMap[i].y=m_Ty[i];
		}
	}
	printflow(img_height,img_width,m_Tx,m_Ty);


//	waitKey(0);
	vector<float>().swap(m_Ix);
	vector<float>().swap(m_Iy);
	vector<float>().swap(m_Magnitude);
	vector<float>().swap(m_Tx);
	vector<float>().swap(m_Ty);

	gray.release();
	vcost.release();
	hcost.release();
	return true;
}
void AppAlgoDoETF::SetTangent(  int img_height,
				int img_width,
				std::vector<float>& update_Tx,
				std::vector<float>& update_Ty,
				std::vector<float>& _Tx,
				std::vector<float>& _Ty,
				std::vector<float>& _magnitude)
{
	int size=img_height*img_width;


	update_Tx.assign(_Tx.begin(),_Tx.end());
	update_Ty.assign(_Ty.begin(),_Ty.end());
	for (unsigned int i=0;i< size; ++i)
	{
// 		update_Tx[i] = _Tx[i];
// 		update_Ty[i] = _Ty[i];

 		float normal_m=sqrt(_Tx[i]*_Tx[i] + _Ty[i]*_Ty[i]);
// 		_magnitude[i]= (normal_m==0)?0:normal_m;

		update_Tx[i] = (normal_m==0)?0:_Tx[i]/normal_m;
		update_Ty[i] = (normal_m==0)?0:_Ty[i]/normal_m;

	}
	
}
void AppAlgoDoETF::DoETF(int iteration/*=3*/,
			int size/*=3*/,
			int img_height,
			int img_width,
			std::vector<float>& _Tx,
			std::vector<float>& _Ty, 
			std::vector<float>& _magnitude)
{
	for (int _iter=0; _iter<iteration; _iter++)
	{
		std::vector<float> new_Tx;
		std::vector<float> new_Ty;
		new_Tx.resize(img_height*img_width,0);
		new_Ty.resize(img_height*img_width,0);
		for (int i=0; i<img_height; i++)
		{
			int min_x = max(i-size/2,0);
			int max_x = min(i+size/2,img_height-1);
			for (int j=0; j<img_width; j++)
			{
				int min_y = max(j-size/2,0);
				int max_y = min(j+size/2,img_width-1);
				for (int y=min_y; y<=max_y; y++)
				{
					for (int x=min_x; x<=max_x; x++)
					{
						double _dot = _Tx[x*img_width+y] * _Tx[i*img_width+j] + _Ty[x*img_width+y] * _Ty[i*img_width+j];

						double phi = (_dot>0)?1:-1;
						double ws = (((y-j)*(y-j)+(x-i)*(x-i))>=((size/2)*(size/2)))? 0:1;
						double wm = 0.5*(1+tanh(_magnitude[x*img_width+y]-_magnitude[i*img_width+j]));
						double wd = abs(_dot);

						new_Tx[i*img_width+j] += phi * _Tx[x*img_width+y] * ws * wm * wd;
						new_Ty[i*img_width+j] += phi * _Ty[x*img_width+y] * ws * wm * wd;	
					}
				}
				new_Tx[i*img_width+j] /= (max_x-min_x+1);
				new_Ty[i*img_width+j] /= (max_y-min_y+1);
			}
		}

		SetTangent(img_height,img_width,_Tx,_Ty,new_Tx,new_Ty,_magnitude);

		vector<float>().swap(new_Tx);
		vector<float>().swap(new_Ty);
	}
}
void AppAlgoDoETF::NormalizVectrs(int img_height,
				  int img_width,
				  std::vector<float>& _Tx,
				  std::vector<float>& _Ty)
{
	for(int	 i = 0;  i < img_height;  i ++)
	{
		for(int	 j = 0;  j < img_width;  j ++)
		{	
			int	index = (i * img_width + j) ;
			float	vcMag = float(  sqrt( double(_Tx[index]*_Tx[index]+_Ty[index]*_Ty[index]) )  );

			float	scale = (vcMag == 0.0f) ? 0.0f : 1.0f / vcMag;
			_Tx[index] *= scale;
			_Ty[index] *= scale;
		}
	}
}
void AppAlgoDoETF::printflow(int img_height,
			     int img_width,
			     std::vector<float>& _Tx,
			     std::vector<float>& _Ty)
{
	Mat FlowField(img_height, img_width, CV_8UC1, Scalar(128));
	for(int i=0;i<img_height;i+=5)
	{
		for(int j=0;j<img_width;j+=5)
		{
			double _px = _Tx[i*img_width+j]*4;
			double _py = _Ty[i*img_width+j]*4;
			cv::line( FlowField, 
				cv::Point(j, i),
				cv::Point(j+_py, i+_px),
				Scalar(1.0), 1 , CV_AA);
			FlowField.data[i*img_width+j]=255;
		}
	}
}