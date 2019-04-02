#pragma once
#include "HSplinePath.h"
#include "HSSSplineSample.h"
#include <vector>

namespace QRWordArt
{
	namespace QRCharacter
	{
		class QRNode
		{
		private:
			HSSSpline::HSplinePath* m_StringLine;

			int   m_Index;

			bool  m_Main;

			bool m_FixU;
			bool m_FixV;

			float m_Weight;

			HSSSpline::Vector2  m_UV;
		public:
			QRNode();
			QRNode(HSSSpline::HSplinePath* spline);
			QRNode(HSSSpline::PathPoint<2> pt,HSSSpline::HSplinePath* spline);
			~QRNode(void);

			double operator[](unsigned int i){return m_UV[i];}
		public:
			int  Index( ) const {return m_Index;} 
			void Index(int index){m_Index = index;}

			HSSSpline::HSplinePath* StringLine(){return m_StringLine;}
			void AssignStringLine(HSSSpline::HSplinePath* spline){m_StringLine=spline;}

			bool FixU(){return m_FixU;}
			void FixU(bool enable){m_FixU=enable;}

			bool FixV(){return m_FixV;}
			void FixV(bool enable){m_FixV=enable;}

			bool Main(){return m_Main;}
			void Main(bool enable){m_Main=enable;}

			float Weight(){return m_Weight;}
			void   Weight(float w){m_Weight=w;}

			HSSSpline::PathPoint<2> Position() const;
			void Position(double x,double y);

			HSSSpline::PathPoint<2> Position_UV(){return m_UV;};
			void Position_UV(double u,double v);

			void Translate(double dx,double dy);
			void Translate_UV(double du,double dv);

			HSSSpline::Sample ToSample();

			HSSSpline::PathPoint<2> Normalize();
		};
		typedef std::vector<QRNode*> QRNodes;
	}
}