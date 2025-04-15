#include <iostream>
#include <algorithm>
#include <vector>

#include "lists.hpp"

using namespace dsa;
// <<< Operator new and delete for S/D/X linked lists
// <<< Inheritance possible for linked lists?
int main()
{
	try
	{
		std::cout << "Tests: Data structures" << std::endl;

		std::cout << "  - Sequences" << std::endl;
		test_StaticArray();
		test_DynamicArray();
		test_SinglyLinkedList();
		test_DoubleLinkedList();
		test_XorLinkedList();

		std::cout << "  - Binary trees" << std::endl;
		std::cout << "  - Non-binary trees" << std::endl;
		std::cout << "  - Internal sorting" << std::endl;
		std::cout << "  - File processing" << std::endl;
		std::cout << "  - External sorting" << std::endl;
		std::cout << "  - Searching" << std::endl;
		std::cout << "  - Indexing" << std::endl;
		std::cout << "  - Graphs" << std::endl;
	}
	catch (std::exception& e) {
		std::cout << "\nError: " << e.what() << std::endl;
	}

	std::cin.get();
	return 0;
}
