#pragma once
#include <vector>
#include <map>

class HSSVec2
{
public:
	double vec[2];
public:
	HSSVec2(void);
	HSSVec2(double in_x,double in_y);

	~HSSVec2(void);

	const double &operator [] (int i) const
	{ return vec[i]; }
	double &operator [] (int i)
	{ return vec[i]; }

	void	 operator = (const HSSVec2& input){vec[0]=input[0]; vec[1]=input[1];}

	HSSVec2	 operator + (const HSSVec2& input)const{return HSSVec2(vec[0]+input[0],vec[1]+input[1]);} 
	void	 operator +=(const HSSVec2& input){vec[0]+=input[0];vec[1]+=input[1];}

	HSSVec2	 operator - (const HSSVec2& input)const{return HSSVec2(vec[0]-input[0],vec[1]-input[1]);}
	void	 operator -=(const HSSVec2& input){vec[0]-=input[0];vec[1]-=input[1];}

	HSSVec2	 operator *(const double input)const{return HSSVec2(vec[0]*input,vec[1]*input);}
	void	 operator *=(const double input){vec[0]*=input;vec[1]*=input;}

	HSSVec2	 operator /(const double input)const{return HSSVec2(vec[0]/input,vec[1]/input);}
	void	 operator /=(const double input){vec[0]/=input;vec[1]/=input;}

	bool	 operator == (const HSSVec2& input)const{return (vec[0]==input[0]&&vec[1]==input[1]);}
	bool	 operator != (const HSSVec2& input)const{return !(*this==input);}

	double Length();
	double Normalize();
	double InterProduct(const HSSVec2& input);
	double CrossProduct(const HSSVec2& input);
	double Distance(const HSSVec2& input);
	void Reverse();

	double RelativeDirection(const HSSVec2& input);
};
