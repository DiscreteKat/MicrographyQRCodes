#include "StdAfx.h"
#include "WordArtRender.h"

HKMedia::WordArtRender::WordArtRender( cv::Mat& img, HKCStringDatas* string_lines ): 
HKCImage(img),
m_String_Lines(string_lines)
{

}

void HKMedia::WordArtRender::Render( const HKCRndrParam& param)
{
	glEnable( GL_BLEND );
	glEnable(GL_TEXTURE_2D);
	//for(int s_id=0;s_id<m_String_Lines->size();s_id++)
	//{
	//	
	//
	//	for(int w_id=0;w_id<(*m_String_Lines)[s_id].size();w_id++)
	//	{
	//
	//		for(int c_id=0;c_id<(*m_String_Lines)[s_id][w_id]->Strings.size();c_id++)
	//		{
	//			QRDeformableChar::QRCharMesh* mesh = (*m_String_Lines)[s_id][w_id]->Strings[c_id]->m_CharMesh;

				glColor4f(1.0f,0.0f,0.0f,1.0f);
				glPointSize(10);
				glBegin(GL_POINTS);
				glVertex2d(10,10);
				glEnd();

	//			mesh->OnDrawCenter();
	//		}
	//	}
	//}
	glDisable(GL_TEXTURE_2D);
	glDisable( GL_BLEND );
}
