#include "str_fct.hpp"
#include <algorithm>
#include <vector>

bool is_digit(char chr)
{
	return '0' <= chr and chr <= '9';
}
bool is_unsigned(std::string const& string)
{
	if (string.empty())
		return false;
	if (string.size() > 1 and string[0] == '0')
		return false;
	for (char chr : string)
	{
		if (not is_digit(chr))
			return false;
	}
	return true;
}
bool is_int(std::string const& string)
{
	return
		is_unsigned(string) or
		(string.size() > 1 and string[0] == '-' and is_unsigned(string.substr(1, string.size() - 1)));
}
bool is_float(std::string const& string)
{
	auto point = string.find('.');
	if (point == std::string::npos)
		return is_int(string);
	else
	{
		auto intPart = string.substr(0, point);
		auto decPart = string.substr(point + 1, string.size() - point);
		for (char c : decPart)
			if (not is_digit(c))
				return false;
		return is_int(intPart);
	}
}
bool is_double(std::string const& string)
{
	auto e = string.find('e');
	auto E = string.find('E');
	if (e == std::string::npos and E == std::string::npos)
		return is_float(string);
	else if (e != std::string::npos and E != std::string::npos)
		return false;
	else
	{
		auto ePos = (e != std::string::npos ? e : E);
		auto exp = string.substr(ePos + 1, string.size() - ePos);
		return is_float(string.substr(0, ePos)) and 
			(is_int(exp) or (exp.size() > 1 and exp[0] == '+' and is_unsigned(exp.substr(1,exp.size()-1))));
	}
}

bool is_string(std::string const& string)
{
	if (string.size() < 2 or string.front() != '"' or string.back() != '"')
		return false;
	for (unsigned i{ 1 } ; i + 1 < string.size() ; ++i)
	{
		if (string[i] == '"' and string[i - 1] != '\\')
			return false;
	}
	return true;
}
