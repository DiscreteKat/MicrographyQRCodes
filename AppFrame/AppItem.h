/**
* @file AppItem.h
*
* Classes for application items
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

#include "AppMediaItem.h"

namespace AppFrame {

	using namespace System;	
	using namespace System::ComponentModel;	
	using namespace System::Collections;
	using namespace System::Collections::Generic;	
	using namespace HKOGLPanel;
	using namespace HKCV;

	/**
	*	@brief Class for the application item
	*/
	public ref class HKCAppItem
	{
		/*==========================  PUBLIC  =================================*/
	public:	
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppItem(void); 									

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		~HKCAppItem(void);

		/*! \}                                                                 */	
		/*---------------------------------------------------------------------*/		
		/*! \name                   Item Operations                            */
		/*! \{                                                                 */

		/// Clear data
		void Clear(void);

		/// Add a media item
		bool Add(HKCMediaItem^);
		bool AddCandidate(HKCMediaItem^);
		bool AddWordArt(HKCMediaItem^);
		bool ClearCandidate( );
		bool ClearWordArt( );
		/// Find the media item with specific label
		HKCMediaItem^ Find(System::String^);				
		HKCMediaItem^ FindCandidate(System::String^);
		/// Create a new media item
		HKCMediaItem^ New(cv::Mat&, System::String^, HKOGLPanelControl^);
		HKCMediaItem^ NewCandidate(cv::Mat&, System::String^, HKOGLPanelControl^);
		HKCMediaItem^ NewWordArt(cv::Mat&, System::String^, HKOGLPanelControl^);
		/// Create a new media item
		HKCMediaItem^ New(HKCMedia*, System::String^, HKOGLPanelControl^);		
		HKCMediaItem^ NewCandidate(HKCMedia*, System::String^, HKOGLPanelControl^);	
		HKCMediaItem^ NewWordArt(HKCMedia*, System::String^, HKOGLPanelControl^);	
		/// Delete media item at specific index
		bool Delete(int);				

		/// Delete media item with specific label
		bool Delete(System::String^);			

		/// Delete media item with the specified labels
		void Delete(cli::array<System::String^>^);

		/// Delete media item except the specified labels
		void DeleteEx(cli::array<System::String^>^);

		/// Select media item with specific index
		void Select(int);		

		/// Select media item with specific label
		void Select(System::String^);		

		/// Show media item with specific index
		void Show(int);		

		/// Show media item with specific label
		void Show(System::String^);

		/// Move the media item to specific location in the list (0:top, -1:bottom)
		void MoveTo(System::String^, int);

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/		
		/*! \name                 Access data members                          */
		/*! \{                                                                 */
		
		/// Access to list of media items
		property List<HKCMediaItem^>^ Items
		{
			List<HKCMediaItem^>^ get(void) { return mp_Items; }			
		}
		/// Access to selected media item
		property HKCMediaItem^ Item
		{
			HKCMediaItem^ get(void) { return mp_Item; }	
			void set(HKCMediaItem^ value) 
			{ 
				mp_Item = value; 
				mp_Prop->Media = (mp_Item) ? mp_Item->Prop : nullptr;
			}
		}
		/// Access to list of media items
		property List<HKCMediaItem^>^ Candidates
		{
			List<HKCMediaItem^>^ get(void) { return mp_candidates; }			
		}
		/// Access to list of media items
		property List<HKCMediaItem^>^ WordArtLayers
		{
			List<HKCMediaItem^>^ get(void) { return mp_wordarts; }			
		}
		/// Access to selected media item
		property HKCMediaItem^ Candidate
		{
			HKCMediaItem^ get(void) { return mp_candidate; }	
			void set(HKCMediaItem^ value) 
			{ 
				mp_candidate = value; 
				//mp_Prop->Media = (mp_candidates) ? mp_Item->Prop : nullptr;
			}
		}
		/// Access to selected media item
		property HKCMediaItem^ WordArtLayer
		{
			HKCMediaItem^ get(void) { return mp_wordart; }	
			void set(HKCMediaItem^ value) 
			{ 
				mp_wordart = value; 
				//mp_Prop->Media = (mp_candidates) ? mp_Item->Prop : nullptr;
			}
		}
		/// Access to application property object
		property HKCAppProp^ Prop
		{
			HKCAppProp^ get(void) { return mp_Prop; }			
		}
		/// Access to application parameter object
		property HKCAppParam^ Param
		{
			HKCAppParam^ get(void) { return mp_Param; }			
		}
		/// Access to application data
		property HKCAppData* Data
		{
			HKCAppData* get(void) { return mp_Data; }			
		}		
		virtual System::String^ ToString() override
		{
			return L"Application Item";
		}

		/*! \}                                                                 */		
		/*==========================  PRIVATE  ================================*/
	private:
		/*---------------------------------------------------------------------*/
		/*! \name                        Data								   */
		/*! \{                                                                 */

		List<HKCMediaItem^>^	mp_Items;		///< List of media items
		HKCMediaItem^		mp_Item;		///< Selected item
		List<HKCMediaItem^>^    mp_candidates;
		HKCMediaItem^       mp_candidate;
		List<HKCMediaItem^>^    mp_wordarts;
		HKCMediaItem^       mp_wordart;
		HKCAppProp^		mp_Prop;		///< Application property object
		HKCAppParam^		mp_Param;		///< Application parameter object
		HKCAppData*		mp_Data;		///< Application data		

		/*! \}                                                                 */
	};
}