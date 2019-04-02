#include "StdAfx.h"
#include "QRWordArtIO.h"

void QRWordArt::IO::SaveWordArt(QRStringLines& data, const char* filename )
{
	std::ofstream file;
	file.open (filename);
	file<<data.size()<<"\n";
	for (int i=0;i<data.size();i++)
	{
		HSSSpline::PathPoints<5> piecewise_points=data[i]->GetPiecewisePoints();
		file<<piecewise_points.size()<<"\n";
		for (int j = 0 ; j <piecewise_points.size();j++){file<<piecewise_points[j].ToString()<<"\n";}
		HSSSpline::PathPoints<5> ctrl_points=data[i]->GetCtrlPoints();
		file<<ctrl_points.size()<<"\n";
		for (int j = 0 ; j <ctrl_points.size();j++){file<<ctrl_points[j].ToString()<<"\n";}

		file<<data[i]->size()<<"\n";
		for (int j = 0 ; j <data[i]->size();j++){file<<(*data[i])[j].ToString()<<"\n";}
	}
	file.close();
	std::cout<<"Save Word Art File"<<std::endl;
}

QRWordArt::QRStringLines QRWordArt::IO::LoadWordArt( const char* filename )
{
	QRWordArt::QRStringLines splines;
	std::ifstream file ( filename , ifstream::in );
	String^ _file;
	_file = gcnew String(filename);
	System::String^ fileExt = Path::GetExtension(_file);
	if(file.is_open())
	{
		int spline_size = 0;
		file>>spline_size;
		QRStringLine* last_spline = NULL;
		for (int i=0;i < spline_size;i++)
		{
			if (System::String::Compare(fileExt, ".wc") == 0)
				printf("\r process (w/ color) ...%d/%d        ",i,spline_size);
			else
				printf("\r process ...%d/%d        ",i,spline_size);
			QRStringLine* spline = new QRStringLine();
			HSSSpline::PathPoints<5> piecewisw_points;
			HSSSpline::PathPoints<5> ctrl_points;
			std::string line;

			int pt_size = 0;
			file>>pt_size;
			getline(file,line);
			for (int p=0;p<pt_size;p++)
			{
				getline(file,line);
				HSSSpline::PathPoint<5> info;
				sscanf(line.c_str(),"%lf %lf %lf %lf %lf",&info[0],&info[1],&info[2],&info[3],&info[4]);
				piecewisw_points().push_back(info);
			}
			spline->AssignPoints(piecewisw_points);

			int cpt_size = 0;
			file>>cpt_size;
			getline(file,line);
			for (int cp=0;cp<cpt_size;cp++)
			{
				getline(file,line);
				HSSSpline::PathPoint<5> info;
				sscanf(line.c_str(),"%lf %lf %lf %lf %lf",&info[0],&info[1],&info[2],&info[3],&info[4]);
				ctrl_points().push_back(info);
			}
			spline->AssignCtrlPoints(ctrl_points);
			
			int sample_size = 0;
			file>>sample_size;getline(file,line);
			for (int cp=0;cp<sample_size;cp++)
			{
				getline(file,line);
				
				std::size_t pos = line.find(" ");
				std::string str1 = line.substr(0,pos);
				line = line.substr(pos+1);
				std::string str10,str9,str8,str7,str6,str5;
				if (System::String::Compare(fileExt, ".wc") == 0)
				{
					pos = line.rfind(" ");
					str10 = line.substr(pos+1);
					line = line.substr(0,pos);
					pos = line.rfind(" ");
					str9 = line.substr(pos+1);
					line = line.substr(0,pos);
					pos = line.rfind(" ");
					str8 = line.substr(pos+1);
					line = line.substr(0,pos);
					pos = line.rfind(" ");
					str7 = line.substr(pos+1);
					line = line.substr(0,pos);
					pos = line.rfind(" ");
					str6 = line.substr(pos+1);
					line = line.substr(0,pos);
					pos = line.rfind(" ");
					str5 = line.substr(pos+1);
					line = line.substr(0,pos);
				}
				pos = line.rfind(" ");
				std::string str4 = line.substr(pos+1);
				line = line.substr(0,pos);
				pos = line.rfind(" ");
				std::string str3 = line.substr(pos+1);
				std::string str2 = line.substr(0,pos);

				int header = atoi( str1.c_str() );
				char c = str2[0];
				HSSSpline::Sample sample;
				sample.seg_idx = atoi( str3.c_str() );
				sample._t = atof( str4.c_str() );

				QRWordArt::QRStringLine::QRSample* qr_sample = spline->AttachChar(c,sample);
				if (System::String::Compare(fileExt, ".wc") == 0)
				{
					qr_sample->WordId = atoi(str5.c_str());
					double r = atof( str6.c_str() );
					double g = atof( str7.c_str() );
					double b = atof( str8.c_str() );
					qr_sample->_IsSentenceStart = (bool) atoi( str9.c_str() );
					qr_sample->_IsSentenceEnd = (bool) atoi( str10.c_str() );
					qr_sample->qr_char->SetColor(r,g,b);
				}
				
				qr_sample->w_header = header;
			}
			
			if (last_spline!=NULL)
			{
				spline->LastLine(last_spline);
				last_spline->NextLine(spline);
			}
			last_spline = spline;
			splines.push_back(spline);
		}
		file.close();
	}
	printf("\r Done                   \n");
	return splines;
}