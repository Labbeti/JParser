#pragma once

#include <ostream>
#include <vector>

class JsonValue;

class JsonArray : public std::vector<JsonValue>
{
public: // Constructors & Destructors
	~JsonArray();

public: // Friends
	friend std::ostream& operator<<(std::ostream& os, JsonArray const& jsonArray);
};

std::ostream& operator<<(std::ostream& os, JsonArray const& jsonArray);