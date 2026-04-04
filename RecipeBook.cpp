#include "RecipeBook.h"
#include <algorithm>
#include <iostream>

// Add a recipe to the book
void RecipeBook::addRecipe(const Recipe& r) {
    m_recipes.push_back(r);
}

// Delete a recipe by name
bool RecipeBook::deleteRecipe(const std::string& name) {
    auto it = std::remove_if(m_recipes.begin(), m_recipes.end(),
        [&](const Recipe& r) {
            return r.getRecipeName() == name;
        });

    if (it == m_recipes.end()) {
        return false; // not found
    }

    m_recipes.erase(it, m_recipes.end());
    return true;
}

// Find a recipe by name (returns pointer or nullptr)
Recipe* RecipeBook::findRecipe(const std::string& name) {
    for (auto& r : m_recipes) {
        if (r.getRecipeName() == name) {
            return &r;
        }
    }
    return nullptr;
}

// Display all recipes in the book
void RecipeBook::displayAll() const {
    if (m_recipes.empty()) {
        std::cout << "No recipes in the book.\n";
        return;
    }

    for (const auto& r : m_recipes) {
        std::cout << r.displayRecipe() << "\n";
    }
}
