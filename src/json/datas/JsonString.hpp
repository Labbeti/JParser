#pragma once

#include "DataType.hpp"
#include <ostream>
#include <string>

class JsonString : public StringType
{
public: // Constructors & Destructors
	JsonString(char const* cString);
	JsonString(StringType const& string);
	~JsonString();

public: // Friends
	friend std::ostream& operator<<(std::ostream& os, JsonString const& jsonString);
	friend struct std::hash<JsonString>;
};

std::ostream& operator<<(std::ostream& os, JsonString const& jsonString);
