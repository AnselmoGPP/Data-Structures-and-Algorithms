
#include <iostream>
#include <algorithm>
#include "lists.hpp"
#include "trees.hpp"

using namespace ans;

bool test_arrayBasedList();
bool test_singlyLinkedList();
bool test_DoubleLinkedList();

int main()
{
	std::string test = "asdflvph";
	std::sort(test.begin(), test.end());
	test.insert(test.begin()+2, 'A');
	test.erase(test.begin() + 2);

	test_arrayBasedList();
	test_singlyLinkedList();
	test_DoubleLinkedList();

	system("pause");
}

void outputResult(bool test, const char* name)
{
	if (test) std::cout << "SUCCESS " << name << std::endl;
	else      std::cout << "FAILURE " << name << std::endl;
}

bool test_arrayBasedList()
{
	bool test = true;
	int result[5] = { 4, 8, 5, 1, 2 };

	ArrayBasedList<int> l(5);
	ArrayBasedList<int> l2 = { 4, 2, 5, 1, 3 };
	ArrayBasedList<int> l3(l2);
	l = l3;
	int n;

	l.next();						// 4[2]5 1 3
	n = l.remove();					// 4[5]1 3
	l.append(n);					// 4[5]1 3 2
	l.moveToPos(3);					// 4 5 1[3]2
	n = l.remove() + l.length();	// 4 5 1[2]    (3+4)
	l.moveToEnd();					// 4 5 1 2[ ]
	l.prev();						// 4 5 1[2]
	n += l.currPos() - l.getValue();// 4 5 1[2]    (7+3-2)
	l.moveToStart();				//[4]5 1 2
	l.next();						// 4[5]1 2
	l.insert(n);					// 4[8]5 1 2

	for (size_t i = 0; i < l.length(); i++)
		if (l[i] != result[i])
			test = false;

	for (l.moveToStart(); l.currPos() != l.length(); l.next())
		if (l.getValue() != result[l.currPos()])
			test = false;

	if (find(l, 8) != 1) test = false;
	l.clear();
	if (l.length()  != 0) test = false;
	if (find(l, 8) != 0) test = false;

	outputResult(test, "arrayBasedList");

	return test;
}

bool test_singlyLinkedList()
{
	bool test = true;
	int result[5] = { 4, 8, 5, 1, 2 };

	SinglyLinkedList<int> l;
	SinglyLinkedList<int> l2 = { 4, 2, 5, 1, 3 };
	SinglyLinkedList<int> l3(l2);
	l = l3;
	int n;

	l.next();						// 4[2]5 1 3
	n = l.remove();					// 4[5]1 3
	l.append(n);					// 4[5]1 3 2
	l.moveToPos(3);					// 4 5 1[3]2
	n = l.remove() + l.length();	// 4 5 1[2]    (3+4)
	l.moveToEnd();					// 4 5 1 2[ ]
	l.prev();						// 4 5 1[2]
	n += l.currPos() - l.getValue();// 4 5 1[2]    (7+3-2)
	l.moveToStart();				//[4]5 1 2
	l.next();						// 4[5]1 2
	l.insert(n);					// 4[8]5 1 2

	for (size_t i = 0; i < l.length(); i++)
		if (l[i] != result[i])
			test = false;

	for (l.moveToStart(); l.currPos() != l.length(); l.next())
		if (l.getValue() != result[l.currPos()])
			test = false;
	
	l.clear();
	if (l.length() != 0) test = false;

	outputResult(test, "singlyLinkedList");

	return true;
}

bool test_DoubleLinkedList()
{
	bool test = true;
	int result[5] = { 4, 8, 5, 1, 2 };

	DoubleLinkedList<int> l;
/*	DoubleLinkedList<int> l2 = { 4, 2, 5, 1, 3 };
	DoubleLinkedList<int> l3(l2);
	l = l3;
	int n;

	l.next();						// 4[2]5 1 3
	n = l.remove();					// 4[5]1 3
	l.append(n);					// 4[5]1 3 2
	l.moveToPos(3);					// 4 5 1[3]2
	n = l.remove() + l.length();	// 4 5 1[2]    (3+4)
	l.moveToEnd();					// 4 5 1 2[ ]
	l.prev();						// 4 5 1[2]
	n += l.currPos() - l.getValue();// 4 5 1[2]    (7+3-2)
	l.moveToStart();				//[4]5 1 2
	l.next();						// 4[5]1 2
	l.insert(n);					// 4[8]5 1 2

	for (size_t i = 0; i < l.length(); i++)
		if (l[i] != result[i])
			test = false;

	for (l.moveToStart(); l.currPos() != l.length(); l.next())
		if (l.getValue() != result[l.currPos()])
			test = false;

	l.clear();
	if (l.length() != 0) test = false;

	outputResult(test, "DoubleLinkedList");
*/
	return true;
}