#include "StdAfx.h"
#include "AppAlgoModuleSelection.h"

AppAlgoModuleSelection::AppAlgoModuleSelection( HKCAppItem^ _appItem )
{
	m_ImgW = _appItem->Data->WordArtEvi.segment_img.cols;
	m_ImgH = _appItem->Data->WordArtEvi.segment_img.rows;
	m_QRcode = &_appItem->Data->QRCData;
	std::vector<int>& seg_id = _appItem->Data->WordArtEvi.seg_pids;
	m_Module_map.create(m_QRcode->QRCImg.rows,m_QRcode->QRCImg.cols,CV_32F);
	int pSize = _appItem->Data->QRCData.module_size;

	for (unsigned int i=0; i<m_QRcode->QRCImg.rows;++i)
	{
		for (unsigned int j=0; j<m_QRcode->QRCImg.cols;++j)
		{
			m_Module_map.at<float>(i,j) = -1;
		}
	}

	for (unsigned int idx=0; idx<seg_id.size();++idx)
	{
		int pid = seg_id[idx];
		int offsetX = m_QRcode->Patches[pid]->patch_Pos.x;
		int offsetY = m_QRcode->Patches[pid]->patch_Pos.y;

		for (int i=0;i<pSize;i++)
		{
			for (int j=0;j<pSize;j++)
			{
				m_Module_map.at<float>(i+offsetX,j+offsetY) = pid;
			}
		}
	}
}

std::vector<int> AppAlgoModuleSelection::SelectModule( cv::Mat& target )
{
	std::vector<int> pids;
	std::vector<bool> assign;
	assign.resize(m_QRcode->Patches.size(),false);

	for (int i=0; i<target.cols; i++)
	{
		for (int j=0;j<target.rows;j++)
		{
			int idx = i*target.rows+j;
			if (target.data[idx*3]==0)
			{
				int p = m_Module_map.at<float>(j,i);
				if (p>0){assign[p] = true;}
			}
		}
	}

	for (int i=0;i<assign.size();i++)
	{
		if (assign[i])
		{
			pids.push_back(i);
		}
	}

	return pids;
}

int AppAlgoModuleSelection::SelectModule( cv::Point2f& target )
{
	return  m_Module_map.at<float>(target.x,target.y);
}

std::vector<int> AppAlgoModuleSelection::SelectModule_Voting( cv::Mat& target,int size )
{
	std::vector<int> seg_pids;
	for (int pid=0;pid<m_QRcode->Patches.size();pid++)
	{
		cv::Point module_posn = m_QRcode->Patches[pid]->grid_sample_Pos;
		int count = 0;

		for (int i=-size*0.5; i<size*0.5; ++i)
		{
			for (int j=-size*0.5; j<size*0.5; ++j)
			{
				int idx = (module_posn.y+i)*target.rows+(module_posn.x+j);
				if (target.data[idx] != 255){count++;}
			}
		}

		if(count>size*size*0.25)seg_pids.push_back(pid);
	}
	return seg_pids;
}

AppAlgoModuleSelection::CM_Map AppAlgoModuleSelection::CharModuleMapping( std::vector<int> pids, HKCQRCData* qrcode, int bg_color, QRWordArt::QRStringLines& strings )
{
	CM_Map map;
	cv::Point2d offset(qrcode->offset.x,qrcode->offset.y);
	for (unsigned int i=0;i<pids.size();i++)
	{
		printf("\r locating...%d/%d        ",i,pids.size());
		int p_id = pids[i];

		cv::Point2d qr_posn = qrcode->Patches[p_id]->patch_Pos;
		qr_posn.x += 0.5*qrcode->module_size; 
		qr_posn.y += 0.5*qrcode->module_size;
		qr_posn.x +=offset.x;
		qr_posn.y = m_ImgH - qr_posn.y -offset.y;
		QRWordArt::QRCharacter::VecChar vec_char = CharInRange( qr_posn,qrcode->module_size*1.5,strings);
		if (bg_color!=qrcode->Patches[p_id]->qr_color)//Cover
		{
			int node_idx=-1;
			int char_idx=-1;
			double min_len = 999999999;
			for (unsigned int c_id = 0;c_id<vec_char.size();c_id++)
			{
				QRWordArt::QRCharacter::QRNodes nodes = vec_char[c_id]->GetNodes();
				int n_id;
				double len = NearestNode(nodes,qr_posn,qrcode->module_size*1.5,&n_id);
				if (min_len>len)
				{
					min_len = len;
					node_idx = n_id;
					char_idx = c_id;
				}
			}

			if (node_idx!=-1 && char_idx!=-1)
			{
				map[vec_char[char_idx]].push_back(p_id);
			}
		}
		else//Avoid
		{
			for (unsigned int c_id = 0;c_id<vec_char.size();c_id++)
			{
				map[vec_char[c_id]].push_back(p_id);
			}
		}
	}
	printf("\r locating...Done                        \n");
	return map;
}

QRWordArt::QRCharacter::VecChar AppAlgoModuleSelection::CharInRange( cv::Point posn,double range,QRWordArt::QRStringLines& strings )
{
	QRWordArt::QRCharacter::VecChar chars;
	for (unsigned int s_id = 0;s_id<strings.size();s_id++)
	{
		for (unsigned int c_id = 0;c_id<strings[s_id]->size();c_id++)
		{
			if ((*strings[s_id])[c_id].qr_char==NULL)continue;

			HSSSpline::PathPoint<2> char_posn = strings[s_id]->get_position((*strings[s_id])[c_id].sample);
			double len = sqrt((char_posn[0]-posn.x)*(char_posn[0]-posn.x) + (char_posn[1]-posn.y)*(char_posn[1]-posn.y));
			if (len<=range)
			{
				chars.push_back((*strings[s_id])[c_id].qr_char);
			}
		}
	}
	return chars;
}

double AppAlgoModuleSelection::NearestNode( QRWordArt::QRCharacter::QRNodes& nodes,cv::Point2d qr_posn,double threhold,int* index )
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
