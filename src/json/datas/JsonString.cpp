#include "JsonString.hpp"

// begin class JsonString
JsonString::JsonString(char const* cString) :
	StringType{ cString }
{}
JsonString::JsonString(StringType const& string) :
	StringType{ string }
{}
JsonString::~JsonString() = default;
// end class JsonString

std::ostream& operator<<(std::ostream& os, JsonString const& jsonString)
{
	return (os << "\"" << std::string(jsonString) << "\"");
}
