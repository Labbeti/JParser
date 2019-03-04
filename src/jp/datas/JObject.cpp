#include "JObject.hpp"
#include "JString.hpp"
#include "JValue.hpp"

// begin class JObject
jp::JObject::~JObject() = default;
jp::JValue& jp::JObject::operator[](jp::JString const& jString)
{
	return this->std::unordered_map<jp::JString, jp::JValue>::operator[](jString);
}
jp::JValue const& jp::JObject::operator[](jp::JString const& jString) const
{
	return this->std::unordered_map<jp::JString, jp::JValue>::at(jString);
}
// end class JObject

std::ostream& jp::operator<<(std::ostream& os, jp::JObject const& jsonObject)
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
	os << " } ";
	return os;
}
