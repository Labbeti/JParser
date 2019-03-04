#include "JFile.hpp"
#include "AllJDatas.hpp"
#include <fstream>
#include <iostream>
#include <stack>
#include <fct/str_fct.hpp>

// local type
enum class JDataType
{
	ARRAY,
	NUMBER,
	OBJECT,
	STRING,
	VALUE
};
// begin local functions
template<class T>
bool pop_stack(std::stack<T>& jDatas, jp::JValue& jValue)
{
	if (jDatas.empty())
		return false;
	jValue = jDatas.top();
	jDatas.pop();
	return true;
}
bool set_value(jp::JValue& jValue, JDataType type,
	std::stack<jp::JArray>& jArrays,
	std::stack<jp::JNumber>& jNumbers,
	std::stack<jp::JObject>& jObjects,
	std::stack<jp::JString>& jStrings,
	std::stack<jp::JValue>& jValues)
{
	switch (type)
	{
	case JDataType::ARRAY:
		return pop_stack(jArrays, jValue);
	case JDataType::NUMBER:
		return pop_stack(jNumbers, jValue);
	case JDataType::OBJECT:
		return pop_stack(jObjects, jValue);
	case JDataType::STRING:
		return pop_stack(jStrings, jValue);
	case JDataType::VALUE:
		return pop_stack(jValues, jValue);
	default:
		return false;
	}
}
// end local functions

// begin class Json
jp::JFile::JFile(std::string const& filepath) :
	data_{ new JObject{} },
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
bool jp::JFile::readFromStream(std::istream& is)
{
	clear();
	lexer_.setStream(is);

	std::stack<JDataType> lastUpdStd;

	std::stack<JNumber> jNumbers;
	std::stack<JString> jStrings;
	std::stack<JArray> jArrays;
	std::stack<JObject> jObjects;
	std::stack<JValue> jValues;

	std::stack<JDataType> lastContainer;
	std::vector<std::vector<std::pair<JString, JValue>>> objectPairValues;
	std::vector<std::vector<JValue>> arrayValues;

	while (not lexer_.end())
	{
		auto token = lexer_.nextToken();
		//std::cout << "DEBUG: json: token = " << token << std::endl; // TODO : enlever

		if (is_double(token))
		{
			jNumbers.push(JNumber{ std::stod(token) });
			lastUpdStd.push(JDataType::NUMBER);
		}
		else if (is_string(token))
		{
			jStrings.push(JString{ token.substr(1, token.size() - 2) });
			lastUpdStd.push(JDataType::STRING);
		}
		else if (token == "null" or token == "true" or token == "false")
		{
			JValue jsonValue;
			if (token == "null")
				jsonValue = nullptr;
			else
				jsonValue = (token == "true");

			jValues.push(jsonValue);
			lastUpdStd.push(JDataType::VALUE);
		}
		else if (token == ":")
		{
			objectPairValues.back().push_back(std::make_pair( jStrings.top(), JValue{} ));
			jStrings.pop();
		}
		else if (token == ",")
		{
			if (lastContainer.top() == JDataType::OBJECT)
			{
				auto& lastPair = objectPairValues.back().back();
				bool isSet = set_value(lastPair.second, lastUpdStd.top(), jArrays, jNumbers, jObjects, jStrings, jValues);
				if (not isSet)
					throw std::runtime_error{ "Error when reading json stream." };
			}
			else if (lastContainer.top() == JDataType::ARRAY)
			{
				JValue jsonValue;
				bool isSet = set_value(jsonValue, lastUpdStd.top(), jArrays, jNumbers, jObjects, jStrings, jValues);
				if (not isSet)
				{
					throw std::runtime_error{ "Error when reading json stream." };
				}
				arrayValues.back().push_back(jsonValue);
			}
		}
		else if (token == "{")
		{
			objectPairValues.push_back({});
			lastContainer.push(JDataType::OBJECT);
		}
		else if (token == "}")
		{
			JObject jObject;
			// If the last object is empty, create an empty JObject
			if (not objectPairValues.back().empty())
			{
				auto& lastPair = objectPairValues.back().back();
				bool isSet = set_value(lastPair.second, lastUpdStd.top(), jArrays, jNumbers, jObjects, jStrings, jValues);
				if (not isSet)
				{
					throw std::runtime_error{ "Error when reading json stream." };
				}
				for (auto& pair : objectPairValues.back())
				{
					jObject.emplace(pair.first, pair.second);
				}
			}
			jObjects.push(jObject);
			lastUpdStd.push(JDataType::OBJECT);
			lastContainer.pop();
			objectPairValues.pop_back();
		}
		else if (token == "[")
		{
			arrayValues.push_back({});
			lastContainer.push(JDataType::ARRAY);
		}
		else if (token == "]")
		{
			JValue jsonValue;
			bool isSet = set_value(jsonValue, lastUpdStd.top(), jArrays, jNumbers, jObjects, jStrings, jValues);
			// Do not push jsonValue is not set (case if we have an empty json array like : "[ ]")
			if (isSet)
				arrayValues.back().push_back(jsonValue);

			JArray jArray;
			for (auto& elt : arrayValues.back())
			{
				jArray.push_back(elt);
			}
			jArrays.push(jArray);
			lastUpdStd.push(JDataType::ARRAY);
			lastContainer.pop();
			arrayValues.pop_back();
		}
		else
		{
			throw std::runtime_error{ "Found incorrect token." };
		}
	}
	if (not (jArrays.empty() and jNumbers.empty() and jStrings.empty() and jValues.empty()))
	{
		std::cout << "DEBUG: json.c: ERROR" << "\n";
		throw std::runtime_error{ "Found error when finished to read stream." };
	}
	if (jObjects.empty())
	{
		return false;
	}

	data_.reset(new JObject{ jObjects.top() });
	return true;
}
void jp::JFile::writeInStream(std::ostream& os) const
{
	os << *data_;
}
void jp::JFile::saveInFile(std::string const& filepath) const
{
	std::ofstream file{ filepath };
	writeInStream(file);
	file.close();
}
void jp::JFile::clear()
{
	data_.reset(new JObject{});
}
bool jp::JFile::empty() const
{
	return data_->empty();
}
jp::JObject const& jp::JFile::content() const
{
	return *data_;
}
jp::JObject& jp::JFile::content()
{
	return *data_;
}
// end class Json

std::ostream& jp::operator<<(std::ostream& os, jp::JFile const& json)
{
	os << *json.data_ << "\n";
	return os;
}
