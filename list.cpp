#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include "list.h"

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

// Validate recipe name according to your rules
static void validateRecipeName(const std::string& name) {
    std::string trimmed = trim(name);

    if (trimmed.empty()) {
        throw std::invalid_argument("Recipe name cannot be empty.");
    }

    // Reject punctuation-only names
    bool onlyPunct = true;
    for (char c : trimmed) {
        if (!std::ispunct(static_cast<unsigned char>(c))) {
            onlyPunct = false;
            break;
        }
    }
    if (onlyPunct) {
        throw std::invalid_argument("Recipe name cannot contain only punctuation.");
    }

    // Reject control characters
    for (char c : trimmed) {
        if (std::iscntrl(static_cast<unsigned char>(c))) {
            throw std::invalid_argument("Recipe name contains invalid characters.");
        }
    }

    // Reject overly long names
    if (trimmed.size() > 100) {
        throw std::invalid_argument("Recipe name is too long.");
    }
}

List::List(const std::string& listName)
    : name(trim(listName))
{
    if (this->name.empty()) {
        throw std::invalid_argument("List name cannot be empty.");
    }
}

// Create a list entry
void List::createList(const std::string& recipe) {
    validateRecipeName(recipe);
    std::string trimmed = trim(recipe);

    // Prevent duplicates
    auto it = std::find(recipes.begin(), recipes.end(), trimmed);
    if (it != recipes.end()) {
        throw std::invalid_argument("Recipe already exists in this list.");
    }

    recipes.push_back(trimmed);
}

// Edit a recipe name
void List::editList(int index, const std::string& newRecipe) {
    if (index < 0 || index >= static_cast<int>(recipes.size())) {
        throw std::out_of_range("Invalid recipe index.");
    }

    validateRecipeName(newRecipe);
    std::string trimmed = trim(newRecipe);

    // Prevent duplicates (except if editing to same name)
    for (int i = 0; i < recipes.size(); ++i) {
        if (i != index && recipes[i] == trimmed) {
            throw std::invalid_argument("Another recipe with this name already exists.");
        }
    }

    recipes[index] = trimmed;
}

// Delete a recipe
void List::deleteList(int index) {
    if (index < 0 || index >= static_cast<int>(recipes.size())) {
        throw std::out_of_range("Invalid recipe index.");
    }

    recipes.erase(recipes.begin() + index);
}

// Get a single recipe
const std::string& List::getRecipe(int index) const {
    if (index < 0 || index >= static_cast<int>(recipes.size())) {
        throw std::out_of_range("Invalid recipe index.");
    }
    return recipes[index];
}

// Clear all recipes
void List::clear() {
    recipes.clear();
}

// Check if empty
bool List::empty() const {
    return recipes.empty();
}

// Display list
void List::displayLists() const {
    std::cout << "List: " << name << std::endl;

    if (recipes.empty()) {
        std::cout << "(No recipes in this list)\n";
        return;
    }

    for (const auto& recipe : recipes) {
        std::cout << "- " << recipe << std::endl;
    }
}
