/**
* @file AppUtils.h
*
* Application utility functions
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#ifndef _APPUTILS_H_
#define _APPUTILS_H_

namespace AppFrame
{	
	/// Coordinate conversion : screen coordinates to world coordinates
	cv::Point2d CoordCvt_Scr2Wrd(const cv::Point2i&);		

	/// Coordinate conversion : world coordinates to image coordinates	
	cv::Point2d CoordCvt_Wrd2Img(const cv::Point2d&, const cv::Rect&);

	/// Coordinate conversion : screen coordinates to image coordinates	
	inline cv::Point2d CoordCvt_Scr2Img(const cv::Point2i& _scrPnt, const cv::Rect& _imgRect)
	{
		return CoordCvt_Wrd2Img(CoordCvt_Scr2Wrd(_scrPnt), _imgRect);
	}	

	/// Value conversion : convert a value in source range to value in target range
	inline double ValCvt_Range2Range(double _r1Val, double _r1Min, double _r1Max, double _r2Min, double _r2Max)
	{
		return _r2Min + Math::Abs(_r1Val-_r1Min)*Math::Abs(_r2Max-_r2Min)/Math::Abs(_r1Max-_r1Min);
	}	

	/// Mat conversion : convert an index map to a color image
	cv::Mat MatCvt_Idx2Color(const cv::Mat&, cv::Scalar);

	/// Mat conversion : convert an index map to a color image
	cv::Mat MatCvt_Idx2Color(const cv::Mat&, VecI&, cv::Scalar);

	/// Mat conversion : convert an value map to a heat distribution
	cv::Mat MatCvt_Val2Heat(const cv::Mat&);

	/// Database conversion: Decode an integer to a binary pattern
	cv::Mat DBCvt_ID2Pattern(int, int);

	/// Database conversion: Encode a binary pattern to an integer
	int DBCvt_Pattern2ID(const cv::Mat&);	
}

#endif