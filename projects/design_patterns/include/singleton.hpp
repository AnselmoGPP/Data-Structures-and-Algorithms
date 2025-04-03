#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <string>

/*
	Singleton:
	Only one instance of an object can exist (as a static member of its class).
	Its constructor is private/protected, forcing others to call its getInstance() method to get the one instance.
	Supporting inheritance requires a static member flag and static setter for it.
*/

/*
	1. Singleton instance: Private static member/attribute
	2. Accessor function: Public static function
		2.1. Lazy initialization (delay creation of an object until it's needed) in the accessor function
		2.2. The singleton can only be manipulated by using the accessor function.
	3. All constructors must be protected (clients cannot create instances)
	4. Inheritance can be supported (set a static member flag and a static setter for it)
*/
class Singleton
{
public:
	virtual int  getValue();
	virtual void setValue(int val);

	static Singleton* getInstance();	/// 2) Accessor function
	static void setType(std::string t);

protected:
	Singleton();						/// 3) All constructors must be protected (clients cannot create instances)

	int value;

private:
	static Singleton* instance;			/// 1) Singleton instance
	static std::string type;
};


/// Subclass that inherits from Singleton class
class tripleInt : public Singleton
{
public:
	friend class Singleton;				/// 4) Inheritance can be supported

	void setValue(int val);

protected:
	tripleInt();
};


void test_singleton();

#endif