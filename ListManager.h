#pragma once
#include <vector>
#include <string>
#include "list.h"

class ListManager {
private:
    std::vector<List> m_lists;

public:
    //Create List
    void createList(const std::string& name);
    //Delete List
    bool deleteList(const std::string& name);

    List* getList(const std::string& name);

    // Add getter for dialogs
    const std::vector<List>& getLists() const { return m_lists; }

    //Display List
    void displayAllLists() const;

};
