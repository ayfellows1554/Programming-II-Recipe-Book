#include "ListManager.h"
#include <iostream>

void ListManager::createList(const std::string& name) {
    // Prevent duplicate list names
    for (const auto& list : m_lists) {
        if (list.getListName() == name) {
            std::cout << "A list with that name already exists.\n";
            return;
        }
    }

    m_lists.emplace_back(name);
    std::cout << "List \"" << name << "\" created.\n";
}

bool ListManager::deleteList(const std::string& name) {
    for (auto it = m_lists.begin(); it != m_lists.end(); ++it) {
        if (it->getListName() == name) {
            m_lists.erase(it);
            return true;
        }
    }
    return false;
}

List* ListManager::getList(const std::string& name) {
    for (auto& list : m_lists) {
        if (list.getListName() == name) {
            return &list;
        }
    }
    return nullptr;
}

void ListManager::displayAllLists() const {
    if (m_lists.empty()) {
        std::cout << "No lists created.\n";
        return;
    }

    std::cout << "Your Lists:\n";
    for (const auto& list : m_lists) {
        std::cout << " - " << list.getListName() << "\n";
    }
}
