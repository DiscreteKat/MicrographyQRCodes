#include "StdAfx.h"
#include "Form1.h"
#include "QRWordArt/QRWordArtIO.h"

#include "AppAlgoQRCodeSegmentation.h"
#include "AppAlgoQRCodeBGColor.h"

#include "AppAlgoEncodingOptimization.h"
#include "AppAlgoMGStreamlineWarping.h"
#include "AppAlgoMGWarpingOptimization.h"
#include "AppAlgoModuleBlending.h"

#include "AppAlgoQRCodeTest.h"
#include "AppAlgoQRCodeEvaluation.h"
#include "AppAlgoQRCodeRenderer.h"

void Form1::MQRC_Action(System::String^ _action)
{
	if(System::String::Compare("PRE_PROCESS", _action) == 0)//建QRCode Info
	{
		if (!mp_AppItem->Data->QRCData.isReady){return;}
		cv::Mat& segment_img = mp_AppItem->Data->WordArtEvi.segment_img;
		if(segment_img.rows==0 || segment_img.cols==0){return;}

		cv::Mat& qrcimg = mp_AppItem->Data->QRCData.QRCImg;
		//=========================================================
		printf("Preprocess Data...\n");
		//-----------------------------
		// Background QRCode Color
		//-----------------------------
		MQRC_Action("BACKGROUNDCOLOR");

		//HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
		
		cv::Mat& qr_background = mp_AppItem->Data->WordArtEvi.qr_background_modules;
		cv::Mat& qr_foreground = mp_AppItem->Data->WordArtEvi.qr_foreground_modules;
		cv::Mat& qr_InfTime = mp_AppItem->Data->WordArtEvi.qr_InfTime_modules;
		qr_foreground = cv::Mat(qrcimg.cols,qrcimg.rows, CV_8UC4,cv::Scalar(0,0,0,0));
		qr_background = cv::Mat(qrcimg.cols,qrcimg.rows, CV_8UC4,cv::Scalar(0,0,0,0));
		qr_InfTime = cv::Mat(qrcimg.cols,qrcimg.rows, CV_8UC4,cv::Scalar(0,0,0,0));
		for (int i=0;i<mp_AppItem->Data->WordArtData.size();i++)
		{
			mp_AppItem->Data->WordArtData[i].naive_combine   = cv::Mat(qrcimg.cols,qrcimg.rows, CV_8UC4,cv::Scalar(0,0,0,0));
			mp_AppItem->Data->WordArtData[i].naive_blending  = cv::Mat(qrcimg.cols,qrcimg.rows, CV_8UC4,cv::Scalar(0,0,0,0));
			mp_AppItem->Data->WordArtData[i].pixel_blending  = cv::Mat(qrcimg.cols,qrcimg.rows, CV_8UC4,cv::Scalar(0,0,0,0));
		}

	}else if (System::String::Compare("BACKGROUNDCOLOR", _action) == 0) {
		HKCAlgorithm^ algoObj_QRBGColor = gcnew AppAlgoQRCBGColor;
		algoObj_QRBGColor->Execute(mp_AppItem);
		std::cout << "Background Color: " << mp_AppItem->Data->WordArtEvi.background_color << std::endl;
	}else if (System::String::Compare("SUPERIMPOSING", _action) == 0){
		printf("Superimposing...\n");
		AppAlgoQRCodeSegmentation^ algoObj_Superimposing = gcnew AppAlgoQRCodeSegmentation;
		algoObj_Superimposing->SegmentQRCode(mp_AppItem);
		algoObj_Superimposing->Execute(mp_AppItem);
	
	}else if(System::String::Compare("PROCESSALL", _action) == 0){
		if (!mp_AppItem->Data->QRCData.isReady){std::cout<<"Error: No QRcode Data"<<std::endl; return;}
		if ( mp_AppItem->Data->WordArtData[0].splines.empty()){std::cout<<"Error: No Word Art Data"<<std::endl; return;}

		MQRC_Action("SUPERIMPOSING");

		HKCAlgorithm^ algoObj_QRCodeOp			= gcnew AppAlgoEncodingOptimization;
		HKCAlgorithm^ algoObj_QRCodeSeg			= gcnew AppAlgoQRCodeSegmentation;
		HKCAlgorithm^ algoObj_SplineWrapping	= gcnew AppAlgoStreamlineWarping;
		HKCAlgorithm^ algoObj_CharWarping		= gcnew AppAlgoWarpingOptimization;

		AppAlgoModuleBlending algoObj_InfoRecover;
		AppAlgoQRCodeEvaluation algoObj_Evaluation;

		//初始化Spline，結果存在WordArtData[1]
		std::vector<HKCWordArtData>& word_data = mp_AppItem->Data->WordArtData;
		mp_AppItem->Data->CurrentWordArtID = 1;//切換ID
		word_data[1].CopyStreamline(word_data[0]);

		

		//-----------------------
		// RS Code Modification
		//-----------------------
		clock_t t1, t2;
		t1 = clock();
		if (mp_AppItem->Data->IO_Handle.rs_control && !mp_AppItem->Data->IO_Handle.rs_done)//***僅做一次
		{
			algoObj_QRCodeOp ->Execute(mp_AppItem);
			algoObj_QRCodeSeg->Execute(mp_AppItem);//重生前景背景
			mp_AppItem->Data->IO_Handle.rs_done = true;
			UpdateQRCode();
		}
		/**Log
		t2 = clock();
		printf("Cost Time: %lf min\n\n", (t2 - t1) / (double)((CLOCKS_PER_SEC) * 60));
		//**/

		//----------------------
		// Spline Wrapping
		//-----------------------
		if (mp_AppItem->Data->IO_Handle.sw_control){algoObj_SplineWrapping->Execute(mp_AppItem);}

		//-----------------------
		// Warping Optimization
		//-----------------------
		//**Log
		t1 = clock();
		//**/
		if (mp_AppItem->Data->IO_Handle.cw_control)
		{
			AppAlgoWarpingOptimization::SetLabelType(GC_LABEL_ALL);
			algoObj_CharWarping->Execute(mp_AppItem);
		}
		/**Log
		t2 = clock();
		printf("Cost Time: %lf min\n\n", (t2 - t1) / (double)((CLOCKS_PER_SEC)*60));
		//**/

		/**Log
		algoObj_Evaluation.EnableVisualEnergy(false);
		algoObj_Evaluation.EnableScanner(false);
		algoObj_Evaluation.Execute(mp_AppItem);
		//**/

		/**Log
		double em = algoObj_Evaluation.QRcodeQuality();
		double i = algoObj_Evaluation.IslandRatio();
		**/
		
		//--------------------
		// Module Blending
		//--------------------
		if(mp_AppItem->Data->IO_Handle.im_control){algoObj_InfoRecover.Execute(mp_AppItem);}

		//-----------------------
		// Evaluation
		//-----------------------
		t2 = clock();
		algoObj_Evaluation.EnableVisualEnergy(true);
		algoObj_Evaluation.EnableScanner(true);
		algoObj_Evaluation.Execute(mp_AppItem);
		printf("Cost Time: %lf sec\n", (t2 - t1) / (double)(CLOCKS_PER_SEC));
		std::cout << "============================" << std::endl;
		/**Log
		double q = algoObj_Evaluation.VisuleQuality();
		
		HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
		std::string filepath = MarshalString(srcItem->Prop->FilePath);
		char buff[500];
		int ec_level = mp_AppItem->Data->QRCData.ECL;
		if (ec_level==0)sprintf(buff,"%s\\EV0.csv",filepath);
		else if (ec_level==1)sprintf(buff,"%s\\EV1.csv",filepath);
		else if (ec_level==2)sprintf(buff,"%s\\EV2.csv",filepath);
		else if (ec_level==3)sprintf(buff,"%s\\EV3.csv",filepath);
		ofstream file;
		file.open(buff);

		file<<"Visual Quality,Pm,Island(before),Time"<<"\n";
		file<<q<<","<<em<<","<<i<<","<<(t2-t1)/(double)(CLOCKS_PER_SEC)<<"\n";
		file.close();
		**/

		//Update View
		SeeLevelCheck1->Checked = true;
		SeeLevelCheck2->Checked = true;
		SeeLevelCheck3->Checked = false;
		UpdateMQRCLayers(false);

		FlashWindow(FindWindow(NULL, TEXT("Application") ),true);

	}else if (System::String::Compare("EVALUATION", _action) == 0){
		AppAlgoQRCodeEvaluation algoObj_Evaluation;
		algoObj_Evaluation.EnableVisualEnergy(true);
		algoObj_Evaluation.EnableScanner(true);
		algoObj_Evaluation.Execute(mp_AppItem);		// Evaluation
		algoObj_Evaluation.SaveFile("EV.csv");

		SeeLevelCheck1->Checked = true;
		SeeLevelCheck2->Checked = true;
		SeeLevelCheck3->Checked = true;
		UpdateMQRCLayers(false);
	}else if (System::String::Compare("BATCH", _action) == 0){

		if (!mp_AppItem->Data->QRCData.isReady){cout<<"Error: No QRcode Data"<<endl; return;}
		if (mp_AppItem->Data->WordArtData[0].splines.empty()){cout<<"Error: No Word Art Data"<<endl; return;}

		//QRCode Error Correction
		HKCAlgorithm^ algoObj_EncodeOptimization= gcnew AppAlgoEncodingOptimization;
		HKCAlgorithm^ algoObj_QRCodeLayering	= gcnew AppAlgoQRCodeSegmentation;
		HKCAlgorithm^ algoObj_Warping			= gcnew AppAlgoWarpingOptimization;
		//HKCAlgorithm^ algoObj_ModuleBlend		= gcnew AppAlgoModuleBlending;
		AppAlgoQRCodeEvaluation algoObj_Evaluation;

		//首輪
		{
			//-----------------------
			// RS Code Modification
			//-----------------------
			if (!mp_AppItem->Data->IO_Handle.rs_done)//***僅做一次
			{
				algoObj_EncodeOptimization->Execute(mp_AppItem);
				algoObj_QRCodeLayering->Execute(mp_AppItem);
				mp_AppItem->Data->IO_Handle.rs_done = true;
			}
// 			//--------------------
// 			// Island
// 			//--------------------
// 			algoObj_InfoRecover->Execute(mp_AppItem);
// 			//-----------------------
// 			// Evaluation
// 			//-----------------------
// 			algoObj_Evaluation.EnableVisualEnergy(true);
// 			algoObj_Evaluation.EnableScanner(true);
// 			algoObj_Evaluation.Execute(mp_AppItem);
// 			algoObj_Evaluation.SaveFile("EV-1.csv");
		}
		

		std::vector<HKCWordArtData>& word_data = mp_AppItem->Data->WordArtData;
		double lambda_value[] = {5,10,15,20,25,30,35,40,45,50,55,60,65,70};
		int wa_idx=1;
//		for (wa_idx=1;wa_idx<4;wa_idx++)
		for(int idx_l=0;idx_l<14;idx_l++)
		{
			mp_AppItem->Data->CurrentWordArtID = wa_idx;
			word_data[wa_idx].CopyStreamline(word_data[0]);

			//-----------------------
			// Character Warping
			//-----------------------
// 			if      (wa_idx==1){AppAlgoWarpingOptimization::SetLabelType(GC_LABEL_S);}
// 			else if (wa_idx==2){AppAlgoWarpingOptimization::SetLabelType(GC_LABEL_B);}
// 			else if (wa_idx==3){AppAlgoWarpingOptimization::SetLabelType(GC_LABEL_SB);}
			AppAlgoWarpingOptimization::SetLabelType(GC_LABEL_ALL);
			mp_AppItem->Param->Optimization->Lambda	= lambda_value[idx_l];
			algoObj_Warping->Execute(mp_AppItem);
			//-----------------------
			// Evaluation
			//-----------------------
			algoObj_Evaluation.EnableVisualEnergy(true);
			algoObj_Evaluation.EnableScanner(false);
			algoObj_Evaluation.Execute(mp_AppItem);

			char buff[100];
			sprintf(buff,"EV-L%.lf-1.csv",lambda_value[idx_l]);
			algoObj_Evaluation.SaveFile(buff);
			//--------------------
			// Island
			//--------------------
//			algoObj_ModuleBlend->Execute(mp_AppItem);
			//-----------------------
			// Evaluation
			//-----------------------
			algoObj_Evaluation.EnableVisualEnergy(true);
			algoObj_Evaluation.EnableScanner(false);
			algoObj_Evaluation.Execute(mp_AppItem);

			char buff2[100];
			sprintf(buff2,"EV-L%.lf-2.csv",lambda_value[idx_l]);
			algoObj_Evaluation.SaveFile(buff2);
		}
		SeeLevelCheck1->Checked = true;
		SeeLevelCheck2->Checked = true;
		SeeLevelCheck3->Checked = false;
		UpdateMQRCLayers(false);
	}else if (System::String::Compare("TEST", _action) == 0){
		std::cout << "TEST" << std::endl;
		AppAlgoQRCodeTest^ algoObj_Test	= gcnew AppAlgoQRCodeTest;
		//algoObj_Test->Execute(mp_AppItem);
		algoObj_Test->Execute2(mp_AppItem);
	}
}

void Form1::UpdateQRCode()
{
	HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
	cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());

	cv::Point2d offset = mp_AppItem->Data->QRCData.offset;
	cv::Mat& qrcimg =mp_AppItem->Data->QRCData.QRCImg;
	cv::Rect clipping(offset.x,offset.y,qrcimg.cols,qrcimg.rows);

	HKCMediaItem^ wordartItem;
	HKCImageProp^ wordartProp;

	if(mp_AppItem->Find("QRCode"))
	{
		wordartItem = mp_AppItem->Find("QRCode");

		cv::Mat qrc(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0));
		cv::Mat temp;
		cv::cvtColor(mp_AppItem->Data->QRCData.QRCImg,temp,CV_GRAY2BGRA);
		temp.copyTo(qrc(clipping));	
		HKCMedia* media = new HKCImage(qrc);	
		wordartItem->Update(media);
		wordartProp = (HKCImageProp^)wordartItem->Prop;
		wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
		wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
	}
}

void Form1::UpdateMQRCLayers(bool all)
{
	HKCMediaItem^ srcItem = mp_AppItem->Find("Source");
	cv::Mat* srcImg = (cv::Mat*)(srcItem->Media->Data());

	cv::Point2d offset = mp_AppItem->Data->QRCData.offset;
	cv::Mat& qrcimg =mp_AppItem->Data->QRCData.QRCImg;
	cv::Rect clipping(offset.x,offset.y,qrcimg.cols,qrcimg.rows);

	HKCWordArtEvi&  wordart_evi = mp_AppItem->Data->WordArtEvi;
	int word_art_idx =  mp_AppItem->Data->CurrentWordArtID;
	HKCWordArtData& wordart_data = mp_AppItem->Data->WordArtData[word_art_idx];

	HKCMediaItem^ wordartItem;
	HKCImageProp^ wordartProp;

	if(!mp_AppItem->Find("Background"))
	{
		cv::Mat back = cv::Mat(srcImg->cols,srcImg->rows,CV_8UC1,cv::Scalar(mp_AppItem->Data->WordArtEvi.background_color));
		wordartItem = mp_AppItem->New(back,"Background", mp_GLPanel);//background_image
	}else{
		wordartItem = mp_AppItem->Find("Background");
		if (all) {
			cv::Mat back = cv::Mat(srcImg->cols, srcImg->rows, CV_8UC1, cv::Scalar(mp_AppItem->Data->WordArtEvi.background_color));
			HKCMedia* media = new HKCImage(back);
			wordartItem->Update(media);
		}
	}
	wordartProp = (HKCImageProp^)wordartItem->Prop;
	wordartProp->Render->Visible = SeeLevelCheck1->Checked||SeeLevelCheck2->Checked;


	/*//Energy
	if(mp_AppItem->Find("Energy"))
	{
		wordartItem     = mp_AppItem->Find("Energy");
		cv::Mat map(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)) ;
		wordart_evi.module_energy_map.CWContour.copyTo(map(clipping));
		HKCMedia* media = new HKCImage(map);
		wordartItem->Update(media);
	}else{
		cv::Mat map(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)) ;
		wordart_evi.module_energy_map.CWContour.copyTo(map(clipping));
		wordartItem = mp_AppItem->New(map, "Energy", mp_GLPanel);//Evaluation [Debug Use]	
	}
	wordartProp = (HKCImageProp^)wordartItem->Prop;
	wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
	wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
	wordartProp->Render->Visible = SeeLevelCheck3->Checked;

	if(mp_AppItem->Find("CW Contour"))
	{
		wordartItem     = mp_AppItem->Find("CW Contour");
	}else{
		cv::Mat map(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)) ;
		mp_AppItem->Data->QRCData.CWContour.copyTo(map(clipping));	
		wordartItem = mp_AppItem->New(map, "CW Contour", mp_GLPanel);//Evaluation [Debug Use]
	}
	wordartProp = (HKCImageProp^)wordartItem->Prop;
	wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
	wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
	wordartProp->Render->Visible = SeeLevelCheck3->Checked;
	//**/

	if(!mp_AppItem->Find("Quiet Zone"))
	{
		cv::Mat map = mp_AppItem->Data->QRCData.QuietZone.clone();
		for (int i=0;i<map.cols;i++){
			for (int j=0;j<map.rows;j++)
			{
				if (map.data[(i*map.rows+j)*4+3]!=0){map.data[(i*map.rows+j)*4+3]=255;}
			}
		}
		wordartItem = mp_AppItem->New(map,"Quiet Zone", mp_GLPanel);
	}else{wordartItem = mp_AppItem->Find("Quiet Zone");}
	wordartProp = (HKCImageProp^)wordartItem->Prop;
	wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
	wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
	wordartProp->Render->Visible = SeeLevelCheck1->Checked;

	if(mp_AppItem->Find("Background Modules"))
	{
		wordartItem = mp_AppItem->Find("Background Modules");
		cv::Mat map(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)) ;
		wordart_evi.qr_background_modules.copyTo(map(clipping));
		HKCMedia* media = new HKCImage(map);	
		wordartItem->Update(media);
	}else{
		wordartItem = mp_AppItem->Find("Background Modules");
		cv::Mat map(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)) ;
		wordart_evi.qr_background_modules.copyTo(map(clipping));	
		wordartItem = mp_AppItem->New(map, "Background Modules", mp_GLPanel);//background_image
	}
	wordartProp = (HKCImageProp^)wordartItem->Prop;
	wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
	wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
	wordartProp->Render->Visible = SeeLevelCheck1->Checked;

	//Line
	if(!mp_AppItem->Find("Editing")){
		wordartItem = mp_AppItem->New(cv::Mat(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)), "Editing", mp_GLPanel);
	}else{wordartItem = mp_AppItem->Find("Editing");}
	wordartProp = (HKCImageProp^)wordartItem->Prop;
	wordartProp->Render->Visible = false;

	/*//Debug RS
	wordartItem = mp_AppItem->New( mp_AppItem->Data->QRCData.RSModify, "RS", mp_GLPanel);
	wordartProp = (HKCImageProp^)wordartItem->Prop;
	wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
	wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
	//*/

// 	if (!mp_AppItem->Find("BoldWarpingTest"))
// 	{		
// 		cv::Mat transparent = cv::Mat(((cv::Mat*)srcItem->Media->Data())->cols,((cv::Mat*)srcItem->Media->Data())->rows,CV_8UC4,cv::Scalar(0,0,0,0));
// 		wordartItem = mp_AppItem->New(transparent, "BoldWarpingTest", mp_GLPanel);//Line [Debug Use]
// 		wordartProp = (HKCImageProp^)wordartItem->Prop;
// 		wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
// 		wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
// 		wordartProp->Render->Visible = false;
// 	}

	//Word Art
	if(!mp_AppItem->Find("Word Art")){wordartItem = mp_AppItem->New(cv::Mat(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)), "Word Art", mp_GLPanel);}
	else{wordartItem = mp_AppItem->Find("Word Art");}
	wordartProp = (HKCImageProp^)wordartItem->Prop;
	wordartProp->Render->Visible = SeeLevelCheck2->Checked;

	//Pattern
	if(!mp_AppItem->Find("Pattern")){
		wordartItem = mp_AppItem->New(cv::Mat(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)), "Pattern", mp_GLPanel);	
	}else{wordartItem = mp_AppItem->Find("Pattern");}
	wordartProp = (HKCImageProp^)wordartItem->Prop;
	wordartProp->Render->Visible = SeeLevelCheck1->Checked;

	//NC
 	if(mp_AppItem->Find("NC"))
 	{
 		wordartItem     = mp_AppItem->Find("NC");
 		cv::Mat map(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)) ;
 		wordart_data.naive_combine.copyTo(map(clipping));	
		HKCMedia* media = new HKCImage(map);	
		wordartItem->Update(media);
 	}else{
		cv::Mat map(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)) ;
		wordart_data.naive_combine.copyTo(map(clipping));	
 		wordartItem = mp_AppItem->New(map,"NC", mp_GLPanel);
 	}
 	wordartProp = (HKCImageProp^)wordartItem->Prop;
 	wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
 	wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
 	wordartProp->Render->Visible = false;

	//NB
 	if(mp_AppItem->Find("NB"))
 	{
		wordartItem     = mp_AppItem->Find("NB");
		cv::Mat map(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)) ;
		wordart_data.naive_blending.copyTo(map(clipping));	
		HKCMedia* media = new HKCImage(map);	
		wordartItem->Update(media);
 	}else{
		cv::Mat map(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)) ;
		wordart_data.naive_blending.copyTo(map(clipping));	
		wordartItem = mp_AppItem->New(map,"NB", mp_GLPanel);
 	}
 	wordartProp = (HKCImageProp^)wordartItem->Prop;
 	wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
 	wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
 	wordartProp->Render->Visible = false;

// 	if(mp_AppItem->Find("Source Image Outside"))
// 	{
// 		wordartItem = mp_AppItem->Find("Source Image Outside");
// 		cv::Mat SrcImgOut;
// 		cv::cvtColor(*srcImg,SrcImgOut,CV_BGR2BGRA);
// 		SrcImgOut(clipping).setTo(cv::Scalar(0,0,0,0));
// 		HKCMedia* media = new HKCImage(SrcImgOut);
// 		wordartItem->Update(media);
// 	}else{
// 		wordartItem = mp_AppItem->New(wordart_evi.qr_foreground_modules, "Source Image Outside", mp_GLPanel);//Source Image Outside
// 	}

 	if(mp_AppItem->Find("QR Code Info"))
 	{
		wordartItem = mp_AppItem->Find("QR Code Info");
		cv::Mat map(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)) ;
		wordart_evi.qr_foreground_modules.copyTo(map(clipping));
		HKCMedia* media = new HKCImage(map);	
		wordartItem->Update(media);
 	}else{
		cv::Mat map(srcImg->cols,srcImg->rows,CV_8UC4,cv::Scalar(0,0,0,0)) ;
		wordart_evi.qr_foreground_modules.copyTo(map(clipping));	
		wordartItem = mp_AppItem->New(map,"QR Code Info", mp_GLPanel);
 	}
 	wordartProp = (HKCImageProp^)wordartItem->Prop;
 	wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
 	wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
 	wordartProp->Render->Visible = SeeLevelCheck1->Checked;
 
 	if(!mp_AppItem->Find("Quiet Zone2")){
		  wordartItem = mp_AppItem->New(mp_AppItem->Data->QRCData.QuietZone,"Quiet Zone2", mp_GLPanel);
 	}else{wordartItem = mp_AppItem->Find("Quiet Zone2");}
	wordartProp = (HKCImageProp^)wordartItem->Prop;
	wordartProp->Texture->MAG_Filter = HKETexFltr::Nearest;
	wordartProp->Texture->MIN_Filter = HKETexFltr::Nearest;
 	wordartProp->Render->Visible = SeeLevelCheck1->Checked;

	mp_GLPanel->Invalidate();
	/// Rebuild layers
	LayerTree->Invalidate();
	mp_AppLayerMgr->Build(this->LayerTree, mp_AppItem);
	this->ParamGrid->Refresh();
	//Centerize the media
	GLPanel_Focus(mp_AppItem);
}