
// Template functions implementations
template<typename T>
bool in(std::vector<T> const& vect, T const& value)
{
	return std::find(vect.begin(), vect.end(), value) != vect.end();
}
template<typename T>
unsigned count(std::vector<T> const& vect, T const& value)
{
	unsigned result{ 0 };
	for (auto const& t : vect)
	{
		if (t == value)
			++result;
	}
	return result;
}
template<typename T>
std::vector<std::vector<T>> split(std::vector<T> const& vect, T const& delimiter)
{
	std::vector<std::vector<T>> result{ {}, 1 };
	for (auto& t : vect)
	{
		if (t == delimiter)
			result.push_back({});
		else
			result.back().push_back(t);
	}
	return result;
}
template<typename T>
std::vector<std::vector<T>> split(std::vector<T> const& vect, std::vector<T> const& delimiters)
{
	std::vector<std::vector<T>> result{ {}, 1 };
	for (auto& t : vect)
	{
		if (search(delimiters, t))
			result.push_back({});
		else
			result.back().push_back(t);
	}
	return result;
}
template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& vect)
{
	os << "vector(";
	for (auto i(0u); i < vect.size(); ++i)
	{
		os << vect[i];
		if (i + 1 < vect.size())
			os << ',';
	}
	os << ')';
	return os;
}
template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, std::pair<T, U> const& pair)
{
	os << "pair(" << pair.first << ',' << pair.second << ')';
	return os;
}
template<typename T>
void remove_range(std::vector<T>& vect, size_t begin, size_t end)
{
	for (auto i{ 0u }; i < (end - begin + 1); ++i)
	{
		std::swap(vect[begin + i], vect[vect.size() - 1 - i]);
	}
	vect.resize(vect.size() - (end - begin + 1));
}
template<typename T, typename U>
std::vector<U> vector_convert(std::function<U(T)> const& fct, std::vector<T> const& vector)
{
	std::vector<U> result;
	for (auto const& t : vector)
	{
		result.push_back(fct(t));
	}
	return result;
}
