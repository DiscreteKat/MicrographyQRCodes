#include "StdAfx.h"
#include "QRNode.h"

namespace QRWordArt
{
	namespace QRCharacter
	{
		QRNode::QRNode():m_FixV(false),m_FixU(false),m_Index(-1),m_Weight(1.0),m_UV(HSSSpline::Vector2(0,0)),m_StringLine(NULL),m_Main(false)
		{

		}

		QRNode::QRNode( HSSSpline::HSplinePath* spline ):m_StringLine(spline),m_FixV(false),m_FixU(false),m_Index(-1),m_Weight(1.0),m_UV(HSSSpline::Vector2(0,0)),m_Main(false)
		{

		}

		QRNode::QRNode( HSSSpline::PathPoint<2> pt,HSSSpline::HSplinePath* spline ):m_StringLine(spline),m_FixV(false),m_FixU(false),m_Index(-1),m_Weight(1.0),m_Main(false)
		{
			spline->World2Local(pt[0],pt[1],&m_UV[0],&m_UV[1]);
		}

		QRNode::~QRNode(void)
		{
			m_StringLine = NULL;
		}

		void QRNode::Position( double x,double y )
		{
			double u,v;
			m_StringLine->World2Local(x,y,&u,&v);
			Position_UV(u,v);
		}

		void QRNode::Position_UV( double u,double v )
		{
			if (!m_FixU)m_UV[0]=u;
			if (!m_FixV)m_UV[1]=v;
		}

		HSSSpline::PathPoint<2> QRNode::Position() const
		{
			double x,y;
			m_StringLine->Local2World(m_UV.val[0],m_UV.val[1],&x,&y);
			return HSSSpline::PathPoint<2>(x,y);
		}

		void QRNode::Translate( double dx,double dy )
		{
			HSSSpline::PathPoint<2> posn = Position();
			Position(posn[0]+dx,posn[1]+dy);
		}

		void QRNode::Translate_UV( double du,double dv )
		{
			Position_UV(m_UV[0]+du,m_UV[1]+dv);
		}

		HSSSpline::Sample QRNode::ToSample()
		{
			HSSSpline::Sample sample(0,0);
			m_StringLine->ShiftSample(sample,m_UV[0],&sample);
			return sample;
		}
	}
}