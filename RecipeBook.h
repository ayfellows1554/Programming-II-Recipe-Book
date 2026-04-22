#pragma once
#include <vector>
#include <string>
#include "Recipe.h"


class RecipeBook {
private:
    std::vector<Recipe> m_recipes;

public:
    const std::vector<Recipe>& getAllRecipes() const { return m_recipes; }

    bool deleteRecipe(const std::string& name);
    Recipe* findRecipe(const std::string& name);
    std::vector<Recipe*> findRecipesByIngredient(const std::string& ingredientName);
    void displayAll() const;
    void clearAll() { m_recipes.clear(); }
    void addRecipe(Recipe r);
};
