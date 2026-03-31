#include <iostream>
#include <format>
#include "classes.h"

// ************ RECIPE ************
// code by Camila
Recipe::Recipe(std::string name, std::string category)
	: m_name{ name }, m_category{ category } {}

// ERROR HANDLING for setters when strings are empty

void Recipe::setRecipeName(std::string name) { m_name = name; }
std::string Recipe::getRecipeName() { return m_name; }

void Recipe::setRecipeCategory(std::string category) { m_category = category; }
std::string Recipe::getRecipeCategory() { return m_category; }



std::string Recipe::displayRecipe() {
	return std::format("\"{}\"\nCategory: {}\nIngredients: \nInstructions: \n", getRecipeName(), getRecipeCategory());
}

// code by [name]
