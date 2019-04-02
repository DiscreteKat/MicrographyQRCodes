#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "HSSVec2.h"
namespace QRWordArt
{
	class QRPattern
	{
	public:
		static std::map<std::string,unsigned int> Patterns;
		static void LoadPattern();
		static void LoadPattern(std::string& filename, std::string& key);
		static void GenPsPattern();
	private:
		HSSVec2		m_Center;
		double      m_Height;
		double      m_Width;

		HSSVec2		m_Vectrix[4];

		unsigned int m_TextureIdx;
		double m_Color[4];
	public:
		QRPattern();
		~QRPattern(){};
	public:
		void SetTexture(std::string& key);
		void SetTexture(unsigned int index);
		void SetColor(double r,double g,double b,double a);
		void SetPosion(double x,double y);
		void SetSize(double width,double height);
		void Draw();
		void DrawSoild();
	};
	typedef std::vector<QRPattern> QRPatterns;
}