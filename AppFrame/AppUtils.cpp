/**
* @file AppUtils.cpp
*
* Implementation of the application utility functions
*
* @author James Hung-Kuo Chu
*/

#include "stdafx.h"
#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppUtils.h"

using namespace AppFrame;
using namespace HKUtils;
using namespace cv;

/// Coordinate conversion : screen coordinates to world coordinates
cv::Point2d AppFrame::CoordCvt_Scr2Wrd(const cv::Point2i& _scrPnt)
{
	HKCOGLProjector* projector = HKCOGLProjector::InstancePtr();		

	cv::Point2i scrPnt(_scrPnt);

	/// make sure the point is within viewport
	int* viewport = projector->Viewport(); 
	if(scrPnt.x < 0) scrPnt.x = 0;
	else if(scrPnt.x >= viewport[2]) scrPnt.x = viewport[2]-1;
	if(scrPnt.y < 0) scrPnt.y = 0;
	else if(scrPnt.y >= viewport[3]) scrPnt.y = viewport[3]-1;

	double rstPnt[3];
	projector->UnProject(scrPnt.x, scrPnt.y, rstPnt);	

	return cv::Point2d(rstPnt[0], rstPnt[1]);
}

/// Coordinate conversion : world coordinates to image coordinates
cv::Point2d AppFrame::CoordCvt_Wrd2Img(const cv::Point2d& _wrdPnt, const cv::Rect& _imgRect)
{
	cv::Point2d imgPnt(_wrdPnt);

	/// Find the clamped coordinates
	if((imgPnt.x-_imgRect.x) < 0) imgPnt.x = _imgRect.x;
	if((imgPnt.x-_imgRect.x) >= _imgRect.width) imgPnt.x = _imgRect.x+_imgRect.width-1;
	if((imgPnt.y-_imgRect.y) < 0) imgPnt.y = _imgRect.y;
	if((imgPnt.y-_imgRect.y) >= _imgRect.height) imgPnt.y = _imgRect.y+_imgRect.height-1;
	imgPnt.y = _imgRect.height - imgPnt.y;

	return imgPnt;
}

/// Convert index map to color image
cv::Mat AppFrame::MatCvt_Idx2Color(const cv::Mat& _src, cv::Scalar _color)
{
	HKCColorTable_Element* ctable = HKCColorTable_Element::InstancePtr();
	HKCColorTable_Element::Color_Type color;

	Mat img = Mat::zeros(_src.size(), CV_8UC3);
	int rows = _src.rows, cols = _src.cols;
	for(int y = 0; y < rows; ++y)
	{
		uchar		*imgPtr = img.ptr<uchar>(y);
		const int	*idxPtr = _src.ptr<int>(y);		
		for(int x = 0; x < cols; ++x, imgPtr+=3, idxPtr++)
		{	
			if(*idxPtr != -1)
			{
				color = ctable->get_Color(*idxPtr);
				imgPtr[0] = color.blue();
				imgPtr[1] = color.green();
				imgPtr[2] = color.red();
			}		
			else
			{
				imgPtr[0] = saturate_cast<uchar>(_color[0]);
				imgPtr[1] = saturate_cast<uchar>(_color[1]);
				imgPtr[2] = saturate_cast<uchar>(_color[2]);
			}
		}
	}

	return img;
}

cv::Mat AppFrame::MatCvt_Idx2Color(const cv::Mat& _src, VecI& _indices, cv::Scalar _color)
{
	Mat img = Mat::zeros(_src.size(), CV_8UC3);
	int rows = _src.rows, cols = _src.cols;
	for(int y = 0; y < rows; ++y)
	{
		uchar		*imgPtr = img.ptr<uchar>(y);
		const int	*idxPtr = _src.ptr<int>(y);		
		for(int x = 0; x < cols; ++x, imgPtr+=3, idxPtr++)
		{	
			VecI::iterator f_it = std::find(_indices.begin(), _indices.end(), *idxPtr);
			if(f_it != _indices.end())
			{
				imgPtr[0] = saturate_cast<uchar>(_color[0]);
				imgPtr[1] = saturate_cast<uchar>(_color[1]);
				imgPtr[2] = saturate_cast<uchar>(_color[2]);
			}
		}
	}

	return img;
}

/// Mat conversion : convert an value map to a heat distribution
cv::Mat AppFrame::MatCvt_Val2Heat(const cv::Mat& _m)
{
	/*HKCColorTable_HOT* ctable = HKCColorTable_HOT::InstancePtr();
	HKCColorTable_HOT::Color_Type color;*/

	HKCColorTable_GRAY* ctable = HKCColorTable_GRAY::InstancePtr();
	HKCColorTable_GRAY::Color_Type color;

	/// Normalize the input map	
	cv::Mat nMat;
	if(_m.depth() != CV_64F) _m.convertTo(nMat, CV_64F, 1.0);
	else nMat = _m;
	//cv::normalize(_m, nMat, 0.0, 1.0, NORM_MINMAX);

	Mat img = Mat::zeros(_m.size(), CV_8UC3);
	int rows = nMat.rows, cols = nMat.cols;
	for(int y = 0; y < rows; ++y)
	{
		uchar	*imgPtr = img.ptr<uchar>(y);
		double	*valPtr = nMat.ptr<double>(y);		
		for(int x = 0; x < cols; ++x, imgPtr+=3, valPtr++)
		{	
			color = ctable->get_Interpolate(*valPtr);
			imgPtr[0] = color.blue();
			imgPtr[1] = color.green();
			imgPtr[2] = color.red();
		}
	}

	return img;
}

/// Database conversion: Decode an integer to a binary image
/// Ex. for a 3X3 pattern
/// Bit stream = (MSB)111111111(LSB) with indices 012345678
/// -------------    ------------------
/// | 0 | 1 | 2 |    |(0,0)|    |     |
/// -------------	 ------------------	
/// | 3 | 4 | 5 |<=> |     |    |     | 
/// -------------    ------------------
/// | 6 | 7 | 8 |	 |     |    |(1,1)| 	
/// -------------    ------------------ 
cv::Mat AppFrame::DBCvt_ID2Pattern(int _id, int _size)
{	
	System::String^ binStr = Convert::ToString(_id, 2);
	int length = _size*_size;		
	cv::Mat img(_size, _size, CV_8UC1);
	img.setTo(cv::Scalar::all(255));
	uchar* imgPtr = img.ptr<uchar>(0);
	for(int i = 0; i < binStr->Length; ++i)
		imgPtr[i] = (System::Convert::ToInt32(binStr->Substring(binStr->Length-i-1, 1))==1) ? 0 : 255;
	return img;
}

/// Database conversion: Encode a binary image to an integer
int AppFrame::DBCvt_Pattern2ID(const cv::Mat& _img)
{
	int nRows = _img.rows;
	int nCols = _img.cols;
	if (_img.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}
	
	double id = 0.0;
	int bit = 0;
	for(int i = 0; i < nRows; ++i)
	{
		const uchar* imgPtr = _img.ptr<uchar>(i);		
		for (int j = 0; j < nCols; ++j)		
		{
			if(imgPtr[j] == 0) id += std::pow(2.0, (double)bit);		
			bit++;
		}
	}

	return cv::saturate_cast<int>(id);
}