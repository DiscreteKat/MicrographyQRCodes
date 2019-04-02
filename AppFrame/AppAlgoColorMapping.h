#pragma once
class AppAlgoColorMapping
{
public:
	static void Jet(double value,char *r,char *g,char *b);
	static void Jet(double value,double *r,double *g,double *b);
	static void Hot2Cold(double value,char *r,char *g,char *b);

	static void DrawJet();
	static void DrawHot2Cold();
};