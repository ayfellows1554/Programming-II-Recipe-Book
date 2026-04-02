#include <format>
#include <algorithm>
#include <cctype>
#include <stdexcept>
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

//Error Handling
void Recipe::validate() const {
    if (m_name.empty()) {
        throw std::invalid_argument("Recipe must have a name.");
    }
    if (m_ingredients.empty()) {
        throw std::invalid_argument("Recipe must have at least one ingredient.");
    }
    if (m_instructions.empty()) {
        throw std::invalid_argument("Recipe must have at least one instruction.");
    }
    if (m_cookTimeMinutes < 0) {
        throw std::invalid_argument("Cook time cannot be negative.");
    }
    if (m_servings <= 0) {
        throw std::invalid_argument("Servings must be greater than zero.");
    }
}


//Getters
std::string Recipe::getRecipeName() { return m_name; }
std::string Recipe::getRecipeCategory() { return m_category; }

//Display for the recipe
std::string Recipe::displayRecipe() {
	return std::format("\"{}\"\nCategory: {}\nServings: {}\nIngredients: \nInstructions: \n", getRecipeName(), getRecipeCategory(), getServings());
}

