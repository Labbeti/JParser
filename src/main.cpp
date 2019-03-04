#include <iostream>
#include "jp/JFile.hpp"

int main()
{
	std::cout << "Testing..." << "\n";

	jp::JFile const json{ "files/default_config.json" };
	std::cout << json << "\n";

	return 0;
}