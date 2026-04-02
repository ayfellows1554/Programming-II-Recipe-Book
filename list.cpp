#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include "List.h"

// trim helper
static std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;

    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;

    return s.substr(start, end - start);
}

List::List(const std::string& listName)
    : name(listName) {}

//Create a list
void List::createList(const std::string& recipe) {
    std::string trimmed = trim(recipe);

    if (trimmed.empty()) {
        throw std::invalid_argument("Recipe name cannot be empty.");
    }

    recipes.push_back(trimmed);
}

//Edit List
void List::editList(int index, const std::string& newRecipe) {
    if (index < 0 || index >= recipes.size()) {
        throw std::out_of_range("Invalid recipe index.");
    }

    std::string trimmed = trim(newRecipe);

    if (trimmed.empty()) {
        throw std::invalid_argument("Recipe name cannot be empty.");
    }

    recipes[index] = trimmed;
}

//Delete List
void List::deleteList(int index) {
    if (index < 0 || index >= recipes.size()) {
        throw std::out_of_range("Invalid recipe index.");
    }

    recipes.erase(recipes.begin() + index);
}

//Display
void List::displayLists() const {
    std::cout << "List: " << name << std::endl;
    for (const auto& recipe : recipes) {
        std::cout << "- " << recipe << std::endl;
    }
}
