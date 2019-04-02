#include "stdafx.h"
#include "AppProperty.h"
#include "AppParameter.h"
#include "AppItem.h"
#include "AppAlgorithm.h"
#include "AppAlgoEnergyVisual.h"
#include "AppAlgoStreamlineTrace.h"
#include "QRWordArt/QRCharFBO.h"
#include "QRWordArt/QRSplineFBO.h"
#include "QRWordArt/QRStringLine.h"
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

using namespace AppFrame;
using namespace HKCV;
using namespace HKUtils;
using namespace cv;
using namespace HKCV;

double AppAlgoEnergyVisual::EvaluateWordSpace( QRWordArt::QRStringLines& spline )
{
	std::vector<double> all_Ews; all_Ews.resize(spline.size());

	#pragma omp parallel for
	for (int i=0;i<spline.size();i++){all_Ews[i]=m_TextEnergy.E_Word_Space(*spline[i]);}

	m_Ews = 0;
	for (int i=0;i<all_Ews.size();i++){m_Ews+=all_Ews[i];}
	if(all_Ews.size()!=0)m_Ews/=all_Ews.size();

	return m_Ews;
}

double AppAlgoEnergyVisual::EvaluateLetterSpace( QRWordArt::QRStringLines& spline )
{
	std::vector<double> all_Els; all_Els.resize(spline.size());

	#pragma omp parallel for
	for (int i=0;i<spline.size();i++){all_Els[i]=m_TextEnergy.E_Letter_Space(*spline[i]);}

	m_Els = 0;
	for(int i=0;i<all_Els.size();i++){m_Els+=all_Els[i];}
	if(all_Els.size()!=0)m_Els/=all_Els.size();

	return m_Els;
}

double AppAlgoEnergyVisual::EvaluateTextEnergy( QRWordArt::QRStringLines& spline,double _sigma )
{
	EvaluateWordSpace(spline);
	EvaluateLetterSpace(spline);
	m_Et = (m_Ews+m_Els)*0.5;
	return m_Et;
}

double AppAlgoEnergyVisual::EvaluateTextEnergy( QRWordArt::QRStringLine& spline,double _sigma/*=0.5*/ )
{
	double _Ews = m_TextEnergy.E_Word_Space(spline);
	double _Els = m_TextEnergy.E_Letter_Space(spline);
	return (_Ews+_Els)*0.5;
}

double AppAlgoEnergyVisual::EvaluateCharStructure( QRWordArt::QRStringLines& spline )
{
	m_Ecs = 0;
	double energy = 0;
	double count  = 0;

	for (int i=0;i<spline.size();i++){
		for (int j=0;j<spline[i]->size();j++){
			if ((*spline[i])[j].qr_char == NULL)continue;
			HSSSpline::Scale3 size = spline[i]->get_size((*spline[i])[j].sample);
			energy+=EvaluateCharStructure((*spline[i])[j].qr_char,size);
			count++;
		}
	}
	
	if (count!=0)m_Ecs = energy/count;
	return m_Ecs;
}

double AppAlgoEnergyVisual::EvaluateCharStructure( QRWordArt::QRCharacter::Char* qr_char, HSSSpline::Scale3& size)
{
	double error  = qr_char->StructError();
	double scale  = size[0]*(size[1]+size[2]);
	double sigma  = 0.001*scale;

	error = 1-exp(-(error)/(sigma*sigma));
	return error;
}

double AppAlgoEnergyVisual::EvaluateCharArea( QRWordArt::QRStringLines& spline)
{
	m_Eca = 0;
	double energy = 0;
	double count  = 0;

	for (int i=0;i<spline.size();i++)
	{
		for (int j=0;j<spline[i]->size();j++)
		{
			if ((*spline[i])[j].qr_char == NULL)continue;
			HSSSpline::Scale3 size = spline[i]->get_size((*spline[i])[j].sample);
			energy += EvaluateCharArea((*spline[i])[j].qr_char,size);
			count++;
		}
	}

	if (count!=0)m_Eca = energy/count;
	return m_Eca;
}

double AppAlgoEnergyVisual::EvaluateCharArea( QRWordArt::QRCharacter::Char* qr_char, HSSSpline::Scale3& size)
{
	double error = qr_char->AreaError();
	double scale = size[0]*(size[1]+size[2]);
	double sigma = 0.01*scale;

	error = 1-exp(-(error*error)/(sigma*sigma));
	return error;
}

double AppAlgoEnergyVisual::EvaluateSplineEnergy( QRWordArt::QRStringLines& splines )
{
	EvaluateLineSpace(splines);
	EvaluateFittingEdge(splines);
	m_Es = (m_Ec+m_Ess)*0.5;
	return m_Es;
}

double AppAlgoEnergyVisual::EvaluateFittingEdge( QRWordArt::QRStringLines& splines )
{
	double energy = 0;
	for (int i = 0 ; i < region_segs.size(); i++){energy += EvaluateFittingEdge(splines,i);}
	m_Ec = energy/region_segs.size();
	return m_Ec;
}

double AppAlgoEnergyVisual::EvaluateVisualEnergy( HKCWordArtData& word_art )
{
	double weight[4] = {0,0.2118866,0.256556749,0.531556651};//Es,Et,Ecs,Eca
	//EvaluateSplineEnergy (word_art.splines);0.207569709

	EvaluateTextEnergy   (word_art.splines);
	EvaluateCharStructure(word_art.splines);
	EvaluateCharArea     (word_art.splines);
	return /*weight[0]*m_Es +*/ weight[1]*m_Et + weight[2]*m_Ecs + weight[3]*m_Eca;
}

vector<double> AppAlgoEnergyVisual::findnearest(HSSSpline::PathPoint<2>& ori_p,HSSSpline::PathPoint<2>& normal, cv::Mat& nearlinemap,double step = 0.05)
{  
	//cv::Mat testmap = nearlinemap.clone();
	//
	vector<double> dist;	
	int direct= 0;		
	cv::Point2d p=cv::Point(ori_p.val[0],ori_p.val[1]);
	//cv::circle(testmap,p,1,Scalar(255,255,255),1);
	while (direct<2)
	{
		if (direct==0)
		{
			p+=cv::Point2d(normal[0],normal[1]);
		}
		if (direct==1)
		{
			p-=cv::Point2d(normal[0],normal[1]);
		}
		/*testmap.data[((int)p.y*nearlinemap.cols+(int)p.x)*3+2]=255;*/
		if (p.y>=img_height||p.x>=img_width||p.y<0||p.x<0)
		{
			double dx = p.x-ori_p.val[0];
			double dy = p.y-ori_p.val[1];
			double d= sqrt(dx*dx+dy*dy);
			if (direct==1)
			{
				d=-d;			
			}
			dist.push_back(d);
			p=cv::Point(ori_p.val[0],ori_p.val[1]);
			direct++;
		}
		if (nearlinemap.data[((int)p.y*nearlinemap.cols+(int)p.x)*3]==255)
		{
			if (nearlinemap.data[((int)p.y*nearlinemap.cols+(int)p.x)*3+1]==0)
			{
				//circle(testmap,p,1,Scalar(0,255,0),1);
				//imshow("testmap",testmap);
				//cout<<"edge"<<endl;
				//waitKey(0);
				direct++;
				continue;
			}
			double dx = p.x-ori_p.val[0];
			double dy = p.y-ori_p.val[1];
			double d= sqrt(dx*dx+dy*dy);
			//circle(testmap,p,1,Scalar(0,255,0),1);
			//imshow("testmap",testmap);
			//cout<<d<<endl;
			//waitKey(0);
			if (direct==1)
			{
				d=-d;			
			}
			dist.push_back(d);
			p=cv::Point(ori_p.val[0],ori_p.val[1]);
			direct++;
		}
	}
	return  dist;
	
}

bool AppAlgoEnergyVisual::initial(HKCAppItem^ _appItem)
{
	m_Es=0;
	m_Ec=0;
	m_Ess=0;

	m_Et=0;
	m_Ews=0;
	m_Els=0;

	m_Ecs=0;
	m_Eca=0;

	img_height = _appItem->Data->WordArtEvi.segment_img.rows;
	img_width  = _appItem->Data->WordArtEvi.segment_img.cols;
	
	region_points=_appItem->Data->WordArtEvi.region_points;
	for (int i = 0 ; i<_appItem->Data->WordArtEvi.region_segs.size();i++)
	{
		cv::Mat mat=_appItem->Data->WordArtEvi.region_segs[i].clone();
		region_segs.push_back(mat);
	}

	total_segment= _appItem->Data->WordArtEvi.segment_img;
	if (total_segment.channels()==3)
	{
		segment_img_RGB = total_segment.clone();		
	}
	else
	{
		cvtColor(total_segment,segment_img_RGB,CV_GRAY2BGR);
	}

	for (int i = 0 ; i <img_height*img_width;i++)
	{
		segment_img_RGB.data[i*3+1]=0;
	}
	flip(segment_img_RGB,segment_img_RGB,0);

	edge_splines =  &_appItem->Data->WordArtEvi.edge_splines;
	return true;
}

double AppAlgoEnergyVisual::EvaluateSingleLineSpace(QRWordArt::QRStringLines& splines,QRWordArt::QRStringLine* spline)
{
	QRWordArt::QRSplineFBO	splineFBO;
	splineFBO.Initialize(img_width,img_height);
	splineFBO.SetBGColor(0.0,0.0,0.0);
	splineFBO.SetSPColor(1.1,1.1,1.1);

	double _sig  = 2;
	double w = 1;
	cv::Mat nearlinemap =segment_img_RGB.clone();

	cv::Mat alllinemap;
	for (int s = 0 ; s <splines.size();s++)
	{
		if (splines[s]==spline){continue;}
		splineFBO.Push(splines[s]);
	}
	splineFBO.Draw(&alllinemap);
	splineFBO.Clear();

	bitwise_or(alllinemap,nearlinemap,nearlinemap);
	
	int    count=0;
	double total_energy=0;
	for(int j = 0 ; j <spline->GetCtrlPoints().size()-1; j++)
	{
		for (double k = 0 ; k< 1 ; k+=0.05)
		{
			double energy=0;
			HSSSpline::Vector2 posn   = spline->get_position(j,k);
			HSSSpline::Vector2 normal = spline->get_normal(j,k);
			vector<double> dists = findnearest(posn,normal,nearlinemap);
			for (int d = 0 ; d < dists.size();d++)
			{	
				double _mean = 5.0;
				if (dists[d]>0){_mean=spline->get_size(j,k)[1]/40*50;}
				else{_mean=spline->get_size(j,k)[2]/40*50;}

				if ((abs(dists[d])-_mean)<0){
					double de=1;
					energy+=de;
				}else{
					double de=(1-exp(-pow(1-(abs(dists[d])-_mean)/w,2)/(2*_sig*_sig)));
					energy+=de;
				}
			}if (dists.size()!=0){
				energy/=dists.size();
				total_energy+=energy;
				count++;
			}
			else{continue;} 							
		}
	}
	m_Ess=total_energy/count;
	return m_Ess;
}

double AppAlgoEnergyVisual::EvaluateLineSpace(QRWordArt::QRStringLines& splines)
{
	std::vector<double> all_Ess; 
	all_Ess.resize(splines.size());

	int count = 0;
	for (int i=0;i<splines.size();i++){
		all_Ess[i]=EvaluateSingleLineSpace(splines,splines[i]);
		count++;
	}

	m_Ess = 0;
	for (int i=0;i<all_Ess.size();i++){m_Ess+=all_Ess[i];}
	m_Ess/=count;
	return m_Ess;
}

double AppAlgoEnergyVisual::EvaluateFittingEdge(QRWordArt::QRStringLines& splines,int region_id)
{
	m_Ec=0;
	QRWordArt::QRSplineFBO	splineFBO,checkFBO;
	checkFBO.Initialize(img_width,img_height);
	splineFBO.Initialize(img_width,img_height);
	int wordsize = 10;
	double _mean=wordsize/2;
	double _sig=0.3333;
	double e=0;
	int n = 0;
	cv::Mat alllinemap;
	cv::Mat segment;

	if (region_id!=-1)
	{
		segment=region_segs[region_id].clone();
	}
	else
	{
		segment=total_segment.clone();
		bitwise_not(segment,segment);
	}

	cv::Mat edge_map=Mat(segment.rows,segment.cols,CV_8UC1,cv::Scalar(0));
	cv::Mat distancemap=Mat(segment.rows,segment.cols,CV_8UC1,cv::Scalar(0));
	cv::Mat Energy_map=Mat(segment.rows,segment.cols,CV_8UC3,cv::Scalar(0,0,0));
	cv::Mat seg_img=Mat(segment.rows,segment.cols,CV_8UC1,cv::Scalar(0));
	cv::Mat boundaryregion=Mat(segment.rows,segment.cols,CV_8UC1,cv::Scalar(0));
	vector<double> e_stack;
	if (segment.channels()==3)
	{
		cvtColor(segment,seg_img,CV_BGR2GRAY);
	}
	else
	{
		seg_img=segment.clone();
	}
	edge_map=Mat(segment.rows,segment.cols,CV_8UC1,cv::Scalar(0));
	boundaryregion=Mat(segment.rows,segment.cols,CV_8UC1,cv::Scalar(0));
	for(int i = 0 ; i < img_height;i++)
	{
		for (int j= 0; j < img_width; j++)
		{
			for (int m = -1;m<=1;m++)
				for (int n = -1;n<=1;n++)
				{
					if ((i+m)>=img_height||(j+n)>=img_width||(i+m)<0||(j+n)<0){continue;}

					if(seg_img.data[(i)*img_width+(j)]==0&&seg_img.data[(i+m)*img_width+(j+n)]!=0)				
					{				
						edge_map.data[(i*img_width+j)]=255;
						circle(boundaryregion,Point2i(j,i),wordsize/2,Scalar(255),-1);
					}	
				}
		}	
	}	

	bitwise_not(edge_map,distancemap);
	distanceTransform(distancemap,distancemap,CV_DIST_L2,3);
	threshold(seg_img,seg_img,1,255,THRESH_BINARY);	
	for (int i = 0 ; i <splines.size();i++)
	{
		Mat checkregion,checkregion_GRAY;
		checkFBO.Push(splines[i]);
		checkFBO.Draw(&checkregion);
		checkFBO.Clear();
		flip(checkregion,checkregion,0);
		bitwise_not(checkregion,checkregion);
		cvtColor(checkregion,checkregion_GRAY,CV_BGR2GRAY);
		double OriPointNum = countNonZero(checkregion_GRAY);
		bitwise_and(checkregion_GRAY,seg_img,checkregion_GRAY);
		double AftPointNum = countNonZero(checkregion_GRAY);
		//cout<<OriPointNum<<" "<<AftPointNum<<endl;
		double ratio=AftPointNum/OriPointNum;
		//cout<<ratio<<endl;
		if (ratio>0.8)
		{
			splineFBO.Push(splines[i]);
		}
		
	}
	splineFBO.Draw(&alllinemap);
	splineFBO.Clear();
	//imshow("seg_img",seg_img);
	flip(alllinemap,alllinemap,0);
	bitwise_not(alllinemap,alllinemap);		
	cvtColor(alllinemap,alllinemap,CV_BGR2GRAY);
	//imshow("allinemap before",alllinemap);

	bitwise_xor(alllinemap,seg_img,alllinemap);
	//imshow("alllinmap2",alllinemap);
	
	bitwise_and(boundaryregion,alllinemap,alllinemap);
//  imshow("alllinmap3",alllinemap);
//  imshow(	"boundary",boundaryregion);
//  waitKey();
	Mat energy_normalize=Mat(segment.rows,segment.cols,CV_32FC1,cv::Scalar(0));
	for (int i = 0 ; i < img_height; i++)
	{
		for (int j = 0 ; j < img_width ; j ++)
		{
			
				if(alllinemap.data[i*img_width+j ]!=0)
				{
					float d=distancemap.at<float>(i ,j);
					e=1-exp(-pow((d)/wordsize,2)/(2*_sig*_sig));
					energy_normalize.at<float>(i ,j)=e;
					e_stack.push_back(e);
					double dr, dg, db;
					if (e>1)e=1;
					else if (e<0)e=0;

					if (e < 0.1242) { 
						db = 0.504 + ((1-0.504) / 0.1242)*e; 
						dg = 0;
						dr = 0; 
					} 
					else if (e < 0.3747) { 
						db = 1; 
						dr = 0; 
						dg = (e - 0.1242) * (1  / (0.3747-0.1242)); 
					} else if (e < 0.6253) {    
						db = (0.6253 - e) * (1  / (0.6253-0.3747)); 
						dg = 1; 			    
						dr = (e - 0.3747) * (1  / (0.6253-0.3747)); 
					} else if (e < 0.8758) {    
						db = 0; 			    
						dr = 1; 			    
						dg = (0.8758 - e) * (1  / (0.8758-0.6253)); 
					} else { 
						db = 0; 
						dg = 0; 
						dr = 1. - (e - 0.8758) * ((1-0.504) / (1-0.8758)); 
					}
					Energy_map.data[(i*img_width+j)*3+0]=db*255;
					Energy_map.data[(i*img_width+j)*3+1]=dg*255;
					Energy_map.data[(i*img_width+j)*3+2]=dr*255;					
					n++;
				}
				else if (boundaryregion.data[i*img_width+j ]!=0)
				{
					e_stack.push_back(0);
				}
			}
	}
//	sort (e_stack.begin(), e_stack.end(), sortenergy);
	double tenavgenergy=0;
	for (int i = 0 ; i<e_stack.size(); i++){tenavgenergy+=e_stack[i];}
	//cout<<e_stack.size()<<" "<<n<<endl;
	m_Ec=tenavgenergy/(e_stack.size());
	m_Ec=1-exp(-m_Ec/0.15);
	//Ec=total_energy;
	//normalize(distancemap,distancemap,0,1,NORM_MINMAX);
// 	imshow("alllinemap",alllinemap);  	
// 	imshow("distancemap",distancemap);
// 	imshow("boundaryregion",boundaryregion);
// 	imshow("edge",edge_map);	 	
// 	imshow("Conpactness energy",Energy_map);
// 	waitKey();
	//imwrite(MarshalString("c"+cc+".png"),Energy_map);
	//imwrite(MarshalString("t"+cc+".png"),alllinemap);
	//cc++;
	return m_Ec;
}

double AppAlgoEnergyVisual::EvaluateLocalVisualEnergy( QRWordArt::QRStringLine& spline,QRWordArt::QRStringLine::QRSample& qr_sample )
{
	double weight[4] = {0,0.2118866,0.256556749,0.531556651};//Es,Et,Ecs,Eca
	double _Et   = EvaluateTextEnergy(spline);

	HSSSpline::Scale3 size = spline.get_size(qr_sample.sample);
	double _Ecs  = EvaluateCharStructure(qr_sample.qr_char,size);
	double _Eca  = EvaluateCharArea(qr_sample.qr_char,size);
	return weight[1]*_Et + weight[2]*_Ecs + weight[3]*_Eca;
}
