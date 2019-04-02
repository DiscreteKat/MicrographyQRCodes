#include "StdAfx.h"
#include "AppAlgoTextAlign.h"
#include "QRWordArt/QRCharacterIO.h"

void AppAlgoTextAlign::Justify(QRWordArt::QRStringLine& spline )
{
	HSSSpline::Sample from(0,0);
	HSSSpline::Sample to(spline.n_segs()-1,1);
	Left(spline,from,to);
	Justify(spline,from,to);
}

void AppAlgoTextAlign::Justify( QRWordArt::QRStringLine& spline,HSSSpline::Sample from,HSSSpline::Sample to )
{
	QRWordArt::QRStringLine::WordSamples w_samples = spline.GetWordSamples();
	if (w_samples.empty()){return;}

	std::string str = spline.GetString();
	int num_char=0, num_space=0;
	for (int i=0;i<str.length();i++)
	{
		if (str[i]==' '){num_space++;}
		else{num_char++;}
	}
	if (num_char<=1){return;}

	if (spline.Remainfront()-spline.BeginToSampleLenght(from) > 0){Left(spline,from,to);}

	double avg_w  = spline.AvgW();
	double remain = spline.Remain()-spline.SampleToEndLenght(to);
	double offside_letter = 0, offside_space  = 0;
	if (num_space==0)
	{
		offside_letter = remain / avg_w / (double)(num_char-1);
	}else{
		double w = 0.3;
		offside_letter =    w  * remain / avg_w / (double)(num_char-num_space-1);
		offside_space  = (1-w) * remain / avg_w / (double)(num_space);
	}

	for(double i=10.0;i>0;i-=0.1)
	{
		bool flag = false;
		flag = Extend(spline,w_samples,str,from,to,offside_space*i,offside_letter*i);
		if (flag){break;}
	}
}

void AppAlgoTextAlign::Right(QRWordArt::QRStringLine& spline )
{
	Right(spline, HSSSpline::Sample(spline.n_segs()-1,1), HSSSpline::Sample(0,0));
}

void AppAlgoTextAlign::Right( QRWordArt::QRStringLine& spline,HSSSpline::Sample from,HSSSpline::Sample to )
{
	QRWordArt::QRStringLine::WordSamples w_samples = spline.GetWordSamples();
	if (w_samples.empty())return;

	std::string str = spline.GetString();

	HSSSpline::Samples new_samples;
	if (spline.R_TypeSetting(str,&new_samples,from,to))
	{
		HSSSpline::Samples::iterator sp_it = new_samples.begin();
		for (int i=0,k=0;i<w_samples.size();i++,k++)
		{
			for (int j=0;j<w_samples[i].size();j++,k++){spline.MoveQRSample(w_samples[i][j],new_samples[k]);}
		}
	}
}

void AppAlgoTextAlign::Left(QRWordArt::QRStringLine& spline )
{
	Left(spline,HSSSpline::Sample(0,0),HSSSpline::Sample(spline.n_segs()-1,1));
}

void AppAlgoTextAlign::Left( QRWordArt::QRStringLine& spline,HSSSpline::Sample from,HSSSpline::Sample to )
{
	QRWordArt::QRStringLine::WordSamples w_samples = spline.GetWordSamples();
	if (w_samples.empty())return;

	std::string str = spline.GetString();
	HSSSpline::Samples new_samples;
	if (spline.TypeSetting(str,&new_samples,from,to))
	{
		//cout<<endl<<str<<" "<<new_samples.size()<<endl;
		HSSSpline::Samples::iterator sp_it = new_samples.begin();
		for (int i=0,k=0;i<w_samples.size();i++,k++)
		{
			for (int j=0;j<w_samples[i].size();j++,k++)
			{
				spline.MoveQRSample(w_samples[i][j],new_samples[k]);
			}
		}
	}
}

bool AppAlgoTextAlign::Extend( QRWordArt::QRStringLine& spline,QRWordArt::QRStringLine::WordSamples& w_samples,std::string all_text,HSSSpline::Sample from,HSSSpline::Sample to,double word_space,double letter_space )
{
	double temp_word = spline.WordSpace();
	double temp_letter = spline.WordSpace();

	spline.WordSpace()  +=word_space;
	spline.LetterSpace()+=letter_space;
	int all_textsize = all_text.size();
	for (int i = 0 ; i < w_samples.size() ; i++)
	{
		if (w_samples[i][0]->_IsSentenceEnd)
		{
			all_textsize-=3;
		}
	}
	HSSSpline::Samples new_samples;
	new_samples.clear();
	if (spline.TypeSetting(all_text,&new_samples,from,to))
	{
		if (new_samples.size()!=all_textsize)
		{
			spline.WordSpace()=temp_word;
			spline.LetterSpace()=temp_letter;
			return false;
		}else{
			for (int i=0,k=0;i<w_samples.size();i++,k++)
			{
				for (int j=0;j<w_samples[i].size();j++,k++)
				{spline.MoveQRSample(w_samples[i][j],new_samples[k]);}
			}
			return true;
		}
	}else{
		spline.WordSpace()=temp_word;
		spline.LetterSpace()=temp_letter;
		return false;
	}
}
