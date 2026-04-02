#pragma once
#include <string>
#include <vector>

class List {
private:
    std::string name;
    std::vector<std::string> recipes;

public:
    List(const std::string& listName);

    void createList(const std::string& recipe);
    void editList(int index, const std::string& newRecipe);
    void deleteList(int index);
    void displayLists() const;
};
