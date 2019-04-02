/**
* @file AppLayerManagerDefault.cpp
*
* Implementation of the class methods for default layer manager
*
* @author James Hung-Kuo Chu (2012/12/22)
*/

#include "stdafx.h"
#include "AppProperty.h"
#include "AppData.h"
#include "AppItem.h"
#include "AppLayerManager.h"

using namespace AppFrame;
using namespace DevComponents::DotNetBar;
using namespace DevComponents::AdvTree;

/***************************************************************************\
*                            Description                                  *
\***************************************************************************/
/*! \class AppFrame::HKCLayerMgrDef

Implementation of the class methods. */

/***************************************************************************\
*                           Class Methods                                 *
\***************************************************************************/
/*---------------------------------------------------------------------*/
/*                           Constructors                              */
HKCLayerMgrDef::HKCLayerMgrDef(void) 
{	
}

/*---------------------------------------------------------------------*/
/*                            Destructor                               */
HKCLayerMgrDef::~HKCLayerMgrDef(void)
{		
}

/*---------------------------------------------------------------------*/
/*                             Operations                              */
/// Add layer
bool HKCLayerMgrDef::Add(AdvTree^ _layerTree, HKCMediaItem^ _item, System::Drawing::Image^ _img)
{
	if(!_layerTree || !_item) return false;

	Node^ layer	= gcnew Node();
	layer->CheckBoxVisible = true;
	layer->Style = _layerTree->NodeStyle;	
	layer->Text	= _item->Label;		
	layer->Image = _img;		
	layer->Checked = _item->Prop->Render->Visible;
	_layerTree->Nodes->Add(layer);
	return true;
}
bool HKCLayerMgrDef::Add(AdvTree^ _layerTree, HKCMediaItem^ _item, System::Drawing::Image^ _img,System::String^ name )
{
	if(!_layerTree || !_item) return false;

	Node^ layer	= gcnew Node();
	layer->CheckBoxVisible = true;
	layer->Style = _layerTree->NodeStyle;	
	layer->Text	= _item->Label;		
	layer->Image = _img;		
	layer->Name = name;
	layer->Checked = _item->Prop->Render->Visible;
	_layerTree->Nodes->Add(layer);
	return true;
}
bool HKCLayerMgrDef::Addnode(Node^ Parent, HKCMediaItem^ _item, System::Drawing::Image^ _img)
{
	if(!Parent || !_item) return false;

	Node^ layer	= gcnew Node();
	layer->CheckBoxVisible = true;
	layer->Style = Parent->Style;	
	layer->Text	= _item->Label;		
	layer->Image = _img;		
	layer->Checked = _item->Prop->Render->Visible;
	Parent->Nodes->Add(layer);
	return true;
}

/// Build layers from application item
void HKCLayerMgrDef::Build(AdvTree^ _layerTree, HKCAppItem^ _appItem)
{
	if(!_layerTree || !_appItem) return;

	/// Clear original layers	
	_layerTree->Nodes->Clear();

	/// Get the resource manager
	System::Reflection::Assembly^ assembly = System::Reflection::Assembly::GetExecutingAssembly();
	System::Reflection::AssemblyName^ assemblyName = assembly->GetName();	
	System::Resources::ResourceManager^ resMgr = gcnew System::Resources::ResourceManager(assemblyName->Name+".AppRes", assembly);
	
	/// Add each item to layer tree
	for each(HKCMediaItem^ item in _appItem->Items)
	{
		System::Drawing::Image^ layerImg = nullptr;
		switch(item->Media->Type())
		{
		case IMAGE:			
			layerImg = cli::safe_cast<System::Drawing::Image^>(resMgr->GetObject(L"LayerImage.Image"));
			break;
		case VIDEO:			
			layerImg = cli::safe_cast<System::Drawing::Image^>(resMgr->GetObject(L"LayerVideo.Image"));		
			break;
		default:			
			Console::WriteLine("HKCLayerMgrDef::Build() : Improper media type!");
			continue;
		}

		/// Fix the button image according to specific context
		if(item->Label->Contains("Canvas") || item->Label->Contains("CANVAS"))
			layerImg = cli::safe_cast<System::Drawing::Image^>(resMgr->GetObject(L"LayerCanvas.Image"));	
		else if(item->Label->Contains("QRCode") || item->Label->Contains("QRCODE"))
			layerImg = cli::safe_cast<System::Drawing::Image^>(resMgr->GetObject(L"LayerQRCode.Image"));
		
		if(!Add(_layerTree, item, layerImg))
			Console::WriteLine("HKCLayerMgrDef::Build() : Add layer failed!");
	}
}

void HKCLayerMgrDef::BuildCandidate(AdvTree^ _layerTree, HKCAppItem^ _appItem)
{
	if(!_layerTree || !_appItem) return;

	/// Clear original layers	
	_layerTree->Nodes->Clear();

	/// Get the resource manager
	System::Reflection::Assembly^ assembly = System::Reflection::Assembly::GetExecutingAssembly();
	System::Reflection::AssemblyName^ assemblyName = assembly->GetName();	
	System::Resources::ResourceManager^ resMgr = gcnew System::Resources::ResourceManager(assemblyName->Name+".AppRes", assembly);

	/// Add each item to layer tree
	int r = 0 ; 
	for each(HKCMediaItem^ Candidate in _appItem->Candidates)
	{
		System::Drawing::Image^ layerImg = nullptr;
		switch(Candidate->Media->Type())
		{
		case IMAGE:			
			layerImg = cli::safe_cast<System::Drawing::Image^>(resMgr->GetObject(L"LayerImage.Image"));
			break;
		case VIDEO:			
			layerImg = cli::safe_cast<System::Drawing::Image^>(resMgr->GetObject(L"LayerVideo.Image"));		
			break;
		default:			
			Console::WriteLine("HKCLayerMgrDef::Build() : Improper media type!");
			continue;
		}
		if (System::String::Compare(Candidate->Label,"user define")==0)
		{
			if(!Add(_layerTree, Candidate, layerImg,"user define"))
				Console::WriteLine("HKCLayerMgrDef::Build() : Add layer failed!");
		}
		else if(!Add(_layerTree, Candidate, layerImg,""+r))
			Console::WriteLine("HKCLayerMgrDef::Build() : Add layer failed!");
		r++;
	}
}

void HKCLayerMgrDef::BuildWordArtLayer(AdvTree^ _layerTree, HKCAppItem^ _appItem)
{
	if(!_layerTree || !_appItem) return;

	/// Clear original layers	
	_layerTree->Nodes->Clear();

	/// Get the resource manager
	System::Reflection::Assembly^ assembly = System::Reflection::Assembly::GetExecutingAssembly();
	System::Reflection::AssemblyName^ assemblyName = assembly->GetName();	
	System::Resources::ResourceManager^ resMgr = gcnew System::Resources::ResourceManager(assemblyName->Name+".AppRes", assembly);

	/// Add each item to layer tree
	int r= 0;
	for each(HKCMediaItem^ Region in _appItem->WordArtLayers)
	{	
		System::Drawing::Image^ layerImg = nullptr;
		switch(Region->Media->Type())
		{
			case IMAGE:			
				layerImg = cli::safe_cast<System::Drawing::Image^>(resMgr->GetObject(L"LayerImage.Image"));
				break;
			case VIDEO:			
				layerImg = cli::safe_cast<System::Drawing::Image^>(resMgr->GetObject(L"LayerVideo.Image"));		
				break;
			default:			
				Console::WriteLine("HKCLayerMgrDef::Build() : Improper media type!");
				continue;
		}
		if(!Add(_layerTree, Region, layerImg))
			Console::WriteLine("HKCLayerMgrDef::Build() : Add layer failed!");
			
		
		r++;
	}
}
/// Update layers' properties
void HKCLayerMgrDef::Update(AdvTree^ _layerTree, HKCAppItem^ _appItem)
{
	if(!_layerTree || !_appItem) return;
	if(_layerTree->Nodes->Count != _appItem->Items->Count)
	{
		Console::WriteLine("HKCLayerMgrDef::Update() : The number of layers and items are not the same!");
		return;
	}

	for(int i = 0; i < _appItem->Items->Count; ++i)
	{
		Node^ layer	= _layerTree->Nodes[i];
		HKCMediaItem^ item = _appItem->Items[i];

		layer->Checked = item->Prop->Render->Visible;
	}
}
/// Update layers' properties
void HKCLayerMgrDef::UpdateCandidate(AdvTree^ _layerTree, HKCAppItem^ _appItem)
{
	if(!_layerTree || !_appItem) return;
	if(_layerTree->Nodes->Count != _appItem->Candidates->Count)
	{
		Console::WriteLine("HKCLayerMgrDef::Update() : The number of layers and items are not the same!");
		return;
	}

	for(int i = 0; i < _appItem->Candidates->Count; ++i)
	{
		Node^ layer	= _layerTree->Nodes[i];
		HKCMediaItem^ Candidate = _appItem->Candidates[i];

		layer->Checked = Candidate->Prop->Render->Visible;
	}
}
void HKCLayerMgrDef::UpdateWordArtLayer(AdvTree^ _layerTree, HKCAppItem^ _appItem)
{
	if(!_layerTree || !_appItem) return;
	if(_layerTree->Nodes->Count != _appItem->WordArtLayers->Count)
	{
		Console::WriteLine("HKCLayerMgrDef::Update() : The number of layers and items are not the same!");
		return;
	}

	for(int i = 0; i < _appItem->WordArtLayers->Count; ++i)
	{
		Node^ layer	= _layerTree->Nodes[i];
		HKCMediaItem^ Region = _appItem->WordArtLayers[i];
		layer->Checked=Region->Prop->Render->Visible;
		
	}
}