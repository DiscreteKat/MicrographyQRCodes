#pragma once

#include "QRWordArt/QRStringLine.h"

public class AppAlgoTextAlign
{
	public:
		void Left   (QRWordArt::QRStringLine& spline);
		void Left   (QRWordArt::QRStringLine& spline,HSSSpline::Sample from,HSSSpline::Sample to);
		void Right  (QRWordArt::QRStringLine& spline);
		void Right  (QRWordArt::QRStringLine& spline,HSSSpline::Sample from,HSSSpline::Sample to);//from為右邊起點
		void Justify(QRWordArt::QRStringLine& spline);
		void Justify(QRWordArt::QRStringLine& spline,HSSSpline::Sample from,HSSSpline::Sample to);
	private:
		bool Extend(QRWordArt::QRStringLine& spline,QRWordArt::QRStringLine::WordSamples& w_samples,std::string all_text,HSSSpline::Sample from,HSSSpline::Sample to,double word_space,double letter_space);
};