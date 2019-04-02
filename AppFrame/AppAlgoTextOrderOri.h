#pragma once

#pragma once

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"
#include "QRWordArt/QRStringLine.h"
#include "QRWordArt/QRSplineFBO.h"

namespace AppFrame 
{

	struct LineGraph{
		vector<int> upid;
		vector<int> downid;
		bool check ;
		int id;
		LineGraph()
		{
			check=false;
		}
	};
	typedef std::vector< LineGraph > LineGraphs;
	public ref class AppAlgoTextOrderOri : public HKCAlgorithm
	{
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~AppAlgoTextOrderOri(void) {}		

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
			System::String^ get(void) override { return "Spline order"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"Spline order";
		}	

	private:
		LineGraphs getneighbor(QRWordArt::QRStringLines& splines,cv::Mat& segment);
		LineGraphs BottomUpCheck(LineGraphs& graph);
		bool PushVer(LineGraphs& graph,int id,LineGraphs& newgraph);
		vector<int> *queue;
		int img_width;
		int img_height;
	};
}