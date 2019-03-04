#pragma once

#include <functional>

namespace jp
{
	class JString;
}

namespace std
{
	template<> struct hash<jp::JString>
	{
		std::size_t operator()(jp::JString const& jsonString) const noexcept;
	};
};
