//NOTE: this file is not needed for wxWidgets to run. There is a MainFrame.cpp where the program runs from //

#include <iostream>
#include <limits>
#include "recipe.h"
#include "list.h"
#include "RecipeBook.h"
#include "ListManager.h"
#include "ingredient.h"
#include "instructions.h"
using namespace std;

// Create a new recipe by prompting the user for details and adding it to the recipe book
void createRecipe(RecipeBook& book) {
    std::string name, category;
    int servings, cookTime;

    cout << "Enter recipe name: ";
    std::getline(cin, name);

    cout << "Enter category: ";
    std::getline(cin, category);

    cout << "Enter servings: ";
    cin >> servings;
    cin.ignore(1000, '\n');

    cout << "Enter cook time (minutes): ";
    cin >> cookTime;
    cin.ignore(1000, '\n');

    Recipe r(name, category);
    r.setServings(servings);
    r.setCookTime(cookTime);

    // INGREDIENTS
    cout << "How many ingredients? ";
    int count;
    cin >> count;
    cin.ignore(1000, '\n');

    for (int i = 0; i < count; i++) {
        string ingName, unit;
        double amount;

        cout << "Ingredient " << (i + 1) << " name: ";
        std::getline(cin, ingName);

        cout << "Amount: ";
        cin >> amount;
        cin.ignore(1000, '\n');

        cout << "Unit: ";
        std::getline(cin, unit);
        
        r.addIngredient(std::make_unique<Ingredient>(amount, unit, ingName));
    }

    // INSTRUCTIONS
    cout << "How many steps? ";
    cin >> count;
    cin.ignore(1000, '\n');

    for (int i = 0; i < count; i++) {
        string step;
        cout << "Step " << (i + 1) << ": ";
        std::getline(cin, step);
        r.addInstruction(step);
    }

    // Validate and add
    try {
        r.validate();
        book.addRecipe(std::move(r));
        cout << "Recipe added successfully!\n";
    }
    catch (const std::exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
}

// Search for a recipe by name and display its details
void searchRecipes(RecipeBook& book) {
    string name;
    cout << "Enter recipe name to search: ";
    std::getline(cin, name);

    Recipe* r = book.findRecipe(name);

    if (!r) {
        cout << "Recipe not found.\n";
        return;
    }

    cout << r->displayRecipe();
}


void viewLists(RecipeBook& book, ListManager& manager) {
    int choice = -1;

    do {
        cout << "\n****** List Manager ******\n";
        cout << "1. View All Lists\n";
        cout << "2. Create New List\n";
        cout << "3. Delete a List\n";
        cout << "4. View List Contents\n";
        cout << "5. Add Recipe to List\n";
        cout << "6. Remove Recipe from List\n";
        cout << "0. Return to Main Menu\n";
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        try {
            switch (choice) {

                // ---------------------------------------------------------
                // 1. View all lists
                // ---------------------------------------------------------
            case 1: {
                manager.displayAllLists();
                break;
            }

                  // ---------------------------------------------------------
                  // 2. Create a new list
                  // ---------------------------------------------------------
            case 2: {
                string name;
                cout << "Enter new list name: ";
                getline(cin, name);

                manager.createList(name);
                break;
            }

                  // ---------------------------------------------------------
                  // 3. Delete a list
                  // ---------------------------------------------------------
            case 3: {
                string name;
                cout << "Enter list name to delete: ";
                getline(cin, name);

                if (manager.deleteList(name))
                    cout << "List deleted.\n";
                else
                    cout << "List not found.\n";

                break;
            }

                  // ---------------------------------------------------------
                  // 4. View list contents
                  // ---------------------------------------------------------
            case 4: {
                string name;
                cout << "Enter list name: ";
                getline(cin, name);

                List* list = manager.getList(name);
                if (!list) {
                    cout << "List not found.\n";
                    break;
                }

                list->displayLists();
                break;
            }

                  // ---------------------------------------------------------
                  // 5. Add recipe to list
                  // ---------------------------------------------------------
            case 5: {
                string listName, recipeName;

                cout << "Enter list name: ";
                getline(cin, listName);

                List* list = manager.getList(listName);
                if (!list) {
                    cout << "List not found.\n";
                    break;
                }

                cout << "Enter recipe name to add: ";
                getline(cin, recipeName);

                // Validate recipe exists in RecipeBook
                if (!book.findRecipe(recipeName)) {
                    cout << "Recipe not found in RecipeBook.\n";
                    break;
                }

                list->createList(recipeName);
                cout << "Recipe added.\n";
                break;
            }

                  // ---------------------------------------------------------
                  // 6. Remove recipe from list
                  // ---------------------------------------------------------
            case 6: {
                string listName, recipeName;

                cout << "Enter list name: ";
                getline(cin, listName);

                List* list = manager.getList(listName);
                if (!list) {
                    cout << "List not found.\n";
                    break;
                }

                cout << "Enter recipe name to remove: ";
                getline(cin, recipeName);

                bool found = false;

                for (int i = 0; i < list->size(); i++) {
                    if (list->getRecipe(i) == recipeName) {
                        list->deleteList(i);
                        found = true;
                        break;
                    }
                }

                if (!found)
                    cout << "Recipe not found in this list.\n";
                else
                    cout << "Recipe removed.\n";

                break;
            }

                  // ---------------------------------------------------------
                  // Exit
                  // ---------------------------------------------------------
            case 0:
                cout << "Returning to main menu...\n";
                break;

            default:
                cout << "Invalid choice.\n";
                break;
            }
        }
        catch (const std::exception& e) {
            cout << "Error: " << e.what() << "\n";
        }

    } while (choice != 0);
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
    RecipeBook recipeBook;
    ListManager listManager;
    
   
    int choice = -1;

    do {
        showMenu();
        std::cin >> choice;

        // Handle letters, symbols, empty input, etc.
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;  // restart loop safely
        }

        // Clear leftover newline
        std::cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

        try {
            switch (choice) {
            case 1:
                createRecipe(recipeBook);
                break;

            case 2:
                searchRecipes(recipeBook);
                break;

            case 3:
                viewLists(recipeBook, listManager);
                break;

            case 0:
                cout << "Thank you for using our Recipe Book!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
                break;
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
