#include <iostream>
#include <algorithm>
#include <vector>

#include "lists.hpp"

using namespace dsa;

int main()
{
	try
	{
		std::cout << "Tests: Data structures" << std::endl;

		std::cout << "  - Sequences" << std::endl;
		test_List<StaticArray>();
		test_List<DynamicArray>();
		test_List<SinglyLinkedList>();
		test_List<DoubleLinkedList>();
		test_List<XorLinkedList>();
		test_Stack<SArrayStack>();
		test_Stack<LinkedStack>();
		test_Queue<SArrayQueue>();
		test_Queue<LinkedQueue>();

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
