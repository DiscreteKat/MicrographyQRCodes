/**
* @file AppAlgoETF.h
*
* Classes for generation of edge tangent flow
*
* @author Elaine Cheng-Li Hsieh
*/
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
	public ref class AppAlgoDoETF : public HKCAlgorithm
	{
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~AppAlgoDoETF(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Algorithm Operations						   */
		/*! \{                                                                 */	

		/// Perform ETF
		virtual bool Execute(HKCAppItem^ _appItem) override;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Access Methods                              */
		/*! \{                                                                 */

		virtual property System::String^ Abbrev
		{
			System::String^ get(void) override { return "DoETF"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"edge tangent flow";
		}	

		/*! \}                                                                 */
		/*=========================  PRIVATE  ===============================*/
	private:	
		void AppAlgoDoETF::SetTangent(  int img_height,
						int img_width,
						std::vector<float>& update_Tx,
						std::vector<float>& update_Ty,
						std::vector<float>& _Tx,
						std::vector<float>& _Ty,
						std::vector<float>& _magnitude);
		void AppAlgoDoETF::DoETF(int iteration/*=3*/,
					 int size/*=3*/,
					 int img_height,
					 int img_width,
					 std::vector<float>& _Tx,
					 std::vector<float>& _Ty, 
					 std::vector<float>& _magnitude);
		void AppAlgoDoETF::NormalizVectrs(int img_height,
						  int img_width,
						  std::vector<float>& _Tx,
						  std::vector<float>& _Ty);
		void AppAlgoDoETF::printflow(	int img_height,
						int img_width,
						std::vector<float>& _Tx,
						std::vector<float>& _Ty 
						);
	};
}