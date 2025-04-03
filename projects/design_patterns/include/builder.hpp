#ifndef BUILDER_HPP
#define BUILDER_HPP

/*
	Builder:
	Build a complex object step by step. One of the many possible representations of the object is created. It is usually a Composite.
	A common input (Reader class) specifies how to create an object. The object is created through a common series of steps (Builder class).
	The "director" invokes Builder services as it interprets the input. Builder creates part of the object each time it's called.
	Finer control over construction process (step by step construction).
	Example: In fast food restaurants, children's meal consists of some items (burguer, fries, drink, toy). There are different types of each item. Different variations of the meal exist, but the construction process is always the same.
*/

/*
    Builder (creational):
    Director controls the construction process through the use of a concrete Builder, which builds parts of the Product
    (complex object) step by step. This keeps the construction process separate from the final representation. It can 
    create different variations of the Product using the same building process.
*/

#include <iostream>
#include <vector>

using namespace std;


enum Size {big, medium, small};

// Object to build
class Burger
{
public:
    void setBun(string bunType);
    void addSauce(string sauce);
    void addIngredient(string ingredient);
    void showBurger() const;

private:
    string bun;
    vector<string> sauces;
    vector<string> ingredients;
};

// Abstract builder class
class BurgerBuilder
{
public:
    virtual ~BurgerBuilder() = default;

    virtual void buildBun() = 0;
    virtual void buildSauces() = 0;
    virtual void buildIngredients() = 0;

    Burger* getBurger();

protected:
    Burger* burger;
};

// Concrete builder 1
class CheeseBurgerBuilder : public BurgerBuilder
{
public:
    CheeseBurgerBuilder();

    void buildBun() override;
    void buildSauces() override;
    void buildIngredients() override;
};

// Concrete builder 2
class VeggieBurgerBuilder : public BurgerBuilder
{
public:
    VeggieBurgerBuilder();

    void buildBun() override;
    void buildSauces() override;
    void buildIngredients() override;
};

// Director controls the building process
class BurgerDirector
{
public:
    void setBuilder(BurgerBuilder* b);
    void construct();
private:
    BurgerBuilder* builder;
};

void test_builder()
{
    BurgerDirector chef;
    CheeseBurgerBuilder cheeseBurgerBuilder;
    VeggieBurgerBuilder veggieBurgerBuilder;

    chef.setBuilder(&cheeseBurgerBuilder);
    chef.construct();
    cheeseBurgerBuilder.getBurger();

    chef.setBuilder(&veggieBurgerBuilder);
    chef.construct();
    veggieBurgerBuilder.getBurger();
}

#endif