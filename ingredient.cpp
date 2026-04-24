#include "Ingredient.h"
#include <iostream>

Ingredient::Ingredient(double amountValue, const std::string& unit, const std::string& name)
    : m_amountValue(amountValue), m_unit(unit), m_name(name)
{
}

void Ingredient::scaleAmount(double ratio)
{
    m_amountValue *= ratio;
}

void Ingredient::displayIngredient() const
{
    std::cout << m_amountValue << " " << m_unit << " " << m_name << "\n";
}
