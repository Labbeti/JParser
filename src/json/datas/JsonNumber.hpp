#pragma once

#include "DataType.hpp"
#include <ostream>

class JsonNumber
{
public: // Constructors & Destructors
	JsonNumber(NumberType number);
	~JsonNumber();

public: // Methods
	JsonNumber& operator=(NumberType number);
	bool operator==(JsonNumber const& other) const;
	operator NumberType() const;
	operator unsigned() const;
	operator int() const;
	operator float() const;

public: // Friends
	friend std::ostream& operator<<(std::ostream& os, JsonNumber const& jsonNumber);
	
private: // Attributes
	NumberType number_;
};

std::ostream& operator<<(std::ostream& os, JsonNumber const& jsonNumber);