#pragma once

#include <functional>
#include <vector>

template<typename T>
bool in(std::vector<T> const& vect, T const& value);
template<typename T>
unsigned count(std::vector<T> const& vect, T const& value);
template<typename T>
std::vector<std::vector<T>> split(std::vector<T> const& vect, T const& delimiter);
template<typename T>
std::vector<std::vector<T>> split(std::vector<T> const& vect, std::vector<T> const& delimiters);
template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& vect);
template<typename T>
void remove_range(std::vector<T>& vect, size_t begin, size_t end);
template<typename T, typename U>
std::vector<U> vector_convert(std::function<U(T)> const& fct, std::vector<T> const& vector);

// Template implementation
#include "vector_fct.inl"
