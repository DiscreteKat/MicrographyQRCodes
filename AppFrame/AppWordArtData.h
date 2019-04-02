#pragma once
#include "QRWordArt/QRStringLine.h"
#include "QRWordArt/QRPattern.h"
#include <vector>

#define BG_STYLE_QRCODE			1
#define BG_STYLE_BLEND			2
#define BG_STYLE_BLEND_WITH_GAP	3
#define BG_STYLE_MODULE			4
#define BG_STYLE_WORDART		5
struct BoldWarpBG
{
	BoldWarpBG(int s,int c,cv::Scalar _scalar){SplineID=s; CharID=c; scalar=_scalar;}
	int SplineID;
	int CharID;
	cv::Scalar scalar;
};

typedef struct RegionParam
{
	bool smallregion;
	int RangeSize;
	double Boundary_Repela;
	double Line_Repela;
	double Boundary_Repelb;
	double Line_Repelb;
}RegionParam;

typedef struct RegionCandidateData
{
	QRWordArt::QRStringLines splines;
	int scaling_number;
	double Et;
	double Es;
	double Ec;
	double Em;
}RegionCandidateData;

class YJFCanData
{
	/*==========================  PUBLIC  =================================*/
public:		
	/*---------------------------------------------------------------------*/
	/*! \name                    Constructors                              */
	/*! \{                                                                 */

	YJFCanData(void) { Clear(); }		

	/*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                     Destructor                               */
	/*! \{                                                                 */

	~YJFCanData(void) { Clear(); }

	/// Clear data
	void Clear(void) 
	{	
		candidates.clear();
	}

	RegionCandidateData			user_candidate;
	vector<RegionCandidateData> candidates;
};

class HKCWordArtEvi//環境
{
	/*==========================  PUBLIC  =================================*/
public:		
	/*---------------------------------------------------------------------*/
	/*! \name                    Constructors                              */
	/*! \{                                                                 */

	HKCWordArtEvi(void) { Clear(); }	
	/*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                     Destructor                               */
	/*! \{                                                                 */

	~HKCWordArtEvi(void) { Clear(); }

	/*! \}                                                                 */
	/*---------------------------------------------------------------------*/		
	/*! \name                      Methods                                 */
	/*! \{                                                                 */

	/// Clear data
	void Clear(void) 
	{	
		flow_map.clear();		
		segment_img.release();
		gap_img.release();

		region_segs.clear();
		region_img.release();
		region_points.clear();
		region_splines.clear();

		background_style = BG_STYLE_MODULE;
		background_color = -1;
	}		

	/*! \}                                                                 */
	/*==========================  PUBLIC  =================================*/
public:	
	/*---------------------------------------------------------------------*/
	/*! \name						Data		                           */
	/*! \{                                                                 */
	
	cv::Mat				segment_img;
	cv::Mat				gap_img;
	vector<cv::Point2f>	flow_map;           //流向資訊

	vector<std::string>				candidate_strings;	//User Input 文字資料

	int								region_num;
	vector<cv::Mat>					region_segs;
	vector<vector<cv::Point2i>>		region_points;
	cv::Mat							region_img;
	vector<RegionParam>				region_params;
	vector<RegionCandidateData>		region_splines;

	int background_style;
	int background_color;//0:black  255:white
	//QRCode Segmentation
	std::vector<int> seg_pids;
	cv::Mat	 qr_background_modules;	 //Background Modules
	cv::Mat  qr_foreground_modules;	 //Foreground Modules
	cv::Mat  qr_InfTime_modules;
	QRWordArt::QRStringLines	edge_splines;
	HKCV::VecEdgeLink*			vecEdgeLink;

	//Evaluation，可刪除
	cv::Mat	 module_energy_map;
	cv::Mat	 codeword_error_map;
	cv::Mat  zbar_error_map;
	cv::Mat  zxing_error_map;
	cv::Mat  qr_seg_modules;	
	/*! \}																	*/
};

class HKCWordArtEdt//編輯控制項
{
	/*==========================  PUBLIC  =================================*/
public:		
	/*---------------------------------------------------------------------*/
	/*! \name                    Constructors                              */
	/*! \{                                                                 */

	HKCWordArtEdt(void) { Clear(); }	
	/*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                     Destructor                               */
	/*! \{                                                                 */

	~HKCWordArtEdt(void) { Clear(); }

	/*! \}                                                                 */
	/*---------------------------------------------------------------------*/		
	/*! \name                      Methods                                 */
	/*! \{                                                                 */

	/// Clear data
	void Clear(void) 
	{	
		OrdEditingMode = false;
		TextbaseEditingMode =false;
		StringLineEditingMode=false;
		ScalingEditingMode=false;
		is_scaling = false;
		Boldwarp=false;
		points.clear();
		ClearSelect();
		CanData.Clear();
		boldwarpBG.clear();
	}	

	void ClearSelect(){
		select_region = -1;
		select=-1;
		select_word=-1;
		select_ctrlpoint=-1;
		select_record=-1;
		select_char=-1;
		selectcolor=cv::Point3d(-1,-1,-1);
		point_record=cv::Point2d(-1,-1);
	}
	/*==========================  PUBLIC  =================================*/
public:	
	/*---------------------------------------------------------------------*/
	/*! \name						Data		                           */

	//Editting information
	int select; //spline
	int select_ctrlpoint;	
	int select_char;
	int select_word;
	int select_record;
	cv::Point3d selectcolor;
	int select_region;
	cv::Point2d point_record;

	bool is_scaling;
	bool StringLineEditingMode;
	bool ScalingEditingMode;
	bool OrdEditingMode;
	bool TextbaseEditingMode;
	bool Boldwarp;//temp use
	vector<BoldWarpBG> boldwarpBG;
	vector<int> adjust_spline_id;
	//Word Art Generation
	QRWordArt::QRStringLines temp_splines; //紀錄上一步用

	QRWordArt::QRStringLines user_splines; //user增加的spline
	HSSSpline::PathPoints<5> points; 

	YJFCanData  CanData;
};

class HKCWordArtData
{
	/*==========================  PUBLIC  =================================*/
public:		
	/*---------------------------------------------------------------------*/
	/*! \name                    Constructors                              */
	/*! \{                                                                 */

	HKCWordArtData(void) { Clear(); }	
	/*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                     Destructor                               */
	/*! \{                                                                 */

	~HKCWordArtData(void) { Clear(); }

	/*! \}                                                                 */
	/*---------------------------------------------------------------------*/		
	/*! \name                      Methods                                 */
	/*! \{                                                                 */

	/// Clear data
	void Clear(void) 
	{	
		ClearSplines();

		naive_combine.release();
		naive_blending.release();
		pattern_blending.clear();
		//pixel_blending.release();
	}	

	void ClearSplines(void) 
	{	
		while(!splines.empty())
		{
			QRWordArt::QRStringLine* spline = splines.back();
			spline->Release();
			delete spline;
			splines.pop_back();
		}
		splines.clear();
	}	

	void CopyStreamline(HKCWordArtData& data){
		this->Clear();
		this->splines.resize(data.splines.size());
		for (int i=0;i<data.splines.size();i++){this->splines[i] = data.splines[i]->Clone();}
		this->naive_combine    = cv::Mat(data.naive_combine.cols,data.naive_combine.rows, CV_8UC4,cv::Scalar(0,0,0,0));
		this->naive_blending   = cv::Mat(data.naive_combine.cols,data.naive_combine.rows, CV_8UC4,cv::Scalar(0,0,0,0));
		//this->pixel_blending   = cv::Mat(data.pixel_blending.cols,data.pixel_blending.rows, CV_8UC4,cv::Scalar(0,0,0,0));
		//this->qr_recover_back_modules  = cv::Mat(data.qr_recover_back_modules.cols,data.qr_recover_back_modules.rows, CV_8UC4,cv::Scalar(0,0,0,0));
	}

	/*! \}                                                                 */
	/*==========================  PUBLIC  =================================*/
public:	
	/*---------------------------------------------------------------------*/
	/*! \name						Data		                           */
	/*! \{ */
	QRWordArt::QRStringLines splines;

	cv::Mat					naive_combine;		//NC
	cv::Mat					naive_blending;		//NB
	QRWordArt::QRPatterns	pattern_blending;	//PB
	cv::Mat					pixel_blending;		//Optimization
};