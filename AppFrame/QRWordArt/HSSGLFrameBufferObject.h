#pragma once

#include <opencv2/core/core.hpp>

class HSSGLFrameBufferObject
{
protected:
	unsigned int m_fbo;
	unsigned int m_Color_Tex;

	int m_Width;
	int m_Height;
public:
	HSSGLFrameBufferObject(void);
	~HSSGLFrameBufferObject(void);

	void Initialize(int w,int h);
	int Draw(cv::Mat* dst = 0);
protected:
	virtual void InitRender() = 0;
	virtual void Render() = 0;

	void Release();
};

