/**
* @file AppAlgoLineTrace.h
*
* Classes for tracing line on flow field
*
* @author
*/
#pragma once


#define	 DISCRETE_FILTER_SIZE	2048
#define  LOWPASS_FILTR_LENGTH	500000.0f
#define	 LINE_SQUARE_CLIP_MAX	100000.0f
#define	 VECTOR_COMPONENT_MIN   0.050000f 
#define  round(x) (x - floor(x) >= 0.5 ? floor(x) + 1 : floor(x))

typedef struct ChosenInfo
{
	vector<cv::Point2i> chosenlines;
	int line_order;
	int region;
	vector<float> usize;
	int lineid;
}ChosenInfo;

typedef struct LineData
{
	int region;
	int id;
	int order;
	int avg_color;
	double score[3];
	float _w;
	float avg_dis;
	int _len;
	vector<double> score_list;
	//int _cb;
	//int _cw;
	int be_chosen;//-1:bad line 0:not choose  1:choose
	vector<cv::Point2f> flow;
}LineData;

#ifndef _choseninfo
#define _choseninfo

#endif
namespace AppFrame 
{
	/**
	*	@brief Class for the base optimization interface
	*/
	public ref class AppAlgoStreamlineTrace : public HKCAlgorithm
	{
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		
		 AppAlgoStreamlineTrace():first_trace_done(false),line_trace_debug(false),line_trace_debug_id(0){}	
		~AppAlgoStreamlineTrace(void){}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Algorithm Operations						   */
		/*! \{                                                                 */	

		/// Perform 
		virtual bool Execute(HKCAppItem^ _appItem) override;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Access Methods                              */
		/*! \{                                                                 */

		virtual property System::String^ Abbrev
		{
			System::String^ get(void) override { return "Trace Line"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"Tracing line on flow field";
		}	
		/*! \}                                                                 */		

	private:
		//=================Tracing Lines=================//
		cv::Point3f AppAlgoStreamlineTrace::findnearest(vector<cv::Point2i>& trace_line,vector<cv::Point2f>& flow_map,cv::Point2i& trace_point);
		bool AppAlgoStreamlineTrace::TracingLines(cv::Mat& src_img, vector<cv::Point2f> flow_map, cv::Mat& segment_img,vector < vector<cv::Point2i > >& blobs, vector<vector<cv::Point2i>>& output_lines, vector<LineData>& lines_info,int r,int range_size);
		int AppAlgoStreamlineTrace::FlowImagingLIC(cv::Point2f start_posi, cv::Mat& src_img, vector<cv::Point2f>& flow_map,  vector<cv::Point2f>& repel_map,vector<cv::Point2i>& line, float krnlen, cv::Mat break_area_img,int range_size);
		void AppAlgoStreamlineTrace::checkseedcover(vector<cv::Point2f> &seed_array,vector<bool> &seed_orientation, cv::Mat& lineregionmask);
		//=================Smooth Lines=================//
		void AppAlgoStreamlineTrace::BuildStringLines_Unifromsize( ChosenInfo& chosen_infos, QRWordArt::QRStringLines& splines );
		
		//=================choose good lines (¿ï¾Ünum_lines_chosen±ø)=================//
		float AppAlgoStreamlineTrace::ChooseGoodLinesR(vector<vector<cv::Point2i>>& line, vector<LineData>& lines_info, cv::Mat& lines_range_mask,cv::Mat& edge_map,QRWordArt::QRStringLines& Edgesplines,QRWordArt::QRStringLines& splines,vector<ChosenInfo>& chosen_infos,int range_size);
		bool AppAlgoStreamlineTrace::checkAcrossLine(std::vector<cv::Point2i>& line,LineData& line_info,cv::Mat& lines_range_mask,cv::Mat& edge_map,QRWordArt::QRStringLines& Edgesplines, vector<ChosenInfo>& chosen_infos,int range_size);
		void AppAlgoStreamlineTrace::smoothsize(vector<float> & linesize, double fit_rate);
		void AppAlgoStreamlineTrace::updatelines(vector<vector<cv::Point2i>>& lines,vector<LineData>& lines_info);
		
		float AppAlgoStreamlineTrace::checkCoverRatio(cv::Mat& src1,cv::Mat& src2);		
		bool AppAlgoStreamlineTrace::traverse_tangent(QRWordArt::QRStringLine* Edgespline, cv::Point2f& pnt, cv::Point2f& tangent,int range_size);
		bool AppAlgoStreamlineTrace::SortLineOrder( vector<ChosenInfo>& chosen_infos,QRWordArt::QRStringLines& splines);

		static bool  line_sort(ChosenInfo& line1, ChosenInfo& line2);
		static bool nline_sort(cv::Point3d& score1, cv::Point3d& score2);
		static bool int_sort(int i,int j);
	private:	
		vector<vector<ChosenInfo>>* regions_chosen_infos;
		static int img_width;
		static int img_height;

		double BoundaryRepela;
		double BoundaryRepelb;
		double LineRepela;
		double LineRepelb;

		bool   smallregion;
		double string_space;
		
		bool first_trace_done;
		//Debug
		bool line_trace_debug;
		int line_trace_debug_id;
	};
}
