#pragma once
#include <string>
#include <vector>

// ************ INSTRUCTIONS ************
// code by Camila & Grace

class Instructions {
public:
    // Add a new step at the end
    void addStep(const std::string& step);

    // Insert a step at a specific index
    void insertStep(int index, const std::string& step);

    // Remove a step by index
    void removeStep(int index);

    // Edit an existing step
    void editStep(int index, const std::string& newStep);

    // Clear all steps
    void clear();

    // Get a single step
    const std::string& getStep(int index) const;

    // Get all steps
    const std::vector<std::string>& getSteps() const;

    // Check if there are no steps
    bool empty() const;

private:
    std::vector<std::string> steps; // vector of instruction steps
};
