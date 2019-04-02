/**
* @file AppMediaItem.h
*
* Class for application media item
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

#include "AppData.h"

namespace AppFrame {

	using namespace System;	
	using namespace System::ComponentModel;	
	using namespace System::Collections;
	using namespace System::Collections::Generic;	
	using namespace HKOGLPanel;
	using namespace HKCV;


	/**
	*	@brief Class for media item
	*/
	public ref class HKCMediaItem
	{	
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCMediaItem(void);

		HKCMediaItem(HKCMedia*, System::String^, HKOGLPanelControl^);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCMediaItem(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                       Update                                 */
		/*! \{                                                                 */

		/// Update media
		virtual bool Update(void) { return Update(UPDATE_ALL); }

		/// Update specific data of media 
		virtual bool Update(int);

		/// Update the alpha channel of the media
		virtual bool Update(cv::Mat&);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                       Render                                 */
		/*! \{                                                                 */

		/// Render media
		virtual void Render(void);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                 Access data members                          */
		/*! \{                                                                 */		

		/// Access to media object
		property HKCMedia* Media
		{
			HKCMedia* get(void) { return mp_Media; }
			void      set(HKCMedia* value) { Update(value); }		
		}
		/// Access to media's property object
		property HKCMediaProp^ Prop
		{
			HKCMediaProp^ get(void) { return mp_Prop; }		
		}
		/// Access to media's transformation
		property HKCXForm* XForm
		{
			HKCXForm* get(void) { return mp_XForm; }			
		}
		/// Access to media's label
		property System::String^ Label
		{
			System::String^ get(void) { return m_Label; }		
			void set(System::String^ value) { m_Label = value; }
		}
		/// Access to belonging OpenGL rendering context
		property HKOGLPanelControl^ glContext
		{
			HKOGLPanelControl^ get(void) { return mp_GLCntxt; }		
			void set(HKOGLPanelControl^ value) { mp_GLCntxt = value; }
		}	
		virtual System::String^ ToString() override
		{
			return L"Media Item";
		}

		/*! \}                                                                 */
		/*=========================  PROTECTED  ===============================*/
		
		/*---------------------------------------------------------------------*/		
		/*! \name                       Update                                 */
		/*! \{                                                                 */

		/// Update media with another input media
		virtual bool Update(HKCMedia*);
protected:
		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                        Data								   */
		/*! \{                                                                 */

		HKCMedia*		mp_Media;		///< Media object		
		HKCMediaProp^		mp_Prop;		///< Media's property object
		HKCXForm*		mp_XForm;		///< Media's 2D transformation 		
		System::String^		m_Label;		///< Media's label
		HKOGLPanelControl^	mp_GLCntxt;		///< OpenGL rendering context

		/*! \}                                                                 */
	};	
}