#pragma once
#include <map>
#include "QRCharacter.h"

namespace QRWordArt
{
	namespace QRCharacter
	{
		namespace IO
		{
			struct NodeData{
				bool main;
				bool fix_v;
				double hori,vert;
				float weight;
			};
			typedef std::vector<NodeData> NodeInfo;

			struct LineData{
				bool fix_v;
				bool collinear;
				double w,h1,h2;
				std::vector<int> n_idx;
			};
			typedef std::vector<LineData> LineInfo;

			struct ExtraData{
				float weight;
				std::vector<int> n_idx;
			};
			typedef std::vector<ExtraData> ExtraInfo;

			struct CharData
			{
				double width;
				double bearing_x;
				double advance;
				NodeInfo node_info;
				LineInfo line_info;
				ExtraInfo extra_info;
			};
			typedef std::map<char,CharData> CharMap;
			extern CharMap Cache;

			void Read(const char* file);
			void Write(const char* file,char c,double width,double bearingX, double advance,NodeInfo& node_info,LineInfo& line_info );
			void Write(const char* file,char c,HSSSpline::Sample& posn,QRWordArt::QRCharacter::Char& _char);
			void Load(const char* file_path);
		}

		extern double WordSpacing;
		extern double LetterSpacing;

		double GetWidth(char c);
		double GetAdvance(char c);
		double GetBearingX(char c);
		double GetBackSpace(char c);
		Char* Instantiate(char c,HSSSpline::HSplinePath* spline,HSSSpline::Sample& posn);
	};
}