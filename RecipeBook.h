#pragma once
#include <vector>
#include <string>
#include "recipe.h"

class RecipeBook {
private:
    std::vector<Recipe> m_recipes;

public:
    void addRecipe(const Recipe& r);
    bool deleteRecipe(const std::string& name);
    Recipe* findRecipe(const std::string& name);
    void displayAll() const;
};
