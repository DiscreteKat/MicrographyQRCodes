#include "stdafx.h"
#include <string>
#include <errno.h>
#include <conio.h>
#include <ctype.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <wchar.h>
#include <vector>


#include "AppAlgoEncodingRSModify.h"

#include "QREncode/qrencode.h"
#include "QREncode/qrspec.h"
#include "QREncode/rscode.h"

#include <iostream>
#include <opencv\cv.h>
#include <opencv\highgui.h>

void AppAlgoRSModify::JHgaussianMethod_clearMatrix(){
	for(int i=0;i<m_GaussianMatrix.size();i++)
		m_GaussianMatrix[i].clear();
	m_GaussianMatrix.clear();
	if(m_GaussianMatrix.size()!=0)std::cout<<"MATRIX not cleared!!!!!"<<std::endl;
}

void AppAlgoRSModify::JHgaussianMethod_buildMatrix(int x,int n){
	unsigned char *data;
	unsigned char *ecc;
	int dl,el;
	if(x==1){
		dl=m_QRCData->RSBdcNum[0];
		el=m_QRCData->RSBecNum[0];
	}else{
		dl=m_QRCData->RSBdcNum[1];
		el=m_QRCData->RSBecNum[1];
	}

	m_GaussianMatrix.resize(dl*8);
	RS* rs = init_rs(8, 0x11d, 0, 1, el, 255 - dl - el);
	for(int k=0;k<dl*8;k++){							//k*8
		data = new unsigned char[dl];
		ecc  = new unsigned char[el];

		for(int j=0;j<dl;j++){
			data[j]=0x00;
			if(k/8==j){
				if(k%8==0){data[j]=data[j]|0x80;}
				else if(k%8==1){data[j]=data[j]|0x40;}
				else if(k%8==2){data[j]=data[j]|0x20;}
				else if(k%8==3){data[j]=data[j]|0x10;}
				else if(k%8==4){data[j]=data[j]|0x08;}
				else if(k%8==5){data[j]=data[j]|0x04;}
				else if(k%8==6){data[j]=data[j]|0x02;}
				else if(k%8==7){data[j]=data[j]|0x01;}
			}
		}
		encode_rs_char(rs, data, ecc);

		m_GaussianMatrix[k].clear();
		m_GaussianMatrix[k].resize((dl+el)*8);
		for(int h=0;h<dl;h++){
			m_GaussianMatrix[k][h*8+0]=((data[h]&0x80)?1:0);
			m_GaussianMatrix[k][h*8+1]=((data[h]&0x40)?1:0);
			m_GaussianMatrix[k][h*8+2]=((data[h]&0x20)?1:0);
			m_GaussianMatrix[k][h*8+3]=((data[h]&0x10)?1:0);
			m_GaussianMatrix[k][h*8+4]=((data[h]&0x08)?1:0);
			m_GaussianMatrix[k][h*8+5]=((data[h]&0x04)?1:0);
			m_GaussianMatrix[k][h*8+6]=((data[h]&0x02)?1:0);
			m_GaussianMatrix[k][h*8+7]=((data[h]&0x01)?1:0);
		}
		for(int h=0;h<el;h++){
			m_GaussianMatrix[k][dl*8+h*8+0]=((ecc[h]&0x80)?1:0);
			m_GaussianMatrix[k][dl*8+h*8+1]=((ecc[h]&0x40)?1:0);
			m_GaussianMatrix[k][dl*8+h*8+2]=((ecc[h]&0x20)?1:0);
			m_GaussianMatrix[k][dl*8+h*8+3]=((ecc[h]&0x10)?1:0);
			m_GaussianMatrix[k][dl*8+h*8+4]=((ecc[h]&0x08)?1:0);
			m_GaussianMatrix[k][dl*8+h*8+5]=((ecc[h]&0x04)?1:0);
			m_GaussianMatrix[k][dl*8+h*8+6]=((ecc[h]&0x02)?1:0);
			m_GaussianMatrix[k][dl*8+h*8+7]=((ecc[h]&0x01)?1:0);	
		}
		delete [] data;
		delete [] ecc;
	}
}

void AppAlgoRSModify::JHgaussianMethod_initialControlList(int x,int n){
	if(x==1){
		int dl=m_QRCData->RSBdcNum[0], el=m_QRCData->RSBecNum[0];
		for(int j=0;j<dl*8;j++)
		{
			if(!JHisRandomLocation(m_BlockLocation[n][j]) || JHisEssentialInform(m_BlockLocation[n][j]))
			{
				m_ControlList[0].push_back(j);
				m_ControlList[1].push_back(j);
			}
		}
	}else if(x==2){
		if(m_QRCData->RSBNum[1]!=0){
			int dl=m_QRCData->RSBdcNum[1], el=m_QRCData->RSBecNum[1];
			for(int j=0;j<dl*8;j++){
				if(!JHisRandomLocation(m_BlockLocation[n+m_QRCData->RSBNum[0]][j]) || JHisEssentialInform(m_BlockLocation[n+m_QRCData->RSBNum[0]][j]))
				{
					m_ControlList[0].push_back(j);
					m_ControlList[1].push_back(j);
				}
			}
		}
	}
}

void AppAlgoRSModify::JHgaussianMethod_addECCControl(int x,int n){
	if(x==1){
		int dl=m_QRCData->RSBdcNum[0], el=m_QRCData->RSBecNum[0];
		for(int j=0;j<(el+dl)*8;j++){
				if( !JHisRandomLocation(m_BlockLocation[n][j])){JHgaussianMethod_addcontrolBit(j);}
		}
	}else if(x==2){
		if(m_QRCData->RSBNum[1]!=0){
			int dl=m_QRCData->RSBdcNum[1], el=m_QRCData->RSBecNum[1];
			for(int j=0;j<(el+dl)*8;j++){
					if( !JHisRandomLocation(m_BlockLocation[m_QRCData->RSBNum[0]+n][j])){JHgaussianMethod_addcontrolBit(j);}
			}
		}
	}
}

void AppAlgoRSModify::JHgaussianMethod_addcontrolBit(int k){	
	//first not controled row with 1
	for(int i=0;i<m_GaussianMatrix.size();i++)
	{
		bool isIncontrolList = false;
		for(int c=0;c<m_ControlList[1].size();c++){if(i==m_ControlList[1][c]){isIncontrolList=true;break;}}	//make sure row i is not in the control list
		if(isIncontrolList == false)
		{
			if	(m_GaussianMatrix[i][k]==1 )
			{
				JHgaussianMethod_XORnotZeroRowAll(i,k);
				m_ControlList[0].push_back(k);
				m_ControlList[1].push_back(i);
				break;
			}
		}
	}
}

void AppAlgoRSModify::JHgaussianMethod_combineBitAndCopy(int x,int n){
	for(int j=0;j<m_ControlList[0].size();j++){
		int sum=0;
		for(int f=0;f<m_GaussianMatrix.size();f++)
			if(m_GaussianMatrix[f][m_ControlList[0][j]]==1)sum++;
		if(sum==1)/*cout<<" correct "*/;else std::cout<<" error ";
	}

	int i=n;
	int *ctemp = new int [m_GaussianMatrix[0].size()];
	for(int j=0;j<m_GaussianMatrix[0].size();j++)ctemp[j]=0;
	for(int j=0;j<m_ControlList[0].size();j++){
		if(x==1){
			if(m_BlockLocation[n][m_ControlList[0][j]]<m_QRCData->QRCBitData.JHbitsStreamModeLength+m_QRCData->QRCBitData.JHbitsStreamCounterLength+m_QRCData->QRCBitData.JHbitsStreamRealStringLength+m_QRCData->QRCBitData.JHbitsStreamTerminatorLength)
			{
				if(m_BitsStream[m_BlockLocation[n][m_ControlList[0][j]]]==1){
					for(int c=0;c<m_GaussianMatrix[0].size();c++){
						if(ctemp[c]==0 && m_GaussianMatrix[m_ControlList[1][j]][c]==0)	   ctemp[c]=0;
						else if(ctemp[c]==0 && m_GaussianMatrix[m_ControlList[1][j]][c]==1)ctemp[c]=1;
						else if(ctemp[c]==1 && m_GaussianMatrix[m_ControlList[1][j]][c]==0)ctemp[c]=1;
						else if(ctemp[c]==1 && m_GaussianMatrix[m_ControlList[1][j]][c]==1)ctemp[c]=0;
					}
				}
			}
			else if(m_SampleStreamBits[m_BlockLocation[n][m_ControlList[0][j]]]==1){
				for(int c=0;c<m_GaussianMatrix[0].size();c++){
					if(ctemp[c]==0 && m_GaussianMatrix[m_ControlList[1][j]][c]==0)	   ctemp[c]=0;
					else if(ctemp[c]==0 && m_GaussianMatrix[m_ControlList[1][j]][c]==1)ctemp[c]=1;
					else if(ctemp[c]==1 && m_GaussianMatrix[m_ControlList[1][j]][c]==0)ctemp[c]=1;
					else if(ctemp[c]==1 && m_GaussianMatrix[m_ControlList[1][j]][c]==1)ctemp[c]=0;
				}
			}
		}
		else if(x==2){
			if(m_BlockLocation[m_QRCData->RSBNum[0]+n][m_ControlList[0][j]]<m_QRCData->QRCBitData.JHbitsStreamModeLength+m_QRCData->QRCBitData.JHbitsStreamCounterLength+m_QRCData->QRCBitData.JHbitsStreamRealStringLength+m_QRCData->QRCBitData.JHbitsStreamTerminatorLength){
				if(m_BitsStream[m_BlockLocation[m_QRCData->RSBNum[0]+n][m_ControlList[0][j]]]==1){
					for(int c=0;c<m_GaussianMatrix[0].size();c++){
						if(ctemp[c]==0 && m_GaussianMatrix[m_ControlList[1][j]][c]==0)	   ctemp[c]=0;
						else if(ctemp[c]==0 && m_GaussianMatrix[m_ControlList[1][j]][c]==1)ctemp[c]=1;
						else if(ctemp[c]==1 && m_GaussianMatrix[m_ControlList[1][j]][c]==0)ctemp[c]=1;
						else if(ctemp[c]==1 && m_GaussianMatrix[m_ControlList[1][j]][c]==1)ctemp[c]=0;
					}
				}
			}
			else if(m_SampleStreamBits[m_BlockLocation[m_QRCData->RSBNum[0]+n][m_ControlList[0][j]]]==1){
				for(int c=0;c<m_GaussianMatrix[0].size();c++){
					if(ctemp[c]==0 && m_GaussianMatrix[m_ControlList[1][j]][c]==0)	   ctemp[c]=0;
					else if(ctemp[c]==0 && m_GaussianMatrix[m_ControlList[1][j]][c]==1)ctemp[c]=1;
					else if(ctemp[c]==1 && m_GaussianMatrix[m_ControlList[1][j]][c]==0)ctemp[c]=1;
					else if(ctemp[c]==1 && m_GaussianMatrix[m_ControlList[1][j]][c]==1)ctemp[c]=0;
				}
			}
		}
	}

	if(x==1){
		for(int j=0;j<m_GaussianMatrix[0].size();j++)m_BitsStream[m_BlockLocation[n][j]]=ctemp[j];
	}else if(x==2){
		if(m_QRCData->RSBNum[1]!=0){
			for(int j=0;j<m_GaussianMatrix[0].size();j++)m_BitsStream[m_BlockLocation[m_QRCData->RSBNum[0]+n][j]]=ctemp[j];
		}
	}
	delete [] ctemp;
}

void AppAlgoRSModify::JHgaussianMethod_XORnotZeroRowAll(int a,int k){	// all xor ecept a
	for(int i=0;i<m_GaussianMatrix.size();i++){
		if(a!=i && m_GaussianMatrix[i][k]==1){
			JHgaussianMethod_XORRow(i,a);
		}
	}	
}

void AppAlgoRSModify::JHgaussianMethod_XORRowAll(int a){	// all xor ecept a
	for(int i=0;i<m_GaussianMatrix.size();i++){
		if(a!=i){
			JHgaussianMethod_XORRow(i,a);
		}
	}
}

void AppAlgoRSModify::JHgaussianMethod_XORRow(int a,int b){	//a is dest
	for(int i=0;i<m_GaussianMatrix[a].size();i++){
		if(m_GaussianMatrix[b][i]==0 && m_GaussianMatrix[a][i]==0)		m_GaussianMatrix[a][i]=0;
		else if(m_GaussianMatrix[b][i]==0 && m_GaussianMatrix[a][i]==1)m_GaussianMatrix[a][i]=1;
		else if(m_GaussianMatrix[b][i]==1 && m_GaussianMatrix[a][i]==0)m_GaussianMatrix[a][i]=1;
		else if(m_GaussianMatrix[b][i]==1 && m_GaussianMatrix[a][i]==1)m_GaussianMatrix[a][i]=0;
	}
}

void AppAlgoRSModify::JHgaussianMethod_swapRow(int a,int b){
	unsigned char temp;
	for(int i=0;i<m_GaussianMatrix[a].size();i++){
		temp=m_GaussianMatrix[a][i];
		m_GaussianMatrix[a][i]=m_GaussianMatrix[b][i];
		m_GaussianMatrix[b][i]=temp;
	}
}

void AppAlgoRSModify::JHoptimizeControlRegion(){
	for(int i=0;i<m_QRCData->RSBNum[0];i++){
		m_ControlList.resize(2);
		JHgaussianMethod_clearMatrix();
		JHgaussianMethod_buildMatrix(1,i);			//1
		JHgaussianMethod_initialControlList(1,i);	//2
		JHgaussianMethod_addECCControl(1,i);		//3
		JHgaussianMethod_combineBitAndCopy(1,i);	//4
		m_ControlList[0].clear();
		m_ControlList[1].clear();
	}
	if(m_QRCData->RSBNum[1]!=0){
		for(int i=0;i<m_QRCData->RSBNum[1];i++){
			m_ControlList.resize(2);
			JHgaussianMethod_clearMatrix();
			JHgaussianMethod_buildMatrix(2,i);			//1
			JHgaussianMethod_initialControlList(2,i);	//2
			JHgaussianMethod_addECCControl(2,i);		//3
			JHgaussianMethod_combineBitAndCopy(2,i);	//4
			m_ControlList[0].clear();
			m_ControlList[1].clear();
		}
	}
}

bool AppAlgoRSModify::JHisEssentialInform(int index){
	if(index<m_QRCData->QRCBitData.JHbitsStreamModeLength+m_QRCData->QRCBitData.JHbitsStreamCounterLength+m_QRCData->QRCBitData.JHbitsStreamRealStringLength+m_QRCData->QRCBitData.JHbitsStreamTerminatorLength)return true;
	else return false;
}

bool AppAlgoRSModify::JHisRandomLocation(int index){
	if(index<m_QRCData->QRCBitData.JHbitsStreamModeLength+m_QRCData->QRCBitData.JHbitsStreamCounterLength+m_QRCData->QRCBitData.JHbitsStreamRealStringLength+m_QRCData->QRCBitData.JHbitsStreamTerminatorLength)return false;
	else if(	m_RandomLocationStream[index]==0	)return true;
	return false;
}

void AppAlgoRSModify::JHsampleStreamBitsMasking(){
	for(int k=0; k<m_QRCData->QRCBitData.JHbitsStreamTotalLength;k++){
		int x=m_QRCData->QRCBitData.JHbitsStreamLocation[k] % JHwidth;
		int y=m_QRCData->QRCBitData.JHbitsStreamLocation[k] / JHwidth;
		if(m_QRMask==0 && (x+y)%2==0){
			if(m_SampleStreamBits[k]==1)m_SampleStreamBits[k]=0;	else m_SampleStreamBits[k] = 1;
		}
		else if(m_QRMask==1 && y%2==0){
			if(m_SampleStreamBits[k]==1)m_SampleStreamBits[k]=0;	else m_SampleStreamBits[k] = 1;
		}
		else if(m_QRMask==2 && x%3==0){
			if(m_SampleStreamBits[k]==1)m_SampleStreamBits[k]=0;  else m_SampleStreamBits[k] = 1;
		}
		else if(m_QRMask==3 && (y+x)%3==0){
			if(m_SampleStreamBits[k]==1)m_SampleStreamBits[k]=0;	else m_SampleStreamBits[k] = 1;
		}
		else if(m_QRMask==4 && ((int)(y/2)+(int)(x/3))%2==0){
			if(m_SampleStreamBits[k]==1)m_SampleStreamBits[k]=0;	else m_SampleStreamBits[k] = 1;
		}
		else if(m_QRMask==5 && ((x*y)%2+(x*y)%3)==0){
			if(m_SampleStreamBits[k]==1)m_SampleStreamBits[k]=0;	else m_SampleStreamBits[k] = 1;
		}
		else if(m_QRMask==6 && ((x*y)%2+(x*y)%3)%2==0){
			if(m_SampleStreamBits[k]==1)m_SampleStreamBits[k]=0;	else m_SampleStreamBits[k] = 1;
		}
		else if(m_QRMask==7 && ((x+y)%2+(x*y)%3)%2==0){
			if(m_SampleStreamBits[k]==1)m_SampleStreamBits[k]=0;	else m_SampleStreamBits[k] = 1;
		}
	}
}

void AppAlgoRSModify::JHbitsStreamMasking(){
	for(int k=0; k<m_QRCData->QRCBitData.JHbitsStreamTotalLength;k++){
		int x=m_QRCData->QRCBitData.JHbitsStreamLocation[k] % JHwidth;
		int y=m_QRCData->QRCBitData.JHbitsStreamLocation[k] / JHwidth;
		if(m_QRMask==0 && (x+y)%2==0){
			if(m_BitsStream[k]==1)m_BitsStream[k]=0;	else m_BitsStream[k] = 1;
		}
		else if(m_QRMask==1 && y%2==0){
			if(m_BitsStream[k]==1)m_BitsStream[k]=0;	else m_BitsStream[k] = 1;
		}
		else if(m_QRMask==2 && x%3==0){
			if(m_BitsStream[k]==1)m_BitsStream[k]=0;  else m_BitsStream[k] = 1;
		}
		else if(m_QRMask==3 && (y+x)%3==0){
			if(m_BitsStream[k]==1)m_BitsStream[k]=0;	else m_BitsStream[k] = 1;
		}
		else if(m_QRMask==4 && ((int)(y/2)+(int)(x/3))%2==0){
			if(m_BitsStream[k]==1)m_BitsStream[k]=0;	else m_BitsStream[k] = 1;
		}
		else if(m_QRMask==5 && ((x*y)%2+(x*y)%3)==0){
			if(m_BitsStream[k]==1)m_BitsStream[k]=0;	else m_BitsStream[k] = 1;
		}
		else if(m_QRMask==6 && ((x*y)%2+(x*y)%3)%2==0){
			if(m_BitsStream[k]==1)m_BitsStream[k]=0;	else m_BitsStream[k] = 1;
		}
		else if(m_QRMask==7 && ((x+y)%2+(x*y)%3)%2==0){
			if(m_BitsStream[k]==1)m_BitsStream[k]=0;	else m_BitsStream[k] = 1;
		}
	}
}

void AppAlgoRSModify::JHinitialBlockLocation(){
	m_BlockLocation.resize(m_QRCData->RSBNum[0]+m_QRCData->RSBNum[1]);
	for(int i=0;i<m_QRCData->RSBNum[0];i++){
		for(int j=0;j<m_QRCData->RSBdcNum[0]*8;j++){
			m_BlockLocation[i].push_back(i*m_QRCData->RSBdcNum[0]*8+j);
		}
		for(int j=0;j<m_QRCData->RSBecNum[0]*8;j++){
			m_BlockLocation[i].push_back(m_QRCData->QRCBitData.JHbitsStreamDataLength+i*m_QRCData->RSBecNum[0]*8+j);
		}
	}

	if(m_QRCData->RSBNum[1]!=0){
		for(int i=m_QRCData->RSBNum[0];i<m_QRCData->RSBNum[1]+m_QRCData->RSBNum[0];i++){
			for(int j=0;j<m_QRCData->RSBdcNum[1]*8;j++){
				m_BlockLocation[i].push_back(m_QRCData->RSBNum[0]*m_QRCData->RSBdcNum[0]*8 +(i-m_QRCData->RSBNum[0])*m_QRCData->RSBdcNum[1]*8+j);
			}
			for(int j=0;j<m_QRCData->RSBecNum[1]*8;j++){
				m_BlockLocation[i].push_back(m_QRCData->RSBNum[0]*m_QRCData->RSBecNum[0]*8+ m_QRCData->QRCBitData.JHbitsStreamDataLength+(i-m_QRCData->RSBNum[0])*m_QRCData->RSBecNum[1]*8+j);
			}
		}
	}
}	

void AppAlgoRSModify::JHinitial(AppFrame::HKCQRCData& qrcData){
	m_QRCData = &qrcData;
	m_QRMask  = qrcData.QRMask;
	JHwidth   = 4*qrcData.Ver+17;

	m_QRCData->RSBecNum[0]  = m_QRCData->RSBecNum[0];
	m_QRCData->RSBecNum[1]  = m_QRCData->RSBecNum[1];

	m_BitsStream = new int [qrcData.QRCBitData.JHbitsStreamTotalLength];
	for(int k=0; k<qrcData.QRCBitData.JHbitsStreamTotalLength;k++)
	{
		int idx = qrcData.QRCBitData.JHbitsStreamLocation[k];
		m_BitsStream[k]=qrcData.Modules[idx]->QRC;
	}
	
	m_RandomLocationStream = new int [m_QRCData->QRCBitData.JHbitsStreamTotalLength];
	for(int k=0; k<m_QRCData->QRCBitData.JHbitsStreamTotalLength;k++){m_RandomLocationStream[k] = 0;}

	JHinitialBlockLocation();
}

bool AppAlgoRSModify::JHisPadding( int index )
{
	return index>=m_QRCData->QRCBitData.JHbitsStreamModeLength+m_QRCData->QRCBitData.JHbitsStreamCounterLength+m_QRCData->QRCBitData.JHbitsStreamRealStringLength+m_QRCData->QRCBitData.JHbitsStreamTerminatorLength && index<m_QRCData->QRCBitData.JHbitsStreamDataLength;
}

void AppAlgoRSModify::SetSampleImageBits( std::vector<int>& sample_image_bits )
{
	//put into samplebitstream
	m_SampleStreamBits = new int [m_QRCData->QRCBitData.JHbitsStreamTotalLength];
	for(int i=0;i<m_QRCData->QRCBitData.JHbitsStreamTotalLength;i++){
		m_SampleStreamBits[i] = sample_image_bits[m_QRCData->QRCBitData.JHbitsStreamLocation[i]];
	}
	JHsampleStreamBitsMasking();	
}

void AppAlgoRSModify::SetPaddingLocation( std::vector<int>& padding_location )
{
	for(int i=0;i<m_QRCData->QRCBitData.JHbitsStreamTotalLength;i++)
	{m_RandomLocationStream[i] = padding_location[m_QRCData->QRCBitData.JHbitsStreamLocation[i]];}
}

void AppAlgoRSModify::Excute()
{
	JHbitsStreamMasking();   //unmask
	JHoptimizeControlRegion(); 
	JHbitsStreamMasking();	//mask
}

bool AppAlgoRSModify::JHisEC( int index )
{
	return index>=m_QRCData->QRCBitData.JHbitsStreamDataLength;
}
