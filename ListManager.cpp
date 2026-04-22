#include <iostream>
#include <algorithm>
#include <cctype>
#include "ListManager.h"

// Trim helper (same as in List.cpp)
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

void ListManager::createList(const std::string& name) {
    std::string trimmed = trim(name);

    if (trimmed.empty()) {
        throw std::invalid_argument("List name cannot be empty.");
        return;
    }

    // Prevent duplicate list names
    for (const auto& list : m_lists) {
        if (list.getListName() == trimmed) {
            std::cout << "A list with that name already exists.\n";
            return;
        }
    }

    m_lists.emplace_back(trimmed);
    std::cout << "List \"" << trimmed << "\" created.\n";
}

bool ListManager::deleteList(const std::string& name) {
    std::string trimmed = trim(name);

    for (auto it = m_lists.begin(); it != m_lists.end(); ++it) {
        if (it->getListName() == trimmed) {
            m_lists.erase(it);
            return true;
        }
    }
    return false;
}

List* ListManager::getList(const std::string& name) {
    std::string trimmed = trim(name);

    for (auto& list : m_lists) {
        if (list.getListName() == trimmed) {
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
