#include "JArray.hpp"
#include "JValue.hpp"

// begin class JArray
jp::JArray::~JArray() = default;
// end class JArray

std::ostream& jp::operator<<(std::ostream& os, jp::JArray const& jsonArray)
{
	os << "[";
	unsigned i{ 0 };
	for (auto& value : jsonArray)
	{
		os << value;
		if (i + 1 < jsonArray.size())
			os << ", ";
		++i;
	}
	os << "]";
	return os;
}