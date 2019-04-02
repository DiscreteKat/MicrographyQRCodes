#include "stdafx.h"
#include "HSSGLFrameBufferObject.h"

#include <windows.h>
#include <gl/glew.h>
#include <gl/GL.h>
#include <gl/GLU.h>

HSSGLFrameBufferObject::HSSGLFrameBufferObject(void):
m_Width(0),m_Height(0),m_fbo(0), m_Color_Tex(0)
{
}


HSSGLFrameBufferObject::~HSSGLFrameBufferObject( void )
{

}

void HSSGLFrameBufferObject::Initialize( int w,int h )
{
	m_Width	 = w;
	m_Height = h;

	glGenTextures(1, &m_Color_Tex);
	glBindTexture(GL_TEXTURE_2D, m_Color_Tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR, GL_UNSIGNED_BYTE, NULL);

	glGenFramebuffersEXT(1, &m_fbo);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);
	//Attach 2D texture to this FBO
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, m_Color_Tex, 0);
}

int HSSGLFrameBufferObject::Draw( cv::Mat* dst )
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, m_fbo);

	InitRender();
	Render();

	if (dst!=NULL)
	{
		*dst = cv::Mat(m_Width, m_Height, CV_8UC3);
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glReadPixels(0, 0, m_Width, m_Height, GL_BGR, GL_UNSIGNED_BYTE, dst->data);
	}

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	return m_Color_Tex;
}

void HSSGLFrameBufferObject::Release()
{
	if (m_Color_Tex != 0)
	{
		glDeleteTextures(1,&m_Color_Tex);
	}

	if (m_fbo != 0)
	{
		glDeleteFramebuffersEXT(1,&m_fbo);
	}
}

//Test
// void AppFrameBufferObject::Render()
// {
// 	glClearColor(0.5, 0.5, 0.5, 0.0);
// 	glClear(GL_COLOR_BUFFER_BIT);
// 	//-------------------------
// 	glViewport(0, 0, 256, 256);
// 	glMatrixMode(GL_PROJECTION);
// 	glLoadIdentity();
// 	glOrtho(0.0, 256.0, 0.0, 256.0, -1.0, 1.0); 
// 	glMatrixMode(GL_MODELVIEW);
// 	glLoadIdentity();
// 	//-------------------------
// 
// 	
// 	glColor3d(1.0,0.0,0.0);
// 	glPointSize(10);
// 	glBegin(GL_POINTS);
// 	glVertex2d(100,100);
// 	glEnd();
// }
