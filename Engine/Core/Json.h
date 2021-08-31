#pragma once
#include "document.h"
#include <string>
#include<vector>
#include <fstream>
#include "istreamwrapper.h"
#include "Math/Color.h"
#include "Math/Vector2.h"


#define JSON_READ(value,data)jc::json::Get(value, #data, data);



namespace jc
{
	namespace json
	{
		bool Load(const std::string& filename, rapidjson::Document& document);
		bool Get(const rapidjson::Value& value, const std::string& name, int& data);

		bool Get(const rapidjson::Value& value, const std::string& name, float& data);
		bool Get(const rapidjson::Value& value, const std::string& name, bool& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::string& data);
		bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data);
		bool Get(const rapidjson::Value& value, const std::string& name, Color& data);
		bool Get(const rapidjson::Value& value, const std::string& name, SDL_Rect& data);

		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data);
		bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data);


	}
}

namespace jc
{
	namespace json
	{
	}
}
