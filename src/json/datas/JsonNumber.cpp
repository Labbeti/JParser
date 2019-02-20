#include "JsonNumber.hpp"

// begin class JsonNumber
JsonNumber::JsonNumber(NumberType number) :
	number_{ number }
{}
JsonNumber::~JsonNumber() = default;

JsonNumber& JsonNumber::operator=(NumberType number)
{
	number_ = number;
	return *this;
}
bool JsonNumber::operator==(JsonNumber const& other) const
{
	return number_ == other.number_;
}
JsonNumber::operator NumberType() const
{
	return number_;
}
JsonNumber::operator unsigned() const
{
	return static_cast<unsigned>(number_);
}
JsonNumber::operator int() const
{
	return static_cast<int>(number_);
}
JsonNumber::operator float() const
{
	return static_cast<float>(number_);
}
// end class JsonNumber

std::ostream& operator<<(std::ostream& os, JsonNumber const& jsonNumber)
{
	os << jsonNumber.number_;
	return os;
}
