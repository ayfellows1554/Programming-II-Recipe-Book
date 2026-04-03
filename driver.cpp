#include <iostream>
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
// basic menu for now
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
// makes sure space is ignored
        cin.ignore(1000, '\n');

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

    } while (choice != 0);

    return 0;
}
