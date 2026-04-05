
#pragma once
#include <string>

class Ingredient {
public:
    // amountValue = numeric amount (e.g., 1.5)
    // unit = "cups", "tbsp", etc.
    // name = "flour", "sugar"
    Ingredient(double amountValue, const std::string& unit, const std::string& name);

    void scaleAmount(double ratio);
    void displayIngredient() const;

    //Return the numeric amount
    double getAmountValue() const { return m_amountValue; }
    //Returns the unit
    const std::string& getUnit() const { return m_unit; }
    //Returns the name
    const std::string& getName() const { return m_name; }

private:
    double m_amountValue;     // numeric amount
    std::string m_unit;       // "cups", "tbsp", etc.
    std::string m_name;       // "flour", "sugar"
};
