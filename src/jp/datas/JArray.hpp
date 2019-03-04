#pragma once

#include <ostream>
#include <vector>

namespace jp
{
	class JValue;

	class JArray : public std::vector<JValue>
	{
	public: // Constructors & Destructors
		~JArray();

	public: // Friends
		friend std::ostream& operator<<(std::ostream& os, JArray const& jsonArray);
	};
}
