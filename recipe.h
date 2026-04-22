#pragma once
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "IngredientBase.h"
#include "Instructions.h"

// Represents a complete recipe, including name, category, ingredients, instructions, cook time, and servings
class Recipe {
public:

    // Constructors
    Recipe(std::string name, std::string category);
    Recipe() = default;

    //Disable copying
    Recipe(const Recipe&) = delete;
    Recipe& operator=(const Recipe&) = delete;

    //Enable moving
    Recipe(Recipe&&) noexcept = default;
    Recipe& operator=(Recipe&&) noexcept = default;

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

    // Ingredient management (polymorphic)
    void addIngredient(std::unique_ptr<IngredientBase> ing);
    void clearIngredients();
    
    const std::vector<std::unique_ptr<IngredientBase>>& getIngredients() const { return m_ingredients; }
    const Instructions& getInstructions() const { return m_instructions; }
    std::vector<std::unique_ptr<IngredientBase>>& getIngredients() { return m_ingredients; }
    Instructions& getInstructions() { return m_instructions; }

    // Instruction management
    void addInstruction(const std::string& step);
    void clearInstructions();


    // Validate entire recipe
    void validate() const;

    // Display
    std::string displayRecipe() const;

private:
    // Basic fields
    std::string m_name;
    std::string m_category;

    // Ingredients + instructions
    std::vector<std::unique_ptr<IngredientBase>> m_ingredients;
    Instructions m_instructions;

    // Serving size (default 1)
    int m_servings{ 1 };

    // Cook time (default 0)
    int m_cookTimeMinutes{ 0 };
};
