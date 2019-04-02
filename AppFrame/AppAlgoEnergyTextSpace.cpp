#include "StdAfx.h"
#include "AppAlgoEnergyTextSpace.h"
#include "QRWordArt/QRCharacterIO.h"

AppAlgoEnergyTextSpace::AppAlgoEnergyTextSpace(void)
{
}


AppAlgoEnergyTextSpace::~AppAlgoEnergyTextSpace(void)
{
}

double AppAlgoEnergyTextSpace::E_Letter_Space( QRWordArt::QRStringLine& spline )
{
	QRWordArt::QRStringLine::WordSamples word = spline.GetWordSamples();
	if (word.empty())return 0;
	
	std::vector<double> error;
	for (int i=0;i<word.size();i++)
	{
		double from=-1,end=-1;
		for (int j=0;j<word[i].size()-1;j++)
		{
			if (word[i][j]->qr_char==NULL || word[i][j+1]->qr_char==NULL )
			{
				from=-1; end=-1;
				continue;
			}

			double next_from = 0;
			if(from==-1){ word[i][j]  ->qr_char->GetBoundU(&from,NULL);}
			if(end ==-1){ word[i][j+1]->qr_char->GetBoundU(&next_from,&end);}
			double size  = (spline.get_w(word[i][j]->sample)+spline.get_w(word[i][j+1]->sample))*0.5;
			double space = (end - from)/size;

			double standard;
			standard = QRWordArt::QRCharacter::GetBackSpace(word[i][j]->_char) + QRWordArt::QRCharacter::GetBearingX(word[i][j+1]->_char);

			error.push_back(abs(space-standard));

			from = next_from;
			end = -1;
		}
	}

	double energy = 1-Gaussion(AVG(error),QRWordArt::QRCharacter::LetterSpacing);
	return energy;
}

double AppAlgoEnergyTextSpace::E_Word_Space( QRWordArt::QRStringLine& spline)
{
	QRWordArt::QRStringLine::WordSamples word = spline.GetWordSamples();
	if (word.size()<=1)return 0;

	std::vector<double> all_space;
	all_space.resize(word.size()-1);

	for (int i=0;i<word.size()-1;i++)
	{
		if (word[i].back()->qr_char==NULL || word[i+1].front()->qr_char==NULL ||word[i].front()->_IsSentenceEnd)continue;

		double from,end;
		word[i].back()   ->qr_char->GetBoundU(&from , NULL);
		word[i+1].front()->qr_char->GetBoundU(NULL  ,&end);
		double size  = (spline.get_w(word[i].back()->sample)+spline.get_w(word[i+1].front()->sample))*0.5;
		double space = (end - from)/size;
		all_space[i] = space;
	}

	double avg = AVG(all_space);
	double word_spacing = QRWordArt::QRCharacter::WordSpacing;
	double energy = 1-Gaussion(avg-word_spacing,word_spacing);
	return energy;
}

double AppAlgoEnergyTextSpace::Gaussion( double x,double a ){return exp(-(x*x)/(2*(a*a)));}

double AppAlgoEnergyTextSpace::AVG( std::vector<double>& set )
{
	if (set.empty())return 0;
	double sum = 0;
	for (unsigned int i=0; i<set.size(); i++){sum += set[i];}
	return sum/set.size();
}

double AppAlgoEnergyTextSpace::STD( std::vector<double>& set )
{
	if (set.empty())return 0;
	double u = AVG(set);
	double sum = 0;
	for (unsigned int i=0; i<set.size(); i++){sum += pow(set[i]-u,2.0);}
	return sqrt(sum/set.size());
}