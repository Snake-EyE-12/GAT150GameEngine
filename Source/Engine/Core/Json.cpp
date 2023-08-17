#include "Json.h"
#include "Logger.h"
#include "FileIO.h"
#include "rapidjson/include/rapidjson/istreamwrapper.h"
#include <sstream>
#include <iostream>
namespace cg
{
	bool Json::Load(const std::string& filename, rapidjson::Document& document)
	{
		std::string buffer;
		if (!readFile(filename, buffer))
		{
			WARNING_LOG("Cannot open file: " << filename);
			return false;
		}
		std::stringstream stream(buffer);
		rapidjson::IStreamWrapper istream(stream);
		// parse stream to json
		document.ParseStream(istream);
		if (!document.IsObject())
		{
			WARNING_LOG("Json file cannot be parsed: " << filename);
			return false;
		}
		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string& name, int& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		data = value[name.c_str()].GetInt();
		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string& name, float& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsFloat())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		data = value[name.c_str()].GetFloat();
		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		data = value[name.c_str()].GetBool();
		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required)
	{
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString())
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		data = value[name.c_str()].GetString();
		return true;
	}
	bool Json::Read(const rapidjson::Value& value, const std::string& name, Vector2& data, bool required)
	{
		// check if 'name' member exists and is an array with 2 elements
		//std::cout << value.HasMember(name.c_str()) << value[name.c_str()].IsArray() << (value[name.c_str()].Size() != 2) << std::endl;
		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2)
		{
			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		}
		// create json array object
		auto& array = value[name.c_str()];
		// get array values
		for (rapidjson::SizeType i = 0; i < array.Size(); i++)
		{
			if (!array[i].IsNumber())
			{
				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			}
			data[i] = array[i].GetFloat();
		}
		return true;
	}
}