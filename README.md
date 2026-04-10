# Programming II Recipe Book
A recipe book that allows users to browse and organize their favorite recipes.

---

## Team Members
- Kris Fellows
- Gabriela Diaz Olivera
- Camila Vaca
- Grace HIlton

---

## How to Run

### Requirements
- C++ compiler like CLion, Visual Studios
- GUI framework used (as applicable): TBD

### Steps
1. Clone the repository:
git clone <https://github.com/ayfellows1554/Programming-II-Recipe-Book.git>
2. Open the project in your IDE (e.g., Visual Studio)
3. Build the project
4. Run the application

Other steps are TBD

### Notes
- If using Visual Studio:
- Open the `.sln` file
- Press **F5** to run
- If using another setup, provide specific instructions here

TBD

---

## Features
-Add, Delete, and Modify recipes

-Change the number of servings (a manual button)

-Search for existing recipes

-Make your own collections of recipes


---

## OOP Concepts Used

### Encapsulation
Encapsulation occurs through the system by ensuring that each class owns and protects its data. The Recipe class stores its name, category, ingredients, and instructions as private members. This means that no outside code can change anything related to that class. The Instruction class keeps its (vector<string>step) private, but has addStep() and removeStep() public so the steps can be validated before being added. We also added a RecipeBook (a recipe manager) class and a ListManager class. The RecipeBook stores the data of the recipes, and only this class can add, delete, or retrieve those recipes. The ListManager works the same way with the lists and keeps that info private, but it has functions like createList() and deleteList() public, so the actual list data can not be altered from anything else.

### Inheritance
We currently do not have any inheritance classes. But it would be something easy to do.

### Polymorphism
Overloading:
First, we use overloading in places where multiple versions of a function share the same name but accept different parameters. For example, the Instruction class may include both addStep(const std::string&) and addStep(int index, const std::string&), allowing steps to be added either at the end or at a specific position. This is compile‑time polymorphism because the compiler decides which version to call based on the argument list. 

Virtual Function:

Second, our design supports runtime polymorphism through virtual functions. If the Recipe class declares virtual void displayRecipe() const, then any subclass—such as a future DessertRecipe or DinnerRecipe—can override that function with its own formatting. When a Recipe* pointer stored inside RecipeManager calls displayRecipe(), C++ will automatically invoke the correct overridden version based on the object’s actual type, not the pointer type. We currently do not have any subclasses yet, but the structure of displayIngredient(), displaySteps(), and displayRecipe() functions already follows the polymorphic pattern of “each object knows how to display itself.”

### Composition
RecipeBook has-a to Recipe
ListManager has-a to List
List has-a to Recipe
Recipe has-a to Ingredient
Recipe has-a to Instructions
Instructions has-a to steps(vector<string>)

Our project uses composition extensively to build larger objects out of smaller, tightly‑bound components. RecipeBook is composed of Recipe objects stored in a private vector, and ListManager is composed of List objects in the same way. Each List is composed of its own collection of Recipe objects, while each Recipe is composed of a vector<Ingredient> and a single Instructions object. The Instructions class itself is composed of a vector<string> representing individual steps. These relationships are all examples of strong composition because the contained objects (ingredients, steps, recipes, lists) cannot exist independently of the parent object that owns them, and they are destroyed automatically when the parent object is destroyed.


---

## Team Contributions

### Member 1: Kris Fellows
- Writing Classes
- GitHub Management/Organization

### Member 2: Gabriela Diaz Olivera
- Code optimization
- Input Validation

### Member 3: Camila Vaca
- Writing Classes
- Measurement Converter Popup

### Member 4: Grace Hilton
- Error Handling
- Made the RecipeBook class and the ListManager class

All members will contribute to GUI, bug-testing, and writing main code.

---
## AI and External Resources Disclosure


- GitHub Copilot: [TBD].


### External Resources
TBD


### Collaboration Policy Statement
All submitted work reflects our team’s understanding. Any external code has been:
- Reviewed
- Modified as needed
- Integrated by our team




---

## Additional Notes
TBD

