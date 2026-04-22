#pragma once
#include "Ingredient.h"
#include <iostream>
#include<memory>

//One of the derived classes from IngredientBase
class DryIngredient : public Ingredient {
public:
    using Ingredient::Ingredient;

    void displayIngredient() const override {
        std::cout << getAmountValue() << " " << getUnit()
            << " " << getName() << " (Dry)" << std::endl;
    }
};
