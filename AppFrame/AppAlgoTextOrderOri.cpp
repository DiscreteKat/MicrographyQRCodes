#include "StdAfx.h"
#include "AppAlgoTextOrderOri.h"
using namespace cv;
bool AppAlgoTextOrderOri::Execute(HKCAppItem^ _appItem)
{
	QRWordArt::QRStringLines& splines = _appItem->Data->WordArtData[0].splines;
	QRWordArt::QRStringLines NewSplines;
	Mat& seg = _appItem->Data->WordArtEvi.segment_img;
	img_height=_appItem->Data->WordArtEvi.segment_img.rows;
	img_width=_appItem->Data->WordArtEvi.segment_img.cols;
	if(splines.empty())
		return false;
	Mat line(img_height,img_width,CV_8UC3,Scalar(0));
	for (int i = 0 ; i <splines.size() ; i ++)
	{
		HSSSpline::PathPoints<5> points =splines[i]->GetUniformSamplePoints(1);
		for (int j = 0 ; j <points().size() ; j ++)
		{
			line.data[((int)points[j][1]*img_width+(int)points[j][0])*3+2]=255*(splines.size()-i)/splines.size();
		}

		/*if (i!=0)
		{
			cv::line(line,Point(splines[i]->get_midpoint()[0],splines[i]->get_midpoint()[1]),Point(splines[i-1]->get_midpoint()[0],splines[i-1]->get_midpoint()[1]),Scalar(0,255,0));
		}*/
	}	
	
	LineGraphs graph =getneighbor(splines,seg);
	LineGraphs newgraph = BottomUpCheck(graph);
	//cout<<newgraph.size()<<endl;
	for (int i = 0 ; i<newgraph.size() ; i++ )
	{
		/*for (int j = 0 ; j <graph[i].upid.size();j++)
		{
			cv::line(line,Point(splines[i]->get_midpoint()[0],splines[i]->get_midpoint()[1]),Point(splines[graph[i].upid[j]]->get_midpoint()[0],splines[graph[i].upid[j]]->get_midpoint()[1]),Scalar(0,255,0));
		}
		for (int j = 0 ; j <graph[i].downid.size();j++)
		{
			cv::line(line,Point(splines[i]->get_midpoint()[0],splines[i]->get_midpoint()[1]),Point(splines[graph[i].downid[j]]->get_midpoint()[0],splines[graph[i].downid[j]]->get_midpoint()[1]),Scalar(255,255,0));
		}*/
		if (i!=0)
		{
			cv::line(line,Point(splines[newgraph[i].id]->get_midpoint()[0],splines[newgraph[i].id]->get_midpoint()[1]),Point(splines[newgraph[i-1].id]->get_midpoint()[0],splines[newgraph[i-1].id]->get_midpoint()[1]),Scalar(0,255,0));
		}
		NewSplines.push_back(splines[newgraph[i].id]);
		/*cout<<graph[i].id<<endl;
		flip(line,line,0);
		imshow("line",line);
		waitKey();
		flip(line,line,0);*/
	}
	splines= NewSplines;
	flip(line,line,0);
	//imshow("line",line);
	return true;
}
LineGraphs AppAlgoTextOrderOri::getneighbor(QRWordArt::QRStringLines& splines,Mat& segment)
{
	LineGraphs graph;
	graph.resize(splines.size());
	Mat seg_img;
	if (segment.channels()==3)
	{
		cvtColor(segment,seg_img,CV_BGR2GRAY);
	}
	else
		seg_img=segment.clone();
	threshold(seg_img,seg_img,1,255,CV_THRESH_BINARY);
	flip(seg_img,seg_img,0);
	for (int id = 0 ; id <splines.size(); id++)
	{
		//cout<<id<<endl;
		HSSSpline::Samples samples = splines[id]->UniformSampling(1);
		Mat line(img_height,img_width,CV_8UC3,Scalar(0));
		for (int i = 0 ; i <splines.size(); i++)
		{
			HSSSpline::PathPoints<5> points =splines[i]->GetUniformSamplePoints(1);
			for (int j = 0 ; j <points().size() ; j ++)
			{
				if (i==id)
				{
					line.at<Vec3b>((int)(points[j][1]),(int)(points[j][0]))[1]=255;
					line.at<Vec3b>((int)(points[j][1]),(int)(points[j][0]))[0]=255;
				}
				else
				{
					line.at<Vec3b>((int)(points[j][1]),(int)(points[j][0]))[2]=i;
					line.at<Vec3b>((int)(points[j][1]),(int)(points[j][0]))[0]=255;
				}
			}
		}
		Mat test;
		/*imshow("seg",seg_img);
		waitKey();*/
		for (int i = 0 ; i<samples.size(); i ++)
		{
			HSSSpline::Vector2 n=splines[id]->get_normal(samples[i]);
			HSSSpline::PathPoint<5> pathpoint=splines[id]->get_point(samples[i]);
			cv::Point2d Point = cv::Point2d(pathpoint[0],pathpoint[1]);
			cv::Point2d UpNormal = cv::Point2d(n[0],n[1]);
			cv::Point2d DownNormal = -UpNormal;
			cv::Point2d p=Point;
			//cout<<i<<endl;
			int count = 0 ; 
			while(1)
			{
				//cout<<count++<<endl;
				//cout<<UpNormal<<endl;
				p = p + UpNormal;	
				//cout<<p<<endl;
				//waitKey();
				int targetid;
				if (seg_img.data[(int)(p.y)*img_width+(int)(p.x)]!=0)
				{
					break;
				}
				else if (((targetid=line.at<Vec3b>((int)(p.y),(int)(p.x))[2])&&targetid!=0)||((targetid=line.at<Vec3b>((int)(p.y),(int)(p.x)+1)[2])&&targetid!=0))
				{
					bool repeat=false;
					for (int g = 0 ; g<graph[id].upid.size();g++)
					{
						repeat= graph[id].upid[g]==targetid?true:false;
						if(repeat)
							break;
					}
					if (!repeat)
					{
						graph[id].upid.push_back(targetid);
					}
					break;
				}
				
			}
			p=Point;
			while(1)
			{
				p = p + DownNormal;	
				int targetid;
				if (seg_img.data[(int)(p.y)*img_width+(int)(p.x)]!=0)
				{
					break;
				}
				else if (((targetid=line.at<Vec3b>((int)(p.y),(int)(p.x))[2])&&targetid!=0)||((targetid=line.at<Vec3b>((int)(p.y),(int)(p.x)+1)[2])&&targetid!=0))
				{
					bool repeat=false;
					for (int g = 0 ; g<graph[id].downid.size();g++)
					{
						repeat= graph[id].downid[g]==targetid?true:false;
						if(repeat)
							break;
					}
					if (!repeat)
					{
						graph[id].downid.push_back(targetid);
					}
					break;
				}
			}

		}
// 		cout<<id<<endl;
// 		cout<<"up "<<graph[id].upid<<endl;
// 		cout<<"down "<<graph[id].downid<<endl;
// 		flip(line,line,0);
// 		imshow("lline",line);
// 		
// 		waitKey();
		graph[id].id=id;
	}
	return graph;
}
bool AppAlgoTextOrderOri::PushVer(LineGraphs& graph,int id,LineGraphs& newgraph)
{
	
	if (graph[id].check)
	{
		//cout<<"id checked "<<id<<endl;
		return false;
	}
//	cout<<id<<endl;
	if (graph[id].upid.size()==0)
	{
		newgraph.push_back(graph[id]);
//		cout<<"no up "<<id<<endl;
		graph[id].check=true;
	}
	else
	{
		bool NoAllCheck =false;
		for (int i = 0 ; i<graph[id].upid.size(); i++)
		{
//			cout<<id<<" down to "<<graph[id].upid[i]<<endl;
			int upid = graph[id].upid[i];
			graph[id].upid.erase(graph[id].upid.begin()+i);			
			i--;
			NoAllCheck = PushVer(graph,upid,newgraph);
			
			if (NoAllCheck)
			{
				return true;
			}
		}
		if (!NoAllCheck)
		{
//			cout<<"up all check "<<id<<endl;
			newgraph.push_back(graph[id]);
			graph[id].check=true;
		}
		
		
	}	
	for (int i = 0 ; i<graph[id].downid.size(); i++)
	{
//		cout<<id<<" down to "<<graph[id].downid[i]<<endl;
		PushVer(graph,graph[id].downid[i],newgraph);
	}
	return true;
}
LineGraphs AppAlgoTextOrderOri::BottomUpCheck(LineGraphs& graph)
{
	LineGraphs newgraph;
	for (int i = 0 ; i <graph.size(); i++)
	{		
		if (!graph[i].check)
		{
//			cout<<"back "<<i<<endl;
			PushVer(graph,i,newgraph);
		}
		
	}
	
//	cout<<"end"<<endl;
	return newgraph;
}