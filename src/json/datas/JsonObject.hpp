#pragma once

#include <ostream>
#include <unordered_map>

class JsonString;
class JsonValue;
#include "JsonStringHash.hpp"

class JsonObject : public std::unordered_map<JsonString, JsonValue>
{
public: // Constructors & Destructors
	~JsonObject();

public: // Methods
	JsonValue& operator[](JsonString const& jString);
	JsonValue const& operator[](JsonString const& jString) const;

public: // Friends
	friend std::ostream& operator<<(std::ostream& os, JsonObject const& jsonObject);
};

std::ostream& operator<<(std::ostream& os, JsonObject const& jsonObject);