#pragma once
#include "QRCharacter.h"
#include "HSplinePath.h"

#include <vector>
namespace QRWordArt
{
	class QRStringLine:public HSSSpline::HSplinePath
	{
	public:
		struct QRSample{
			int w_header;//Word Header (後面Char數量)
			char _char;
			QRCharacter::Char *qr_char;
			HSSSpline::Sample sample;
			int WordId;
			bool _IsSentenceStart;
			bool _IsSentenceEnd;
			QRSample():w_header(0),WordId(-1),_IsSentenceStart(false),_IsSentenceEnd(false),qr_char(NULL){};			
			bool operator > (QRSample& in){return sample>in.sample;}
			bool operator < (QRSample& in){return sample<in.sample;}
			void operator = (QRSample& in)
			{
				w_header = in.w_header;
				qr_char  = in.qr_char;
				_char    = in._char;
				sample   = in.sample;
			}

			std::string ToString() const
			{
				char buff[100];
				double r,g,b;
				qr_char->GetColor(&r,&g,&b);
				sprintf(buff,"%d %c %d %lf %d %lf %lf %lf %d %d",w_header,_char,sample.seg_idx,sample._t,WordId,r,g,b,_IsSentenceStart,_IsSentenceEnd);
				return std::string(buff);
			}
		};
		typedef std::vector<QRSample*> QRSamples;
		typedef std::vector<QRSamples> WordSamples;
	private:
		QRSamples m_QRSample;

		QRStringLine* m_Last;
		QRStringLine* m_Next;

		double	m_Letter_Space;
		double	m_Word_Space;

		double m_StrokeScale;

		bool m_Fix;
		int  m_RegionIdx;
	public:
		QRStringLine(void);
		~QRStringLine();
		
		void Update();//Update Characters

		QRSample& operator[](int idx){return *m_QRSample[idx];}
		int size(){return m_QRSample.size();}
		int ctrl_size(){return m_Ctrl_Points().size();}
		QRSample* GetQRSample(int idx){return m_QRSample[idx];}
		QRSamples& GetQRSamples(){return m_QRSample;}
		double& StrokeScale(){return m_StrokeScale;}
		bool& Fix(){return m_Fix;}
		int& Region(){return m_RegionIdx;}
		double& WordSpace(){return m_Word_Space;}
		double& LetterSpace(){return m_Letter_Space;}

		QRStringLine* Clone();
		void Release();

	public:
		double get_stroke_top(int _seg, double _t){return get_value(3,_seg,_t)*m_StrokeScale;}
		double get_stroke_top(const HSSSpline::Sample& sample){return get_stroke_top(sample.seg_idx,sample._t);}
		double get_stroke_bottom(int _seg, double _t){return get_value(4,_seg,_t)*m_StrokeScale;}
		double get_stroke_bottom(const HSSSpline::Sample& sample){return get_stroke_bottom(sample.seg_idx,sample._t);}

	public:
		QRStringLine* NextLine(){return m_Next;}
		QRStringLine* LastLine(){return m_Last;}
		void NextLine(QRStringLine* next){m_Next=next;}
		void LastLine(QRStringLine* last){m_Last=last;}
		std::vector<QRWordArt::QRStringLine*> GetNeighbors();

		bool TypeSetting(std::string& str, HSSSpline::Samples* output, 
			             HSSSpline::Sample from = HSSSpline::Sample(0,0), /*Default (0,0)*/
						 HSSSpline::Sample to = HSSSpline::Sample(-1,-1)  /*Default (n_seg-1,1)*/); 
		QRSamples AttachWord( std::string& word, std::vector<HSSSpline::Sample>& samples);
		QRSample* AttachChar( char c,HSSSpline::Sample& to_sample);

		bool R_TypeSetting(std::string& str, HSSSpline::Samples* output,
						   HSSSpline::Sample from = HSSSpline::Sample(-1,-1),  /*Default (n_seg-1,1)*/
						   HSSSpline::Sample to = HSSSpline::Sample(0,0)	   /*Default (0,0)*/);
		QRSamples R_AttachWord( std::string& word, std::vector<HSSSpline::Sample>& samples);
		QRSample* R_AttachChar( char c,HSSSpline::Sample& to_sample);

		int CharIDtoWordID(int id);
		WordSamples GetWordSamples();
		std::vector<std::string> GetWords();
		std::string GetString();

		void SortWords();
		void CleanNullSamples();

		void Duplicate(HSSSpline::Sample& from, HSSSpline::Sample& to, QRStringLine* output);
		void DuplicateWithChar(QRStringLine* dst,HSSSpline::Sample from = HSSSpline::Sample(0,0),HSSSpline::Sample to = HSSSpline::Sample(-1,-1));

	//編輯
	public:
		double SelectChar( double x,double y,int *select );
		double SelectWord( double x,double y,int *select );
		void EditCharSample(int s_idx,HSSSpline::Sample& sample);
		void EditSamplePoint(int s_idx,double x,double y);
		void EditSamplePoint(HSSSpline::Sample& sample,HSSSpline::PathPoint<2>& point);

		void MoveQRSample(QRSample* qr_sample, HSSSpline::Sample to_sample);

		//override
		void ScaleSpline(double scale);
		//編輯Ctrl Point位置
		void EditCtrlPoint(int c_id,HSSSpline::PathPoint<2>& point);
		//編輯Ctrl Point位置
		void TranslateCtrlPoint(int c_id,HSSSpline::PathPoint<2>& point);
		//編輯Ctrl Point位置
		void TranslateAllCtrlPoint(HSSSpline::PathPoint<2>& point);
		//編輯Ctrl Point大小
		void EditCtrlPointSize(int c_id,HSSSpline::PathPoint<3>& size);
		//編輯所有Ctrl Point大小
		void EditAllCtrlPointSize(HSSSpline::PathPoint<3>& size);
		//編輯Ctrl Point大小，並內插其他點
		void SoftEditCtrlPointSize(int c_id,HSSSpline::PathPoint<3>& size);
		//編輯Sample Point大小
		void EditSamplePointSize(const HSSSpline::Sample& sample,HSSSpline::PathPoint<3>& size);
		//編輯所有Ctrl Point大小
		void Scale(double scale);
		//編輯所有point 大小
		void EditAllPointSize( bool plus );
		void EditAllPointPosition( int flag, double amount=0.1 );
		void EditAllPointPosition( HSSSpline::Vector2& vect );

	//Draw
	public:
		void DrawCharPoint();
		void DrawWordArt(bool debug);
		void DrawStroke();
		void DrawStroke(HSSSpline::Sample& from,HSSSpline::Sample& to);

	//長度計算
	public:
		HSSSpline::Sample Cursor();
		double Offset(char c,HSSSpline::Sample& sample);
		double R_Offset(char c,HSSSpline::Sample& sample);

		double AvgW();
		double Remain();
		double Remainfront();
	};
	typedef std::vector<QRStringLine*> QRStringLines;
}