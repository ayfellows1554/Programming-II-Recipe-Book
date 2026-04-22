#pragma once
#include <string>
#include <vector>

class List {
private:
    std::string name;                 // Name of the list/category
    std::vector<std::string> recipes; // Stored recipe names

public:
    // Constructor
    List(const std::string& listName);

    // Add a recipe to the list
    void createList(const std::string& recipe);

    // Edit an existing recipe name
    void editList(int index, const std::string& newRecipe);

    // Delete a recipe by index
    void deleteList(int index);

    // Remove all recipes
    void clear();

    // Check if the list is empty
    bool empty() const;

    // Display all recipes in the list
    void displayLists() const;

    // Get a single recipe by index
    const std::string& getRecipe(int index) const;

    // Get the list name
    const std::string& getListName() const { return name; }

    //expose size() to help menus
    //loop through recipes.size() instead of calling empty() to avoid double lookup
    int size() const { return static_cast<int>(recipes.size()); }
};
