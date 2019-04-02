#include "StdAfx.h"
#include <algorithm>
#include <cmath>
#include "HSplinePath.h"

namespace HSSSpline
{
	PathPoint<2> HSplinePath::get_position(int _seg, double _t)
	{
		PathPoint<2> position;
		position[0] = get_x(_seg, _t);
		position[1] = get_y(_seg, _t);
		return position;
	}

	PathPoint<2> HSplinePath::get_tangent(int _seg, double _t)
	{
		PathPoint<2> tangent_dir;
		tangent_dir[0] = get_D1_value(0,_seg, _t);
		tangent_dir[1] = get_D1_value(1,_seg, _t);
		double len = sqrt(tangent_dir[0]*tangent_dir[0]+tangent_dir[1]*tangent_dir[1]);
		if (len!=0)
		{
			tangent_dir[0] /= len;
			tangent_dir[1] /= len;
		}
		return tangent_dir;
	}

	PathPoint<2> HSplinePath::get_normal(int _seg, double _t)
	{
		PathPoint<2> normal_dir;
		float x_temp = get_D1_value(0,_seg, _t);
		float y_temp = get_D1_value(1,_seg, _t);

		normal_dir[0] = (y_temp==0?0:-y_temp);
		normal_dir[1] = (x_temp==0?0:x_temp);
		double len = sqrt(normal_dir[0]*normal_dir[0]+normal_dir[1]*normal_dir[1]);
		if (len!=0)
		{
			normal_dir[0] /= len;
			normal_dir[1] /= len;
		}
		return normal_dir;
	}

	PathPoint<5>  HSplinePath::get_midpoint()
	{
		PathPoints<5> points = GetUniformSamplePoints(1);
		int id = points().size()/2;
		return points[id];
	}

	double HSplinePath::Lenght(const Sample& s0,const Sample& s1 )
	{
		return BeginToSampleLenght(s1)-BeginToSampleLenght(s0);
	}

	double HSplinePath::Lenght()
	{
		double len=0;
		for (unsigned int i=0;i<m_LineSeg_List.size();i++)
		{
			len += SegLenght(i);
		}
		return len;
	}

	double HSplinePath::SegLenght( int seg_idx )
	{
		if (m_SegLenght[seg_idx]<0)
		{
			double len=0;
			double step = 0.00001;
			for (double k=0;k<1;k+=step)
			{
				PathPoint<2> p0 = get_position(seg_idx,k);
				PathPoint<2> p1 = get_position(seg_idx,k+step);
				len += sqrt((p1[0]-p0[0])*(p1[0]-p0[0]) + (p1[1]-p0[1])*(p1[1]-p0[1]));
			}
			m_SegLenght[seg_idx] = len;
		}
		return m_SegLenght[seg_idx];
	}

	double HSplinePath::BeginToSampleLenght(const Sample& s )
	{
		double len=0;
		for (unsigned int i=0;i<s.seg_idx;i++)
		{
			len += SegLenght(i);
		}
		len += SegToSampleLenght(s);

		return len;
	}

	double HSplinePath::SampleToEndLenght(const Sample& s )
	{
		return Lenght()-BeginToSampleLenght(s);
	}

	double HSplinePath::SegToSampleLenght(const Sample& sample )
	{
		double len=0;
		double step = 0.01;
		for (double k=0;k<sample._t;k+=step)
		{
			PathPoint<2> p0 = get_position(sample.seg_idx,k);
			PathPoint<2> p1 = get_position(sample.seg_idx,k+step);
			len += sqrt((p1[0]-p0[0])*(p1[0]-p0[0]) + (p1[1]-p0[1])*(p1[1]-p0[1]));
		}
		return len;
	}

	PathPoint<3> HSplinePath::get_size( int _seg, double _t )
	{
		PathPoint<3> size;
		size[0] = get_w (_seg, _t);
		size[1] = get_top(_seg, _t);
		size[2] = get_bottom(_seg, _t);
		return size;
	}

	void HSplinePath::PushBack( PathPoint<2>& point )
	{
		m_Piecewise_Points().push_back(PathPoint<5>(point[0],point[1]));
	}

	void HSplinePath::PushBack( PathPoint<5>& point_info )
	{
		m_Piecewise_Points().push_back(point_info);
	}

	void HSplinePath::AssignPoints( PathPoints<5>& points )
	{
		m_Piecewise_Points().assign(points().begin(),points().end());
	}

	void HSplinePath::AssignCtrlPoints( PathPoints<5>& ctrl_points )
	{
		m_Ctrl_Points().clear();
		m_Ctrl_Points().assign(ctrl_points().begin(),ctrl_points().end());
		BuildingSpline(m_Ctrl_Points);
	}

	void HSplinePath::AugmentCtrlPoint( int num )
	{
		PathPoints<5> ctrl;
		ctrl().push_back(get_point(0,0));
		for (int i=0;i<n_segs();i++)
		{
			double seg = 1/(double)num;
			for (double t=seg;t<=1;t+=seg)
			{
				ctrl().push_back(get_point(i,t));
			}
		}
		AssignCtrlPoints(ctrl);
	}

	void HSplinePath::FittingCurve( double fit_ratio, bool auto_adjust )
	{
		if (m_Piecewise_Points().empty())return;

		BuildingSpline(m_Piecewise_Points);
		m_Ctrl_Points().clear();
		double lenght = Lenght();

		if (auto_adjust)
		{
			if (lenght<50)
			{
				fit_ratio = 0.5;
			}else if (lenght<150)
			{
				fit_ratio = 0.2;
			}else
			{
				fit_ratio /= (int)(1+lenght/500);
			}
		}
		
		m_Ctrl_Points = GetUniformSamplePoints(fit_ratio*lenght);
		BuildingSpline(m_Ctrl_Points);
	}

	void HSplinePath::RefittingCurve( double fit_ratio )
	{
		if (Lenght()<30)
		{
			fit_ratio=0.5;
		}
		else if (Lenght()<50)
		{
			fit_ratio=0.25;
		}
	/*	else if(Lenght()<100)
		{
			fit_ratio=0.2;
		}
		else if(Lenght()<150)
		{
			fit_ratio=0.1;
		}*/
		m_Ctrl_Points = GetUniformSamplePoints(fit_ratio*Lenght());
		BuildingSpline(m_Ctrl_Points);
	}

	HSSSpline::Samples HSplinePath::UniformSampling( double per_len )
	{
		Samples samples;

		Sample sample_0;
		sample_0.seg_idx = 0;
		sample_0._t = 0;
		samples.push_back(sample_0);

		double temp_len = 0;
		for (unsigned int i=0;i<m_LineSeg_List.size();i++)
		{
			double step = 1/SegLenght(i);
			for (double k=0;k<1;k+=step)
			{
				PathPoint<2> p0 = get_position(i,k);
				PathPoint<2> p1;
				if (k+step<=1){p1 = get_position(i,k+step);}
				else {p1 = get_position(i,1);}

				temp_len += sqrt((p1[0]-p0[0])*(p1[0]-p0[0]) + (p1[1]-p0[1])*(p1[1]-p0[1]));

				if (temp_len >= per_len)
				{
					Sample sample;
					sample.seg_idx = i;
					sample._t = k+step;
					samples.push_back(sample);
					temp_len = 0;
				}
			}
		}
		return samples;
	}

	HSSSpline::PathPoints<5> HSplinePath::GetUniformSamplePoints( double per_len )
	{
		HSSSpline::PathPoints<5> points;
		double temp_len = 0;

		points().push_back(get_point(0,0));
		for (unsigned int i=0;i<m_LineSeg_List.size();i++)
		{
			double step = 0.01;
			for (double k=0;k<1;k+=step)
			{
				PathPoint<5> p0 = get_point(i,k);
				PathPoint<5> p1;
				if (k+step<=1){p1 = get_point(i,k+step);}
				else {p1 = get_point(i,1);}
				double len = sqrt((p1[0]-p0[0])*(p1[0]-p0[0]) + (p1[1]-p0[1])*(p1[1]-p0[1]));
				temp_len += len;

				if (abs(temp_len - per_len)<0.01)
				{
					points().push_back(p1);
					temp_len = 0;
				}else{
					if (temp_len > per_len)
					{
						temp_len-=len;
						step/=10;
					}
				}
			}
		}

		if (temp_len>per_len*0.5)
		{
			points().push_back(get_point(m_LineSeg_List.size()-1,1));
		}

		return points;
	}

	double HSplinePath::SelectCtrlPoint( double x,double y,int *select )
	{
		*select = -1;
		double min_dis = 100;
		for (unsigned int i=0;i<m_Ctrl_Points().size();i++)
		{
			double dis = (m_Ctrl_Points[i][0] - x)*(m_Ctrl_Points[i][0] - x) + (m_Ctrl_Points[i][1] - y)*(m_Ctrl_Points[i][1] - y);
			if (min_dis > dis)
			{
				min_dis = dis;
				*select = i;
			}
		}
		return min_dis;
	}
	
	void HSplinePath::EditCtrlPoint( int c_id,PathPoint<2>& point )
	{
		m_Ctrl_Points[c_id][0] = point[0];
		m_Ctrl_Points[c_id][1] = point[1];
		BuildingSpline(m_Ctrl_Points);
	}

	void HSplinePath::TranslateCtrlPoint( int c_id,PathPoint<2>& point )
	{
		m_Ctrl_Points[c_id][0] += point[0];
		m_Ctrl_Points[c_id][1] += point[1];
		BuildingSpline(m_Ctrl_Points);
	}

	void HSplinePath::TranslateAllCtrlPoint( PathPoint<2>& point )
	{
		for (int i=0;i<m_Ctrl_Points().size();i++)
		{
			m_Ctrl_Points[i][0] += point[0];
			m_Ctrl_Points[i][1] += point[1];
		}
		BuildingSpline(m_Ctrl_Points);
	}

	void HSplinePath::EditSamplePoint( Sample& sample,PathPoint<2>& p1 )
	{
		PathPoint<2> p0 = get_position(sample);

		int c0 = sample.seg_idx;
		int c1 = c0 + 1;

		PathPoint<2> vec = p1 - p0;

		m_Ctrl_Points[c0][0] += vec[0]*(1-sample._t);
		m_Ctrl_Points[c0][1] += vec[1]*(1-sample._t);
		
		m_Ctrl_Points[c1][0] += vec[0]*   sample._t ;
		m_Ctrl_Points[c1][1] += vec[1]*   sample._t ;
		
		BuildingSpline(m_Ctrl_Points);
	}

	void HSplinePath::EditCtrlPointSize( int c_id,PathPoint<3>& size )
	{
		m_Ctrl_Points[c_id][2] = size[0];
		m_Ctrl_Points[c_id][3] = size[1];
		m_Ctrl_Points[c_id][4] = size[2];
		BuildingSpline(m_Ctrl_Points);
	}

	void HSplinePath::SoftEditCtrlPointSize( int c_id,PathPoint<3>& size )
	{
		PathPoint<3> v;
		v[0] = size[0]-m_Ctrl_Points[c_id][2];
		v[1] = size[1]-m_Ctrl_Points[c_id][3];
		v[2] = size[2]-m_Ctrl_Points[c_id][4];

		int left_num  = c_id;
		int right_num = m_Ctrl_Points().size() - c_id;

		for (int i=0;i<left_num;i++)
		{
			PathPoint<3> scale;
			double interpolated = (double)i / (double)left_num;
			scale[0] = m_Ctrl_Points[i][2] + interpolated*v[0];
			scale[1] = m_Ctrl_Points[i][3] + interpolated*v[1];
			scale[2] = m_Ctrl_Points[i][4] + interpolated*v[2];
			EditCtrlPointSize(i,scale);
		}

		for (int i=1;i<=right_num;i++)
		{
			PathPoint<3> scale;
			double interpolated = (double)(right_num-i) / (double)right_num;
			scale[0] = m_Ctrl_Points[c_id+i][2] + interpolated*v[0];
			scale[1] = m_Ctrl_Points[c_id+i][3] + interpolated*v[1];
			scale[2] = m_Ctrl_Points[c_id+i][4] + interpolated*v[2];
			EditCtrlPointSize(c_id+i,scale);
		}

		EditCtrlPointSize(c_id,size);
	}

	void HSplinePath::EditAllCtrlPointSize( PathPoint<3>& size )
	{
		for (int i=0;i<m_Ctrl_Points().size();i++)
		{
			m_Ctrl_Points[i][2] = size[0];
			m_Ctrl_Points[i][3] = size[1];
			m_Ctrl_Points[i][4] = size[2];
		}
		BuildingSpline(m_Ctrl_Points);
	}

	void HSplinePath::EditSamplePointSize(const Sample& sample,PathPoint<3>& s1 )
	{
		PathPoint<3> s0 = get_size(sample);

		int c0 = sample.seg_idx;
		int c1 = c0 + 1;

		PathPoint<3> vec = s1 - s0;

		m_Ctrl_Points[c0][2] += vec[0]*(1-sample._t);
		m_Ctrl_Points[c0][3] += vec[1]*(1-sample._t);
		m_Ctrl_Points[c0][4] += vec[2]*(1-sample._t);
		
		m_Ctrl_Points[c1][2] += vec[0]*   sample._t ;
		m_Ctrl_Points[c1][3] += vec[1]*   sample._t ;
		m_Ctrl_Points[c1][4] += vec[2]*   sample._t ;
		
		BuildingSpline(m_Ctrl_Points);
	}

	void HSplinePath::EditAllPointSize( bool plus )
	{

		for (int i = 0 ; i <m_Ctrl_Points.size(); i++)
		{
			if (plus)
			{
				m_Ctrl_Points[i][2] = m_Ctrl_Points[i][2]+0.2;
				m_Ctrl_Points[i][3] = m_Ctrl_Points[i][3]+0.1;
				m_Ctrl_Points[i][4] = m_Ctrl_Points[i][4]+0.1;
			}else
			{
				m_Ctrl_Points[i][2] = m_Ctrl_Points[i][2]-0.2;
				m_Ctrl_Points[i][3] = m_Ctrl_Points[i][3]-0.1;
				m_Ctrl_Points[i][4] = m_Ctrl_Points[i][4]-0.1;
			}
		}
		BuildingSpline(m_Ctrl_Points);
	}

	void HSplinePath::EditAllPointPosition( HSSSpline::Vector2& vect )
	{
		for (int i = 0 ; i <m_Ctrl_Points.size(); i++)
		{
			m_Ctrl_Points[i][1] += vect[1];
			m_Ctrl_Points[i][0] += vect[0];
		}
		BuildingSpline(m_Ctrl_Points);
	}

	void HSplinePath::EditAllPointPosition( int flag ,double amount)
	{

		for (int i = 0 ; i <m_Ctrl_Points.size(); i++)
		{
			switch(flag)
			{
			case 0:
				m_Ctrl_Points[i][1] += amount;
				break;
			case 1:
				m_Ctrl_Points[i][1] -= amount;
				break;
			case 2:
				m_Ctrl_Points[i][0] += amount;
				break;
			case 3:
				m_Ctrl_Points[i][0] -= amount;
				break;
			}
		}
		BuildingSpline(m_Ctrl_Points);
	}

	void HSplinePath::Scale( double scale )
	{
		for (int i=0;i<m_Ctrl_Points().size();i++)
		{
			m_Ctrl_Points[i][2] *= scale;
			m_Ctrl_Points[i][3] *= scale;
			m_Ctrl_Points[i][4] *= scale;
		}
		BuildingSpline(m_Ctrl_Points);
	}

	bool HSplinePath::ShiftSample( Sample& from,double offset,Sample* output )
	{
		if (offset<0)
		{
			return ShiftSampleBackward(from,abs(offset),output);
		}else{
			return ShiftSampleForeward(from,abs(offset),output);
		}
	}

	bool HSplinePath::ShiftSampleForeward( Sample& from,double offset,Sample* output )
	{
		double step = 0.001;
		double sum_dis = 0;

		//Head
		for(double k=from._t;k<1;k+=step)
		{
			PathPoint<2> p0 = get_position(from.seg_idx,k);
			if(k+step>1)break;
			PathPoint<2> p1 = get_position(from.seg_idx,k+step);

			double dis = sqrt((p1[0]-p0[0])*(p1[0]-p0[0])+(p1[1]-p0[1])*(p1[1]-p0[1]));
			sum_dis += dis;

			if (offset<=sum_dis)
			{
				output->seg_idx = from.seg_idx;
				output->_t = k;
				return true;
			}
		}

		for (int i=from.seg_idx+1;i<m_LineSeg_List.size();i++)
		{
			double seg_len = SegLenght(i);
			if (sum_dis + seg_len < offset)
			{
				sum_dis += seg_len;
			}else{
				double k=0;
				for(double k=0;k<1;k+=step)
				{
					PathPoint<2> p0 = get_position(i,k);
					if(k+step>1)break;
					PathPoint<2> p1 = get_position(i,k+step);

					double dis = sqrt((p1[0]-p0[0])*(p1[0]-p0[0])+(p1[1]-p0[1])*(p1[1]-p0[1]));
					sum_dis += dis;

					if (offset<=sum_dis)
					{
						output->seg_idx = i;
						output->_t = k;
						return true;
					}
				}
			}
		}

		output->seg_idx = m_LineSeg_List.size()-1;
		output->_t = 1;
		return false;
	}

	bool HSplinePath::ShiftSampleBackward( Sample& from,double offset,Sample* output )
	{
		double step = 0.001;
		double sum_dis = 0;

		//Head
		for(double k=from._t;k>0;k-=step)
		{
			PathPoint<2> p0 = get_position(from.seg_idx,k);
			if(k-step<0)break;
			PathPoint<2> p1 = get_position(from.seg_idx,k-step);

			double dis = sqrt((p1[0]-p0[0])*(p1[0]-p0[0])+(p1[1]-p0[1])*(p1[1]-p0[1]));
			sum_dis += dis;

			if (offset<=sum_dis)
			{
				output->seg_idx = from.seg_idx;
				output->_t = k;
				return true;
			}
		}

		for (int i=from.seg_idx-1;i>=0;i--)
		{
			double seg_len = SegLenght(i);
			if (sum_dis + seg_len < offset)
			{
				sum_dis += seg_len;
			}else{
				double k=0;
				for(double k=1;k>0;k-=step)
				{
					PathPoint<2> p0 = get_position(i,k);
					if(k-step<0)break;
					PathPoint<2> p1 = get_position(i,k-step);

					double dis = sqrt((p1[0]-p0[0])*(p1[0]-p0[0])+(p1[1]-p0[1])*(p1[1]-p0[1]));
					sum_dis += dis;

					if (offset<=sum_dis)
					{
						output->seg_idx = i;
						output->_t = k;
						return true;
					}
				}
			}
		}

		output->seg_idx = 0;
		output->_t = 0;
		return false;
	}

	HSSSpline::Sample HSplinePath::World2Local( double x,double y,double* u,double* v )
	{
		double min_len = 99999999999;
		HSSSpline::Sample sample;

		int cp = 0;
		for (int c=0;c<m_Ctrl_Points.size();c++)
		{
			double  dis = sqrt((m_Ctrl_Points[c][0]-x)*(m_Ctrl_Points[c][0]-x)+(m_Ctrl_Points[c][1]-y)*(m_Ctrl_Points[c][1]-y));
			if (min_len>dis)
			{
				min_len = dis;
				cp = c;
			}
 		}

		min_len = 99999999999;
		int cp_begin = max(cp-2,0);
		int cp_end   = min(cp+2,n_segs()-1);
		for (int i=cp_begin;i<=cp_end;i++)
		{
			for (double t=0;t<=1;t+=0.01)
			{
				PathPoint<2> vec = get_position(i,t);
				vec[0]-=x;vec[1]-=y;

				double  dis = vec[0]*vec[0]+vec[1]*vec[1];
				if (min_len>dis)
				{
					min_len=dis;
					sample.seg_idx = i;
					sample._t = t;

					//Normalize
					dis = sqrt(dis);
					if (dis!=0){vec[0]/=dis;vec[1]/=dis;}

					PathPoint<2> normal = get_normal(sample);
					double dot = normal[0]*vec[0]+normal[1]*vec[1];
					if (dot<0){*v = dis / get_bottom(sample);}
					else{*v = -1*dis / get_top(sample);}
				}
			}
		}
		if (sample.seg_idx>=n_segs()){sample.seg_idx = n_segs()-1;sample._t = 1;}

		*u = BeginToSampleLenght(sample)/Lenght();
		return sample;
	}

	HSSSpline::Sample HSplinePath::Local2World( double u,double v,double* x,double* y )
	{
		HSSSpline::Sample sample;
		double offset = u * Lenght();
		bool flag = ShiftSample(sample,offset,&sample);

		if (!flag)
		{
			if (offset>0)
			{
				sample.seg_idx = n_segs()-1; 
				sample._t = 1;
			}else{
				sample.seg_idx = 0; 
				sample._t = 0;
			}
		}

		PathPoint<2> p=get_position(sample);
		PathPoint<2> normal = get_normal(sample);

		double len = 0;
		if (v>0){len = get_top(sample);}
		else{len = get_bottom(sample);}

		*x = p[0]+v*len*normal[0];
		*y = p[1]+v*len*normal[1];

		return sample;
	}
	void HSplinePath::DrawLine()
	{
		Sample begin(0,0);
		Sample end(m_LineSeg_List.size()-1,1);
		DrawLine( begin,end );
	}

	void HSplinePath::DrawLine( Sample& from,Sample& to )
	{
		double step = 0.1;
		glBegin(GL_LINES);
		for (int i=from.seg_idx;i<=to.seg_idx;i++)
		{
			double k = 0;
			if (i==from.seg_idx){k = from._t;}
			double end = 1;
			if (i==to.seg_idx){end = to._t;}

			while(k<end)
			{
				PathPoint<2>  p1 = get_position(i,k);
				k+=step;
				if (k>end)k=end;
				PathPoint<2>  p2 = get_position(i,k);

				glVertex2d(p1[0],p1[1]);
				glVertex2d(p2[0],p2[1]);
			}
		}
		glEnd();
	}

	void HSplinePath::DrawStroke()
	{
		Sample begin(0,0);
		Sample end(m_LineSeg_List.size()-1,1);
		DrawStroke( begin,end );
	}

	void HSplinePath::DrawStroke( Sample& from,Sample& to )
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
				PathPoint<2> n1 = get_normal(i,k);

				PathPoint<2> p1 = get_position(i,k);
				p1[0] += n1[0] * s1_1 * 1.2;
				p1[1] += n1[1] * s1_1 * 1.2;
				PathPoint<2> p2 = get_position(i,k);
				p2[0] -= n1[0] * s1_2 * 1.2;
				p2[1] -= n1[1] * s1_2 * 1.2;

				k+=step;
				if (k>end)k=end;
				double s2_1 = get_top(i,k);
				double s2_2 = get_bottom(i,k);
				PathPoint<2> n2 = get_normal(i,k);

				PathPoint<2> p3 = get_position(i,k);
				p3[0] += n2[0] * s2_1 * 1.2;
				p3[1] += n2[1] * s2_1 * 1.2;
				PathPoint<2> p4 = get_position(i,k);
				p4[0] -= n2[0] * s2_2 * 1.2;
				p4[1] -= n2[1] * s2_2 * 1.2;

				glBegin(GL_TRIANGLE_STRIP);
				glVertex2d(p1[0],p1[1]);
				glVertex2d(p2[0],p2[1]);
				glVertex2d(p3[0],p3[1]);
				glVertex2d(p4[0],p4[1]);
				glEnd();
			}
		}
	}

	void HSplinePath::DrawCtrlPoint()
	{
		glPointSize(5);
		glColor3d(1.0,0.0,0.0);
		glBegin(GL_POINTS);
		for (int i=0;i<m_Ctrl_Points().size();i++){glVertex2d(m_Ctrl_Points[i][0],m_Ctrl_Points[i][1]);}
		glEnd();
	}

	void HSplinePath::DrawCapLine()
	{
		Sample begin(0,0);
		Sample end(m_LineSeg_List.size()-1,1);

		glLineWidth(1.0);
		glColor4d(0.0,0.0,1.0,1.0);

		DrawCapLine( begin,end );
	}

	void HSplinePath::DrawCapLine( Sample& from,Sample& to )
	{
		double step = 0.1;
		glBegin(GL_LINES);
		for (int i=from.seg_idx;i<=to.seg_idx;i++)
		{
			double k = 0;
			if (i==from.seg_idx)k = from._t;
			double end = 1;
			if (i==to.seg_idx)end = to._t;

			PathPoint<2>  p1 = get_position(i,k);
			p1 +=get_normal(i,k)*get_top(i,k);
			while(k<end)
			{
				k+=step;
				if(k>end)k=end;

				PathPoint<2>  p2 = get_position(i,k);
				p2 += get_normal(i,k)*get_top(i,k);

				glVertex2d(p1[0],p1[1]);
				glVertex2d(p2[0],p2[1]);

				p1=p2;
			}
		}
		glEnd();
	}

	void HSplinePath::DrawBaseLine()
	{
		Sample begin(0,0);
		Sample end(m_LineSeg_List.size()-1,1);

		glLineWidth(1.0);
		glColor4d(0.0,0.0,1.0,1.0);

		DrawBaseLine( begin,end );
	}

	void HSplinePath::DrawBaseLine( Sample& from,Sample& to )
	{
		double step = 0.1;
		glBegin(GL_LINES);
		for (int i=from.seg_idx;i<=to.seg_idx;i++)
		{
			double k = 0;
			if (i==from.seg_idx)k = from._t;
			double end = 1;
			if (i==to.seg_idx)end = to._t;

			PathPoint<2> p1 = get_position(i,k);
			p1-=get_normal(i,k)*get_bottom(i,k);
			while(k<end)
			{
				k+=step;
				if(k>end)k=end;

				PathPoint<2> p2 = get_position(i,k);
				p2-=get_normal(i,k)*get_bottom(i,k);

				glVertex2d(p1[0],p1[1]);
				glVertex2d(p2[0],p2[1]);

				p1=p2;
			}
		}
		glEnd();
	}

	HSSSpline::Sample HSplinePath::GetSample( double u )
	{
		HSSSpline::Sample sample(0,0);
		ShiftSample(sample,u,&sample);
		return sample;
	}

	int HSplinePath::BuildingSpline( PathPoints<5> &_points )
	{
		int flag = HSplineCore::BuildingSpline(_points);
		if (flag==0)//預算線段長度
		{
			m_SegLenght.clear();
			m_SegLenght.resize(n_segs(),-1);
			for (int i=0;i<n_segs();i++){SegLenght(i);}
		}
		return flag;
	}

	void HSplinePath::ScaleSpline( double scale )
	{
		for (int i = 0 ; i < m_Ctrl_Points.size();i++)
		{
			m_Ctrl_Points[i][0]*=scale;
			m_Ctrl_Points[i][1]*=scale;
			m_Ctrl_Points[i][2]*=scale;
			m_Ctrl_Points[i][3]*=scale;
			m_Ctrl_Points[i][4]*=scale;
		}
		BuildingSpline(m_Ctrl_Points);
	}

}