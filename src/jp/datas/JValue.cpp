#include "JValue.hpp"
#include <iostream>
#include "JArray.hpp"
#include "JNumber.hpp"
#include "JObject.hpp"
#include "JString.hpp"

// begin class JValue
jp::JValue::JValue() :
	array_{},
	number_{},
	object_{},
	string_{},
	literal_{ LiteralType::NONE }
{}
jp::JValue::JValue(JArray const& jsonArray) :
	JValue{}
{
	array_ = jsonArray;
}
jp::JValue::JValue(JNumber const& jsonNumber) :
	JValue{}
{
	number_ = jsonNumber;
}
jp::JValue::JValue(JObject const& jsonObject) :
	JValue{}
{
	object_ = jsonObject;
}
jp::JValue::JValue(JString const& jsonString) :
	JValue{}
{
	string_ = jsonString;
}
jp::JValue::JValue(std::nullptr_t nullp) :
	JValue{}
{
	literal_ = LiteralType::NULLPTR;
}
jp::JValue::JValue(bool value) :
	JValue{}
{
	literal_ = (value ? LiteralType::TRUE : LiteralType::FALSE);
}

jp::JValue::~JValue() = default;

jp::JValue& jp::JValue::operator=(std::nullptr_t nullp)
{
	clear();
	literal_ = LiteralType::NULLPTR;
	return *this;
}
jp::JValue& jp::JValue::operator=(bool value)
{
	clear();
	literal_ = (value ? LiteralType::TRUE : LiteralType::FALSE);
	return *this;
}
jp::JValue& jp::JValue::operator=(std::string const& string)
{
	clear();
	string_ = string;
	return *this;
}
jp::JValue& jp::JValue::operator[](unsigned i)
{
	if (not isArray())
		throw std::runtime_error{ "Cannot use operator[](unsigned) on this json value. " + debugState() };
	return (*array_)[i];
}
jp::JValue& jp::JValue::operator[](JString const& jsonString)
{
	if (not isObject())
		throw std::runtime_error{ "Cannot use operator[](JString) on this json value. " + debugState() };
	return (*object_)[jsonString];
}
bool jp::JValue::operator==(jp::JValue const& other) const
{
	return array_ == other.array_ and number_ == other.number_ and object_ == other.object_ and string_ == other.string_ and literal_ == other.literal_;
}

jp::JValue::operator jp::JArray const&() const
{
	if (not isArray())
		throw std::runtime_error{ "Cannot use JArray() on this json value. " + debugState() };
	return *array_;
}
jp::JValue::operator jp::JObject const&() const
{
	if (not isObject())
		throw std::runtime_error{ "Cannot use JObject() on this json value. " + debugState() };
	return *object_;
}
jp::JValue::operator jp::JArray&()
{
	if (not isArray())
		throw std::runtime_error{ "Cannot use JArray() on this json value. " + debugState() };
	return *array_;
}
jp::JValue::operator jp::JObject&()
{
	if (not isObject())
		throw std::runtime_error{ "Cannot use JObject() on this json value. " + debugState() };
	return *object_;
}
jp::JValue::operator jp::JNumber() const
{
	if (not isNumber())
		throw std::runtime_error{ "Cannot use JNumber() on this json value. " + debugState() };
	return *number_;
}
jp::JValue::operator jp::JString() const
{
	if (not isString())
		throw std::runtime_error{ "Cannot use JString() on this json value. " + debugState() };
	return *string_;
}
jp::JValue::operator std::nullptr_t() const
{
	if (not isNull())
		throw std::runtime_error{ "Cannot use nullptr_t() on this json value. " + debugState() };
	return nullptr;
}
jp::JValue::operator bool() const
{
	if (not isTrue() and not isFalse())
		throw std::runtime_error{ "Cannot use JString() on this json value. " + debugState() };
	return literal_ == LiteralType::TRUE;
}
jp::JValue::operator std::string() const
{
	if (not isString())
		throw std::runtime_error{ "Cannot use string() on this json value. " + debugState() };
	return *string_;
}
jp::JValue::operator Real() const
{
	if (not isNumber())
		throw std::runtime_error{ "Cannot use double() on this json value. " + debugState() };
	return *number_;
}

bool jp::JValue::isArray() const
{
	return array_.has_value();
}
bool jp::JValue::isNumber() const
{
	return number_.has_value();
}
bool jp::JValue::isObject() const
{
	return object_.has_value();
}
bool jp::JValue::isString() const
{
	return string_.has_value();
}
bool jp::JValue::isLiteral() const
{
	return isTrue() or isFalse() or isNull();
}
bool jp::JValue::isTrue() const
{
	return literal_ == LiteralType::TRUE;
}
bool jp::JValue::isFalse() const
{
	return literal_ == LiteralType::FALSE;
}
bool jp::JValue::isNull() const
{
	return literal_ == LiteralType::NULLPTR;
}

void jp::JValue::clear()
{
	array_.reset();
	number_.reset();
	object_.reset();
	string_.reset();
	literal_ = LiteralType::NONE;
}
std::string jp::JValue::debugState() const
{
	return "JValue(str=" + std::to_string(isArray()) + ", num=" + std::to_string(isNumber()) + ", obj=" + std::to_string(isObject()) + ", str=" + std::to_string(isString()) + ", lit=" + std::to_string(isLiteral()) + ")";
}
// end class JValue

std::ostream& jp::operator<<(std::ostream& os, jp::JValue const& jsonValue)
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
		throw std::runtime_error{ "Cannot display an unknown JValue." };
	return os;
}
