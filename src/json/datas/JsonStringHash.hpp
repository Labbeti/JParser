#pragma once

#include <functional>

class JsonString;

namespace std
{
	template<> struct hash<JsonString>
	{
		std::size_t operator()(JsonString const& jsonString) const noexcept;
	};
};
