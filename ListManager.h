#pragma once
#include <vector>
#include <string>
#include "List.h"

class ListManager {
private:
    std::vector<List> m_lists;

public:
    void createList(const std::string& name);
    bool deleteList(const std::string& name);

    List* getList(const std::string& name);

    void displayAllLists() const;
};
