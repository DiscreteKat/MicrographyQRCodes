#include "StdAfx.h"
#include "QRPattern.h"

QRWordArt::QRPattern::QRPattern():m_Center(HSSVec2(100,100)),m_Height(10),m_Width(10),m_TextureIdx(0)
{
	SetSize(m_Width,m_Height);
	SetColor(0.0,0.0,0.0,0.0);
}

std::map<std::string,unsigned int> QRWordArt::QRPattern::Patterns;

void QRWordArt::QRPattern::LoadPattern()
{
	QRWordArt::QRPattern::LoadPattern(std::string("Pattern/Pattern_Module.bmp"),std::string("Module"));
	QRWordArt::QRPattern::LoadPattern(std::string("Pattern/Pattern_Square.bmp"),std::string("Square"));
	QRWordArt::QRPattern::LoadPattern(std::string("Pattern/Pattern_Star.bmp"),std::string("Star"));
	QRWordArt::QRPattern::LoadPattern(std::string("Pattern/Pattern_Noise2.bmp"),std::string("Ink"));

	GenPsPattern();
}

void QRWordArt::QRPattern::LoadPattern( std::string& filename, std::string& key )
{
	cv::Mat alpha = cv::imread(filename,CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat img;
	img.create(alpha.rows,alpha.cols,CV_8UC4);
	for (int i=0;i<alpha.rows*alpha.cols;i++){
		img.data[i*4+0] = 255;
		img.data[i*4+1] = 255;
		img.data[i*4+2] = 255;
		img.data[i*4+3] = alpha.data[i];
	}

	unsigned int texture_id;
	glGenTextures( 1, &texture_id);
	glBindTexture( GL_TEXTURE_2D,texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	gluBuild2DMipmaps(GL_TEXTURE_2D,4,img.cols,img.rows,GL_BGRA_EXT,GL_UNSIGNED_BYTE,img.data);

	Patterns[key] = texture_id;
}

void QRWordArt::QRPattern::GenPsPattern()
{
	int size   = 81;
	cv::Mat alpha =cv::Mat(size, size, CV_8UC4,cv::Scalar(0,0,0,0));

	double sigma = (double)size*0.15;
	//double sigma = (double)size*0.2;
	for (int i=0; i<size;i++){
		for (int j=0; j<size;j++){
			int x = abs(j-(int)(size*0.5));
			int y = abs(i-(int)(size*0.5));
			double a = exp(-(double)(x*x+y*y)/(2*sigma*sigma));

 			int idx = i*size + j;
 			alpha.data[idx*4+0] = 255;
 			alpha.data[idx*4+1] = 255;
 			alpha.data[idx*4+2] = 255;
 			alpha.data[idx*4+3] = (int)(255.0*a);		
		}
	}

	//cv::imshow("alpha",alpha);

	unsigned int texture_id;
	glGenTextures( 1, &texture_id);
	glBindTexture( GL_TEXTURE_2D,texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST) ;
 	gluBuild2DMipmaps(GL_TEXTURE_2D,4,alpha.cols,alpha.rows,GL_BGRA_EXT,GL_UNSIGNED_BYTE,alpha.data); 

	Patterns["PsPattern"] = texture_id;
}

void QRWordArt::QRPattern::SetTexture( unsigned int index ){m_TextureIdx = index;}

void QRWordArt::QRPattern::SetTexture( std::string& key ){m_TextureIdx = Patterns[key];}

void QRWordArt::QRPattern::SetColor( double r,double g,double b,double a )
{
	m_Color[0]=r;
	m_Color[1]=g;
	m_Color[2]=b;
	m_Color[3]=a;
}

void QRWordArt::QRPattern::SetPosion( double x,double y )
{
	HSSVec2 new_center(x,y);
	HSSVec2 vec = new_center-m_Center;
	m_Center = new_center;

	for (int i=0;i<4;i++){m_Vectrix[i] += vec;}
}

void QRWordArt::QRPattern::SetSize( double width,double height )
{
	m_Vectrix[0][0] = m_Center[0]-width *0.5;
	m_Vectrix[0][1] = m_Center[1]-height*0.5;

	m_Vectrix[1][0] = m_Center[0]+width *0.5;
	m_Vectrix[1][1] = m_Center[1]-height*0.5;

	m_Vectrix[2][0] = m_Center[0]+width *0.5;
	m_Vectrix[2][1] = m_Center[1]+height*0.5;

	m_Vectrix[3][0] = m_Center[0]-width *0.5;
	m_Vectrix[3][1] = m_Center[1]+height*0.5;
}

void QRWordArt::QRPattern::Draw()
{
	glBindTexture( GL_TEXTURE_2D,m_TextureIdx);
	glColor4d(m_Color[0],m_Color[1],m_Color[2],m_Color[3]);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);glVertex2d(m_Vectrix[0][0],m_Vectrix[0][1]);
	glTexCoord2d(1,0);glVertex2d(m_Vectrix[1][0],m_Vectrix[1][1]);
	glTexCoord2d(1,1);glVertex2d(m_Vectrix[2][0],m_Vectrix[2][1]);
	glTexCoord2d(0,1);glVertex2d(m_Vectrix[3][0],m_Vectrix[3][1]);
	glEnd();
}

void QRWordArt::QRPattern::DrawSoild()
{
	glBindTexture( GL_TEXTURE_2D,m_TextureIdx);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);glVertex2d(m_Vectrix[0][0],m_Vectrix[0][1]);
	glTexCoord2d(1,0);glVertex2d(m_Vectrix[1][0],m_Vectrix[1][1]);
	glTexCoord2d(1,1);glVertex2d(m_Vectrix[2][0],m_Vectrix[2][1]);
	glTexCoord2d(0,1);glVertex2d(m_Vectrix[3][0],m_Vectrix[3][1]);
	glEnd();
}
