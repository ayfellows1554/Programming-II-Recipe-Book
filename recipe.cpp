#include <format>
#include <algorithm>
#include <cctpye>
#include "recipe.h"

// ************ RECIPE ************
// code by Camila

//This defines the trim() function, so the strings will automatically be trimmed before being saved
static std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;

    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;

    return s.substr(start, end - start);
}

//Constructor
Recipe::Recipe(std::string name, std::string category) {
	setRecipeName(name);
	setRecipeCategory(category);
}

// Setters with validation
void Recipe::setRecipeName(std::string name) {
    name = trim(name);

    if (name.empty()) {
        throw std::invalid_argument("Recipe name cannot be empty.");
    }

    m_name = name;
}

void Recipe::setRecipeCategory(std::string category) {
    category = trim(category);

    if (category.empty()) {
        throw std::invalid_argument("Recipe category cannot be empty.");
    }

    m_category = category;
}

//Serving Sizes 
void Recipe::setServings(int servings) {
    if (servings <= 0) {
        throw std::invalid_argument("Servings must be greater than zero.");
    }
    m_servings = servings;
}

int Recipe::getServings() const {
    return m_servings;
}

//Serving Size Scaling with the error inside
void Recipe::scaleServings(int newServings) {
    if (newServings <= 0) {
        throw std::invalid_argument("New serving size must be greater than zero.");
    }

    double ratio = static_cast<double>(newServings) / m_servings;

    // When you add ingredients later:
    // for (auto& ingredient : m_ingredients) {
    //     ingredient.scaleAmount(ratio);
    // }

    m_servings = newServings;
}

std::string Recipe::getRecipeName() { return m_name; }

std::string Recipe::getRecipeCategory() { return m_category; }

//Display for the recipe
std::string Recipe::displayRecipe() {
	return std::format("\"{}\"\nCategory: {}\nIngredients: \nInstructions: \n", getRecipeName(), getRecipeCategory(), getServings());
}

