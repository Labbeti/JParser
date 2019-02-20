#include "JsonObject.hpp"
#include "JsonString.hpp"
#include "JsonValue.hpp"

// begin class JsonObject
JsonObject::~JsonObject() = default;
JsonValue& JsonObject::operator[](JsonString const& jString)
{
	return this->std::unordered_map<JsonString, JsonValue>::operator[](jString);
}
JsonValue const& JsonObject::operator[](JsonString const& jString) const
{
	return this->std::unordered_map<JsonString, JsonValue>::at(jString);
}
// end class JsonObject

std::ostream& operator<<(std::ostream& os, JsonObject const& jsonObject)
{
	os << "{ ";
	unsigned i{ 0 };
	for (auto it = jsonObject.begin() ; it != jsonObject.end() ; ++it)
	{
		os << it->first << " : " << it->second;
		if (i + 1 < jsonObject.size())
			os << ", ";
		++i;
	}
	os << "} ";
	return os;
}
