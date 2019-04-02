#include "StdAfx.h"
#include "AppAlgoMGLetterWarping.h"
#include "AppAlgoModuleSelection.h"

AppAlgoLetterWarping::AppAlgoLetterWarping( HKCAppItem^ _appItem ):m_ModuleEnergy(_appItem),m_VisualEnergy(_appItem)
{
	m_QRCData	= &_appItem->Data->QRCData;
	m_ImgW	= _appItem->Data->WordArtEvi.segment_img.cols;
	m_ImgH	= _appItem->Data->WordArtEvi.segment_img.rows;
	m_Wa	= _appItem->Data->QRCData.module_size;
	m_da	= _appItem->Data->QRCData.center_size;
	m_Clipping_Window = cv::Rect(m_QRCData->offset.x,m_QRCData->offset.y,m_QRCData->QRCImg.cols,m_QRCData->QRCImg.rows);
	m_BGColor = _appItem->Data->WordArtEvi.background_color;
	
	m_FBO.Initialize(m_ImgW,m_ImgH);
	m_FBO.SetBackground(m_BGColor);
	m_FBO.Enable(QRWordArt::QRCharacter::CharFBO::SOILD_COLOR);

	int word_art_idx = _appItem->Data->CurrentWordArtID;
	m_WordArt = &_appItem->Data->WordArtData[word_art_idx];
}

void AppAlgoLetterWarping::Targeting( HKCAppItem^ _appItem )
{
	m_TargetMap.clear();
	m_FBO.Clear();

	std::vector<int> seg_pid = _appItem->Data->WordArtEvi.seg_pids;

	AppAlgoModuleSelection app_locate(_appItem);
	AppAlgoModuleSelection::CM_Map module_map =  app_locate.CharModuleMapping(seg_pid,m_QRCData,m_BGColor,m_WordArt->splines);

	for (int sp_id=0;sp_id<m_WordArt->splines.size();sp_id++){
		for (int c_id=0;c_id<m_WordArt->splines[sp_id]->size();c_id++){
			QRWordArt::QRCharacter::Char* qr_char = (*m_WordArt->splines[sp_id])[c_id].qr_char;
			if (qr_char == NULL){continue;}
			//==AABB==
 			double min_x = m_Clipping_Window.x;
 			double min_y = m_Clipping_Window.y;
 			double max_x = m_Clipping_Window.x+m_Clipping_Window.width;
 			double max_y = m_Clipping_Window.y+m_Clipping_Window.height;
 			HSSSpline::PathPoint<2> posn = m_WordArt->splines[sp_id]->get_position((*m_WordArt->splines[sp_id])[c_id].sample);
 			if (posn[0]<min_x || posn[0]>max_x || posn[1]<min_y || posn[1]>max_y){continue;}
			//========
			m_FBO.Push(qr_char);
			cv::Mat map;
			m_FBO.Draw(&map);
			cv::flip(map,map,0);
			map(m_Clipping_Window).copyTo(map);
			m_FBO.Pop();
			//cv::imshow("map",map);cv::waitKey(1);

			std::vector<double> module_energy = m_ModuleEnergy.Execute_Modules(map,module_map[qr_char]);
			QRWordArt::QRCharacter::Node_Targets targets = CalTargets(m_QRCData,m_BGColor,module_map[qr_char],module_energy,(*m_WordArt->splines[sp_id])[c_id]);
			if(!targets.empty()){ExtraTarget(targets,qr_char);}

			m_TargetMap[qr_char] = targets;
		}
	}
}

void AppAlgoLetterWarping::Execute(double alpha,QRWordArt::QRCharacter::Char* qr_char)
{
	if (alpha==0)return;
	TargetMap::iterator target_it = m_TargetMap.find(qr_char);
	if (target_it==m_TargetMap.end())return;
	qr_char->Editing(target_it->second,alpha);
	qr_char->Update();
}

QRWordArt::QRCharacter::Node_Targets AppAlgoLetterWarping::CalTargets( HKCQRCData* qrcode,int bg_color,std::vector<int>& modules,std::vector<double> energy,const QRWordArt::QRStringLine::QRSample& sample )
{
	QRWordArt::QRCharacter::Char* c = sample.qr_char;
	QRWordArt::QRCharacter::Node_Targets targets;

	for (unsigned int p_id=0;p_id<modules.size();p_id++)
	{
		cv::Point2d qr_posn = qrcode->Patches[modules[p_id]]->patch_Pos;
		qr_posn.x = qr_posn.x + qrcode->offset.x + 0.5*m_Wa;
		qr_posn.y = m_ImgH - (qr_posn.y + qrcode->offset.y + 0.5*m_Wa);

		if (bg_color!=qrcode->Patches[modules[p_id]]->qr_color)//Cover
		{
			QRWordArt::QRCharacter::QRNodes nodes = c->GetNodes();
			int node_idx;
			NearestNode(nodes,qr_posn,m_Wa*0.55,&node_idx);

			if (node_idx!=-1)
			{
				QRWordArt::QRCharacter::Node_Target node_target = CalTarget(0,qr_posn,c->Node(node_idx),m_Wa,m_da,1);
				bool offside_flag = CheckOffside(c->Node(node_idx),node_target,sample);
				if (!offside_flag || node_target.second.w > 0.0001){targets.push_back(node_target);}
			}
		}else{//Avoid
			if (energy[p_id]>0.05)//Move
			{
				std::vector<bool> check;
				check.resize(c->NodeSize(),false);
				for (int s=0; s<c->SkeletonSize(); s++)
				{
					QRWordArt::QRCharacter::QRNodes nodes = c->Skeleton(s)->GetNodes();
					int node_idx;
					NearestNode(nodes,qr_posn,m_Wa*0.25+m_da*0.25,&node_idx);

					if (node_idx!=-1 && !check[node_idx])
					{
						QRWordArt::QRCharacter::Node_Target node_target = CalTarget(1,qr_posn,c->Node(node_idx),m_Wa,m_da,1);
						bool offside_flag = CheckOffside(c->Node(node_idx),node_target,sample);
						if (!offside_flag || node_target.second.w > 0.0001)
						{
							targets.push_back(node_target);
							for (int i=0;i<nodes.size();i++)
							{
								int idx = nodes[i]->Index();
								check[idx] = true;
							}
						}
					}
				}
			}else{//Stay
				QRWordArt::QRCharacter::QRNodes nodes = c->GetMainNodes();
				for (unsigned int n_id=0;n_id<nodes.size();n_id++)
				{
					HSSSpline::Vector2 n_pos = nodes[n_id]->Position();
					double  len = sqrt((n_pos[0]-qr_posn.x)*(n_pos[0]-qr_posn.x) + (n_pos[1]-qr_posn.y)*(n_pos[1]-qr_posn.y));

					if (len<m_Wa*0.5)
					{
						QRWordArt::QRCharacter::Node_Target node_target = CalTarget(2,qr_posn,nodes[n_id],m_Wa,m_da,0.25);
						targets.push_back(node_target);
					}
				}
			}
		}
	}
	return targets;
}

QRWordArt::QRCharacter::Node_Target AppAlgoLetterWarping::CalTarget( int type,cv::Point2d qr_posn,QRWordArt::QRCharacter::QRNode* node, double _wa,double _da, double weight )
{
	QRWordArt::QRCharacter::Node_Target node_target;
	node_target.first = node->Index();
	node_target.second.w = weight;

	HSSSpline::Vector2 n_pos = node->Position();
	if (type==2)//Soft Fix
	{
		node_target.second.posn[0] = n_pos[0];
		node_target.second.posn[1] = n_pos[1];
	}
	else
	{
		double h_da = _da*0.5;
		double h_wa = _wa*0.5;
		if (type==0)//Cover
		{
			node_target.second.posn[0] =  qr_posn.x;
			node_target.second.posn[1] =  qr_posn.y;
		}
		else if (type==1)//Avoid
		{
			double  len = sqrt((n_pos[0]-qr_posn.x)*(n_pos[0]-qr_posn.x) + (n_pos[1]-qr_posn.y)*(n_pos[1]-qr_posn.y));

			HSSSpline::Vector2 vec;
			if (len>0)
			{
				vec[0] = (n_pos[0]-qr_posn.x)/len;
				vec[1] = (n_pos[1]-qr_posn.y)/len;
			}

			node_target.second.posn[0] =  qr_posn.x + (h_da+(h_wa-h_da)*0.5)*vec[0];
			node_target.second.posn[1] =  qr_posn.y + (h_da+(h_wa-h_da)*0.5)*vec[1];
		}
		
		double len = sqrt((n_pos[0]-node_target.second.posn[0])*(n_pos[0]-node_target.second.posn[0]) + (n_pos[1]-node_target.second.posn[1])*(n_pos[1]-node_target.second.posn[1]));
		node_target.second.w *= CalWeight(len,h_da);
	}
	return node_target;
}

double AppAlgoLetterWarping::CalWeight( double len,double a )
{
	return exp(-(len*len)/(2*a*a));
}

double AppAlgoLetterWarping::NearestNode( QRWordArt::QRCharacter::QRNodes& nodes,cv::Point2d qr_posn,double threhold,int* index )
{
	*index = -1;
	double min_len = threhold;

	for (unsigned int n=0;n<nodes.size();n++)
	{
		HSSSpline::Vector2 n_pos = nodes[n]->Position();
		double len = sqrt((qr_posn.x - n_pos[0])*(qr_posn.x - n_pos[0]) + (qr_posn.y - n_pos[1])*(qr_posn.y - n_pos[1]));
		if (min_len>=len && len!=0)
		{
			min_len   = len;
			*index    = nodes[n]->Index();
		}
	}
	return min_len;
}

void AppAlgoLetterWarping::ExtraTarget( QRWordArt::QRCharacter::Node_Targets& targets,QRWordArt::QRCharacter::Char* c )
{
	if (c->SkeletonSize()<2)
	{
		if (targets.size()==1)
		{
			QRWordArt::QRCharacter::QRNodes nodes = c->GetMainNodes();
			for (unsigned int n_id=0;n_id<nodes.size();n_id++){
				if (nodes[n_id]->FixV() && nodes[n_id]->Index()){
					QRWordArt::QRCharacter::Node_Target node_target;
					node_target.first = nodes[n_id]->Index();
					node_target.second.posn = nodes[n_id]->Position();
					node_target.second.w = 0.1;
					targets.push_back(node_target);
				}
			}
		}
	}else{
		int node_size = c->NodeSize();

		std::vector<int> check;
		check.resize(node_size,0);

		for (unsigned int i=0;i<targets.size();i++)
		{
			int idx = targets[i].first;
			check[idx] = 2;
		}

		for (int s=0; s<c->SkeletonSize(); s++)
		{
			QRWordArt::QRCharacter::QRNodes nodes = c->Skeleton(s)->GetNodes();
			bool found = false;
			for (unsigned int n=0;n<nodes.size();n++)
			{
				int idx = nodes[n]->Index();
				if (check[idx]==2){found = true; break;}
			}

			if (found)
			{
				for (unsigned int n=0;n<nodes.size();n++)
				{
					int idx = nodes[n]->Index();
					if(check[idx]!=2)check[idx]=1;
				}
			}
		}

		for (int s=0; s<c->SkeletonSize(); s++)
		{
			QRWordArt::QRCharacter::QRNodes nodes = c->GetSkeletonMainNodes(s);
			for (unsigned int n_id=0;n_id<nodes.size();n_id++)
			{
				int idx = nodes[n_id]->Index();
				if ( (nodes[n_id]->FixV()||nodes[n_id]->Weight()<1) && nodes[n_id]->Main() && check[idx]==0)
				{
					QRWordArt::QRCharacter::Node_Target node_target;
					node_target.first = idx;
					node_target.second.posn = c->Node(idx)->Position();
					node_target.second.w = 0.1;
					targets.push_back(node_target);
				}
			}
		}
	}
}

bool AppAlgoLetterWarping::CheckOffside( QRWordArt::QRCharacter::QRNode* node,QRWordArt::QRCharacter::Node_Target& target,const QRWordArt::QRStringLine::QRSample& qr_sample )
{
	double u,v;
	node->StringLine()->World2Local(target.second.posn[0],target.second.posn[1],&u,&v);

	double error = 0.8;
	return abs(v) > 1+error;
}

bool AppAlgoLetterWarping::CheckAvoid( QRWordArt::QRCharacter::Node_Target& target,const QRWordArt::QRStringLine::QRSample& qr_sample )
{
	HSSSpline::Vector2 node_pos = qr_sample.qr_char->Node(target.first)->Position();
	HSSSpline::Vector2 target_pos = target.second.posn;
	HSSSpline::Vector2 vec = target_pos - node_pos;
	HSSSpline::Vector2 inv_pos= node_pos - vec;

	double min_len = 999999999;
	for (int i=0;i<qr_sample.qr_char->NodeSize();i++)
	{
		if (i==target.first)continue;
		HSSSpline::Vector2 pos = qr_sample.qr_char->Node(i)->Position();
		double len = (pos[0]-inv_pos[0])*(pos[0]-inv_pos[0])+(pos[1]-inv_pos[1])*(pos[1]-inv_pos[1]);
		if (min_len>len){min_len = len;}
	}
	return min_len > qr_sample.qr_char->StringLine()->get_w(qr_sample.sample)*0.1;
}