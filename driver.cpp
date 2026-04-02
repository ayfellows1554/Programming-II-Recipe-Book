// Recipe Book driver (main code)
#include <iostream>
#include <string>
#include <format>
#include "recipe.h"
#include "instructions.h"

int main() {
    std::string name;
    std::string category;
	std::string servingsInput;
	int servings = 1;

    while (true) {
        try { 
			//Name
			std::cout << "Enter recipe name (or type CANCEL): ";
            std::getline(std::cin, name);

            if (name == "CANCEL" || name == "cancel") {
                std::cout << "Operation cancelled.\n";
                return 0;
            }

            //Category
			std::cout << "Enter recipe category (or type CANCEL): ";
            std::getline(std::cin, category);

            if (category == "CANCEL" || category == "cancel") {
                std::cout << "Operation cancelled.\n";
                return 0;
            }

            //Serving Size
			while (true) {
                std::cout << "Enter serving size (positive number): ";
                std::getline(std::cin, servingsInput);

                if (servingsInput == "CANCEL" || servingsInput == "cancel") {
                    std::cout << "Operation cancelled.\n";
                    return 0;
                }

                try {
                    servings = std::stoi(servingsInput);

                    if (servings <= 0) {
                        std::cout << "Serving size must be greater than zero.\n";
                        continue;
                    }

                    break; // valid serving size

                } catch (...) {
                    std::cout << "Invalid number. Please enter a positive integer.";
                }
            }

			//Construct Recipe
			Recipe recipe1(name, category);
			recipe1.setServings(servings);
			std::cout<<"\nRecipe created successfully:\n";
			std::cout<< recipe1.displayRecipe();
			
			// This will throw if name/category are empty or whitespace
            Recipe recipe1(name, category);

            std::cout << "\nRecipe created successfully:\n";
            std::cout << recipe1.displayRecipe();

            break; // success → exit loop

        } catch (const std::exception& ex) {
            std::cout << "\nError: " << ex.what() << "\n";
            std::cout << "Please try again.\n\n";
        }
    }
	return 0;
}




 
