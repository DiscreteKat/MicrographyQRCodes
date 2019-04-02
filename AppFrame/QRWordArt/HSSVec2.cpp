#include "stdafx.h"
#include "HSSVec2.h"

#include <cmath>
#include <iostream>

HSSVec2::HSSVec2(void)
{
	vec[0] = 0;
	vec[1] = 0;
}

HSSVec2::HSSVec2( double in_x,double in_y )
{
	vec[0] = in_x;
	vec[1] = in_y;
}


HSSVec2::~HSSVec2(void)
{
}

double HSSVec2::Normalize()
{
	double len = Length();
	if (len>0.0000001)
	{
		vec[0]/=len;
		vec[1]/=len;
	}else{
		vec[0]=0;
		vec[1]=0;
		len=0;
	}
	return len;
}

double HSSVec2::InterProduct(const HSSVec2& input )
{
	return vec[0]*input[0] + vec[1]*input[1];
}

double HSSVec2::Length()
{
	return sqrt(vec[0]*vec[0]+vec[1]*vec[1]);
}

double HSSVec2::Distance(const HSSVec2& input )
{
	return sqrt((vec[0]-input[0])*(vec[0]-input[0])+(vec[1]-input[1])*(vec[1]-input[1]));
}

void HSSVec2::Reverse()
{
	vec[0] *= -1;
	vec[1] *= -1;
}

double HSSVec2::CrossProduct(const HSSVec2& input )
{
	return vec[0]*input[1] - vec[1]*input[0];
}

double HSSVec2::RelativeDirection( const HSSVec2& input )
{
	HSSVec2 vec = input-(*this);
	vec.Normalize();

	double sita;
	sita = acos(vec[0]);
	if (vec[1]<0)
	{
		sita *= -1;
	}
	return sita;
}