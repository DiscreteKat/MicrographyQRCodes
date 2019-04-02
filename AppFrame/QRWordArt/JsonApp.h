#pragma once
#include <json\json.h>
//************************************
// Namespace:   JsonApp
// Qualifier:	Deal with Json I/O
//************************************
namespace JsonApp
{
	bool ReadFile(Json::Value* root,const char* filepath);
	bool ReadStream(Json::Value* root,std::string& stream);

	bool WriteFile(Json::Value& root,const char* filepath,int mode=0);
};

