#pragma once
#include <string>

class Ingredient {
public:
    Ingredient(double amountValue, const std::string& amount, const std::string& name);

    void scaleAmount(double ratio);  
    void displayIngredient() const;

private:
    std::string m_unit; //cups, tbsp ... etc
    std::string m_name; // flour, sugar
    double m_amountValue; //numeric amount

};
