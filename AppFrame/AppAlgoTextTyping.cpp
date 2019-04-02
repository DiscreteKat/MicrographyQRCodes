#include "StdAfx.h"
#include "AppAlgoTextTyping.h"
#include "AppAlgoProbabilityModule.h"
#include "AppAlgoModuleSelection.h"
#include "AppAlgoTextColor.h"
#include "QRWordArt/QRCharFBO.h"
#include "QRWordArt/QRCharacterIO.h"

AppAlgoTextTyping::AppAlgoTextTyping( void ){}

void AppAlgoTextTyping::Typing_Order( vector<std::string>& strings_data,QRWordArt::QRStringLine& spline,int& str_idx,bool cut_word)
{
	bool flag = true;
	
	HSSSpline::Sample cursor = spline.Cursor();
	HSSSpline::Sample end(spline.n_segs()-1,1);

	if (cursor.seg_idx!=0&&cursor._t!=0){flag = Typing_Space( spline, cursor, end, &cursor);}//非起始點補空白
	while (flag)
	{
		bool UseRemain = false;
		int idx = str_idx%(strings_data.size());
		std::string word;
		if (cut_word&&TextRemain.size()!=0)	{
			word = TextRemain; UseRemain = true;
			TextRemainId = idx-1;
		}
		else word = strings_data[idx];
		HSSSpline::Samples samples;
		int size = spline.GetWords().size();
		if (Typing(word,spline,cursor,end,&cursor,cut_word)){
			  if ((idx == strings_data.size()-1&&!UseRemain)||(idx == 0 && UseRemain))
			  {
				  spline.GetWordSamples().back()[0]->_IsSentenceEnd=false;
				  flag = Typing_Space(spline,cursor,end,&cursor,false);
			  }
			  else
			  {
				  flag = Typing_Space(spline,cursor,end,&cursor);			  
			  }
			  
		}else{flag = false;}

		if(spline.GetWords().size()>size)
		{
			if (!UseRemain)
			{
				str_idx++;		
				spline.GetWordSamples().back()[0]->WordId = idx;
			}
			else
				spline.GetWordSamples().back()[0]->WordId = TextRemainId;
			if (idx==0&&!UseRemain)
			{
				spline.GetWordSamples().back()[0]->_IsSentenceStart=true;
			}
			
		}
	}
	if(!cut_word)Typing_Fitting(strings_data,spline);//補字
	//else{  }
}

void AppAlgoTextTyping::Typing_Random( vector<std::string>& strings_data,QRWordArt::QRStringLine& spline, bool cut_word)
{
	bool flag = true;
	HSSSpline::Sample cursor = spline.Cursor();
	HSSSpline::Sample end(spline.n_segs()-1,1);

	if (cursor.seg_idx!=0&&cursor._t!=0){flag = Typing_Space( spline, cursor, end, &cursor);}

	while (flag)
	{
		int s_idx = rand()%(strings_data.size());
		std::string word = strings_data[s_idx];
		HSSSpline::Samples samples;
		if (Typing(word,spline,cursor,end,&cursor,cut_word)){
			  flag = Typing_Space(spline,cursor,end,&cursor);
		}else{flag = false;}
	}
	if(!cut_word)Typing_Fitting(strings_data,spline);//補字
}

void AppAlgoTextTyping::Typing_Fitting( vector<std::string>& strings_data,QRWordArt::QRStringLine& spline ,int id)
{
	std::sort(strings_data.begin(),strings_data.end());
	std::reverse(strings_data.begin(),strings_data.end());

	bool flag = true;
	HSSSpline::Sample cursor=spline.Cursor();
	HSSSpline::Sample end(spline.n_segs()-1,1);

	if (cursor.seg_idx!=0&&cursor._t!=0){flag = Typing_Space( spline, cursor, end, &cursor);}
	if (id!=-1)
	{
		HSSSpline::Samples samples;
		if (spline.TypeSetting(strings_data[id],&samples,cursor,end))
		{
			spline.AttachWord(strings_data[id],samples);
		}
	}
	flag = false;
	while (flag)
	{
		flag = false;
		for (int i=0;i<strings_data.size();i++)
		{
			HSSSpline::Samples samples;
			if (spline.TypeSetting(strings_data[i],&samples,cursor,end))
			{
				spline.AttachWord(strings_data[i],samples);
				break;
			}
		}
	}
}

void AppAlgoTextTyping::Typing_Energy(HKCAppItem^ _appItem,QRWordArt::QRStringLine& spline,bool cut_word)
{
	vector<std::string>& strings_data=_appItem->Data->WordArtEvi.candidate_strings;
	bool flag = true;
	HSSSpline::Sample cursor=spline.Cursor();
	HSSSpline::Sample end(spline.n_segs()-1,1);

	if (cursor.seg_idx!=0&&cursor._t!=0){flag = Typing_Space( spline, cursor, end, &cursor);}

	int bg_color=_appItem->Data->WordArtEvi.background_color;
	cv::Mat& foreground=_appItem->Data->WordArtEvi.qr_foreground_modules;
	cv::Mat& background=_appItem->Data->WordArtEvi.qr_background_modules;
	
	AppAlgoProbabilityModule ModuleEnergy(_appItem);
	AppAlgoModuleSelection ModuleLocated(_appItem);
	AppAlgoTextColor	text_color(_appItem);

	//cout<<"num "<<strings_data.size()<<endl;
	while (flag)
	{
		int s_idx ;
		double min_energy=1;
		double minid=0;
		vector<int> pids;
		for (s_idx = 0 ; s_idx < strings_data.size() ; s_idx++)
		{
			QRWordArt::QRCharacter::CharFBO charFBO;
			charFBO.Initialize(img_height,img_width);	
			double energy;
			HSSSpline::Sample c_cursor=cursor;
			QRWordArt::QRStringLine *new_spline=new QRWordArt::QRStringLine;
			spline.Duplicate(HSSSpline::Sample(0,0),HSSSpline::Sample(spline.n_segs()-1,1),new_spline);
			new_spline->Region()=spline.Region();
			std::string word = strings_data[s_idx];
			HSSSpline::Samples samples;
			if (Typing(word,*new_spline,c_cursor,end,&c_cursor,cut_word))
			{
				text_color.Execute(*new_spline);			
				for (int i = 0 ; i <new_spline->GetQRSamples().size();i++)
				{
					if (new_spline->GetQRSamples()[i]->qr_char!=NULL)
					{
						charFBO.Push(new_spline->GetQRSamples()[i]->qr_char);
					}
				}
				cv::Mat alpha;
				charFBO.Enable(QRWordArt::QRCharacter::CharFBO::BOUNDINGBOX);
				charFBO.SetBackground(1.0);
				charFBO.Draw(&alpha);
				cv::flip(alpha,alpha,0);	
				pids=ModuleLocated.SelectModule(alpha);
				//imshow("alpha",alpha);	
				charFBO.Enable(QRWordArt::QRCharacter::CharFBO::SOILD_COLOR);
				charFBO.SetBackground(bg_color);
				charFBO.Draw(&alpha);
				cv::flip(alpha,alpha,0);
				//imshow("alpha1",alpha);					
				energy=ModuleEnergy.Execute_Modules_Avg(alpha,pids);
				//cout<<pids<<endl;
				if (energy<min_energy)
				{
					min_energy=energy;
					minid=s_idx;
				}				
				flag=true;
			}else{
				flag = !flag;
			}
			charFBO.Clear();
			new_spline->Release();
			delete new_spline;
		}
		if (flag)
		{
			if (Typing(strings_data[minid],spline,cursor,end,&cursor,cut_word)){flag = Typing_Space(spline,cursor,end,&cursor);}
			else{flag = false;}
		}
	}
}

bool AppAlgoTextTyping::Typing( std::string& string, QRWordArt::QRStringLine& spline, HSSSpline::Sample from, HSSSpline::Sample to, HSSSpline::Sample* cursor,bool cut_word/*=false*/ )
{
	TextRemain.clear();
	HSSSpline::Samples samples;
	bool flag = true;
	if (spline.TypeSetting(string,&samples,from,to))
	{
		spline.AttachWord(string,samples);
		double offset = spline.Offset(string.back(),samples.back());
		flag = spline.ShiftSampleForeward(samples.back(),offset,cursor);	
	}else{
		if (cut_word && samples.size()>0)
		{
			std::string cut_string;
			for (int i=0;i<string.size();i++)
			{
				if (i<samples.size())
				{
					cut_string.push_back(string[i] );
				}
				else
				{
					TextRemain.push_back(string[i] );
				}
				
				
			}
			spline.AttachWord(cut_string,samples);
		}		
		cursor->seg_idx = spline.n_segs()-1;
		cursor->_t      = 1;
		flag = false;
	}	
	return flag;
}

bool AppAlgoTextTyping::R_Typing( std::string string, QRWordArt::QRStringLine& spline, HSSSpline::Sample from, HSSSpline::Sample to,HSSSpline::Sample* cursor, bool cut_word/*=false*/ )
{
	HSSSpline::Samples samples;

	bool flag = true;
	if (spline.R_TypeSetting(string,&samples,from,to))
	{
		spline.R_AttachWord(string,samples);
		double offset = spline.Offset(string.front(),samples.front());
		flag = spline.ShiftSampleBackward(samples.front(),offset,cursor);	
	}else{
		if (cut_word && samples.size()>0)
		{
			std::string cut_string;
			for (int i=0;i<samples.size();i++)
			{
				int idx = string.length()-i-1;
				cut_string.push_back(string[idx]);
			}
			std::reverse(cut_string.begin(),cut_string.end());
			spline.R_AttachWord(cut_string,samples);
		}		
		cursor->seg_idx = 0;
		cursor->_t = 0;
		flag = false;
	}	
	return flag;
}

bool AppAlgoTextTyping::Typing_Space( QRWordArt::QRStringLine& spline, HSSSpline::Sample from, HSSSpline::Sample to,HSSSpline::Sample* cursor ,bool IsEnd)
{
	bool flag = true;
	double offset = (QRWordArt::QRCharacter::WordSpacing + spline.WordSpace())*spline.get_w(*cursor);
	if (IsEnd)
	{
		offset=4*offset;
	}
	flag = spline.ShiftSampleForeward(*cursor,offset,cursor);
	return flag;
}

bool AppAlgoTextTyping::R_Typing_Space( QRWordArt::QRStringLine& spline, HSSSpline::Sample from, HSSSpline::Sample to,HSSSpline::Sample* cursor )
{
	bool flag = true;
	double offset = (QRWordArt::QRCharacter::WordSpacing + spline.WordSpace())*spline.get_w(*cursor);
	flag = spline.ShiftSampleBackward(*cursor,offset,cursor);
	return flag;
}