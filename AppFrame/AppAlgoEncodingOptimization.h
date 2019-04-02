#pragma once

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"

#include "AppAlgoEncodingRSModify.h"

namespace AppFrame 
{
	/**
	*	@brief Class for the base optimization interface
	*/
	public ref class AppAlgoEncodingOptimization : public HKCAlgorithm
	{
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~AppAlgoEncodingOptimization(void) {}		

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
			System::String^ get(void) override { return "AppAlgoQRCodeOp"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"AppAlgoQRCodeOp";
		}	

		/*! \}                                                                 */
		/*=========================  PRIVATE  ===============================*/
	private:
		std::vector<int> SelectModules(cv::Mat& mask,HKCQRCData& qrcData,std::vector<double>& module_energy,AppAlgoRSModify& app_rsmodify);
		void QRCodeMasking(HKCQRCData& qrcData,cv::Mat& mask,std::vector<int>& bit);
		void SortModules(std::vector<double>& module_energy,std::vector<int>& targets/*Output*/);

		//Debug Using
		void BitFlagImg(HKCQRCData& qrcData, AppAlgoRSModify& app_rsmodify);
		void BitFlagImg2(HKCQRCData& qrcData, AppAlgoRSModify& app_rsmodify,std::vector<int> select,std::vector<double>& energy);
	};
}