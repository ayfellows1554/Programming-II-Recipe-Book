#include <iostream>
#include <algorithm>
#include <cctype>
#include "RecipeBook.h"

// Adds a recipe to the book
void RecipeBook::addRecipe(Recipe r) {
    m_recipes.push_back(std::move(r));
}


// Returns true if a recipe was deleted, false if not found
bool RecipeBook::deleteRecipe(const std::string& name) {
    for (auto it = m_recipes.begin(); it != m_recipes.end(); ++it) {
        if (it->getRecipeName() == name) {
            m_recipes.erase(it);
            return true;
        }
    }
    return false;
}

// Returns a pointer to the recipe if found, nullptr if not
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

// Returns a vector of pointers to recipes that contain the ingredient (case-insensitive)
std::vector<Recipe*> RecipeBook::findRecipesByIngredient(const std::string& ingredientName)
{
    std::vector<Recipe*> results;

    for (auto& r : m_recipes)
    {
        for (const auto& ingPtr : r.getIngredients())
        {
            // Case-insensitive match
            std::string ingName = ingPtr->getName();
            std::string target = ingredientName;

            std::transform(ingName.begin(), ingName.end(), ingName.begin(), [](unsigned char c){ return std::tolower(c); });
            std::transform(target.begin(), target.end(), target.begin(), [](unsigned char c){ return std::tolower(c); });

            if (ingName.find(target) != std::string::npos)
            {
                results.push_back(&r);
                break;
            }
        }
    }

    return results;
}
