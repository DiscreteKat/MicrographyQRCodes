/**
* @file AppAlgoTextGeneration.h
*
* Classes for generating text on mesh
*
* @author 
*/
#pragma once
namespace AppFrame 
{
	/**
	*	@brief Class for the base optimization interface
	*/
	
	public ref class AppAlgoTextGeneration : public HKCAlgorithm
	{
		/*==========================  PUBLIC  =================================*/
	public:				
		/*---------------------------------------------------------------------*/
		/*! \name                     Destructor                               */
		/*! \{                                                                 */		
		AppAlgoTextGeneration(void):m_TypeSet(1),m_CutWord(true){}
		virtual ~AppAlgoTextGeneration(void) {}		

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                 Algorithm Operations						   */
		/*! \{                                                                 */	

		/// Perform 
		virtual bool Execute(HKCAppItem^ _appItem) override;

		/*! \}                                                                 */
		/*---------------------------------------------------------------------*/
		/*! \name                  Access Methods                              */
		/*! \{                                                                 */

		virtual property System::String^ Abbrev
		{
			System::String^ get(void) override { return " Text Generation"; }				
		}
		virtual System::String^ ToString() override
		{
			return L"generating text on mesh";
		}	

	public:
		void TypeSet(int set){m_TypeSet=set;}
		void Enable_CutWord(bool fit){m_CutWord=fit;}
		void TextGeneration(HKCAppItem^ _appItem, QRWordArt::QRStringLines& splines, vector<std::string>&  candidate_strings);
		void TextGeneration(HKCAppItem^ _appItem, std::vector<int>& splines_idx, vector<std::string>&  candidate_strings);
	public:
		static int Text_Record_Order = 0;
	private:	
		int  m_TypeSet;//0-Random 1-Order
		bool m_CutWord;
	};
}
