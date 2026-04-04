#pragma once
#include <string>
#include <vector>
#include "Ingredient.h"
#include "instructions.h"

// ************ RECIPE ************
// code by Camila & Grace

class Recipe {
public:
    // Constructor
    Recipe(std::string name, std::string category);

    // Name
    void setRecipeName(std::string name);
    const std::string& getRecipeName() const;

    // Category
    void setRecipeCategory(std::string category);
    const std::string& getRecipeCategory() const;

    // Cook time
    void setCookTime(int minutes);
    int getCookTime() const { return m_cookTimeMinutes; }

    // Serving size
    void setServings(int servings);
    int getServings() const;

    // Scale servings
    void scaleServings(int newServings);

    // Ingredient management
    void addIngredient(const Ingredient& ing);
    void clearIngredients();
    const std::vector<Ingredient>& getIngredients() const { return m_ingredients; }

    // Instruction management
    void addInstruction(const std::string& step);
    void clearInstructions();
    const Instructions& getInstructions() const { return m_instructions; }

    // Validate entire recipe
    void validate() const;

    // Display
    std::string displayRecipe();

private:
    // Basic fields
    std::string m_name;
    std::string m_category;

    // Ingredients + instructions
    std::vector<Ingredient> m_ingredients;
    Instructions m_instructions;

    // Serving size (default 1)
    int m_servings{1};

    // Cook time (default 0)
    int m_cookTimeMinutes{0};
};

