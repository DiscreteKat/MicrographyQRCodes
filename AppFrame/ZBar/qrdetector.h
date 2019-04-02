//This code is based on zbar version 0.10
//by  Jeff Brown Copyright 2007-2010 (c), released under LGPL 2.1
//http://zbar.sourceforge.net/
//
//Adapted for use under windows by Oliver Zendel, 09-2012

#ifndef _ZBAR_QR_DETECT_H_
#define _ZBAR_QR_DETECT_H_

//Maximum allowed characters in one qr tag
#define QR_CODE_MAX_CHARS_ALLOWED 128

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct zbar_qrdetect_single_s { 
		int      qr_content_len;
		char    *qr_content;
		int	     px[4];
		int	     py[4];
	} zbar_qrdetect_single;

	typedef struct zbar_qrdetect_results_s {
		unsigned 	    num_detected;
		zbar_qrdetect_single *result;
	} zbar_qrdetect_results;

	int initialize_zbar_qrdetect();
	zbar_qrdetect_results singleimage_zbar_qrdetect(unsigned char* data_left_top_origin_nopadding, int width, int height);
	zbar_qrdetect_results singleimage_zbar_qrdetect_roi(unsigned char* data_left_top_origin, int width, int height, int bpline); //bpline=bytes per line, also often called width step, allows detection in ROI and images with padding
	unsigned char *qr_binarize_result(const unsigned char *_img,int _width,int _height);
	int *GridSampling_result(int *dim);
	void free_zbar_qrdetect_result(zbar_qrdetect_results free_res);
	void destroy_zbar_qrdetect();
	void print_last_zbar_qrdetect_error();

#ifdef __cplusplus
}
#endif

#endif
