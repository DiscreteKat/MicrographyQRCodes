/**
* @file AppAlgoGenLayerData.h
*
* Classes for generating layer images of result
*
* @author Elaine Cheng-Li Hsieh
*/
#pragma once

namespace AppFrame 
{
	/**
	*	@brief Class for generating layer images
	*/
	public ref class AppAlgoQRCodeSegmentation : public HKCAlgorithm
	{
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~AppAlgoQRCodeSegmentation(void) {}		

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
			System::String^ get(void) override { return "Layer image"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"generating layer images";
		}	

		void SegmentQRCode(HKCAppItem^ _appItem);
		static std::vector<int> SegmentQRCode(cv::Mat& segment_img,HKCQRCData& qrcData,int module_size);
	private:
		void    GapAbandon(cv::Mat& gap,int bg_color, HKCQRCData& qrcData);
		void    GapAbandonCW(HKCQRCData& qrcData);
		cv::Mat GenBackground(int style,cv::Mat& segment_img,cv::Mat& gap,HKCQRCData& qrcData, int wa, int da, std::vector<int>& seg_pids);
	};
}