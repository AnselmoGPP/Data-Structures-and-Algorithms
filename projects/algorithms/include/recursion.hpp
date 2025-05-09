#ifndef RECURSION_HPP
#define RECURSION_HPP

#include "../../data_structures/include/lists.hpp"

using namespace dss;

/*
   Recursion can always be replaced with a stack, but not always with iteration (like in TOH).
   - Recursion: A function calls itself in order to solve a problem by breaking it down into smaller subproblems of same type.
   - Stack: Linear data structure where the last element added to the stack is the first one to be removed (LIFO).
   - Iteration: A set of instructions is repeatedly executed using a loop until a certain condition is met.
*/

long fact_iteration(unsigned n);   //!< O(n). Factorial algorithm solved using iteration.
long fact_recursive(unsigned n);   //!< O(n). Factorial algorithm solved using recursion.
long fact_stack(unsigned n, LinkedStack<unsigned>& stack);   //!< O(n). Factorial algorithm solved using a stack.

class Pole;
class TOHobj;
void TOH_recursive(unsigned n, Pole& start, Pole& goal, Pole& temp);   //!< O(?). Towers of Hanoi algorithm solved using recursion.
void TOH_stack(unsigned n, Pole& start, Pole& goal, Pole& temp, LinkedStack<TOHobj*>& stack);   //!< O(?). Towers of Hanoi algorithm solved using a stack.

void test_fact();   //!< Test for factorial algorithm.
void test_TOH();   //!< Test for TOH algorithm.
void verifyTOH(size_t n, Pole& start, Pole& temp, Pole& goal);   //!< Verify goal contains n sorted plates, and start and temp are empty.

/// Pole class. Adapted LinkedStack<unsigned> object.
class Pole : protected LinkedStack<unsigned>
{
public:
    Pole(unsigned n = 0);

    void move(Pole& dest);   //!< Move top element from this pole to another (dest).
    bool isSorted();

    LinkedStack<unsigned>::clear;
    LinkedStack<unsigned>::topValue;
    LinkedStack<unsigned>::length;
};

/// Operations.
enum TOHop { DOMOVE, DOTOH };

/// Representation of a TOH game set and an operation to perform in it.
class TOHobj
{
public:
    TOHobj(unsigned n, Pole& start, Pole& goal, Pole& temp);
    TOHobj(Pole& start, Pole& goal);

    TOHop operation;   // operation type
    unsigned count;   // disks count
    Pole &start, &goal, &temp;
};

#endif