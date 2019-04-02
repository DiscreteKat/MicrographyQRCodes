/**
* @file Form_WordArt.cpp
*
* Implementation of QR code generator's functions
*
* @author Elaine Cheng-Li Hsieh
*/

#include "StdAfx.h"
#include "Form1.h"
#include <string.h>

#include "AppAlgoETF.h"
#include "AppAlgoStreamlineTrace.h"

#include "AppAlgoTextBigScale.h"

#include "AppAlgoProbabilityModule.h"
#include "AppAlgoModuleSelection.h"

#include "AppAlgoRegionSeg.h"

#include "AppAlgoTextGeneration.h"
#include "AppAlgoTextColor.h"

#include "AppAlgoQRCodeEvaluation.h"
#include "AppAlgoEnergyVisual.h"

#include "AppAlgoTextWarping.h"
#include "AppAlgoTextOrderOri.h"

#include "QRWordArt/QRWordArtIO.h"
#include "QRWordArt/QRCharacterIO.h"

#include "AppUtils.h"
#include "AppState.h"
using namespace AppFrame;
using namespace DevComponents::DotNetBar;
using namespace DevComponents::Editors;
using namespace HKOGLPanel;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::Form1

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                         Word Art functions                           */
/// WordArt generator's action
void Form1::WordArt_Action(System::String^ _action)
{
// 	unsigned _s=10;
	
	if(!mp_AppItem) return;

	//HKCQRCParam^ qrcParam = mp_AppItem->Param->QRCode;
	if(System::String::Compare("Strings", _action) == 0)
	{
		if (WordArtText2->Text!=mp_AppItem->Param->WordArt->strings)
		{WordArtText2->Text = mp_AppItem->Param->WordArt->strings;}

		vector<std::string>& candidate_strings = mp_AppItem->Data->WordArtEvi.candidate_strings;
		candidate_strings.clear();

		cli::array<System::Char>^ chars = {';'};
		cli::array<System::String^>^ split = mp_AppItem->Param->WordArt->strings->Split(chars);
		StringData->Text="";
		for(int i=0;i<split->GetLength(0);i++)
		{
			StringData->Text+="string ";
			StringData->Text+=(i+1);
			StringData->Text+=" : ";
			StringData->Text+=split[i];
			StringData->Text+="\n";

			char* str = (char*)(void*)Marshal::StringToHGlobalAnsi(split[i]);
			int len=strlen(str);
			if(len==0)
				continue;

			std::string string;
			for(int j=0;j<len;j++){string.push_back(str[j]);}
			candidate_strings.push_back(string);
		}
	}
	else if (System::String::Compare("LOADSEG", _action) == 0)
	{
		std::cout<<"Load Segment Image...\n";

		cv::Mat& segment_img = mp_AppItem->Data->WordArtEvi.segment_img;
		cv::Mat& region_img  = mp_AppItem->Data->WordArtEvi.region_img;
		region_img = cv::imread(mp_AppItem->Data->IO_Handle.seg_filename, CV_LOAD_IMAGE_GRAYSCALE);
		threshold(region_img,segment_img,254,255,cv::THRESH_BINARY);
		
		HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
		cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());
		// Resize Segmentation img 	
		cv::Size newSize = srcImg->size();
		cv::resize(segment_img, segment_img, newSize, 0, 0, cv::INTER_NEAREST);
		cv::resize(region_img , region_img , newSize, 0, 0, cv::INTER_NEAREST);

		AppAlgoRegionSeg app_region_seg;
		app_region_seg.Execute(mp_AppItem);

		HKCMediaItem^ wordartItem;
		if(mp_AppItem->Find("Region")) mp_AppItem->Delete("Region");
		wordartItem = mp_AppItem->New(region_img, "Region", mp_GLPanel);
		mp_GLPanel->Invalidate();
		/// Rebuild layers
		mp_AppLayerMgr->Build(this->LayerTree, mp_AppItem);
		this->ParamGrid->Refresh();

		//Centerize the media
		GLPanel_Focus(mp_AppItem);
		MQRC_Action("PRE_PROCESS");
	}
	else if (System::String::Compare("LOADVFB", _action) == 0)
	{
		std::cout<<"Load Vector Field...";

		vector<cv::Point2f>& seg_flow=mp_AppItem->Data->WordArtEvi.flow_map;
		vector<cv::Point2f>().swap(seg_flow);

		FILE *stream = fopen(mp_AppItem->Data->IO_Handle.vbf_filename.c_str(), "rb" );
		if ( !stream ) {std::cout<<"\n  - ERROR!! Can't read "<<'\n';}
		else{
			int vf_w , vf_h;
			fread(&vf_w,sizeof(int),1,stream);
			fread(&vf_h,sizeof(int),1,stream);

			float *data = new float[vf_w*vf_h*2];
			for(int i=0; i<vf_w*vf_h; i++){
				fread(&data[2*i],sizeof(float),1,stream);
				fread(&data[2*i+1],sizeof(float),1,stream);
			}

			for(int x = 0 ; x < vf_h ; x++){
				for(int y = 0 ; y < vf_w ; y++){
					int id =(vf_h - x - 1) * vf_w + y;
					float x_vec=(-1)*data[2*id+1];
					float y_vec=data[2*id];
					if(isnan(x_vec))x_vec = 0;
					if(isnan(y_vec))y_vec = 0;
					seg_flow.push_back(cv::Point2f(x_vec,y_vec));
				}
			}
			delete [] data;

			std::cout<<"Done"<<std::endl;
			mp_AppItem->Data->IO_Handle.flowfield_loaded = true;
		}
	}
	else if (System::String::Compare("LOADARTICLE", _action) == 0)
	{
		std::cout<<"Load Article File...";
		vector<std::string>& candidate_strings = mp_AppItem->Data->WordArtEvi.candidate_strings;
		candidate_strings.clear();

		ifstream read(mp_AppItem->Data->IO_Handle.art_filename.c_str());
		string x;
		while(!read.eof())
		{
			string sub;
			read>>sub;
			transform(sub.begin(), sub.end(), sub.begin(), toupper);
			candidate_strings.push_back(sub);			
		}
		//getline(read,x);
		read.close();
		/*
		istringstream iss(x);
		do
		{
			string sub;
			iss >> sub;
			transform(sub.begin(), sub.end(), sub.begin(), toupper);
			candidate_strings.push_back(sub);
		} while (iss);*/
		candidate_strings.pop_back();

		mp_AppItem->Data->IO_Handle.article_loaded=true;
		AppAlgoTextGeneration::Text_Record_Order  = 0;
		mp_AppItem->Param->WordArt->ColorMode = WORDART_COLOR::SENTENCE;
		std::cout<<"Done"<<std::endl;
	}
	else if(System::String::Compare("PROCESSALL", _action) == 0)//Word Art產生
	{
		if (!mp_AppItem->Data->QRCData.isReady)
		{
			cout<<"Error: No QRcode Data"<<endl;
			return;
		}

		HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
		cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());
		cv::Mat& segment_img = mp_AppItem->Data->WordArtEvi.segment_img;
		if(segment_img.rows==0 || segment_img.cols==0)
		{
			cout<<"Error: No Segment Image"<<endl;
			return;
		}
		WordArt_Action("CLEAR");

		//Word Art Generation
		HKCAlgorithm^ algoObj_ETF = gcnew AppAlgoDoETF;
		HKCAlgorithm^ algoOderOri = gcnew AppAlgoTextOrderOri;
		HKCAlgorithm^ algoObj_LineTrace = gcnew AppAlgoStreamlineTrace;
		HKCAlgorithm^ algoObj_WidthAdjust =gcnew AppAlgoTextWarping;
		AppAlgoTextGeneration^ algoObj_TextGeneration = gcnew AppAlgoTextGeneration;
		AppAlgoTextBigScale algoObj_BuildBigScale;
		AppAlgoQRCodeEvaluation EnergyEvaluate;
		
		if (!mp_AppItem->Data->IO_Handle.flowfield_loaded)
		{
			//--------------------
			// Flow Field Generation
			//--------------------
			printf("Edge tangent flow...");
			algoObj_ETF->Execute(mp_AppItem);
			printf("Done\n");
		}
		
		//-----------------------
		// Line Tracing
		//-----------------------
		algoObj_LineTrace->Execute(mp_AppItem);
		//-----------------------
		// Width Adjust evaluate
		//-----------------------
		if (this->WarpCheckBox->Checked==true){algoObj_WidthAdjust->Execute(mp_AppItem);}		
		//-----------------------
		// Text Generation
		//-----------------------
		algoObj_TextGeneration->TypeSet(mp_AppItem->Param->WordArt->TextType);
		algoObj_TextGeneration->Execute(mp_AppItem);
		
		//Soild
		cv::Mat transparent = cv::Mat(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0));
	
		/// Show the WordArt image layer
		HKCWordArtEvi& wordart_data = mp_AppItem->Data->WordArtEvi;
		HKCMediaItem^ wordartItem;
		HKCImageProp^ wordartProp;
		AppAlgoProbabilityModule ModuleEnergy(mp_AppItem);
		AppAlgoEnergyVisual visualenergy(mp_AppItem);
		AppAlgoEnergyTextSpace   text_energy;
		for(int r = 0 ; r< mp_AppItem->Data->WordArtEvi.region_num;r++)
		{
				mp_AppItem->Data->WordArtData[0].splines.insert(mp_AppItem->Data->WordArtData[0].splines.end(),mp_AppItem->Data->WordArtEvi.region_splines[r].splines.begin(),mp_AppItem->Data->WordArtEvi.region_splines[r].splines.end());
				
				mp_AppItem->Data->WordArtEvi.region_splines[r].Ec=visualenergy.EvaluateFittingEdge(mp_AppItem->Data->WordArtEvi.region_splines[r].splines,r);
				mp_AppItem->Data->WordArtEvi.region_splines[r].Es=visualenergy.EvaluateLineSpace(mp_AppItem->Data->WordArtEvi.region_splines[r].splines);
				mp_AppItem->Data->WordArtEvi.region_splines[r].Et=visualenergy.EvaluateTextEnergy(mp_AppItem->Data->WordArtEvi.region_splines[r].splines);
				
				std::cout<<"====Region"<<r<<"===="<<std::endl;
				std::cout<<"Ec: "<<mp_AppItem->Data->WordArtEvi.region_splines[r].Ec<<std::endl;
				std::cout<<"Es: "<<mp_AppItem->Data->WordArtEvi.region_splines[r].Es<<std::endl;
				std::cout<<"Et: "<<mp_AppItem->Data->WordArtEvi.region_splines[r].Et<<std::endl;

				wordartItem = mp_AppItem->NewWordArt(transparent,""+r,mp_GLPanel);
				wordartProp = (HKCImageProp^)wordartItem->Prop;
				wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
				wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
				wordartProp->Render->Visible = true;
		}		
		EnergyEvaluate.Execute(mp_AppItem);
		QRCInf_Action(QRcodeLabel,EnergyEvaluate);
		QRenergyBar->Value=1000*(EnergyEvaluate.QRcodeQuality());
		this->label2->Text=L"QR energy : 0."+ this->QRenergyBar->Value.ToString();


		//algoOderOri->Execute(mp_AppItem);
		//??
// 		vector<int> count;
// 		count.resize(mp_AppItem->Data->WordArtEvi.candidate_strings.size(),0);
// 		for (int i =0 ; i<mp_AppItem->Data->WordArtData[0].splines.size();i++)
// 		{
// 			QRWordArt::QRStringLine* spline=mp_AppItem->Data->WordArtData[0].splines[i];
// 			for (int j = 0 ; j<spline->GetWords().size();j++)
// 			{
// 				for (int k = 0 ; k<mp_AppItem->Data->WordArtEvi.candidate_strings.size();k++)
// 				{
// 					if (spline->GetWords()[j].compare(mp_AppItem->Data->WordArtEvi.candidate_strings[k])==0)
// 					{
// 						count[k]++;
// 						break;
// 					}
// 				}
// 				
// 			}
// 		}
// 		cout<<count<<endl;

		wordartProp=(HKCImageProp^)srcItem->Prop;
		wordartProp->Render->Visible = false;
		
		SeeLevelCheck1->Checked = false;
		SeeLevelCheck2->Checked = true;
		SeeLevelCheck3->Checked = false;
		UpdateMQRCLayers(false);
	}
	else if (System::String::Compare("SCALING", _action) == 0)
	{
		HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
		cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());
		cv::Mat& segment_img = mp_AppItem->Data->WordArtEvi.segment_img;
		if(segment_img.rows==0 || segment_img.cols==0)
		{
			cout<<"Error: No Segment Image"<<endl;
			return;
		}
		if (mp_AppItem->Data->WordArtData[0].splines.size()==0)
		{
			cout<<"Error: NO spline"<<endl;
			return;
		}
		AppAlgoTextBigScale algoObj_BuildBigScale;
		//-----------------------
		// scaling optimize
		//-----------------------
		if (mp_AppItem->Data->WordArtEdt.temp_splines.empty())
		{
			mp_AppItem->Data->WordArtEdt.temp_splines.insert(mp_AppItem->Data->WordArtEdt.temp_splines.begin(),mp_AppItem->Data->WordArtData[0].splines.begin(),mp_AppItem->Data->WordArtData[0].splines.end());
			mp_AppItem->Data->WordArtData[0].splines.clear();
		}
		algoObj_BuildBigScale.Execute(mp_AppItem);
		
		HKCMediaItem^ wordartItem;
		HKCImageProp^ wordartProp;

		cv::Mat transparent = cv::Mat(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0));
		for (int i = 0 ;i < mp_AppItem->Data->WordArtEdt.CanData.candidates.size();i++)
		{
			wordartItem = mp_AppItem->NewCandidate(transparent, System::Convert::ToString(i)  , mp_GLPanel);//Candidates
			wordartProp = (HKCImageProp^)wordartItem->Prop;
			wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
			wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
			wordartProp->Render->Visible = i==0?true:false;
		}
		mp_AppLayerMgr->BuildCandidate(this->CandidateLayer, mp_AppItem);
		SeeLevelChange(2,true);
		this->ParamGrid->Refresh();
		GLPanel_Focus(mp_AppItem);
	}
	else if(System::String::Compare("CLEAR", _action) == 0)//清除Word Art資訊
	{
		mp_AppItem->ClearCandidate();
		mp_AppItem->ClearWordArt();

		mp_AppItem->Data->WordArtData[0].splines.clear();
		if (!mp_AppItem->Data->WordArtEvi.region_splines.empty())
		{
			for(int i = 0 ; i<mp_AppItem->Data->WordArtEvi.region_splines.size();i++)
			{
				QRWordArt::QRStringLines & splines= mp_AppItem->Data->WordArtEvi.region_splines[i].splines;
				while(!splines.empty())
				{
					QRStringLine* spline = splines.back();
					spline->Release();
					delete spline;
					splines.pop_back();
				}
			}
			mp_AppItem->Data->WordArtEvi.region_splines.clear();
		}

		if (!mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.empty())
		{
			QRWordArt::QRStringLines & splines= mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines;
			while(!splines.empty())
			{
				QRStringLine* spline = splines.back();
				spline->Release();
				delete spline;
				splines.pop_back();
			}
			mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.clear();
		}

		while(!mp_AppItem->Data->WordArtEdt.CanData.candidates.empty())
		{
			QRWordArt::QRStringLines & splines= mp_AppItem->Data->WordArtEdt.CanData.candidates.back().splines;
			while(!splines.empty())
			{
				QRStringLine* spline = splines.back();
				spline->Release();
				delete spline;
				splines.pop_back();
			}
			mp_AppItem->Data->WordArtEdt.CanData.candidates.pop_back();
		}		

		QRWordArt::QRStringLines& splines = mp_AppItem->Data->WordArtEdt.user_splines;
		while(!splines.empty())
		{
			QRStringLine* spline = splines.back();
			spline->Release();
			delete spline;
			splines.pop_back();
		}
	}
}

void Form1::ScalingTool_Action(System::String^ _action,cv::Point2i pos)
{
	if (System::String::Compare("click",_action)==0&&mp_AppItem->Data->WordArtData[0].splines.size()!=0)
	{				
		if (mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.size()==0)
		{	 
			AppAlgoTextTyping	text_typing;
			AppAlgoTextAlign	text_align;
			AppAlgoTextColor	text_color(mp_AppItem);
			text_color.Enable((int)mp_AppItem->Param->WordArt->ColorMode);
			QRWordArt::QRStringLines& splines = mp_AppItem->Data->WordArtData[0].splines;		
			for (int i = 0 ; i <splines.size(); i ++)
			{
				QRWordArt::QRStringLine* newspline=new QRStringLine;	
				splines[i]->Duplicate(HSSSpline::Sample(0,0),HSSSpline::Sample(splines[i]->n_segs()-1,1),newspline);
				newspline->Region()=splines[i]->Region();
				HSSSpline::Sample cursor(0,0);
				HSSSpline::Sample end(splines[i]->n_segs()-1,1);
				for(int j  = 0 ; j <splines[i]->GetWords().size(); j++)
				{
					HSSSpline::Samples samples;
					if (text_typing.Typing(splines[i]->GetWords()[j],*newspline,cursor,end,&cursor,true))
					{
						text_typing. Typing_Space(*newspline,cursor,end,&cursor);
						newspline->GetWordSamples().back()[0]->_IsSentenceStart=splines[i]->GetWordSamples()[j][0]->_IsSentenceStart;
						newspline->GetWordSamples().back()[0]->_IsSentenceEnd=splines[i]->GetWordSamples()[j][0]->_IsSentenceEnd;
						newspline->GetWordSamples().back()[0]->WordId=splines[i]->GetWordSamples()[j][0]->WordId;
						for (int w = 0 ; w<splines[i]->GetWordSamples()[j].size(); w++)
						{
							double r,g,b;
							splines[i]->GetWordSamples()[j][w]->qr_char->GetColor(&r,&g,&b);
							newspline->GetWordSamples().back()[w]->qr_char->SetColor(r,g,b);
						}
						
					}
					else
					{
						cout<<"fail"<<endl;
					}					
				}
				mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.push_back(newspline);
				if (i!=0)
				{
					newspline->LastLine(mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines[i-1]);
					mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines[i-1]->NextLine(newspline);
				}
				//text_align.Justify(*mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines[i]);
				//text_color.Execute(*mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines[i]);
			}
			mp_AppItem->Data->WordArtEdt.CanData.user_candidate.scaling_number=0;
		}

		//****要改成記入上一步非一開始的
		if (mp_AppItem->Data->WordArtEdt.temp_splines.empty())
		{
			//****未Clone
			mp_AppItem->Data->WordArtEdt.temp_splines.insert(mp_AppItem->Data->WordArtEdt.temp_splines.begin(),mp_AppItem->Data->WordArtData[0].splines.begin(),mp_AppItem->Data->WordArtData[0].splines.end());
		}
		HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
		cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());
		cv::Size cnvsSize = srcImg->size();
		cv::Rect cnvsRect(0, 0, cnvsSize.width, cnvsSize.height);
		srcItem->glContext->Make_Current();
		cv::Point2d imgpos= CoordCvt_Scr2Img(pos,cnvsRect);
		cout<<imgpos<<endl;
		AppAlgoTextBigScale algoObj_BuildBigScale;
		double min_dis=9999999;
		int select      = -1;
		int select_word = -1;
		QRWordArt::QRStringLines& user_splines = mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines;
		for (int i=0;i<user_splines.size()-mp_AppItem->Data->WordArtEdt.CanData.user_candidate.scaling_number;++i)
		{
			int wp=-1;
			double dis = user_splines[i]->SelectWord(imgpos.x,imgpos.y,&wp);
			if (wp!=-1 && dis<min_dis)
			{
				min_dis = dis;
				select = i;
				select_word=wp;
			}
		}
		cout<<"select line & word:"<<select<<" "<<select_word<<endl;
		if (select!=-1&&select_word!=-1)
		{
			if (algoObj_BuildBigScale.GenUserBigScale(mp_AppItem,select,select_word))
			{
				HKCMediaItem^ wordartItem;
				HKCImageProp^ wordartProp;
				cv::Mat transparent = cv::Mat(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0));
				mp_AppItem->Data->WordArtData[0].splines.clear();
				mp_AppItem->Data->WordArtEdt.is_scaling=true;
				mp_AppItem->Data->WordArtData[0].splines.insert(mp_AppItem->Data->WordArtData[0].splines.begin(),mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.begin(),mp_AppItem->Data->WordArtEdt.CanData.user_candidate.splines.end());
				
				if(mp_AppItem->FindCandidate("user define")==nullptr) 
				{					
					wordartItem = mp_AppItem->NewCandidate(transparent, "user define"  , mp_GLPanel);//Candidates
					wordartProp = (HKCImageProp^)wordartItem->Prop;
					wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
					wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
					wordartProp->Render->Visible = true;
				}
				
				mp_AppLayerMgr->BuildCandidate(this->CandidateLayer, mp_AppItem);
				this->ParamGrid->Refresh();
				GLPanel_Focus(mp_AppItem);
			}			
		}
	}
	else
	{
		cout<<"single scale fail"<<endl;
	}

	SeeLevelChange(2,true);
}

void Form1::ReadWordArt(System::String^ file)
{
	WordArt_Action("CLEAR");
	cv::Mat& segment_img = mp_AppItem->Data->WordArtEvi.segment_img;
	if(segment_img.rows==0 || segment_img.cols==0)
	{
		cout<<"Error: No Segment Image"<<endl;return;
	}

	std::cout<<"Loaded Word Art...\n";
	System::String^ fileExt = Path::GetExtension(file);
	QRWordArt::QRStringLines& splines=mp_AppItem->Data->WordArtData[0].splines;
	splines.clear();
	mp_AppItem->Data->IO_Handle.wordart_filename = std::string((const char*)(Marshal::StringToHGlobalAnsi(file)).ToPointer());
	splines = QRWordArt::IO::LoadWordArt((const char*)(Marshal::StringToHGlobalAnsi(file)).ToPointer());
	
	if (!splines.empty())
	{
		AppAlgoTextColor	text_color(mp_AppItem);
		text_color.Enable((int)mp_AppItem->Param->WordArt->ColorMode);
		//AppAlgoTextAlign text_align;
		for (int i=0;i<splines.size();i++)
		{
			//text_align.Justify(*splines[i]);			
			if (System::String::Compare(fileExt, ".wc") != 0){text_color.Execute(*splines[i]);}
		}
		HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
		cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());

		AppAlgoQRCodeEvaluation EnergyEvaluate;
		EnergyEvaluate.Execute(mp_AppItem);
		QRCInf_Action(QRcodeLabel,EnergyEvaluate);
		QRenergyBar->Value=1000*(EnergyEvaluate.QRcodeQuality());
		this->label2->Text=L"QR energy : 0."+ this->QRenergyBar->Value.ToString();

		HKCWordArtEvi& wordart_data = mp_AppItem->Data->WordArtEvi;
		cv::Mat transparent = cv::Mat(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0));
		HKCImageProp^ wordartProp;
		wordartProp=(HKCImageProp^)srcItem->Prop;
		wordartProp->Render->Visible = false;

		SeeLevelCheck1->Checked = false;
		SeeLevelCheck2->Checked = true;
		SeeLevelCheck3->Checked = false;
		UpdateMQRCLayers(false);
	}else{std::cout<<"Fail"<<'\n';}
}

void Form1::TextOrderOrien_Action(System::String^ _action,cv::Point2i pos)
{
	QRWordArt::QRStringLines& splines = mp_AppItem->Data->WordArtData[0].splines;	
	if (System::String::Compare("OrienClick",_action)==0&&mp_AppItem->Data->WordArtData[0].splines.size()!=0)
	{
		AppAlgoQRCodeEvaluation EnergyEvaluate;
		HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
		cv::Size cnvsSize = ((cv::Mat*)srcItem->Media->Data())->size();

		int region_select=-1;
		vector<cv::Mat>& region_segs  = this->mp_AppItem->Data->WordArtEvi.region_segs;
		for (int r = 0 ; r <region_segs.size();r++)
		{
			if (region_segs[r].data[(int)(cnvsSize.height-pos.y)* cnvsSize.height +(int)pos.x]!=0)
			{
				region_select=r;
				cout<<r<<endl;								 
				break;
			}
		}
		if (region_select!=-1)
		{
			vector<int >& adjustspline_id = mp_AppItem->Data->WordArtEdt.adjust_spline_id;
			for (int i = 0 ; i <splines.size(); i++)
			{
				if (splines[i]->Region()==region_select)
				{
					adjustspline_id.push_back(i);
					QRWordArt::QRStringLine* newspline = new QRWordArt::QRStringLine;
					HSSSpline::PathPoints<5> points =splines[i]->GetUniformSamplePoints(1);
					for (int j = points.size()-1 ; j>=0; j--)
					{
						newspline->PushBack(points[j]);
					}
					newspline->Fix()=splines[i]->Fix();
					newspline->Region()=splines[i]->Region();
					newspline->FittingCurve(0.1);
					newspline->RefittingCurve(0.05);
					splines[i]->Release();
					splines[i]=newspline;
					if (i!=0&&splines[i-1]->Region()==region_select)
					{
						splines[i-1]->NextLine(splines[i]);
						splines[i]->LastLine(splines[i-1]);
					}
				}
			}

			//-----------------------
			// Text Generation
			//-----------------------
			AppAlgoTextGeneration^ algoObj_TextGeneration = gcnew AppAlgoTextGeneration;
			algoObj_TextGeneration->TypeSet(mp_AppItem->Param->WordArt->TextType);
			algoObj_TextGeneration->TextGeneration(mp_AppItem,adjustspline_id,mp_AppItem->Data->WordArtEvi.candidate_strings);
		}
		
		EnergyEvaluate.Execute(mp_AppItem);
		QRCInf_Action(QRcodeLabel,EnergyEvaluate);
		QRenergyBar->Value=1000*(EnergyEvaluate.QRcodeQuality());
		this->label2->Text=L"QR energy : 0."+ this->QRenergyBar->Value.ToString();

		this->ParamGrid->Refresh();
		GLPanel_Focus(mp_AppItem);
	}
}

void Form1::TextChange_Action(System::String^ _action,int lineid,int charid,char c)
{
	QRWordArt::QRStringLines& splines = mp_AppItem->Data->WordArtData[0].splines;	
	if (System::String::Compare("TextChange",_action)==0&&lineid<splines.size())
	{
		double r,g,b;
		QRWordArt::QRStringLine::QRSample* c_sample = splines[lineid]->GetQRSamples()[charid];
		c_sample->qr_char->GetColor(&r,&g,&b);
		delete c_sample->qr_char;
		c_sample->qr_char = QRWordArt::QRCharacter::Instantiate(c,splines[lineid],splines[lineid]->GetQRSamples()[charid]->sample);
		c_sample->qr_char->SetColor(r,g,b);
	}
}

//1: QRcode Modules
//2: Word Art
//3: Energy
//4: Editing
//5: Text Order
void Form1::SeeLevelChange(int type,bool enable)
{
	if(mp_AppItem->Find("Background"))mp_AppItem->Find("Background")->Prop->Render->Visible       = true;
	if(mp_AppItem->Find("Editing"))mp_AppItem->Find("Editing")->Prop->Render->Visible             = false;
	switch(type)
	{
		case 1:
			SeeLevelCheck1->Checked = enable;
			if(mp_AppItem->Find("Background Modules"))mp_AppItem->Find("Background Modules")->Prop->Render->Visible = enable;
			if(mp_AppItem->Find("QR code info"))mp_AppItem->Find("QR code info")->Prop->Render->Visible				= enable;
			if(mp_AppItem->Find("Blending"))mp_AppItem->Find("Pattern")->Prop->Render->Visible			            = enable;
			break;
		case 2:
			SeeLevelCheck2->Checked = enable;
			if(mp_AppItem->Find("Word Art"))mp_AppItem->Find("Word Art")->Prop->Render->Visible = enable;
			break;
		case 3:
			SeeLevelCheck3->Checked = enable;
			if(mp_AppItem->Find("Energy"))mp_AppItem->Find("Energy")->Prop->Render->Visible			= enable;
			if(mp_AppItem->Find("CW Contour"))mp_AppItem->Find("CW Contour")->Prop->Render->Visible = enable;
			break;
		case 4:
			SeeLevelChange(1,false);
			SeeLevelChange(2,true);
			if(mp_AppItem->Find("Editing"))mp_AppItem->Find("Editing")->Prop->Render->Visible = enable;
			break;
		case 5:
			SeeLevelChange(1,false);
			SeeLevelChange(2,true);
			SeeLevelChange(3,false);
			if(mp_AppItem->Find("Editing"))mp_AppItem->Find("Editing")->Prop->Render->Visible = enable;
			break;
	}
	mp_GLPanel->Invalidate();

	/// Rebuild layers
	this->WordArtLayer->Invalidate();
	mp_AppLayerMgr->Build(this->LayerTree, mp_AppItem);
	this->ParamGrid->Refresh();

	//Centerize the media
	GLPanel_Focus(mp_AppItem);
}