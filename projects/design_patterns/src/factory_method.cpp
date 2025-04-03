#include "factory_method.hpp"


Document::Document(char* fileName) { strcpy(name, fileName); }

char* Document::GetName() { return name; }


MyDocument::MyDocument(char* fileName) : Document(fileName) { }

void MyDocument::Open() { std::cout << "   MyDocument: Open()" << std::endl; }

void MyDocument::Close() { std::cout << "   MyDocument: Close()" << std::endl; }


Application::Application() : _index(0) { std::cout << "Application: ctor" << std::endl; }

void Application::NewDocument(char* name)
{
	std::cout << "Application: NewDocument()" << std::endl;
	_docs[_index] = CreateDocument(name);
	_docs[_index++]->Open();
}

void Application::OpenDocument() { }

void Application::ReportDocs() 
{ 
	std::cout << "Application: ReportDocs()" << std::endl;
	for (int i = 0; i < _index; i++)
		std::cout << "   " << _docs[i]->GetName() << std::endl;
}


MyApplication::MyApplication() { std::cout << "MyApplication: ctor" << std::endl; }

Document* MyApplication::CreateDocument(char* fileName)
{
	std::cout << "   MyApplication: CreateDocument()" << std::endl;
	return new MyDocument(fileName);
}


void test_factory_method()
{
	std::cout << '\n' << __func__ << "----------" << std::endl;

	MyApplication myApp;	// Client's Framework's customization

	myApp.NewDocument("foo");
	myApp.NewDocument("bar");
	myApp.ReportDocs();
}