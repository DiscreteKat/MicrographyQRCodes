#include "StdAfx.h"
#include "QRCharacterIO.h"
#include "JsonApp.h"
#include <map>

namespace QRWordArt
{
	QRCharacter::IO::CharMap QRCharacter::IO::Cache = QRCharacter::IO::CharMap();

	void QRCharacter::IO::Read( const char* file )
	{
		Json::Value root;
		JsonApp::ReadFile(&root,file);

		char c = root["char"].asString().at(0);
		double  width = root["width"].asDouble();
		double bear_x = root["bear_x"].asDouble();
		double advance = root["advance"].asDouble();

		NodeInfo node_info;
		for (unsigned int i=0;i<root["nodes"].size();i++)
		{
			NodeData data;
			data.fix_v  = root["nodes"][i]["fix"].asBool();
			data.main   = root["nodes"][i]["main"].asBool();
			data.weight = (float)root["nodes"][i]["w"].asDouble();
			data.hori   = root["nodes"][i]["hori"].asDouble();
			data.vert   = root["nodes"][i]["vert"].asDouble();
			node_info.push_back(data);
		}

		LineInfo line_info;
		for (unsigned int i=0;i<root["lines"].size();i++)
		{
			LineData data;
			for (unsigned int j=0;j<root["lines"][i]["node index"].size();j++)
			{
				data.n_idx.push_back(root["lines"][i]["node index"][j].asInt());
			}
			data.fix_v = root["lines"][i]["fix"].asBool();
			data.collinear = root["lines"][i]["collinear"].asBool();
			data.w = root["lines"][i]["w"].asDouble();
			data.h1 = root["lines"][i]["h1"].asDouble();
			data.h2 = root["lines"][i]["h2"].asDouble();
			line_info.push_back(data);
		}

		ExtraInfo extra_info;
		for (unsigned int i=0;i<root["extra"].size();i++)
		{
			ExtraData data;
			data.weight = root["extra"][i]["w"].asDouble();
			for (unsigned int j=0;j<root["extra"][i]["node index"].size();j++)
			{
				data.n_idx.push_back(root["extra"][i]["node index"][j].asInt());
			}
			extra_info.push_back(data);
		}

		Cache[c].width		= width;
		Cache[c].bearing_x	= bear_x;
		Cache[c].advance	= advance;
		Cache[c].node_info	= node_info;
		Cache[c].line_info	= line_info;
		Cache[c].extra_info = extra_info;
	}

	void QRCharacter::IO::Write( const char* file,char c,double width,double bearingX, double advance, NodeInfo& node_info,LineInfo& line_info )
	{
		Json::Value root;
		std::string c_str;
		c_str += c;
		root["char"] = c_str;
		root["width"] = width;
		root["bear_x"] = bearingX;
		root["advance"] = advance;

		Json::Value nodes_value;
		nodes_value.resize(node_info.size());
		for (unsigned int i=0;i<node_info.size();i++)
		{
			nodes_value[i]["hori"] = node_info[i].hori;
			nodes_value[i]["vert"] = node_info[i].vert;
			nodes_value[i]["fix"]  = node_info[i].fix_v;
			nodes_value[i]["w"]    = node_info[i].weight;
		}
		root["nodes"] = nodes_value;

		Json::Value lines_value;
		lines_value.resize(line_info.size());
		for (unsigned int i=0;i<line_info.size();i++)
		{
			Json::Value n_idx;
			n_idx.resize(line_info[i].n_idx.size());
			for (int j=0;j<line_info[i].n_idx.size();j++)
			{
				n_idx[j] = line_info[i].n_idx[j];
			}
			lines_value[i]["node index"] = n_idx;
			lines_value[i]["fix"] = line_info[i].fix_v;
			lines_value[i]["collinear"] = line_info[i].collinear;
			lines_value[i]["w"] = line_info[i].w;
			lines_value[i]["h1"] = line_info[i].h1;
			lines_value[i]["h2"] = line_info[i].h2;
		}
		root["lines"] = lines_value;
		JsonApp::WriteFile(root,file,1);
	}

	void QRCharacter::IO::Write( const char* file,char c , HSSSpline::Sample& posn, QRWordArt::QRCharacter::Char& _char )
	{
		Json::Value root;
		std::string c_str;
		c_str += c;
		root["char"]    = c_str;
		root["width"]   = Cache[c].width;
		root["bear_x"]  = Cache[c].bearing_x;
		root["advance"] = Cache[c].advance;

		double u = _char.StringLine()->BeginToSampleLenght(posn);
		double size = _char.StringLine()->get_w(posn);

		Json::Value nodes_value;
		nodes_value.resize(_char.NodeSize());
		for (unsigned int i=0;i<_char.NodeSize();i++)
		{
			nodes_value[i]["hori"] = (_char.Node(i)->Position_UV()[0]-u)/size;
			nodes_value[i]["vert"] = _char.Node(i)->Position_UV()[1];
			nodes_value[i]["fix"]  = _char.Node(i)->FixV();
			nodes_value[i]["w"]    = _char.Node(i)->Weight();
			nodes_value[i]["main"] = false;
		}
		root["nodes"] = nodes_value;

		Json::Value lines_value;
		lines_value.resize(_char.SkeletonSize());
		for (unsigned int i=0;i<_char.SkeletonSize();i++)
		{
			Json::Value n_idx;
			QRCharacter::QRNodes nodes = _char.Skeleton(i)->GetNodes();
			n_idx.resize(nodes.size());
			for (int j=0;j<nodes.size();j++){n_idx[j] = nodes[j]->Index();}
			lines_value[i]["node index"] = n_idx;

			lines_value[i]["fix"] = Cache[c].line_info[i].fix_v;
			lines_value[i]["collinear"] = Cache[c].line_info[i].collinear;
			lines_value[i]["w"]  = _char.Skeleton(i)->Width()/size;
			lines_value[i]["h1"] = _char.Skeleton(i)->Height1()/size;
			lines_value[i]["h2"] = _char.Skeleton(i)->Height2()/size;
		}
		root["lines"] = lines_value;
		JsonApp::WriteFile(root,file,1);
	}

	double QRCharacter::WordSpacing = 0;
	double QRCharacter::LetterSpacing = 0;
	void QRCharacter::IO::Load( const char* file_path )
	{
		Cache.clear();
		double letter_space=0;
		for (char c='A';c<='Z';c++)
		{
			char buff[100];
			sprintf(buff,"%s/%c.qrchar",file_path,c);
			QRCharacter::IO::Read(buff);
			letter_space += QRCharacter::GetAdvance(c) - QRCharacter::GetWidth(c);
		}
		QRCharacter::WordSpacing   = QRCharacter::GetAdvance('I');
 		QRCharacter::LetterSpacing = letter_space/26.0;
	}

	QRCharacter::Char* QRCharacter::Instantiate( char c, HSSSpline::HSplinePath* spline, HSSSpline::Sample& posn )
	{
		IO::CharMap::iterator it_char = IO::Cache.find(c);
		if (it_char != IO::Cache.end())
		{
			double w_size = spline->get_w(posn);
			double posn_u = spline->BeginToSampleLenght(posn);

			QRCharacter::Char* qr_char = new QRCharacter::Char(c);
			qr_char->BindStringLine(spline);

			for (int i=0; i<it_char->second.node_info.size();i++)
			{
				double u = (posn_u +  w_size*it_char->second.node_info[i].hori) /spline->Lenght();//Normalize
				double v = it_char->second.node_info[i].vert;
				
				QRNode* node = new QRNode(spline);
				node->Position_UV(u,v);
				node->Main(it_char->second.node_info[i].main);
				node->FixV(it_char->second.node_info[i].fix_v);
				node->Weight(it_char->second.node_info[i].weight);
				qr_char->AddNode(node);
			}

			for (int i=0; i<it_char->second.line_info.size();i++)
			{
				bool fix_v		= it_char->second.line_info[i].fix_v;
				bool collinear	= it_char->second.line_info[i].collinear;
				double w		= it_char->second.line_info[i].w *w_size;
				double h1		= it_char->second.line_info[i].h1*w_size;
				double h2		= it_char->second.line_info[i].h2*w_size;
				qr_char->CreateSkeleton(it_char->second.line_info[i].n_idx,posn,fix_v,collinear,w,h1,h2);
			}

			//structure constrain
			for (int i=0; i<it_char->second.extra_info.size();i++){qr_char->AddSpacingConstrain(it_char->second.extra_info[i].weight,it_char->second.extra_info[i].n_idx);}

			qr_char->InitData();
			qr_char->Update();

			return qr_char;
		}
		return NULL;
	}

	double QRCharacter::GetWidth( char c )
	{
		IO::CharMap::iterator it_char = IO::Cache.find(c);
		if (it_char != IO::Cache.end()){return it_char->second.width;}
		return -1;
	}

	double QRCharacter::GetAdvance( char c )
	{
		IO::CharMap::iterator it_char = IO::Cache.find(c);
		if (it_char != IO::Cache.end()){return it_char->second.advance;}
		return -1;
	}

	double QRCharacter::GetBearingX( char c )
	{
		IO::CharMap::iterator it_char = IO::Cache.find(c);
		if (it_char != IO::Cache.end()){return it_char->second.bearing_x;}
		return -1;
	}

	double QRCharacter::GetBackSpace( char c )
	{
		IO::CharMap::iterator it_char = IO::Cache.find(c);
		if (it_char != IO::Cache.end()){return GetAdvance(c)-GetBearingX(c)-GetWidth(c);}
		return -1;
	}

}