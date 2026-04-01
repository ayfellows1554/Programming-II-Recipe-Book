#pragma once
#include <string>
#include <string_view>
#include <vector>

// ************ INSTRUCTIONS ************
// code by Camila

class Instructions {	// Each Instructions obj belongs to its respective Recipe
public:
	// FIGURE OUT CONSTRUCTION!!!!

	// Use vector index to find step -> manip it?
	void addStep(int index) {};
	void removeStep(int index) {};

private:
	std::vector<std::string> steps{}; // vector of steps (which are strings)
};
