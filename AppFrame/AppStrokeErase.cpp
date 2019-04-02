/**
* @file AppStrokeErase.cpp
*
* Implementation of the class methods for eraser stroke
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "AppStroke.h"

using namespace AppFrame;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/

/*! \class AppFrame::HKCStrkErase

Implementation of the class methods. */

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                            Painting                                 */
/// Painting as an eraser
void HKCStrkErase::Paint(cv::Mat& _img, cv::Point2d& _pnt1, cv::Point2d& _pnt2, cv::Scalar _color, int _size)
{
	if(!_img.empty())
		cv::line(_img, _pnt1, _pnt2, cv::Scalar(255,255,255,0), _size);	
}