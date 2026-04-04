#pragma once
#include <vector>
#include <string>
#include "List.h"

class ListManager {
private:
    std::vector<List> m_lists;

public:
    //Create List
    void createList(const std::string& name);
    //Delete List
    bool deleteList(const std::string& name);

    List* getList(const std::string& name);

    //Display List
    void displayAllLists() const;
   
};
