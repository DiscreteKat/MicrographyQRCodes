#include "stdafx.h"
#include "JsonApp.h"

#include <iostream>
#include <fstream>


//************************************
// Method:    ReadFile
// FullName:  JsonApp::ReadFile
// Access:    public 
// Returns:   bool 
// Qualifier: Read File to stream and pass to Json Reader
// Parameter: Json::Value * root
// Parameter: const char * filepath
//************************************
bool JsonApp::ReadFile( Json::Value* root,const char* filepath )
{
	std::string stream;
	std::ifstream jsonfile (filepath);
	if (jsonfile.is_open())
	{
		std::string line;
		while ( getline (jsonfile,line) )
		{
			stream += line;
			stream += '\n';
		}
		jsonfile.close();
	}else{
		std::cout  << "[Message] Failed to open File < "<<filepath<<" >\n";
		return false;
	}
	jsonfile.close();
	return ReadStream(root,stream);
	Json::Reader reader;
}

//************************************
// Method:    ReadStream
// FullName:  JsonApp::ReadStream
// Access:    public 
// Returns:   bool
// Qualifier: Pass stream to Json Reader
// Parameter: Json::Value * root
// Parameter: std::string stream
//************************************
bool JsonApp::ReadStream( Json::Value* root,std::string& stream )
{
	Json::Reader reader;
	// will contains the root value after parsing.
	bool parsingSuccessful = reader.parse( stream, *root );
	if ( !parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		std::cout  << "[Message] Failed to parse configuration\n";
		return false;
	}else{
		return true;
	}
}

bool JsonApp::WriteFile( Json::Value& root,const char* filepath,int mode )
{

	std::ofstream jsonfile (filepath);
	if (mode==0)
	{
		Json::FastWriter writer;
		jsonfile<<writer.write(root);
	}else{
		Json::StyledWriter writer;
		jsonfile<<writer.write(root);
	}
	jsonfile.close();
	
	return true;
}