#include <iostream>
#include <format>
#include "recipe.h"

// ************ RECIPE ************
// code by Camila
Recipe::Recipe(std::string name, std::string category) {
	setRecipeName(name);
	setRecipeCategory(category);
}

// ERROR HANDLING for setters when strings are empty

void Recipe::setRecipeName(std::string name) {
	m_name = name;
	// implement validation
} 
std::string Recipe::getRecipeName() { return m_name; }

void Recipe::setRecipeCategory(std::string category) {
	m_category = category;
	// implement validation
} 
std::string Recipe::getRecipeCategory() { return m_category; }



std::string Recipe::displayRecipe() {
	return std::format("\"{}\"\nCategory: {}\nIngredients: \nInstructions: \n", getRecipeName(), getRecipeCategory());
}

// code by [name]
