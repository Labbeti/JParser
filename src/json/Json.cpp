#include "Json.hpp"
#include "datas/JsonArray.hpp"
#include "datas/JsonNumber.hpp"
#include "datas/JsonObject.hpp"
#include "datas/JsonString.hpp"
#include "datas/JsonValue.hpp"
#include <fstream>
#include "JsonDataType.hpp"
#include <stack>
#include <util/fct/str_fct.hpp>

// begin local functions
template<class T>
bool pop_stack(std::stack<T>& jDatas, JsonValue& jsonValue)
{
	if (jDatas.empty())
		return false;
	jsonValue = jDatas.top();
	jDatas.pop();
	return true;
}
bool set_value(JsonValue& jsonValue, JsonDataType type, 
	std::stack<JsonArray>& jArrays,
	std::stack<JsonNumber>& jNumbers,
	std::stack<JsonObject>& jObjects,
	std::stack<JsonString>& jStrings,
	std::stack<JsonValue>& jValues)
{
	switch (type)
	{
	case JsonDataType::ARRAY:
		return pop_stack(jArrays, jsonValue);
	case JsonDataType::NUMBER:
		return pop_stack(jNumbers, jsonValue);
	case JsonDataType::OBJECT:
		return pop_stack(jObjects, jsonValue);
	case JsonDataType::STRING:
		return pop_stack(jStrings, jsonValue);
	case JsonDataType::VALUE:
		return pop_stack(jValues, jsonValue);
	default:
		return false;
	}
}
// end local functions

// begin class Json
Json::Json(std::string const& filepath) :
	data_{ new JsonObject{} },
	lexer_{},
	filepath_{ filepath }
{
	if (not filepath.empty())
	{
		std::ifstream file{ filepath };
		if (file.is_open())
		{
			readFromStream(file);
			file.close();
		}
	}
}
bool Json::readFromStream(std::istream& is)
{
	clear();
	lexer_.setStream(is);

	std::stack<JsonDataType> lastUpdStd;

	std::stack<JsonNumber> jNumbers;
	std::stack<JsonString> jStrings;
	std::stack<JsonArray> jArrays;
	std::stack<JsonObject> jObjects;
	std::stack<JsonValue> jValues;

	std::stack<JsonDataType> lastContainer;
	std::vector<std::vector<std::pair<JsonString, JsonValue>>> objectPairValues;
	std::vector<std::vector<JsonValue>> arrayValues;

	while (not lexer_.end())
	{
		auto token = lexer_.nextToken();
		//std::cout << "DEBUG: json: token = " << token << std::endl; // TODO : enlever

		if (is_double(token))
		{
			jNumbers.push(JsonNumber{ std::stod(token) });
			lastUpdStd.push(JsonDataType::NUMBER);
		}
		else if (is_string(token))
		{
			jStrings.push(JsonString{ token.substr(1, token.size() - 2) });
			lastUpdStd.push(JsonDataType::STRING);
		}
		else if (token == "null" or token == "true" or token == "false")
		{
			JsonValue jsonValue;
			if (token == "null")
				jsonValue = nullptr;
			else
				jsonValue = (token == "true");

			jValues.push(jsonValue);
			lastUpdStd.push(JsonDataType::VALUE);
		}
		else if (token == ":")
		{
			objectPairValues.back().push_back(std::make_pair( jStrings.top(), JsonValue{} ));
			jStrings.pop();
		}
		else if (token == ",")
		{
			if (lastContainer.top() == JsonDataType::OBJECT)
			{
				auto& lastPair = objectPairValues.back().back();
				set_value(lastPair.second, lastUpdStd.top(), jArrays, jNumbers, jObjects, jStrings, jValues);
			}
			else if (lastContainer.top() == JsonDataType::ARRAY)
			{
				JsonValue jsonValue;
				set_value(jsonValue, lastUpdStd.top(), jArrays, jNumbers, jObjects, jStrings, jValues);
				arrayValues.back().push_back(jsonValue);
			}
		}
		else if (token == "{")
		{
			objectPairValues.push_back({});
			lastContainer.push(JsonDataType::OBJECT);
		}
		else if (token == "}")
		{
			JsonObject jObject;
			// If the last object is empty, create an empty JsonObject
			if (not objectPairValues.back().empty())
			{
				auto& lastPair = objectPairValues.back().back();
				set_value(lastPair.second, lastUpdStd.top(), jArrays, jNumbers, jObjects, jStrings, jValues);

				for (auto& pair : objectPairValues.back())
				{
					jObject.emplace(pair.first, pair.second);
				}
			}
			jObjects.push(jObject);
			lastUpdStd.push(JsonDataType::OBJECT);
			lastContainer.pop();
			objectPairValues.pop_back();
		}
		else if (token == "[")
		{
			arrayValues.push_back({});
			lastContainer.push(JsonDataType::ARRAY);
		}
		else if (token == "]")
		{
			JsonValue jsonValue;
			bool isSet = set_value(jsonValue, lastUpdStd.top(), jArrays, jNumbers, jObjects, jStrings, jValues);
			if (isSet)
				arrayValues.back().push_back(jsonValue);

			JsonArray jArray;
			for (auto& elt : arrayValues.back())
			{
				jArray.push_back(elt);
			}
			jArrays.push(jArray);
			lastUpdStd.push(JsonDataType::ARRAY);
			lastContainer.pop();
			arrayValues.pop_back();
		}
	}

	if (jObjects.empty())
	{
		return false;
	}

	data_.reset(new JsonObject{ jObjects.top() });
	return true;
}
void Json::writeInStream(std::ostream& os) const
{
	os << data_;
}
void Json::clear()
{
	data_.reset(new JsonObject{});
}
JsonObject::iterator Json::begin() const
{
	return data_->begin();
}
JsonObject::iterator Json::end() const
{
	return data_->end();
}
bool Json::empty() const
{
	return data_->empty();
}
JsonObject const& Json::content() const
{
	return *data_;
}
JsonObject& Json::content()
{
	return *data_;
}
// end class Json

std::ostream& operator<<(std::ostream& os, Json const& json)
{
	os << *json.data_ << "\n";
	return os;
}