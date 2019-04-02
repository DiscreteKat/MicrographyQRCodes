/**
* @file AppAlgoTextGeneration.h
*
* Classes for generating text on mesh
*
* @author 
*/
#pragma once
namespace AppFrame 
{
	/**
	*	@brief Class for the base optimization interface
	*/
	
	public ref class AppAlgoRegionSeg : public HKCAlgorithm
	{
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		
		AppAlgoRegionSeg(void){}
		virtual ~AppAlgoRegionSeg(void) {}		

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
			System::String^ get(void) override { return " Text Generation"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"Region Segmentation";
		}
	private:
		void FindBlobs(const cv::Mat &binary, std::vector < std::vector<cv::Point2i> > &blobs);
		void BuildEdgeLines(VecEdgeLink* vecEdgeLink,QRWordArt::QRStringLines& edgesplines);
	};
}
