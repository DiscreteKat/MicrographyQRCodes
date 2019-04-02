#include "qrFlag.h"
#include "stdafx.h"
bool locateFlag=0;
bool colorFlag=0;
int codeWFlag=0;
int maskFlag=-1;

void changeColorFlag(bool inputColorFlag){
  colorFlag=inputColorFlag;
}
void changeMaskFlag(int inputMaskFlag){
  maskFlag=inputMaskFlag;
}

void changeCodeWFlag(int inputcodeWFlag){
  codeWFlag=inputcodeWFlag;
}

void changeLocateFlag(bool inputloacteFlag){
	locateFlag = inputloacteFlag;
}