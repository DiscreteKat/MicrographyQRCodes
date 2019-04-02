#pragma once
#include "QRNode.h"
#include "QRSkeleton.h"
#include <map>

namespace QRWordArt
{
	namespace QRCharacter
	{
		struct TargetData{
			double w;
			HSSSpline::Vector2 posn;
			TargetData():w(1),posn(HSSSpline::Vector2(0,0)){}

			void operator =(const TargetData& in)
			{
				w = in.w;
				posn[0] = in.posn.val[0];
				posn[1] = in.posn.val[1];
			}
		};
		typedef std::pair<int,TargetData> Node_Target;
		typedef std::vector<Node_Target>  Node_Targets;

		struct DeformationData{
			std::vector<HSSSpline::Vector2> node_uv;
			std::vector<HSSSpline::Scale3>  skeleton_bold;
		};
		typedef std::vector<DeformationData>  DeformationDatas;

		class Char
		{
		private:
			static double _Wsp;
			static double _Wst;
			static double _Wal;
		private:
			struct LaplacianData{
				QRNodes link;
				HSSSpline::Vector2 laplacian;
			};
			typedef std::map<QRNode*,LaplacianData> LaplacianMap;

			struct CollinearData{
				QRNodes nodes;
				std::vector<HSSSpline::Vector2> laplacian;
			};
			typedef std::vector<CollinearData> Collinears;

			struct SpacingData{
				float w;
				QRNodes nodes;
				std::vector<HSSSpline::Vector2> laplacian;
			};
			typedef std::vector<SpacingData> Spacings;

			HSSSpline::HSplinePath* m_StringLine;

			const char     m_Char;
			QRNodes        m_Nodes;
			QRSkeletons    m_Skeletons;

			LaplacianMap	m_Laplacian;
			Collinears		m_Collinear;
			Spacings		m_Spacing;

			double m_SkeletonArea;
			double m_Color[3];
			double m_BoundBox[4];
			double m_BoundU[2];
		public:
			Char(char c);
			~Char(void);

			char GetChar(){return m_Char;}
			void Release();

			void BindStringLine(HSSSpline::HSplinePath* spline){m_StringLine = spline;}
			HSSSpline::HSplinePath* StringLine(){return m_StringLine;}

			void Update();
		public:
			void AddNode(QRNode* node);
			int SelectNode(double x,double y);
			int NodeSize(){return m_Nodes.size();}
			QRNode* Node(int idx){return m_Nodes[idx];}
			QRNodes GetMainNodes();
			QRNodes GetNodes(){return m_Nodes;}

			void CreateSkeleton(std::vector<int>& node_idx, HSSSpline::Sample& sample, bool fix_v, bool collinear,double w, double h1, double h2);
			void AddSpacingConstrain(float w, std::vector<int> nodes);

			void AddSkeleton(QRSkeleton* skeleton);
			int			SkeletonSize(){return m_Skeletons.size();}
			QRSkeleton* Skeleton(int i){return m_Skeletons[i];}

			QRNodes GetSkeletonMainNodes(int i);
			double* GetBoundBox(){return m_BoundBox;}

			void CalBoundBox();
			void GetBoundU(double* max_u,double* min_u);
			void InitData();//≠p∫‚Laplacian

			std::vector<HSSSpline::Vector2> GetAllNodesUV();
			void SetAllNodesUV(std::vector<HSSSpline::Vector2>& uv);
			std::vector<HSSSpline::Scale3> GetAllFontWeight();
			void SetAllFontWeight(std::vector<HSSSpline::Scale3>& bold);

			DeformationData GetDeformationData();
			void SetDeformationData(DeformationData& data);
		public:
			void SetColor(double  r,double  g,double  b){m_Color[0]=r;m_Color[1]=g;m_Color[2]=b;}
			void GetColor(double *r,double *g,double *b){*r=m_Color[0];*g=m_Color[1];*b=m_Color[2];}

			void Draw(bool debug);

			void DrawSoild();
			void DrawNodes();
			void DrawBoundingBox();
		public:
			void Smoothing(Node_Targets& target);
			void Editing(Node_Targets& target,double alpha);
			void BuildScaleChar(double scale);

			double StructError();
			double AreaError();
		};
		typedef std::vector<Char*> VecChar;
	}
}