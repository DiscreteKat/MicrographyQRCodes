#include "StdAfx.h"
#include "QRSplineFBO.h"


QRWordArt::QRSplineFBO::QRSplineFBO(void):HSSGLFrameBufferObject()
{
	SetBGColor(1.0,1.0,1.0);
	SetSPColor(0.0,0.0,0.0);
}

QRWordArt::QRSplineFBO::QRSplineFBO( int w,int h ):HSSGLFrameBufferObject()
{
	Initialize(w,h);
}

QRWordArt::QRSplineFBO::~QRSplineFBO(void)
{
	Release();
}

void QRWordArt::QRSplineFBO::InitRender()
{
	glClearColor(m_BGColor[0],m_BGColor[1],m_BGColor[2], 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//-------------------------
	glViewport(0, 0, m_Width, m_Height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, m_Width, 0.0, m_Height, -1.0, 1.0); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//-------------------------
	glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_POLYGON_SMOOTH);
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void QRWordArt::QRSplineFBO::Render()
{
	glColor4d(m_SPColor[0],m_SPColor[1],m_SPColor[2],1.0);
	for (int i=0;i<m_Splines.size();i++)
	{
		m_Splines[i]->DrawStroke(m_From[i],m_End[i]);
	}
}

void QRWordArt::QRSplineFBO::Push( QRStringLine* spline )
{
	m_Splines.push_back(spline);
	m_From.push_back(HSSSpline::Sample(0,0));
	m_End.push_back(HSSSpline::Sample(spline->n_segs()-1,1));
}

void QRWordArt::QRSplineFBO::Push( QRStringLine* spline,HSSSpline::Sample& from,HSSSpline::Sample& end )
{
	m_Splines.push_back(spline);
	m_From.push_back(from);
	m_End.push_back(end);
}

void QRWordArt::QRSplineFBO::Pop()
{
	m_Splines.pop_back();
	m_From.pop_back();
	m_End.pop_back();
}

void QRWordArt::QRSplineFBO::Clear()
{
	m_Splines.clear();
	m_From.clear();
	m_End.clear();
}

void QRWordArt::QRSplineFBO::SetBGColor( double r,double g,double b )
{
	m_BGColor[0] = r;
	m_BGColor[1] = g;
	m_BGColor[2] = b;
}

void QRWordArt::QRSplineFBO::SetSPColor( double r,double g,double b )
{
	m_SPColor[0] = r;
	m_SPColor[1] = g;
	m_SPColor[2] = b;
}
