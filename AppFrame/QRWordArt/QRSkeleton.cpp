#include "StdAfx.h"
#include "QRSkeleton.h"

namespace QRWordArt
{
	namespace QRCharacter
	{
		QRSkeleton::QRSkeleton( void ):m_W(1),m_H1(1),m_H2(1)
		{

		}

		QRSkeleton::~QRSkeleton( void )
		{
			m_LineSeg_List.clear();
			m_Nodes.clear();
		}

		void QRSkeleton::Update()
		{
			HSSSpline::PathPoints<2> points;
			for (int i=0;i<m_Nodes.size();i++){points().push_back(m_Nodes[i]->Position());}
			BuildingSpline(points);
			points.clear();
		}

		void QRSkeleton::InterpolateNode( HSSSpline::HSplinePath* spline,HSSSpline::Sample& posn, double perlen, bool fix_v )
		{
			HSplineCore<2> uv_spline;
			double spline_len = spline->Lenght();

			double top    = spline->get_top(posn);
			double bottom = spline->get_bottom(posn);

			HSSSpline::PathPoints<2> points;
			for (int i=0;i<m_Nodes.size();i++)
			{
				HSSSpline::Vector2 uv = m_Nodes[i]->Position_UV();
				if (uv[1]>0)uv[1]*=top;
				else uv[1]*=bottom;
				points().push_back(uv);
			}
			uv_spline.BuildingSpline(points);

			QRNodes new_nodes;
			for (int i=0;i<uv_spline.n_segs();i++)
			{
				new_nodes.push_back(m_Nodes[i]);

				double len = SplineLenght(uv_spline,i);
				double seg = floor(len/perlen);
				double seg_len  = len/seg;

				double step = 0.0001;
				double temp_len = 0;
				double k = 0;
				for (double t=0; t<=1-step && k<seg; t+=step)
				{
					HSSSpline::Vector2 p0 = uv_spline.get_point(i,t);
					HSSSpline::Vector2 p1 = uv_spline.get_point(i,t+step);

					temp_len += sqrt((p1[0]-p0[0])*(p1[0]-p0[0]) + (p1[1]-p0[1])*(p1[1]-p0[1]));

					if (temp_len >= seg_len)
					{
						QRNode* node = new QRNode(spline);
						double v = 0;
						if (p1[1]>0)v = p1[1] / top;
						else v = p1[1] / bottom;

						node->Position_UV(p1[0],v);
						node->FixV(fix_v);
						new_nodes.push_back(node);
						temp_len = 0;

						k++;
					}
				}	
			}
			new_nodes.push_back(m_Nodes[uv_spline.n_segs()]);

			m_Nodes.clear();
			m_Nodes = new_nodes;

			Update();
		}

		double QRSkeleton::SplineLenght( HSplineCore<2>& spline,int seg_idx )
		{
			double len=0;
			double step = 0.00001;
			for (double k=0;k<1;k+=step)
			{
				HSSSpline::PathPoint<2> p0= spline.get_point(seg_idx,k);
				HSSSpline::PathPoint<2> p1= spline.get_point(seg_idx,k+step);
				len += sqrt((p1[0]-p0[0])*(p1[0]-p0[0]) + (p1[1]-p0[1])*(p1[1]-p0[1]));
			}
			return len;
		}

		void QRSkeleton::Draw()
		{
			double step = 0.01;
			glBegin(GL_LINES);
			glLineWidth(1.0f);
			for (int i=0;i<n_segs();i++)
			{
				double k = 0;
				while(k<1)
				{
					HSSSpline::PathPoint<2> p1 = get_point(i,k);
					k+=step;if (k>1)k=1;
					HSSSpline::PathPoint<2> p2 = get_point(i,k);

					glVertex2d(p1[0],p1[1]);
					glVertex2d(p2[0],p2[1]);
				}
			}
			glEnd();
		}

		void QRSkeleton::DrawStroke()
		{
			double step = 0.1;
			if (m_W<0.01)
			{
				glBegin(GL_LINES);
				glLineWidth(2.0f);
				for (int i=0;i<n_segs();i++)
				{
					double k = 0;
					while(k<1)
					{
						HSSSpline::PathPoint<2> p1 = get_point(i,k);
						k+=step;if (k>1)k=1;
						HSSSpline::PathPoint<2> p2 = get_point(i,k);

						glVertex2d(p1[0],p1[1]);
						glVertex2d(p2[0],p2[1]);
					}
				}
				glEnd();
			}else{
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_ALPHA_TEST);
				glAlphaFunc(GL_GREATER,0.5);
				glBindTexture(GL_TEXTURE_2D,m_StrokeTexture);
				glBegin(GL_QUADS);
				for (int i=0;i<n_segs();i++)
				{
					for(double k=0;k<1;k+=step)
					{
						HSSSpline::PathPoint<2> p = get_point(i,k);
						HSSSpline::PathPoint<2> normal  = get_normal(i,k);
						HSSSpline::PathPoint<2> tangent = get_tangent(i,k);
						glTexCoord2d(0,0);glVertex2d(p[0]+m_W*tangent[0]+m_H1*normal[0],p[1]+m_W*tangent[1]+m_H1*normal[1]);
						glTexCoord2d(1,0);glVertex2d(p[0]+m_W*tangent[0]-m_H2*normal[0],p[1]+m_W*tangent[1]-m_H2*normal[1]);
						glTexCoord2d(1,1);glVertex2d(p[0]-m_W*tangent[0]-m_H2*normal[0],p[1]-m_W*tangent[1]-m_H2*normal[1]);
						glTexCoord2d(0,1);glVertex2d(p[0]-m_W*tangent[0]+m_H1*normal[0],p[1]-m_W*tangent[1]+m_H1*normal[1]);
					}
				}
				glEnd();
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_ALPHA_TEST);
			}
		}

		HSSSpline::PathPoint<2> QRSkeleton::get_normal( int _seg,double _t )
		{
			HSSSpline::PathPoint<2> normal;
			double x_tangent = get_D1_value(0,_seg, _t);
			double y_tangent = get_D1_value(1,_seg, _t);

			normal[0] = (y_tangent==0?0:-y_tangent);
			normal[1] = (x_tangent==0?0: x_tangent);

			double len = sqrt(normal[0]*normal[0] + normal[1]*normal[1]);

			normal[0] /= len;
			normal[1] /= len;

			return normal;
		}

		HSSSpline::PathPoint<2> QRSkeleton::get_tangent( int _seg,double _t )
		{
			HSSSpline::PathPoint<2> tangent;
			tangent[0] = get_D1_value(0,_seg, _t);
			tangent[1] = get_D1_value(1,_seg, _t);

			double len = sqrt(tangent[0]*tangent[0] + tangent[1]*tangent[1]);

			tangent[0] /= len;
			tangent[1] /= len;

			return tangent;
		}

		unsigned int QRSkeleton::m_StrokeTexture=0;
		void QRSkeleton::LoadStrokeTexture()
		{
			cv::Mat src = cv::imread("pattern/stroke.bmp",CV_LOAD_IMAGE_GRAYSCALE);
			glGenTextures(1, &m_StrokeTexture);
			glBindTexture(GL_TEXTURE_2D, m_StrokeTexture);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, src.cols, src.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE,(GLvoid*)src.data);
			glDisable(GL_TEXTURE_2D);
		}

		void QRSkeleton::SetBold( double w,double h1,double h2 )
		{
			m_W  = w;
			m_H1 = h1;
			m_H2 = h2;
		}

		void QRSkeleton::ScaleSize( double s )
		{
			m_W  *= s;
			m_H1 *= s;
			m_H2 *= s;
		}

		std::vector<HSSSpline::Vector2> QRSkeleton::GetStoke()
		{
			std::vector<HSSSpline::Vector2> stroke_pts;

			for (int i=0;i<n_segs();i++)
			{
				HSSSpline::PathPoint<2> p = get_point(i,0);
				HSSSpline::PathPoint<2> normal  = get_normal(i,0);
				HSSSpline::PathPoint<2> tangent = get_tangent(i,0);

				HSSSpline::PathPoint<2> p1( p[0]+m_W*tangent[0]+m_H1*normal[0],p[1]+m_W*tangent[1]+m_H1*normal[1] );
				stroke_pts.push_back(p1);
				HSSSpline::PathPoint<2> p2( p[0]+m_W*tangent[0]-m_H2*normal[0],p[1]+m_W*tangent[1]-m_H2*normal[1] );
				stroke_pts.push_back(p2);
				HSSSpline::PathPoint<2> p3( p[0]-m_W*tangent[0]-m_H2*normal[0],p[1]-m_W*tangent[1]-m_H2*normal[1] );
				stroke_pts.push_back(p3);
				HSSSpline::PathPoint<2> p4( p[0]-m_W*tangent[0]+m_H1*normal[0],p[1]-m_W*tangent[1]+m_H1*normal[1] );
				stroke_pts.push_back(p4);
			}

			HSSSpline::PathPoint<2> p = get_point(n_segs()-1,1);
			HSSSpline::PathPoint<2> normal  = get_normal(n_segs()-1,1);
			HSSSpline::PathPoint<2> tangent = get_tangent(n_segs()-1,1);

			HSSSpline::PathPoint<2> p1( p[0]+m_W*tangent[0]+m_H1*normal[0],p[1]+m_W*tangent[1]+m_H1*normal[1] );
			stroke_pts.push_back(p1);
			HSSSpline::PathPoint<2> p2( p[0]+m_W*tangent[0]-m_H2*normal[0],p[1]+m_W*tangent[1]-m_H2*normal[1] );
			stroke_pts.push_back(p2);
			HSSSpline::PathPoint<2> p3( p[0]-m_W*tangent[0]-m_H2*normal[0],p[1]-m_W*tangent[1]-m_H2*normal[1] );
			stroke_pts.push_back(p3);
			HSSSpline::PathPoint<2> p4( p[0]-m_W*tangent[0]+m_H1*normal[0],p[1]-m_W*tangent[1]+m_H1*normal[1] );
			stroke_pts.push_back(p4);

			return stroke_pts;
		}
	}
}