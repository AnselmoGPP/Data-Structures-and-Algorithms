#include <stdexcept>
#include <iostream>

#include "recursion.hpp"


// -- Factorial --------------------------------------

long fact_iteration(unsigned n)
{
    if (n == 0) return 1;

    long result = 1;
    while (n != 0)
    {
        result *= n;
        n--;
    }

    return result;
}

long fact_recursive(unsigned n)
{
    if (n == 0) return 1;
    return n * fact_recursive(n - 1);
}

long fact_stack(unsigned n, LinkedStack<unsigned>& stack)
{
    if (n < 0 || n > 12) throw std::out_of_range("Input out of range");

    while (n > 1) stack.push(n--);
    long result = 1;
    while (stack.length() > 0) result *= stack.pop();
    return result;
}

// -- TOH (Towers of Hanoi) --------------------------------------

Pole::Pole(unsigned n)
{
    while (n != 0)
    {
        push(n);
        n--;
    }
}

void Pole::move(Pole& dest)
{
    if (length() == 0) return;

    dest.push(pop());
}

bool Pole::isSorted()
{
    LinkedStack<unsigned> stack = *this;

    unsigned last;
    if (stack.length()) last = stack.pop();
    while (stack.length())
    {
        if (last > stack.topValue()) return false;
        last = stack.pop();
    }

    return true;
}

void TOH_recursive(unsigned n, Pole& start, Pole& goal, Pole& temp)
{
	if (n == 0) return;
    TOH_recursive(n - 1, start, temp, goal);   // 1. Move n-1 disks from start to temp
	start.move(goal);   // 2. Move largest disk to goal
    TOH_recursive(n - 1, temp, goal, start);   // 2. Move n-1 disks from temp to goal
}

TOHobj::TOHobj(unsigned n, Pole start, Pole goal, Pole temp)
    : op(DOTOH), num(n), start(start), goal(goal), tmp(temp) { }

TOHobj::TOHobj(Pole start, Pole goal)
    : op(DOMOVE), start(start), goal(goal) { }

void TOH_stack(unsigned n, Pole& start, Pole& goal, Pole& temp, LinkedStack<TOHobj*>& S)
{
    S.push(new TOHobj(n, start, goal, temp));
    TOHobj* t;
    while (S.length() > 0)   // Grab next task
    {
        t = S.pop();
        if (t->op == DOMOVE)   // Do a move
            t->start.move(t->goal);
        else if (t->num > 0)   // Store in reverse 3 recursive statements
        {
            int num = t->num;
            Pole tmp = t->tmp;
            Pole goal = t->goal;
            Pole start = t->start;
            S.push(new TOHobj(num - 1, tmp, goal, start));
            S.push(new TOHobj(start, goal));
            S.push(new TOHobj(num - 1, start, tmp, goal));
        }
        delete t;
    }
}
/*
void TOH_stack(unsigned n, Pole& start, Pole& goal, Pole& temp, LinkedStack<TOHobj*>& S)
{
    S.push(new TOHobj(n, start, goal, temp));
    TOHobj* t;
    while (S.length() > 0)   // Grab next task
    {
        t = S.pop();
        if (t->op == DOMOVE)   // Do a move
            t->start.move(t->goal);
        else if (t->num > 0)   // Store in reverse 3 recursive statements
        {
            int num = t->num;
            Pole tmp = t->tmp;
            Pole goal = t->goal;
            Pole start = t->start;
            S.push(new TOHobj(num - 1, tmp, goal, start));
            S.push(new TOHobj(start, goal));
            S.push(new TOHobj(num - 1, start, tmp, goal));
        }
        delete t;
    }
}
*/

// -- Tests --------------------------------------

void test_fact()
{
    unsigned count = 0;
    std::cout << __func__ << ": " << std::flush;

    std::cout << ++count << " " << std::flush;
    if(fact_iteration(0) != 1) throw std::exception("Incorrect result");

    std::cout << ++count << " " << std::flush;
    if (fact_iteration(10) != 3628800) throw std::exception("Incorrect result");

    std::cout << ++count << " " << std::flush;
    if(fact_recursive(0) != 1) throw std::exception("Incorrect result");

    std::cout << ++count << " " << std::flush;
    if (fact_recursive(10) != 3628800) throw std::exception("Incorrect result");

    std::cout << ++count << " " << std::flush;
    LinkedStack<unsigned> stack1;
    if(fact_stack(0, stack1) != 1) throw std::exception("Incorrect result");

    std::cout << ++count << " " << std::flush;
    LinkedStack<unsigned> stack2;
    if (fact_stack(10, stack2) != 3628800) throw std::exception("Incorrect result");

    std::cout << std::endl;
}

void test_TOH()
{
    unsigned count = 0;
    std::cout << __func__ << ": " << std::flush;

    std::cout << ++count << " " << std::flush;
    Pole start1, goal1, temp1;
    TOH_recursive(0, start1, goal1, temp1);
    verifyTOH(0, start1, temp1, goal1);

    std::cout << ++count << " " << std::flush;
    Pole start2(10), goal2, temp2;
    TOH_recursive(10, start2, goal2, temp2);
    verifyTOH(10, start2, temp2, goal2);

    std::cout << ++count << " " << std::flush;
    Pole start3, goal3, temp3;
    LinkedStack<TOHobj*> stack3;
    TOH_stack(0, start3, goal3, temp3, stack3);
    verifyTOH(0, start3, temp3, goal3);

    std::cout << ++count << " " << std::flush;
    Pole start4(10), goal4, temp4;
    LinkedStack<TOHobj*> stack4;
    TOH_stack(10, start4, goal4, temp4, stack4);
    std::cout << start4.length() << "-" << temp4.length() << "-" << goal4.length() << std::endl;
    verifyTOH(10, start4, temp4, goal4);

    std::cout << std::endl;
}

void verifyTOH(size_t n, Pole& start, Pole& temp, Pole& goal)
{
    if (start.length() == 0 && temp.length() == 0 && goal.length() == n && goal.isSorted())
        return;

    throw std::exception("Incorrect result");
}