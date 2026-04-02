#include <iostream>
#include "Ingredient.h"

Ingredient::Ingredient(const std::string& amt, const std::string& n)
    : amount(amt), name(n) {}

void Ingredient::displayIngredient() const {
    std::cout << amount << " " << name << std::endl;
}
