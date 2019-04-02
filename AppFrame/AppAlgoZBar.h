/**
* @file AppAlgoZBar.h
*
* Classes for ZBar verification
*
* @author James Hung-Kuo Chu
*/

#pragma once

namespace AppFrame 
{
	/**
	*	@brief Class for the ZBar Grid Sampling
	*/
	public class HKCZBarGridSampling
	{
		/*==========================  PUBLIC  =================================*/
	public:		                                                            
		HKCZBarGridSampling(void)  {}						
		~HKCZBarGridSampling(void) {}		

		bool Execute_Detect( HKCAppItem^ item,cv::Mat src);

		cv::Mat GetErrorImg(){return m_ErrorImg;}
		std::vector<bool> GetMError(){return m_Module_Error;}
		std::vector<std::vector<bool>> GetCWError(){return m_CW_Error;}

		int N_ErrorModule(){return m_Num_Error_Module;};
		std::vector<int> N_ErrorCW(){return m_Num_Error_CW;}

		std::vector<std::string>& QRContent(){return m_QR_Content;}
	protected:
		cv::Mat           m_ErrorImg;
		std::vector<bool> m_Module_Error;
		std::vector<std::vector<bool>> m_CW_Error;

		int              m_Num_Error_Module;
		std::vector<int> m_Num_Error_CW;

		std::vector<std::string> m_QR_Content;
	};
}