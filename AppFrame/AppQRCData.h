#pragma once
#include <opencv/cv.h>
#include <vector>
#include "QREncode/qrBitData.h"

namespace AppFrame
{	
	/**
	*	@brief Class for the QR code module
	*/
	class HKCModule
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                    Constructors                              */
		/*! \{                                                                 */

		HKCModule(void) { Clear(); }		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */

		~HKCModule(void) { Clear(); }

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                      Methods                                 */
		/*! \{                                                                 */

		/// Clear data
		void Clear(void) 
		{	
			Type = -1;
			Pos = cv::Point(0,0);
			QRC = -1;
			RSID = -1;
			CWID = -1;	
			abandon      = false;
		}		

		/*! \}                                                                 */
		/*==========================  PUBLIC  =================================*/
	public:	
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */

		/// 0:Codewords
		/// 1:Remaining Bits
		/// 2:Version Information
		/// 3:Format Information 
		/// 4:Alignment Patterns
		/// 5:Timing Patterns
		/// 6:Separators and Position Detection Patterns
		int         Type;   ///< Type of module

		cv::Point   Pos;	///< Module's position		
		int         QRC;	///< QR code value (1: black, 0: white)

		int	    RSID;	///< RS block ID (1-based index, -1 indicates non data module)
		int	    CWID;	///< Codeword ID in the RS block (1-based index, -1 indicates non data module)

		bool        abandon;
		/*! \}                                                                 */
	};
	/// type define for the vector of QR code module
	typedef std::vector<HKCModule*> VecMdu;

	/**
	*	@brief Class for the image patch data
	*/
	class HKCPatchData
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                    Constructors                              */
		/*! \{                                                                 */

		HKCPatchData(void) { Clear(); }		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */

		~HKCPatchData(void) { Clear(); }

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                      Methods                                 */
		/*! \{                                                                 */

		/// Clear data
		void Clear(void) 
		{	
			qr_color     = -1;
			patch_Pos       = cv::Point(0,0);
			grid_sample_Pos = cv::Point(0,0);
		}		

		/*! \}                                                                 */
		/*==========================  PUBLIC  =================================*/
	public:	
		/*---------------------------------------------------------------------*/
		/*! \name						Data	       */
		/*! \{     
		*/
		int			qr_color;      //QRCode Color
		cv::Point	patch_Pos;	   // 左上角
		cv::Point	grid_sample_Pos; // 中心點
	};
	/// type define for the vector of QR code module
	typedef std::vector<HKCPatchData*> VecPatch;

	class QRCW
	{
	public:
		std::vector<int> module_idx;
		QRCW(){}
	};

	class QRRSCode
	{
	public:
		std::vector<QRCW> cw_data;
		int max_error;
		QRRSCode():max_error(0){}

		int   size(){return cw_data.size();}
		QRCW& operator[](int idx){return cw_data[idx];}
	};
	typedef std::vector<QRRSCode> QRCWData;//QRCWData[RS][CW]

	/**
	*	@brief Class for the QR code data
	*/
	class HKCQRCData
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                    Constructors                              */
		/*! \{                                                                 */

		HKCQRCData(void) { Clear(); }		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */

		~HKCQRCData(void) { Clear(); }

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                      Methods                                 */
		/*! \{                                                                 */

		/// Clear data
		void Clear(void) 
		{	
			isReady = false;
			Text = "";
			Ver = -1;
			ECL = -1;
			ECC = -1;						
			QRCode.release();
			QRCImg.release();
			QuietZone.release();

			offset=cv::Point2d(0,0);
			//Free_VecPtr(Modules);
			//Free_VecPtr(Patches);

			module_size      =  9;
			center_size      = module_size/3;
			cw_error_thershold     = 0.466382021;
			cw_error_thershold_std = 0.121311436;
			cw_error_thershold_confidence = -1;
			recover_stop_point = 0;

			RSMap.release();
			CWMap.release();

			QRMask = -1;
		}		

		/*! \}                                                                 */
		/*==========================  PUBLIC  =================================*/
	public:	
		/*---------------------------------------------------------------------*/
		/*! \name						Data		                           */
		/*! \{                                                                 */
		cv::Point2d     offset;
		bool			isReady;	///< Flag indicates if the data is ready
		std::string		Text;		///< Encoded text string
		int				Ver;		///< QR code version (5, 10)
		int				ECL;		///< Error correction level
		int				ECC;		///< Error correction capacity	
		int				RSNum;
		int				RSBNum[2];
		int				RSBcwNum[2];
		int				RSBdcNum[2];
		int				RSBecNum[2];
		int				QRMask;

		QRBitData		QRCBitData;

		cv::Mat			QRCode;		///< Original QR code (8UC1)
		cv::Mat			QRCImg;		///< Upsample version QR code image (8UC1)
		cv::Mat			QuietZone;

		VecMdu			Modules;	///< QR code modules	
		VecPatch        Patches;    ///< image patch
		QRCWData		CWData;

		int module_size;
		int center_size;
		double cw_error_thershold;
		double cw_error_thershold_std;
		double cw_error_thershold_confidence;
		double recover_stop_point;

		//std::vector<int> max_error;

		//Debug Use
		cv::Mat			RSMap;		///< RS block map  (CV_32SC1, 1-based index and value -1 indicates non-used pixel)
		cv::Mat			CWMap;		///< Code word map (CV_32SC1, 1-based index and value -1 indicates non-used pixel)	
		cv::Mat			CWContour;
		cv::Mat         RSModify;
		/*! \}                                                                 */
	};
}