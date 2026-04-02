#include <iostream>
#include "List.h"

List::List(const std::string& listName)
    : name(listName) {}

void List::createList(const std::string& recipe) {
    recipes.push_back(recipe);
}

void List::editList(int index, const std::string& newRecipe) {
    if (index >= 0 && index < recipes.size()) {
        recipes[index] = newRecipe;
    }
}

void List::deleteList(int index) {
    if (index >= 0 && index < recipes.size()) {
        recipes.erase(recipes.begin() + index);
    }
}

void List::displayLists() const {
    std::cout << "List: " << name << std::endl;
    for (const auto& recipe : recipes) {
        std::cout << "- " << recipe << std::endl;
    }
}
