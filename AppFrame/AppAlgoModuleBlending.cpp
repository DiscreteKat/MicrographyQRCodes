#include "StdAfx.h"
#include <algorithm> 
#include <gsl/gsl_multimin.h>

#include "QRWordArt/QRCharFBO.h"
#include "AppAlgoModuleBlending.h"

#include "AppAlgoQRCodeRenderer.h"
#include "AlgoAppImageColor.h"
#include "AppAlgoBinarization.h"

bool AppFrame::AppAlgoModuleBlending::Execute( HKCAppItem^ _appItem )
{
	HKCMediaItem^ srcItem = _appItem->Find("Source");
	if(!srcItem) return false;

	std::cout<<"Module Blending..."<<std::endl;

	Begin(_appItem);
	RecoverInf(_appItem);
	RecoverCW(_appItem);
	End(_appItem);

	return true;
}

void AppFrame::AppAlgoModuleBlending::Begin( HKCAppItem^ _appItem )
{
	int word_art_idx = _appItem->Data->CurrentWordArtID;
	m_Count = 0;
	{//初始化環境	
		HKCMediaItem^ srcItem = _appItem->Find("Source");
		m_SrcImg = (cv::Mat*)(srcItem->Media->Data());
		m_QRCData = &_appItem->Data->QRCData;
		m_QRImg   = &_appItem->Data->QRCData.QRCImg;

		m_QRWidth  = m_QRImg->rows;
		m_QRHeight = m_QRImg->cols;
		m_QROffset = &m_QRCData->offset;
		m_BG_Color  = _appItem->Data->WordArtEvi.background_color;
		m_Wa        = _appItem->Data->QRCData.module_size;
		m_da        = _appItem->Data->QRCData.center_size;

		m_Foreground_Modules  = &_appItem->Data->WordArtEvi.qr_foreground_modules;
		m_Background_Modules  = &_appItem->Data->WordArtEvi.qr_background_modules;

		m_SegImg = new cv::Mat;
		cv::Rect clipping(m_QROffset->x,m_QROffset->y,m_QRWidth,m_QRHeight);
		(_appItem->Data->WordArtEvi.segment_img)(clipping).copyTo(*m_SegImg);

		m_WordMap = new cv::Mat;
		AppAlgoQRCodeRenderer::GenWordMap(_appItem,m_WordMap);
		(*m_WordMap)(clipping).copyTo(*m_WordMap);
	}

	{//Pre-cal Module color
		m_ModuleColor = new cv::Mat(m_QRWidth,m_QRHeight,CV_8UC3);
		QRWordArt::QRStringLines* spline = &_appItem->Data->WordArtData[word_art_idx].splines;

		for (int i=0;i<m_QRCData->Patches.size();i++)
		{
			cv::Point   posn = m_QRCData->Patches[i]->grid_sample_Pos;
			cv::Point2d posn_Ry=cv::Point2d(posn.x+m_QRCData->offset.x,m_SrcImg->rows-(m_QRCData->offset.y+posn.y));
			double r=0,g=0,b=0;
			double min=99999999;
			for (unsigned int i=0 ; i <spline->size(); i++)
			{
				int select = -1;
				double dis = (*spline)[i]->SelectChar(posn_Ry.x,posn_Ry.y,&select);
				if (select!=-1 && dis<min)
				{
					(*spline)[i]->GetQRSamples()[select]->qr_char->GetColor(&r,&g,&b);
					min = dis;
				}
			}
			AppAlgoQRCodeRenderer::DrawModule3(posn,r*255,g*255,b*255,m_Wa,m_ModuleColor);
		}
		//cv::imshow("MCM",*m_ModuleColor);cv::waitKey();
	}
	
	{//初始化Output Data
		m_NaiveCombine  = &_appItem->Data->WordArtData[word_art_idx].naive_combine;
		*m_NaiveCombine = cv::Mat(m_QRImg->cols,m_QRImg->rows, CV_8UC4,cv::Scalar(0,0,0,0));

		m_NaiveBlending  = &_appItem->Data->WordArtData[word_art_idx].naive_blending;
		*m_NaiveBlending = cv::Mat(m_QRImg->cols,m_QRImg->rows, CV_8UC4,cv::Scalar(0,0,0,0));

		m_PatternBlending =  &_appItem->Data->WordArtData[word_art_idx].pattern_blending;
		m_PatternBlending->clear();
	}

	m_ProbMoudle = new AppAlgoProbabilityModule(_appItem);
	m_ProbModel  = new AppAlgoProbabilityModel(_appItem);
}

void AppFrame::AppAlgoModuleBlending::End( HKCAppItem^ _appItem )//Clear Data
{
	m_QRImg   = NULL;
	m_QRCData = NULL;
	m_SrcImg				= NULL;
	m_Foreground_Modules	= NULL;
	m_Background_Modules	= NULL;

	if(m_WordMap != NULL)
	{
		m_WordMap->release();
		delete m_WordMap;
	}
	m_WordMap = NULL;

	if(m_SegImg != NULL)
	{
		m_SegImg->release();
		delete m_SegImg;
	}
	m_SegImg = NULL;

	if(m_ProbMoudle != NULL){delete m_ProbMoudle;}
	m_ProbMoudle = NULL;
	if(m_ProbModel  != NULL){delete m_ProbModel;}
	m_ProbModel  = NULL;
}

bool AppFrame::AppAlgoModuleBlending::RecoverCW( HKCAppItem^ _appItem)
{
	QRCWData& cw_data  = m_QRCData->CWData;
	VecPatch& qr_patch = m_QRCData->Patches;

	cv::Mat src;
	AppAlgoQRCodeRenderer::Combine(*m_WordMap,*m_NaiveCombine,*m_Background_Modules,*m_Foreground_Modules,m_BG_Color,&src);
	std::vector<double> module_energy = m_ProbMoudle->Execute(src);

	std::vector<std::vector<double>> cw_prob = m_ProbModel->CodewordsErrProbability(module_energy);

	int max_iter = 0;
	for (int i=0;i<cw_data.size();i++){max_iter = max(max_iter,cw_data[i].size());}

	int black_module = 0;
	int white_module = 0;
	for (int iter=0;iter<max_iter;iter++){
		printf("\r Codeword Recover...%d     ",max_iter-iter);
		for (int i=0;i<cw_data.size();i++){
			if (iter>=cw_data[i].size()){continue;}
			int cw_idx = iter;
			int num0, num1;
			RecoverCW(i,cw_idx,m_Wa,m_da,&module_energy,&cw_prob, &num0, &num1);
			black_module += num0;
			white_module += num1;
		}
	}
	printf("\r Codeword Recovering...done (%d:%d)     \n", white_module, black_module);

	return m_ProbModel->IsErrorQRcode(cw_prob);
}

void AppFrame::AppAlgoModuleBlending::RecoverCW(int rs_id,int cw_idx,int wa,int da, std::vector<double>* energy,std::vector<std::vector<double>>* cw_prob, int* num0, int* num1)
{
	VecPatch& qr_patch = m_QRCData->Patches;
	QRCWData& cw_data  = m_QRCData->CWData;
	cv::Mat src;
	AppAlgoQRCodeRenderer::Combine(*m_WordMap,*m_NaiveCombine,*m_Background_Modules,*m_Foreground_Modules,m_BG_Color,&src);
	std::vector<double> module_energy = m_ProbMoudle->Execute(src);

	int count[2] = { 0, 0 };
	std::vector<int> sorted_module = SortModule(cw_data[rs_id][cw_idx].module_idx,*energy);//from high energy
	for (int k=0;k<sorted_module.size();k++){
		if (!m_ProbModel->IsErrorCodeword((*cw_prob)[rs_id][cw_idx])){break;}

		int id = sorted_module[k];
		cv::Point posn = qr_patch[id]->grid_sample_Pos;

		NaiveCombination(posn,wa,da,m_NaiveCombine);//NC

		NaiveBlending(posn,wa,da,m_NaiveBlending);//NB

		int q = PatternBlending(id,wa,da);//Pattern Blending

		Update(rs_id,cw_idx,energy,cw_prob);
		count[q]++;
	}
	*num0 = count[0];
	*num1 = count[1];
}

void AppFrame::AppAlgoModuleBlending::RecoverInf(HKCAppItem^ _appItem)
{
	VecPatch& qr_patch = m_QRCData->Patches;
	VecMdu& qr_module  = m_QRCData->Modules;
	QRCWData& cw_data  = m_QRCData->CWData;

	std::vector<int>& seg_pid = _appItem->Data->WordArtEvi.seg_pids;
	std::cout<<" Info Recovering...";
	int counter = 0;
	for (int i=0;i<seg_pid.size();i++){
		int k = seg_pid[i];
		if (qr_module[k]->Type!=2 && qr_module[k]->Type!=3 && qr_module[k]->Type!=5){continue;}

		cv::Point posn = qr_patch[k]->grid_sample_Pos;
		//NC
		NaiveCombination(posn,m_Wa,m_da,m_NaiveCombine);
		//NB
		NaiveBlending(posn,m_Wa,m_da,m_NaiveBlending);
		//Pattern Blending
		PatternBlending(k,m_Wa,m_da);

		counter++;
	}
	std::cout<<"done ("<<counter<<")"<<std::endl;
}

std::vector<int> AppFrame::AppAlgoModuleBlending::SortModule( std::vector<int>& module_idx,std::vector<double>& module_energy )
{
	std::vector<int>     sort_module_idx;
	std::vector<double>  sort_module_energy;
	for (int i=0;i<module_idx.size();i++){
		int id = module_idx[i];
		sort_module_idx.push_back(id);
		sort_module_energy.push_back(module_energy[id]);
	}

	for (int i=0;i<sort_module_idx.size()-1;i++){
		for (int j=i+1;j<sort_module_idx.size();j++){
			if (sort_module_energy[j]>sort_module_energy[i]){
				int temp_id = sort_module_idx[i];
				sort_module_idx[i] = sort_module_idx[j];
				sort_module_idx[j] = temp_id;

				double temp_energy = sort_module_energy[i];
				sort_module_energy[i] = sort_module_energy[j];
				sort_module_energy[j] = temp_energy;
			}
		}
	}
	return sort_module_idx;
}

void AppFrame::AppAlgoModuleBlending::Update( int rs_id,int cw_id,std::vector<double>* dst_energy,std::vector<std::vector<double>>* dst_cw_prob )
{
	cv::Mat src;
	AppAlgoQRCodeRenderer::Combine(*m_WordMap,*m_NaiveCombine,*m_Background_Modules,*m_Foreground_Modules,m_BG_Color,&src);
	//cv::imshow("src",src);cv::waitKey(1);
	std::vector<double> new_energy = m_ProbMoudle->Execute_Modules(src,m_QRCData->CWData[rs_id][cw_id].module_idx);
	for (int i=0;i<new_energy.size();i++){
		int id = m_QRCData->CWData[rs_id][cw_id].module_idx[i];
		(*dst_energy)[id] = new_energy[i];
	}

	double new_prob = m_ProbModel->CodewordErrProbability(m_QRCData->CWData[rs_id][cw_id],*dst_energy);
	(*dst_cw_prob)[rs_id][cw_id] = new_prob;
}

double AppFrame::AppAlgoModuleBlending::LuminanceAdjustment( int q, double delta,int *r,int *g,int* b)
{
	if     ( delta > 1.0 ){delta=1;}
	else if( delta < 0.0 ){delta=0;}

	double _Ymax = 1.0; 	
	double _Ymin = 0.0;

	double h,s,_Yin;
	RGB2HSL(*r,*g,*b,&h,&s,&_Yin);

	double _Yout = (_Ymax*q+_Ymin*(1-q))*(1-delta) + _Yin*delta;

	HSL2RGB(h,s,_Yout,r,g,b);

	return abs(_Yout-_Yin);//Error
}

int AppFrame::AppAlgoModuleBlending::ModuleLuminanceOptimize(int module_idx, double init_delta,double step,int *out_R,int *out_G,int* out_B )
{
	cv::Point& posn = m_QRCData->Patches[module_idx]->grid_sample_Pos;
	int idx = posn.y*m_QRImg->cols+posn.x;
	int q = (m_QRImg->data[idx]==0)?0:1;

	bool   flag = true;
	double delta = init_delta;
	double omega = 10;
	double energy= 1000;

	//Init
	{
		//Adjust Luminance
		int r = m_ModuleColor->data[idx*3+2];
		int g = m_ModuleColor->data[idx*3+1];
		int b = m_ModuleColor->data[idx*3+0];
		LuminanceAdjustment(q,delta,&r,&g,&b);

		cv::Mat mqrc;
		cv::Mat blend_map = cv::Mat(m_QRImg->cols,m_QRImg->rows, CV_8UC4,cv::Scalar(0,0,0,0));
		AppAlgoQRCodeRenderer::DrawModule4(posn,r,g,b,255,m_da,&blend_map);

		AppAlgoQRCodeRenderer::Combine(*m_WordMap,blend_map,*m_Background_Modules,*m_Foreground_Modules,m_BG_Color,&mqrc);
		double _Pm = m_ProbMoudle->Execute_Module(mqrc,module_idx);

		double luminance_error = ModuleLuminanceError(posn,m_da,blend_map);

		energy = omega*_Pm + luminance_error;
		//cv::imshow("mqrc",mqrc);cv::waitKey(10);
	}

	//SA
	do{
		delta += step;
		if (delta>1){delta=1;break;}
		if (delta<0){delta=0;break;}

		//Adjust Luminance
		int r = m_ModuleColor->data[idx*3+2];
		int g = m_ModuleColor->data[idx*3+1];
		int b = m_ModuleColor->data[idx*3+0];
		LuminanceAdjustment(q,delta,&r,&g,&b);

		cv::Mat mqrc;
		cv::Mat blend_map = cv::Mat(m_QRImg->cols,m_QRImg->rows, CV_8UC4,cv::Scalar(0,0,0,0));
		AppAlgoQRCodeRenderer::DrawModule4(posn,r,g,b,255,m_da,&blend_map);

		AppAlgoQRCodeRenderer::Combine(*m_WordMap,blend_map,*m_Background_Modules,*m_Foreground_Modules,m_BG_Color,&mqrc);
		double _Pm = m_ProbMoudle->Execute_Module(mqrc,module_idx);

		double luminance_error = ModuleLuminanceError(posn,m_da,blend_map);

		double new_energy = omega*_Pm + luminance_error;

 		if (new_energy-energy>10e-4)
 		{
 			delta -= step;
 			flag   = false;
		}else{
			energy = new_energy;
		}
		//cv::imshow("mqrc",mqrc);cv::waitKey(10);
	}while (flag);

	*out_R = m_ModuleColor->data[idx*3+2];
	*out_G = m_ModuleColor->data[idx*3+1];
	*out_B = m_ModuleColor->data[idx*3+0];
	LuminanceAdjustment(q,delta,out_R,out_G,out_B);

	//cv::waitKey();
	return q;
}

double AppFrame::AppAlgoModuleBlending::LuminanceError( int pixel_idx,int r,int g,int b )
{
	double ori_H, ori_S, ori_L;
	RGB2HSL(m_WordMap->data[pixel_idx*4+2],m_WordMap->data[pixel_idx*4+1],m_WordMap->data[pixel_idx*4+0], &ori_H, &ori_S, &ori_L);

	double var_H, var_S, var_L;
	RGB2HSL(r,g,b, &var_H, &var_S, &var_L);
	return abs(var_L-ori_L);
}

double AppFrame::AppAlgoModuleBlending::ModuleLuminanceError( cv::Point& posn,int da,cv::Mat& src )
{
	double luminance_error = 0;
	for (int i=-da*0.5; i<da*0.5; ++i){
		for (int j=-da*0.5; j<da*0.5; ++j){
			int pixel_idx = (posn.y+i)*src.cols+(posn.x+j);
			luminance_error+=LuminanceError(pixel_idx,src.data[pixel_idx*4+2],src.data[pixel_idx*4+1],src.data[pixel_idx*4+0]);
		}
	}
	return luminance_error/=(da*da);
}

void AppFrame::AppAlgoModuleBlending::NaiveCombination( cv::Point& posn,double wa,double da,cv::Mat* dst )
{
	int idx = posn.x+posn.y*m_QRWidth;
	AppAlgoQRCodeRenderer::DrawModule4(posn,m_QRImg->data[idx],m_QRImg->data[idx],m_QRImg->data[idx],128,da,dst);
}

void AppFrame::AppAlgoModuleBlending::NaiveBlending( cv::Point& posn,double wa,double da,cv::Mat* dst )
{
	int idx = posn.x+posn.y*m_QRWidth;

	int target_color[4] = {0,0,0,255};
	if (m_BG_Color==m_QRImg->data[idx] || m_SegImg->data[idx]==255){
		target_color[0] = m_QRImg->data[idx]; 
		target_color[1] = m_QRImg->data[idx]; 
		target_color[2] = m_QRImg->data[idx]; 
	}else{
		target_color[0]= m_ModuleColor->data[idx*3+2];
		target_color[1]= m_ModuleColor->data[idx*3+1];
		target_color[2]= m_ModuleColor->data[idx*3  ];
	}

	AppAlgoQRCodeRenderer::DrawModule4(posn,target_color[0],target_color[1],target_color[2],255,da,dst);
}

int AppFrame::AppAlgoModuleBlending::PatternBlending( int module_idx,double wa,double da)
{
	cv::Point2d offset = m_QRCData->offset;
	cv::Point& posn = m_QRCData->Patches[module_idx]->grid_sample_Pos;
	QRWordArt::QRPattern pattern;
	pattern.SetPosion(posn.x+0.5+offset.x,m_SrcImg->rows-posn.y-0.5-offset.y);
	pattern.SetSize(wa,wa);
	pattern.SetTexture(std::string("PsPattern"));

	int target_color[4] = {0,0,0,255};
	int q = ModuleLuminanceOptimize(module_idx,0, 0.25,&target_color[0],&target_color[1],&target_color[2]);
	
	pattern.SetColor(	target_color[0]/255.0,
						target_color[1]/255.0,
						target_color[2]/255.0,
						target_color[3]/255.0);

	m_PatternBlending->push_back(pattern);
	return q;
}

void AppFrame::AppAlgoModuleBlending::RGB2HSL( int r,int g,int b,double* out_H,double* out_S,double* out_L )
{
	double var_H,var_S,var_L;

	double var_R = ( (double)r / 255.0 );   //RGB from 0 to 255
	double var_G = ( (double)g / 255.0 );
	double var_B = ( (double)b / 255.0 );

	double min, max, delta;

	min = var_R < var_G ? var_R : var_G;
	min = min   < var_B ? min   : var_B;

	max = var_R > var_G ? var_R : var_G;
	max = max   > var_B ? max   : var_B;

	delta = max - min;

	// V
	var_L = (max+min)*0.5;                            

	// S
	if (delta != 0.0){ var_S = delta / (1-abs(2*var_L-1));}
	else{ var_S = 0; }

	//H
	if (delta==0){ var_H = 0;}
	else if (max == var_R && var_G >= var_B){ var_H = 60 * ((var_G-var_B)/delta);}
	else if (max == var_R && var_G < var_B) { var_H = 60 * ((var_G-var_B)/delta + 6);}
	else if (max == var_G){ var_H = 60 * ((var_B-var_R)/delta + 2);}
	else if (max == var_B){ var_H = 60 * ((var_R-var_G)/delta + 4);}

	*out_H = var_H;
	*out_S = var_S;
	*out_L = var_L;
}

void AppFrame::AppAlgoModuleBlending::HSL2RGB( double var_H,double var_S,double var_L,int* out_R,int* out_G,int* out_B )
{
	double var_R,var_G,var_B;
	double var_C,var_X,m;

	var_C = (1-abs(2*var_L-1))*var_S;
	var_X = var_C * (1-abs( fmod((float)var_H/60.0f, 2)-1 ));
	m = var_L - var_C*0.5;

	if(  0<=var_H && var_H<60 ){var_R=var_C; var_G=var_X; var_B=0;    }//(C,X,0)
	else if( 60<=var_H && var_H<120){var_R=var_X; var_G=var_C; var_B=0;    }//(X,C,0)
	else if(120<=var_H && var_H<180){var_R=0    ; var_G=var_C; var_B=var_X;}//(0,C,X)
	else if(180<=var_H && var_H<240){var_R=0    ; var_G=var_X; var_B=var_C;}//(0,C,X)
	else if(240<=var_H && var_H<300){var_R=var_X; var_G=0    ; var_B=var_C;}//(X,0,C)
	else if(300<=var_H && var_H<360){var_R=var_C; var_G=0    ; var_B=var_X;}//(C,0,X)

	*out_R = (int)(ceil((var_R+m) * 255.0));
	*out_G = (int)(ceil((var_G+m) * 255.0));
	*out_B = (int)(ceil((var_B+m) * 255.0));
}