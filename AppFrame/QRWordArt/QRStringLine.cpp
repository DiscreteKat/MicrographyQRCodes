#include "StdAfx.h"
#include "QRStringLine.h"
#include "QRCharacterIO.h"

QRWordArt::QRStringLine::QRStringLine( void ):
m_Last(NULL),m_Next(NULL),m_Letter_Space(0),m_Word_Space(0),m_Fix(false),m_StrokeScale(1.2)
{
}

QRWordArt::QRStringLine::~QRStringLine()
{
	Release();
	m_Last=NULL;
	m_Next=NULL;
}

QRWordArt::QRStringLine::QRSample* QRWordArt::QRStringLine::AttachChar( char c,HSSSpline::Sample& to_sample )
{
	QRSample* char_sample = new QRSample();
	char_sample->qr_char  = QRCharacter::Instantiate(c,(HSplinePath*)this,to_sample);
	char_sample->_char  = c;
	char_sample->sample = to_sample;
	m_QRSample.push_back(char_sample);
	return char_sample;
}

QRWordArt::QRStringLine::QRSamples QRWordArt::QRStringLine::AttachWord( std::string& word, std::vector<HSSSpline::Sample>& samples )
{
	int num = 0;
	bool is_head = true;
	QRWordArt::QRStringLine::QRSample* head = NULL;
	std::vector<QRWordArt::QRStringLine::QRSample*> c_samples;
	for (int i=0;i<samples.size() && i<word.size() ;i++)
	{
		if(word[i]==' ')
		{
			if(head!=NULL){head->w_header = num;}
			is_head = true;
		}else{
			QRWordArt::QRStringLine::QRSample* c_sample = AttachChar(word[i],samples[i]);
			if (is_head)
			{
				num  = 0;
				head = c_sample;
				is_head = false;
			}
			c_samples.push_back(c_sample);
			num++;
		}
	}
	if (head!=NULL){head->w_header = num;}
	return c_samples;
}

QRWordArt::QRStringLine::QRSample* QRWordArt::QRStringLine::R_AttachChar( char c,HSSSpline::Sample& to_sample )
{
	QRSample* char_sample = new QRSample();
	char_sample->qr_char   = QRCharacter::Instantiate(c,(HSplinePath*)this,to_sample);
	char_sample->_char = c;
	char_sample->sample = to_sample;
	m_QRSample.insert(m_QRSample.begin(),char_sample);
	return char_sample;
}

QRWordArt::QRStringLine::QRSamples QRWordArt::QRStringLine::R_AttachWord( std::string& word, std::vector<HSSSpline::Sample>& samples )
{
	std::vector<QRWordArt::QRStringLine::QRSample*> c_samples;
	int num = 0;
	QRWordArt::QRStringLine::QRSample* head = NULL;
	for (int i=0; i<samples.size() && i<word.size() ;i++)
	{
		if (word[word.length()-1-i]==' ')
		{
			if (head!=NULL){head->w_header = num;}
			num = 0;
		}else{
			QRWordArt::QRStringLine::QRSample* c_sample = R_AttachChar(word[word.length()-1-i],samples[samples.size()-1-i]);
			head = c_sample;
			c_samples.push_back(c_sample);
			num++;
		}
	}
	if (head!=NULL){head->w_header = num;}

	return c_samples;
}

void QRWordArt::QRStringLine::Update()
{
	if (m_QRSample.empty())return;
	for (int i=0;i<m_QRSample.size();i++)
	{
		if (m_QRSample[i]->qr_char == NULL){continue;}
		m_QRSample[i]->qr_char->Update();
	}
}

void QRWordArt::QRStringLine::EditSamplePoint( int s_idx,double x,double y)
{
	if (s_idx<0 || s_idx>m_QRSample.size())return;
	EditSamplePoint(m_QRSample[s_idx]->sample,HSSSpline::PathPoint<2>(x,y));
}

void QRWordArt::QRStringLine::EditSamplePoint( HSSSpline::Sample& sample,HSSSpline::PathPoint<2>& point )
{
	HSSSpline::HSplinePath::EditSamplePoint(sample,point);
	Update();
}

double  QRWordArt::QRStringLine::SelectChar( double x,double y,int *select )
{
	*select = -1;
	double min_dis = 100;
	for (int i=0;i<m_QRSample.size();i++)
	{
		if (m_QRSample[i]->qr_char==NULL){continue;}
		HSSSpline::PathPoint<5> p0 = get_point(m_QRSample[i]->sample);
		double dis = (p0[0] - x)*(p0[0] - x) + (p0[1] - y)*(p0[1] - y);
		if (min_dis > dis)
		{
			min_dis = dis;
			*select = i;
		}		
	}
	return min_dis;
}

double QRWordArt::QRStringLine::SelectWord( double x,double y,int *select )
{
	*select = -1;
	double min_dis = 100;
	QRWordArt::QRStringLine::WordSamples w_samples =GetWordSamples();
	for (unsigned int i=0;i<w_samples.size();i++)
	{
		for (unsigned int k=0;k<w_samples[i].size();k++)
		{
			HSSSpline::PathPoint<2> p0 = get_position(w_samples[i][k]->sample);
			double dis = (p0[0] - x)*(p0[0] - x) + (p0[1] - y)*(p0[1] - y);
			if (min_dis > dis)
			{
				min_dis = dis;
				*select = i;
			}
		}
	}
	return min_dis;
}

bool QRWordArt::QRStringLine::TypeSetting( std::string& str, HSSSpline::Samples* output, HSSSpline::Sample from ,HSSSpline::Sample to)
{
	if (to.seg_idx==-1 && to._t==-1){to.seg_idx=n_segs()-1;to._t=1;}

	bool flag=true;
	output->clear();
	for (int i=0;i<str.length()&&flag;i++)
	{
		double size     = get_w(from);
		double width    = size*QRWordArt::QRCharacter::GetWidth(str[i]);
		double bearingX = size*QRWordArt::QRCharacter::GetBearingX(str[i]);
		double advance  = size*QRWordArt::QRCharacter::GetAdvance(str[i]);

		if (str[i]!=' ' && width>0)
		{
			HSSSpline::Sample check;
			flag = ShiftSample(from,bearingX+width,&check);
			if ( check > to ){flag = false;}
		
			if (flag)
			{
				HSSSpline::Sample center;
				ShiftSample(from,bearingX+0.5*width,&center);
				output->push_back(center);

				if (i!=str.length()-1)
				{
					HSSSpline::Sample next;
					double offside = advance;
					if (i+1<str.length() && str[i+1]!=' '){offside += m_Letter_Space*size;}
					flag = ShiftSample(from,offside,&next);
					from = next;
				}
			}
		}else{
			if (str[i+1]==' ')//End
			{
				HSSSpline::Sample center;
				ShiftSample(from,(m_Word_Space+QRCharacter::WordSpacing)*size*2,&center);
				output->push_back(center);

				HSSSpline::Sample next;
				flag = ShiftSample(from,(m_Word_Space+QRCharacter::WordSpacing)*4*size,&next);
				from = next;
				i+=3;
			}
			else//space
			{
				HSSSpline::Sample center;
				ShiftSample(from,(m_Word_Space+QRCharacter::WordSpacing)*size*0.5,&center);
				output->push_back(center);

				HSSSpline::Sample next;
				flag = ShiftSample(from,(m_Word_Space+QRCharacter::WordSpacing)*size,&next);
				from = next;
			}
			
		}
	}
	return flag;
}

bool QRWordArt::QRStringLine::R_TypeSetting( std::string& str, HSSSpline::Samples* output, HSSSpline::Sample from, HSSSpline::Sample to)
{
	if (from.seg_idx==-1 && from._t==-1){from.seg_idx=n_segs()-1;from._t=1;}
	bool flag=true;
	output->clear();
	for (int i=str.length()-1;i>=0 && flag;i--)
	{
		if (!flag)break;
		double size = get_w(from);
		double width    = size*QRCharacter::GetWidth(str[i]);
		double bearingX = size*QRCharacter::GetBearingX(str[i]);
		double advance  = size*QRCharacter::GetAdvance(str[i]);
		if (str[i]!=' ' && width>0)
		{
			HSSSpline::Sample check;
			flag = ShiftSample(from,bearingX-advance,&check);
			
			if ( check < to ){flag = false;}

			if (flag)
			{
				HSSSpline::Sample center;
				ShiftSample(from,bearingX+0.5*width-advance,&center);
				output->push_back(center);

				if (i!=0)
				{
					HSSSpline::Sample next;
					double offside = advance;
					if (i-1>=0 && str[i-1]!=' '){offside += m_Letter_Space*size;}
					flag = ShiftSample(from,-1*offside,&next);
					from = next;
				}
			}
		}else{
			HSSSpline::Sample center;
			ShiftSample(from,-1*(m_Word_Space+QRCharacter::WordSpacing)*size*0.5,&center);
			output->push_back(center);

			HSSSpline::Sample next;
			flag = ShiftSample(from,-1*(m_Word_Space+QRCharacter::WordSpacing)*size,&next);
			from = next;
		}
	}
	std::reverse(output->begin(),output->end());
	return flag;
}

std::vector<QRWordArt::QRStringLine*> QRWordArt::QRStringLine::GetNeighbors()
{
	std::vector<QRWordArt::QRStringLine*> neighbors;
	if (m_Next!=NULL)neighbors.push_back(m_Next);
	if (m_Last!=NULL)neighbors.push_back(m_Last);
	return neighbors;
}
 
double QRWordArt::QRStringLine::Remain()
{
	return SampleToEndLenght(Cursor());
}

double QRWordArt::QRStringLine::Remainfront()
{
	if (!m_QRSample.empty())
	{
		HSSSpline::Sample sample = m_QRSample.front()->sample;
		double offset = R_Offset(m_QRSample.front()->_char,m_QRSample.front()->sample);
		ShiftSample(sample,offset,&sample);
		return BeginToSampleLenght(sample);
	}else{
		return Lenght();
	}
 }

void QRWordArt::QRStringLine::EditCharSample( int s_idx,HSSSpline::Sample& sample )
{
	m_QRSample[s_idx]->sample = sample;
	m_QRSample[s_idx]->qr_char->Update();
}

void QRWordArt::QRStringLine::Duplicate( HSSSpline::Sample& from, HSSSpline::Sample& to, QRStringLine* output )
{
	if (to.seg_idx > n_segs()-1||(to.seg_idx==-1&&to._t==-1)){
		to.seg_idx = n_segs()-1;
		to._t = 1;
	}

	output->AssignPoints(m_Piecewise_Points);

	HSSSpline::PathPoints<5> ctrl_points;
	ctrl_points().push_back(get_point(from));

	int begin = from.seg_idx;
	if (from._t>0.7){begin++;}

	int end = to.seg_idx;
	if (to._t<0.3){end--;}

	for(int i=begin; i<end; i++)
	{
		ctrl_points().push_back(get_point(i,1));
	}
	ctrl_points().push_back(get_point(to));

	output->AssignCtrlPoints(ctrl_points);
}

void QRWordArt::QRStringLine::DuplicateWithChar(QRStringLine* dst, HSSSpline::Sample from, HSSSpline::Sample to )
{
	if (to.seg_idx==-1 && to._t==-1)
	{
		to.seg_idx=n_segs()-1;
		to._t=1;
	}
	this->Duplicate(from,to,dst);

	for (int i = 0 ; i < this->GetQRSamples().size();i++)
	{				
		if (this->GetQRSamples()[i]->sample.seg_idx==from.seg_idx&&this->GetQRSamples()[i]->sample._t>=from._t)
		{
			QRSample * newcharsample = new QRSample;
			*newcharsample = *this->GetQRSamples()[i];
			dst->GetQRSamples().push_back(newcharsample);
		}
		else if  (this->GetQRSamples()[i]->sample.seg_idx==to.seg_idx&&this->GetQRSamples()[i]->sample._t<=to._t)
		{
			QRSample * newcharsample = new QRSample;
			*newcharsample = *this->GetQRSamples()[i];
			dst->GetQRSamples().push_back(newcharsample);
		}
		else if (this->GetQRSamples()[i]->sample.seg_idx>from.seg_idx&&this->GetQRSamples()[i]->sample.seg_idx<to.seg_idx)
		{
			QRSample * newcharsample = new QRSample;
			*newcharsample = *this->GetQRSamples()[i];
			dst->GetQRSamples().push_back(newcharsample);
		}		
	}
}

int QRWordArt::QRStringLine::CharIDtoWordID(int id)
{
	if (id<0){return -1;}

	WordSamples words =GetWordSamples();
	id+=1;
	for (int i = 0 ; i <words.size(); i ++)
	{
		if (id<=words[i].size()){return i;}
		id-=words[i].size();		
	}
	return -1;
}

QRWordArt::QRStringLine::WordSamples QRWordArt::QRStringLine::GetWordSamples()
{
	QRWordArt::QRStringLine::WordSamples w_samples;

	for (unsigned int i=0;i<m_QRSample.size();)
	{
		int next = i+m_QRSample[i]->w_header;
		
		if (m_QRSample[i]->w_header != 0)
		{
			QRWordArt::QRStringLine::QRSamples c_samples;
			while(i<next)
			{
				c_samples.push_back(m_QRSample[i]);
				i++;
			}
			w_samples.push_back(c_samples);
		}else{
			i++;
		}
	}

	return w_samples;
}

std::vector<std::string> QRWordArt::QRStringLine::GetWords()
{
	std::vector<std::string> words;
	for (unsigned int i=0;i<m_QRSample.size();)
	{
		int w_len = i+m_QRSample[i]->w_header;
		if (m_QRSample[i]->w_header != 0)
		{
			std::string word;
			while(i<w_len)
			{
				word += m_QRSample[i]->_char;
				i++;
			}
			words.push_back(word);
		}else{i++;}
	}
	return words;
}

 
void QRWordArt::QRStringLine::CleanNullSamples()
{
	QRSamples::iterator c_it=m_QRSample.begin();
	while (c_it!=m_QRSample.end())
	{
		int next = (*c_it)->w_header;
		if (next!=0)
		{
			for(int i=0;i<next;i++){c_it++;}
		}
		else
		{
			c_it = m_QRSample.erase(c_it);
		}
	}
}

void QRWordArt::QRStringLine::SortWords()
{
	QRWordArt::QRStringLine::WordSamples unsort = GetWordSamples();
	QRSamples sort;
	while(!unsort.empty())
	{
		int min_idx = -1;
		HSSSpline::Sample sample(n_segs()+1,1);
		for (int i=0;i<unsort.size();i++)
		{
			if(unsort[i].front()->sample<sample)
			{
				min_idx = i;
				sample = unsort[i].front()->sample;
			}
		}

		if (min_idx != -1)
		{
			for (int i=0;i<unsort[min_idx].size();i++)
			{
				sort.push_back(unsort[min_idx][i]);
			}
			unsort.erase(unsort.begin()+min_idx);
		}else{
			break;
		}
	}

	m_QRSample.clear();
	m_QRSample.assign(sort.begin(),sort.end());

}

void QRWordArt::QRStringLine::Release()
{
	while(!m_QRSample.empty())
	{
		QRSample* c_sample = m_QRSample.back();
		if (c_sample!=NULL)
		{
			if (c_sample->qr_char!=NULL)
			{
				delete c_sample->qr_char;
				c_sample->qr_char = NULL;
			}
			delete c_sample;
			c_sample = NULL;
		}
		m_QRSample.pop_back();
	}
	m_Letter_Space= 0;
	m_Word_Space  = 0;
}

void QRWordArt::QRStringLine::DrawWordArt(bool debug)
{
	for (int i=0;i<m_QRSample.size();i++)
	{
		if (m_QRSample[i]->qr_char == NULL){continue;}
		m_QRSample[i]->qr_char->Draw(debug);
	}
}

void QRWordArt::QRStringLine::MoveQRSample( QRSample* qr_sample, HSSSpline::Sample to_sample )
{
	if (qr_sample->qr_char!=NULL)
	{
		double u0 = BeginToSampleLenght(qr_sample->sample) / Lenght();
		double u1 = BeginToSampleLenght(to_sample)  / Lenght();
		double w0 = get_w(qr_sample->sample);
		double w1 = get_w(to_sample);
		for (int i=0;i<qr_sample->qr_char->NodeSize();i++)
		{
			HSSSpline::Vector2 uv = qr_sample->qr_char->Node(i)->Position_UV();
			double new_u = u1 + (uv[0]-u0)/w0 * w1;
			qr_sample->qr_char->Node(i)->Position_UV(new_u,uv[1]);
		}
		for (int i=0;i<qr_sample->qr_char->SkeletonSize();i++){qr_sample->qr_char->Skeleton(i)->ScaleSize(w1/w0);}
		qr_sample->qr_char->Update();
		qr_sample->qr_char->InitData();
	}
	qr_sample->sample = to_sample;
}

std::string QRWordArt::QRStringLine::GetString()
{
	std::vector<std::string> words = GetWords();
	WordSamples wordsamples =GetWordSamples();
	std::string all_text;
	for (int i=0;i<words.size();i++)
	{
		all_text += words[i];
		if (i!=words.size()-1)
		{
			all_text += " ";
			if (wordsamples[i][0]->_IsSentenceEnd) all_text += "   ";
		}
	}
	return all_text;
}

double QRWordArt::QRStringLine::AvgW()
{
	double avg = 0;
	for (int i=0;i<m_Ctrl_Points().size();i++)
	{
		avg += m_Ctrl_Points[i][2];
	}
	if (m_Ctrl_Points().size()!=0)avg/=m_Ctrl_Points().size();
	return avg;
}

void QRWordArt::QRStringLine::DrawCharPoint()
{
	glPointSize(10);
	glColor3d(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	for (int i=0;i<m_QRSample.size();i++)
	{
		HSSSpline::PathPoint<5> p=get_point(m_QRSample[i]->sample);
		glVertex2d(p[0],p[1]);
	}
	glEnd();
}

HSSSpline::Sample QRWordArt::QRStringLine::Cursor()
{
	if (!m_QRSample.empty())
	{
		HSSSpline::Sample sample = m_QRSample.back()->sample;
		double offset = Offset(m_QRSample.back()->_char,m_QRSample.back()->sample);
		bool flag = ShiftSample(sample,offset,&sample);
		if (!flag)
		{
			sample.seg_idx = n_segs()-1;
			sample._t = 1;
		}
		return sample;
	}else{
		return HSSSpline::Sample(0,0);
	}
}

double QRWordArt::QRStringLine::Offset( char c,HSSSpline::Sample& sample )
{
	double size = get_w(sample);
	double width    = size*QRWordArt::QRCharacter::GetWidth(c);
	double bearingX = size*QRWordArt::QRCharacter::GetBearingX(c);
	double advance  = size*QRWordArt::QRCharacter::GetAdvance(c);
	double offset = 0;
	if (width==-1){offset = QRWordArt::QRCharacter::WordSpacing*size*0.5;}
	else          {offset = advance-0.5*width-bearingX;}
	return offset;
}

double QRWordArt::QRStringLine::R_Offset( char c,HSSSpline::Sample& sample )
{
	double size = get_w(sample);
	double width    = size*QRWordArt::QRCharacter::GetWidth(m_QRSample.front()->_char);
	double bearingX = size*QRWordArt::QRCharacter::GetBearingX(m_QRSample.front()->_char);
	double advance  = size*QRWordArt::QRCharacter::GetAdvance(m_QRSample.front()->_char);
	double offset = 0;
	if (width==-1){offset = -1*QRWordArt::QRCharacter::WordSpacing*size*0.5;}
	else{offset = -0.5*width-bearingX;}
	return offset;
}

void QRWordArt::QRStringLine::DrawStroke()
{
	HSSSpline::Sample begin(0,0);
	HSSSpline::Sample end(m_LineSeg_List.size()-1,1);
	DrawStroke( begin,end );
}

void QRWordArt::QRStringLine::DrawStroke( HSSSpline::Sample& from, HSSSpline::Sample& to )
{
	for (int i=from.seg_idx;i<=to.seg_idx;i++)
	{
		double step = 0.1;

		double k = 0;
		if (i==from.seg_idx)k = from._t;
		double end = 1;
		if (i==to.seg_idx)end = to._t;

		while (k<end)
		{
			double s1_1 = get_top(i,k);
			double s1_2 = get_bottom(i,k);
			HSSSpline::PathPoint<2> n1 = get_normal(i,k);

			HSSSpline::PathPoint<2> p1 = get_position(i,k);
			p1[0] += n1[0] * s1_1 * m_StrokeScale;
			p1[1] += n1[1] * s1_1 * m_StrokeScale;
			HSSSpline::PathPoint<2> p2 = get_position(i,k);
			p2[0] -= n1[0] * s1_2 * m_StrokeScale;
			p2[1] -= n1[1] * s1_2 * m_StrokeScale;

			k+=step;
			if (k>end)k=end;
			double s2_1 = get_top(i,k);
			double s2_2 = get_bottom(i,k);
			HSSSpline::PathPoint<2> n2 = get_normal(i,k);

			HSSSpline::PathPoint<2> p3 = get_position(i,k);
			p3[0] += n2[0] * s2_1 * m_StrokeScale;
			p3[1] += n2[1] * s2_1 * m_StrokeScale;
			HSSSpline::PathPoint<2> p4 = get_position(i,k);
			p4[0] -= n2[0] * s2_2 * m_StrokeScale;
			p4[1] -= n2[1] * s2_2 * m_StrokeScale;

			glBegin(GL_TRIANGLE_STRIP);
			glVertex2d(p1[0],p1[1]);
			glVertex2d(p2[0],p2[1]);
			glVertex2d(p3[0],p3[1]);
			glVertex2d(p4[0],p4[1]);
			glEnd();
		}
	}
}

QRWordArt::QRStringLine* QRWordArt::QRStringLine::Clone()
{
	QRStringLine* spline = new QRStringLine;
	spline->AssignCtrlPoints(m_Ctrl_Points);
	for (int i=0;i<m_QRSample.size();i++)
	{
		QRWordArt::QRStringLine::QRSample* qr_sample = spline->AttachChar(m_QRSample[i]->_char,m_QRSample[i]->sample);
		qr_sample->w_header = m_QRSample[i]->w_header;
		if (qr_sample->qr_char!=NULL)
		{
			double r,g,b;
			m_QRSample[i]->qr_char->GetColor(&r,&g,&b);
			qr_sample->qr_char->SetColor(r,g,b);
		}
	}
	return spline;
}

void QRWordArt::QRStringLine::ScaleSpline( double scale )
{
	HSplinePath::ScaleSpline(scale);
	for (int i = 0 ; i < m_QRSample.size() ; i++)
	{
		vector<HSSSpline::Scale3> font_weight = m_QRSample[i]->qr_char->GetAllFontWeight();
		for(int f = 0 ; f<font_weight.size();f++)
		{
			font_weight[f]=font_weight[f]*scale;
		}
		m_QRSample[i]->qr_char->SetAllFontWeight(font_weight);
	}
	Update();
}

void QRWordArt::QRStringLine::EditCtrlPoint( int c_id,HSSSpline::PathPoint<2>& point )
{
	HSplinePath::EditCtrlPoint(c_id,point); 
	Update();
}

void QRWordArt::QRStringLine::TranslateCtrlPoint( int c_id,HSSSpline::PathPoint<2>& point )
{
	HSplinePath::TranslateCtrlPoint(c_id,point); 
	Update();
}

void QRWordArt::QRStringLine::TranslateAllCtrlPoint( HSSSpline::PathPoint<2>& point )
{
	HSplinePath::TranslateAllCtrlPoint(point); 
	Update();
}

void QRWordArt::QRStringLine::EditCtrlPointSize( int c_id,HSSSpline::PathPoint<3>& size )
{
	HSplinePath::EditCtrlPointSize(c_id,size); 
	Update();
}

void QRWordArt::QRStringLine::EditAllCtrlPointSize( HSSSpline::PathPoint<3>& size )
{
	HSplinePath::EditAllCtrlPointSize(size); 
	Update();
}

void QRWordArt::QRStringLine::SoftEditCtrlPointSize( int c_id,HSSSpline::PathPoint<3>& size )
{
	HSplinePath::SoftEditCtrlPointSize(c_id,size); 
	Update();
}

void QRWordArt::QRStringLine::EditSamplePointSize( const HSSSpline::Sample& sample,HSSSpline::PathPoint<3>& size )
{
	HSplinePath::EditSamplePointSize(sample,size); 
	Update();
}

void QRWordArt::QRStringLine::EditAllPointSize( bool plus )
{
	HSplinePath::EditAllPointSize(plus); 
	Update();
}

void QRWordArt::QRStringLine::EditAllPointPosition( int flag, double amount/*=0.1 */ )
{
	HSplinePath::EditAllPointPosition(flag, amount); 
	Update();
}

void QRWordArt::QRStringLine::EditAllPointPosition( HSSSpline::Vector2& vect )
{
	HSplinePath::EditAllPointPosition(vect); 
	Update();
}

void QRWordArt::QRStringLine::Scale( double scale )
{
	HSplinePath::Scale(scale);	
	Update();
}