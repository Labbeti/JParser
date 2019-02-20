#include "JsonValue.hpp"
#include "JsonArray.hpp"
#include "JsonNumber.hpp"
#include "JsonObject.hpp"
#include "JsonString.hpp"
#include <iostream>

// begin class JsonValue
JsonValue::JsonValue() :
	array_{},
	number_{},
	object_{},
	string_{},
	literal_{ LiteralType::NONE }
{}
JsonValue::JsonValue(JsonArray const& jsonArray) :
	JsonValue{}
{
	array_ = jsonArray;
}
JsonValue::JsonValue(JsonNumber const& jsonNumber) :
	JsonValue{}
{
	number_ = jsonNumber;
}
JsonValue::JsonValue(JsonObject const& jsonObject) :
	JsonValue{}
{
	object_ = jsonObject;
}
JsonValue::JsonValue(JsonString const& jsonString) :
	JsonValue{}
{
	string_ = jsonString;
}
JsonValue::JsonValue(BooleanType value) :
	JsonValue{}
{
	literal_ = ( value ? LiteralType::TRUE : LiteralType::FALSE );
}
JsonValue::JsonValue(std::nullptr_t nullp) :
	JsonValue{}
{
	literal_ = LiteralType::NULLPTR;
}

JsonValue::~JsonValue() = default;

JsonValue& JsonValue::operator=(BooleanType value)
{
	clear();
	literal_ = (value ? LiteralType::TRUE : LiteralType::FALSE);
	return *this;
}
JsonValue& JsonValue::operator=(std::nullptr_t nullp)
{
	clear();
	literal_ = LiteralType::NULLPTR;
	return *this;
}
JsonValue& JsonValue::operator=(std::string const& string)
{
	clear();
	string_ = string;
	return *this;
}
JsonValue& JsonValue::operator[](unsigned i)
{
	if (not isArray())
		throw std::runtime_error{ "Cannot use operator[](unsigned) on this json value. " + debugState() };
	return (*array_)[i];
}
JsonValue& JsonValue::operator[](JsonString const& jsonString)
{
	if (not isObject())
		throw std::runtime_error{ "Cannot use operator[](JsonString) on this json value. " + debugState() };
	return (*object_)[jsonString];
}
bool JsonValue::operator==(JsonValue const& other) const
{
	return array_ == other.array_ and number_ == other.number_ and object_ == other.object_ and string_ == other.string_ and literal_ == other.literal_;
}

JsonValue::operator JsonArray const&() const
{
	if (not isArray())
		throw std::runtime_error{ "Cannot use JsonArray() on this json value. " + debugState() };
	return *array_;
}
JsonValue::operator JsonObject const&() const
{
	if (not isObject())
		throw std::runtime_error{ "Cannot use JsonObject() on this json value. " + debugState() };
	return *object_;
}
JsonValue::operator JsonArray&()
{
	if (not isArray())
		throw std::runtime_error{ "Cannot use JsonArray() on this json value. " + debugState() };
	return *array_;
}
JsonValue::operator JsonObject&()
{
	if (not isObject())
		throw std::runtime_error{ "Cannot use JsonObject() on this json value. " + debugState() };
	return *object_;
}
JsonValue::operator JsonNumber() const
{
	if (not isNumber())
		throw std::runtime_error{ "Cannot use JsonNumber() on this json value. " + debugState() };
	return *number_;
}
JsonValue::operator JsonString() const
{
	if (not isString())
		throw std::runtime_error{ "Cannot use JsonString() on this json value. " + debugState() };
	return *string_;
}
JsonValue::operator bool() const
{
	if (not isTrue() and not isFalse())
		throw std::runtime_error{ "Cannot use JsonString() on this json value. " + debugState() };
	return literal_ == LiteralType::TRUE;
}
JsonValue::operator std::nullptr_t() const
{
	if (not isNull())
		throw std::runtime_error{ "Cannot use nullptr_t() on this json value. " + debugState() };
	return nullptr;
}
JsonValue::operator StringType() const
{
	if (not isString())
		throw std::runtime_error{ "Cannot use string() on this json value. " + debugState() };
	return *string_;
}
JsonValue::operator NumberType() const
{
	if (not isNumber())
		throw std::runtime_error{ "Cannot use number() on this json value. " + debugState() };
	return static_cast<NumberType>(*number_);
}
JsonValue::operator unsigned() const
{
	if (not isNumber())
		throw std::runtime_error{ "Cannot use number() on this json value. " + debugState() };
	return static_cast<unsigned>(*number_);
}
JsonValue::operator int() const
{
	if (not isNumber())
		throw std::runtime_error{ "Cannot use int() on this json value. " + debugState() };
	return static_cast<int>(*number_);
}
JsonValue::operator float() const
{
	if (not isNumber())
		throw std::runtime_error{ "Cannot use int() on this json value. " + debugState() };
	return static_cast<float>(*number_);
}

JsonObject::iterator JsonValue::begin()
{
	if (not isObject())
		throw std::runtime_error{ "Cannot use begin() on this json value. " + debugState() };
	return object_->begin();
}
JsonObject::iterator JsonValue::end()
{
	if (not isObject())
		throw std::runtime_error{ "Cannot use end() on this json value. " + debugState() };
	return object_->end();
}
bool JsonValue::isArray() const
{
	return array_.has_value();
}
bool JsonValue::isNumber() const
{
	return number_.has_value();
}
bool JsonValue::isObject() const
{
	return object_.has_value();
}
bool JsonValue::isString() const
{
	return string_.has_value();
}
bool JsonValue::isLiteral() const
{
	return isTrue() or isFalse() or isNull();
}
bool JsonValue::isTrue() const
{
	return literal_ == LiteralType::TRUE;
}
bool JsonValue::isFalse() const
{
	return literal_ == LiteralType::FALSE;
}
bool JsonValue::isNull() const
{
	return literal_ == LiteralType::NULLPTR;
}

void JsonValue::clear()
{
	array_.reset();
	number_.reset();
	object_.reset();
	string_.reset();
	literal_ = LiteralType::NONE;
}
std::string JsonValue::debugState() const
{
	return "JsonValue(str=" + std::to_string(isArray()) + ", num=" + std::to_string(isNumber()) + ", obj=" + std::to_string(isObject()) + ", str=" + std::to_string(isString()) + ", lit=" + std::to_string(isLiteral()) + ")";
}
// end class JsonValue

std::ostream& operator<<(std::ostream& os, JsonValue const& jsonValue)
{
	if (jsonValue.isString())
		os << *jsonValue.string_;
	else if (jsonValue.isNumber())
		os << *jsonValue.number_;
	else if (jsonValue.isObject())
		os << *jsonValue.object_;
	else if (jsonValue.isArray())
		os << *jsonValue.array_;
	else if (jsonValue.isNull())
		os << "null";
	else if (jsonValue.isTrue())
		os << "true";
	else if (jsonValue.isFalse())
		os << "false";
	else
		throw std::runtime_error{ "Cannot display an unknown JsonValue." };
	return os;
}
