#include "StdAfx.h"
#include "AppAlgoTextColor.h"

#include "QRWordArt/QRCharFBO.h"
static int colorTableNum = 18;
static cv::Point3f colorTable[18] ={
	
	cv::Point3f(0.122  ,0.467  ,0.716  ),
	cv::Point3f(0.682  ,0.78   ,0.91   ),
	cv::Point3f(1.0    ,0.498  ,0.055  ),
	cv::Point3f(1.0    ,0.733  ,0.471  ),
	cv::Point3f(0.173  ,0.627  ,0.173  ),
	cv::Point3f(0.596  ,0.875  ,0.541  ),
	cv::Point3f(0.839  ,0.153  ,0.157  ),
	cv::Point3f(1.0    ,0.596  ,0.588  ),
	cv::Point3f(0.58   ,0.404  ,0.741  ),
	cv::Point3f(0.773  ,0.690  ,0.835  ),
	cv::Point3f(0.549  ,0.337  ,0.294  ),
	cv::Point3f(0.769  ,0.612  ,0.58   ),
	cv::Point3f(0.89   ,0.467  ,0.761  ),
	cv::Point3f(0.949  ,0.714  ,0.824  ),
	cv::Point3f(0.737  ,0.741  ,0.013  ),
	cv::Point3f(0.859  ,0.859  ,0.553  ),
	cv::Point3f(0.09   ,0.745  ,0.812  ),
	cv::Point3f(0.62   ,0.855  ,0.898  )


/*	cv::Point3f(0      ,1      ,0.804  ),
	cv::Point3f(0.58   ,0.067  ,1      ),
	cv::Point3f(1      ,0.961  ,0      ),
	cv::Point3f(1      ,0.392  ,0      )*/
/*	cv::Point3f(0.4    ,0.337  ,0.102  ),
	cv::Point3f(0.165  ,0.345  ,0.086  ),
	cv::Point3f(0.118  ,0.098  ,0.278  ),
	cv::Point3f(0.376  ,0.094  ,0.145  )*/
};

AppAlgoTextColor::AppAlgoTextColor( HKCAppItem^ _appItem ):m_Color_Mode(COLOR_SAMPLE_WORD),m_Sample_Quality(FAST_SAMPLE)
{
	color_id=0;
	HKCMediaItem^ srcItem = _appItem->Find("Source");
	m_SrcImg = ((cv::Mat*)(srcItem->Media->Data()));
	m_SegImg = &_appItem->Data->WordArtEvi.segment_img;

	m_FBO.Initialize(m_SrcImg->cols,m_SrcImg->rows);
}

AppAlgoTextColor::AppAlgoTextColor( cv::Mat& src,cv::Mat& seg ):m_Color_Mode(COLOR_SAMPLE_WORD),m_Sample_Quality(FAST_SAMPLE)
{
	color_id=0;
	m_SrcImg = &src;
	m_SegImg = &seg;

	m_FBO.Initialize(src.cols,src.rows);
}

void AppAlgoTextColor::Execute( QRWordArt::QRStringLine& spline)
{
	if (m_Color_Mode == COLOR_ALPHA)
	{
		for (int i=0; i<spline.size(); i++)
		{
			if(spline[i].qr_char != NULL){spline[i].qr_char->SetColor(1.0,1.0,1.0);}
		}
	}else if (m_Color_Mode == COLOR_SENTENCE)
	{
		AssignColorTable(spline);
	}
	else{
		if (m_Sample_Quality == PERFECT_SAMPLE){AssignColor(spline);}
		else{AssignColor_Fast(spline);}
	}
}

bool AppAlgoTextColor::GetMeshColor( cv::Mat& src_img,cv::Mat& seg_img, QRWordArt::QRCharacter::Char* qr_char, cv::Point3f* color )
{
	cv::Mat map;
	m_FBO.Push(qr_char);
	m_FBO.Draw(&map);
	m_FBO.Pop();
	cv::flip(map,map,0);
	map.convertTo(map, CV_32FC1, 1.0f/255.0f);

	///***
	double left,right,top,bottom;
	left   = 0;
	bottom = 0;
	right  = src_img.cols;
	top    = src_img.rows;
	//qr_char->BoundingBox(&left,&right,&top,&bottom);

	color->x = 0;color->y = 0;color->z = 0;
	double k = 0;
	for (int i=bottom;i<top;i++)
	{
		for (int j=left;j<right;j++)
		{
			int idx = i*src_img.cols+j;
			if (!((float*)map.data)[idx*3] && seg_img.data[idx]!=255)
			{
				color->x += (double)src_img.data[idx*3+2]/ 255.0;
				color->y += (double)src_img.data[idx*3+1]/ 255.0;
				color->z += (double)src_img.data[idx*3  ]/ 255.0;
				k++;
			}
		}
	}

	if (k>0)
	{
		color->x=color->x / k ;
		color->y=color->y / k ;
		color->z=color->z / k ;
		return true;
	}else{
		return false;
	}
}

bool AppAlgoTextColor::GetPosnColor( cv::Mat& src_img, cv::Point2f& posn,cv::Mat& seg_img, cv::Point3f* color )
{
	if(posn.x>=src_img.cols || posn.x<0)return false;
	if(posn.y>=src_img.rows || posn.y<0)return false;

	int idx = (int)posn.y*src_img.cols + (int)posn.x;
	if (seg_img.data[idx]==0 && posn.x<src_img.cols && posn.y<src_img.rows)
	{
		color->x = (double)src_img.data[idx*3+2]/ 255.0;
		color->y = (double)src_img.data[idx*3+1]/ 255.0;
		color->z = (double)src_img.data[idx*3  ]/ 255.0;
		return true;
	}else{
		return false;
	}
}

void AppAlgoTextColor::AssignColor( QRWordArt::QRStringLine& spline )
{
	QRWordArt::QRStringLine::WordSamples w_samples = spline.GetWordSamples();
	cout<<m_Color_Mode<<endl;
	for (int w_id=0;w_id<w_samples.size();w_id++)
	{		
		cv::Point3f word_color(0,0,0);
		int k=0;
		for(int c_id=0;c_id<w_samples[w_id].size();c_id++)
		{
			QRWordArt::QRCharacter::Char* qr_char = w_samples[w_id][c_id]->qr_char;
			if (qr_char==NULL){continue;}

			cv::Point3f color;
			cv::Point2f posn(spline.get_x(w_samples[w_id][c_id]->sample),spline.get_y(w_samples[w_id][c_id]->sample));
			if(GetMeshColor(*m_SrcImg,*m_SegImg,qr_char,&color))
			{
				k++;
				word_color += color;
			}
			else 
				if(GetPosnColor(*m_SrcImg,posn,*m_SegImg,&color))
				{
					k++;
					word_color += color;
				}

				if (m_Color_Mode==COLOR_SAMPLE_CHAR)
				{qr_char->SetColor(color.x,color.y,color.z);}
		}

		if (m_Color_Mode==COLOR_SAMPLE_WORD)
		{
			if (k>0)
			{
				word_color.x /= k;
				word_color.y /= k;
				word_color.z /= k;
			}

			for(int c_id=0;c_id<w_samples[w_id].size();c_id++)
			{
				QRWordArt::QRCharacter::Char* qr_char = w_samples[w_id][c_id]->qr_char;
				qr_char->SetColor(word_color.x,word_color.y,word_color.z);
			}
		}		
	}
}
void AppAlgoTextColor::AssignColorTable( QRWordArt::QRStringLine& spline )
{
	QRWordArt::QRStringLine::WordSamples w_samples = spline.GetWordSamples();
	for (int w_id=0;w_id<w_samples.size();w_id++)
	{
		cv::Point3f word_color(0,0,0);
		if (w_samples[w_id][0]->_IsSentenceStart==true)
		{
			color_id++;
			color_id=color_id%colorTableNum;
		}
		word_color=colorTable[color_id];
		for(int c_id=0;c_id<w_samples[w_id].size();c_id++)
		{				
			QRWordArt::QRCharacter::Char* qr_char = w_samples[w_id][c_id]->qr_char;
			if (qr_char==NULL){continue;}
			qr_char->SetColor(word_color.x,word_color.y,word_color.z);
		}
	}
}
void AppAlgoTextColor::AssignColor_Fast( QRWordArt::QRStringLine& spline )
{
	QRWordArt::QRStringLine::WordSamples w_samples = spline.GetWordSamples();

	//#pragma omp parallel for
	for (int w_id=0;w_id<w_samples.size();w_id++)
	{
		int k=0;
		cv::Point3f word_color(0,0,0);
		for(int c_id=0;c_id<w_samples[w_id].size();c_id++)
		{
			QRWordArt::QRCharacter::Char* qr_char = w_samples[w_id][c_id]->qr_char;
			if (qr_char==NULL){continue;}

			cv::Point3f color;
			cv::Point2f posn(spline.get_x(w_samples[w_id][c_id]->sample),m_SrcImg->rows-spline.get_y(w_samples[w_id][c_id]->sample));
			if(GetPosnColor(*m_SrcImg,posn,*m_SegImg,&color))
			{
				k++;
				word_color += color;
			}
			else if (GetMeshColor(*m_SrcImg,*m_SegImg,qr_char,&color))
			{
				k++;
				word_color += color;
			}

			if (m_Color_Mode==COLOR_SAMPLE_CHAR)
			{qr_char->SetColor(color.x,color.y,color.z);}
		}

		if (m_Color_Mode==COLOR_SAMPLE_WORD)
		{
			if (k>0)
			{
				word_color.x /= k;
				word_color.y /= k;
				word_color.z /= k;
			}

			for(int c_id=0;c_id<w_samples[w_id].size();c_id++)
			{
				QRWordArt::QRCharacter::Char* qr_char = w_samples[w_id][c_id]->qr_char;
				if (qr_char==NULL){continue;}
				qr_char->SetColor(word_color.x,word_color.y,word_color.z);
			}
		}
	}
}

void AppAlgoTextColor::Enable( int enable )
{
	if (enable<SAMPLE_MODE)
	{
		m_Color_Mode = enable;
	}else if (enable<SAMPLE_QUALITY)
	{
		m_Sample_Quality = enable;
	}
}

