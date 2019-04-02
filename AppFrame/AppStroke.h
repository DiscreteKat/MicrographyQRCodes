/**
* @file AppStroke.h
*
* Class for application painter stroke
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

namespace AppFrame 
{
	/**
	*	@brief Class for the painter stroke
	*/
	public ref class HKCStroke abstract
	{		
		/*==========================  PUBLIC  =================================*/
	public:					
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCStroke(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                      Painting                                */
		/*! \{                                                                 */				
		
		/// Painting
		virtual void Paint(cv::Mat&, cv::Point2d&, cv::Point2d&, cv::Scalar, int) = 0;

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCStroke(void) {}						

		/*! \}                                                                 */
	};

	/**
	*	@brief Class for the brush stroke
	*/
	public ref class HKCStrkBrush : public HKCStroke
	{
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCStrkBrush(void) {}						

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCStrkBrush(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                      Painting                                */
		/*! \{                                                                 */				

		/// Painting with colored brush
		virtual void Paint(cv::Mat&, cv::Point2d&, cv::Point2d&, cv::Scalar, int) override;

		/*! \}                                                                 */					
	};

	/**
	*	@brief Class for the erase stroke
	*/
	public ref class HKCStrkErase : public HKCStroke
	{
		/*==========================  PUBLIC  =================================*/
	public:			
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCStrkErase(void) {}						

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCStrkErase(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                      Painting                                */
		/*! \{                                                                 */				

		/// Painting as an eraser
		virtual void Paint(cv::Mat&, cv::Point2d&, cv::Point2d&, cv::Scalar, int) override;

		/*! \}                                                                 */			
	};
}