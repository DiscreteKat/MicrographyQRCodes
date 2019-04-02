#pragma once

#include "QRWordArt/QRCharacter.h"
class AppAlgoWarpingOperator
{
public:
	AppAlgoWarpingOperator(void){};
	~AppAlgoWarpingOperator(void){};

	virtual void Execute(double param,QRWordArt::QRCharacter::Char* qr_char){};
};