#pragma once
#include <string>
#include <string_view>
#include <vector>

// ************ RECIPE ************
// code by Camila
class Recipe {
public: 
	
//Constructor
Recipe(std::string name, std::string category);
	// ingredient and instruction classes added later
	
//Name		
void setRecipeName(std::string name);
std::string getRecipeName();

//Category
void setRecipeCategory(std::string category);	
std::string getRecipeCategory();

//Display	
std::string displayRecipe();

//Serving Size	
void setServings(int servings);	
int getServings() const;

//Scales the servings
void scaleServings(int newServings);

//Validation (checks all fields)
void validate() const;


private:
	//Basic Fields
	std::string m_name{};
	std::string m_category{};
	
//std::vector<Ingredient> m_ingredients{}; // vector of Ingredient object	
//std::vector<Instruction> m_instructions{}; // vector of Instruction object

//Defaults the serving size to 1	
int m_servings{1} 

//Cook Time default is 0
int m_cookTimeMinutes{0};


};
