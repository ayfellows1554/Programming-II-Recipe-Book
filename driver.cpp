// Recipe Book driver (main code)
#include <iostream>
#include <string>
#include <format>
#include "recipe.h"
#include "instructions.h"

int main() {
	std::string name;
	std::string category;
	// Let user create recipe

	std::cout << "Enter recipe name: ";
	getline(std::cin, name);

	std::cout << "Enter recipe category: ";
	getline(std::cin, category);

	Recipe recipe1(name, category);
	std::cout << recipe1.displayRecipe();
	return 0;
}

 