#pragma once
#include "QRCharacter.h"
#include "HSSGLFrameBufferObject.h"

namespace QRWordArt
{
	namespace QRCharacter
	{ 
		class CharFBO : public HSSGLFrameBufferObject
		{
		public:
			enum DrawMode{
				SOILD,
				SOILD_COLOR,
				BOUNDINGBOX
			};
		private:
			VecChar m_Pool;
			double m_BackgroundColor;

			DrawMode m_Mode;
		public:
			CharFBO(void);
			CharFBO(int w,int h);
			~CharFBO(void);

			void Push(QRCharacter::Char* c);
			void Pop();
			void Clear();

			void SetBackground(int color);
			void Enable(DrawMode mode);
		protected:
			void InitRender();
			void Render();

		};
	}
}