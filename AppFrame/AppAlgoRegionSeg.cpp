#include "stdafx.h"
#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"

#include "AppAlgoRegionSeg.h"
#include "AppAlgoStreamlineTrace.h"

#include <time.h>
#include <stdlib.h>

using namespace AppFrame;
using namespace HKCV;
using namespace HKUtils;

bool AppAlgoRegionSeg::Execute(HKCAppItem^ _appItem)
{
	std::cout<<" Initial Region Data..."<<std::endl;
	HKCWordArtEvi& word_art_evi = _appItem->Data->WordArtEvi;

	HKCMediaItem^ srcItem = _appItem->Find("Source");
	cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());
	int img_height=srcImg->rows;
	int img_width=srcImg->cols;

	cv::Mat& segment_img = word_art_evi.segment_img;
	cv::Mat& region_img  = word_art_evi.region_img;
	
	VecEdgeLink* vecEdgeLink = word_art_evi.vecEdgeLink;
	vecEdgeLink = new HKCV::VecEdgeLink;

	word_art_evi.region_points.clear();
	word_art_evi.region_segs.clear();

	cv::Mat region;
	cv::Mat initialregion;	
	initialregion=region_img.clone();
	bitwise_not(initialregion,initialregion);

	initialregion.convertTo(region,CV_32FC1);
	normalize(region,region,0,1,CV_MINMAX);

	int biggest=0;
	double smallregionratio = _appItem->Param->WordArt->SmallRangeRatio;

	FindBlobs(region, word_art_evi.region_points);
	for (int r = 0 ; r<word_art_evi.region_points.size();r++)
	{
		region=cv::Mat(srcImg->rows,srcImg->cols,CV_8UC1,cv::Scalar(0));
		for(size_t i=0; i <  word_art_evi.region_points[r].size(); i++)
		{
			int x =  _appItem->Data->WordArtEvi.region_points[r][i].x;
			int y =  _appItem->Data->WordArtEvi.region_points[r][i].y;
			if(region_img.data[y*srcImg->cols+x]!=255){region.data[y*srcImg->cols+x]=255;}
		}

		if(countNonZero(region)<20)
		{
			word_art_evi.region_points.erase( word_art_evi.region_points.begin()+r);
			r--;
		}
		else
		{
			word_art_evi.region_segs.push_back(region);
			biggest=biggest>word_art_evi.region_points[r].size()?biggest:word_art_evi.region_points[r].size();

			cv::Mat region_edge=cv::Mat (img_height,img_width,CV_8UC1,cv::Scalar(0));
			for(int i = 0 ; i < img_height;i++)
			{
				for (int j= 0; j < img_width; j++)
				{
					if (i==img_height-1 || j==img_width-1 || i==0 || j==0)
					{
						if(region.data[(i)*img_width+(j)]==255)
						{
							region_edge.data[(i*img_width+j)]=255;
							continue;
						}
					}
					for (int m = -1;m<=1;m++)
						for (int n = -1;n<=1;n++)
						{
							if ((i+m)>=img_height||(j+n)>=img_width||(i+m)<0||(j+n)<0)
							{
								continue;
							}
							if(region.data[(i)*img_width+(j)]==0&&region.data[(i+m)*img_width+(j+n)]==255)				
							{									
								region_edge.data[(i*img_width+j)]=255;
							}	
						}
				}	
			}	
			Thinning(region_edge);
			region_edge/=255;
			Edge_Linking(region_edge,*vecEdgeLink,HKCEdgeLink::PntT(0, 0), 1);		
			BuildEdgeLines(vecEdgeLink,word_art_evi.edge_splines);
		}
	}
	word_art_evi.region_params.resize(word_art_evi.region_segs.size());

	//Init Param
	int numsmallregion=0;
	for (int r = 0 ; r<word_art_evi.region_points.size();r++)
	{
		if (countNonZero(word_art_evi.region_segs[r])<biggest/smallregionratio)
		{
			word_art_evi.region_params[r].smallregion=true;
			word_art_evi.region_params[r].RangeSize=_appItem->Param->WordArt->SmallRangeSize;
			numsmallregion++;
		}
		else
		{
			word_art_evi.region_params[r].smallregion=false;
			word_art_evi.region_params[r].RangeSize=_appItem->Param->WordArt->RangeSize;
		}

		word_art_evi.region_params[r]. Boundary_Repela= _appItem->Param->WordArt->Boundary_Repela;
		word_art_evi.region_params[r]. Line_Repela    = _appItem->Param->WordArt->Line_Repela;
		word_art_evi.region_params[r]. Boundary_Repelb= _appItem->Param->WordArt->Boundary_Repelb;
		word_art_evi.region_params[r]. Line_Repelb    = _appItem->Param->WordArt->Line_Repelb;
	}
	std::cout<<" Small Region Number: "<<numsmallregion<<std::endl;

	return true;
}

void AppFrame::AppAlgoRegionSeg::FindBlobs( const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs )
{
	blobs.clear();

	// Fill the label_image with the blobs
	// 0  - background
	// 1  - unlabelled foreground
	// 2+ - labelled foreground

	cv::Mat label_image=cv::Mat(binary.size(),CV_32SC1,cv::Scalar(0));
	cv::Mat binary_clone;
	binary.convertTo(binary_clone, CV_32FC1);

	int label_count = 2; // starts at 2 because 0,1 are used already

	for(int y=0; y < binary_clone.rows; y++) {
		float *row = (float*)binary_clone.ptr(y);
		int *row1 = (int*)label_image.ptr(y);
		for(int x=0; x < binary_clone.cols; x++) {
			if(row[x] > 1||row1[x]!=0) {
				continue;
			}
			cv::Rect rect;
			cv::floodFill(binary_clone, cv::Point(x,y), label_count, &rect, 0.02, 0.02, 4);

			std::vector <cv::Point2i> blob;

			for(int i=rect.y; i < (rect.y+rect.height); i++) {
				float *row2 = (float*)binary_clone.ptr(i);
				int *row3 = (int*)label_image.ptr(i);				
				for(int j=rect.x; j < (rect.x+rect.width); j++) {
					if(row2[j] != label_count) {
						continue;
					}					
					row3[j]=label_count;
					blob.push_back(cv::Point2i(j,i));
				}
			}

			blobs.push_back(blob);

			label_count++;
		}
	}
}

void AppFrame::AppAlgoRegionSeg::BuildEdgeLines( VecEdgeLink* vecEdgeLink,QRWordArt::QRStringLines& edgesplines )
{
	for(int i=0;i<vecEdgeLink->size();i++)
	{
		QRWordArt::QRStringLine* spline = new QRWordArt::QRStringLine();
		HKCEdgeLink::VecPnt *p = &(vecEdgeLink->at(i)->Points());
		//cout << p->size() << endl;

		for(int j=0;j<p->size();j++){
			HSSSpline::PathPoint<5> p((*p)[j].x,(*p)[j].y, //Vector
				0.02,0.01,0.01); //Size
			spline->PushBack(p);
		}	
		spline->Fix()=true;
		spline->FittingCurve(0.02);
		edgesplines.push_back(spline);
	}
}
