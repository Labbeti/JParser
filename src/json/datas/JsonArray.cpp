#include "JsonArray.hpp"
#include "JsonValue.hpp"

// begin class JsonArray
JsonArray::~JsonArray() = default;
// end class JsonArray

std::ostream& operator<<(std::ostream& os, JsonArray const& jsonArray)
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