#include "stdafx.h"
#include "AppProperty.h"
#include "AppParameter.h"
#include "AppItem.h"
#include "AppAlgorithm.h"
#include "AppAlgoProbabilityModule.h"
#include "AppAlgoTextBigScale.h"
#include "AppAlgoTextGeneration.h"
#include "AppAlgoEnergyTextSpace.h"
#include "AppAlgoTextTyping.h"
#include "AppAlgoTextAlign.h"
#include "AppAlgoTextColor.h"
#include "AppAlgoQRCodeSegmentation.h"
#include "AppAlgoEnergyVisual.h"
#include "QRWordArt/QRCharFBO.h"
#include "QRWordArt/QRStringLine.h"
#include "QRWordArt/QRSplineFBO.h"
#include "QRWordArt/QRCharacterIO.h"
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <time.h>

using namespace QRWordArt;
using namespace cv;

bool AppAlgoTextBigScale::candidate_sort(RegionCandidateData can1, RegionCandidateData can2)
{
	if(can1.Et < can2.Et)
		return true;
	else
		return false;
}
/*
bool AppAlgoTextBigScale::sort_island(YJFID id1, YJFID id2)
{
	if(id1.score < id2.score)
		return true;
	else
		return false;
}*/

HSSSpline::PathPoints<5> AppAlgoTextBigScale::getallpoint(QRWordArt::QRStringLine* spline,double step)
{
	HSSSpline::PathPoints<5> allpoint;
		
	for (int i=0;i<spline->GetCtrlPoints().size()-1;i++)
	{
		for (double k=0;k<1;k+=step)
		{
			allpoint().push_back(spline->get_point(i,k));
		}
	}
	//cout<<allpoint.size()<<endl;
	return allpoint;
}

HSSSpline::PathPoint<5> AppAlgoTextBigScale::findnearest(HSSSpline::PathPoints<5>& line,HSSSpline::PathPoint<5>trace_point,int id)
{
	cv::Mat testf = Mat(333,333,CV_8UC3,cv::Scalar(0,0,0));
	double minx;
	double miny;
	double minw;
	double minh1;
	double minh2;
	double _mind;
	testf.data[((int)trace_point[1]*333+(int)trace_point[0])*3+1]=255;
	for (int i = 0 ; i< line.size(); i++)
	{

		testf.data[((int)line[i][1]*333+(int)line[i][0])*3]=255;
		testf.data[((int)line[i][1]*333+(int)line[i][0])*3+1]=255;
 		testf.data[((int)line[i][1]*333+(int)line[i][0])*3+2]=255;
		double dx = trace_point[0]-line[i][0];
		double dy = trace_point[1]-line[i][1];
		double _dist = sqrt(dx*dx+dy*dy);
		//int p =(int)line[i][0]*img_width+(int)line[i][1];
		if(_mind>=_dist||i==0)
		{					
				id = i;
				minx= line[i][0];
				miny= line[i][1];
				minw= line[i][2];
				minh1= line[i][3];
				minh2= line[i][4];
				_mind=+_dist;				
		}
	}
	testf.data[((int)miny*333+(int)minx)*3+0]=0;
	testf.data[((int)miny*333+(int)minx)*3+1]=0;
	testf.data[((int)miny*333+(int)minx)*3+2]=255;
	//flip(testf,testf,0);
	//imshow("test",testf);
	//waitKey();
	//cout<<minx<<" "<<miny<<" "<<minw<<" "<<minh1<<" "<<minh2<<endl;
	return HSSSpline::PathPoint<5>(minx,miny,minw,minh1,minh2);
}

void AppAlgoTextBigScale::drawallsplines(QRStringLines& splines, cv::Mat& allmask,int bg_color,cv::Mat& foreground,cv::Mat& background)
{
	
	QRWordArt::QRCharacter::CharFBO charFBO;
	//charFBO.Initialize(img_width,img_height);	
	charFBO.Initialize(img_height,img_width);	
	int checkn=0;
	for (int i = 0 ; i < splines.size();i++)
	{
		for (int j = 0 ; j < splines[i]->GetQRSamples().size();j++)
		{
			if (splines[i]->GetQRSamples()[j]->qr_char!=NULL)
			{
				charFBO.Push(splines[i]->GetQRSamples()[j]->qr_char);
				checkn++;
			}
			
		}
	}

	cv::Mat alpha;
	charFBO.Draw(&alpha);
	cv::flip(alpha,alpha,0);

	charFBO.Enable(QRWordArt::QRCharacter::CharFBO::SOILD_COLOR);
	charFBO.SetBackground(bg_color/255.0);
	charFBO.Draw(&allmask);
	cv::flip(allmask,allmask,0);	

	for (int i=0; i<img_height; i++)
	{
		for (int j=0; j<img_width; j++)
		{
			int idx = i*img_width+j;
			if (alpha.data[idx*3]!=0)
			{
				allmask.data[idx*3  ] = bg_color*(1-background.data[idx*4+3]/255.0)+background.data[idx*4]*(background.data[idx*4+3]/255.0);
				allmask.data[idx*3+1] = bg_color*(1-background.data[idx*4+3]/255.0)+background.data[idx*4]*(background.data[idx*4+3]/255.0);
				allmask.data[idx*3+2] = bg_color*(1-background.data[idx*4+3]/255.0)+background.data[idx*4]*(background.data[idx*4+3]/255.0);
			}

			allmask.data[idx*3  ] = allmask.data[idx*3  ]*(1-foreground.data[idx*4+3]/255.0)+foreground.data[idx*4]*(foreground.data[idx*4+3]/255.0);
			allmask.data[idx*3+1] = allmask.data[idx*3+1]*(1-foreground.data[idx*4+3]/255.0)+foreground.data[idx*4]*(foreground.data[idx*4+3]/255.0);
			allmask.data[idx*3+2] = allmask.data[idx*3+2]*(1-foreground.data[idx*4+3]/255.0)+foreground.data[idx*4]*(foreground.data[idx*4+3]/255.0);
		}
	}

}
bool AppAlgoTextBigScale::Execute(HKCAppItem^ _appItem)
{	
	AppAlgoEnergyVisual visualenergy(_appItem);
	HKCMediaItem^ srcItem = _appItem->Find("Source");
	cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());
	img_height=srcImg->rows;
	img_width=srcImg->cols;
	edgeImg=new cv::Mat;
	*edgeImg=_appItem->Data->WordArtEvi.segment_img.clone();
	if (edgeImg->channels()!=1)
	{
		if (edgeImg->channels()==3)
		{
			cv::cvtColor(*edgeImg,*edgeImg,CV_BGR2GRAY);
		}
		else if (edgeImg->channels()==4)
		{
			cv::cvtColor(*edgeImg,*edgeImg,CV_BGRA2GRAY);
		}
	}
	for (int i = 0; i< 2;i++)
	{
		GenBigScale(_appItem,i);

		if (i==0)
		{
			_appItem->Data->WordArtData[0].splines.insert(_appItem->Data->WordArtData[0].splines.begin(),_appItem->Data->WordArtEdt.CanData.candidates[0].splines.begin(),_appItem->Data->WordArtEdt.CanData.candidates[0].splines.end());
		}
		
		//visualenergy.EvaluateLineSpace(_appItem->Data->CanData.candidates[i].splines,_appItem->Data->WordArtEvi.segment_img,_appItem->Data->WordArtEvi.adjustsamples);
		//visualenergy.EvaluateFittingEdge(_appItem->Data->CanData.candidates[i].splines,_appItem->Data->WordArtEvi.segment_img,_appItem->Data->WordArtEvi.vecEdgeLink);

		_appItem->Data->WordArtEdt.CanData.candidates[i].Ec=visualenergy.getEc();
		_appItem->Data->WordArtEdt.CanData.candidates[i].Es=visualenergy.getEss();
	}
	sort(_appItem->Data->WordArtEdt.CanData.candidates.begin(),_appItem->Data->WordArtEdt.CanData.candidates.end(),candidate_sort);
	//cout<<"123 "<<	_appItem->Data->WordArtEvi.scaling_splines.size()<<endl;

	///***
	delete edgeImg;
	delete delete_idx;
	delete delete_charsample;
	return true;
}
bool AppAlgoTextBigScale::GenUserBigScale(HKCAppItem^ _appItem,int line,int word)
{	
	AppAlgoEnergyVisual visualenergy(_appItem);
	HKCMediaItem^ srcItem = _appItem->Find("Source");
	cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());
	img_height=srcImg->rows;
	img_width=srcImg->cols;
	edgeImg=new cv::Mat;
	cv::Mat word_mask;
	*edgeImg=_appItem->Data->WordArtEvi.segment_img.clone();	
	vector<YJFID > id_picked;
	vector<int> line_word_order;
	if (edgeImg->channels()!=1)
	{
		if (edgeImg->channels()==3)
		{
			cv::cvtColor(*edgeImg,*edgeImg,CV_BGR2GRAY);
		}
		else if (edgeImg->channels()==4)
		{
			cv::cvtColor(*edgeImg,*edgeImg,CV_BGRA2GRAY);
		}
	}
	line_word_order.resize(_appItem->Data->WordArtEdt.CanData.user_candidate.splines.size()-_appItem->Data->WordArtEdt.CanData.user_candidate.scaling_number,-1);
	AppAlgoTextColor  text_color(_appItem);
	text_color.Enable((int)_appItem->Param->WordArt->ColorMode);
	vector<std::string>& candidate_strings = _appItem->Data->WordArtEvi.candidate_strings;
	AppFrame::AppAlgoTextBigScale::setori(_appItem->Data->WordArtEdt.CanData.user_candidate.splines.size()-_appItem->Data->WordArtEdt.CanData.user_candidate.scaling_number);
	AppFrame::AppAlgoTextBigScale::setflag(true,true);	
	vector<double> energy;
	energy.resize(3,100000);
	QRStringLines &orisplines = _appItem->Data->WordArtEdt.CanData.user_candidate.splines;
	/*RegionCandidateData can;
	for (int i = 0 ;i<_appItem->Data->WordArtEdt.CanData.user_candidate.splines.size();i++)
	{
		QRStringLine *orispline = _appItem->Data->WordArtEdt.CanData.user_candidate.splines[i];
		QRStringLine *spline=new QRStringLine;
		HSSSpline::Sample cursor(0,0);
		HSSSpline::Sample end(orispline->n_segs()-1,1);
		orispline->Duplicate(cursor,end,spline);
		spline->Region()=orispline->Region();
		for(int j  = 0 ; j <orispline->GetWords().size(); j++)
		{
			HSSSpline::Samples samples;
			if(spline->TypeSetting(orispline->GetWords()[j],&samples,cursor,end))
			{
				spline->AttachWord(orispline->GetWords()[j],samples);
				double offset = spline->Offset(orispline->GetWords()[j].back(),samples.back());
				spline->ShiftSampleForeward(samples.back(),offset,&cursor);
				offset = (QRWordArt::QRCharacter::WordSpacing + spline->WordSpace())*spline->get_w(cursor);
				spline->ShiftSampleForeward(cursor,offset,&cursor);
			}
		}
		//_appItem->Data->CanData.user_candidate.splines[i]->DuplicateWithChar(spline);

		if (i!=0)
		{
			can.splines.back()->NextLine(spline);
			spline->LastLine(can.splines.back());
		}
		can.splines.push_back(spline);
	}*/
	int t = 1;
	int WordId;
	AppFrame::AppAlgoTextBigScale::setidx(line,word,t);	
	if(BuildBigScale(orisplines,word_mask))
	{
		//text_color.Execute(*can.splines.back());
		YJFID id(line,word,t,word_mask);
		id_picked.push_back(id);

		for (int j= 0 ;j<id.endline-id.startline+1;j++)
		{				
			line_word_order[id.startline+j]=1;
		}
		/*can.scaling_number++;*/
		//cout<<can.splines[nspline+1]->GetWordSamples().size()<<endl;

		WordId = orisplines[nspline]->GetWordSamples()[nword][0]->WordId;
		orisplines.back()->GetQRSamples()[0]->WordId=WordId;
		orisplines.back()->GetQRSamples()[0]->_IsSentenceStart=orisplines[nspline]->GetWordSamples()[nword][0]->_IsSentenceStart;
		orisplines.back()->GetQRSamples()[0]->_IsSentenceEnd=orisplines[nspline]->GetWordSamples()[nword][0]->_IsSentenceEnd;
		ReTextGen(orisplines,_appItem,id_picked,line_word_order);
	}
	for (int i =newsplineId ; i <orisplines.size() ; i ++)
	{
		orisplines[i]->Release();
	}
	AppAlgoTextGeneration::Text_Record_Order  = WordId+1;
	cout<<WordId<<endl;
	AppAlgoTextGeneration^ algoObj_TextGeneration = gcnew AppAlgoTextGeneration;
	algoObj_TextGeneration->TypeSet(_appItem->Param->WordArt->TextType);
	algoObj_TextGeneration->TextGeneration( _appItem,orisplines,_appItem->Data->WordArtEvi.candidate_strings);

	return true;
}
bool AppAlgoTextBigScale::GenBigScale(HKCAppItem^ _appItem,int randcount)
{	
	AppAlgoTextColor	text_color(_appItem);
	text_color.Enable((int)_appItem->Param->WordArt->ColorMode);
	vector<std::string>& candidate_strings = _appItem->Data->WordArtEvi.candidate_strings;
	vector<vector<cv::Point>> wordarray;
	vector<cv::Point> wordrand;
	vector<int> word_picked;
	QRWordArt::QRStringLines& splines = _appItem->Data->WordArtData[0].splines;
	
	RegionCandidateData can;
	for (int i = 0 ;i<splines.size();i++)
	{
		QRStringLine *spline=new QRStringLine;
		HSSSpline::Sample cursor(0,0);
		HSSSpline::Sample end(splines[i]->n_segs()-1,1);
		splines[i]->Duplicate(cursor,end,spline);
		spline->Region()=splines[i]->Region();
		for(int j  = 0 ; j <splines[i]->GetWords().size(); j++)
		{
			HSSSpline::Samples samples;
			if(spline->TypeSetting(splines[i]->GetWords()[j],&samples,cursor,end))
			{
				spline->AttachWord(splines[i]->GetWords()[j],samples);
				double offset = spline->Offset(splines[i]->GetWords()[j].back(),samples.back());
				spline->ShiftSampleForeward(samples.back(),offset,&cursor);
				offset = (QRWordArt::QRCharacter::WordSpacing + spline->WordSpace())*spline->get_w(cursor);
				spline->ShiftSampleForeward(cursor,offset,&cursor);
			}
		}
		//splines[i]->DuplicateWithChar(spline);

		if (i!=0)
		{
			can.splines.back()->NextLine(spline);
			spline->LastLine(can.splines.back());
		}
		can.splines.push_back(spline);
	}
	AppFrame::AppAlgoTextBigScale::setori(can.splines.size());
	AppFrame::AppAlgoTextBigScale::setflag(true,true);	
	vector<int> line_word_order;
	line_word_order.resize(can.splines.size(),-1);
	delete_idx=new vector<cv::Point3i>;
	delete_charsample= new vector<QRWordArt::QRCharacter::Char*>;	
	AppAlgoProbabilityModule ModuleEnergy(_appItem);
	cv::Mat word_mask;
	cv::Mat allmask;
	vector<YJFID > id;
	vector<YJFID > id_picked;
	int pick_num=1;
	int n=0;
	vector<int> randomseed;
	for(int i = 0; i <2000;i++)
	{
		randomseed.push_back(rand());
	}
	randcount*=20;
	int orisplinesize=can.splines.size();
	sortwordarray(can.splines,candidate_strings,wordarray);
	
	drawallsplines(can.splines,allmask,_appItem->Data->WordArtEvi.background_color,_appItem->Data->WordArtEvi.qr_foreground_modules,_appItem->Data->WordArtEvi.qr_background_modules);
	double orie=ModuleEnergy.Execute_Modules_Avg(allmask,_appItem->Data->WordArtEvi.seg_pids);
	AppAlgoEnergyVisual visualenergy(_appItem);
	double orite=visualenergy.EvaluateTextEnergy(can.splines);
	cout<<"ori et "<<orite<<endl;;
	cout<<"ori eqr "<<orie<<endl;;
	while(n<pick_num)
	{
		for(int i = 0 ; i <candidate_strings.size();i++)
		{
			wordrand.push_back(cv::Point(randomseed[randcount++]%wordarray[i].size(),randomseed[randcount++]%3));
		}
		
		for(int i = 0 ; i <candidate_strings.size();i++)
		{		
			cv::Point id_rand=wordarray[i][wordrand[i].x];
			AppFrame::AppAlgoTextBigScale::setidx(id_rand.x,id_rand.y,wordrand[i].y);

			if(BuildBigScale(can.splines,word_mask))
			{			
				//text_color.AssignColor(*can.splines.back());
				//drawallsplines(can.splines,allmask,_appItem->Data->background_color,_appItem->Data->WordArtEvi.qr_foreground_modules,_appItem->Data->WordArtEvi.qr_background_modules);
				
				double diff=1;
				//  					id.push_back(ID(3,3,3,diff));
				//  					id.back().word_mask=word_mask.clone();
				if(diff>0)
				{						

					id.push_back(YJFID(id_rand.x,id_rand.y,wordrand[i].y));
					id.back().word_mask=word_mask.clone();
				}

// 				CONSOLE_SCREEN_BUFFER_INFO csbi;
// 				GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi);
// 				csbi.dwCursorPosition.Y-=1;
// 				SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ),csbi.dwCursorPosition);

// 				for (int d=delete_idx->size()-1; d >=0;d--)
// 				{	
// 					cv::Point3i idx= (*delete_idx)[d];							
// 					can.splines[idx.x]->GetWordSamples()[idx.y][idx.z]->mesh=(*delete_charsample)[d];
// 				}

				//delete_charsample->clear();
				//delete_idx->clear();

				//can.splines.pop_back();
				//can.splines.back()->LastLine(NULL);		
			}
			else
			{
				wordrand[i].x=randomseed[randcount++]%wordarray[i].size();
				wordrand[i].y=randomseed[randcount++]%3;

				i--;
			}
		}	
		for(int i = 0 ; i <candidate_strings.size();i++)
		{
			can.splines.pop_back();
			can.splines.back()->LastLine(NULL);		
		}
		n++;
	} 			

	AppFrame::AppAlgoTextBigScale::setflag(true,false);
	//sort(id.begin(),id.end(),sort_island);
	cout<<"id size "<<id.size()<<endl;

	int chose=0;
	cv::Mat no_use;
	//test= true;
	for(int i = 0 ; i<id.size();i++)
	{
		AppFrame::AppAlgoTextBigScale::setidx(id[i].nl,id[i].nw,id[i].nt);	
		if(BuildBigScale(can.splines,no_use))
		{
			text_color.Execute(*can.splines.back());
			
			id_picked.push_back(id[i]);

			for (int j= 0 ;j<id[i].endline-id[i].startline+1;j++)
			{				
				line_word_order[id[i].startline+j]=1;
			}
			chose++;
			id[i].word_mask.release();
			id.erase(id.begin()+i);
			i=-1;
			if (chose>5)
			{
				break;
			}
		}
		else
		{
			//cout<<"f"<<endl;
			id[i].word_mask.release();
			id.erase(id.begin()+i);
			i--;
		}	
		
	}
	/*for (int i = 0 ; i < line_word_order.size(); i++)
	{
		cout<<line_word_order[i]<<" ";
	}
	cout<<endl;
	cout<<"start retextgen"<<endl;*/

	int aftersplinesize=can.splines.size();
 	ReTextGen(can.splines,_appItem,id_picked,line_word_order);
	double Et=visualenergy.EvaluateTextEnergy(can.splines);
	cout<<"after ET "<<Et<<endl;

	for (int i = 0 ; i <can.splines.size();i++)
	{
		text_color.Execute(*can.splines[i]);
	}
	drawallsplines(can.splines,allmask,_appItem->Data->WordArtEvi.background_color,_appItem->Data->WordArtEvi.qr_foreground_modules,_appItem->Data->WordArtEvi.qr_background_modules);
	double Em=ModuleEnergy.Execute_Modules_Avg(allmask,_appItem->Data->WordArtEvi.seg_pids);
	cout<<"after Em "<<Em<<endl;
	can.Em=Em;
	can.Et=Et;
	_appItem->Data->WordArtEdt.CanData.candidates.push_back(can);


	//cout<<can.splines.size()<<endl;

	
	return true;
}
double AppAlgoTextBigScale::calcQRenergy(HKCAppItem^ _appItem,vector<double>& orienergys,cv::Mat &allmask ,cv::Mat &word_mask)
{
	AppAlgoProbabilityModule ModuleEnergy(_appItem);
	int erosion_size=2;		
	cv::Mat element = getStructuringElement( cv::MORPH_RECT,cv::Size( 2*erosion_size + 1, 2*erosion_size+1 ),cv::Point( erosion_size, erosion_size ) );
	cv::Mat word_mask_erode;
	cv::erode( word_mask, word_mask_erode, element );
	cvtColor(word_mask_erode,word_mask_erode,CV_BGR2GRAY);
	vector<int> covermodule= AppAlgoQRCodeSegmentation::SegmentQRCode(word_mask_erode,_appItem->Data->QRCData,_appItem->Data->QRCData.module_size);
	bitwise_not(allmask,allmask);
	imshow("word_mask_erode",word_mask_erode);
	imshow("allmask",allmask);	
	vector<double> covermodule_e = ModuleEnergy.Execute_Modules(allmask,covermodule);
	imshow("after",allmask);		
	double diff=0;
	//cout<<covermodule.size()<<endl;
	
	for (int i = 0 ; i <covermodule.size();i++)
	{
		//cout<<i<<covermodule.size()<<endl;
		int id = covermodule[i];
		//cout<<id<<" "<<orienergys[id]<<" "<<covermodule_e[i]<<endl;				
		diff+=orienergys[id]-covermodule_e[i];
	}
	return diff;
}
bool AppAlgoTextBigScale::BuildBigScale(QRStringLines& splines	,cv::Mat& word_mask)
{
	

	QRWordArt::QRStringLine* CopySpline=new QRWordArt::QRStringLine();

	AppAlgoTextTyping	text_typing;
	string word=splines[nspline]->GetWords()[nword];
	printf("start build big scale %d %d %d\n",nspline,nword,nsizetype);	
	
	
	HSSSpline::Sample from = splines[nspline]->GetWordSamples()[nword][0]->sample;
	std::string string = splines[nspline]->GetWords()[nword];
	HSSSpline::Sample backsample = splines[nspline]->GetWordSamples()[nword].front()->sample;
	double offset = splines[nspline]->Offset(string.back(),backsample);
	splines[nspline]->ShiftSampleBackward(from,offset,&from);
	HSSSpline::Sample to ;
	to.seg_idx = (*splines[nspline]).n_segs()-1;
	to._t = 1;

	
	(*splines[nspline]).Duplicate(from,to,CopySpline);
	HSSSpline::PathPoints<5> ctrlpoints=CopySpline->GetCtrlPoints();
	HSSSpline::PathPoints<5> allpoints=CopySpline->GetUniformSamplePoints(1);
	
	HSSSpline::Vector2 avg_normal;

	if(CopySpline->n_segs()%2==0)
		avg_normal=CopySpline->get_normal(CopySpline->n_segs()/2,0);
	else
		avg_normal=CopySpline->get_normal(CopySpline->n_segs()/2,0.5);
	switch(nsizetype)
	{
	case 0:
		for(int i = 0 ; i<allpoints.size();i++)
		{
			int nearest_idx;
			HSSSpline::PathPoint<5>p1,p2;
			if((*splines[nspline]).LastLine()!=NULL)
				p1=findnearest( splines[nspline]->LastLine()->GetUniformSamplePoints(1),allpoints[i],nearest_idx);
			else
			{
				//cout<<"last null "<<nspline<<" "<<nword<<endl;
				return false;
			}
			p2=allpoints[i];
			double off1h1=100*p1[3]/2;
			double off1h2=100*p1[4]/2;
			double off2h1=100*p2[3]/2;
			double off2h2=100*p2[4]/2;
			double off1=(off1h1/50+off1h2/50)/2;
			double off2=(off2h1/50+off2h2/50)/2;
			double d=sqrt((p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1]));
			//cout<<d<<" "<<off1<<" "<<off2<<endl;
			double dall=d+off2+off1;
			allpoints[i]=HSSSpline::PathPoint<5>((p1[0]*(dall/2-off2)/d+p2[0]*(dall/2-off1)/d),(p1[1]*(dall/2-off2)/d+p2[1]*(dall/2-off1)/d),dall*2*40/100,dall*40/100,dall*40/100);
			//cout<<allpoints[i].ToString()<<endl;
		}
		CopySpline->Clean();
		CopySpline->AssignPoints(allpoints);
		CopySpline->FittingCurve(0.1);
		break;
	case 1:
		for(int i = 0 ; i<allpoints.size();i++)
		{
			int nearest_idx;
			HSSSpline::PathPoint<5>p1,p2;
			if((*splines[nspline]).NextLine()!=NULL)
				p1=findnearest( splines[nspline]->NextLine()->GetUniformSamplePoints(1),allpoints[i],nearest_idx);
			else
			{
				//cout<<"next null "<<nspline<<" "<<nword<<endl;
				return false;
			}
			p2=allpoints[i];		
			double off1h1=100*p1[3]/2;
			double off1h2=100*p1[4]/2;
			double off2h1=100*p2[3]/2;
			double off2h2=100*p2[4]/2;
			double off1=(off1h1/50+off1h2/50)/2;
			double off2=(off2h1/50+off2h2/50)/2;
			double d=sqrt((p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1]));
			//cout<<d<<" "<<off1<<" "<<off2<<endl;
			double dall=d+off2+off1;
			allpoints[i]=HSSSpline::PathPoint<5>((p1[0]*(dall/2-off2)/d+p2[0]*(dall/2-off1)/d),(p1[1]*(dall/2-off2)/d+p2[1]*(dall/2-off1)/d),dall*2*40/100,dall*40/100,dall*40/100);
			//cout<<(p1[0]*(dall/2-off2)/d+p2[0]*(dall/2-off1)/d)<<" "<<(p1[1]*(dall/2-off2)/d+p2[1]*(dall/2-off1)/d)<<" "<<dall/100<<" "<<dall/100<<endl;
		}
		CopySpline->Clean();
		CopySpline->AssignPoints(allpoints);
		CopySpline->FittingCurve(0.1);

		break;
	case 2:
		//cout<<"here"<<endl;		
		for(int i = 0 ; i<allpoints.size();i++)
		{
			int nearest_idx;
			HSSSpline::PathPoint<5>p1,p2;
			if((*splines[nspline]).LastLine()!=NULL)
				p1=findnearest( splines[nspline]->LastLine()->GetUniformSamplePoints(1),allpoints[i],nearest_idx);
			else
			{
				//cout<<"last null "<<nspline<<" "<<nword<<endl;
				return false;
			}
			if((*splines[nspline]).NextLine()!=NULL)
				p2=findnearest( splines[nspline]->NextLine()->GetUniformSamplePoints(1),allpoints[i],nearest_idx);
			else
			{
				//cout<<"next null "<<nspline<<" "<<nword<<endl;
				return false;
			}			

			double off1h1=100*p1[3]/2;
			double off1h2=100*p1[4]/2;
			double off2h1=100*p2[3]/2;
			double off2h2=100*p2[4]/2;
			double off1=(off1h1/50+off1h2/50)/2;
			double off2=(off2h1/50+off2h2/50)/2;
			double d=sqrt((p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1]));
			//cout<<d<<" "<<off1<<" "<<off2<<endl;
			double dall=d+off2+off1;
			allpoints[i]=HSSSpline::PathPoint<5>((p1[0]*(dall/2-off2)/d+p2[0]*(dall/2-off1)/d),(p1[1]*(dall/2-off2)/d+p2[1]*(dall/2-off1)/d),dall*2*40/100,dall*40/100,dall*40/100);
			//cout<<(p1[0]*(dall/2-off2)/d+p2[0]*(dall/2-off1)/d)<<" "<<(p1[1]*(dall/2-off2)/d+p2[1]*(dall/2-off1)/d)<<" "<<dall/100<<" "<<dall/100<<endl;
		}
		CopySpline->Clean();
		CopySpline->AssignPoints(allpoints);
		CopySpline->FittingCurve(0.1);	
		break;
	case 3:
		for(int i = 0 ; i<allpoints.size();i++)
		{
			int nearest_idx;
			HSSSpline::PathPoint<5>p1,p2;
			
			p1=allpoints[i];
			if((*splines[nspline]).NextLine()!=NULL&&(*splines[nspline]).NextLine()->NextLine()!=NULL)
				p2=findnearest( splines[nspline]->NextLine()->NextLine()->GetUniformSamplePoints(1),allpoints[i],nearest_idx);
			else
			{
				//cout<<"next next null "<<nspline<<" "<<nword<<endl;
				return false;
			}			

			double off1h1=100*p1[3]/2;
			double off1h2=100*p1[4]/2;
			double off2h1=100*p2[3]/2;
			double off2h2=100*p2[4]/2;
			double off1=(off1h1/50+off1h2/50)/2;
			double off2=(off2h1/50+off2h2/50)/2;
			double d=sqrt((p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1]));
			//cout<<d<<" "<<off1<<" "<<off2<<endl;
			double dall=d+off2+off1;
			allpoints[i]=HSSSpline::PathPoint<5>((p1[0]*(dall/2-off2)/d+p2[0]*(dall/2-off1)/d),(p1[1]*(dall/2-off2)/d+p2[1]*(dall/2-off1)/d),dall*2*40/100,dall*40/100,dall*40/100);
			//cout<<(p1[0]*(dall/2-off2)/d+p2[0]*(dall/2-off1)/d)<<" "<<(p1[1]*(dall/2-off2)/d+p2[1]*(dall/2-off1)/d)<<" "<<dall/100<<" "<<dall/100<<endl;
		}
		CopySpline->Clean();
		CopySpline->AssignPoints(allpoints);
		CopySpline->FittingCurve(0.1);
		break;
	case 4:
		for(int i = 0 ; i<allpoints.size();i++)
		{
			int nearest_idx;
			HSSSpline::PathPoint<5>p1,p2;
			if((*splines[nspline]).LastLine()!=NULL&&(*splines[nspline]).LastLine()->LastLine()!=NULL)
				p1=findnearest(splines[nspline]->LastLine()->LastLine()->GetUniformSamplePoints(1),allpoints[i],nearest_idx);
			else
			{
				//cout<<"last last null "<<nspline<<" "<<nword<<endl;
				return false;
			}
			p2=allpoints[i];
		
			double off1h1=100*p1[3]/2;
			double off1h2=100*p1[4]/2;
			double off2h1=100*p2[3]/2;
			double off2h2=100*p2[4]/2;
			double off1=(off1h1/50+off1h2/50)/2;
			double off2=(off2h1/50+off2h2/50)/2;

			double d=sqrt((p1[0]-p2[0])*(p1[0]-p2[0])+(p1[1]-p2[1])*(p1[1]-p2[1]));
			//cout<<d<<" "<<off1<<" "<<off2<<endl;
			double dall=d+off2+off1;
			allpoints[i]=HSSSpline::PathPoint<5>((p1[0]*(dall/2-off2)/d+p2[0]*(dall/2-off1)/d),(p1[1]*(dall/2-off2)/d+p2[1]*(dall/2-off1)/d),dall*2*40/100,dall*40/100,dall*40/100);
			//cout<<(p1[0]*(dall/2-off2)/d+p2[0]*(dall/2-off1)/d)<<" "<<(p1[1]*(dall/2-off2)/d+p2[1]*(dall/2-off1)/d)<<" "<<dall/100<<" "<<dall/100<<endl;
		}
		CopySpline->Clean();
		CopySpline->AssignPoints(allpoints);
		CopySpline->FittingCurve(0.1);
		break;
	default:
		return false;
		break;
	}	

	HSSSpline::Samples samples_out;

	if(CopySpline->TypeSetting(word,&samples_out,HSSSpline::Sample(0,0),HSSSpline::Sample(-1,-1)))
	{			
		std::vector<QRWordArt::QRStringLine::QRSample*> c_samples = CopySpline->AttachWord(word,samples_out);	
		if(m_checkroveredge)
		{
			if(CheckOverEdge(c_samples,*edgeImg))
			{
				cout<<"fail: over edge"<<endl;
				delete CopySpline;
				return false;
			}
		}			
		if(m_checkoverlap)
		{

			
			for (int i = ori_num ; i<=splines.size()-1;i++)
			{
				if (CheckOverlap(splines[i]->GetQRSamples(),c_samples))
				{
					cout<<"fail: overlap"<<endl;
					delete CopySpline;
					return false;
				}					
			}				
		}
		
		if(m_checkroveredge&&0)
		{
			DeleteCovered(splines,c_samples);				
		}	

		QRWordArt::QRSplineFBO charFBO;
		charFBO.Initialize(img_width,img_height);
		


		QRWordArt::QRStringLine* CopyCopySpline=new QRWordArt::QRStringLine();
		
		HSSSpline::Sample to=CopySpline->GetQRSamples().back()->sample;
		
		string = CopySpline->GetWords()[0];
		backsample = CopySpline->GetWordSamples()[0].back()->sample;
		offset = CopySpline->Offset(string.back(),backsample);
		CopySpline->ShiftSampleForeward(to,offset,&to);
		CopySpline->Duplicate(HSSSpline::Sample(0,0),to,CopyCopySpline);
		CopyCopySpline->Region()=splines[nspline]->Region();
		charFBO.Push(CopySpline,HSSSpline::Sample(0,0),to);
		charFBO.Draw(&word_mask);
		cv::flip(word_mask,word_mask,0);					
		charFBO.Clear();
		HSSSpline::Sample* cusor =new HSSSpline::Sample(0,0);
		//cout<<"get wordsize 1 "<<CopySpline->GetWords().size()<<endl;
		samples_out.clear();
		for(int i = 0 ; i <CopySpline->GetWords().size();i++)
		{			
			//cout<<line<<" "<<newspline->GetWords()[i]<<endl;
			CopyCopySpline->TypeSetting(CopySpline->GetWords()[i],&samples_out,HSSSpline::Sample(0,0),HSSSpline::Sample(-1,-1));
			CopyCopySpline->AttachWord(CopySpline->GetWords()[i],samples_out);
			/*for(int c = 0 ; c<c)
			CopyCopySpline*/
		}
		//cout<<"get wordsize 2 "<<CopyCopySpline->GetWords().size()<<endl;
		///***
		delete cusor;
		delete CopySpline;
		splines.back()->NextLine(CopyCopySpline);
		CopyCopySpline->LastLine(splines.back());
		splines.push_back(CopyCopySpline);
		//splines.insert(splines.begin()+nspline+1,CopyCopySpline);
	}
	else
	{
		cout<<"fail: typesetting"<<endl;
		//delete CopySpline;
		return false;
	} 
	
	return true;
}

bool AppFrame::AppAlgoTextBigScale::ReTextGen(QRStringLines& splines,HKCAppItem^ _appItem,vector<YJFID>& id_picked,vector<int>& line_word_order)
{		
	vector<int> char_map_index;
	bool covered=false;
	int str_idx=0;
	vector<std::string>& strings = _appItem->Data->WordArtEvi.candidate_strings;
	AppAlgoTextAlign	text_align;
	AppAlgoTextColor	text_color(_appItem);
	text_color.Enable((int)_appItem->Param->WordArt->ColorMode);
	AppAlgoTextTyping	text_typing;
	int erosion_size=3;		
	cv::Mat element = getStructuringElement( cv::MORPH_RECT,cv::Size( 2*erosion_size + 1, 2*erosion_size+1 ),cv::Point( erosion_size, erosion_size ) );
	cv::Mat other_char_map;
	QRStringLines newsplines;
	HSSSpline::Sample test = splines[3]->GetWordSamples()[3][0]->sample;
	for (int line = line_word_order.size()-1 ;line>=0;line--)
	{	
		if (line_word_order[line]==-1)
		{
			continue;
		}
		//int order=line_word_order[line];
		cout<<line<<endl;
		Mat linemap=cv::Mat(img_height,img_width,CV_8UC3,cv::Scalar(255,255,255));
		for (int j = 0 ; j <id_picked.size(); j ++)
		{
// 			cout<<line<<endl;
// 			cout<<id_picked[j].startline<<" "<<id_picked[j].endline<<endl;; 
			if (line>=id_picked[j].startline&&line<=id_picked[j].endline)
			{
				bitwise_and(linemap,id_picked[j].word_mask,linemap);
			}
		}
		//imshow("wordmask",linemap);
		//waitKey();
		//cv::erode( linemap, linemap, element );
		for (int i=0;i<img_width*img_height;++i)
		{
			if(linemap.data[i*3]==0)
				char_map_index.push_back(i);
		}
		
		flip(linemap,linemap,0);
		//imshow("linemap",linemap);
		
		HSSSpline::Sample from(0,0);
		HSSSpline::Sample to(0,0);
		HSSSpline::Sample refrom;
		HSSSpline::Sample reto;
		Mat test=linemap.clone();
		while(true)
		{
			bool covered=false;
			bool end=false;
			int count=0;
			HSSSpline::PathPoint<5> point_to =splines[line]->get_point(to);
			
			test.data[((int)point_to.val[1]*img_width+(int)point_to.val[0])*3+0]=0;
			test.data[((int)point_to.val[1]*img_width+(int)point_to.val[0])*3+1]=255;
			test.data[((int)point_to.val[1]*img_width+(int)point_to.val[0])*3+2]=0;
	
			if(linemap.data[((int)point_to.val[1]*img_width+(int)point_to.val[0])*3]!=255)
			{
				covered=true;
			}
			if (to.seg_idx>=splines[line]->n_segs()-1&&to._t>=1)
			{
				end=true;
			}	
			QRStringLine *newspline=new QRStringLine;
			bool front=false;
			bool back= false;
			if((from.seg_idx<to.seg_idx||(from.seg_idx==to.seg_idx&&from._t<to._t))&&(covered||end))
			{									
				test=linemap.clone();				
								
				cout<<"initial "<<from.seg_idx<<" "<<from._t<<"  -  "<<to.seg_idx<<" "<<to._t<<endl;

				HSSSpline::Sample cursor(0,0);
				HSSSpline::Sample sample_end(splines[line]->n_segs()-1,1);
				splines[line]->Duplicate(from,to,newspline);

				if (from.seg_idx!=0||from._t!=0)
				{
					front=true;
				}
				else if (to.seg_idx!=splines[line]->n_segs()-1||to._t!=1)
				{
					back=true;
				}
				if (line<=nspline&&back==true)
				{
					cout<<"line <= nspline"<<endl;
					QRWordArt::QRStringLine::WordSamples& qrSamples = splines[line]->GetWordSamples();
					refrom=HSSSpline::Sample(0,0);
					reto=HSSSpline::Sample(newspline->n_segs()-1,1);
					for (int i = 0 ; i <qrSamples.size(); i++)
					{
						bool flag = false;
						if (qrSamples[i][0]->sample.seg_idx==from.seg_idx&&qrSamples[i][0]->sample._t>=from._t)
						{
							flag=true;
						}
						else if  (qrSamples[i][0]->sample.seg_idx==to.seg_idx&&qrSamples[i][0]->sample._t<=to._t)
						{
							flag=true;
						}
						else if (qrSamples[i][0]->sample.seg_idx>from.seg_idx&&qrSamples[i][0]->sample.seg_idx<to.seg_idx)
						{
							flag=true;
						}	
						if (!flag)
						{
							continue;
						}
						std::string word =splines[line]->GetWords()[i];
						if (text_typing.Typing(word,*newspline,refrom,reto,&refrom,false))
						{
							text_typing.Typing_Space(*newspline,refrom,reto,&refrom);
							double r,g,b;
							for (int w = 0 ;w<word.size();w++)
							{
								qrSamples[i][w]->qr_char->GetColor(&r,&g,&b);
								newspline->GetWordSamples().back()[w]->qr_char->SetColor(r,g,b);
								newspline->GetWordSamples().back()[w]->WordId = qrSamples[i][w]->WordId;
								newspline->GetWordSamples().back()[w]->_IsSentenceEnd =  qrSamples[i][w]->_IsSentenceEnd;
								newspline->GetWordSamples().back()[w]->_IsSentenceStart =  qrSamples[i][w]->_IsSentenceStart;
							}
							
						}

					}
				}
				newspline->Region()=splines[line]->Region();
				/*if (front)
				{				
					cout<<"front"<<endl;
					//cout<<line<<" before "<<newspline->GetCharSample().size()<<endl;				
					int wordsizerecord=newspline->GetWords().size();
					bool flag = false;
					refrom=HSSSpline::Sample(0,0);
					reto=HSSSpline::Sample(newspline->n_segs()-1,1);
					bool first =false;
					while (flag)
					{
						int idx = str_idx%(strings.size());
						std::string word = strings[idx];
						HSSSpline::Samples samples;
						if (text_typing.Typing(word,*newspline,refrom,reto,&refrom,true))
						{
							flag = text_typing.Typing_Space(*newspline,refrom,reto,&refrom);
						}else{
							flag = false;
						}
						if (newspline->GetWords().size()>wordsizerecord)
							str_idx++;		
						wordsizerecord=newspline->GetWords().size();
					}
				}				
				else if (back)
				{	
					cout<<"back"<<endl;
					int wordsizerecord=newspline->GetWords().size();
					bool flag = false;
					reto=HSSSpline::Sample(0,0);
					refrom=HSSSpline::Sample(newspline->n_segs()-1,1);
					bool first =false;
					while (flag)
					{
						int idx = str_idx%(strings.size());
						std::string word = strings[idx];
						HSSSpline::Samples samples;
						if (text_typing.R_Typing(word,*newspline,refrom,reto,&refrom,true))
						{
							flag = text_typing.R_Typing_Space(*newspline,refrom,reto,&refrom);
						}else{
							flag = false;
						}
						if (newspline->GetWords().size()>wordsizerecord)
							str_idx++;		
						wordsizerecord=newspline->GetWords().size();
					}	
				}*/
			}
			else if(!covered||!end)
			{
				if (to._t<=1)
				{
					to._t+=0.05;
				}
				else if(to.seg_idx<splines[line]->n_segs()-1)
				{
					to._t=0;
					to.seg_idx++;
				}
				HSSSpline::PathPoint<5> point_from=splines[line]->get_point(from);
				///***
				if(linemap.data[((int)point_from.val[1]*img_width+(int)point_from.val[0])*3]!=255)
				{
					test=linemap.clone();
					from=to;
				}
				continue;
			}
			
			if((from.seg_idx<to.seg_idx||(from.seg_idx==to.seg_idx&&from._t<to._t))&&(covered||end))//&&newspline->GetQRSamples().size()!=0)
			{				
				newspline->SortWords();	
				//text_align.Justify(*newspline);
				if (newsplines.size()!=0)
				{
					newsplines.back()->NextLine(newspline);
					newspline->LastLine(newsplines.back());
					newsplines.push_back(newspline);
				}
				else
				{					
					newsplines.push_back(newspline);
				}	
				
			}
			if (end)
			{
				break;
			}
			from=to;		
			if (line==nspline&&newsplines.size()==1)
			{
				QRStringLine* BigSpline = splines.back();
				if (newsplines.size()==1)
				{
					if (back==true)
					{
						newsplines.front()->NextLine(BigSpline);
						BigSpline->LastLine(newsplines.back());
						newsplines.push_back(BigSpline);
						newsplineId=nspline+2;
					}
					else if (front ==true)
					{
						newsplines.back()->LastLine(BigSpline);
						BigSpline->NextLine(newsplines.back());
						newsplines.insert(newsplines.begin(),BigSpline);
						newsplineId=nspline+1;
					}
					splines.pop_back();
				}
			}
		}
		
		
		if(line!=0)
		{
			splines[line-1]->NextLine(newsplines.front());
		}
		if((line+1)<splines.size())
		{
			splines[line+1]->LastLine(newsplines.back());
		}
		splines.erase(splines.begin()+line);
		splines.insert(splines.begin()+line,newsplines.begin(),newsplines.end());
		
		newsplines.clear();
		linemap.release();
	}
	return true;
}

void AppFrame::AppAlgoTextBigScale::sortwordarray(QRStringLines& splines,vector<std::string>& strings,vector<vector<cv::Point>>& wordarray)
{
	wordarray.resize(strings.size());
	for (int i = 0 ; i <splines.size();i++)
	{
		for(int j =0 ; j <splines[i]->GetWords().size(); j++)
		{
			for (int k = 0; k<strings.size();k++)
			{
				if (splines[i]->GetWords()[j]==strings[k])
				{
					wordarray[k].push_back(cv::Point(i,j));
					break;
				}
			}
		}
	}
}
bool AppFrame::AppAlgoTextBigScale::CheckOverlap( QRStringLine::QRSamples& string_data1,QRStringLine::QRSamples& string_data2 )
{
	QRWordArt::QRCharacter::CharFBO charFBO;
	charFBO.Initialize(img_width,img_height);
	charFBO.Enable(QRWordArt::QRCharacter::CharFBO::BOUNDINGBOX);
	for (int i = 0 ; i<string_data1.size();i++)	
	{
		QRWordArt::QRCharacter::Char *qr_char = string_data1[i]->qr_char;
		if(qr_char!=NULL)charFBO.Push(qr_char);
	}

	cv::Mat other_char_map;
	charFBO.Draw(&other_char_map);
	cv::flip(other_char_map,other_char_map,0);
	charFBO.Clear();
	for (int i = 0 ; i<string_data2.size();i++)
	{
		QRWordArt::QRCharacter::Char *qr_char = string_data2[i]->qr_char;
		if(qr_char!=NULL){charFBO.Push(qr_char);}
	}
	cv::Mat char_map;
	charFBO.Draw(&char_map);
	cv::flip(char_map,char_map,0);

	for (int i=0;i<img_width*img_height;++i)
	{
		if (char_map.data[i*3]==0 && other_char_map.data[i*3]==0)
		{
			return true;
		}
	}
	char_map.release();
	other_char_map.release();
	return false;
}

bool AppFrame::AppAlgoTextBigScale::CheckOverEdge( QRStringLine::QRSamples& string_data1,cv::Mat break_area_img )
{
	QRWordArt::QRCharacter::CharFBO charFBO;
	charFBO.Initialize(img_width,img_height);	
	cv::threshold(break_area_img,break_area_img,254,255,cv::THRESH_BINARY);
	
	for (int i = 0 ; i<string_data1.size();i++)
	{
		QRWordArt::QRCharacter::Char *qr_char = string_data1[i]->qr_char;
		if(qr_char!=NULL)charFBO.Push(qr_char);
	}

		cv::Mat other_char_map;
		charFBO.Draw(&other_char_map);
		cv::flip(other_char_map,other_char_map,0);
		charFBO.Clear();

		for (int i=0;i<img_width*img_height;++i)
		{
			if (other_char_map.data[i*3]==0&&break_area_img.data[i]==255  )
			{
					return true;
			}
		}

			return false;
}

bool AppFrame::AppAlgoTextBigScale::DeleteCovered(QRWordArt::QRStringLines & splines,QRWordArt::QRStringLine::QRSamples& word_data)
{
	vector<cv::Point3i> deleteidx;
	QRWordArt::QRCharacter::CharFBO charFBO;
	charFBO.Enable(QRWordArt::QRCharacter::CharFBO::BOUNDINGBOX);
	vector<int> char_map_index;
	bool covered=false;
	charFBO.Initialize(img_width,img_height);

	for(int i=0;i<word_data.size();i++)
	{
		QRWordArt::QRCharacter::Char *qr_char = word_data[i]->qr_char;
		if(qr_char!=NULL){charFBO.Push(qr_char);}
	}
	cv::Mat char_map;
	charFBO.Draw(&char_map);
	cv::flip(char_map,char_map,0);
	charFBO.Clear();
	for (int i=0;i<img_width*img_height;++i)
	{
		if(char_map.data[i*3]==0)
			char_map_index.push_back(i);
	}
	int startline,endline;

	switch(nsizetype)
	{
	case 0:
		startline=nspline-1;
		endline=nspline;
		break;
	case 1:
		startline=nspline;
		endline=nspline+1;
		break;
	case 2:
		startline=nspline-1;
		endline=nspline+1;
		break;
	case 3:
		startline=nspline;
		endline=nspline+2;
		break;
	case 4:
		startline=nspline-2;
		endline=nspline;
		break;
	}
	cv::Mat other_char_map;
	for (int i = startline ; i<=endline;i++)
	{

		for(int j=0;j<splines[i]->GetWordSamples().size();j++)
		{
			for (int k = 0 ; k<splines[i]->GetWordSamples()[j].size();k++)
			{
				QRWordArt::QRCharacter::Char *qr_char = splines[i]->GetWordSamples()[j][k]->qr_char;
				if (qr_char==NULL)continue;

				charFBO.Push(qr_char);				
				charFBO.Draw(&other_char_map);
				cv::flip(other_char_map,other_char_map,0);
				
				for (int s=0;s<char_map_index.size();++s)
				{
					int idx=char_map_index[s];
					if (other_char_map.data[idx*3]==0)
					{						
						deleteidx.push_back(cv::Point3i(i,j,k));
						break;
					}
				}
				charFBO.Clear();
				other_char_map.release();
			}	
		}
	}
	
	for (int i=deleteidx.size()-1; i >=0;i--)
	{		
		cv::Point3i idx = deleteidx[i];
		delete_idx->push_back(idx);
		delete_charsample->push_back(splines[idx.x]->GetWordSamples()[idx.y][idx.z]->qr_char);
		splines[idx.x]->GetWordSamples()[idx.y][idx.z]->qr_char=NULL;
	}

	char_map.release();
	return true;
}