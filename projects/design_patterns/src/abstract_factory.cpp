#include <iostream>

#include "abstract_factory.hpp"


int Shape::total_ = 0;

Shape::Shape() { id_ = total_++; }

void Circle::draw() { std::cout << "Circle id: " << id_ << std::endl; }
void Square::draw() { std::cout << "Square id: " << id_ << std::endl; }
void Ellipse::draw() { std::cout << "Ellipse id: " << id_ << std::endl; }
void Rectangle::draw() { std::cout << "Rectangle id: " << id_ << std::endl; }

Shape* SimpleShapeFactory::createCurvedInstance() { return new Circle; }
Shape* SimpleShapeFactory::createStraightInstance() { return new Square; }

Shape* RobustShapeFactory::createCurvedInstance() { return new Ellipse; }
Shape* RobustShapeFactory::createStraightInstance() { return new Rectangle; }

#define ROBUST 1

void test_abstract_factory()
{
	std::cout << '\n' << __func__ << "----------" << std::endl;

	// Create the factory you want.
	#ifdef SIMPLE
		Factory* factory = new SimpleShapeFactory;
	#elif ROBUST
		Factory* factory = new RobustShapeFactory;
	#endif

	// Create the objects
	Shape* shapes[3];

	shapes[0] = factory->createCurvedInstance();
	shapes[1] = factory->createStraightInstance();
	shapes[2] = factory->createCurvedInstance();

	for (size_t i = 0; i < 3; i++) shapes[i]->draw();
}