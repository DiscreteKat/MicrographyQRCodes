#include "StdAfx.h"
#include "AppAlgoMGFontWeightAdjustment.h"
#include "AppAlgoModuleSelection.h"

AppAlgoFontWeightAdjustment::AppAlgoFontWeightAdjustment( HKCAppItem^ _appItem ):m_ModuleEnergy(_appItem),m_VisualEnergy(_appItem)
{
	m_QRCData	= &_appItem->Data->QRCData;
	m_ImgW = _appItem->Data->WordArtEvi.segment_img.cols;
	m_ImgH = _appItem->Data->WordArtEvi.segment_img.rows;
	m_FBO.Initialize(m_ImgW,m_ImgH);
	m_Clipping_Window = cv::Rect(m_QRCData->offset.x,m_QRCData->offset.y,m_QRCData->QRCImg.cols,m_QRCData->QRCImg.rows);
	int bg_color = _appItem->Data->WordArtEvi.background_color;
	m_FBO.SetBackground(bg_color);
	m_FBO.Enable(QRWordArt::QRCharacter::CharFBO::SOILD_COLOR);	

	int word_art_idx =  _appItem->Data->CurrentWordArtID;
	m_WordArt = &_appItem->Data->WordArtData[word_art_idx];
}

double AppAlgoFontWeightAdjustment::Targeting( double scale,QRWordArt::QRCharacter::Char* qr_char,std::vector<int>& module_idxs )
{
	double target[2] = {-1,1};
	double energy[2] = { 0,0};

	m_FBO.Push(qr_char);
	std::vector<HSSSpline::Scale3> ori_bold = qr_char->GetAllFontWeight();
	for (int i=0;i<2;i++){
		for (int sk_id = 0 ; sk_id<qr_char->SkeletonSize(); sk_id++)
		{
			qr_char->Skeleton(sk_id)->Width()   = ori_bold[sk_id][0]*(1+target[i]*scale);
			qr_char->Skeleton(sk_id)->Height1() = ori_bold[sk_id][1]*(1+target[i]*scale);
			qr_char->Skeleton(sk_id)->Height2() = ori_bold[sk_id][2]*(1+target[i]*scale);
		}

		cv::Mat char_mat;
		m_FBO.Draw(&char_mat); 
		cv::flip(char_mat,char_mat,0);
		char_mat(m_Clipping_Window).copyTo(char_mat);
		energy[i] = m_ModuleEnergy.Execute_Modules_Avg(char_mat,module_idxs);

		qr_char->SetAllFontWeight(ori_bold);
	}
	m_FBO.Pop();

	if (energy[0]<energy[1])return target[0];
	else{return target[1];}
}

void AppAlgoFontWeightAdjustment::Execute( double scale,QRWordArt::QRCharacter::Char* qr_char)
{
	if (scale==0)return;

	std::vector<HSSSpline::Scale3> ori_bold   = qr_char->GetAllFontWeight();
	for (int sk_id = 0 ; sk_id<qr_char->SkeletonSize(); sk_id++)
	{
		qr_char->Skeleton(sk_id)->Width()   = ori_bold[sk_id][0]*(1+scale);
		qr_char->Skeleton(sk_id)->Height1() = ori_bold[sk_id][1]*(1+scale);
		qr_char->Skeleton(sk_id)->Height2() = ori_bold[sk_id][2]*(1+scale);
	}
	qr_char->CalBoundBox();
}