#include "JStringHash.hpp"
#include "JString.hpp"

std::size_t std::hash<jp::JString>::operator()(jp::JString const& jsonString) const noexcept
{
	return std::hash<std::string>{}(jsonString);
}
