#include "StdAfx.h"
#include "AppAlgoTextWarping.h"
#include "QRWordArt/QRSplineFBO.h"
bool AppFrame::AppAlgoTextWarping::Execute( HKCAppItem^ _appItem )
{

	img_height=_appItem->Data->WordArtEvi.segment_img.rows;
	img_width=_appItem->Data->WordArtEvi.segment_img.cols;
	for (int r = 0;r<_appItem->Data->WordArtEvi.region_splines.size();r++)
	{
		AdjustSplines(_appItem->Data->WordArtEvi.region_splines[r].splines,_appItem->Data->WordArtEvi.region_segs[r]);
	}

	return true;
}

void AppFrame::AppAlgoTextWarping::AdjustSplines( QRWordArt::QRStringLines& splines,cv::Mat& segment_img)
{
	QRWordArt::QRSplineFBO	splineFBO;
	cv::Mat allmasks;
	cv::Mat seg;
	double offset=1;
	double adjustthreshold=0.5;
	double step =0.1;
	double preserve  = 0.5;
	if (segment_img.channels()==3)
	{
		seg=segment_img.clone();		
	}
	else
	{
		cvtColor(segment_img,seg,CV_GRAY2BGR);
	}
	bitwise_not(seg,seg);
	for (int i = 0 ; i <img_height;i++)
	{
		for(int j= 0 ; j <img_width; j++)
		{
			seg.data[(i*img_width+j)*3+1]=0;
		}
	}
	flip(seg,seg,0);
	splineFBO.Initialize(img_width,img_height);
	double threshold = 50;
	
	vector<bool> splines_fix;
	splines_fix.resize(splines.size(),false);
	std::vector<HSSSpline::PathPoints<5>> all_ctrl_scale;
	int erosion_size=1;		
	cv::Mat element = getStructuringElement( cv::MORPH_RECT,cv::Size( 2*erosion_size + 1, 2*erosion_size+1 ),cv::Point( erosion_size, erosion_size ) );
	for (int i=0;i<splines.size();i++)
	{
		allmasks=seg.clone();
		printf("Spline Width Adjectment... %d  %d \r",i,splines.size());
		cv::Mat line;
		drawallsplines(splines[i],line,img_width,img_height);

		for (int s = 0 ; s <splines.size();s++)
		{
			cv::Mat alllinemap;
			if (s==i)
			{
				continue;
			}
			splineFBO.Push(splines[s]);
			splineFBO.Draw(&alllinemap);
			bitwise_not(alllinemap,alllinemap);
			if (splines[s]->Fix()==true)
			{
				for (int x =0 ; x<img_height*img_width;x++)
				{
					alllinemap.data[x*3+2]=0;
				}
				//cv::erode( alllinemap, alllinemap, element );
			}
			bitwise_or(alllinemap,allmasks,allmasks);
			splineFBO.Clear();
		}
		//imshow("allmasks",allmasks);
		//cv::waitKey();
		cv::Mat edge(img_height,img_width,CV_8UC1,cv::Scalar(255));	
		int oricover=checkcoverneighbor(allmasks,line);
		line.release();
		HSSSpline::PathPoint<3> lastscale;
		//HSSSpline::Samples samples=splines[i]->UniformSampling(1);
		HSSSpline::Samples samples;
		samples.resize(splines[i]->GetCtrlPoints().size());

		//cout<<samples[i].size()<<endl;
		for (int j=0;j<samples.size();j++)
		{
			if (j == samples.size()-1)
			{
				samples[j].seg_idx=splines[i]->n_segs()-1;
				samples[j]._t=1;
			}
			else
			{
				samples[j].seg_idx=j;
				samples[j]._t=0;
			}
			//cout<<j<<" "<<samples.size()<<endl;
			HSSSpline::Vector2 point  = splines[i]->get_position(samples[j]);
			HSSSpline::Vector2 normal = splines[i]->get_normal(samples[j]);
			HSSSpline::Scale3 scale  = splines[i]->get_size(samples[j]);			
			HSSSpline::Scale3 oriscale=scale;
			vector<bool> targets_adjusted;
			vector<HSSSpline::Vector2> targetpoints;
			vector <HSSSpline::Scale3> target_scales;
			vector <double > target_dists;
			vector <bool > target_edges;
			cv::Mat testmat=allmasks.clone();
			for (int d= 0 ; d<2; d++)
			{
				bool adjusted=false;				
				bool   target_found = false;
				HSSSpline::Vector2 targetPoint;	
				bool targetedge=false;		
				double _dist;
				HSSSpline::Vector2 npoint=point;
				for (int t = 0 ; t< threshold; t++)
				{
					if (npoint[0]<0||npoint[1]<0||npoint[1]>=img_height||npoint[0]>=img_width)
					{
						break;
					}
					else if (allmasks.data[((int)npoint[1]*img_width+(int)npoint[0])*3]==255)
					{
						if (allmasks.data[((int)npoint[1]*img_width+(int)npoint[0])*3+1]==0)
						{
							if (d==0)
							{
								npoint[0]-=normal[0];
								npoint[1]-=normal[1];
							}
							else if (d==1)
							{
								npoint[0]+=normal[0];
								npoint[1]+=normal[1];
							}
						}
						cv::circle(testmat,cv::Point(point[0],point[1]),1,cv::Scalar(0,0,255),-1);
						//imshow("test",testmat);
						//cv::waitKey();
						double dx=npoint[0]-point[0];
						double dy=npoint[1]-point[1];
						_dist = std::sqrt(dx*dx+dy*dy);
						if(threshold>=_dist)
						{	
							targetPoint=npoint;
							if (allmasks.data[((int)npoint[1]*img_width+(int)npoint[0])*3+1]==0)
							{
								targetedge=true;
								adjusted=true;
							}
							else if (allmasks.data[((int)npoint[1]*img_width+(int)npoint[0])*3+2]==0)
							{
								targetedge=false;
								adjusted=true;
							}
							else
							{
								targetedge=false;
								adjusted=false;
							}										

							target_found=true;
						}
						break;
					}
					if (d==0)
					{
						npoint[0]+=normal[0];
						npoint[1]+=normal[1];
					}
					else if (d==1)
					{
						npoint[0]-=normal[0];
						npoint[1]-=normal[1];
					}

				}	  							
				if (target_found)
				{
					targetpoints.push_back(targetPoint);
					target_edges.push_back(targetedge);
					targets_adjusted.push_back(adjusted);
					//targets_adjusted.push_back(true);
					if(d==0) target_dists.push_back(_dist);
					else if (d==1) {target_dists.push_back(-_dist);}
				}

			}

			if (targetpoints.size()>0)
			{
				
				for (int t = 0; t<targetpoints.size(); t++)
				{
					int seg_record =j;
					HSSSpline::PathPoint<5> Ctrl1 = splines[i]->GetCtrlPoint(seg_record);
					HSSSpline::Scale3 Ctrl1size1 = HSSSpline::PathPoint<3> (Ctrl1[2],Ctrl1[3],Ctrl1[4]);					
					double move;
					//cout<<target_dists[t]<<endl;
					if (targets_adjusted[t]==true)
					{ 
						move=(abs(target_dists[t]))*40/50;
					}
					if(targets_adjusted[t]==false)
					{					
						if (target_dists[t]<0)
						{
							move=((abs(target_dists[t]))*40/50+scale[2])/2;
						}
						else
						{
							move=((abs(target_dists[t]))*40/50+scale[1])/2;
						}						
					}
					move-=preserve;
					//move/=1.2;
					if (target_dists[t]>0)
					{	
						//cout<<"up "<<move<<endl;
						if (scale[1]<move)
						{
							scale=HSSSpline::PathPoint<3>((move+scale[2]),move,scale[2]);
							/*if (scale[1]>lastscale[1]+adjustthreshold)
							{
								scale[1]=lastscale[1]+adjustthreshold;
								scale[0]=(scale[1]+scale[2]);
							}
							else if(j!=0&&lastscale[1]>scale[1]+adjustthreshold)
							{
								lastscale[1]=scale[1]+adjustthreshold;
								lastscale[0]=(lastscale[1]+lastscale[2]);
								splines[i]->EditSamplePointSize(samples[j-1],lastscale);
							}
							splines[i]->EditSamplePointSize(samples[j],scale);*/
							splines[i]->EditCtrlPointSize(j,scale);

						}
					}												  
					else if (target_dists[t]<0)
					{
						//cout<<"down "<<move<<endl;
						if (scale[2]<move)
						{
							//point=(targetpoints[t]+targetpoints[t])/2 ;
							scale=HSSSpline::PathPoint<3>((move+scale[1]),scale[1],move);	
							/*if (j!=0&&scale[2]>lastscale[2]+adjustthreshold)
							{
								scale[2]=lastscale[2]+adjustthreshold;
								scale[0]=(scale[1]+scale[2]);
							}
							else if(j!=0&&lastscale[2]>scale[2]+adjustthreshold)
							{
								lastscale[2]=scale[2]+adjustthreshold;
								lastscale[0]=(lastscale[1]+lastscale[2]);
								splines[i]->EditSamplePointSize(samples[j-1],lastscale);
							}
							splines[i]->EditSamplePointSize(samples[j],scale);*/
							splines[i]->EditCtrlPointSize(j,scale);

						}
					}	
					else
					{
						continue;
					}
					//cout<<j<<" "<<target_dists[t]<<endl;
					int ncover;
					//cout<<"ori "<<oriscale.ToString()<<endl;
					//cout<<"aft "<<scale.ToString()<<endl;
					
					int test=0;
					//cout<<" start "<<endl;
					bool touch=false;
					while (true)
					{
// 						if (target_dists[t]<0)
// 						{
// 							cout<<"down ";
// 						}
// 						else
// 						{
// 							cout<<"up ";
// 						}
// 						cout<<test++<<endl;
						drawallsplines(splines[i],line,img_width,img_height);
						ncover=checkcoverneighbor(allmasks,line);						
						if (ncover>oricover)
						{
							touch=true;
							line.release();
							if (target_dists[t]<0)
							{
								scale[2]-=step;
								if (scale[2]<oriscale[2])
								{	
									splines[i]->EditCtrlPointSize(j,Ctrl1size1);
									break;
								}
							}
							else if (target_dists[t]>0)
							{
								scale[1]-=step;
								if (scale[1]<oriscale[1])
								{
									splines[i]->EditCtrlPointSize(j,Ctrl1size1);
									break;
								}
							}
							//cout<<target_dists[t]<<" "<<j<<endl;
								
						}
						else
						{
							line.release();
							if(touch)
							{
								if (target_dists[t]<0)
								{
									scale[2]-=preserve;
								}
								else if (target_dists[t]>0)
								{
									scale[1]-=preserve;
								}
								scale[0]=(scale[1]+scale[2]);
								splines[i]->EditCtrlPointSize(j,scale);
							}
							//cout<<"out range"<<endl;
							break;
						}
						scale[0]=(scale[1]+scale[2]);
						//splines[i]->EditSamplePointSize(samples[j],scale);
						splines[i]->EditCtrlPointSize(j,scale);
					}
					oricover=ncover;
					lastscale=scale;
				}	
				//cout<<" end "<<endl;
			}

		}
		splines[i]->Fix()=true;
		
	}
}

void AppFrame::AppAlgoTextWarping::drawallsplines( QRWordArt::QRStringLine* spline, cv::Mat& mask,int img_width,int img_height )
{
	QRWordArt::QRSplineFBO splineFBO;
	splineFBO.Initialize(img_width,img_height);	

	splineFBO.Push(spline);
	splineFBO.Draw(&mask);
	splineFBO.Clear();
}

int AppFrame::AppAlgoTextWarping::checkcoverneighbor( cv::Mat allmasks,cv::Mat mask )
{
	cv::Mat check;
	cv::Mat neightbor;
	cvtColor(allmasks,allmasks,CV_BGR2GRAY);
	cvtColor(mask,mask,CV_BGR2GRAY);
	threshold(allmasks,allmasks,0,255,cv::THRESH_BINARY);
	threshold(mask,mask,0,255,cv::THRESH_BINARY);
	//bitwise_not(allmasks,neightbor);
	bitwise_not(mask,mask);
	bitwise_and(mask,allmasks,check);
	int n =countNonZero(check);
// 	 imshow("1234",check);
// 		imshow("mask",mask);
// 	 	imshow("allmasks",allmasks);
// 		cv::waitKey(0);
	return n;
}

