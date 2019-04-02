/**
* @file AppPainter.h
*
* Class for application painter tool
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

#include "AppStroke.h"

namespace AppFrame 
{
	/**
	*	@brief Class for the painter tool
	*/
	public ref class HKCPainter : public HKCAppTool
	{		
		/*==========================  PUBLIC  =================================*/
	public:	
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCPainter(System::String^);

		HKCPainter(System::String^, HKCToolProp^);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCPainter(void);		

		/*! \}                                                                 */	
		/*---------------------------------------------------------------------*/		
		/*! \name                       Render                                 */
		/*! \{                                                                 */		

		virtual void Render(void) override;		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                      Painting                                */
		/*! \{                                                                 */

		/// Painting on an image
		virtual void Paint(cv::Mat&, cv::Point2d&, cv::Point2d&);

		/// Painting on an image
		virtual void Paint(cv::Mat&, cv::Point2d&, cv::Point2d&, cv::Scalar, int);
		
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */				

		/// Activate painter
		virtual bool Activate(HKCAppItem^) override;

		/// Deactivate painter
		virtual bool DeActivate(HKCAppItem^) override;
		
		/**
		* @brief Painter's action.
		*
		* @param _act Label of action.
		*			  1. "STROKE_Name", Name = {BRUSH, ERASE} : Different strokes. 
		*			  2. "CLEAN" : Clean canvas.
		*
		* @param _appItem Application item
		*/
		virtual bool Action(System::String^, HKCAppItem^) override;		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                Access data members                           */
		/*! \{                                                                 */	

		/// Access to stroke object
		property HKCStroke^ Stroke
		{
			HKCStroke^ get(void) { return mp_Stroke; }
			void set(HKCStroke^ value) 
			{ 
				if(mp_Stroke == value) return;	
				if(mp_Stroke) delete mp_Stroke;
				mp_Stroke = value;										
			}			
		}

		/// Access to current mouse cursor position
		property cv::Point2d* Cursor
		{
			cv::Point2d* get(void) { return mp_Cursor; }
			void set(cv::Point2d* value) 
			{ 
				if(mp_Cursor == value) return;	
				(*mp_Cursor) = (*value);				
			}			
		}	

		/// Access to painter's property object
		property HKCPntrProp^ PainterProp
		{
			HKCPntrProp^ get(void) { return mp_PntrProp; }		
		}

		virtual System::String^ ToString() override
		{
			return L"Application Painter Tool";
		}

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
	protected:								
		/*---------------------------------------------------------------------*/
		/*! \name                       Data                                   */
		/*! \{                                                                 */

		HKCStroke^		mp_Stroke;		///< Stroke object
		cv::Point2d*	mp_Cursor;		///< Cursor's position
		HKCPntrProp^	mp_PntrProp;	///< Painter's property object

		/*! \}                                                                 */
	};
}