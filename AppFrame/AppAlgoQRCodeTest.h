#pragma once

#pragma once

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"

namespace AppFrame 
{
	/**
	*	@brief Class for the base optimization interface
	*/
	public ref class AppAlgoQRCodeTest : public HKCAlgorithm
	{
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~AppAlgoQRCodeTest(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Algorithm Operations						   */
		/*! \{                                                                 */	

		/// Perform
		virtual bool Execute(HKCAppItem^ _appItem) override;
		bool Execute2(HKCAppItem^ _appItem);
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Access Methods                              */
		/*! \{                                                                 */

		virtual property System::String^ Abbrev
		{
			System::String^ get(void) override { return "QR Code Test"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"QR Code Test";
		}	

	private:
		std::vector<int> RandomModule(int num);
		void DrawModule_Ring(cv::Point& posn, int color, int out_size,int in_size,cv::Mat* dst);
		void DrawModule_RI(cv::Point& posn, int color, int size, int r, cv::Mat* dst);
		void DrawModule_I(cv::Point& posn, int color, int size,cv::Mat* dst);

		double CalThreshold(int target,std::vector<double>& cw_prob);
		double CalThreshold(int target,std::vector<double>& cw_prob,double head,double tail,int iter);
		void CreateTestingData(HKCQRCData& qrcData,int pSize,int iSize,int num_module,int num_pixel,cv::Mat& test1,cv::Mat& test2);

		cv::Mat addGaussianNoise( cv::Mat &matI, int mean, int stddev );
		cv::Mat addSaltAndPepperNoise( cv::Mat &matI, int lowerBound, int upperBound );

		std::vector<int> SortCWModule( std::vector<int>& module_idx,std::vector<double>& module_energy );


	};
}