#pragma once
class AppAlgoQRCodeRenderer
{
public:
	AppAlgoQRCodeRenderer(void);
	~AppAlgoQRCodeRenderer(void);
public:
	static void GenResult(HKCAppItem^ _appItem,cv::Mat* dst);
	static void AddQuietZone(cv::Mat& result,cv::Mat* dst);
	static void GenWordMap(HKCAppItem^ _appItem,cv::Mat* dst);
	static void GenPatternMap(HKCAppItem^ _appItem,cv::Mat* dst);
	static void Combine(cv::Mat& word,       //¦r
						cv::Mat& pattern,    //module blending
						cv::Mat& background, //qr code ­I´º
						cv::Mat& foreground, //qr code «e´º
						int bg_color,
						cv::Mat* dst);

	static void DrawModule1(cv::Point& posn, int grayscale, int size,cv::Mat* dst);
	static void DrawModule3(cv::Point& posn, int r,int g,int b, int size,cv::Mat* dst);
	static void DrawModule4(cv::Point& posn, int r,int g,int b,int alpha, int size,cv::Mat* dst);
};