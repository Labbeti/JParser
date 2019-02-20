#include "JsonStringHash.hpp"
#include "JsonString.hpp"

std::size_t std::hash<JsonString>::operator()(JsonString const& jsonString) const noexcept
{
	return std::hash<std::string>{}(jsonString);
}
