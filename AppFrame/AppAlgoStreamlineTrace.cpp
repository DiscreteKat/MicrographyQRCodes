#include "stdafx.h"
#include <limits>
#include <algorithm>
#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"
#include "AppAlgoStreamlineTrace.h"
#include "QRWordArt/QRSplineFBO.h"
#include <math.h>
#include <sstream>
#include <stdlib.h>
// #include <time.h>
using namespace AppFrame;
using namespace HKCV;
using namespace HKUtils;
using namespace cv;
using namespace HKCV;
//using namespace OMT;
bool AppAlgoStreamlineTrace::traverse_tangent(QRWordArt::QRStringLine* Edgespline, cv::Point2f& pnt, cv::Point2f& tangent,int range_size)
{
	//Mat test(333,333,CV_8UC3,Scalar(0,0,0));
	HSSSpline::Samples samples = Edgespline->UniformSampling(1);
	double min_dist=img_height*img_width;
	bool find=false;
	for(int i = 0 ;i< samples.size() ;i++ )
	{
		int x=Edgespline->get_x(samples[i]);
		int y=Edgespline->get_y(samples[i]);
		y =img_height-y;
		//test.data[(333*y+x)*3]=255;
		//circle(test,Point2f(x,y),1,Scalar(255,0,0),-1);
		HSSSpline::PathPoint<2> tan=Edgespline->get_tangent(samples[i]);
		//line(test,Point(x,y),Point(x+tan[0]*10,y-tan[1]*10),Scalar(0,255,255),1);
// 		imshow("test",test);
// 		waitKey(0);
		double dist = sqrt((x-pnt.x)*(x-pnt.x)+(y-pnt.y)*(y-pnt.y));
		if (dist<range_size&&dist<min_dist)
		{		
			min_dist=dist;
			tangent.x = tan[0];
			tangent.y = -tan[1];
			find=true;
		}			
	}
	return find;
}

bool AppAlgoStreamlineTrace::line_sort(ChosenInfo& line1, ChosenInfo& line2){return (line1.line_order < line2.line_order);}
bool AppAlgoStreamlineTrace::nline_sort(Point3d& score1, Point3d& score2){return (score1.y > score2.y);}
bool AppAlgoStreamlineTrace::int_sort(int i,int j) { return (i>j);}

bool AppAlgoStreamlineTrace::SortLineOrder( vector<ChosenInfo>& chosen_infos,QRWordArt::QRStringLines& splines)
{
	QRWordArt::QRStringLines newsplines;
	sort(chosen_infos,line_sort);
	for (int i = 0; i<chosen_infos.size(); i++)
	{
		int id =chosen_infos[i].lineid;

		if (newsplines.size()!=0)
		{
			newsplines.back()->NextLine(splines[id]);
			splines[id]->LastLine(newsplines.back());
		}
		newsplines.push_back(splines[id]);
		
	}
	splines = newsplines;
	return true;
}

bool AppAlgoStreamlineTrace::Execute(HKCAppItem^ _appItem)
{	
	if(!_appItem) return false;
	/// Get data ready
	printf("Line Tracing...\n");

	HKCMediaItem^ srcItem = _appItem->Find("Source");
	if(!srcItem) return false;
	Mat* srcImg = (Mat*)(srcItem->Media->Data());
	img_height=srcImg->rows;
	img_width=srcImg->cols;
	HKCWordArtEvi& StringLinesData = _appItem->Data->WordArtEvi;
	vector<cv::Point2f>& flowMap = StringLinesData.flow_map;
	cv::Mat& segment_img = StringLinesData.segment_img;
	cv::Mat& region_img = StringLinesData.region_img;	
	cv::Mat edge_map=cv::Mat (img_height,img_width,CV_8UC1,cv::Scalar(0));
	vector<vector<cv::Point2f>> lines_position; 	
	vector<vector<cv::Point2i>>& blobs=_appItem->Data->WordArtEvi.region_points;
	_appItem->Data->WordArtEvi.vecEdgeLink=new HKCV::VecEdgeLink;
	VecEdgeLink* vecEdgeLink = _appItem->Data->WordArtEvi.vecEdgeLink;
	cv::Mat break_area_img=segment_img.clone();
	string_space=_appItem->Param->WordArt->LineSpace;
	vector<vector<vector<cv::Point2i>>> region_lines;
	/******************************************************************/
	/***********    1. Line Tracing                     ***************/
	/******************************************************************/
	printf("step1 : TracingLines... ..                    \r");
	cv::Mat region;
	for (int r = 0 ; r<blobs.size();r++)
	{
		region=_appItem->Data->WordArtEvi.region_segs[r].clone();
// 		imshow("region",region);
// 		waitKey(0);
		
		for(int i = 0 ; i < img_height;i++)
		{
			for (int j= 0; j < img_width; j++)
			{
				if (i==img_height-1 || j==img_width-1 || i==0 || j==0)
				{
					if(region.data[(i)*img_width+(j)]==255)
					{
						edge_map.data[(i*img_width+j)]=255;
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
							edge_map.data[(i*img_width+j)]=255;
						}	
					}
			}	
		}	
	}
	//////////////////////////////////////////////////////////////////////////
	//get edge 
	//////////////////////////////////////////////////////////////////////////
	QRWordArt::QRStringLines & Edgesplines=_appItem->Data->WordArtEvi.edge_splines;
	//edge_map=segment_img.clone();
	_appItem->Data->WordArtEvi.region_num=blobs.size();
	regions_chosen_infos=new vector<vector<ChosenInfo>> [blobs.size()];
	vector<RegionCandidateData>& region_splines = _appItem->Data->WordArtEvi.region_splines;
	
	vector<vector<cv::Point2i>> lines;
	vector<LineData> lines_data;
	double smallregionratio = _appItem->Param->WordArt->SmallRangeRatio;
	int NumSmallRegion=0;
	
	for (int r = 0 ; r<blobs.size();r++)
	{	
		printf("region %d-%d tracing                                                  \r",r,blobs.size());
		int range_size=_appItem->Data->WordArtEvi.region_params[r].RangeSize;
		smallregion=_appItem->Data->WordArtEvi.region_params[r].smallregion;	
		BoundaryRepela =_appItem->Data->WordArtEvi.region_params[r].Boundary_Repela;
		LineRepela=_appItem->Data->WordArtEvi.region_params[r].Line_Repela;
		BoundaryRepelb=_appItem->Data->WordArtEvi.region_params[r].Boundary_Repelb;
		LineRepelb=_appItem->Data->WordArtEvi.region_params[r].Line_Repelb;
		RegionCandidateData newcandidate;
		QRWordArt::QRStringLines& splines= newcandidate.splines;
		TracingLines(*srcImg,flowMap,segment_img,blobs,lines,lines_data,r,range_size);
		vector<ChosenInfo> chosen_infos;
		int tracing_time=1;
		cv::Mat alllinemask(img_height,img_width,CV_8UC3,cv::Scalar(0,0,0));
		cv::Mat allline=segment_img.clone();

		float last_cover_ratio=0;
		float ratio_lines_record=0;
		printf("region %d-%d start                                                    \r",r,blobs.size());
		///////////////////////////////////////////////////////////
	
		int num_lines=0;
		float Ratio_count=0;
		/******************************************************************/
		/***********    4. Choose Good Lines of each line in ratio    ***************/
		/******************************************************************/
		//waitKey(0);
					
		vector<cv::Point2i> chosen_line_id;
		
		Ratio_count = ChooseGoodLinesR(lines,lines_data,alllinemask,edge_map,Edgesplines,splines,chosen_infos,range_size);
		//updatelines(lines,lines_data);		

		break_area_img=segment_img.clone();



		/*for (int i =0 ; i < chosen_infos.size();i++)
		{
			for (int j = 0;j<chosen_infos[i].usize.size();j++)
			{
				chosen_infos[i].usize[j]=chosen_infos[i].usize[j]*40;					
			}
			BuildStringLines_Unifromsize(chosen_infos[i],splines);	
		}*/

		printf("chosenlines %d                                    \r",(chosen_infos).size());
		
		
		region_splines.push_back(newcandidate);

		vector<vector<cv::Point2i>>().swap(lines);
		vector<LineData>().swap(lines_data);
		regions_chosen_infos[r].push_back(chosen_infos);
		
		printf("region %d-%d done                                   \r",r,blobs.size());
	}
	cout<<"small region number : "<< NumSmallRegion<<endl;
 	//imshow("alllinemask",alllinemask);	  
	//imshow("allline",allline);
	

	return true;
}
Point3f AppAlgoStreamlineTrace::findnearest(vector<cv::Point2i>& trace_line,vector<cv::Point2f>& flow_map,cv::Point2i& trace_point)
{
	float minx;
	float miny;
 	float _mind = FLT_MAX;
	for (int i = 0 ; i< trace_line.size(); i++)
	{
		float dx = trace_point.x-trace_line[i].x;
		float dy = trace_point.y-trace_line[i].y;
		float _dist = sqrt(dx*dx+dy*dy);
		int p =(int)trace_line[i].x*img_width+(int)trace_line[i].y;
		if(_mind>_dist)
		{		

			if (!_isnan(flow_map[p].x) && _finite(flow_map[p].x) &&!_isnan(flow_map[p].y) && _finite(flow_map[p].y))			
			{
				minx= trace_line[i].x;
				miny= trace_line[i].y;
				_mind=+_dist;
			}		
		}
	}
	int _idx=minx*img_width+miny;
	if ((flow_map[_idx].y*(trace_point.x-minx)-flow_map[_idx].x*(trace_point.y-miny))>0)
	{			
		//cout<<"right"<<endl;
		_mind=-_mind;			
	}
	else
	{
		//cout<<"left"<<endl;
		_mind=_mind;
	}
	//imshow("testf",testf);
	//waitKey(0);
	return Point3f(minx,miny,_mind);
}
void AppAlgoStreamlineTrace::checkseedcover(vector<cv::Point2f> &seed_array,vector<bool> &seed_orientation, cv::Mat& lineregionmask)
{
// 	cv::Mat Tt=lineregionmask.clone();
// 	cout<<seed_array.size()<<endl;
// 	cvtColor(Tt,Tt,CV_GRAY2BGR);
	for (int i = 0  ; i < seed_array.size(); i++)
	{	
		
		int _idx=round(seed_array[i].x)*img_width+round(seed_array[i].y);
// 		Tt.data[_idx*3+0]=0;
// 		Tt.data[_idx*3+1]=0;
// 		Tt.data[_idx*3+2]=255;
		if (lineregionmask.data[_idx]==0)
		{
			seed_array.erase(seed_array.begin()+i);
			seed_orientation.erase(seed_orientation.begin()+i);
			i--;
		}
	}	
	
//	cout<<seed_array.size()<<endl;
	//imshow("Tt",Tt);
//	waitKey();

}
bool AppAlgoStreamlineTrace::TracingLines(cv::Mat& src_img, vector<cv::Point2f> flow_map, cv::Mat& segment_img,vector < vector<cv::Point2i > >& blobs, vector<vector<cv::Point2i>>& output_lines, vector<LineData>& lines_info,int r,int range_size)
{
	range_size+=1;	
	if (smallregion)
	{
		string_space=0;
	}
	int _count=0;
	float x1,y1,x2,y2;
	vector<cv::Point2i> boundarypoint;
	vector<cv::Point2i> trace_line;
	vector<cv::Point2f> repel_map;
	repel_map.resize(flow_map.size(),Point2f(0,0));
	float normaly;
	float normalx;
	int dilation_size=1;
	cv::Mat kernel= getStructuringElement(2,Size(2*dilation_size + 1, 2*dilation_size+1),Point(dilation_size, dilation_size));
	cv::Mat test(img_height,img_width,CV_8UC3,cv::Scalar(0,0,0));
	cv::Mat boundary(img_height,img_width,CV_8UC1,cv::Scalar(0));
	cv::Mat lineout(img_height,img_width,CV_8UC3,cv::Scalar(0,0,0));
	cv::Mat linemask(img_height,img_width,CV_8UC1,cv::Scalar(0));
	cvtColor(segment_img,lineout,CV_GRAY2BGR);
	float midx;
	float midy;
	cv::Mat region;
	vector<Point2f> SeedQueue;
	vector<bool> SeedOrientation;
	if(r<blobs.size()){

		repel_map.resize(flow_map.size(),Point2f(0,0));
		region=cv::Mat(img_height,img_width,CV_8UC1,cv::Scalar(0));
		for(size_t j=0; j < blobs[r].size(); j++) {

			int x = blobs[r][j].x;
			int y = blobs[r][j].y;
			region.data[y*img_width+x]=255;			
		}
	
		/////////////////////boundary repel///////////////////////////////////////
		test=Mat(img_height,img_width,CV_8UC3,cv::Scalar(0,0,0));
		boundary=Mat(img_height,img_width,CV_8UC3,cv::Scalar(0,0,0));
		for(int i = 0 ; i < img_height;i++)
		{
			for (int j= 0; j < img_width; j++)
			{
				if (i==img_height-1 || j==img_width-1 || i==0 || j==0)
				{
					if(region.data[(i)*img_width+(j)]==0)
					{
						boundarypoint.push_back(Point2f(i,j));
						boundary.data[(i*img_width+j)*3]=255;
						boundary.data[(i*img_width+j)*3+1]=255;
						boundary.data[(i*img_width+j)*3+2]=255;		
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

						if(region.data[(i)*img_width+(j)]==255&&region.data[(i+m)*img_width+(j+n)]==0)				
						{
							boundarypoint.push_back(Point2f(i,j));
							boundary.data[(i*img_width+j)*3]=255;
							boundary.data[(i*img_width+j)*3+1]=255;
							boundary.data[(i*img_width+j)*3+2]=255;
							//linemask.data[(i*img_width+j)]=255;
						}			
					}

			}	
		}
		bitwise_not(boundary,boundary);
		//imshow("region",region);
		//imshow("boundary",region);
	
		for(int i = 0 ; i < img_height;i++)
		{
			for (int j= 0; j < img_width; j++)
			{
				if(boundary.data[(i*img_width+j)*3]==0&&region.data[i*img_width+j]==255)
				{
					circle(test,Point(j,i),range_size/2,Scalar(255,255,255),-1);
				}						
			}	
		}	
		//imshow("test",test);
		//	waitKey();
		for(int i = 0;i<img_height;i++)
		{
			for (int j = 0 ; j< img_width ;j++)
			{
				if(test.data[(i*img_width+j)*3+2]==255&&region.data[(i*img_width+j)]==255)
				{
					float _ny;
					float _nx;
					float nor;
					Point3f nvec_id=findnearest(boundarypoint,flow_map,Point2i(i,j));
					if (nvec_id.z>=0)
					{
						nor = exp(-nvec_id.z*BoundaryRepelb)*BoundaryRepela;
						_ny=flow_map[(int)nvec_id.x*img_width+(int)nvec_id.y].x;
						_nx=-flow_map[(int)nvec_id.x*img_width+(int)nvec_id.y].y;
					}
					else if (nvec_id.z<0)
					{
						nor = exp(nvec_id.z*BoundaryRepelb)*BoundaryRepela;
						_ny=-flow_map[(int)nvec_id.x*img_width+(int)nvec_id.y].x;
						_nx=flow_map[(int)nvec_id.x*img_width+(int)nvec_id.y].y;
					}
					repel_map[i*img_width+j].x+=nor*_nx;
					repel_map[i*img_width+j].y+=nor*_ny;							
					
				}
			}
		}
		
		/////set first line///////
		int min_order=1;
		int max_order=0;
		cvtColor(boundary,boundary,CV_BGR2GRAY);
		Canny(region,boundary,100, 300,3);
		bitwise_not(boundary,boundary);
		distanceTransform(boundary,boundary,CV_DIST_L2,3);
// 		cv::Mat t = boundary.clone();
// 		cv::Mat tt ;
// 		bitwise_not(segment_img,tt);		
// 		normalize(t,t,0,1,NORM_MINMAX);
// 		imshow("region",region);
// 		imshow("t.bmp",t);
// 		waitKey();
		test=segment_img.clone();
		int centerd=-1;
		Point2i center;
		for(int i=0;i<img_height;i++)
		{
			for(int j=0;j<img_width;j++)
			{
				float d=boundary.at<float>(i ,j);		
				if(region.data[i*img_width+j]==255&&d>=centerd)
				{
					centerd=d;
					center=Point2i(i,j);
				}
			}
		}			
		SeedQueue.push_back(center);
		SeedOrientation.push_back(true);
		cv::Mat lineregionmask =region.clone();
		cv::Mat linecirclemask =region.clone();
		Mat linecirclemaskrecord = region.clone();
		cv::Mat linedistancae(img_height,img_width,CV_8UC1,cv::Scalar(0));

		while(SeedQueue.size())
		{
			//tttt=false;
			bool region_check=false;
			cv::Mat local_range_pattern(5,5,CV_8UC1,cv::Scalar(0));
			cv::circle(local_range_pattern,cv::Point(2,2),2,Scalar(255),-1);
			vector<cv::Point2i> test_line;
			float min_d=FLT_MAX;
			int min_id=0;		
			bitwise_not(linemask,linedistancae);
			//imshow("linemask",linemask);
			distanceTransform(linedistancae,linedistancae,CV_DIST_L2,3);
			if (SeedQueue.size()>1)
			for (int i = 0; i < SeedQueue.size() ; i++)
			{
				FlowImagingLIC(SeedQueue[i],src_img,flow_map,repel_map,test_line,LOWPASS_FILTR_LENGTH,linecirclemaskrecord,range_size);
				float avg_d;
				for (int j = 0; j<test_line.size();j++)
				{
					float d =abs(linedistancae.at<float>(test_line[j].x ,test_line[j].y)-(range_size+string_space));
						
					avg_d+=1-exp(-pow(d,2)/(2));
				}
				
				avg_d/=test_line.size();
				if(i==0) 
				{
					min_d=avg_d;
					min_id=0;
				}
				else if (min_d>avg_d)
				{
					min_d=avg_d;
					min_id=i;
				}
				test_line.clear();
			}
			
			//tttt=true;
			if (!region_check)
			{				
				//imshow("region",region);
				int avg_color = FlowImagingLIC(SeedQueue[min_id],src_img,flow_map,repel_map,trace_line,LOWPASS_FILTR_LENGTH,linecirclemaskrecord,range_size);
				//waitKey();
				float avg_d=0;
				for (int i = 0; i<trace_line.size();i++)
				{
					avg_d+=boundary.at<float>(trace_line[i].x ,trace_line[i].y);
				}
				avg_d/=trace_line.size();
				if(trace_line.size()>5&&avg_d>1.5)
				{
					LineData* data=new LineData;
					data->id=_count;
					data->region=r;
					if (SeedOrientation[min_id])
					{
						min_order--;
						data->order=min_order;
					}
					else
					{
						max_order++;
						data->order=max_order;
					}
					data->avg_color=avg_color;
					data->_len=trace_line.size();
					data->be_chosen=0;					
					
					_count++;
					test=Mat(img_height,img_width,CV_8UC3,cv::Scalar(0,0,0));
					int seed_count= 0 ;
					
					for(int lines=0;lines<(int)trace_line.size();lines++)
					{
						int x_p=(int)trace_line[lines].x;
						int y_p=(int)trace_line[lines].y;							
						int _idx=x_p*img_width+y_p;
						x1=x_p;y1=y_p;x2=x_p;y2=y_p;
						circle(test,Point(y_p,x_p),range_size+range_size/2,Scalar(255,255,255),-1);
						if (range_size-1<1)
							circle(lineregionmask,Point(y_p,x_p),1,Scalar(0),-1);
						else
							circle(lineregionmask,Point(y_p,x_p),range_size-1,Scalar(0),-1);
						if (range_size-3<1)
							circle(linecirclemask,Point(y_p,x_p),0,Scalar(0),-1);
						else
							circle(linecirclemask,Point(y_p,x_p),range_size-3,Scalar(0),-1);

						//if (range_size-4<1)
							circle(linecirclemaskrecord,Point(y_p,x_p),0,Scalar(0),-1);
						//else
						//	circle(linecirclemaskrecord,Point(y_p,x_p),range_size-4,Scalar(0),-1);
						data->flow.push_back(flow_map[_idx]);
						if (seed_count==trace_line.size()/10)
						{
							seed_count=0;
							normaly=-float(flow_map[( _idx )].x);
							normalx=float(flow_map[( _idx )].y);
							x1+=normalx*(range_size+string_space);
							y1+=normaly*(range_size+string_space);
							x2-=normalx*(range_size+string_space);
							y2-=normaly*(range_size+string_space);
							int _id1=(int)x1*img_width+(int)y1;
							int _id2=(int)x2*img_width+(int)y2;
							if (x1>=0&&x1<img_height&&y1>=0&&y1<img_width&&region.data[_id1]==255){								
								SeedQueue.push_back(cv::Point2f(x1,y1));
								SeedOrientation.push_back(false);
							}
							if (x2>=0&&x2<img_height&&y2>=0&&y2<img_width&&region.data[_id2]==255){								
								SeedQueue.push_back(cv::Point2f(x2,y2));
								SeedOrientation.push_back(true);
							}
						}

						lineout.data[_idx*3+1]=255;
						lineout.data[((int)SeedQueue[min_id].x*img_width+(int)SeedQueue[min_id].y)*3+2]=255;
						lineout.data[((int)SeedQueue[min_id].x*img_width+(int)SeedQueue[min_id].y)*3+1]=0;
						linemask.data[_idx]=255;
						seed_count++;
					}
					//repel flow map
					for(int lines=0;lines<(int)trace_line.size();lines++)
					{

						int x_p=(int)trace_line[lines].x;
						int y_p=(int)trace_line[lines].y;
						int _idx=x_p*img_width+y_p;
						test.data[(_idx)*3]=0;
						test.data[(_idx)*3+1]=0;
						test.data[(_idx)*3+2]=0;
					}						
					
					for(int i = 0;i<img_height;i++)
					{
						for (int j = 0 ; j< img_width ;j++)
						{
							if(test.data[(i*img_width+j)*3+2]==255&&region.data[(i*img_width+j)]==255)
							{
								float _ny;
								float _nx;
								float nor;
								Point3f nvec_id=findnearest(trace_line,flow_map,Point2i(i,j));
								if (nvec_id.z>0)
								{
									nor = exp(-nvec_id.z*LineRepelb)*LineRepela;
									_ny=flow_map[(int)nvec_id.x*img_width+(int)nvec_id.y].x;
									_nx=-flow_map[(int)nvec_id.x*img_width+(int)nvec_id.y].y;
								}
								else if (nvec_id.z<0)
								{
									nor = exp(nvec_id.z*LineRepelb)*LineRepela;
									_ny=-flow_map[(int)nvec_id.x*img_width+(int)nvec_id.y].x;
									_nx=+flow_map[(int)nvec_id.x*img_width+(int)nvec_id.y].y;
								}
								//cout<<flow_map[i*img_width+j].x<<" "<<flow_map[i*img_width+j].y<<endl;
								repel_map[i*img_width+j].x+=nor*_nx;
								repel_map[i*img_width+j].y+=nor*_ny;							
								//cout<<nor<<" "<<_nx<<" "<<_ny<<" "<<flow[i*img_width+j].x<<" "<<repel_map[i*img_width+j].y<<endl;
							}
						}
					}
 					//imshow("lineregionmask",lineregionmask);
 					//imshow("linecirclemask",linecirclemask);
 					//imshow("lineout",lineout);
// 					cout<<data->order<<endl;
 					//waitKey(1);
					lines_info.push_back(*data);
					output_lines.push_back(trace_line);
					//delete data;
				}

				trace_line.clear();
			}
			SeedQueue.erase(SeedQueue.begin()+min_id);
			SeedOrientation.erase(SeedOrientation.begin()+min_id);
			checkseedcover(SeedQueue,SeedOrientation,lineregionmask);
		}
		for (int i = 0 ; i <lines_info.size();i++)
		{
			lines_info[i].order+=-min_order;
		}
		//imwrite("lineout.bmp",lineout);
		line_trace_debug=false;
		SeedQueue.clear();
	}

	return true;
}
int AppAlgoStreamlineTrace::FlowImagingLIC(cv::Point2f start_posi, cv::Mat& src_img, vector<cv::Point2f>& flow_map,vector<cv::Point2f>& repel_map ,vector<cv::Point2i>& line, float krnlen, cv::Mat break_area_img,int range_size)
{
	int	vec_id;						///ID in the VECtor buffer (for the input flow field)
	int	advDir;						///ADVection DIRection (0: positive;  1: negative)
	int	advcts;						///number of ADVeCTion stepS per direction (a step counter)
	int	ADVCTS = krnlen;				///MAXIMUM number of advection steps per direction to break dead loops

	float	vctr_x;						///x-component  of the VeCToR at the forefront point
	float	vctr_y;						///y-component  of the VeCToR at the forefront point
	float	clp0_x;						///x-coordinate of CLiP point 0 (current)
	float	clp0_y;						///y-coordinate of CLiP point 0	(current)
	float	clp1_x;						///x-coordinate of CLiP point 1 (next   )
	float	clp1_y;						///y-coordinate of CLiP point 1 (next   )
	float	tmpLen;						///TeMPorary LENgth of a trial clipped-segment
	float	segLen;						///SEGment   LENgth
	float	curLen;						///CURrent   LENgth of the streamline
	float	prvLen;						///PReVious  LENgth of the streamline

	int line_range_avg_color=0;
	int line_range_points=0;
	int n_points=0;


	vector<cv::Point2i> linerecord;
	cv::Mat range_record_flag(img_width,img_height,CV_8UC3,Scalar(0,0,0));
	//cout<<start_posi.x<<" "<<start_posi.y<<endl;
	cv::Mat local_range_pattern(range_size*3/2,range_size*3/2,CV_8UC1,cv::Scalar(0));
	cv::circle(local_range_pattern,cv::Point(range_size*3/4,range_size*3/4),range_size*3/4,Scalar(255),-1);
	//imshow("local_range_pattern",local_range_pattern);
	//	system("pause");
	line.push_back(cv::Point2i(int(start_posi.x),int(start_posi.y)));
	for(advDir = 0;  advDir < 2;  advDir ++)
	{
		int range_across=0;
		int across_time=0;
		//		writeText("log.txt","advDir... ..",advDir);
		///init the step counter, curve-length measurer, and streamline seed///
		advcts = 0;
		curLen = 0.0f;
		clp0_x = int(start_posi.x)/* + 0.5f*/;
		clp0_y = int(start_posi.y)/* + 0.5f*/;
		std::vector<cv::Point2f> last_vector;
		last_vector.resize(2,cv::Point2f(-1,-1));

		if(( int(clp0_x) * img_width + int(clp0_y))>=flow_map.size())
			break;
		last_vector[0].x=float(flow_map[( int(clp0_x) * img_width + int(clp0_y) )].x);
		last_vector[0].y=float(flow_map[( int(clp0_x) * img_width + int(clp0_y) )].y);
		if(advDir==1)
		{
			last_vector[0].x=last_vector[0].x*(-1);
			last_vector[0].y=last_vector[0].y*(-1);
		}
		last_vector[0].x+=repel_map[( int(clp0_x) * img_width + int(clp0_y) )].x;
		last_vector[0].y+=repel_map[( int(clp0_x) * img_width + int(clp0_y) )].y;
		if (first_trace_done)
		{
			flow_map[( int(clp0_x) * img_width + int(clp0_y) )].x+=repel_map[( int(clp0_x) * img_width + int(clp0_y) )].x;
			flow_map[( int(clp0_x) * img_width + int(clp0_y) )].y+=repel_map[( int(clp0_x) * img_width + int(clp0_y) )].y;
		}

		while( curLen < krnlen && advcts < ADVCTS )
		{
			///access the vector at the sample///
			vec_id = ( int(clp0_x) * img_width + int(clp0_y) );
			if( vec_id>=flow_map.size())
			{
				if(line_trace_debug)
				{
					cout<<"id "<<line_trace_debug_id<<endl;
					cout<<"1"<<endl;
				}
				break;
			}
			vctr_x = float(flow_map[vec_id].x);//pVectr[vec_id    ];
			vctr_y = float(flow_map[vec_id].y);//pVectr[vec_id + 1];

			if (_isnan(vctr_x) || !_finite(vctr_x) || _isnan(vctr_y) || !_finite(vctr_y))
			{
				if(line_trace_debug)
				{
					cout<<"id "<<line_trace_debug_id<<endl;
					cout<<"2"<<endl;
				}
				break;
			}
			///in case of a critical point///
			if( vctr_x == 0.0f && vctr_y == 0.0f )
			{
				if(line_trace_debug)
				{
					cout<<"id "<<line_trace_debug_id<<endl;
					cout<<"3"<<endl;
				}
				break;
			}
			///negate the vector for the backward-advection case///
			///negate the vector for the backward-advection case///
			vctr_x = (advDir == 0) ? vctr_x : -vctr_x;
			vctr_y = (advDir == 0) ? vctr_y : -vctr_y;

			//cout<<"1 "<<vctr_x<<" "<<vctr_y<<endl;
			vctr_x+=repel_map[( int(clp0_x) * img_width + int(clp0_y) )].x;
			vctr_y+=repel_map[( int(clp0_x) * img_width + int(clp0_y) )].y;
			if (first_trace_done)
			{
				flow_map[( int(clp0_x) * img_width + int(clp0_y) )].x+=repel_map[( int(clp0_x) * img_width + int(clp0_y) )].x;
				flow_map[( int(clp0_x) * img_width + int(clp0_y) )].y+=repel_map[( int(clp0_x) * img_width + int(clp0_y) )].y;
			}
			if (_isnan(vctr_x) || !_finite(vctr_x) || _isnan(vctr_y) || !_finite(vctr_y))
			{
				if(line_trace_debug)
				{
					cout<<"id "<<line_trace_debug_id<<endl;
					cout<<"2-2"<<endl;
				}
				break;
			}
			///clip the segment against the pixel boundaries --- find the shorter from the two clipped segments///
			///replace  all  if-statements  whenever  possible  as  they  might  affect the computational speed///
			segLen = LINE_SQUARE_CLIP_MAX;
			segLen = (vctr_x < -VECTOR_COMPONENT_MIN) ? ( int(     clp0_x         ) - clp0_x ) / vctr_x : segLen;
			segLen = (vctr_x >  VECTOR_COMPONENT_MIN) ? ( int( int(clp0_x) + 1.5f ) - clp0_x ) / vctr_x : segLen;
			segLen = (vctr_y < -VECTOR_COMPONENT_MIN) ?
				(      (    (  tmpLen = ( int(     clp0_y)          - clp0_y ) / vctr_y  )  <  segLen    ) ? tmpLen : segLen      )
				: segLen;
			segLen = (vctr_y >  VECTOR_COMPONENT_MIN) ?
				(      (    (  tmpLen = ( int( int(clp0_y) + 1.5f ) - clp0_y ) / vctr_y  )  <  segLen    ) ? tmpLen : segLen      )
				: segLen;

			///update the curve-length measurers///
			prvLen = curLen;
			curLen+= segLen;
			segLen+= 0.00041f;

			///check if the filter has reached either end///
			segLen = (curLen > krnlen) ? ( (curLen = krnlen) - prvLen ) : segLen;

			///obtain the next clip point///
			clp1_x = clp0_x + vctr_x * segLen;
			clp1_y = clp0_y + vctr_y * segLen;

			///update the step counter and the "current" clip point///
			advcts ++;
			clp0_x = clp1_x;
			clp0_y = clp1_y;

			///check if the streamline has gone beyond the flow field///
			if( clp0_x < 0.0f || clp0_x >= img_height || clp0_y < 0.0f || clp0_y >= img_width)  break;

			//check repeat point
			int _check_r=0;
			for(int i=0;i<line.size();i++)
			{
				if(int(clp0_x)==int(line[i].x) && int(clp0_y)==int(line[i].y))
				{
					//writeText("log.txt","check repeat point... ..",advDir);
					_check_r=1;
 					//cout<<"4"<<endl;
					break;
				}
			}
			if(_check_r==1)
				continue;
			//check Angle between vectors
			if(last_vector[0].x!=-1 && last_vector[0].y!=-1 && last_vector[1].x!=-1 && last_vector[1].y!=-1)
			{

				double angle = acos(last_vector[0].x*vctr_x + last_vector[0].y*vctr_y)*180/M_PI;
				if(angle>=30)
				{
					if(line_trace_debug)
					{
						cout<<"id "<<line_trace_debug_id<<endl;
						cout<<"5-1"<<endl;
					}
					break;
				}
				angle = acos(last_vector[1].x*vctr_x + last_vector[1].y*vctr_y)*180/M_PI;
				if(angle>=30)
				{
					if(line_trace_debug)
					{
						cout<<"id "<<line_trace_debug_id<<endl;
						cout<<"5-2"<<endl;
					}
					break;
				}
			}
			if(break_area_img.data[int(clp0_x)*img_width+int(clp0_y)]==0)
			{
				if(line_trace_debug)
				{
					cout<<"id "<<line_trace_debug_id<<endl;
					cout<<"6"<<endl;
				}
				break;
			}
			cv::Mat t1;
			//check across 
			if (linerecord.size()>range_size*2)
			{
				
				range_record_flag.data[(int(linerecord[linerecord.size()-range_size*2].x)*img_width+(int)(linerecord[linerecord.size()-range_size*2].y))*3+0]=0;
				range_record_flag.data[(int(linerecord[linerecord.size()-range_size*2].x)*img_width+(int)(linerecord[linerecord.size()-range_size*2].y))*3+1]=0;
				range_record_flag.data[(int(linerecord[linerecord.size()-range_size*2].x)*img_width+(int)(linerecord[linerecord.size()-range_size*2].y))*3+2]=255;
				t1=range_record_flag.clone();
				circle(t1,Point2i(int(clp0_y),(int)(clp0_x)),range_size*3/4,Scalar(0,255,0),-1);
				int across_count=0;
				for(int i=-range_size*3/4;i<range_size*3/4;i++)
				{
					for(int j=-range_size*3/4;j<range_size*3/4;j++)
					{
						int x_p=(int)clp0_x+j;
						int y_p=(int)clp0_y+i;
						int _idx=x_p*img_width+y_p;
						if(x_p<0 || x_p>=img_height || y_p<0 || y_p>=img_width)
							continue;
						if(local_range_pattern.data[(i+range_size*3/4)*local_range_pattern.cols+(j+range_size*3/4)]!=255)
							continue;
						if(range_record_flag.data[_idx*3+2] == 255)
						{
							t1.data[_idx*3+1]=255;
							across_count++;
							if (across_count>0)
							{
								range_across=1;
							}

						}
					}
				}
				
			}
			//imshow("ra",range_record_flag);
			//cout<<"across self"<<endl;
			//waitKey();
			
			if (range_across==1)
			{
				//imshow("ra",t1);
				//cout<<"across self"<<endl;
				//waitKey();
				break;
			}
			last_vector[1]=last_vector[0];
			last_vector[0].x=vctr_x;
			last_vector[0].y=vctr_y;
			if (!_isnan(clp0_x)&&_finite(clp0_x)&&!isnan(clp0_y)&&_finite(clp0_y))
			{
				if(advDir==0)
				{
					line.push_back(cv::Point2i(int(clp0_x),int(clp0_y)));
					linerecord.push_back(cv::Point2i(int(clp0_x),int(clp0_y)));
				}
				else
				{
					line.insert(line.begin(), cv::Point2i(int(clp0_x),int(clp0_y)));
					linerecord.push_back( cv::Point2i(int(clp0_x),int(clp0_y)));
				}
			}
			n_points++;
		}
		// 		cout<<n_points<<endl;
		// 		system("pause");
		//		writeText("log.txt","while end... ..",line.size());
		std::vector<cv::Point2f>().swap(last_vector);
		reverse(linerecord.begin(),linerecord.end());
		range_record_flag=Mat(img_width,img_height,CV_8UC3,Scalar(0,0,0));
		if (linerecord.size()>range_size*2)
		for (int i = 0 ; i<linerecord.size()-range_size*2;i++)
		{
			range_record_flag.data[(int(linerecord[i].x)*img_width+(int)(linerecord[i].y))*3+0]=0;
			range_record_flag.data[(int(linerecord[i].x)*img_width+(int)(linerecord[i].y))*3+1]=0;
			range_record_flag.data[(int(linerecord[i].x)*img_width+(int)(linerecord[i].y))*3+2]=255;
		}
	}

	local_range_pattern.release();
	range_record_flag.release();
	linerecord.clear();
	if (line_trace_debug)
	{
		line_trace_debug_id++;
	}
	

	return line_range_avg_color;
}	
void AppAlgoStreamlineTrace::updatelines(vector<vector<cv::Point2i>>& lines,vector<LineData>& lines_info)
{
	cv::Mat testmat(img_height, img_width, CV_8UC1, cv::Scalar(0));
	vector<LineData> lines_info_temp;
	vector<vector<cv::Point2i>> lines_temp;
	int _count=0;
	//cout<<lines.size()<<endl;
	for (int i=0;i<lines_info.size();i++)
	{
		int id = lines_info[i].id;
		//cout<<id<<endl;
		if(lines_info[i].be_chosen!=1)
		{
			lines_info[i].be_chosen=0;			
			for (int j=0;j<lines[id].size();j++)
			{
				testmat.data[lines[id][j].x*img_width+lines[id][j].y]=255;
			}

// 			lines_info_temp.push_back(lines_info[i]);
// 			lines_temp.push_back(lines[id]);
			_count++;
		}
	}
	//imshow("remain line",testmat);
	//waitKey(0);
// 	lines.clear();
// 	lines_info.clear();
// 	lines_info.swap(lines_info_temp);
// 	lines.swap(lines_temp);
}
float AppAlgoStreamlineTrace::ChooseGoodLinesR(vector<vector<cv::Point2i>>& line, vector<LineData>& lines_info, cv::Mat& lines_range_mask,cv::Mat& edge_map ,QRWordArt::QRStringLines& Edgesplines,QRWordArt::QRStringLines& splines, vector<ChosenInfo>& chosen_infos,int range_size)
{
	//int range_size[3]={11,7,5};
	//return number of lines
	QRWordArt::QRSplineFBO splineFBO;	
	
	float choose_Ratio_count=0;
	cv::Mat initial_mask=lines_range_mask.clone();
	for(int i=0;i<line.size();i++)
	{			
		splineFBO.Initialize(img_width,img_height);
		for (int s = 0 ; s<splines.size();s++)
		{
			splineFBO.Push(splines[s]);			
		}
		splineFBO.Draw(&lines_range_mask);
		cv::flip(lines_range_mask,lines_range_mask,0);
		bitwise_not(lines_range_mask,lines_range_mask);
		splineFBO.Clear();
		float coverratio=0;
		float region=0;

		if(lines_info[i].be_chosen==1)
		{	
			continue;
		}
		else if(lines_info[i].be_chosen==-1)
		{	
			continue;
		}
		
		cv::Mat word_line_mask=lines_range_mask.clone();
		if(!checkAcrossLine(line[i],lines_info[i],lines_range_mask,edge_map,Edgesplines,chosen_infos,range_size))
		{
			
			word_line_mask.release();
			//lines_info[_id].be_chosen=-1;
			continue;
		}
		lines_info[i].be_chosen=1;		
		chosen_infos.back().line_order=lines_info[i].order;
		chosen_infos.back().region=lines_info[i].region;
		word_line_mask.release();		
		for (int j = 0;j<chosen_infos.back().usize.size();j++)
		{
			chosen_infos.back().usize[j]=chosen_infos.back().usize[j]*40;					
		}
		BuildStringLines_Unifromsize(chosen_infos.back(),splines);	
		chosen_infos.back().lineid = splines.size()-1;
		
	}
	SortLineOrder(chosen_infos,splines);
	choose_Ratio_count=checkCoverRatio(initial_mask,lines_range_mask);
 	//cout<<"choose Ratio_count "<<choose_Ratio_count<<endl;
	
	return choose_Ratio_count;
}
bool AppAlgoStreamlineTrace::checkAcrossLine(std::vector<cv::Point2i>& line,LineData& line_info,cv::Mat& lines_range_mask,cv::Mat& edge_map,QRWordArt::QRStringLines& Edgesplines, vector<ChosenInfo>& chosen_infos,int range_size)
{
	ChosenInfo temp_chose_info;
	cv::Mat testmat;
	//cvtColor(lines_range_mask,testmat,CV_GRAY2BGR);	
	testmat=lines_range_mask.clone();
	if (lines_range_mask.channels()==3)
	{
		cvtColor(lines_range_mask,lines_range_mask,CV_BGR2GRAY);
	}
	else
	{
		cout<<endl;
		cout<<"no channel 3"<<endl;
	}
	for (int i = 0 ; i < testmat.rows;i++)
	{
		for (int j = 0 ; j < testmat.cols;j++)
		{
			if(testmat.at<Vec3b>(i,j)[0]==255||edge_map.at<uchar>(i,j)!=0)
			{
				testmat.at<Vec3b>(i,j)[0]=128;
				testmat.at<Vec3b>(i,j)[1]=128;
				testmat.at<Vec3b>(i,j)[2]=128;				
			}
		}
	}
	int startpoint=0;
	int endpoint=0;
	vector<cv::Point2i> longline;
	vector<float> longlinesize;
	vector<float> linesize;
	cv::Point2f edge_t;	
	bool reach_edge= false;
	cv::Mat local_range_pattern(range_size,range_size,CV_8UC1,cv::Scalar(0));
	cv::circle(local_range_pattern,cv::Point(range_size/2,range_size/2),range_size/2,Scalar(255),-1);
	//imshow("local_range_pattern",local_range_pattern);
	vector<vector<cv::Point2i>> chosen;
	vector<vector<float>> chusize;
	int across_time=0;
	int longest=0;
	//cout<<"range_size "<<range_size<<endl;
	
	
	for(int lines=0;lines<line.size();lines++)
	{
// 		imshow("linesrangemask",lines_range_mask);
// 		imshow("edge",edge_map);
		reach_edge= false;
		int across_count1=0;
		for(int i=-range_size/2;i<range_size/2;i++)
		{
			for(int j=-range_size/2;j<range_size/2;j++)
			{
				int x_p=(int)line[lines].x+i;
				int y_p=(int)line[lines].y+j;
				int _idx=x_p*img_width+y_p;
				if(x_p<0 || x_p>=img_height || y_p<0 || y_p>=img_width)
					continue;
				if(local_range_pattern.at<uchar>((i+range_size/2),(j+range_size/2))==255 &&  lines_range_mask.at<uchar>(x_p,y_p)!=0)
				{
					across_count1++;
				}
				if(edge_map.at<uchar>(x_p,y_p)!=0&&traverse_tangent(Edgesplines[line_info.region],Point2f(y_p,x_p),edge_t,range_size))
				{
					across_count1++;
					double angle = acos(line_info.flow[lines].x*edge_t.y + line_info.flow[lines].y*edge_t.x)*180/M_PI;
					double dist = abs(x_p-line[lines].x)*abs(x_p-line[lines].x)+abs(y_p-line[lines].y)*abs(y_p-line[lines].y);
					dist=sqrt(dist);
					if (abs(angle-90)<50)
					{
						across_count1--;
					}
				}
			}
		}

		if(true)//(across_count1<=0&&!reach_edge)
		{
			circle(testmat,Point(line[lines].y,line[lines].x),range_size/2,Scalar(0,255,0),-1);
			endpoint=lines;
			across_time=0;
			linesize.push_back(range_size);
		}		
		else if (across_count1>0)
		{
			bool sizepass=false;
			float s;
					
			for ( s=range_size-1;s>0&&!reach_edge;s--)
			{				
				cv::Mat sizecheck(s,s,CV_8UC1,cv::Scalar(0));
				cv::circle(sizecheck,cv::Point(s/2,s/2),s/2,Scalar(255),-1);
				//imshow("sizecheck",sizecheck);
				//waitKey();
				int across_count2=0;
				int smin=-s/2;
				int smax=(int)s%2==0?s/2:s/2+1;
				for(int i=smin;i<smax;i++)
				{
					for(int j=smin;j<smax;j++)
					{
						int x_p=(int)line[lines].x+i;
						int y_p=(int)line[lines].y+j;
						int _idx=x_p*img_width+y_p;
						if(x_p<0 || x_p>=img_height || y_p<0 || y_p>=img_width)
							continue;
						if(sizecheck.at<uchar>((i+s/2),(j+s/2))==255 &&  (lines_range_mask.at<uchar>(x_p,y_p)!=0 ||edge_map.at<uchar>(x_p,y_p)!=0))
						{
							across_count2++;
						}
					}
				}
				if (across_count2<=0)
				{
					sizepass=true;
					break;
				}
			}			
			if(sizepass)
			{	
				linesize.push_back(s);
				endpoint=lines;
				across_time=0;
				circle(testmat,Point(line[lines].y,line[lines].x),s/2,Scalar(255,255,0),-1);
			}			
			else
			{
				linesize.push_back(0);
				testmat.at<Vec3b>(line[lines].x,line[lines].y)[2]=255;
				
				if(1)
				{
						endpoint=endpoint-1;	
						if(endpoint-startpoint>longest)
						{
							longline.clear();
							longlinesize.clear();
							longest=endpoint-startpoint;
							longline.insert(longline.begin(),line.begin()+startpoint,line.begin()+endpoint);
							longlinesize.insert(longlinesize.begin(),linesize.begin()+startpoint,linesize.begin()+endpoint);
						}
					
					endpoint=lines+1;
					startpoint=lines+1;
				}
			}			
		}
//     		imshow("testmat",testmat);
// 			waitKey(1);

	}

	if(endpoint-startpoint>longest)
	{
		longline.clear();
		longlinesize.clear();
		longest=endpoint-startpoint;
		longline.insert(longline.begin(),line.begin()+startpoint,line.begin()+endpoint);
		longlinesize.insert(longlinesize.begin(),linesize.begin()+startpoint,linesize.begin()+endpoint);
	}
	if (longline.size()>line.size()/4)
	{
		
		chosen.push_back(longline);
		chusize.push_back(longlinesize);
		longline.clear();
		longlinesize.clear();
	}
	else
	{
		longline.clear();
		longlinesize.clear();
		return false;
	}
	if (chosen.size()!=0)
	{			
		temp_chose_info.chosenlines.insert(temp_chose_info.chosenlines.end(),chosen[0].begin(),chosen[0].begin()+chosen[0].size());
		temp_chose_info.usize.insert(temp_chose_info.usize.end(),chusize[0].begin(),chusize[0].begin()+chusize[0].size());
		(chosen_infos).push_back(temp_chose_info);
	}	
	else
	{
		longline.clear();
		return false;
	}
	
	
//  	for(int i=0;i<chusize.size();i++)
//  	{
//  		smoothsize(chusize[i],0.1);
//  	}
// 	cout<<"chosen "<<chosen[0].size()<<endl;
// 	for(int i = 0; i <chosen[0].size();i++ )
// 	{
// 		cout<<chosen[0][i]<<" ";
// 	}
// 	cout<<endl;
// 	cout<<"chusize "<<chusize[0].size()<<endl;

//	cout<<endl;
// 	imshow("edgemap",edge_map);
// 	imshow("lines_range_mask",lines_range_mask);
//	waitKey(0);
	chosen.clear();
	longline.clear();
	local_range_pattern.release();
	return true;
}
void AppAlgoStreamlineTrace::smoothsize(vector<float> & linesize, double fit_rate)
{
	int start_point = 0;
	//cout<<linesize.size()<<endl;
 	for (int end_point=(int)(linesize.size()*fit_rate);end_point<linesize.size();end_point+=(int)(linesize.size()*fit_rate))
	{		
		//cout<<linesize[start_point]<<" "<<linesize[end_point]<<(int)(linesize.size()*fit_rate)<<endl;
		for ( int j=0;j<=(int)(linesize.size()*fit_rate);j++)
		{
			//cout<<"point "<<start_point+j<<" size "<<linesize[start_point]+(linesize[end_point]-linesize[start_point])*((float)j/(int)(linesize.size()*fit_rate))<<endl;;
			linesize[start_point+j]=linesize[start_point]+(linesize[end_point]-linesize[start_point])*((float)j/(int)(linesize.size()*fit_rate));
		}
		start_point=end_point;
		//waitKey(0);
 	}
	
	if (start_point!=(linesize.size()-1))
	{
		//cout<<linesize[start_point]<<" "<<linesize[linesize.size()-1]<<endl;
		for ( int j=0;j<=linesize.size()-start_point-1;j++)
		{
			//cout<<"point "<<start_point+j<<" size "<<linesize[start_point]+(linesize[linesize.size()-1]-linesize[start_point])*((float)j/(linesize.size()-start_point-1))<<endl;
			linesize[start_point+j]=linesize[start_point]+(linesize[linesize.size()-1]-linesize[start_point])*((float)j/(linesize.size()-start_point-1));
		}
	}
	//waitKey(0);
}
float AppAlgoStreamlineTrace::checkCoverRatio(cv::Mat& src1,cv::Mat& src2)
{
	float ori_count=0;
	float new_count=0;
	if (src1.channels()==1){cvtColor(src1,src1,CV_GRAY2BGR);}
	if (src2.channels()==1){cvtColor(src2,src2,CV_GRAY2BGR);}
	for (int i=0;i<src1.rows;i++)
	{
		for (int j=0;j<src1.cols;j++)
		{
			if (src1.data[(i*src1.cols+j)*3]==0){
				ori_count++;
				if (src2.data[(i*src2.cols+j)*3]==255){new_count++;}
			}
		}
	}

	return (new_count/ori_count)*100;
}
void AppFrame::AppAlgoStreamlineTrace::BuildStringLines_Unifromsize( ChosenInfo& chosen_infos, QRWordArt::QRStringLines& splines)
{
	QRWordArt::QRStringLine* spline = new QRWordArt::QRStringLine();
	for(int j=0;j<chosen_infos.chosenlines.size();++j)
	{	
		HSSSpline::PathPoint<5> p(chosen_infos.chosenlines[j].y,img_height-chosen_infos.chosenlines[j].x, //Vector
								  chosen_infos.usize[j]*0.02,chosen_infos.usize[j]*0.01,chosen_infos.usize[j]*0.01); //Size
		spline->PushBack(p);
	}
	spline->Fix()=false;
	spline->Region()=chosen_infos.region;
	spline->FittingCurve(0.1);
	//spline->RefittingCurve(0.1);

	if (splines.size()!=0)
	{
		splines.back()->NextLine(spline);
		spline->LastLine(splines.back());
	}
	splines.push_back(spline);
	
}