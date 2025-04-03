#include <iostream>
#include "singleton.hpp"


std::string Singleton::type = "Singleton";

Singleton* Singleton::instance = nullptr;

Singleton::Singleton() { }

int  Singleton::getValue() { return value; }

void Singleton::setValue(int val) { value = val; }

Singleton* Singleton::getInstance()
{
	if (!instance)		// 2.1) Lazy initialization (delay creation of an object until it's needed) in the accessor function
		if (type == "tripleInt")
			instance = new tripleInt();
		else
			instance = new Singleton();
	
	return instance;
}

void Singleton::setType(std::string t)
{
	type = t;
	delete instance;
	instance = nullptr;
}


tripleInt::tripleInt() { }

void tripleInt::setValue(int val) { value = val * 3; }


void test_Singleton()
{
	std::cout << '\n' << __func__ << "----------" << std::endl;

	//Singleton obj;   ->   Error: Cannot access protected constructor.

	Singleton::getInstance()->setValue(10);		// 2.2) The singleton can only be manipulated by using the accessor function
	std::cout << Singleton::getInstance()->getValue() << std::endl;		// returns 10

	Singleton::setType("tripleInt");   // Modify type of the singleton
	Singleton::getInstance()->setValue(20);
	std::cout << Singleton::getInstance()->getValue() << std::endl;		// returns 3*20 = 60
}