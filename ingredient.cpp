#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include "Ingredient.h"

//This trims the strings so that there isn't anything left dangling
static std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;

    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;

    return s.substr(start, end - start);
}

Ingredient::Ingredient(double amountValue, const std::string& amt, const std::string& n) {
    std::string trimmedAmt = trim(amt);
    std::string trimmedName = trim(n);

    if (trimmedAmt.empty()) {
        throw std::invalid_argument("Ingredient amount cannot be empty.");
    }
    if (trimmedName.empty()) {
        throw std::invalid_argument("Ingredient name cannot be empty.");
    }
    amount = trimmedAmt;
    name = trimmedName;
}
void Ingredient::scaleAmount(double ratio) {
if (ratio <= 0) {
        throw std::invalid_argument("Scale ratio must be greater than zero.");
    }

    m_amountValue *= ratio;

}

void Ingredient::displayIngredient() const {
    std::cout << amount << " " << m_name << std::endl;'
}
