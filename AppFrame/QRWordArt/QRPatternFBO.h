#pragma once
#include "QRPattern.h"
#include "HSSGLFrameBufferObject.h"

namespace QRWordArt
{ 
	class QRPatternFBO : public HSSGLFrameBufferObject
	{
	public:
		enum DrawMode{
			SOILD,
			SOILD_COLOR
		};
	private:
		QRPatterns m_Pool;
		double m_BackgroundColor;

		DrawMode m_Mode;
	public:
		QRPatternFBO(void);
		QRPatternFBO(int w,int h);
		~QRPatternFBO(void);

		void Push(QRPattern& c);
		void Pop();
		void Clear();

		void SetBackground(int color);
		void Enable(DrawMode mode);
	protected:
		void InitRender();
		void Render();

	};
}

