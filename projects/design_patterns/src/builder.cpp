#include "builder.hpp"


void Burger::setBun(string bunType) { bun = bunType; }

void Burger::addIngredient(string ingredient) { ingredients.push_back(ingredient); }

void Burger::addSauce(string sauce) { sauces.push_back(sauce); }

void Burger::showBurger() const
{
    std::cout << "Burger with:\n";
    
    std::cout << "  - " << bun << " bun\n";
    
    std::cout << "  - sauces: ";    
    for (const auto& sauce : sauces)
        std::cout << sauce << " ";
    std::cout << std::endl;
    
    std::cout << "  - ingredients: ";
    for (const auto& ingredient : ingredients)
        std::cout << ingredient << " ";
    std::cout << std::endl;
}

Burger* BurgerBuilder::getBurger() { return burger; }

CheeseBurgerBuilder::CheeseBurgerBuilder() { burger = new Burger(); }

void CheeseBurgerBuilder::buildBun() { burger->setBun("Sesame"); }

void CheeseBurgerBuilder::buildSauces()
{
    burger->addIngredient("ketchup");
    burger->addIngredient("mustard");
}

void CheeseBurgerBuilder::buildIngredients()
{
    burger->addIngredient("Cheese");
    burger->addIngredient("Beef Patty");
    burger->addIngredient("Lettuce");
}

VeggieBurgerBuilder::VeggieBurgerBuilder() { burger = new Burger(); }

void VeggieBurgerBuilder::buildBun() { burger->setBun("Whole Grain"); }

void VeggieBurgerBuilder::buildSauces()
{
    burger->addIngredient("mayonnaise");
    burger->addIngredient("soy");
}

void VeggieBurgerBuilder::buildIngredients()
{
    burger->addIngredient("Lettuce");
    burger->addIngredient("Tomato");
    burger->addIngredient("Veggie Patty");
}

void BurgerDirector::setBuilder(BurgerBuilder* b) { builder = b; }

void BurgerDirector::construct()
{
    builder->buildBun();
    builder->buildSauces();
    builder->buildIngredients();
}
