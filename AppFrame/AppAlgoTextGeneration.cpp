#include "stdafx.h"
#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"
#include "AppAlgoTextGeneration.h"

#include "AppAlgoTextTyping.h"
#include "AppAlgoTextAlign.h"
#include "AppAlgoTextColor.h"

#include "AppAlgoEnergyTextSpace.h"

#include <time.h>
#include <stdlib.h>

using namespace AppFrame;
using namespace HKCV;
using namespace HKUtils;

bool AppAlgoTextGeneration::Execute(HKCAppItem^ _appItem)
{
	std::cout<<"Text Generation..."<<std::endl;

	vector<std::string>&  candidate_strings = _appItem->Data->WordArtEvi.candidate_strings;
	vector<RegionCandidateData>&   region_splines    = _appItem->Data->WordArtEvi.region_splines;
	for (int r = 0 ;r<region_splines.size();r++ )
	{
		QRWordArt::QRStringLines& splines = _appItem->Data->WordArtEvi.region_splines[r].splines;
		TextGeneration(_appItem,splines,candidate_strings);
	}
	
	std::cout<<" process...Done"<<std::endl;
	return true;
}

void AppFrame::AppAlgoTextGeneration::TextGeneration( HKCAppItem^ _appItem, QRWordArt::QRStringLines& splines,vector<std::string>&  candidate_strings)
{
	AppAlgoTextTyping text_typing;
	HKCMediaItem^ srcItem = _appItem->Find("Source");
	cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());
	text_typing.img_height= srcImg->rows;
	text_typing.img_width = srcImg->cols;

	AppAlgoTextAlign  text_align;
	AppAlgoTextColor  text_color(_appItem);
	text_color.Enable((int)_appItem->Param->WordArt->ColorMode);

	int order = Text_Record_Order;
	for (int i=0;i<splines.size();i++)
	{
		
		while(splines[i]->GetWords().empty())
		{
			switch(m_TypeSet)
			{
			case 0:
				printf("\r Text Generating(random)...%d/%d                                ",i,splines.size());
				text_typing.Typing_Random(candidate_strings,*splines[i],m_CutWord);
				break;
			case 1:
				printf("\r Text Generating(order)...%d/%d                                ",i,splines.size());
				text_typing.Typing_Order(candidate_strings,*splines[i],order,m_CutWord);
				break;
			case 2:
				printf("\r Text Generating(energy)...%d/%d                                ",i,splines.size());
				text_typing.Typing_Energy(_appItem,*splines[i],!m_CutWord);
				break;
			}
			if(splines[i]->GetWords().empty()){splines[i]->Scale(0.9);}//無法產生字，縮小spline
		}

		text_align.Justify(*splines[i]);
		text_color.Execute(*splines[i]);
	}
	if(!_appItem->Data->IO_Handle.article_loaded) Text_Record_Order = order;
	printf("\r                                                                      ");
	printf("\r");
}

void AppFrame::AppAlgoTextGeneration::TextGeneration( HKCAppItem^ _appItem, std::vector<int>& splines_idx, vector<std::string>& candidate_strings )
{
	QRWordArt::QRStringLines& splines = _appItem->Data->WordArtData[0].splines;
	if (_appItem->Data->IO_Handle.article_loaded)
	{
		splines_idx.clear();
		for (int i = 0 ; i <splines.size();i++){splines_idx.push_back(i);}
	}

	QRWordArt::QRStringLines target_splines;
	for (int i=0;i<splines_idx.size();i++)
	{
		int idx = splines_idx[i];
		splines[idx]->Release();
		target_splines.push_back(splines[idx]);
	}

	TextGeneration(_appItem,target_splines,candidate_strings);
	splines_idx.clear();
}