#include "StdAfx.h"
#include <omp.h>

#include "AppAlgoProbabilityModule.h"

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"

#include "AppAlgoBinarization.h"

AppAlgoProbabilityModule::AppAlgoProbabilityModule( HKCAppItem^ _appItem)
{
	m_WordArtData = &_appItem->Data->WordArtEvi;
	m_QRcode      = &_appItem->Data->QRCData;
	m_Dim	= m_QRcode->Ver*4+17;
	m_Wa	= _appItem->Data->QRCData.module_size;
	m_da	= _appItem->Data->QRCData.center_size;
	BuildSampleProbMap(m_Dim,m_Wa,m_da);
}

AppAlgoProbabilityModule::~AppAlgoProbabilityModule( void ){}

void AppAlgoProbabilityModule::Binarization_Modules( cv::Mat& src,std::vector<int>& pids,cv::Mat* dst )
{
	*dst = cv::Mat(src.cols,src.rows,CV_8UC1,cv::Scalar(128));
	AppAlgoBinarization binarization(src);

	//#pragma omp parallel for
	for (int p=0; p<pids.size(); p++)
	{
		int offset_x = m_QRcode->Patches[pids[p]]->patch_Pos.x;
		int offset_y = m_QRcode->Patches[pids[p]]->patch_Pos.y;
		for (int i= 0; i<m_Wa; i++)
		{
			for (int j=0; j<m_Wa; j++)
			{
				int idx = (offset_y+i)*src.rows+offset_x+j;
				dst->data[idx] = binarization.ZBar_Binarization(offset_x+j,offset_y+i);
			}	
		}
	}
}

std::vector<double> AppAlgoProbabilityModule::BuildSampleProb( int _Wa,int da )
{
	std::vector<double> prob;
	prob.resize(_Wa*_Wa);
	double sigma = (double)_Wa/4.0;
	double constant = 1/(sigma*sqrt(M_PI*2));
	//double constant = 1/(sigma*sigma*M_PI*2);
	double total = 0;

	//#pragma omp parallel for
	for (int i=0; i<_Wa;i++)
	{
		for (int j=0; j<_Wa;j++)
		{
			int x = abs(j-(int)(_Wa*0.5));
			int y = abs(i-(int)(_Wa*0.5));

			prob[i*_Wa+j] = constant*exp(-(double)(x*x+y*y)/(2*sigma*sigma));

			total += prob[i*_Wa+j];
			if (x<da*0.5 && y<da*0.5){prob[i*_Wa+j] = 1;} //da ¤º¬°¹s
		}
	}
	return prob;
}

void AppAlgoProbabilityModule::BuildSampleProbMap( int num,int _Wa,int da )
{
	std::vector<double> prob;
	prob = BuildSampleProb(_Wa,da);

	m_ProbMap.create(num*_Wa,num*_Wa,CV_32F);

	#pragma omp parallel for
	for (int i=0;i<num;i++)
	{
		int offset_y = i*_Wa;
		for (int j=0;j<num;j++)
		{
			int offset_x = j*_Wa;
			for (int y=0;y<_Wa;y++)
			{
				for (int x=0;x<_Wa;x++)
				{
					int idx = (offset_y+y)*_Wa + (offset_x+x);
					m_ProbMap.at<float>(offset_x+x,offset_y+y) = prob[y*_Wa+x];
				}
			}
		}
	}
}

double AppAlgoProbabilityModule::E_Derr( cv::Point module_posn,int da,cv::Mat& bImg,cv::Mat& qrImg )
{
	double err = 0;
	for (int i=-da*0.5; i<da*0.5; ++i)
	{
		for (int j=-da*0.5; j<da*0.5; ++j)
		{
			err += E_Berr( module_posn.x+j,module_posn.y+i,bImg,qrImg ) ;
		}
	}
	return err/(da*da);
}

double AppAlgoProbabilityModule::E_Berr( int x,int y,cv::Mat& bImg,cv::Mat& qrImg )
{
	int idx = y*bImg.rows+x;
	return (bImg.data[idx]!=qrImg.data[idx])?1:0;
}

double AppAlgoProbabilityModule::E_Module( cv::Point module_posn,int _Wa, int da, cv::Mat& bImg, cv::Mat& qrImg)
{
	double d_err = E_Derr(module_posn,da,bImg,qrImg);
	double energy = 0;

	for (int i=-_Wa*0.5; i<_Wa*0.5; ++i)
	{
		for (int j=-_Wa*0.5; j<_Wa*0.5; ++j)
		{
			int idx = (module_posn.y+i)*bImg.rows+(module_posn.x+j);
			double ps = m_ProbMap.at<float>(module_posn.x+j,module_posn.y+i);
			double e = ps*E_Berr(module_posn.x+j,module_posn.y+i,bImg,qrImg) + (1-ps)*d_err;

			energy += e;
		}
	}

	return energy/(_Wa*_Wa);
}

std::vector<double> AppAlgoProbabilityModule::Execute(cv::Mat& src)
{
	std::vector<double> module_energy;
	module_energy.resize(m_QRcode->Patches.size());

	AppAlgoBinarization binarization(src);
	cv::Mat bImg;
	binarization.ZBar_Binarization(&bImg);
	
//	#pragma omp parallel for
	for (int i=0;i<m_QRcode->Patches.size();i++)
	{
		double energy = E_Module(m_QRcode->Patches[i]->grid_sample_Pos,m_Wa,m_da,bImg,m_QRcode->QRCImg);
		module_energy[i]=energy;
	}

	return module_energy;
}

std::vector<double> AppAlgoProbabilityModule::Execute( cv::Mat& src,cv::Mat& qrImg )
{
	std::vector<double> module_energy;
	module_energy.resize(m_QRcode->Patches.size());

	AppAlgoBinarization binarization(src);
	cv::Mat bImg;
	binarization.ZBar_Binarization(&bImg);

	for (int i=0;i<m_QRcode->Patches.size();i++)
	{
		double energy = E_Module(m_QRcode->Patches[i]->grid_sample_Pos,m_Wa,m_da,bImg,qrImg);
		module_energy[i]=energy;
	}

	return module_energy;
}

double AppAlgoProbabilityModule::Execute_Modules_Avg( cv::Mat& src, std::vector<int>& pids )
{
	std::vector<double> energy_v = Execute_Modules(src,pids);

	double energy = 0;
	for (unsigned int i=0; i<energy_v.size();++i){energy += energy_v[i];}

	if (energy_v.size() != 0){energy/=energy_v.size();}

	return energy;
}

double AppAlgoProbabilityModule::Execute_Avg( cv::Mat& src )
{
	double module_energy = 0;

	AppAlgoBinarization binarization(src);
	cv::Mat bImg;
	binarization.ZBar_Binarization(&bImg);

	for (int i=0;i<m_QRcode->Patches.size();i++)
	{
		double energy = E_Module(m_QRcode->Patches[i]->grid_sample_Pos,m_Wa,m_da,bImg,m_QRcode->QRCImg);
		module_energy+=energy;
	}
	bImg.release();
	return module_energy/m_QRcode->Patches.size();
}

std::vector<double> AppAlgoProbabilityModule::Execute_Modules( cv::Mat& src, std::vector<int>& pids )
{
	cv::Mat bImg;
	Binarization_Modules(src,pids,&bImg);

	std::vector<double> module_energy;
	module_energy.resize(pids.size());

	for (int i=0; i<pids.size();++i)
	{
		int pid = pids[i];
		double energy= E_Module(m_QRcode->Patches[pid]->grid_sample_Pos,m_Wa,m_da,bImg,m_QRcode->QRCImg);
		module_energy[i] = energy;
	}
	bImg.release();
	return module_energy;
}

cv::Mat AppAlgoProbabilityModule::Execute_EnergyMap( cv::Mat& src )
{
	std::vector<double> module_energy = Execute(src);
	return Execute_EnergyMap( module_energy );
}

cv::Mat AppAlgoProbabilityModule::Execute_EnergyMap( std::vector<double>& energy )
{
	cv::Mat energy_map(m_QRcode->QRCode.rows,m_QRcode->QRCode.cols,CV_32FC1);
	for (int i=0;i<energy.size();i++)
	{
		energy_map.at<float>(i) = energy[i];
	}
	cv::Size size(m_QRcode->QRCImg.rows,m_QRcode->QRCImg.cols);
	cv::resize(energy_map,energy_map,size,0,0,cv::INTER_NEAREST);

	return energy_map;
}

double AppAlgoProbabilityModule::Execute_Module( cv::Mat& src, int pid, bool bin )
{
	std::vector<int> pids;
	pids.push_back(pid);

	cv::Mat bImg;
	if (bin) 
	{
		Binarization_Modules(src, pids, &bImg);
	}
	else
	{ 
		bImg = src.clone();
	}

	double energy= E_Module(m_QRcode->Patches[pid]->grid_sample_Pos,m_Wa,m_da,bImg,m_QRcode->QRCImg);
	return energy;
}
