#pragma once
#include "QRStringLine.h"
#include "HSSGLFrameBufferObject.h"

namespace QRWordArt
{ 
	class QRSplineFBO : public HSSGLFrameBufferObject
	{
	private:
		HSSSpline::Samples m_From;
		HSSSpline::Samples m_End;
		QRStringLines m_Splines;

		double m_BGColor[3];
		double m_SPColor[3];
	public:
		QRSplineFBO(void);
		QRSplineFBO(int w,int h);
		~QRSplineFBO(void);

		void Push(QRStringLine* spline);
		void Push(QRStringLine* spline,HSSSpline::Sample& from,HSSSpline::Sample& end);
		void Pop();
		void Clear();

		void SetBGColor(double r,double g,double b);
		void SetSPColor(double r,double g,double b);
	protected:
		void InitRender();
		void Render();
	};
}

