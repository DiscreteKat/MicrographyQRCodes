#include "StdAfx.h"
#include "AppAlgoQRCodeRenderer.h"
#include "QRWordArt/QRCharFBO.h"
#include "QRWordArt/QRPatternFBO.h"
#include "QRWordArt/QRStringLine.h"

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"

AppAlgoQRCodeRenderer::AppAlgoQRCodeRenderer(void){}

AppAlgoQRCodeRenderer::~AppAlgoQRCodeRenderer(void){}

void AppAlgoQRCodeRenderer::GenResult( HKCAppItem^ _appItem,cv::Mat* dst )
{
	cv::Point2d offset = _appItem->Data->QRCData.offset;
	int w = _appItem->Data->QRCData.QRCImg.cols;
	int h = _appItem->Data->QRCData.QRCImg.rows;
	int bg_color =  _appItem->Data->WordArtEvi.background_color;
	int word_art_idx =  _appItem->Data->CurrentWordArtID;
	cv::Rect clipping(offset.x,offset.y,w,h);
	QRWordArt::QRStringLines& spline = _appItem->Data->WordArtData[word_art_idx].splines;
	cv::Mat& foreground     = _appItem->Data->WordArtEvi.qr_foreground_modules;
	cv::Mat& background     = _appItem->Data->WordArtEvi.qr_background_modules;

	cv::Mat& blend  = _appItem->Data->WordArtData[word_art_idx].naive_combine;
	// cv::Mat& blend  = _appItem->Data->WordArtData[word_art_idx].pixel_blending;
	// cv::Mat blend;GenPatternMap(_appItem,&blend);

	cv::Mat word_map;
	GenWordMap(_appItem,&word_map);
	//cv::imshow("word_map",word_map);cv::waitKey();
	word_map(clipping).copyTo(word_map);

	Combine(word_map,blend,background,foreground,bg_color,dst);
}

void AppAlgoQRCodeRenderer::Combine( cv::Mat& word, /*¦r */ cv::Mat& pattern, /*module blending */ cv::Mat& background, /*qr code ­I´º */ cv::Mat& foreground, /*qr code «e´º */ int bg_color, cv::Mat* dst )
{
	//cv::imshow("word",word);
	//cv::imshow("pattern",pattern);
	//cv::imshow("background",background);
	//cv::imshow("foreground",foreground);
	//cv::waitKey();
	dst->create(word.rows,word.cols,CV_8UC3);
	for (int i=0; i<word.rows*word.cols; i++)
	{
		dst->data[i*3  ] = bg_color;
		dst->data[i*3+1] = bg_color;
		dst->data[i*3+2] = bg_color;

		dst->data[i*3  ] = dst->data[i*3  ]*(1-background.data[i*4+3]/255.0)+background.data[i*4  ]*(background.data[i*4+3]/255.0);
		dst->data[i*3+1] = dst->data[i*3+1]*(1-background.data[i*4+3]/255.0)+background.data[i*4+1]*(background.data[i*4+3]/255.0);
		dst->data[i*3+2] = dst->data[i*3+2]*(1-background.data[i*4+3]/255.0)+background.data[i*4+2]*(background.data[i*4+3]/255.0);

		dst->data[i*3  ] = dst->data[i*3  ]*(1-word.data[i*4+3]/255.0)+word.data[i*4  ]*(word.data[i*4+3]/255.0);
		dst->data[i*3+1] = dst->data[i*3+1]*(1-word.data[i*4+3]/255.0)+word.data[i*4+1]*(word.data[i*4+3]/255.0);
		dst->data[i*3+2] = dst->data[i*3+2]*(1-word.data[i*4+3]/255.0)+word.data[i*4+2]*(word.data[i*4+3]/255.0);

		dst->data[i*3  ] = dst->data[i*3  ]*(1-pattern.data[i*4+3]/255.0)+pattern.data[i*4  ]*(pattern.data[i*4+3]/255.0);
		dst->data[i*3+1] = dst->data[i*3+1]*(1-pattern.data[i*4+3]/255.0)+pattern.data[i*4+1]*(pattern.data[i*4+3]/255.0);
		dst->data[i*3+2] = dst->data[i*3+2]*(1-pattern.data[i*4+3]/255.0)+pattern.data[i*4+2]*(pattern.data[i*4+3]/255.0);

		dst->data[i*3  ] = dst->data[i*3  ]*(1-foreground.data[i*4+3]/255.0)+foreground.data[i*4  ]*(foreground.data[i*4+3]/255.0);
		dst->data[i*3+1] = dst->data[i*3+1]*(1-foreground.data[i*4+3]/255.0)+foreground.data[i*4+1]*(foreground.data[i*4+3]/255.0);
		dst->data[i*3+2] = dst->data[i*3+2]*(1-foreground.data[i*4+3]/255.0)+foreground.data[i*4+2]*(foreground.data[i*4+3]/255.0);
	}
}

void AppAlgoQRCodeRenderer::GenWordMap( HKCAppItem^ _appItem,cv::Mat* dst )
{
	int w = _appItem->Data->WordArtEvi.segment_img.cols;
	int h = _appItem->Data->WordArtEvi.segment_img.rows;

	int word_art_idx =  _appItem->Data->CurrentWordArtID;
	QRWordArt::QRStringLines& spline = _appItem->Data->WordArtData[word_art_idx].splines;

	int bg_color =  _appItem->Data->WordArtEvi.background_color;

	QRWordArt::QRCharacter::CharFBO fbo;
	fbo.Initialize(w,h);

	for (int sp_id=0;sp_id<spline.size();sp_id++)
	{
		for (int c_id=0;c_id<spline[sp_id]->size();c_id++)
		{
			QRWordArt::QRCharacter::Char* qr_char = (*spline[sp_id])[c_id].qr_char;
			if (qr_char != NULL){fbo.Push(qr_char);}
		}
	}

	cv::Mat alpha;
	fbo.Draw(&alpha);
	cv::flip(alpha,alpha,0);

	cv::Mat word;
	fbo.Enable(QRWordArt::QRCharacter::CharFBO::SOILD_COLOR);
	fbo.SetBackground(bg_color/255.0);
	fbo.Draw(&word);
	cv::flip(word,word,0);

	dst->create(w,h,CV_8UC4);
	for (int i=0; i<w*h; i++)
	{
		dst->data[i*4  ] =   word.data[i*3  ];
		dst->data[i*4+1] =   word.data[i*3+1];
		dst->data[i*4+2] =   word.data[i*3+2];
		dst->data[i*4+3] =   255-alpha.data[i*3];
	}
}

void AppAlgoQRCodeRenderer::AddQuietZone( cv::Mat& result,cv::Mat* dst )
{
	int padding = 50;
	cv::Mat quiet_zone = cv::Mat(result.cols+padding*2,result.rows+padding*2,CV_8UC3,cv::Scalar(255,255,255));
	for (int i=0;i<result.rows;i++)
	{
		for (int j=0;j<result.cols;j++)
		{
			int idx1 = (i+padding)*quiet_zone.cols+j+padding;
			int idx2 = i*result.cols+j;

			quiet_zone.data[idx1*3  ] = result.data[idx2*3  ] ;
			quiet_zone.data[idx1*3+1] = result.data[idx2*3+1] ;
			quiet_zone.data[idx1*3+2] = result.data[idx2*3+2] ;
		}
	}
	*dst = quiet_zone.clone();
}

void AppAlgoQRCodeRenderer::GenPatternMap( HKCAppItem^ _appItem,cv::Mat* dst )
{
	int w = _appItem->Data->QRCData.QRCImg.cols;
	int h = _appItem->Data->QRCData.QRCImg.rows;

	int word_art_idx =  _appItem->Data->CurrentWordArtID;
	QRWordArt::QRPatterns& patterns = _appItem->Data->WordArtData[word_art_idx].pattern_blending;
	int bg_color =  _appItem->Data->WordArtEvi.background_color;

	QRWordArt::QRPatternFBO fbo;
	fbo.Initialize(w,h);

	for (int i=0;i<patterns.size();i++){fbo.Push(patterns[i]);}

	cv::Mat alpha;
	fbo.Draw(&alpha);
	cv::flip(alpha,alpha,0);

	cv::Mat pattern;
	fbo.Enable(QRWordArt::QRPatternFBO::SOILD_COLOR);
	fbo.SetBackground(bg_color/255.0);
	fbo.Draw(&pattern);
	cv::flip(pattern,pattern,0);

	dst->create(w,h,CV_8UC4);
	for (int i=0; i<w*h; i++)
	{
		dst->data[i*4  ] =   pattern.data[i*3  ];
		dst->data[i*4+1] =   pattern.data[i*3+1];
		dst->data[i*4+2] =   pattern.data[i*3+2];
		dst->data[i*4+3] =   255-alpha.data[i*3];
	}
}

void AppAlgoQRCodeRenderer::DrawModule1( cv::Point& posn, int grayscale, int size,cv::Mat* dst )
{
	for (int i=-size*0.5; i<size*0.5; ++i)
	{
		for (int j=-size*0.5; j<size*0.5; ++j)
		{
			if (posn.y+i<0 || posn.y+i>=dst->rows || posn.x+j<0 || posn.x+j>=dst->cols ){continue;}
			int idx = (posn.y+i)*dst->cols+(posn.x+j);
			dst->data[idx] = grayscale; 
		}
	}
}

void AppAlgoQRCodeRenderer::DrawModule3( cv::Point& posn, int r,int g,int b, int size,cv::Mat* dst )
{
	for (int i=-size*0.5; i<size*0.5; ++i)
	{
		for (int j=-size*0.5; j<size*0.5; ++j)
		{
			if (posn.y+i<0 || posn.y+i>=dst->rows || posn.x+j<0 || posn.x+j>=dst->cols ){continue;}
			int idx = (posn.y+i)*dst->cols+(posn.x+j);
			dst->data[idx*3  ] = b; 
			dst->data[idx*3+1] = g; 
			dst->data[idx*3+2] = r; 
		}
	}
}

void AppAlgoQRCodeRenderer::DrawModule4( cv::Point& posn, int r,int g,int b,int alpha, int size,cv::Mat* dst )
{
	for (int i=-size*0.5; i<size*0.5; ++i)
	{
		for (int j=-size*0.5; j<size*0.5; ++j)
		{
			if (posn.y+i<0 || posn.y+i>=dst->rows || posn.x+j<0 || posn.x+j>=dst->cols ){continue;}
			int idx = (posn.y+i)*dst->cols+(posn.x+j);
			dst->data[idx*4  ] = b; 
			dst->data[idx*4+1] = g; 
			dst->data[idx*4+2] = r; 
			dst->data[idx*4+3] = alpha; 
		}
	}
}
