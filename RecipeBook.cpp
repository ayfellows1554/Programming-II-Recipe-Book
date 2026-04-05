#include <iostream>
#include "RecipeBook.h"

void RecipeBook::addRecipe(const Recipe& r) {
    m_recipes.push_back(r);
}

bool RecipeBook::deleteRecipe(const std::string& name) {
    for (auto it = m_recipes.begin(); it != m_recipes.end(); ++it) {
        if (it->getRecipeName() == name) {
            m_recipes.erase(it);
            return true;
        }
    }
    return false;
}

Recipe* RecipeBook::findRecipe(const std::string& name) {
    for (auto& r : m_recipes) {
        if (r.getRecipeName() == name) return &r;
    }
    return nullptr;
}

void RecipeBook::displayAll() const {
    if (m_recipes.empty()) {
        std::cout << "No recipes in the book yet.\n";
        return;
    }
    for (const auto& r : m_recipes) {
        std::cout << r.displayRecipe() << "\n";
    }
}
