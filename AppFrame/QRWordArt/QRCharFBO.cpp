#include "StdAfx.h"
#include "QRCharFBO.h"

namespace QRWordArt
{
	QRCharacter::CharFBO::CharFBO(void):HSSGLFrameBufferObject(),
		m_BackgroundColor(1.0),m_Mode(SOILD)
	{
	}

	QRCharacter::CharFBO::CharFBO( int w,int h ):HSSGLFrameBufferObject(),
		m_BackgroundColor(1.0),m_Mode(SOILD)
	{
		Initialize(w,h);
	}

	QRCharacter::CharFBO::~CharFBO(void)
	{
		Release();
	}

	void QRCharacter::CharFBO::InitRender()
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

	void QRCharacter::CharFBO::Render()
	{
		glColor4d(0.0,0.0,0.0,1.0);
		for (unsigned int i=0;i<m_Pool.size();++i)
		{
			switch(m_Mode)
			{
			case SOILD_COLOR:
				m_Pool[i]->Draw(false);
				break;
			case BOUNDINGBOX:
				glColor4d(1.0,1.0,1.0,1.0);
				m_Pool[i]->DrawBoundingBox();
				break;
			default:
				m_Pool[i]->DrawSoild();
				break;
			}
		}
	}

	void QRCharacter::CharFBO::Push( QRCharacter::Char* c )
	{
		m_Pool.push_back(c);
	}

	void QRCharacter::CharFBO::Pop()
	{
		m_Pool.pop_back();
	}

	void QRCharacter::CharFBO::Clear()
	{
		m_Pool.clear();
	}

	void QRCharacter::CharFBO::Enable( DrawMode mode )
	{
		m_Mode = mode;
	}

	void QRCharacter::CharFBO::SetBackground( int color )
	{
		m_BackgroundColor = color;
	}
}