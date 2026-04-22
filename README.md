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
-Using Windows 10 or later
-Visual Studio 2022 or later
-Download wxWidgets 3.2x (Built for x64)

### Steps
Part 1:
1. Install wxWidgets 3.2x
2.  Extract it to a folder
3. Set the environment variables
   -Variable value: C:\wxWidgets-3.2.5
   -Variable name: WXWIN
   
Part 2: Build wxWidgets (required once)
1. Open x64 Native Tools Command Prompt for VS 2022
2. Navigate to the wxWidgets folder (cd %WXWIN\build\msw)
3. Build the library (nmake /f makefile.vc BUILD=release SHARED=0)

Part 3: Download the project
If using Git:
git clone https://github.com/<Programming-II-Recipe-Book>.git

 Or download the ZIP from GitHub and extract it

Part 4: Open the Solution
1. Open the .sln file in Visual Studio 2022
-Select the configuration, and the platform is x64
2. Configure Include and Library Paths:

2a. In VS, Project -> Properties -> C/C++ -> General -> Additional Include Directories
    $(WXWIN)\include
    $(WXWIN)\include\msvc


 2b. Project -> Properties -> Linker -> General -> Additional Library Directories 
    $(WXWIN)\lib\vc_x64_lib


2c. Project -> Properties -> Linker -> Input -> Additional Dependecies
    wxmsw32u_core.lib
    wxbase32u.lib
    wxpng.lib
    wxzlib.lib
    wxregexu.lib
    wxexpat.lib

3. Build the Project (Ctrl + Shift + B or Build Solution)
4. Run the App

### Notes
-wxWidgets must be built in the same configuration as the project, which is x64
(x64 Debug and x64 Release)

-If you get a linker error, double-check the library directories, the build type, and that wxWidgets was compiled successfully

-If Visual Studio behaves weirdly, then delete .vs/ x64/ and ipch/ and rebuild the solution
-The app uses a wxWidgetsApp entry point (wxImplement_APP), so no main() function is needed

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
The project uses inheritance to model different ingredient types in a clean, extensible way. At the core is IngredientBase, which defines the shared interface and common data for all ingredients. Specific ingredient categories—such as Produce, Meat, Spices, Dairy, and Dry—inherit from this base class and override behavior where needed, allowing the application to treat all ingredients uniformly while still supporting category‑specific logic. This polymorphic design lets the Recipe class store ingredients as std::unique_ptr<IngredientBase> and operate on them through the base interface, making the system flexible, type‑safe, and easy to extend with new ingredient types in the future.

### Polymorphism
The project uses polymorphism to allow the application to treat all ingredient types through a single, unified interface while still preserving each ingredient’s unique behavior. All ingredients inherit from IngredientBase, which defines the core functions shared across the system. Each derived class—such as Produce, Meat, Spices, Dairy, and Dry—overrides these virtual functions to provide category‑specific behavior. Because ingredients are stored as std::unique_ptr<IngredientBase> inside each Recipe, the program can call methods like getName() or toString() without knowing the ingredient’s concrete type. At runtime, C++ automatically dispatches the correct overridden function based on the actual object, enabling flexible, extensible behavior that cleanly supports new ingredient types without modifying existing code.

Virtual Runtime
The project uses virtual functions in the IngredientBase class to enable runtime polymorphism. Functions such as getName(), getType(), or toString() are declared as virtual in the base class and overridden in derived classes like Produce, Meat, Spices, Dairy, and Dry. Because recipes store ingredients as std::unique_ptr<IngredientBase>, the program relies on virtual dispatch to automatically call the correct overridden method based on the actual ingredient type at runtime. This allows the application to treat all ingredients through a single interface while still supporting type‑specific behavior.

### Composition
RecipeBook has‑a Recipe

ListManager has‑a List

List has‑a Recipe

Recipe has‑a Ingredient

Recipe has‑a Instructions

Instructions has‑a steps (vector<string>)

Our project uses composition extensively to build larger, tightly‑bound objects from smaller components. The RecipeBook class is composed of Recipe objects stored in a private vector, and the ListManager class similarly contains a private collection of List objects. Each List is composed of its own set of Recipe instances, while every Recipe is composed of a vector<Ingredient> along with a single Instructions object. The Instructions class itself contains a vector<string> representing individual steps. These are all examples of strong composition because the contained objects—ingredients, steps, recipes, and lists—cannot exist independently of the parent object that owns them, and they are automatically destroyed when that parent object is destroyed.


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
- Error and Validation Handling
- Made the RecipeBook class and the ListManager class
- Did the GUI
- Did the inheritance class and derived classes

---
## AI and External Resources Disclosure

GitHub Copilot, as well as Microsoft Copilot, did help with the error handling at the end by showing where mixed naming was occurring, giving solutions on why there was a persistent error (for example: c2672) and showing where there was a missing header


### Collaboration Policy Statement
All submitted work reflects our team’s understanding. Any external code has been:
- Reviewed
- Modified as needed
- Integrated by our team




---

