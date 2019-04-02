#include <string>
#include <vector>
#include "AppQRCData.h"

#include "qrencode/qrencode.h"

#ifndef JH_RS_MODIFY
#define JH_RS_MODIFY
class AppAlgoRSModify{
	private:
		AppFrame::HKCQRCData* m_QRCData;
		int m_QRMask;

		std::vector<std::vector<int>> m_ControlList;						//only a one in , [0]=col,[1]=row
		std::vector<std::vector<int>> m_GaussianMatrix; 
		std::vector<std::vector<int>> m_BlockLocation; 

		int *m_RandomLocationStream;//要替換的Bit位置
	public:
		int JHwidth;
		int *m_BitsStream;
		int *m_SampleStreamBits;    //要替換成的Bits

		AppAlgoRSModify():m_BitsStream(0),m_SampleStreamBits(0),m_RandomLocationStream(0){}
		~AppAlgoRSModify()
		{
			if (m_BitsStream!=NULL)delete[] m_BitsStream;
			if (m_SampleStreamBits!=NULL)delete[] m_SampleStreamBits;
			if (m_RandomLocationStream!=NULL)delete[] m_RandomLocationStream;
		}

		void JHinitial(AppFrame::HKCQRCData& qrcData);					//initial
		void SetSampleImageBits(std::vector<int>& sample_image_bits);   //smaple image to streambits
		void SetPaddingLocation(std::vector<int>& padding_location);
		void Excute();

		bool JHisEssentialInform(int bit_idx);
		bool JHisEC(int bit_idx);
		bool JHisPadding(int bit_idx);         //未修改前Padding
		bool JHisRandomLocation(int bit_idx);  //非固定區域

	private:
		void JHsampleStreamBitsMasking();

		void JHbitsStreamMasking();
		void JHoptimizeControlRegion();					//gaussian	OPTIMIZE

		void JHinitialBlockLocation();

		void JHgaussianMethod_clearMatrix();
		void JHgaussianMethod_buildMatrix(int x,int n);			//1
		void JHgaussianMethod_initialControlList(int x,int n);	//2
		void JHgaussianMethod_addECCControl(int x,int n);		//3
		void JHgaussianMethod_addcontrolBit(int k);				//3-1
		void JHgaussianMethod_combineBitAndCopy(int x,int n);	//4

		void JHgaussianMethod_swapRow(int a,int b);
		void JHgaussianMethod_XORRow(int a,int b);
		void JHgaussianMethod_XORRowAll(int a);
		void JHgaussianMethod_XORnotZeroRowAll(int a,int k);
};
#endif