#include "StdAfx.h"
#include "AppAlgoQRCodeTest.h"

#include "AppAlgoProbabilityModule.h"
#include "AppAlgoQRCodeEvaluation.h"
#include "AppAlgoProbabilityModel.h"
#include "AppAlgoQRCodeRenderer.h"
#include "AppAlgoZBar.h"
#include "AppAlgoZXing.h"

void AppFrame::AppAlgoQRCodeTest::DrawModule_RI( cv::Point& posn, int color, int size, int r_num,cv::Mat* dst )
{
	std::vector<int> r_idx;
	for (int i=0;i<r_num;)
	{
		int idx = rand()%(size*size);
		if (find(r_idx.begin(),r_idx.end(),idx)==r_idx.end())
		{
			r_idx.push_back(idx);
			i++;
		}
	}

	int k=0;
	for (int i=-size*0.5; i<size*0.5; ++i)
	{
		for (int j=-size*0.5; j<size*0.5; ++j)
		{
			int idx = (posn.y+i)*dst->cols+(posn.x+j);
			if (find(r_idx.begin(),r_idx.end(),k)!=r_idx.end()){dst->data[idx] = color; }
			k++;
		}
	}
}

void AppFrame::AppAlgoQRCodeTest::DrawModule_I(cv::Point & posn, int color, int size, cv::Mat * dst)
{
	for (int i = -size * 0.5; i<size*0.5; ++i)
	{
		for (int j = -size * 0.5; j<size*0.5; ++j)
		{
			int idx = (posn.y + i)*dst->cols + (posn.x + j);
			dst->data[idx] = color;
		}
	}
}

void AppFrame::AppAlgoQRCodeTest::DrawModule_Ring( cv::Point& posn, int color, int out_size, int in_size,cv::Mat* dst )
{
	for (int i=-out_size*0.5; i<out_size*0.5; ++i)
	{
		for (int j=-out_size*0.5; j<out_size*0.5; ++j)
		{
			if (abs(i)<=in_size*0.5 && abs(j)<=in_size*0.5)continue;

			int idx = (posn.y+i)*dst->cols+(posn.x+j);
			dst->data[idx] = color; 
		}
	}
}

std::vector<int> AppFrame::AppAlgoQRCodeTest::RandomModule( int num )
{
	std::vector<int> r_idx;
	for (int i=0;i<num;)
	{
		int idx = rand()%8;
		if (find(r_idx.begin(),r_idx.end(),idx)==r_idx.end())
		{
			r_idx.push_back(idx);
			i++;
		}
	}
	return r_idx;
}

void AppFrame::AppAlgoQRCodeTest::CreateTestingData(HKCQRCData& qrcData,int pSize,int iSize,int num_module,int num_pixel,cv::Mat& test1,cv::Mat& test2)
{
	test1 = cv::Mat(qrcData.QRCImg.cols,qrcData.QRCImg.rows, CV_8UC3);
	for (int i=0;i<qrcData.Patches.size();i++)
	{
		cv::Point posn = qrcData.Patches[i]->grid_sample_Pos;
		int idx = posn.x + posn.y * qrcData.QRCImg.cols;
		int color = qrcData.Patches[i]->qr_color;
		AppAlgoQRCodeRenderer::DrawModule3(posn,color,color,color,pSize,&test1);
	}

	std::vector<int> modules;
	for (int i=0;i<qrcData.CWData.size();i++)
	{
		for (int j=0;j<qrcData.CWData[i].size();j++)
		{
			int m_rand = num_module;
			if (num_module == -1)m_rand = rand()%8;
			std::vector<int> rand_module = RandomModule(m_rand);

			for (int m=0;m<rand_module.size();m++)
			{
				int module_idx = qrcData.CWData[i][j].module_idx[rand_module[m]];
				modules.push_back(module_idx);
				cv::Point posn = qrcData.Patches[module_idx]->grid_sample_Pos;
				int idx = posn.x + posn.y * qrcData.QRCImg.cols;

				int p_rand = num_pixel;
				if (num_pixel == -1)p_rand = rand()%(iSize*iSize);
			
				if (p_rand>0){
					
					if (num_pixel>=iSize*iSize){
						int color = 255-qrcData.Patches[module_idx]->qr_color;
						AppAlgoQRCodeRenderer::DrawModule3(posn,color,color,color,iSize,&test1);
					}else DrawModule_RI(posn,255-qrcData.Patches[module_idx]->qr_color,iSize,p_rand,&test1);
				}
			}
		}
	}

	test2 = test1.clone();
	for (int i=0;i<modules.size();i++)
	{
		int module_idx = modules[i];
		cv::Point posn = qrcData.Patches[module_idx]->grid_sample_Pos;
		int idx = posn.x + posn.y * qrcData.QRCImg.cols;
		if (qrcData.Modules[module_idx]->Type==0)
		{DrawModule_Ring(posn,255 - qrcData.Patches[module_idx]->qr_color,pSize,iSize,&test2);}
	}
}

double AppFrame::AppAlgoQRCodeTest::CalThreshold( int target,std::vector<double>& cw_prob,double head,double tail,int iter)
{
	iter++;
	double threshold = (head+tail)*0.5;
	
	int count = 0;
	for (int i=0;i<cw_prob.size();i++)
	{
		if (cw_prob[i]>threshold){count++;}
	}

	if (count<target){tail=threshold;}
	else if(count>target){head=threshold;}
	else return threshold;

	if (iter>100){return threshold;}
	else return CalThreshold(target,cw_prob,head,tail,iter);
}

double AppFrame::AppAlgoQRCodeTest::CalThreshold( int target,std::vector<double>& cw_prob )
{
	return CalThreshold(target,cw_prob,0.0,1.0,0.0);
}

cv::Mat AppFrame::AppAlgoQRCodeTest::addGaussianNoise( cv::Mat &matI, int mean, int stddev )
{
	cv::Mat matO;

	vector<cv::Mat> channels(3);
	split( matI, channels);

	cv::Mat gaussian_noise = cv::Mat::zeros( matI.rows, matI.cols, CV_8U );
	randn( gaussian_noise, mean, stddev);

	for(int i=0;i<matI.channels();i++)
		channels[i] = channels[i] + gaussian_noise;

	merge(channels,matO);

	return matO;
}

cv::Mat AppFrame::AppAlgoQRCodeTest::addSaltAndPepperNoise( cv::Mat &matI, int lowerBound, int upperBound )
{
	cv::Mat matO;

	cv::Mat saltpepper_noise = cv::Mat::zeros(matI.rows, matI.cols,CV_8U);
	randu(saltpepper_noise,0,255);

	cv::Mat black = saltpepper_noise < lowerBound;
	cv::Mat white = saltpepper_noise > upperBound;

	matO = matI.clone();
	matO.setTo(255,white);
	matO.setTo(0,black);

	return matO;
}

std::vector<int> AppFrame::AppAlgoQRCodeTest::SortCWModule( std::vector<int>& module_idx,std::vector<double>& module_energy )
{
	std::vector<int>     sort_module_idx;
	std::vector<double>  sort_module_energy;
	for (int i=0;i<module_idx.size();i++)
	{
		int id = module_idx[i];
		sort_module_idx.push_back(id);
		sort_module_energy.push_back(module_energy[id]);
	}

	for (int i=0;i<sort_module_idx.size()-1;i++)
	{
		for (int j=i+1;j<sort_module_idx.size();j++)
		{
			if (sort_module_energy[j]>sort_module_energy[i])
			{
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

bool AppFrame::AppAlgoQRCodeTest::Execute( HKCAppItem^ _appItem )
{
	int wa,da;
	wa = _appItem->Data->QRCData.module_size;
	da = _appItem->Data->QRCData.center_size;

	HKCQRCData& qrcData = _appItem->Data->QRCData;
	QRCWData& cw_data   = qrcData.CWData;

	cv::Mat qrImage = _appItem->Data->QRCData.QRCImg.clone();

	AppAlgoProbabilityModule algo_Em(_appItem);
	AppAlgoProbabilityModel algo_Pcw(_appItem);

	double threshold[4];
	double t   = _appItem->Data->QRCData.cw_error_thershold;
	double s   = _appItem->Data->QRCData.cw_error_thershold_std;
	double c[] = {1,0,-1,-2};

	for (int i=0;i<4;i++){threshold[i] = t+s*c[i];}
	for (int c=0;c<4;c++)
	{
		double low  = (c+1>4)?threshold[c+1]:0;
		double high = threshold[c];
		for (int n=0;n<100;n++)
		{
			cv::Mat exp = qrImage.clone();
			std::vector<double> module_Energy = algo_Em.Execute(qrImage);
			for (int rs_idx=0;rs_idx<cw_data.size();rs_idx++)
			{
				for (int cw_idx=0;cw_idx<cw_data[rs_idx].size();cw_idx++)
				{
// 					if (cw_idx < cw_data[rs_idx].max_error)
// 					{
// 						for (int m=0;m<cw_data[rs_idx][cw_idx].module_idx.size();m++)
// 						{
// 							int id = cw_data[rs_idx][cw_idx].module_idx[m];
// 							cv::Point posn = qrcData.Patches[id]->grid_sample_Pos;
// 							DrawModule_C1(posn,255-qrcData.Patches[id]->qr_color,wa,&exp);
// 						}
// 					}else
					{
						std::vector<int> module_idx;
						for (int m=0;m<cw_data[rs_idx][cw_idx].module_idx.size();m++){module_idx.push_back(cw_data[rs_idx][cw_idx].module_idx[m]);}
						for (int m=0;m<module_idx.size();m++)
						{
							int r = rand()%module_idx.size();
							int temp = module_idx[m];
							module_idx[m] = module_idx[r];
							module_idx[r] = temp;
						}

						for (int m=0;m<module_idx.size();m++)
						{
							int id = module_idx[m];
							cv::Point posn = qrcData.Patches[id]->grid_sample_Pos;

							int r = rand()%(da*da+1);
							bool flag = false;
// 							while (true)
// 							{
//								DrawModule_RI(posn,255-qrcData.Patches[id]->qr_color,da,r,&exp);
//								module_Energy[id] = algo_Em.Execute_Module(exp,id);
// 								double pcw = algo_Pcw.Execute_CW(cw_data[rs_idx][cw_idx],module_Energy);
// 								if (pcw>low && pcw<high)
// 								{
// 									flag = true;
// 									break;
// 								}else if(pcw>high){
// 									DrawModule_C1(posn,qrcData.Patches[id]->qr_color,da,&exp);
// 									module_Energy[id] = 0;
// 									r--;
// 								}else{break;}
// 							}
							//if(flag){break;}
								int r2 = rand()%2;
								if (r2)
								{
									DrawModule_Ring(posn,255-qrcData.Patches[id]->qr_color,wa,da,&exp);
								}
						}
					}
				}
			}
			char buff2[1000];
			sprintf(buff2,"F:\\Current Project\\QR Code\\EXP4_%d\\%03d.png",c,n);
			cv::imwrite(buff2,exp);
		}
	}
	return true;
}

bool AppFrame::AppAlgoQRCodeTest::Execute2(HKCAppItem ^ _appItem)
{
	int wa, da;
	wa = _appItem->Data->QRCData.module_size;
	da = _appItem->Data->QRCData.center_size;

	HKCQRCData& qrcData = _appItem->Data->QRCData;
	QRCWData& cw_data = qrcData.CWData;

	AppAlgoProbabilityModule algo_Em(_appItem);

	double error = 0;
	double num = 0;
	cv::Mat qrImage = _appItem->Data->QRCData.QRCImg.clone();
	for (int i = 0; i<qrcData.Patches.size(); i++)
	{
		if (qrcData.Modules[i]->Type > 1){continue;}
		cv::Point posn = qrcData.Patches[i]->grid_sample_Pos;
		int color = qrcData.Patches[i]->qr_color;
		//DrawModule_Ring(posn, 255 - color, wa, da, &qrImage);
		DrawModule_I(posn, 255 - color, da, &qrImage);
		error += algo_Em.Execute_Module(qrImage, i, false);
		num ++ ;
		
	}
	error /= num;
	std::cout << error << std::endl;
	HKCZBarGridSampling zbar;
	zbar.Execute_Detect(_appItem, qrImage);

	HKCZBarGridSampling zxing;
	zxing.Execute_Detect(_appItem, qrImage);

	std::cout << error << "," << (double)zbar.N_ErrorModule()/num  <<","<< (double)zxing.N_ErrorModule()/num << std::endl;
	cv::imshow("QR",qrImage);
	return true;
}
