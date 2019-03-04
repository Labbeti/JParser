#pragma once

#include <ostream>
#include <string>

namespace jp
{
	class JString : public std::string
	{
	public: // Constructors & Destructor
		JString(char const* cString);
		JString(std::string const& string);
		~JString();

	public: // Friends
		friend std::ostream& operator<<(std::ostream& os, JString const& jsonString);
		friend struct std::hash<JString>;
	};
}
