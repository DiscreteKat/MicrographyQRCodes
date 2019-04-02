#include "StdAfx.h"
#include "QRPatternFBO.h"


QRWordArt::QRPatternFBO::QRPatternFBO(void):HSSGLFrameBufferObject(),
m_BackgroundColor(1.0),m_Mode(SOILD)
{
}

QRWordArt::QRPatternFBO::QRPatternFBO( int w,int h ):HSSGLFrameBufferObject(),
m_BackgroundColor(1.0),m_Mode(SOILD)
{
	Initialize(w,h);
}

QRWordArt::QRPatternFBO::~QRPatternFBO(void)
{
	Release();
}

void QRWordArt::QRPatternFBO::InitRender()
{
	glClearColor(m_BackgroundColor,m_BackgroundColor,m_BackgroundColor, 0.0);
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

void QRWordArt::QRPatternFBO::Render()
{
	glEnable( GL_BLEND );
	glEnable(GL_TEXTURE_2D);

	glColor4d(0.0,0.0,0.0,1.0);
	for (unsigned int i=0;i<m_Pool.size();++i)
	{
		switch(m_Mode)
		{
		case SOILD_COLOR:
			m_Pool[i].Draw();
			break;
		default:
			m_Pool[i].DrawSoild();
			break;
		}
	}

	glDisable( GL_BLEND );
	glDisable(GL_TEXTURE_2D);
}

void QRWordArt::QRPatternFBO::Push( QRPattern& c )
{
	m_Pool.push_back(c);
}

void QRWordArt::QRPatternFBO::Pop()
{
	m_Pool.pop_back();
}

void QRWordArt::QRPatternFBO::Clear()
{
	m_Pool.clear();
}

void QRWordArt::QRPatternFBO::Enable( DrawMode mode )
{
	m_Mode = mode;
}

void QRWordArt::QRPatternFBO::SetBackground( int color )
{
	m_BackgroundColor = color;
}