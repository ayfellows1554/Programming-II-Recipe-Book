#pragma once
#include <string>
#include <string_view>
#include <vector>

// ************ INSTRUCTIONS ************
// code by Camila

class Instructions {	// Each Instructions obj belongs to its respective Recipe
public:
	void addStep(const std::string& step);
	void insertStep(int index, const std::string& step);
	void removeStep(int index);

	const std::vecotr<std::string>& getSteps() const;

private:
	std::vector<std::string> steps{}; // vector of steps (which are strings)
};
