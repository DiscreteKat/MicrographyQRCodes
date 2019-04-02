#include "StdAfx.h"
#include "AppAlgoMGStreamlineWarping.h"
#include "AppAlgoModuleSelection.h"

bool AppFrame::AppAlgoStreamlineWarping::Execute( HKCAppItem^ _appItem )
{
	//if (_appItem->Param->Optimization->SCWarping_Level==0)return false;

	std::cout<<"Spline Warping..."<<std::endl;
	double alpha = 0.1;//_appItem->Param->Optimization->Lambda;
	std::cout<<" alpha: "<<alpha<<std::endl;
	m_AlgoModuleEnergy  = new AppAlgoProbabilityModule(_appItem);

	m_QRCData = &_appItem->Data->QRCData;
	m_Wa = _appItem->Data->QRCData.module_size;
	m_ImgW = _appItem->Data->QRCData.QRCImg.rows;
	m_ImgH = _appItem->Data->QRCData.QRCImg.cols;
	int bg_color = _appItem->Data->WordArtEvi.background_color;
	int word_art_idx =  _appItem->Data->CurrentWordArtID;
	QRWordArt::QRStringLines& strings = _appItem->Data->WordArtData[word_art_idx].splines;

	QRWordArt::QRCharacter::CharFBO fbo;
	fbo.Initialize(m_ImgW,m_ImgH);
	fbo.SetBackground(bg_color);
	fbo.Enable(QRWordArt::QRCharacter::CharFBO::SOILD_COLOR);

	AppAlgoModuleSelection app_locate(_appItem);
	std::vector<int>& seg_pid = _appItem->Data->WordArtEvi.seg_pids;
	CQRMap module_map = app_locate.CharModuleMapping(seg_pid,m_QRCData,bg_color,strings);

	for (int sp_id = 0;sp_id<strings.size();sp_id++)
	{
		printf("\r process...%d/%d                                   ",sp_id,strings.size());
		SplineWarpingTargetData target_data;
		for (int c_id = 0;c_id<strings[sp_id]->size();c_id++)
		{
			QRWordArt::QRCharacter::Char* qr_char = (*strings[sp_id])[c_id].qr_char;
			if (qr_char==NULL)continue;

			fbo.Push(qr_char);
			cv::Mat map;
			fbo.Draw(&map);
			cv::flip(map,map,0);
			fbo.Pop();

			std::vector<double> energy = m_AlgoModuleEnergy->Execute_Modules(map,module_map[qr_char]);
			CalTargets(m_QRCData,bg_color,module_map[qr_char],energy,(*strings[sp_id])[c_id],&target_data);
		}
		SplineWarping(*strings[sp_id],target_data,alpha);
	}
	printf("\r process...Done                                   \n");
	return true;
}

void AppFrame::AppAlgoStreamlineWarping::CalTargets( HKCQRCData* qrcode,int bg_color,std::vector<int> modules,std::vector<double> energy,const QRWordArt::QRStringLine::QRSample& qr_sample,SplineWarpingTargetData* target_data )
{
	QRWordArt::QRCharacter::Char* c = qr_sample.qr_char;
	double _Wa = qrcode->module_size;
	double _da = qrcode->center_size;

	for (int p_id=0;p_id<modules.size();p_id++)
	{
		cv::Point2d qr_posn = qrcode->Patches[modules[p_id]]->patch_Pos;
		qr_posn.x += 0.5*m_Wa; 
		qr_posn.y += 0.5*m_Wa;
		qr_posn.y = m_ImgH - qr_posn.y;

		if (bg_color!=qrcode->Patches[modules[p_id]]->qr_color)//Cover
		{
			if (energy[p_id]>0.3)//Move
			{
				QRWordArt::QRCharacter::QRNodes nodes = c->GetNodes();
				int node_idx;
				NearestNode(nodes,qr_posn +qrcode->offset,_Wa*0.55,&node_idx);

				if (node_idx!=-1)
				{
					SplineWarpingSampleTarget sample_target;
					if(CalTarget(0,qr_posn + qrcode->offset,c->Node(node_idx),_Wa,_da,&sample_target)){
						target_data->push_back(sample_target);
					}
				}
			}
			else//Stay
			{
				SplineWarpingSampleTarget sample_target;
				sample_target.first = qr_sample.sample;
				sample_target.second.w = 1;
				sample_target.second.move = 0;
			}
		}
		else//Avoid
		{
			if (energy[p_id]>0.1)//Move
			{
				QRWordArt::QRCharacter::QRNodes nodes = c->GetNodes();
				int node_idx;
				NearestNode(nodes,qr_posn+ qrcode->offset,_Wa*0.55,&node_idx);

				if (node_idx!=-1)
				{
					SplineWarpingSampleTarget sample_target;
					if(CalTarget(1,qr_posn+ qrcode->offset,c->Node(node_idx),_Wa,_da,&sample_target)){
						target_data->push_back(sample_target);
					}
				}
			}
			else//Stay
			{
				SplineWarpingSampleTarget sample_target;
				sample_target.first = qr_sample.sample;
				sample_target.second.w = 1;
				sample_target.second.move = 0;
			}
		}
	}
}

bool AppFrame::AppAlgoStreamlineWarping::CalTarget( int type,cv::Point qr_posn,QRWordArt::QRCharacter::QRNode* node, double _wa,double _da, SplineWarpingSampleTarget* sample_target )
{
	HSSSpline::Vector2 n_pos = node->Position();
	double  len = sqrt((n_pos[0]-qr_posn.x)*(n_pos[0]-qr_posn.x) + (n_pos[1]-qr_posn.y)*(n_pos[1]-qr_posn.y));

	HSSSpline::Vector2 vec;
	if (len>0)
	{
		vec[0] = (n_pos[0]-qr_posn.x)/len;
		vec[1] = (n_pos[1]-qr_posn.y)/len;
	}

	double h_da = _da*0.5;
	double h_wa = _wa*0.5;

	HSSSpline::PathPoint<2> target;
	switch(type){
	case 0://Cover
		target[0] =  qr_posn.x;
		target[1] =  qr_posn.y;
		break;
	case 1://Avoid
		target[0] =  qr_posn.x + (h_da+(h_wa-h_da)*0.5)*vec[0];
		target[1] =  qr_posn.y + (h_da+(h_wa-h_da)*0.5)*vec[1];
		break;
	}

	HSSSpline::HSplinePath *spline = node->StringLine();
	HSSSpline::PathPoint<2> normal = spline->get_normal(node->ToSample());


	double inter_produce = normal[0]*(target[0]-n_pos[0]) + normal[1]*(target[1]-n_pos[1]);
	double length = (target[0]-n_pos[0])*(target[0]-n_pos[0])+(target[1]-n_pos[1])*(target[1]-n_pos[1]);
	if ((inter_produce*inter_produce)/length<0.25){return false;}
	else
	{
		sample_target->first       = node->ToSample();
		sample_target->second.w    = CalWeight(inter_produce,h_da);
		sample_target->second.move = inter_produce;
		return true;
	}
	return true;
}

double AppFrame::AppAlgoStreamlineWarping::CalWeight( double len,double a )
{
	double w = exp(-(len*len)/(2*a*a));
	return w;
}

double AppFrame::AppAlgoStreamlineWarping::NearestNode( QRWordArt::QRCharacter::QRNodes& nodes,cv::Point qr_posn,double threhold,int* index )
{
	*index = -1;
	double min_len = threhold;
	for (int n=0;n<nodes.size();n++)
	{
		HSSSpline::Vector2 n_pos = nodes[n]->Position();
		double len = sqrt((qr_posn.x - n_pos[0])*(qr_posn.x - n_pos[0]) + (qr_posn.y - n_pos[1])*(qr_posn.y - n_pos[1]));
		if (min_len>=len && len!=0)
		{
			min_len     = len;
			*index    = nodes[n]->Index();
		}
	}
	return min_len;
}

void AppFrame::AppAlgoStreamlineWarping::SplineWarping( QRWordArt::QRStringLine& string,SplineWarpingTargetData& data,double alpaha )
{
	if (data.empty())return;
	
	std::vector<std::vector<SplineWarpingTarget>> ctrl_target;
	HSSSpline::PathPoints<5> ctrl_points = string.GetCtrlPoints();
	ctrl_target.resize(ctrl_points.size());

	for (int i=0;i<data.size();i++)
	{
		HSSSpline::Sample sample = data[i].first;
		int cp0 = sample.seg_idx;
		int cp1 = sample.seg_idx + 1;

		SplineWarpingTarget target;
		target.w = data[i].second.w;
		target.move = data[i].second.move;

		ctrl_target[cp0].push_back(target);
		ctrl_target[cp1].push_back(target);
	}

	for (int i=0;i<ctrl_target.size();i++)
	{
		double all_weight = 1/alpaha;
		for (int j=0;j<ctrl_target[i].size();j++){all_weight += ctrl_target[i][j].w;}

		double scale = 0;
		for (int j=0;j<ctrl_target[i].size();j++)
		{
			scale += (ctrl_target[i][j].w / all_weight) * ctrl_target[i][j].move;
		}

		HSSSpline::Vector2 normal;
		if(i!=ctrl_target.size()-1){normal = string.get_normal(i,0);}
		else{normal = string.get_normal(i-1,1);}

		ctrl_points[i][0] +=  scale*normal[0];
		ctrl_points[i][1] +=  scale*normal[1];
	}

	string.AssignCtrlPoints(ctrl_points);
	string.Update();
}
