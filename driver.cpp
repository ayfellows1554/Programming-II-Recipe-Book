#include <iostream>
#include <limits>
#include "recipe.h"
#include "list.h"

using namespace std;

// Placeholder functions (to be implemented later)
void createRecipe() {
    cout << "Create Recipe feature...\n";
}

void searchRecipes() {
    cout << "Search Recipe feature...\n";
}

void viewLists() {
    cout << "View Lists feature...\n";
}

void showMenu() {
    cout << "\n****** Recipe Manager ******\n";
    cout << "1. Create Recipe\n";
    cout << "2. Search Recipes\n";
    cout << "3. View Lists\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    do {
        showMenu();

        cin >> choice;

        // Handle any errors for letters, symbols, empty input, etc.
        if (cin.fail()) {
            cin.clear(); // reset fail state
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        // Clear leftover newline
        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        try {
            switch (choice) {
                case 1:
                    createRecipe();
                    break;

                case 2:
                    searchRecipes();
                    break;

                case 3:
                    viewLists();
                    break;

                case 0:
                    cout << "Thank you for using our Recipe Book!\n";
                    break;

                default:
                    cout << "Invalid choice. Try again.\n";
            }
        }
        catch (const std::invalid_argument& e) {
            cout << "Input Error: " << e.what() << "\n";
        }
        catch (const std::out_of_range& e) {
            cout << "Range Error: " << e.what() << "\n";
        }
        catch (const std::runtime_error& e) {
            cout << "Error: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            cout << "Unexpected Error: " << e.what() << "\n";
        }

    } while (choice != 0);

    return 0;
}
