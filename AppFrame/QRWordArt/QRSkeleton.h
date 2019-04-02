#pragma once
#include "HSplineCore.h"
#include "QRNode.h"

namespace QRWordArt
{
	namespace QRCharacter
	{
		class QRSkeleton:public HSSSpline::HSplineCore<2>
		{
			private:
				static unsigned int m_StrokeTexture;
			public:
				static void LoadStrokeTexture();
			private:
				QRNodes m_Nodes;

				double m_W;
				double m_H1;
				double m_H2;
			public:
				QRSkeleton(void);
				~QRSkeleton(void);

				void AddNode(QRNode* node){m_Nodes.push_back(node);}
				QRNodes GetNodes(){return m_Nodes;}

				void SetBold(double w,double h1,double h2);
				void SetBold(HSSSpline::Scale3& bold){SetBold(bold[0],bold[1],bold[2]);}

				HSSSpline::Scale3 Bold(){return HSSSpline::Scale3(m_W,m_H1,m_H2);}
				double& Width()  {return m_W;}
				double& Height1(){return m_H1;}
				double& Height2(){return m_H2;}
				void ScaleSize(double s);

				void InterpolateNode(HSSSpline::HSplinePath* spline,HSSSpline::Sample& sample, double perlen, bool fix_v);
				void Update();

				std::vector<HSSSpline::Vector2> GetStoke();

				void Draw();
				void DrawStroke();
				HSSSpline::PathPoint<2> get_normal(int seg,double t);
				HSSSpline::PathPoint<2> get_tangent(int seg,double t);
				double SplineLenght(HSplineCore<2>& spline,int seg);
		};
		typedef std::vector<QRSkeleton*> QRSkeletons;
	}
}