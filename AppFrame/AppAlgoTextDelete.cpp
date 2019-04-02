#include "StdAfx.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "AppAlgoTextDelete.h"
#include "AppAlgoTextColor.h"
#include "AppAlgoTextAlign.h"

bool AppFrame::AppAlgoTextDelete::Execute( HKCAppItem^ _appItem )
{
	AppAlgoTextAlign text_align;
	AppAlgoTextColor	text_color(_appItem);
	text_color.Enable((int)_appItem->Param->WordArt->ColorMode);
	int word_art_idx =  _appItem->Data->CurrentWordArtID;
	QRWordArt::QRStringLines& strings = _appItem->Data->WordArtData[word_art_idx].splines;

	std::vector<int> random;
	for (int sp_id = 0;sp_id<strings.size();sp_id++){random.push_back(sp_id);}
	srand(0);
	for (int i=0;i<random.size();i++)
	{
		int idx		= (int)(pow(13.0,double(i+1)))%random.size();
		int temp	= random[i];
		random[i]	= random[idx];
		random[idx] = temp;
	}

	int delete_num = 1;
	double percent = DPercent;
	for (int idx = 0;idx<strings.size()*percent;idx++)
	{
		int sp_id = random[idx];
		QRWordArt::QRStringLine::WordSamples w_sample = strings[sp_id]->GetWordSamples();

		if (w_sample.size()==1&&w_sample[0].size()<=2)continue;

		for (int i=0;i<delete_num;i++)
		{
			w_sample.back().pop_back();
			if (w_sample.back().empty()){w_sample.pop_back();}
		}
		std::vector<std::string> words;
		std::vector<std::vector<HSSSpline::Sample>> word_sample;
		for (int i=0;i<w_sample.size();i++)
		{
			std::string word;
			std::vector<HSSSpline::Sample> samples;
			for (int j=0;j<w_sample[i].size();j++)
			{
				word += w_sample[i][j]->_char;
				samples.push_back(w_sample[i][j]->sample);
			}
			words.push_back(word);
			word_sample.push_back(samples);
		}
		strings[sp_id]->Release();
		for (int i=0;i<words.size();i++)
		{
			strings[sp_id]->AttachWord(words[i],word_sample[i]);
		}
		text_align.Justify(*strings[sp_id]);
		text_color.Execute(*strings[sp_id]);
	}
	return true;
}