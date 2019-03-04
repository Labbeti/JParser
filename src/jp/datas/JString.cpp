#include "JString.hpp"

// begin class JString
jp::JString::JString(char const* cString) :
	std::string{ cString }
{}
jp::JString::JString(std::string const& string) :
	std::string{ string }
{}
jp::JString::~JString() = default;
// end class JString

std::ostream& jp::operator<<(std::ostream& os, jp::JString const& jsonString)
{
	return (os << "\"" << std::string(jsonString) << "\"");
}
