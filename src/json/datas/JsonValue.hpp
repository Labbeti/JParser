#pragma once

#include "DataType.hpp"
#include <optional>
#include <string>
#include "JsonArray.hpp"
#include "JsonString.hpp"
#include "JsonNumber.hpp"
#include "JsonObject.hpp"

class JsonValue
{
public: // Constructors
	JsonValue();
	JsonValue(JsonArray const& jsonArray);
	JsonValue(JsonNumber const& jsonNumber);
	JsonValue(JsonObject const& jsonObject);
	JsonValue(JsonString const& jsonString);
	JsonValue(BooleanType value);
	JsonValue(std::nullptr_t nullp);

public: // Destructor
	~JsonValue();

private: // Types
	enum class LiteralType
	{
		NONE,
		TRUE,
		FALSE,
		NULLPTR
	};

public: // Methods operators
	JsonValue& operator=(BooleanType value);
	JsonValue& operator=(std::nullptr_t nullp);
	JsonValue& operator=(std::string const& string);
	JsonValue& operator[](unsigned i);
	JsonValue& operator[](JsonString const& jsonString);
	bool operator==(JsonValue const& other) const;

	// Note: Use references for avoid copy of these structures
	operator JsonArray const&() const;
	operator JsonObject const&() const;
	operator JsonArray&();
	operator JsonObject&();
	operator JsonNumber() const;
	operator JsonString() const;
	operator bool() const;
	operator std::nullptr_t() const;
	operator StringType() const;
	operator NumberType() const;
	operator unsigned() const;
	operator int() const;
	operator float() const;
	
private: // Methods getters
	JsonObject::iterator begin();
	JsonObject::iterator end();
	bool isArray() const;
	bool isNumber() const;
	bool isObject() const;
	bool isString() const;
	bool isLiteral() const;
	bool isTrue() const;
	bool isFalse() const;
	bool isNull() const;

private: // Methods
	void clear();
	std::string debugState() const;

public: // Friends
	friend std::ostream& operator<<(std::ostream& os, JsonValue const& jsonValue);

private: // Attributes
	std::optional<JsonArray> array_;
	std::optional<JsonNumber> number_;
	std::optional<JsonObject> object_;
	std::optional<JsonString> string_;
	LiteralType literal_;
};
