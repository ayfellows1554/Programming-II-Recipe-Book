#pragma once
#include "Ingredient.h"
#include <iostream>

//One of the  derived classes for inheritance
class ProduceIngredient : public Ingredient {
public:
    using Ingredient::Ingredient; // inherit constructor

    void displayIngredient() const override {
        std::cout << getAmountValue() << " " << getUnit()
            << " " << getName() << " (Produce)" << std::endl;
    }
};
