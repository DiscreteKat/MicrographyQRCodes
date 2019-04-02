#include "StdAfx.h"
#include "AppAlgoMGWarpingOptimization.h"

#include "AppAlgoModuleSelection.h"


bool AppFrame::AppAlgoWarpingOptimization::Execute( HKCAppItem^ _appItem )
{
	std::cout<<"Character Warping...\n";
	m_QRCdata = &_appItem->Data->QRCData;
	m_ImgW = _appItem->Data->WordArtEvi.segment_img.cols;
	m_ImgH = _appItem->Data->WordArtEvi.segment_img.rows;
	m_BGColor = _appItem->Data->WordArtEvi.background_color;
	m_Clipping_Window =new cv::Rect(m_QRCdata->offset.x,m_QRCdata->offset.y,m_QRCdata->QRCImg.rows,m_QRCdata->QRCImg.cols);
	m_FBO = new QRWordArt::QRCharacter::CharFBO;
	m_FBO->Initialize(m_ImgW,m_ImgH);
	m_FBO->SetBackground(m_BGColor);
	m_FBO->Enable(QRWordArt::QRCharacter::CharFBO::SOILD_COLOR);

	m_ModuleEnergy = new AppAlgoProbabilityModule(_appItem);
	m_VisualEnergy = new AppAlgoEnergyVisual(_appItem);

	int word_art_idx =  _appItem->Data->CurrentWordArtID;
	QRWordArt::QRStringLines& splines = _appItem->Data->WordArtData[word_art_idx].splines;

	//Greedy
	//GreedyWarping(_appItem,splines);

	//Graph Cut
	std::vector<double> cs_alpha,cb_alpha;

	if (m_LabelSet==GC_LABEL_ALL || m_LabelSet==GC_LABEL_S)
	{
		cs_alpha.push_back(0.0);
		cs_alpha.push_back(0.25);
		cs_alpha.push_back(0.5);
		cs_alpha.push_back(0.75);
		cs_alpha.push_back(1.0);
		cs_alpha.push_back(1.25);
		cs_alpha.push_back(1.5);
		cs_alpha.push_back(1.75);
		cs_alpha.push_back(2.0);
	}else{cs_alpha.push_back(0.0);}
	
	if (m_LabelSet==GC_LABEL_ALL || m_LabelSet==GC_LABEL_B)
	{
		cb_alpha.push_back(-0.5);
		cb_alpha.push_back(-0.4);
		cb_alpha.push_back(-0.3);
		cb_alpha.push_back(-0.2);
		cb_alpha.push_back(-0.1);
		cb_alpha.push_back( 0.0);
		cb_alpha.push_back( 0.1);
		cb_alpha.push_back( 0.2);
		cb_alpha.push_back( 0.3);
		cb_alpha.push_back( 0.4);
		cb_alpha.push_back( 0.5);
	}else{cb_alpha.push_back(0.0);}
	
	double weight = _appItem->Param->Optimization->Lambda;
	GraphCutWarping(_appItem,splines,cs_alpha,cb_alpha,weight);

	//Release
	delete m_VisualEnergy;
	m_VisualEnergy = NULL;
	delete m_ModuleEnergy;
	m_ModuleEnergy = NULL;
	delete m_FBO;
	m_FBO = NULL;
	delete m_Clipping_Window;
	m_Clipping_Window = NULL;
	return true;
}
void AppFrame::AppAlgoWarpingOptimization::GreedyWarping(HKCAppItem^ _appItem,QRWordArt::QRStringLines& strings)
{
	std::vector<int> seg_pid = _appItem->Data->WordArtEvi.seg_pids;

	AppAlgoModuleSelection app_locate(_appItem);
	CQRMap module_map =  app_locate.CharModuleMapping(seg_pid,m_QRCdata,m_BGColor,strings);

	AppAlgoFontWeightAdjustment bold_warping(_appItem);
	AppAlgoLetterWarping struct_warping(_appItem);

	struct_warping.Targeting(_appItem);


	QRWordArt::QRCharacter::CharFBO fbo_alpha;
	fbo_alpha.Initialize(m_ImgW,m_ImgH);

	double bold_step   = 0.1;//_appItem->Param->ErrorCorrection->CBWarping_Scale;
	double struct_step = 0.1;//_appItem->Param->ErrorCorrection->CSWarping_Level;
	
	for (int sp_id=0;sp_id<strings.size();sp_id++)
	{
		for (int c_id=0;c_id<strings[sp_id]->size();c_id++)
		{
			printf("\r process...%d/%d - %d/%d                                   ",sp_id,strings.size(),c_id,strings[sp_id]->size());
			QRWordArt::QRCharacter::Char* qr_char = (*strings[sp_id])[c_id].qr_char;
			if (qr_char == NULL)continue;

			//Init
			cv::Mat char_mat;
			m_FBO->Push(qr_char);
			m_FBO->Draw(&char_mat); 
			cv::flip(char_mat,char_mat,0);
			m_FBO->Pop();

			cv::Mat char_alpha;
			fbo_alpha.Push(qr_char);
			fbo_alpha.Draw(&char_alpha); 
			cv::flip(char_alpha,char_alpha,0);
			fbo_alpha.Pop();
			cv::Mat elem = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(9,9));
			cv::morphologyEx(char_alpha, char_alpha, cv::MORPH_ERODE, elem);
			std::vector<int> module_idx = app_locate.SelectModule(char_alpha);

			double module_energy = m_ModuleEnergy->Execute_Modules_Avg(char_mat,module_idx);
			double visual_energy = m_VisualEnergy->EvaluateLocalVisualEnergy(*strings[sp_id],(*strings[sp_id])[c_id]);

			double bold_target = bold_warping.Targeting(bold_step*3,qr_char,module_idx);

			bool flag = true;
			int bold_iter   = 1;
			int struct_iter = 5;
			int bold_limit  = 5;
			while(flag)
			{
				std::vector<double> param;
				std::vector<AppAlgoWarpingOperator*> op;

				QRWordArt::QRCharacter::DeformationData bold_data;
				std::vector<double>						bold_energy;
				param.push_back(bold_target*bold_step);
				op.push_back(&bold_warping);
				bold_energy = WarpingEvaluation(*strings[sp_id],(*strings[sp_id])[c_id],module_idx,param,op,&bold_data);

				param.clear(); op.clear();

				QRWordArt::QRCharacter::DeformationData struct_data;
				std::vector<double>             struct_energy;
				param.push_back(bold_target*bold_step);
				op.push_back(&bold_warping);
				struct_energy = WarpingEvaluation(*strings[sp_id],(*strings[sp_id])[c_id],module_idx,param,op,&bold_data);

				if(bold_energy[0]<module_energy && struct_energy[0]<module_energy){
					double e1,e2;
					e1 = (bold_energy[1]  -visual_energy)/(module_energy-bold_energy[0]);
					e2 = (struct_energy[1]-visual_energy)/(module_energy-struct_energy[0]);

					if (e1<e2 && bold_iter<=bold_limit)
					{
						qr_char->SetDeformationData(bold_data);
						module_energy = bold_energy[0];
						visual_energy = bold_energy[1];
						bold_iter++;
						//std::cout<<"B";
					}else{
						qr_char->SetDeformationData(struct_data);
						module_energy = struct_energy[0];
						visual_energy = struct_energy[1];
						struct_iter++;
						//std::cout<<"S";
					}
				}else if (bold_energy[0]<module_energy){
					if (bold_iter>bold_limit){break;}

					qr_char->SetDeformationData(bold_data);
					module_energy = bold_energy[0];
					visual_energy = bold_energy[1];
					bold_iter++;
					//std::cout<<"B";
				}else if (struct_energy[0]<module_energy){
					qr_char->SetDeformationData(struct_data);
					module_energy = struct_energy[0];
					visual_energy = struct_energy[1];
					struct_iter++;
					//std::cout<<"S";
				}else{flag = false;}
			}
			std::cout<<std::endl;
		}
	}
}
void AppFrame::AppAlgoWarpingOptimization::GraphCutWarping( HKCAppItem^ _appItem,QRWordArt::QRStringLines& strings,std::vector<double>& csw_samples,std::vector<double>& cbw_samples,double weight )
{
	std::cout<<"Graph Cut ";
	if     (m_LabelSet==GC_LABEL_S){std::cout<<"Structure Only"<<std::endl;}
	else if(m_LabelSet==GC_LABEL_B){std::cout<<"Bold Only"<<std::endl;}
	else{std::cout<<std::endl;}
	std::cout<<" Weight: "<<weight<<std::endl;
	//Init Site
	GCSiteDatas site_datas;
	int wa = _appItem->Data->QRCData.module_size;
	SelectSites(strings,wa,&site_datas);

	int num_site = site_datas.size();
	std::cout<<" Number of Site : "<<num_site<<std::endl;

	//Init Label
	GCLabelDatas label_datas;
	for (int i=0;i<csw_samples.size();i++)
	{
			for (int j=0;j<cbw_samples.size();j++)
			{
				GCLabelData data;
				data[0] = csw_samples[i];
				data[1] = cbw_samples[j];
				label_datas.push_back(data);
			}
	}
	int num_label = label_datas.size();
	std::cout<<" Number of Label: "<<num_label<<std::endl;

	//Generate Energy
	AppAlgoFontWeightAdjustment font_weight(_appItem);
	AppAlgoLetterWarping struct_warping(_appItem);
 	struct_warping.Targeting(_appItem);


	bool io_flag = false;
	std::string filename = _appItem->Data->IO_Handle.wordart_filename;//MarshalString(srcItem->Prop->FileName);
	if (!filename.empty())
	{
		filename = filename.substr(0,filename.rfind("."));
		int ec_level = _appItem->Data->QRCData.ECL;
		char buff[100];
		sprintf(buff,"_%d_%dx%d.gce\0",ec_level,csw_samples.size(),cbw_samples.size());
		filename += buff;
		io_flag = ReadEnergy(filename,site_datas,csw_samples,cbw_samples);
	}
	
	if (!io_flag){
		GC_CalEnergy(_appItem,font_weight,struct_warping,label_datas,&site_datas);
		OutputEnergy(filename,site_datas,csw_samples,cbw_samples);
	}else{std::cout<<" read energy"<<std::endl;}

	try{
		GCoptimizationGeneralGraph *gc = new GCoptimizationGeneralGraph(num_site,num_label);
		//Set Neighbors
		GC_SetNeighbors(gc,site_datas);
		//Smooth Penalty
		GC_SetSoomthPenalty(gc,label_datas);
		//Data Term
 		printf(" set data term...             ");
 		for (int site_id=0;site_id<num_site;site_id++)
 		{
 			for (int label_id =0; label_id<num_label; label_id++)
 			{
 				double e = weight*site_datas[site_id].energy[label_id][0]+site_datas[site_id].energy[label_id][1];
 				gc->setDataCost(site_id,label_id,e);
 				printf("\r set data term...%d %d %lf            ",site_id,label_id,e);
 			}
 		}
 		printf("\r set data term...Done            \n");

		//Excute OP
		gc->swap();

		//Assign Deformation
		for (int site_id=0;site_id<site_datas.size();site_id++)
		{
			QRWordArt::QRCharacter::Char* qr_char = site_datas[site_id].qr_sample->qr_char;
			if (qr_char==NULL)continue;

			int label_id = gc->whatLabel(site_id);

			struct_warping.Execute(label_datas[label_id][0],qr_char);
			font_weight.Execute(label_datas[label_id][1],qr_char);
  		}
		delete gc;
	}catch(GCException e){
		e.Report();
		system("pause");
	}
}

void AppFrame::AppAlgoWarpingOptimization::GC_SetNeighbors(GCoptimizationGeneralGraph* gc, GCSiteDatas& site_datas)
{
	printf(" set neighbors...             ");
	for (int site1 = 0; site1<site_datas.size()-1; site1++){
		HSSSpline::Vector2 p1 = site_datas[site1].spline->get_position(site_datas[site1].qr_sample->sample);
		double distance = site_datas[site1].spline->get_w(site_datas[site1].qr_sample->sample);
		for (int site2 = site1+1; site2<site_datas.size(); site2++){
			if (site1==site2)continue;
			HSSSpline::Vector2 p2 = site_datas[site2].spline->get_position(site_datas[site2].qr_sample->sample);
			double dis = (p1[0]-p2[0])*(p1[0]-p2[0]) + (p1[1]-p2[1])*(p1[1]-p2[1]);
			if (dis<=distance*distance){
				double w = exp(-dis/(2*distance*distance));
				gc->setNeighbors(site1, site2, w);
				gc->setNeighbors(site2, site1, w);
				printf("\r set neighbors...%d  %d  %lf           ",site1,site2,w);
			}
		}
	}
	printf("\r set neighbors...Done                                              \n");
}

void AppFrame::AppAlgoWarpingOptimization::GC_SetSoomthPenalty( GCoptimizationGeneralGraph* gc, GCLabelDatas& label_datas )
{
	printf(" set penalty...             ");
	for (int label1 = 0; label1<label_datas.size()-1; label1++){
		for (int label2 = label1+1; label2<label_datas.size(); label2++){
			if (label1==label2)continue;
			double penalty = abs(label_datas[label1][1]-label_datas[label2][1]);
			gc->setSmoothCost(label1,label2,penalty);
			gc->setSmoothCost(label2,label1,penalty);
			printf("\r set penalty...%d %d %lf           ",label1,label2,penalty);
		}
	}
	printf("\r set penalty...Done               \n");
}

void AppFrame::AppAlgoWarpingOptimization::GC_CalEnergy( HKCAppItem^ _appItem,AppAlgoFontWeightAdjustment& bold_warping,AppAlgoLetterWarping& struct_warping,GCLabelDatas& label_datas ,GCSiteDatas* site_datas)
{
	printf(" generate energy...             ");
	std::vector<int> seg_pid = _appItem->Data->WordArtEvi.seg_pids;
	AppAlgoModuleSelection app_locate(_appItem);

	QRWordArt::QRCharacter::CharFBO fbo_alpha;
	fbo_alpha.Initialize(m_ImgW,m_ImgH);

	for (int site_id=0;site_id<site_datas->size();site_id++)
	{
		QRWordArt::QRCharacter::Char* qr_char = (*site_datas)[site_id].qr_sample->qr_char;
		if (qr_char == NULL)continue;

		//Locate Module
		cv::Mat char_alpha;
		fbo_alpha.Push(qr_char);
		fbo_alpha.Draw(&char_alpha); 
		cv::flip(char_alpha,char_alpha,0);
		char_alpha(*m_Clipping_Window).copyTo(char_alpha);
		fbo_alpha.Pop();
		cv::Mat elem = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(9,9));
		cv::morphologyEx(char_alpha, char_alpha, cv::MORPH_ERODE, elem);
		//cv::imshow("char_alpha",char_alpha);cv::waitKey();
		std::vector<int> module_idx = app_locate.SelectModule(char_alpha);
		
		m_FBO->Push(qr_char);

		//SetEnergy
		(*site_datas)[site_id].energy.resize(label_datas.size());
		double last_structure_alpha = 0; //¬ö¿ýSturcture Warping
		std::vector<HSSSpline::Vector2> ori_skeleton = qr_char->GetAllNodesUV();//¬ö¿ý­ì©lDeformation
		std::vector<HSSSpline::Scale3>  ori_bold     = qr_char->GetAllFontWeight();
		for (int label_id =0; label_id<label_datas.size(); label_id++)
		{
			if (last_structure_alpha!=label_datas[label_id][0])
			{
				if (label_datas[label_id][0]!=0){
					struct_warping.Execute(label_datas[label_id][0],qr_char);
				}else{
					qr_char->SetAllNodesUV(ori_skeleton);
				}
				last_structure_alpha = label_datas[label_id][0];
			}

			bold_warping.Execute(label_datas[label_id][1],qr_char);
 			cv::Mat char_mat;
 			m_FBO->Draw(&char_mat); 
 			cv::flip(char_mat,char_mat,0);
			char_mat(*m_Clipping_Window).copyTo(char_mat);

 			(*site_datas)[site_id].energy[label_id][0] = m_ModuleEnergy->Execute_Modules_Avg(char_mat,module_idx);
 			(*site_datas)[site_id].energy[label_id][1] = m_VisualEnergy->EvaluateLocalVisualEnergy(*(*site_datas)[site_id].spline,*(*site_datas)[site_id].qr_sample);

			qr_char->SetAllFontWeight(ori_bold);
			char_mat.release();

			printf("\r generate energy...%d %d %lf %lf                      ",site_id,label_id,(*site_datas)[site_id].energy[label_id][0],(*site_datas)[site_id].energy[label_id][1]);
		}
		qr_char->SetAllNodesUV(ori_skeleton);
		m_FBO->Pop();
	}
	printf("\r generate energy...Done                      \n");
}

std::vector<double> AppFrame::AppAlgoWarpingOptimization::WarpingEvaluation( QRWordArt::QRStringLine& spline,QRWordArt::QRStringLine::QRSample& qr_sample, std::vector<int>& module_idxs,std::vector<double>& warping_param, std::vector<AppAlgoWarpingOperator*>& warping_op, QRWordArt::QRCharacter::DeformationData* result )
{
	std::vector<double> energy;
	energy.resize(2);

	QRWordArt::QRCharacter::DeformationData ori = qr_sample.qr_char->GetDeformationData();
	Warping(qr_sample.qr_char,warping_param,warping_op);

	cv::Mat char_mat;
	m_FBO->Push(qr_sample.qr_char);
	m_FBO->Draw(&char_mat); 
	cv::flip(char_mat,char_mat,0);
	m_FBO->Pop();

	energy[0] = m_ModuleEnergy->Execute_Modules_Avg(char_mat,module_idxs);
	energy[1] = m_VisualEnergy->EvaluateLocalVisualEnergy(spline,qr_sample);

	if(result!=NULL)*result = qr_sample.qr_char->GetDeformationData();
	qr_sample.qr_char->SetDeformationData(ori);

	char_mat.release();
	return energy;
}

void AppFrame::AppAlgoWarpingOptimization::Warping( QRWordArt::QRCharacter::Char* qr_char,std::vector<double>& warping_param, std::vector<AppAlgoWarpingOperator*>& warping_op )
{
	for (int i=0;i<warping_op.size();i++){warping_op[i]->Execute(warping_param[i],qr_char);}
}

void AppFrame::AppAlgoWarpingOptimization::OutputEnergy( std::string filename,GCSiteDatas& data,std::vector<double>& csw_samples,std::vector<double>& cbw_samples )
{
	std::ofstream file;
	file.open (filename);
	file<<csw_samples.size()<<"\n";
	for (int i=0;i<csw_samples.size();i++)
	{
		file<<csw_samples[i]<<" ";
	}
	file<<"\n"<<cbw_samples.size()<<"\n";
	for (int i=0;i<cbw_samples.size();i++)
	{
		file<<cbw_samples[i]<<" ";
	}
	file<<"\n"<<data.size()<<"\n";
	for (int i=0;i<data.size();i++)
	{
		for (int j=0;j<data[i].energy.size();j++)
		{
			file<<data[i].energy[j][0]<<" ";
			file<<data[i].energy[j][1]<<" ";
		}
		file<<"\n";
	}
	file.close();
}

bool AppFrame::AppAlgoWarpingOptimization::ReadEnergy( std::string filename,GCSiteDatas& data,std::vector<double>& csw_samples,std::vector<double>& cbw_samples )
{
	QRWordArt::QRStringLines splines;
	std::ifstream file ( filename , ifstream::in );
	if(file.is_open())
	{
		int num_csw,num_cbw,num_site;
		file>>num_csw;
		if (num_csw!=csw_samples.size()){return false;}
		for (int i=0;i<num_csw;i++)
		{
			double csw;
			file>>csw;
			if (csw!=csw_samples[i]){return false;}
		}

		file>>num_cbw;
		if (num_cbw!=cbw_samples.size()){return false;}
		for (int i=0;i<num_cbw;i++)
		{
			double cbw;
			file>>cbw;
			if (cbw!=cbw_samples[i]){return false;}
		}

		file>>num_site;
		if (num_site!=data.size()){return false;}
		for (int i=0;i<num_site;i++)
		{
			data[i].energy.resize(num_csw*num_cbw);
			for (int j=0;j<num_csw*num_cbw;j++)
			{
				file>>data[i].energy[j][0];
				file>>data[i].energy[j][1];
			}
		}
		file.close();
		return true;
	}else{return false;}
}

void AppFrame::AppAlgoWarpingOptimization::SelectSites( QRWordArt::QRStringLines& strings,double wa,GCSiteDatas* site_datas )
{
	cv::Mat qrMap = cv::Mat(m_ImgW,m_ImgH,CV_8UC1,cv::Scalar(255));
	qrMap(*m_Clipping_Window).setTo(cv::Scalar(0));
	cv::Mat elem = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(wa,wa));
	cv::morphologyEx(qrMap, qrMap, cv::MORPH_ERODE, elem);
	//cv::imshow("QRMap",qrMap);cv::waitKey();
	site_datas->clear();
	for (int s_id = 0 ; s_id < strings.size() ; s_id++){
		QRWordArt::QRStringLine* stringline = strings[s_id];
		for (int c_id = 0 ; c_id <stringline->GetQRSamples().size() ; c_id++){
			QRWordArt::QRCharacter::Char* qr_char = (*strings[s_id])[c_id].qr_char;
			if (qr_char == NULL)continue;
			HSSSpline::PathPoint<2> posn = stringline->get_position(stringline->GetQRSamples()[c_id]->sample);
			posn[1] = m_ImgH-posn[1];//height
			if (qrMap.at<uchar>(posn[1],posn[0])==0){
				GCSiteData data;
				data.spline    = stringline;
				data.qr_sample = stringline->GetQRSample(c_id);
				site_datas->push_back(data);
			}
		}
	}
}
