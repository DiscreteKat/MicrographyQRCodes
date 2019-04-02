/**
* @file AppStrokeBrush.cpp
*
* Implementation of the class methods for brush stroke
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "AppStroke.h"

using namespace AppFrame;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/*! \class AppFrame::HKCStrkBrush

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                            Painting                                 */
/// Painting with colored brush
void HKCStrkBrush::Paint(cv::Mat& _img, cv::Point2d& _pnt1, cv::Point2d& _pnt2, cv::Scalar _color, int _size)
{
	if(!_img.empty())
		cv::line(_img, _pnt1, _pnt2, _color, _size);	
}