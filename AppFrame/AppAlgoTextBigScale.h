#pragma once

struct YJFID
{
	int nl;//Ctrl Point 區段
	int nw;//內差參數 0~1
	int nt;
	int startline;
	int endline;
	cv::Mat word_mask;
	vector<int> word_order;
	YJFID(int l,int w ,int t)
	{
		nl=l;
		nw=w;
		nt=t;
		setline();
	}
	YJFID(int l,int w ,int t,cv::Mat mask)
	{
		nl=l;
		nw=w;
		nt=t;
		word_mask=mask;
		setline();
	}
	void setline()
	{
		switch(nt)
		{
		case 0:
			startline=nl-1;
			endline=nl;
			break;
		case 1:
			startline=nl;
			endline=nl+1;
			break;
		case 2:
			startline=nl-1;
			endline=nl+1;
			break;
		case 3:
			startline=nl;
			endline=nl+2;
			break;
		case 4:
			startline=nl-2;
			endline=nl;
			break;
		}
	}
};
namespace AppFrame 
{
	/**
	*	@brief Class for the base optimization interface
	*/
	using namespace  QRWordArt;
	public class AppAlgoTextBigScale
	{
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~AppAlgoTextBigScale(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Algorithm Operations						   */
		/*! \{                                                                 */	

		bool Execute(HKCAppItem^ _appItem);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Access Methods                              */
		/*! \{                                                                 */

		
		bool AppAlgoTextBigScale::BuildBigScale(QRStringLines& splines	,cv::Mat& word_mask);
		bool AppAlgoTextBigScale::GenUserBigScale(HKCAppItem^ _appItem,int line,int word);
		bool AppAlgoTextBigScale::GenBigScale(HKCAppItem^ _appItem,int randcount);
	private:
		double AppAlgoTextBigScale::calcQRenergy(HKCAppItem^ _appItem,vector<double>& orienergys,cv::Mat &allmask ,cv::Mat &word_mask);
 		bool AppFrame::AppAlgoTextBigScale::CheckOverlap( QRStringLine::QRSamples& string_data1,QRStringLine::QRSamples& string_data2 );
 		bool AppFrame::AppAlgoTextBigScale::CheckOverEdge( QRStringLine::QRSamples& string_data1,cv::Mat break_area_img );
 		bool AppFrame::AppAlgoTextBigScale::DeleteCovered(QRWordArt::QRStringLines & splines,QRWordArt::QRStringLine::QRSamples& word_data);
 		bool AppFrame::AppAlgoTextBigScale::ReTextGen(QRStringLines& splines,HKCAppItem^ _appItem,vector<YJFID>& id_picked,vector<int>& line_word_order);
		float AppAlgoTextBigScale::checkCoverRatio(cv::Mat& segment,QRWordArt::QRStringLines & splines,bool check_big);
		void AppAlgoTextBigScale::drawallsplines(QRStringLines& splines, cv::Mat& allmask,int bg_color,cv::Mat& foreground,cv::Mat& background);
		void AppAlgoTextBigScale::sortwordarray(QRStringLines& splines,vector<std::string>& strings,vector<vector<cv::Point>>& wordarray);
		void AppAlgoTextBigScale::setidx(int i,int j,int k){nspline=i;nword=j;nsizetype=k;}
		void AppAlgoTextBigScale::setori(int num){ori_num=num;}
		void AppAlgoTextBigScale::setflag(bool checkoverlap,bool checkroveredge){m_checkoverlap=checkoverlap;m_checkroveredge=checkroveredge;}

		HSSSpline::PathPoints<5> getallpoint(QRWordArt::QRStringLine* spline,double step =0.05);
		HSSSpline::PathPoint<5>  findnearest(HSSSpline::PathPoints<5>& line,HSSSpline::PathPoint<5>trace_point,int id);
	private:
		static bool candidate_sort(RegionCandidateData can1, RegionCandidateData can2);
		static bool sort_island(YJFID id1, YJFID id2);
	private:	
		cv::Mat *edgeImg;
		vector<cv::Point3i>* delete_idx;
		vector<QRWordArt::QRCharacter::Char*>* delete_charsample;
		int newsplineId;
		int img_width;
		int img_height;
		int nspline;
		int nsizetype;//0 向上兩倍 1向下兩倍 2三倍
		int nword;
		bool m_checkoverlap;
		bool m_checkroveredge;
		int ori_num;
		int island_num;
		int error_num;
	};
}
