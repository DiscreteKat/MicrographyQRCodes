#pragma once

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"


namespace AppFrame 
{
	public ref class AppAlgoTextWarping : public HKCAlgorithm
	{

		
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		
		AppAlgoTextWarping(void){}
		virtual ~AppAlgoTextWarping(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Algorithm Operations						   */
		/*! \{                                                                 */	

		virtual bool Execute(HKCAppItem^ _appItem) override;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Access Methods                              */
		/*! \{                                                                 */

		virtual property System::String^ Abbrev
		{
			System::String^ get(void) override { return "Spline Width Adjustment"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"Spline Width Adjustment";
		}	
		
	private:
		void AdjustSplines(QRWordArt::QRStringLines& splines,cv::Mat& segment_img);
		
		void drawallsplines(QRWordArt::QRStringLine* spline, cv::Mat& mask,int img_width,int img_height);
		int checkcoverneighbor(cv::Mat allmasks,cv::Mat mask);

		int img_width;
		int img_height;
	};
}