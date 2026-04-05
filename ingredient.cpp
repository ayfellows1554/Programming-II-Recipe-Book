#include <stdexcept>
#include <algorithm>
#include <cctype>
#include "Ingredient.h"
#include <iostream>


static std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;

    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;

    return s.substr(start, end - start);
}

Ingredient::Ingredient(double amountValue, const std::string& unit, const std::string& n)
{
    std::string trimmedUnit = trim(unit);
    std::string trimmedName = trim(n);

    if (amountValue <= 0) {
        throw std::invalid_argument("Ingredient amount must be greater than zero.");
    }

    if (trimmedUnit.empty()) {
        throw std::invalid_argument("Ingredient unit cannot be empty.");
    }

    // Unit cannot contain digits
    for (char c : trimmedUnit) {
        if (std::isdigit(static_cast<unsigned char>(c))) {
            throw std::invalid_argument("Ingredient unit cannot contain numbers.");
        }
    }

    if (trimmedName.empty()) {
        throw std::invalid_argument("Ingredient name cannot be empty.");
    }

    m_amountValue = amountValue;
    m_unit = trimmedUnit;
    m_name = trimmedName;
}

void Ingredient::scaleAmount(double ratio) {
    if (ratio <= 0) {
        throw std::invalid_argument("Scale ratio must be greater than zero.");
    }
    m_amountValue *= ratio;
}

void Ingredient::displayIngredient() const {
    std::cout << m_amountValue << " " << m_unit << " " << m_name << std::endl;
}
