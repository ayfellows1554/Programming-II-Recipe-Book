#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <sstream>
#include <ostream>
#include "Recipe.h"

// Trim helper
static std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) {
        ++start;
    }

    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) {
        --end;
    }
    return s.substr(start, end - start);
}

// Validate name/category
static void validateStringField(const std::string& field, const std::string& fieldName) {
    std::string trimmed = trim(field);
    if (trimmed.empty()) {
        throw std::invalid_argument(fieldName + " cannot be empty.");
    }

    // Reject punctuation-only
    bool onlyPunct = true;
    for (char c : trimmed) {
        if (!std::ispunct(static_cast<unsigned char>(c))) {
            onlyPunct = false;
            break;
        }
    }
    if (onlyPunct) {
        throw std::invalid_argument(fieldName + " cannot contain only punctuation.");
    }

    // Reject control characters
    for (char c : trimmed) {
        if (std::iscntrl(static_cast<unsigned char>(c))) {
            throw std::invalid_argument(fieldName + " contains invalid characters.");
        }
    }

    // Reject overly long fields
    if (trimmed.size() > 100) {
        throw std::invalid_argument(fieldName + " is too long.");
    }
}

// Constructor
Recipe::Recipe(std::string name, std::string category)
    : m_cookTimeMinutes(0), m_servings(1)
{
    setRecipeName(std::move(name));
    setRecipeCategory(std::move(category));
}

// Setters with validation
void Recipe::setRecipeName(std::string name) {
    validateStringField(name, "Recipe name");
    m_name = trim(name);
}

void Recipe::setRecipeCategory(std::string category) {
    validateStringField(category, "Recipe category");
    m_category = trim(category);
}

// Cook time setter
void Recipe::setCookTime(int minutes) {
    if (minutes < 0) {
        throw std::invalid_argument("Cook time cannot be negative.");
    }
    m_cookTimeMinutes = minutes;
}

// Serving sizes
void Recipe::setServings(int servings) {
    if (servings <= 0) {
        throw std::invalid_argument("Servings must be greater than zero.");
    }
    m_servings = servings;
}

int Recipe::getServings() const {
    return m_servings;
}

// Serving size scaling
void Recipe::scaleServings(int newServings) {
    if (newServings <= 0) {
        throw std::invalid_argument("New serving size must be greater than zero.");
    }

    double ratio = static_cast<double>(newServings) / m_servings;

    // Scale ingredients
    for (auto& ingredient : m_ingredients) {
        ingredient->scaleAmount(ratio);
    }
    m_servings = newServings;
}

// Ingredient management
void Recipe::addIngredient(std::unique_ptr<IngredientBase> ing) {
    m_ingredients.push_back(std::move(ing));
}

void Recipe::clearIngredients() {
    m_ingredients.clear();
}

// Instruction management
void Recipe::addInstruction(const std::string& step) {
    if (trim(step).empty()) {
        throw std::invalid_argument("Instruction step cannot be empty.");
    }
    m_instructions.addStep(step);
}

void Recipe::clearInstructions() {
    m_instructions.clear();
}

// Validation for entire recipe
void Recipe::validate() const {
    if (m_name.empty()) {
        throw std::invalid_argument("Recipe must have a name.");
    }
    if (m_category.empty()) {
        throw std::invalid_argument("Recipe must have a category.");
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

// Getters
const std::string& Recipe::getRecipeName() const { return m_name; }
const std::string& Recipe::getRecipeCategory() const { return m_category; }

// Display recipe
std::string Recipe::displayRecipe() const {
    std::ostringstream out;
    out << m_name << "\n";
    out << "Category: " << m_category << "\n";
    out << "Servings: " << m_servings << "\n";
    out << "Cook Time: " << m_cookTimeMinutes << " minutes\n\n";
    out << "Ingredients:\n";

    for (const auto& ing : m_ingredients) {
        out << " - " << ing->getAmountValue() << " "
            << ing->getUnit() << " " << ing->getName() << "\n";
    }

    out << "\nInstructions:\n";
    int stepNum = 1;
    for (const auto& step : m_instructions.getSteps()) {
        out << " " << stepNum++ << ". " << step << "\n";
    }
    return out.str();
}
