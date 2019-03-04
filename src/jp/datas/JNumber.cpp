#include "JNumber.hpp"

// begin class JNumber
jp::JNumber::JNumber(Real number) :
	number_{ number }
{}
jp::JNumber::JNumber(unsigned number) :
	number_{ static_cast<Real>(number) }
{}
jp::JNumber::~JNumber() = default;

jp::JNumber& jp::JNumber::operator=(Real number)
{
	number_ = number;
	return *this;
}
bool jp::JNumber::operator==(JNumber const& other) const
{
	return number_ == other.number_;
}
jp::JNumber::operator Real() const
{
	return number_;
}
jp::JNumber::operator unsigned() const
{
	return static_cast<unsigned>(number_);
}
jp::JNumber::operator int() const
{
	return static_cast<int>(number_);
}
jp::JNumber::operator float() const
{
	return static_cast<float>(number_);
}
// end class JNumber

std::ostream& jp::operator<<(std::ostream& os, JNumber const& jsonNumber)
{
	os << jsonNumber.number_;
	return os;
}
