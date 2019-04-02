#include "StdAfx.h"
#include "QRCharacter.h"

#include "LinearSystemSolver.h"
#include "SparseLinearSystemManager.h"

namespace QRWordArt
{
	namespace QRCharacter
	{
		double Char::_Wsp=10;
		double Char::_Wst=10;
		double Char::_Wal=1000000000000;

		Char::Char( char c):m_Char(c)
		{
			m_Color[0] = 0.0;m_Color[1] = 0.0;m_Color[2] = 0.0;
		}

		Char::~Char( void ){Release();}

		void Char::AddNode( QRNode* node )
		{
			if (node->Index()==-1)
			{
				m_Nodes.push_back(node);
				node->Index(m_Nodes.size()-1);
			}
		}

		void Char::CreateSkeleton( std::vector<int>& node_idx, HSSSpline::Sample& posn, bool fix_v, bool collinear,double w, double h1, double h2)
		{
			QRSkeleton* skeleton = new QRSkeleton;
			skeleton->SetBold(w,h1,h2);
			for (int i=0;i<node_idx.size();i++)
			{
				skeleton->AddNode(m_Nodes[node_idx[i]]);
			}

			//skeleton->InterpolateNode(m_StringLine,posn,0.065*m_StringLine->get_w(posn),fix_v);
			QRNodes nodes = skeleton->GetNodes();
			//for (int i=0;i<nodes.size();i++){AddNode(nodes[i]);}

			for (int i=0;i<nodes.size();i++)
			{
				LaplacianMap::iterator info_it = m_Laplacian.find(nodes[i]);
				if (info_it == m_Laplacian.end())
				{
					LaplacianData data;
					if (i-1>=0){data.link.push_back(nodes[i-1]);}
					if (i+1< nodes.size()){data.link.push_back(nodes[i+1]);}
					m_Laplacian[nodes[i]] = data;
				}else{
					if (i-1>=0){info_it->second.link.push_back(nodes[i-1]);}
					if (i+1< nodes.size()){info_it->second.link.push_back(nodes[i+1]);}
				}
			}

			if (collinear)
			{
				CollinearData data;
				for (int i=0;i<node_idx.size();i++)
				{
					if(m_Nodes[node_idx[i]]->Main())data.nodes.push_back(m_Nodes[node_idx[i]]);
				}
				m_Collinear.push_back(data) ;
			}

			m_Skeletons.push_back(skeleton);
		}

		int Char::SelectNode( double x,double y )
		{
			double threshold = 50;
			double min_len = 9999999999999999;
			int target = -1;
			for (int i=0;i<m_Nodes.size();i++)
			{
				HSSSpline::PathPoint<2> posn = m_Nodes[i]->Position();
				double len = (posn[0]-x)*(posn[0]-x) + (posn[1]-y)*(posn[1]-y);
				if (len < threshold && len < min_len)
				{
					target = i;
					min_len = len;
				}
			}
			return target;
		}

		void Char::InitData()
		{
			for (LaplacianMap::iterator info_it = m_Laplacian.begin();info_it != m_Laplacian.end();info_it++)
			{
				HSSSpline::Vector2 v1(0,0);
				for (int i=0;i<info_it->second.link.size();i++)
				{
					HSSSpline::Vector2 posn = info_it->second.link[i]->Position_UV();
					v1[0] += posn[0]; 
					v1[1] += posn[1];
				}

				if (info_it->second.link.size() > 0)
				{
					v1[0] /= info_it->second.link.size();
					v1[1] /= info_it->second.link.size();
				}

				HSSSpline::Vector2 v0 = info_it->first->Position_UV();
				info_it->second.laplacian[0] = v1[0] - v0[0];
				info_it->second.laplacian[1] = v1[1] - v0[1];
			}

			//Collinear Constrain
			for (int i=0;i<m_Collinear.size();i++)
			{
				m_Collinear[i].laplacian.resize(m_Collinear[i].nodes.size());
				for (int n=0;n<m_Collinear[i].nodes.size();n++)
				{
					HSSSpline::Vector2 v0 = m_Collinear[i].nodes[n]->Position_UV();

					int k=0;
					HSSSpline::Vector2 v1;
					if (n-1>=0)
					{
						v1[0] += m_Collinear[i].nodes[n-1]->Position_UV()[0]; 
						v1[1] += m_Collinear[i].nodes[n-1]->Position_UV()[1];
						k++;
					}
					if (n+1<m_Collinear[i].nodes.size())
					{
						v1[0] += m_Collinear[i].nodes[n+1]->Position_UV()[0]; 
						v1[1] += m_Collinear[i].nodes[n+1]->Position_UV()[1];
						k++;
					}
					v1[0] /= k; v1[1] /= k;

					HSSSpline::Vector2 l;
					l[0] = v1[0] - v0[0]; l[1] = v1[1] - v0[1];
					m_Collinear[i].laplacian[n] = l;
				}
			}

			//Spacing Constrain
			for (int i=0;i<m_Spacing.size();i++)
			{
				m_Spacing[i].laplacian.resize(m_Spacing[i].nodes.size());
				for (int n=0;n<m_Spacing[i].nodes.size();n++)
				{
					HSSSpline::Vector2 v0 = m_Spacing[i].nodes[n]->Position_UV();

					int k=0;
					HSSSpline::Vector2 v1;
					if (n-1>=0)
					{
						v1[0] += m_Spacing[i].nodes[n-1]->Position_UV()[0]; 
						v1[1] += m_Spacing[i].nodes[n-1]->Position_UV()[1];
						k++;
					}
					if (n+1<m_Spacing[i].nodes.size())
					{
						v1[0] += m_Spacing[i].nodes[n+1]->Position_UV()[0]; 
						v1[1] += m_Spacing[i].nodes[n+1]->Position_UV()[1];
						k++;
					}
					v1[0] /= k; v1[1] /= k;

					HSSSpline::Vector2 l;
					l[0] = v1[0] - v0[0]; l[1] = v1[1] - v0[1];
					m_Spacing[i].laplacian[n] = l;
				}
			}

			//Skeleton Area
			m_SkeletonArea=0;
			for (int i=0;i<m_Skeletons.size();i++)
			{
				double area = m_Skeletons[i]->Width() * (m_Skeletons[i]->Height1()+m_Skeletons[i]->Height2());
				m_SkeletonArea += area;
			}
			if (m_Skeletons.size()!=0)m_SkeletonArea / (double)m_Skeletons.size();
		}

		void Char::Smoothing( Node_Targets& target )
		{
			std::vector<int> fix_u,fix_v;
			for (int i=0;i<m_Nodes.size();i++)
			{
				if(m_Nodes[i]->FixU()){fix_u.push_back(i);}
				if(m_Nodes[i]->FixV()){fix_v.push_back(i);}
			}

			int collinear_row=0;
			for (int i=0;i<m_Collinear.size();i++)
			{
				collinear_row+=m_Collinear[i].laplacian.size();
			}

			//Ax=B
			LinearSystemLib::GeneralSparseMatrix matrixAu;//Ax=B 的 A
			LinearSystemLib::GeneralSparseMatrix matrixAv;
			double** bu = new double*[1];//Ax=B 的 B
			double** bv = new double*[1];

			int row_u = m_Nodes.size()+target.size()+collinear_row+fix_u.size();
			int row_v = m_Nodes.size()+target.size()+collinear_row+fix_v.size();
			matrixAu.Create(row_u,m_Nodes.size());
			matrixAv.Create(row_v,m_Nodes.size());
			bu[0] = new double[row_u];
			bv[0] = new double[row_v];

			int current_row = 0;

			//Shape
			for (int i=0;i<m_Nodes.size();i++)
			{
				LaplacianData* data = &m_Laplacian[m_Nodes[i]];
				int n_size = data->link.size();

				double w = _Wsp*(double)m_Nodes[i]->Weight();
				if (m_Nodes[i]->Weight()>=1)w*=1.25;

				matrixAu.SetElement(i,i,-1*w);
				matrixAv.SetElement(i,i,-1*w);

				if (n_size>0)
				{
					double value = 1/(double)n_size *w;
					for (int n=0;n<data->link.size();n++)
					{
						int n_idx = data->link[n]->Index();
						matrixAu.SetElement(i,n_idx,value);
						matrixAv.SetElement(i,n_idx,value);
					}
				}

				bu[0][i] = data->laplacian[0]*w;
				bv[0][i] = data->laplacian[1]*w;
			}
			current_row+= m_Nodes.size();

			//Position
			for (int i=0;i<target.size();i++)
			{
				double node_idx = target[i].first;

				double w = target[i].second.w;
				matrixAu.SetElement(current_row+i,node_idx,w);
				matrixAv.SetElement(current_row+i,node_idx,w);

				HSSSpline::PathPoint<2> posn = m_Nodes[node_idx]->Position_UV();

				bu[0][current_row+i] = w*posn[0];
				bv[0][current_row+i] = w*posn[1];
			}
			current_row+= target.size();

			//Colliear
			int k=0;
			for (int i=0;i<m_Collinear.size();i++)
			{
				for (int n=1;n<m_Collinear[i].nodes.size()-1;n++)
				{
					double w = _Wst;
					
					matrixAu.SetElement(current_row+k,m_Collinear[i].nodes[n-1]->Index(),w*0.5);
					matrixAv.SetElement(current_row+k,m_Collinear[i].nodes[n-1]->Index(),w*0.5);
					matrixAu.SetElement(current_row+k,m_Collinear[i].nodes[n+1]->Index(),w*0.5);
					matrixAv.SetElement(current_row+k,m_Collinear[i].nodes[n+1]->Index(),w*0.5);

					matrixAu.SetElement(current_row+k,m_Collinear[i].nodes[n]->Index(),-1*w);
					matrixAv.SetElement(current_row+k,m_Collinear[i].nodes[n]->Index(),-1*w);

					bu[0][current_row+k] = m_Collinear[i].laplacian[n][0]*w;
					bv[0][current_row+k] = m_Collinear[i].laplacian[n][1]*w;

					k++;  
				}
			}
			current_row+= collinear_row;

			//Fix
			for (int i=0;i<fix_u.size();i++)
			{
				int node_idx = fix_u[i];
				matrixAu.SetElement(current_row+i,node_idx,_Wal);
				bu[0][current_row+i] = _Wal*m_Nodes[node_idx]->Position_UV()[0];
			}

			for (int i=0;i<fix_v.size();i++)
			{
				int node_idx = fix_v[i];
				matrixAv.SetElement(current_row+i,node_idx,_Wal);
				bv[0][current_row+i] = _Wal*m_Nodes[node_idx]->Position_UV()[1];
			}

			// solving it !! Ax = B.
			LinearSystemLib::SparseLinearSystem sls_u(new LinearSystemLib::StableSparseMatrix(matrixAu), bu, 1);
			LinearSystemLib::SparseLinearSystem sls_v(new LinearSystemLib::StableSparseMatrix(matrixAv), bv, 1);
			//-------------------------------------------------
			try
			{
				// the solution will be stored here.
				double** x_u = 0;
				double** x_v = 0;

				// solve it !!
				bool result_u = LinearSystemLib::LeastSquareSparseLSSolver::GetInstance()->Solve( &sls_u, x_u );
				bool result_v = LinearSystemLib::LeastSquareSparseLSSolver::GetInstance()->Solve( &sls_v, x_v );
				// output the solution..!!
				//-------------------------------------------------
				if( !(result_u && result_v))
					cerr << "solve error!!! check your matrix." << endl;
				else
				{
					for (int i=0;i<m_Nodes.size();i++)
					{
						m_Nodes[i]->Position_UV(x_u[0][i],x_v[0][i]);
					}
					Update();
				}

				// 須要自行 release solution memory, A，B 不用!!
				//-------------------------------------------------
				if (x_u!=0)
				{
					for( int i = 0 ; i < 1 ; ++i ){delete[] x_u[i];}
					delete[] x_u;
					x_u = NULL;
				}

				if (x_v!=0)
				{
					for( int i = 0 ; i < 1 ; ++i ){delete[] x_v[i];}
					delete[] x_v;
					x_v = NULL;
				}

				matrixAu.Free();
				matrixAv.Free();
			} 
			catch( exception e )
			{
				cerr << e.what() << endl;
			}
		}

		void Char::Editing( Node_Targets& target, double alpha)
		{
			if (target.empty())return;

			double w_l  = 10;
			double w_p  = alpha;
			double w_c  = 1;
			double w_f  = 10000000;

			std::vector<int> fix_u,fix_v;
			for (int i=0;i<m_Nodes.size();i++)
			{
				if (m_Nodes[i]->FixU()){fix_u.push_back(i);}
				if (m_Nodes[i]->FixV()){fix_v.push_back(i);}
			}

			int collinear_row=0;
			for (int i=0;i<m_Collinear.size();i++){collinear_row+=m_Collinear[i].laplacian.size();}

			int spacing_row=0;
			for (int i=0;i<m_Spacing.size();i++){spacing_row+=m_Spacing[i].laplacian.size();}

			//Ax=B
			LinearSystemLib::GeneralSparseMatrix matrixAu;//Ax=B 的 A
			LinearSystemLib::GeneralSparseMatrix matrixAv;
			double** bu = new double*[1];//Ax=B 的 B
			double** bv = new double*[1];

			int row_u = m_Nodes.size()+target.size()+collinear_row+spacing_row+fix_u.size();
			int row_v = m_Nodes.size()+target.size()+collinear_row+spacing_row+fix_v.size();
			matrixAu.Create(row_u,m_Nodes.size());
			matrixAv.Create(row_v,m_Nodes.size());
			bu[0] = new double[row_u];
			bv[0] = new double[row_v];

			int current_row = 0;

			//Shape 
			for (int i=0;i<m_Nodes.size();i++)
			{
				LaplacianData* data = &m_Laplacian[m_Nodes[i]];
				int n_size = data->link.size();

				double w = _Wsp*(double)m_Nodes[i]->Weight();
				matrixAu.SetElement(i,i,-1*w);
				matrixAv.SetElement(i,i,-1*w);

				if (n_size>0)
				{
					double value = 1/(double)n_size *w;
					for (int n=0;n<data->link.size();n++)
					{
						int n_idx = data->link[n]->Index();
						matrixAu.SetElement(i,n_idx,value);
						matrixAv.SetElement(i,n_idx,value);
					}
				}

				bu[0][i] = data->laplacian[0]*w;
				bv[0][i] = data->laplacian[1]*w;
			}
			current_row+= m_Nodes.size();

			//Position
			for (int i=0;i<target.size();i++)
			{
				double node_idx = target[i].first;

				double w = w_p*target[i].second.w;
				matrixAu.SetElement(current_row+i,node_idx,w);
				matrixAv.SetElement(current_row+i,node_idx,w);

				double u,v;
				m_StringLine->World2Local(target[i].second.posn[0],target[i].second.posn[1],&u,&v);

				bu[0][current_row+i] = w*u;
				bv[0][current_row+i] = w*v;
			}
			current_row+= target.size();

			//Collinear Constrain
			int k=0;
			for (int i=0;i<m_Collinear.size();i++)
			{
				for (int n=1;n<m_Collinear[i].nodes.size()-1;n++)
				{
					double w = 0.5*_Wst;
					matrixAu.SetElement(current_row+k,m_Collinear[i].nodes[n-1]->Index(),w*0.5);
					matrixAv.SetElement(current_row+k,m_Collinear[i].nodes[n-1]->Index(),w*0.5);
					matrixAu.SetElement(current_row+k,m_Collinear[i].nodes[n+1]->Index(),w*0.5);
					matrixAv.SetElement(current_row+k,m_Collinear[i].nodes[n+1]->Index(),w*0.5);

					matrixAu.SetElement(current_row+k,m_Collinear[i].nodes[n]->Index(),-1*w);
					matrixAv.SetElement(current_row+k,m_Collinear[i].nodes[n]->Index(),-1*w);

					bu[0][current_row+k] = m_Collinear[i].laplacian[n][0]*w;
					bv[0][current_row+k] = m_Collinear[i].laplacian[n][1]*w; 

					k++;
				}
			}
			current_row+= collinear_row;

			//Spacing Constrain
			k=0;
			for (int i=0;i<m_Spacing.size();i++)
			{
				for (int n=0;n<m_Spacing[i].nodes.size();n++)
				{
					double w = m_Spacing[i].w*_Wst;
					if (n==0)
					{
						matrixAu.SetElement(current_row+k,m_Spacing[i].nodes[n+1]->Index(),w);
						matrixAv.SetElement(current_row+k,m_Spacing[i].nodes[n+1]->Index(),w);
					}else if (n==m_Spacing[i].nodes.size()-1){
						matrixAu.SetElement(current_row+k,m_Spacing[i].nodes[n-1]->Index(),w);
						matrixAv.SetElement(current_row+k,m_Spacing[i].nodes[n-1]->Index(),w);
					}else{
						matrixAu.SetElement(current_row+k,m_Spacing[i].nodes[n-1]->Index(),w*0.5);
						matrixAv.SetElement(current_row+k,m_Spacing[i].nodes[n-1]->Index(),w*0.5);
						matrixAu.SetElement(current_row+k,m_Spacing[i].nodes[n+1]->Index(),w*0.5);
						matrixAv.SetElement(current_row+k,m_Spacing[i].nodes[n+1]->Index(),w*0.5);
					}

					matrixAu.SetElement(current_row+k,m_Spacing[i].nodes[n]->Index(),-1*w);
					matrixAv.SetElement(current_row+k,m_Spacing[i].nodes[n]->Index(),-1*w);

					bu[0][current_row+k] = m_Spacing[i].laplacian[n][0]*w;
					bv[0][current_row+k] = m_Spacing[i].laplacian[n][1]*w; 

					k++;
				}
			}
			current_row+= spacing_row;

			//Fix
			for (int i=0;i<fix_u.size();i++)
			{
				int node_idx = fix_u[i];
				matrixAu.SetElement(current_row+i,node_idx,_Wal);
				bu[0][current_row+i] = _Wal*m_Nodes[node_idx]->Position_UV()[0];
			}

			for (int i=0;i<fix_v.size();i++)
			{
				int node_idx = fix_v[i];
				matrixAv.SetElement(current_row+i,node_idx,_Wal);
				bv[0][current_row+i] = _Wal*m_Nodes[node_idx]->Position_UV()[1];
			}

			// solving it !! Ax = B.
			LinearSystemLib::SparseLinearSystem sls_u(new LinearSystemLib::StableSparseMatrix(matrixAu), bu, 1);
			LinearSystemLib::SparseLinearSystem sls_v(new LinearSystemLib::StableSparseMatrix(matrixAv), bv, 1);
			//-------------------------------------------------
			try
			{
				// the solution will be stored here.
				double** x_u = 0;
				double** x_v = 0;

				// solve it !!
				bool result_u = LinearSystemLib::LeastSquareSparseLSSolver::GetInstance()->Solve( &sls_u, x_u );
				bool result_v = LinearSystemLib::LeastSquareSparseLSSolver::GetInstance()->Solve( &sls_v, x_v );
				// output the solution..!!
				//-------------------------------------------------
				if( !(result_u && result_v)){
					cerr << "solve error!!! check your matrix." << endl;
				}else{
					for (int i=0;i<m_Nodes.size();i++){m_Nodes[i]->Position_UV(x_u[0][i],x_v[0][i]);}
					Update();
				}

				// 須要自行 release solution memory, A，B 不用!!
				//-------------------------------------------------
				if (x_u!=0)
				{
					for( int i = 0 ; i < 1 ; ++i ){delete[] x_u[i];}
					delete[] x_u;
					x_u = NULL;
				}

				if (x_v!=0)
				{
					for( int i = 0 ; i < 1 ; ++i ){delete[] x_v[i];}
					delete[] x_v;
					x_v = NULL;
				}

				matrixAu.Free();
				matrixAv.Free();
			} 
			catch( exception e ){cerr << e.what() << endl;}
		}

		void Char::BuildScaleChar(double scale)
		{
			for (int i = 0 ; i < m_Nodes.size() ; i++)
			{
				HSSSpline::PathPoint<2> p = m_Nodes[i]->Position_UV();				
				p[0] = p[0]*scale;
				cout<<p.ToString()<<endl;
				m_Nodes[i]->Position_UV(p[0],p[1]);
			}
			Update();
		}

		void Char::Update()
		{
			for (int i=0;i<m_Skeletons.size();i++){m_Skeletons[i]->Update();}
			CalBoundBox();
		}

		void Char::Draw( bool debug )
		{
			glColor3dv(m_Color);
			for (int i=0;i<m_Skeletons.size();i++){m_Skeletons[i]->DrawStroke();}
			if (debug)
			{
				glColor3d(0.8,0.8,0.8);
				for (int i=0;i<m_Skeletons.size();i++){m_Skeletons[i]->Draw();}
				DrawNodes();
				//DrawBoundingBox();
			}
		}

		void Char::DrawNodes()
		{
			glPointSize(3);
			
			for (int i=0;i<m_Nodes.size();i++)
			{
				if (m_Nodes[i]->Main()){glPointSize(5);}
				else glPointSize(2);

				double w = (double)m_Nodes[i]->Weight()*0.8;
				if (m_Nodes[i]->FixV()){
					glColor3d(w,w,1);
				}else{
					glColor3d(1,w,w);
				}
				HSSSpline::PathPoint<2> posn= m_Nodes[i]->Position();

				glBegin(GL_POINTS);
				glVertex2d(posn[0],posn[1]);
				glEnd();
			}
		}

		void Char::Release()
		{
			while (!m_Skeletons.empty())
			{
				QRSkeleton* skeleton = m_Skeletons.back();
				m_Skeletons.pop_back();
				delete skeleton;
				skeleton = NULL;
			}

			while (!m_Nodes.empty())
			{
				QRNode* node = m_Nodes.back();
				m_Nodes.pop_back();
				delete node;
				node = NULL;
			}

			m_Laplacian.clear();
			m_Collinear.clear();
			m_StringLine = NULL;
		}

		QRNodes Char::GetMainNodes()
		{
			QRNodes nodes;
			for (int i=0;i<m_Nodes.size();i++)
			{
				if(m_Nodes[i]->Main())nodes.push_back(m_Nodes[i]);
			}
			return nodes;
		}

		void Char::DrawSoild()
		{
			glColor3d(0.0,0.0,0.0);
			for (int i=0;i<m_Skeletons.size();i++){m_Skeletons[i]->DrawStroke();}
		}

		QRNodes Char::GetSkeletonMainNodes( int i )
		{
			QRNodes main;
			QRNodes nodes = m_Skeletons[i]->GetNodes();
			for (int n=0;n<nodes.size();n++)
			{
				if(nodes[n]->Main()){main.push_back(nodes[n]);}
			}
			return main;
		}

		void Char::AddSpacingConstrain(float w, std::vector<int> n_idxs )
		{
			SpacingData data;
			data.w = w;
			for (int i=0;i<n_idxs.size();i++)
			{
				int idx = n_idxs[i];
				data.nodes.push_back(m_Nodes[idx]);
			}
			m_Spacing.push_back(data);
		}

		void Char::CalBoundBox( )
		{
			m_BoundBox[0]	= -999999;
			m_BoundBox[1]	=  999999;
			m_BoundBox[2]	= -999999;
			m_BoundBox[3]	=  999999;
			m_BoundU[0]		= -999999;//Max U
			m_BoundU[1]		=  999999;//Min U

			for (int i=0;i<m_Skeletons.size();i++)
			{
				std::vector<HSSSpline::Vector2> stroke = m_Skeletons[i]->GetStoke();
				for (int j=0;j<stroke.size();j++)
				{
					if(stroke[j][0] > m_BoundBox[0]){m_BoundBox[0] = stroke[j][0];}
					if(stroke[j][0] < m_BoundBox[1]){m_BoundBox[1] = stroke[j][0];}
					if(stroke[j][1] > m_BoundBox[2]){m_BoundBox[2] = stroke[j][1];}
					if(stroke[j][1] < m_BoundBox[3]){m_BoundBox[3] = stroke[j][1];}

					double u,v;
					m_StringLine->World2Local(stroke[j][0],stroke[j][1],&u,&v);
					if(u > m_BoundU[0]){m_BoundU[0] = u;}
					if(u < m_BoundU[1]){m_BoundU[1] = u;}
				}
			}
			
		}

		void Char::GetBoundU( double* max_u,double* min_u)
		{
			if(max_u!=NULL)*max_u = m_BoundU[0]*m_StringLine->Lenght();
			if(min_u!=NULL)*min_u = m_BoundU[1]*m_StringLine->Lenght();
		}

		void Char::DrawBoundingBox()
		{
			glBegin(GL_QUADS);
			glVertex2d(m_BoundBox[0],m_BoundBox[2]);
			glVertex2d(m_BoundBox[0],m_BoundBox[3]);
			glVertex2d(m_BoundBox[1],m_BoundBox[3]);
			glVertex2d(m_BoundBox[1],m_BoundBox[2]);
			glEnd();
		}

		double Char::StructError()
		{
			double error_sp  = 0;
			for (LaplacianMap::iterator info_it = m_Laplacian.begin();info_it != m_Laplacian.end();info_it++)
			{
				HSSSpline::Vector2 v0 = info_it->first->Position_UV();
				HSSSpline::Vector2 v1(0,0);
				for (int i=0;i<info_it->second.link.size();i++)
				{
					HSSSpline::Vector2 posn = info_it->second.link[i]->Position_UV();
					v1[0] += posn[0]; 
					v1[1] += posn[1];
				}
				if (info_it->second.link.size() > 0)
				{
					v1[0] /= info_it->second.link.size();
					v1[1] /= info_it->second.link.size();
				}

				HSSSpline::Vector2 sigma1 = v1 - v0;
				HSSSpline::Vector2 sigma0 = info_it->second.laplacian;
				double err = (sigma0[0]-sigma1[0])*(sigma0[0]-sigma1[0]) + (sigma0[1]-sigma1[1])*(sigma0[1]-sigma1[1]);
				error_sp  += info_it->first->Weight()*err;
			}

			double error_st  = 0;
			for (int i=0;i<m_Collinear.size();i++)
			{
				for (int n=1;n<m_Collinear[i].nodes.size()-1;n++)
				{
					HSSSpline::Vector2 v0 = m_Collinear[i].nodes[n]->Position_UV();
					HSSSpline::Vector2 v1(0,0);
					int k=0;
					if (n-1>=0){
						v1[0] += m_Collinear[i].nodes[n-1]->Position_UV()[0]; 
						v1[1] += m_Collinear[i].nodes[n-1]->Position_UV()[1];
						k++;
					}

					if (n+1<m_Collinear[i].nodes.size()){
						v1[0] += m_Collinear[i].nodes[n+1]->Position_UV()[0]; 
						v1[1] += m_Collinear[i].nodes[n+1]->Position_UV()[1];
						k++;
					}
					v1[0] /= k; v1[1] /= k;

					HSSSpline::Vector2 sigma1 = v1 - v0;
					HSSSpline::Vector2 sigma0 =m_Collinear[i].laplacian[n];

					double err = (sigma0[0]-sigma1[0])*(sigma0[0]-sigma1[0]) + (sigma0[1]-sigma1[1])*(sigma0[1]-sigma1[1]);
					error_st += 0.5*err;
				}
			}
			
			for (int i=0;i<m_Spacing.size();i++)
			{
				for (int n=0;n<m_Spacing[i].nodes.size();n++)
				{
					HSSSpline::Vector2 v0 = m_Spacing[i].nodes[n]->Position_UV();
					HSSSpline::Vector2 v1(0,0);
					int k=0;
					if (n-1>=0)
					{
						v1[0] += m_Spacing[i].nodes[n-1]->Position_UV()[0]; 
						v1[1] += m_Spacing[i].nodes[n-1]->Position_UV()[1];
						k++;
					}
					if (n+1<m_Spacing[i].nodes.size())
					{
						v1[0] += m_Spacing[i].nodes[n+1]->Position_UV()[0]; 
						v1[1] += m_Spacing[i].nodes[n+1]->Position_UV()[1];
						k++;
					}
					v1[0] /= k; v1[1] /= k;

					HSSSpline::Vector2 sigma1 = v1 - v0;
					HSSSpline::Vector2 sigma0 =m_Spacing[i].laplacian[n];

					double err = (sigma0[0]-sigma1[0])*(sigma0[0]-sigma1[0]) + (sigma0[1]-sigma1[1])*(sigma0[1]-sigma1[1]);
					error_st += m_Spacing[i].w*err;
				}
			}

			return _Wsp*error_sp+_Wst*error_st;
		}

		double Char::AreaError()
		{
			double area=0;
			for (int i=0;i<m_Skeletons.size();i++){area += m_Skeletons[i]->Width() * (m_Skeletons[i]->Height1()+m_Skeletons[i]->Height2());}
			if (m_Skeletons.size()!=0)area / (double)m_Skeletons.size();
			return area - m_SkeletonArea;
		}

		std::vector<HSSSpline::Vector2> Char::GetAllNodesUV()
		{
			std::vector<HSSSpline::Vector2> uv;
			uv.resize(m_Nodes.size());
			for (int i=0;i<m_Nodes.size();i++){uv[i]=m_Nodes[i]->Position_UV();}
			return uv;
		}

		void Char::SetAllNodesUV( std::vector<HSSSpline::Vector2>& uv )
		{
			for (int i=0;i<m_Nodes.size();i++){m_Nodes[i]->Position_UV(uv[i][0],uv[i][1]);}
			Update();
		}

		std::vector<HSSSpline::Scale3> Char::GetAllFontWeight()
		{
			std::vector<HSSSpline::Scale3> temp_bold;
			temp_bold.resize(m_Skeletons.size());
			for (int sk_id = 0 ; sk_id<m_Skeletons.size(); sk_id++)
			{
				temp_bold[sk_id]=m_Skeletons[sk_id]->Bold();
			}
			return temp_bold;
		}

		void Char::SetAllFontWeight( std::vector<HSSSpline::Scale3>& bold )
		{
			for (int sk_id = 0 ; sk_id<m_Skeletons.size(); sk_id++){m_Skeletons[sk_id]->SetBold(bold[sk_id]);}
		}

		QRWordArt::QRCharacter::DeformationData Char::GetDeformationData()
		{
			DeformationData data;
			data.node_uv = GetAllNodesUV();
			data.skeleton_bold = GetAllFontWeight();
			return data;
		}

		void Char::SetDeformationData( DeformationData& data )
		{
			SetAllNodesUV(data.node_uv);
			SetAllFontWeight(data.skeleton_bold);
		}
	}
}