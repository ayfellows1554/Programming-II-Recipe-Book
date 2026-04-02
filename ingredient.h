#pragma once
#include <string>

class Ingredient {
public:
    Ingredient(const std::string& amount, const std::string& name);

    void displayIngredient() const;

private:
    std::string amount;
    std::string name;
};
