#include <iostream>

#include "recursion.hpp"

int main()
{
	try
	{
		std::cout << "Tests: Algorithms" << std::endl;

		std::cout << "  - Recursion" << std::endl;
		test_fact();
		test_TOH();
	}
	catch (std::exception& e) {
		std::cout << "\nError: " << e.what() << std::endl;
	}

	std::cin.get();
	return 0;
}
