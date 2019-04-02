#include "stdafx.h"
#include "YJPSNRSSIM.h"
PSNR::PSNR(cv::Mat A,cv::Mat B,cv::Mat mask,double *MSE, double *psnr)
{
	if (A.cols!=B.cols||A.rows!=B.rows)
	{
		std::cout<<"Difference input size! "<<std::endl;
		std::cout<<"cols: "<<A.cols<<" "<<B.cols<<std::endl;
		std::cout<<"rows: "<<A.rows<<" "<<B.rows<<std::endl;
		return;
	}
	if (mask.channels()!=1)
	{
		std::cout<<"wrong mask nchan"<<std::endl;
		return;
	}	
	long long int sigma = 0;
	long long int sigma2 = 0 ;
	*MSE=0;*psnr=0;
	int frameSize =0;
	int L1=0, L2=0;
	int A1=0, A2=0;
	int B1=0, B2=0;
	int  i = 5; 
	cv::Mat src1,src2;
	cvtColor(A,src1,CV_BGR2Lab);
	cvtColor(B,src2,CV_BGR2Lab);
	cv::GaussianBlur( src1, src1, cv::Size( i, i ), 0, 0 );
	cv::GaussianBlur( src2, src2, cv::Size( i, i ), 0, 0 );
	cv::resize(mask,mask,cv::Size(src1.rows,src1.cols));
	
	for(int i=0;i<src1.rows;i++){
		for(int j=0;j<src1.cols;j++){
			uchar m = mask.at<uchar>(i,j);
			if (m==0)
			{
				continue;
			}
			frameSize++;
			cv::Vec3b vA = src1.at<cv::Vec3b>(i,j);
			cv::Vec3b vB = src2.at<cv::Vec3b>(i,j);
			L1=vA[0];//L		
			L2=vB[0];//L
// 			A1=vA[1];//L		
// 			A2=vB[1];//L
// 			B1=vA[2];//L		
// 			B2=vB[2];
			sigma+=(L1-L2)*(L1-L2);
			
		}
	}
	if (frameSize>0)
	{
		*MSE=sigma/(double)frameSize;
	}
	*psnr=10*log10(255*255/ *MSE);
	
// 	cout<<"sigma: "<<sigma<<endl;;
// 	cout<<"MSE: "<<MSE<<endl;;
//	cout<<"PSNR: "<<*psnr<<endl;;

}
SSIM::SSIM(cv::Mat A ,cv::Mat B, cv::Mat mask,double*mssim,cv::Mat ssim_map)
{
	if (A.cols!=B.cols||A.rows!=B.rows)
	{
		std::cout<<"Difference input size! "<<std::endl;
		return;
	}
	if (mask.channels()!=1)
	{
		std::cout<<"wrong mask nchan"<<std::endl;
		return;
	}
	*mssim=0;
	double K1= 0.01,K2=0.03,L = 255;
	const double C1 = (K1 * L) * (K1 * L); //6.5025 C1 = (K(1)*L)^2;
	const double C2 = (K2 * L) * (K2 * L); //58.5225 C2 = (K(2)*L)^2;
	const int downsamplewidth=256;
	//const int gaussian_window=7;
	const cv::Size gaussian_window(11,11);
	const double gaussian_sigma=1.5;
	//¡@get width and height
	cv::Mat Gray_A,Gray_B;
	cvtColor(A,Gray_A,CV_BGR2GRAY);
	cvtColor(B,Gray_B,CV_BGR2GRAY);
	//IplImage *Src1 = &IplImage(Gray_A);
	//IplImage *Src2 = &IplImage(Gray_B);

	//IplImage* _mask=&IplImage(mask);
	cv::Mat _mask=mask.clone();
	int x=Gray_A.cols, y=Gray_A.rows;

	//¡@distance (down sampling) setting
	int rate_downsampling = std::max(1, int((std::min(x,y) / downsamplewidth) + 0.5));

	int nChan=1, d=IPL_DEPTH_32F;

	//¡@size before down sampling
	CvSize size_L = cvSize(x, y);

	//¡@size after down sampling
	CvSize size = cvSize(x / rate_downsampling, y / rate_downsampling);

	//¡@image allocation
	
	//cv::Ptr<IplImage> img1 = cvCreateImage( size, d, nChan);
	//cv::Ptr<IplImage> img2 = cvCreateImage( size, d, nChan);
	cv::Mat img1= cv::Mat(size,CV_32FC1);
	cv::Mat img2= cv::Mat(size,CV_32FC1);

	//¡@convert 8 bit to 32 bit float value
	//cv::Ptr<IplImage> img1_L = cvCreateImage( size_L, d, nChan);
	//cv::Ptr<IplImage> img2_L = cvCreateImage( size_L, d, nChan);
	cv::Mat img1_L=cv::Mat(size_L,CV_32FC1);
	cv::Mat img2_L=cv::Mat(size_L,CV_32FC1);
// 	cvConvert(Gray_A, img1_L);
// 	cvConvert(Gray_B, img2_L);
	Gray_A.convertTo(img1_L, CV_32FC1);
	Gray_B.convertTo(img2_L, CV_32FC1);
	//¡@down sampling
	cv::resize(img1_L, img1,size);
	cv::resize(img2_L, img2,size);

	//¡@buffer alocation
	//cv::Ptr<IplImage> img1_sq = cvCreateImage( size, d, nChan);
	//cv::Ptr<IplImage> img2_sq = cvCreateImage( size, d, nChan);
	//cv::Ptr<IplImage> img1_img2 = cvCreateImage( size, d, nChan);
	cv::Mat img1_sq = cv::Mat(size,CV_32FC1);
	cv::Mat img2_sq = cv::Mat(size,CV_32FC1);
	cv::Mat img1_img2 = cv::Mat(size,CV_32FC1);

	//¡@pow and mul
// 	cvPow( img1, img1_sq, 2 );
// 	cvPow( img2, img2_sq, 2 );
// 	cvMul( img1, img2, img1_img2, 1 );
	cv::pow(img1,2,img1_sq);
	cv::pow(img2,2,img2_sq);
	cv::multiply( img1, img2, img1_img2, 1 );
	//¡@get sigma
// 	cv::Ptr<IplImage> mu1 = cvCreateImage( size, d, nChan);
// 	cv::Ptr<IplImage> mu2 = cvCreateImage( size, d, nChan);
// 	cv::Ptr<IplImage> mu1_sq = cvCreateImage( size, d, nChan);
// 	cv::Ptr<IplImage> mu2_sq = cvCreateImage( size, d, nChan);
// 	cv::Ptr<IplImage> mu1_mu2 = cvCreateImage( size, d, nChan);
	cv::Mat mu1 = cv::Mat(size,CV_32FC1);
	cv::Mat mu2 = cv::Mat(size,CV_32FC1);
	cv::Mat mu1_sq = cv::Mat(size,CV_32FC1);
	cv::Mat mu2_sq = cv::Mat(size,CV_32FC1);
	cv::Mat mu1_mu2 = cv::Mat(size,CV_32FC1);

// 	cv::Ptr<IplImage> sigma1_sq = cvCreateImage( size, d, nChan);
// 	cv::Ptr<IplImage> sigma2_sq = cvCreateImage( size, d, nChan);
// 	cv::Ptr<IplImage> sigma12 = cvCreateImage( size, d, nChan);
// 	cv::Ptr<IplImage> sigma1 = cvCreateImage( size, d, nChan);
// 	cv::Ptr<IplImage> sigma2 = cvCreateImage( size, d, nChan);
// 	cv::Ptr<IplImage> sigma1_sigma2 = cvCreateImage( size, d, nChan);
	cv::Mat sigma1_sq = cv::Mat(size,CV_32FC1);
	cv::Mat sigma2_sq = cv::Mat(size,CV_32FC1);
	cv::Mat sigma12 = cv::Mat(size,CV_32FC1);
	cv::Mat sigma1 = cv::Mat(size,CV_32FC1);
	cv::Mat sigma2 = cv::Mat(size,CV_32FC1);
	cv::Mat sigma1_sigma2 = cv::Mat(size,CV_32FC1);

// 	cv::Ptr<IplImage> L_xy = cvCreateImage( size, d, nChan);
// 	cv::Ptr<IplImage> C_xy = cvCreateImage( size, d, nChan);
	cv::Mat L_xy = cv::Mat(size,CV_32FC1);
	cv::Mat C_xy = cv::Mat(size,CV_32FC1);
	//¡@allocate buffer
// 	cv::Ptr<IplImage> temp1 = cvCreateImage( size, d, nChan);
// 	cv::Ptr<IplImage> temp2 = cvCreateImage( size, d, nChan);
// 	cv::Ptr<IplImage> temp3 = cvCreateImage( size, d, nChan);
	cv::Mat temp1 = cv::Mat(size,CV_32FC1);
	cv::Mat temp2 = cv::Mat(size,CV_32FC1);	
	cv::Mat temp3 = cv::Mat(size,CV_32FC1);
	//ssim map
	//cv::Ptr<IplImage> ssim_maps = cvCreateImage( size, d, nChan);
	cv::Mat ssim_maps = cv::Mat(size,CV_32FC1);

	//////////////////////////////////////////////////////////////////////////
	// 	// PRELIMINARY COMPUTING

	//¡@gaussian smooth
	cv::GaussianBlur( img1, mu1,  gaussian_window, gaussian_sigma );
	cv::GaussianBlur( img2, mu2,  gaussian_window, gaussian_sigma );
	//cvSmooth( img2, mu2, CV_GAUSSIAN, gaussian_window, gaussian_window, gaussian_sigma );

	//¡@get mu
	cv::pow( mu1, 2 , mu1_sq );
	cv::pow( mu2, 2 , mu2_sq );
	//cvMul( mu1, mu2, mu1_mu2, 1 );
	cv::multiply( mu1, mu2, mu1_mu2, 1 );
	//¡@calc sigma
	//cvSmooth( img1_sq, sigma1_sq, CV_GAUSSIAN, gaussian_window, gaussian_window, gaussian_sigma );
	cv::GaussianBlur( img1_sq, sigma1_sq,  gaussian_window, gaussian_sigma );
	cv::addWeighted( sigma1_sq, 1, mu1_sq, -1, 0, sigma1_sq );
	//cvPow(sigma1_sq,sigma1,0.5);
	//cvSmooth( img2_sq, sigma2_sq, CV_GAUSSIAN, gaussian_window, gaussian_window, gaussian_sigma);
	cv::GaussianBlur( img2_sq, sigma2_sq,  gaussian_window, gaussian_sigma );
	cv::addWeighted( sigma2_sq, 1, mu2_sq, -1, 0, sigma2_sq );
	//cvPow(sigma2_sq,sigma2,0.5);
	//cvSmooth( img1_img2, sigma12, CV_GAUSSIAN, gaussian_window, gaussian_window, gaussian_sigma );
	cv::GaussianBlur( img1_img2, sigma12,  gaussian_window, gaussian_sigma );
	cv::addWeighted( sigma12, 1, mu1_mu2, -1, 0, sigma12 );
// 	cvMul( sigma1_sq, sigma2_sq, sigma1_sigma2, 1 );
// 	cvPow(sigma1_sigma2,sigma1_sigma2,0.5);
	cv::multiply( sigma1_sq, sigma2_sq, sigma1_sigma2, 1 );
	cv::pow( sigma1_sigma2, 0.5 , sigma1_sigma2 );
	//////////////////////////////////////////////////////////////////////////
	//Formula
	// (2*mu1_mu2 + C1)
	//cvScale( mu1_mu2, temp1, 2 );
	//cvAddS( temp1, cvScalarAll(C1), temp1 );
	temp1=2*mu1_mu2+C1;
	// (mu1_sq + mu2_sq + C1)
	//cvAdd( mu1_sq, mu2_sq, temp2 );
	//cvAddS( temp2, cvScalarAll(C1), temp2 );
	temp2=mu1_sq+mu2_sq+C1;
	// L=(2*mu1_mu2 + C1)/(mu1_sq + mu2_sq + C1)
	//cvDiv( temp1, temp2, L_xy, 1 );
	cv::divide(temp1,temp2,L_xy);
//	cv::divide(temp1,temp2,ssim_maps);
	
	
// (2*sigma1_sigma2 + C2)
// 	cvScale( sigma1_sigma2, temp1, 2 );
// 	cvAddS( temp1, cvScalarAll(C2), temp1 );
	temp1=2*sigma1_sigma2+C2;
	// (sigma1_sq + sigma2_sq + C2)
// 	cvAdd( sigma1_sq, sigma2_sq, temp2 );
// 	cvAddS( temp2, cvScalarAll(C2), temp2 );
	temp2=sigma1_sq+sigma2_sq+C2;
	// C=(2*sigma1_sigma2 + C2)/(sigma1_sq + sigma2_sq + C2)
	//cvDiv( temp1, temp2, C_xy, 1 );
	cv::divide( temp1, temp2, C_xy, 1 );
	//Lxy.Cxy
	//cvMul(L_xy,C_xy,ssim_maps,1);
	cv::multiply( L_xy, C_xy, ssim_maps, 1 );
	
// 	cv::Ptr<IplImage> stemp = cvCreateImage( size, IPL_DEPTH_8U, 1);
// 	cv::Ptr<IplImage> mask2 = cvCreateImage( size, IPL_DEPTH_8U, 1);
	cv::Mat stemp = cv::Mat( size, CV_8UC1);
	cv::Mat mask2 = cv::Mat( size, CV_8UC1);
	//IplImage * dest=cvCreateImage(cvGetSize(Src1),8,1);
	cv::Mat dest = cv::Mat(Gray_A.rows,Gray_A.cols,CV_8UC1);
	//cvConvertScale(ssim_maps, stemp, 255.0, 0.0);
	ssim_maps.convertTo(stemp,CV_8UC1,255.0,0.0);
	//cvResize(stemp,dest);
	cv::resize(stemp,dest,cv::Size(Gray_A.rows,Gray_A.cols));
	ssim_map =dest;
	//cvResize(_mask,size,mask2);
	cv::resize(_mask, mask2,size);
	CvScalar index_scalar = cv::mean( ssim_maps,mask2);

	// through observation, there is approximately 
	// 1% error max with the original matlab program

	*mssim= index_scalar.val[0];
//	cout<<"ssim: "<<*mssim<<endl;
	imshow("ssim_map",ssim_map);
	//cv::waitKey();
}