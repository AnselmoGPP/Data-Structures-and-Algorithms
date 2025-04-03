#ifndef ABSTRACT_FACTORY_HPP
#define ABSTRACT_FACTORY_HPP

/*
	Abstract factory (AF):
	Useful when we have different families of related objects (products). Example:
		- Different platforms (families) support different applications (products)
		- Different car models (families) have different car parts (products).
	Each factory
		- Is a concrete class instance (CF) from the AF (the AF consists of a factory method per product).
		- Can create products of one family without having to specify their concrete classes.
		- Encapsulates the new operator and the family-specific product classes.
	Process:
		1. Define a matrix of families versus objects (car models vs car parts).
		2. Define a factory derived class for each platform that encapsulate all references to new.
		3. The client only uses the factory methods to create the product objects.
	The AF encapsulate family dependencies, so it doesn't require many #ifdef.
	To replace the entire familiy of products just instantiate a different concrete instance (CF) of the abstract factory (AF).
*/

/*
	We consider 2 families of shapes: Simple (circle, square) and Robust (ellipse, rectangle).
	Factory class: Abstract factory (interface).
		SimpleShapeFactory: Concrete factory instance for simple shapes.
		RobustShapeFactory: Concrete factory instance for robust shapes.
*/

/*
	We have a family of shapes: Circle, Square, Ellipse, Rectangle.
	We have a family of factory classes: SimpleShapeFactory, RobustShapeFactory.
	Each factory subclass can create some of the shapes: {Circle, Square}, {Ellipse, Rectangle}
*/

class Shape
{
public:
	Shape();
	virtual void draw() = 0;

protected:
	int id_;
	static int total_;
};

class Circle : public Shape
{
public:
	void draw();
};

class Square : public Shape
{
public:
	void draw();
};

class Ellipse : public Shape
{
public:
	void draw();
};

class Rectangle : public Shape
{
public:
	void draw();
};

class Factory
{
public:
	virtual Shape* createCurvedInstance() = 0;
	virtual Shape* createStraightInstance() = 0;
};

class SimpleShapeFactory : public Factory
{
public:
	Shape* createCurvedInstance();
	Shape* createStraightInstance();
};

class RobustShapeFactory : public Factory
{
public:
	Shape* createCurvedInstance();
	Shape* createStraightInstance();
};

void test_abstract_factory();

#endif