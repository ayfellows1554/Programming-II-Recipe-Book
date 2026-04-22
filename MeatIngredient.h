#pragma once
#include "Ingredient.h"
#include <iostream>

//One of the derived classes
class MeatIngredient : public Ingredient {
public:
    using Ingredient::Ingredient;

    void displayIngredient() const override {
        std::cout << getAmountValue() << " " << getUnit()
            << " " << getName() << " (Meat)" << std::endl;
    }
};
