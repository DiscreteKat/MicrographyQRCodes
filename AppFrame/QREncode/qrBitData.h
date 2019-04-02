#ifndef QR_BIT_DATA
#define QR_BIT_DATA

#include <vector>
struct QRBitData{
public:
	std::vector<int> JHbitsStreamLocation;		     // data+ECC's location

	int JHbitsStreamLocation_dir;		//?

	int JHbitsStreamTotalLength;		//1+2+3

	int JHbitsStreamDataLength;			//1
	int JHbitsStreamECCLength;			//2
	int JHbitsStreamRemaiderLength;		//3

	int JHbitsStreamModeLength;			//1-1
	int JHbitsStreamCounterLength;		//1-2
	int JHbitsStreamRealStringLength;	//1-3
	int JHbitsStreamTerminatorLength;	//1-4

	void operator=(QRBitData& input){
		JHbitsStreamLocation.clear();
		JHbitsStreamLocation.assign(input.JHbitsStreamLocation.begin(),input.JHbitsStreamLocation.end());

		JHbitsStreamLocation_dir   = input.JHbitsStreamLocation_dir;
		JHbitsStreamTotalLength    = input.JHbitsStreamTotalLength;
		JHbitsStreamDataLength     = input.JHbitsStreamDataLength;
		JHbitsStreamECCLength      = input.JHbitsStreamECCLength;		
		JHbitsStreamRemaiderLength = input.JHbitsStreamRemaiderLength;

		JHbitsStreamModeLength       =  input.JHbitsStreamModeLength;			
		JHbitsStreamCounterLength    =  input.JHbitsStreamCounterLength;		
		JHbitsStreamRealStringLength =  input.JHbitsStreamRealStringLength;
		JHbitsStreamTerminatorLength =  input.JHbitsStreamTerminatorLength;

	}
};
#endif
extern QRBitData g_QRBitData;