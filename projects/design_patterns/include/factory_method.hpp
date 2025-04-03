#ifndef FACTORY_METHOD_HPP
#define FACTORY_METHOD_HPP

/*
	Factory method:
	Define an abstract class (interface) for creating an object, but use pure virtual methods to let subclasses (provided by the client) decide which class to instantiate.
	Similar to Abstract Factory, but without emphasis on families.
	Tipically specified by an architectural framework, and then implemented by the user of it.
	The factory method is a static method that returns an object of that class' type or subclass.
	The client is totally decoupled from the implementation details of derived classes. Polymorphic creation is now possible.
	If you have an inheritance hierarchy that exercises polymorphism, consider adding a polymorphic creation capability by defining a static factory method in the base class.
	Consider designing an internal "object pool" that allows objects to be reused instead of created from scratch.
	Consider making all constructors private or protected.
*/

/*
	A framework specifies the structure and flow of control of its domain, but the client may extend/replace some pieces.
	The following framework knows when to create a new document, but not what kind of document. 
	It declares a placeholder (Application::CreateDocument()) for the client to specify what document to create.
*/

/*
	Virtual class A can create objects of type B* (base and subclass objects) with A::NewDocument().
	The user defines what type is created by overriding virtual method A::createDocument(), which is used in A::NewDocument().
*/

#include <string>
#include <iostream>


/// Abstract base class declared by the framework
class Document
{
public:
	Document(char* fileName);

	char* GetName();
	virtual void Open() = 0;
	virtual void Close() = 0;

private:
	char name[20];
};

/// Concrete derived class defined by client (for open and close operations)
class MyDocument : public Document
{
public:
	MyDocument(char* fileName);

	void Open() override;
	void Close() override;
};

/// Framework
class Application
{
public:
	Application();

	void NewDocument(char* name);	//!< The client calls this "entry point" of the framework.

	void OpenDocument();
	void ReportDocs();
	virtual Document* CreateDocument(char*) = 0;	// Hole in the framework for the client to fill.

private:
	int _index;
	Document* _docs[10];	// Document's base class is used here
};

/// Customization of framework defined by client (for CreateDocument operation)
class MyApplication : public Application
{
public:
	MyApplication();

	Document* CreateDocument(char* fileName) override;	// Client defines Framework's "hole".
};

void test_factory_method();

#endif