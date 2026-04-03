#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include "instructions.h"

// Trim helper
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

// Validate a step string according to all your rules
static void validateStep(const std::string& step) {
    std::string trimmed = trim(step);

    if (trimmed.empty()) {
        throw std::invalid_argument("Instruction step cannot be empty.");
    }

    // Reject punctuation-only steps
    bool onlyPunct = true;
    for (char c : trimmed) {
        if (!std::ispunct(static_cast<unsigned char>(c))) {
            onlyPunct = false;
            break;
        }
    }
    if (onlyPunct) {
        throw std::invalid_argument("Instruction step cannot contain only punctuation.");
    }

    // Reject control characters
    for (char c : trimmed) {
        if (std::iscntrl(static_cast<unsigned char>(c))) {
            throw std::invalid_argument("Instruction contains invalid characters.");
        }
    }

    // Reject overly long steps (optional limit)
    if (trimmed.size() > 500) {
        throw std::invalid_argument("Instruction step is too long.");
    }
}

// Add a step
void Instructions::addStep(const std::string& step) {
    validateStep(step);
    steps.push_back(trim(step));
}

// Insert a step at a specific index
void Instructions::insertStep(int index, const std::string& step) {
    if (index < 0 || index > static_cast<int>(steps.size())) {
        throw std::out_of_range("Invalid step index.");
    }

    validateStep(step);
    steps.insert(steps.begin() + index, trim(step));
}

// Remove a step
void Instructions::removeStep(int index) {
    if (index < 0 || index >= static_cast<int>(steps.size())) {
        throw std::out_of_range("Invalid step index.");
    }

    steps.erase(steps.begin() + index);
}

// Edit an existing step
void Instructions::editStep(int index, const std::string& newStep) {
    if (index < 0 || index >= static_cast<int>(steps.size())) {
        throw std::out_of_range("Invalid step index.");
    }

    validateStep(newStep);
    steps[index] = trim(newStep);
}

// Clear all steps
void Instructions::clear() {
    steps.clear();
}

// Get a single step
const std::string& Instructions::getStep(int index) const {
    if (index < 0 || index >= static_cast<int>(steps.size())) {
        throw std::out_of_range("Invalid step index.");
    }
    return steps[index];
}

// Get all steps
const std::vector<std::string>& Instructions::getSteps() const {
    return steps;
}

// Check if empty
bool Instructions::empty() const {
    return steps.empty();
}
