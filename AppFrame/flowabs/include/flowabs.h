//
// by Jan Eric Kyprianidis <www.kyprianidis.com>
// Copyright (C) 2008-2011 Computer Graphics Systems Group at the
// Hasso-Plattner-Institut, Potsdam, Germany <www.hpi3d.de>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// Modified by James Hung Kuo Chu in 2012/08/30
#pragma once

namespace flowabs
{
	class CFlowAbs
	{
		/*==========================  PUBLIC  =================================*/
	public:			
		/*---------------------------------------------------------------------*/
		/*! \name                     Typedefs                                 */
		/*! \{                                                                 */

		typedef std::unordered_map<int, texture_2d> TexMapT;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		CFlowAbs(void);

		CFlowAbs(const std::string&);

		CFlowAbs(const cv::Mat&);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~CFlowAbs(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */

		/// Initialize data and OpenGL content
		void Init(void);

		/// Set source image
		void setSource(const cv::Mat&);

		/// Read image from file
		bool Read(const std::string&);

		/// Read result to file
		bool Write(const std::string&, int=1);

		/// Capture frame buffer to cv::Mat
		bool Capture(cv::Mat&, int=1);

		/// Render image
		void Render(int=1);

		/// Get image width
		int Width(void) { return (m_Src.data) ? m_Src.cols : 0; }

		/// Get image height
		int Height(void) { return (m_Src.data) ? m_Src.rows : 0; }

		/// Process all
		bool ProcessAll(const CFAbsParam&, int=CACHE_ALL);

		/// Compute Smoothed Structure Tensor
		bool Smoothed_Structure_Tensor(const CFAbsParam&, int=TANGENT_FLOW);
		
		/// Compute Orientation aligned Bilateral Filter
		bool Orientation_aligned_Bilateral_Filter(const CFAbsParam&, int=BILATERAL1);

		/// Compute Flow-based DoG Filter
		bool FDoG_Filter(const CFAbsParam&, int=DIFFERENCE_OF_GAUSSIAN);

		/// Compute DoG Filter
		bool DoG_Filter(const CFAbsParam&, int=DIFFERENCE_OF_GAUSSIAN);
		
		/// Compute Color Quantization
		bool Color_Quantization(const CFAbsParam&, int=COLOR_QUANTIZE);

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:		
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */

		/// Request noise map
		void Request_Noise(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                        Data                                  */
		/*! \{                                                                 */

		bool		m_isReady;
		GLuint		m_FBO;
		cv::Mat		m_Src;
		texture_2d	m_Noise;
		TexMapT		m_TexMap;

		/*! \}                                                                 */
	};

	texture_2d rgb2lab(const texture_2d&);
	texture_2d lab2rgb(const texture_2d&);
	texture_2d gauss_filter(const texture_2d&, float);
	texture_2d tangent_flow_map(const texture_2d&, float);
	texture_2d orientation_aligned_bilateral_filter(const texture_2d&, const texture_2d&, int, float, float);
	texture_2d overlay(const texture_2d&, const texture_2d&);
	texture_2d fdog_filter(const texture_2d&, const texture_2d&, int, float, float, float, float, float); 
	texture_2d dog_filter(const texture_2d&, int, float, float, float, float);
	texture_2d color_quantization(const texture_2d&, int, float, int);
	texture_2d lic_filter(const texture_2d&, const texture_2d&, float);
	texture_2d mix_filter(const texture_2d&, const texture_2d&, const float*);
	texture_2d smooth_filter(const texture_2d&, const texture_2d&, int, float);
}
