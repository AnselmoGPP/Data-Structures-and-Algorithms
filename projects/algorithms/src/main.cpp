
#include <iostream>
#include "header.hpp"

using namespace ans;

bool test_arrayBasedList();
bool test_singlyLinkedList();

int main()
{
	test_arrayBasedList();
	test_singlyLinkedList();

	system("pause");
}

void outputResult(bool test, const char* name)
{
	if (test) std::cout << "SUCCESS " << name << std::endl;
	else      std::cout << "FAILURE " << std::endl;
}

bool test_arrayBasedList()
{
	arrayBasedList<int> l(5);
	arrayBasedList<int> l2 = { 4, 2, 5, 1, 3 };
	arrayBasedList<int> l3(l2);
	l = l3;
	int n;

	l.next();						// 4[2]5 1 3
	n = l.remove();					// 4[5]1 3
	l.append(n);					// 4[5]1 3 2
	l.moveToPos(3);					// 4 5 1[3]2
	n = l.remove() + l.length();	// 4 5 1[2]
	l.moveToEnd();					// 4 5 1 2[ ]
	l.prev();						// 4 5 1[2]
	n += l.currPos() + l.getValue();// 4 5 1[2]
	l.moveToStart();				//[4]5 1 2
	l.next();						// 4[5]1 2
	l.insert(n);					// 4[12]5 1 2

	bool test = true;
	int result[5] = { 4, 12, 5, 1, 2 };

	for (size_t i = 0; i < l.length(); i++)
		if (l[i] != result[i])
			test = false;

	for (l.moveToStart(); l.currPos() != l.length(); l.next())
		if (l.getValue() != result[l.currPos()])
			test = false;

	if (find(l, 12) != 1) test = false;
	l.clear();
	if (l.length()  != 0) test = false;
	if (find(l, 12) != 0) test = false;

	outputResult(test, "arrayBasedList");

	return test;
}

bool test_singlyLinkedList()	// COMPLETE THIS TEST
{
	singlyLinkedList<int> l;
	singlyLinkedList<int> l2 = { 5, 3, 7, 1, 9, 2 };
	singlyLinkedList<int> l3(l2);
	l = l3;

	bool test = true;
	int result[6] = { 5, 3, 7, 1, 9, 2 };

	for (l.moveToStart(); l.currPos() != l.length(); l.next())
		if (l.getValue() != result[l.currPos()])
			test = false;

	outputResult(test, "singlyLinkedList");

	return true;
}

