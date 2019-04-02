#pragma once
#include "QRWordArt/QRStringLine.h"

class AppAlgoTextTyping
{
public:
	AppAlgoTextTyping(void);
public:
	//¶K¿é¤J¦r¦ê¡A¦^¶Ç¯à§_¶K¤W¥h
	//¸m¥ª
	bool Typing(std::string& string, QRWordArt::QRStringLine& spline, HSSSpline::Sample from, HSSSpline::Sample to,
		        HSSSpline::Sample* cursor,bool cut_word=false);  //"´å¼Ð¦ì¸m"
	bool Typing_Space(QRWordArt::QRStringLine& spline, HSSSpline::Sample from, HSSSpline::Sample to,
		        HSSSpline::Sample* cursor, bool IsEnd= false);	 //"´å¼Ð¦ì¸m"
	//¸m¥k
	bool R_Typing(std::string string, QRWordArt::QRStringLine& spline, HSSSpline::Sample from, HSSSpline::Sample to,
		        HSSSpline::Sample* cursor,bool cut_word=false);  //"´å¼Ð¦ì¸m"
	bool R_Typing_Space(QRWordArt::QRStringLine& spline, HSSSpline::Sample from, HSSSpline::Sample to,
		        HSSSpline::Sample* cursor);	 //"´å¼Ð¦ì¸m"

	//¿ï¾Ü¶K¿é¤J¦r¦ê
	void Typing_Order(vector<std::string>& strings_data,QRWordArt::QRStringLine& spline,int& from,bool cut_word=false);
	void Typing_Random(vector<std::string>& strings_data,QRWordArt::QRStringLine& spline,bool cut_word=false);
	void Typing_Energy(HKCAppItem^ _appItem,QRWordArt::QRStringLine& spline,bool cut_word=false);
	void Typing_Fitting(vector<std::string>& strings_data,QRWordArt::QRStringLine& spline , int id = -1 );

	string TextRemain;
	int TextRemainId;
	int img_height;
	int img_width;
};