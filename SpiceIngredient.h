#pragma once
#include "Ingredient.h"
#include <iostream>

//One of the derived classes for IngredientBase
class SpiceIngredient : public Ingredient {
public:
    using Ingredient::Ingredient;

    void displayIngredient() const override {
        std::cout << getAmountValue() << " " << getUnit()
            << " " << getName() << " (Spices)" << std::endl;
    }
};
