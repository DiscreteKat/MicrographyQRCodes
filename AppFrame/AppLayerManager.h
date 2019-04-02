/**
* @file AppLayerManager.h
*
* Classes for application layer manager
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#pragma once

namespace AppFrame 
{	
	using namespace System::Windows::Forms;
	using namespace DevComponents::AdvTree;

	/**
	*	@brief Base class for the application layer manager
	*/
	public ref class HKCAppLayerMgr abstract
	{
		/*==========================  PUBLIC  =================================*/
	public:					
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCAppLayerMgr(void) {}

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Operations                               */
		/*! \{                                                                 */			

		/// Add layer
		virtual bool Add(AdvTree^, HKCMediaItem^, System::Drawing::Image^) = 0;
		virtual bool Addnode(Node^ Parent, HKCMediaItem^ _item, System::Drawing::Image^ _img)=0;
		/// Build layers from application item
		virtual void Build(AdvTree^, HKCAppItem^) = 0;
		virtual void BuildCandidate(AdvTree^, HKCAppItem^) =0;
		virtual void BuildWordArtLayer(AdvTree^, HKCAppItem^) =0;
		/// Update layers' properties
		virtual void Update(AdvTree^, HKCAppItem^) =0;
		virtual void UpdateCandidate(AdvTree^, HKCAppItem^) =0;
		virtual void UpdateWordArtLayer(AdvTree^, HKCAppItem^) =0;
		/*! \}                                                                 */		
		/*---------------------------------------------------------------------*/		
		/*! \name                 Access Data Members                          */
		/*! \{                                                                 */	

		virtual System::String^ ToString() override
		{
			return L"Application Layer Manager";
		}

		/*! \}                                                                 */	
		/*=========================  PROTECTED  ===============================*/
	protected:				
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCAppLayerMgr(void) {}			

		/*! \}                                                                 */		
	};

	/**
	*	@brief Class for the default layer manager
	*/
	public ref class HKCLayerMgrDef : public HKCAppLayerMgr
	{		
		/*==========================  PUBLIC  =================================*/
	public:		
		/*---------------------------------------------------------------------*/
		/*! \name                   Constructors                               */
		/*! \{                                                                 */

		HKCLayerMgrDef(void);					

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		

		virtual ~HKCLayerMgrDef(void);	

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Layer Operations                            */
		/*! \{                                                                 */			

		/// Add layer
		virtual bool Add(AdvTree^, HKCMediaItem^, System::Drawing::Image^) override;
		bool Add(AdvTree^, HKCMediaItem^, System::Drawing::Image^ ,System::String^ name);
		virtual bool Addnode(Node^ Parent, HKCMediaItem^ _item, System::Drawing::Image^ _img)override;
		/// Build layers from application item
		virtual void Build(AdvTree^, HKCAppItem^) override;
		virtual void BuildCandidate(AdvTree^, HKCAppItem^) override;
		virtual void BuildWordArtLayer(AdvTree^, HKCAppItem^) override;
		/// Update layers' properties
		virtual void Update(AdvTree^, HKCAppItem^) override;
		virtual void UpdateCandidate(AdvTree^, HKCAppItem^) override;
		virtual void UpdateWordArtLayer(AdvTree^, HKCAppItem^) override;
		/*! \}                                                                 */		
		/*=========================  PROTECTED  ===============================*/
	protected:				
		
	};	
}