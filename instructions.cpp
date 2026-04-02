#include <iostream>
#include <format>
#include "instructions.h"

// ************ INSTRUCTIONS ************
// code by Camila
//Code by Grace

#include "instructions.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>

// trim helper
static std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start]))) ++start;

    size_t end = s.size();
    while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;

    return s.substr(start, end - start);
}

void Instructions::addStep(const std::string& step) {
    std::string trimmed = trim(step);

    if (trimmed.empty()) {
        throw std::invalid_argument("Instruction step cannot be empty.");
    }

    steps.push_back(trimmed);
}

//Way to insert steps
void Instructions::insertStep(int index, const std::string& step) {
    if (index < 0 || index > static_cast<int>(steps.size())) {
        throw std::out_of_range("Invalid step index.");
    }

    std::string trimmed = trim(step);

    if (trimmed.empty()) {
        throw std::invalid_argument("Instruction step cannot be empty.");
    }

    steps.insert(steps.begin() + index, trimmed);
}

//Removes the instruction steps
void Instructions::removeStep(int index) {
    if (index < 0 || index >= static_cast<int>(steps.size())) {
        throw std::out_of_range("Invalid step index.");
    }

    steps.erase(steps.begin() + index);
}

const std::vector<std::string>& Instructions::getSteps() const {
    return steps;
}
