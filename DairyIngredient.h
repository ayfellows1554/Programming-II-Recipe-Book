#pragma once
#include "Ingredient.h"
#include <iostream>
#include<memory>

//One of the derived classes for IngredientBase
class DairyIngredient : public Ingredient {
public:
    using Ingredient::Ingredient;

    void displayIngredient() const override {
        std::cout << getAmountValue() << " " << getUnit()
            << " " << getName() << " (Dairy)" << std::endl;
    }
};
