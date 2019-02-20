#pragma once

#include <string>

// chr is in [0..9]
bool is_digit(char chr);
// string is [0..9]+
bool is_unsigned(std::string const& string);
// string is -?[0..9]+ or unsigned
bool is_int(std::string const& string);
// string is -?[0..9]*.[0..9]*
bool is_float(std::string const& string);
// string is -?[0..9]*.[0..9]*(e|E)?(-|+)?[0..9]+
bool is_double(std::string const& string);

// string is "['a'..'z' 'A'..'Z']+"
bool is_string(std::string const& string);

// Hash for strings
size_t hash_str(std::string const& string);

std::string rand_hex_str(unsigned size);

std::string str_replace(std::string const& src, std::string const& pattern, std::string const& newStr);