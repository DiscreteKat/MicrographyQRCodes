#pragma once

#include "AppProperty.h"
#include "AppParameter.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppAlgorithm.h"

#include "QRWordARt/QRCharacter.h"
#include "QRWordARt/QRStringLine.h"
#include "QRWordArt/QRCharFBO.h"
/**
*	@brief Class for 
*/
public class AppAlgoModuleSelection
{
	public:
		typedef std::map<QRWordArt::QRCharacter::Char*,std::vector<int>> CM_Map;
	private:
		HKCQRCData* m_QRcode;
		cv::Mat m_Module_map;
		double m_ImgW;
		double m_ImgH;
	public:				
		AppAlgoModuleSelection(HKCAppItem^ _appItem);
		virtual ~AppAlgoModuleSelection(void) {}

		int SelectModule(cv::Point2f& target);
		std::vector<int> SelectModule(cv::Mat& target);
		std::vector<int> SelectModule_Voting(cv::Mat& target,int range);
		
		//不同於背景色 分配到最近的Char
		//相同於背景色 分配到在範圍內的Char
		CM_Map CharModuleMapping(std::vector<int> pids, HKCQRCData* qrcode, int bg_color, QRWordArt::QRStringLines& strings);

	private:
		QRWordArt::QRCharacter::VecChar CharInRange(cv::Point posn,double range,QRWordArt::QRStringLines& strings);	
		double NearestNode(QRWordArt::QRCharacter::QRNodes& nodes,cv::Point2d qr_posn,double threhold,int* index);
};
