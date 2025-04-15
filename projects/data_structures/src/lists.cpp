#include "lists.hpp"

#include <iostream>

namespace dsa
{
	void test_StaticArray()
	{
		size_t testNumber = 0;

		std::cout << ++testNumber << " " << std::flush;   // 1
		StaticArray<int> list1(0);
		list1.clear();
		list1.moveToEnd();
		if (list1.length() != 0) throw std::exception("Failed at length()");
		if (list1.currPos() != 0) throw std::exception("Failed at currPos()");

		std::cout << ++testNumber << " " << std::flush;   // 2
		StaticArray<int> list2(10);
		list2.append(0);
		list2.append(1);
		list2.append(3);
		list2.append(4);
		list2.moveToEnd();
		list2.prev();
		list2.prev();
		list2.insert(2);
		list2.insert(3);
		list2.append(5);
		list2.append(6);
		list2.append(8);
		list2.moveToPos(8);
		list2.insert(7);
		list2.moveToStart();
		list2.next();
		list2.next();
		list2.remove();
		if (list2.length() != 9) throw std::exception("Failed at length()");
		if (list2.currPos() != 2) throw std::exception("Failed at currPos()");
		if (list2.getValue() != 2) throw std::exception("Failed at getValue()");
		if (list2[7] != 7) throw std::exception("Failed at operator[]");
		if(dsa::find(&list2, 5) != 5) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 3
		StaticArray<int> list3({ 0,1,2,3,4,5,6,7,8,9 });
		list3.moveToPos(3);
		if (list3.length() != 10) throw std::exception("Failed at length()");
		if (list3.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list3.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list3[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list3, 9) != 9) throw std::exception("Failed at find()");
		list3.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 4
		StaticArray<int> list4(list3);
		if (list4.length() != 10) throw std::exception("Failed at length()");
		if (list4.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list4.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list4[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list4, 9) != 9) throw std::exception("Failed at find()");
		list4.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 5
		StaticArray<int> list5 = list4;
		if (list5.length() != 10) throw std::exception("Failed at length()");
		if (list5.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list5.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list5[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list5, 9) != 9) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 6
		StaticArray<int> list6 = list5;
		list6.clear();
		if (list6.length() != 0) throw std::exception("Failed at length()");
		if (list6.currPos() != 0) throw std::exception("Failed at currPos()");

		std::cout << std::endl;
	}

	void test_DynamicArray()
	{
		size_t testNumber = 0;

		std::cout << ++testNumber << " " << std::flush;   // 1
		DynamicArray<int> list1(0);
		list1.clear();
		list1.moveToEnd();
		list1.append(0);
		list1.append(1);
		list1.append(2);
		list1.append(3);
		list1.append(4);
		list1.append(5);
		list1.append(6);
		list1.append(7);
		list1.append(8);
		list1.append(9);
		list1.append(10);
		if (list1.length() != 11) throw std::exception("Failed at length()");
		if (list1.currPos() != 0) throw std::exception("Failed at currPos()");
		if (list1.getValue() != 0) throw std::exception("Failed at getValue()");
		if (list1[7] != 7) throw std::exception("Failed at operator[]");
		if (dsa::find(&list1, 5) != 5) throw std::exception("Failed at find()");
		
		std::cout << ++testNumber << " " << std::flush;   // 2
		DynamicArray<int> list2(10);
		list2.append(0);
		list2.append(1);
		list2.append(3);
		list2.append(4);
		list2.moveToEnd();
		list2.prev();
		list2.prev();
		list2.insert(2);
		list2.insert(3);
		list2.append(5);
		list2.append(6);
		list2.append(8);
		list2.moveToPos(8);
		list2.insert(7);
		list2.moveToStart();
		list2.next();
		list2.next();
		list2.remove();
		if (list2.length() != 9) throw std::exception("Failed at length()");
		if (list2.currPos() != 2) throw std::exception("Failed at currPos()");
		if (list2.getValue() != 2) throw std::exception("Failed at getValue()");
		if (list2[7] != 7) throw std::exception("Failed at operator[]");
		if (dsa::find(&list2, 5) != 5) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 3
		DynamicArray<int> list3({ 0,1,2,3,4,5,6,7,8,9 });
		list3.moveToPos(3);
		if (list3.length() != 10) throw std::exception("Failed at length()");
		if (list3.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list3.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list3[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list3, 9) != 9) throw std::exception("Failed at find()");
		list3.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 4
		DynamicArray<int> list4(list3);
		if (list4.length() != 10) throw std::exception("Failed at length()");
		if (list4.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list4.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list4[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list4, 9) != 9) throw std::exception("Failed at find()");
		list4.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 5
		DynamicArray<int> list5 = list4;
		if (list5.length() != 10) throw std::exception("Failed at length()");
		if (list5.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list5.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list5[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list5, 9) != 9) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 6
		DynamicArray<int> list6 = list5;
		list6.clear();
		if (list6.length() != 0) throw std::exception("Failed at length()");
		if (list6.currPos() != 0) throw std::exception("Failed at currPos()");

		std::cout << std::endl;
	}

	void test_SinglyLinkedList()
	{
		size_t testNumber = 0;

		std::cout << ++testNumber << " " << std::flush;   // 1
		SinglyLinkedList<int> list1;
		list1.clear();
		list1.moveToEnd();
		list1.append(0);
		list1.append(1);
		list1.append(2);
		list1.append(3);
		list1.append(4);
		list1.append(5);
		list1.append(6);
		list1.append(7);
		list1.append(8);
		list1.append(9);
		list1.append(10);
		if (list1.length() != 11) throw std::exception("Failed at length()");
		if (list1.currPos() != 0) throw std::exception("Failed at currPos()");
		if (list1.getValue() != 0) throw std::exception("Failed at getValue()");
		if (list1[7] != 7) throw std::exception("Failed at operator[]");
		if (dsa::find(&list1, 5) != 5) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 2
		SinglyLinkedList<int> list2;
		list2.append(0);
		list2.append(1);
		list2.append(3);
		list2.append(4);
		list2.moveToEnd();
		list2.prev();
		list2.prev();
		list2.insert(2);
		list2.insert(3);
		list2.append(5);
		list2.append(6);
		list2.append(8);
		list2.moveToPos(8);
		list2.insert(7);
		list2.moveToStart();
		list2.next();
		list2.next();
		list2.remove();
		if (list2.length() != 9) throw std::exception("Failed at length()");
		if (list2.currPos() != 2) throw std::exception("Failed at currPos()");
		if (list2.getValue() != 2) throw std::exception("Failed at getValue()");
		if (list2[7] != 7) throw std::exception("Failed at operator[]");
		if (dsa::find(&list2, 5) != 5) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 3
		SinglyLinkedList<int> list3({ 0,1,2,3,4,5,6,7,8,9 });
		list3.moveToPos(3);
		if (list3.length() != 10) throw std::exception("Failed at length()");
		if (list3.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list3.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list3[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list3, 9) != 9) throw std::exception("Failed at find()");
		list3.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 4
		SinglyLinkedList<int> list4(list3);
		if (list4.length() != 10) throw std::exception("Failed at length()");
		if (list4.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list4.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list4[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list4, 9) != 9) throw std::exception("Failed at find()");
		list4.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 5
		SinglyLinkedList<int> list5 = list4;
		if (list5.length() != 10) throw std::exception("Failed at length()");
		if (list5.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list5.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list5[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list5, 9) != 9) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 6
		SinglyLinkedList<int> list6 = list5;
		list6.clear();
		if (list6.length() != 0) throw std::exception("Failed at length()");
		if (list6.currPos() != 0) throw std::exception("Failed at currPos()");

		std::cout << std::endl;
	}

	void test_DoubleLinkedList()
	{
		size_t testNumber = 0;

		std::cout << ++testNumber << " " << std::flush;   // 1
		DoubleLinkedList<int> list1;
		list1.clear();
		list1.moveToEnd();
		list1.moveToStart();
		list1.append(0);
		list1.append(1);
		list1.append(2);
		list1.append(3);
		list1.append(4);
		list1.append(5);
		list1.append(6);
		list1.append(7);
		list1.append(8);
		list1.append(9);
		list1.append(10);
		if (list1.length() != 11) throw std::exception("Failed at length()");
		if (list1.currPos() != 0) throw std::exception("Failed at currPos()");
		if (list1.getValue() != 0) throw std::exception("Failed at getValue()");
		if (list1[7] != 7) throw std::exception("Failed at operator[]");
		if (dsa::find(&list1, 5) != 5) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 2
		DoubleLinkedList<int> list2;
		list2.append(0);
		list2.append(1);
		list2.append(3);
		list2.append(4);
		list2.moveToEnd();
		list2.prev();
		list2.prev();
		list2.insert(2);
		list2.insert(3);
		list2.append(5);
		list2.append(6);
		list2.append(8);
		list2.moveToPos(8);
		list2.insert(7);
		list2.moveToStart();
		list2.next();
		list2.next();
		list2.remove();
		if (list2.length() != 9) throw std::exception("Failed at length()");
		if (list2.currPos() != 2) throw std::exception("Failed at currPos()");
		if (list2.getValue() != 2) throw std::exception("Failed at getValue()");
		if (list2[7] != 7) throw std::exception("Failed at operator[]");
		if (dsa::find(&list2, 5) != 5) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 3
		DoubleLinkedList<int> list3({ 0,1,2,3,4,5,6,7,8,9 });
		list3.moveToPos(3);
		if (list3.length() != 10) throw std::exception("Failed at length()");
		if (list3.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list3.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list3[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list3, 9) != 9) throw std::exception("Failed at find()");
		list3.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 4
		DoubleLinkedList<int> list4(list3);
		if (list4.length() != 10) throw std::exception("Failed at length()");
		if (list4.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list4.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list4[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list4, 9) != 9) throw std::exception("Failed at find()");
		list4.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 5
		DoubleLinkedList<int> list5 = list4;
		if (list5.length() != 10) throw std::exception("Failed at length()");
		if (list5.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list5.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list5[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list5, 9) != 9) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 6
		DoubleLinkedList<int> list6 = list5;
		list6.clear();
		if (list6.length() != 0) throw std::exception("Failed at length()");
		if (list6.currPos() != 0) throw std::exception("Failed at currPos()");

		std::cout << std::endl;
	}

	void test_XorLinkedList()
	{
		size_t testNumber = 0;

		std::cout << ++testNumber << " " << std::flush;   // 1
		XorLinkedList<int> list1;
		list1.clear();
		list1.moveToEnd();
		list1.moveToStart();
		list1.append(0);
		list1.append(1);
		list1.append(2);
		list1.append(3);
		list1.append(4);
		list1.append(5);
		list1.append(6);
		list1.append(7);
		list1.append(8);
		list1.append(9);
		list1.append(10);
		if (list1.length() != 11) throw std::exception("Failed at length()");
		if (list1.currPos() != 0) throw std::exception("Failed at currPos()");
		if (list1.getValue() != 0) throw std::exception("Failed at getValue()");
		if (list1[7] != 7) throw std::exception("Failed at operator[]");
		if (dsa::find(&list1, 5) != 5) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 2
		XorLinkedList<int> list2;
		list2.append(0);
		list2.append(1);
		list2.append(3);
		list2.append(4);
		list2.moveToEnd();
		list2.prev();
		list2.prev();
		list2.insert(2);
		list2.insert(3);
		list2.append(5);
		list2.append(6);
		list2.append(8);
		list2.moveToPos(8);
		list2.insert(7);
		list2.moveToStart();
		list2.next();
		list2.next();
		list2.remove();
		if (list2.length() != 9) throw std::exception("Failed at length()");
		if (list2.currPos() != 2) throw std::exception("Failed at currPos()");
		if (list2.getValue() != 2) throw std::exception("Failed at getValue()");
		if (list2[7] != 7) throw std::exception("Failed at operator[]");
		if (dsa::find(&list2, 5) != 5) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 3
		XorLinkedList<int> list3({ 0,1,2,3,4,5,6,7,8,9 });
		list3.moveToPos(3);
		if (list3.length() != 10) throw std::exception("Failed at length()");
		if (list3.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list3.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list3[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list3, 9) != 9) throw std::exception("Failed at find()");
		list3.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 4
		XorLinkedList<int> list4(list3);
		if (list4.length() != 10) throw std::exception("Failed at length()");
		if (list4.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list4.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list4[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list4, 9) != 9) throw std::exception("Failed at find()");
		list4.moveToPos(3);

		std::cout << ++testNumber << " " << std::flush;   // 5
		XorLinkedList<int> list5 = list4;
		if (list5.length() != 10) throw std::exception("Failed at length()");
		if (list5.currPos() != 3) throw std::exception("Failed at currPos()");
		if (list5.getValue() != 3) throw std::exception("Failed at getValue()");
		if (list5[6] != 6) throw std::exception("Failed at operator[]");
		if (dsa::find(&list5, 9) != 9) throw std::exception("Failed at find()");

		std::cout << ++testNumber << " " << std::flush;   // 6
		XorLinkedList<int> list6 = list5;
		list6.clear();
		if (list6.length() != 0) throw std::exception("Failed at length()");
		if (list6.currPos() != 0) throw std::exception("Failed at currPos()");

		std::cout << std::endl;
	}
}
