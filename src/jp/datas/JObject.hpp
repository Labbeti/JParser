#pragma once

#include "JStringHash.hpp"
#include <ostream>
#include <unordered_map>

namespace jp
{
	class JString;
	class JValue;

	class JObject : public std::unordered_map<JString, JValue>
	{
	public: // Constructors & Destructors
		~JObject();

	public: // Methods
		JValue& operator[](JString const& jString);
		JValue const& operator[](JString const& jString) const;

	public: // Friends
		friend std::ostream& operator<<(std::ostream& os, JObject const& jsonObject);
	};
}
