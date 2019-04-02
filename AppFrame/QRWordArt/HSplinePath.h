#pragma once
#include "HSSSplineSample.h"
#include "HSplineCore.h"

namespace HSSSpline
{
	class HSplinePath: public HSplineCore<5>//x,y,w,t,b
	{
	protected:
		PathPoints<5>		m_Piecewise_Points;//原始輸入點
		PathPoints<5>		m_Ctrl_Points;     //控制點
		std::vector<double> m_SegLenght;
	public:
		int BuildingSpline(PathPoints<5> &_points);

		void Clean(){m_Piecewise_Points().clear();}

		void PushBack(PathPoint<5>& point_info);
		void PushBack(PathPoint<2>& posn);

		void AssignPoints(PathPoints<5>& points);
		PathPoints<5> GetPiecewisePoints(){return m_Piecewise_Points;}

		const PathPoint<5>& GetCtrlPoint(int idx){return m_Ctrl_Points[idx];}
		PathPoints<5>       GetCtrlPoints(){return m_Ctrl_Points;}
		virtual void	 AssignCtrlPoints(PathPoints<5>& ctrl_points);
		void			 AugmentCtrlPoint(int num);

		PathPoint<5> Begin(){return m_Ctrl_Points().front();}
		PathPoint<5> End(){return m_Ctrl_Points().back();}
	//GetInfo
	public:
		/*取得spline上的某一點位置, seg是哪一段, t是參數*/
		PathPoint<2> get_position(int _seg, double _t);
		PathPoint<2> get_position(const Sample& sample){return get_position(sample.seg_idx,sample._t);}
		/*取得spline上的某一點切線, seg是哪一段, t是參數*/
		PathPoint<2> get_tangent(int _seg, double _t);
		PathPoint<2> get_tangent(const Sample& sample){return get_tangent(sample.seg_idx,sample._t);}
		/*取得spline上的某一點法向量, seg是哪一段, t是參數*/
		PathPoint<2> get_normal(int _seg, double _t);
		PathPoint<2> get_normal(const Sample& sample){return get_normal(sample.seg_idx,sample._t);}
		/*取得spline上的某一點scale, seg是哪一段, t是參數*/
		PathPoint<3> get_size(int _seg, double _t);
		PathPoint<3> get_size(const Sample& sample){return get_size(sample.seg_idx,sample._t);}

		PathPoint<5> get_midpoint();

		/*取座標分量*/
		double get_x(int _seg, double _t){return get_value(0,_seg,_t);}
		double get_x(const Sample& sample){return get_x(sample.seg_idx,sample._t);}
		double get_y(int _seg, double _t){return get_value(1,_seg,_t);}
		double get_y(const Sample& sample){return get_y(sample.seg_idx,sample._t);}
		double get_w(int _seg, double _t){return get_value(2,_seg,_t);}
		double get_w(const Sample& sample){return get_w(sample.seg_idx,sample._t);}
		double get_top(int _seg, double _t){return get_value(3,_seg,_t);}
		double get_top(const Sample& sample){return get_top(sample.seg_idx,sample._t);}
		double get_bottom(int _seg, double _t){return get_value(4,_seg,_t);}
		double get_bottom(const Sample& sample){return get_bottom(sample.seg_idx,sample._t);}

	//Editting
	public:
		virtual void ScaleSpline(double scale);

		double  SelectCtrlPoint(double x,double y,int *select);//回傳最短距離，Select為選到的點
		//編輯Ctrl Point位置
		virtual void EditCtrlPoint(int c_id,PathPoint<2>& point);
		//編輯Ctrl Point位置
		virtual void TranslateCtrlPoint(int c_id,PathPoint<2>& point);
		//編輯Ctrl Point位置
		virtual void TranslateAllCtrlPoint(PathPoint<2>& point);
		//編輯Sample Point位置
		virtual void EditSamplePoint(Sample& sample,PathPoint<2>& point);
		//編輯Ctrl Point大小
		virtual void EditCtrlPointSize(int c_id,PathPoint<3>& size);
		//編輯所有Ctrl Point大小
		virtual void EditAllCtrlPointSize(PathPoint<3>& size);
		//編輯Ctrl Point大小，並內插其他點
		virtual void SoftEditCtrlPointSize(int c_id,PathPoint<3>& size);
		//編輯Sample Point大小
		virtual void EditSamplePointSize(const Sample& sample,PathPoint<3>& size);
		//編輯所有Ctrl Point大小
		virtual void Scale(double scale);
		//編輯所有point 大小
		virtual void EditAllPointSize( bool plus );
		virtual void EditAllPointPosition( int flag, double amount=0.1 );
		virtual void EditAllPointPosition( HSSSpline::Vector2& vect );
	//Sampling
	public:
		//從pixel取樣 
		void    FittingCurve(double fit_ratio,bool auto_adjust = true);//   1 / Fit Ratio = 區段數
		//從目前curve取樣
		void    RefittingCurve(double fit_ratio);

		Samples        UniformSampling(double per_len);
		PathPoints<5>  GetUniformSamplePoints(double per_len);
	//長度計算
	public:
		double Lenght();
		double BeginToSampleLenght(const Sample& s);
		double SampleToEndLenght(const Sample& s);
		double Lenght(const Sample& s0,const Sample& s1);
	protected:
		double SegLenght(int seg_idx);
		double SegToSampleLenght(const Sample& sample);

	//Shift
	public:
		bool ShiftSample(Sample& from,double offset,Sample*  output);
		bool ShiftSampleForeward(Sample& from,double offset,Sample*  output);
		bool ShiftSampleBackward(Sample& from,double offset,Sample*  output);

	public:
		Sample World2Local(double x,double y,double* u,double* v);
		Sample Local2World(double u,double v,double* x,double* y);
		Sample GetSample(double u);
	//Rendering
	public:
		void DrawLine();
		void DrawLine(Sample& from,Sample& to);
		void DrawStroke();
		void DrawStroke(Sample& from,Sample& to);
 		void DrawCapLine();
 		void DrawCapLine(Sample& from,Sample& to);
 		void DrawBaseLine();
 		void DrawBaseLine(Sample& from,Sample& to);
		void DrawCtrlPoint();
	};
}