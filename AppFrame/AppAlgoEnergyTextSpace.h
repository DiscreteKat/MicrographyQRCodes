#pragma once

#include "QRWordArt/QRStringLine.h"

class AppAlgoEnergyTextSpace
{
public:
	AppAlgoEnergyTextSpace(void);
	~AppAlgoEnergyTextSpace(void);

	double E_Word_Space(QRWordArt::QRStringLine& spline);
	double E_Letter_Space(QRWordArt::QRStringLine& spline);
private:
	double Gaussion(double x,double a);
	double AVG(std::vector<double>& set);
	double STD(std::vector<double>& set);
};