#include <iostream>
#include "json/Json.hpp"

int main()
{
	std::cout << "Testing..." << "\n";

	Json json{ "files/default_config.json" };
	std::cout << json << "\n";

	return 0;
}