#pragma once
#include <HKMedia.h>
#include "AppData.h"

namespace HKMedia
{	
	class WordArtRender : public HKCImage
	{
	protected:
		HKCStringDatas* m_String_Lines;
	public:
		WordArtRender(cv::Mat& img, HKCStringDatas* string_lines);	

		void Render(const HKCRndrParam&);
	};
}


