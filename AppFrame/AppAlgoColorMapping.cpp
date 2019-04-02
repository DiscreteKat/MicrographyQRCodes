#include "StdAfx.h"
#include "AppAlgoColorMapping.h"

void AppAlgoColorMapping::Jet( double v,char *r,char *g,char *b )
{
	double dr, dg, db;
	Jet(v,&dr,&dg,&db);

	*r = dr * 255;
	*g = dg * 255;
	*b = db * 255;
}

void AppAlgoColorMapping::Jet( double v,double *r,double *g,double *b )
{
	double dr, dg, db;

	if (v>1)v=1;
	else if (v<0)v=0;

	if (v < 0.1242) { 
		db = 0.504 + ((1-0.504) / 0.1242)*v; 
		dg = 0;
		dr = 0; 
	} else if (v < 0.3747) { 
		db = 1; 
		dr = 0; 
		dg = (v - 0.1242) * (1  / (0.3747-0.1242)); 
	} else if (v < 0.6253) {    
		db = (0.6253 - v) * (1  / (0.6253-0.3747)); 
		dg = 1; 			    
		dr = (v - 0.3747) * (1  / (0.6253-0.3747)); 
	} else if (v < 0.8758) {    
		db = 0; 			    
		dr = 1; 			    
		dg = (0.8758 - v) * (1  / (0.8758-0.6253)); 
	} else { 
		db = 0; 
		dg = 0; 
		dr = 1. - (v - 0.8758) * ((1-0.504) / (1-0.8758)); 
	}

	*r = dr;
	*g = dg;
	*b = db;
}

void AppAlgoColorMapping::Hot2Cold( double v,char *r,char *g,char *b )
{
	double dr = 1.0;
	double dg = 1.0;
	double db = 1.0;

	if (v>1)v=1;
	else if (v<0)v=0;

	if (v < 0.25) {
		dr = 0;
		dg = 4 * v;
	} else if (v < 0.5) {
		dr = 0;
		db = 1 + 4 * (0.25 - v);
	} else if (v < (0.75)) {
		dr = 4 * (v - 0.5);
		db = 0;
	} else {
		dg = 1 + 4 * (0.75 - v);
		db = 0;
	}

	*r = dr * 255;
	*g = dg * 255;
	*b = db * 255;
}

void AppAlgoColorMapping::DrawHot2Cold()
{
	cv::Mat map;
	double w = 100;
	double h = 500;

	map.create(h,w,CV_8UC3);
	for (int i=0;i<h;i++)
	{
		char r,g,b;
		double v = (double)i/(double)h;
		Hot2Cold(v,&r,&g,&b);
		for (int j=0;j<w;j++)
		{
			int idx = i*w+j;
			map.data[idx*3  ] = b;
			map.data[idx*3+1] = g;
			map.data[idx*3+2] = r;
		}
	}
	cv::flip(map,map,0);
	imshow("Hot2Cold",map);
}

void AppAlgoColorMapping::DrawJet()
{
	cv::Mat map;
	double w = 100;
	double h = 500;

	map.create(h,w,CV_8UC3);
	for (int i=0;i<h;i++)
	{
		char r,g,b;
		double v = (double)i/(double)h;
		Jet(v,&r,&g,&b);
		for (int j=0;j<w;j++)
		{
			int idx = i*w+j;
			map.data[idx*3  ] = b;
			map.data[idx*3+1] = g;
			map.data[idx*3+2] = r;
		}
	}
	cv::flip(map,map,0);
	imshow("Jet",map);
}
