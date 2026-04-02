#pragma once
#include <string>
#include <string_view>
#include <vector>

// ************ RECIPE ************
// code by Camila
class Recipe {
public: 
	Recipe(std::string name, std::string category);
	// ingredient and instruction classes added later
	
	void setRecipeName(std::string name);
	std::string getRecipeName();

	void setRecipeCategory(std::string category);
	std::string getRecipeCategory();

	std::string displayRecipe();

	void setServings(int servings);
	int getServings() const;

	void scaleServings(int newServings);


private:
	std::string m_name{};
	std::string m_category{};
	//std::vector<Ingredient> m_ingredients{}; // vector of Ingredient object
	//std::vector<Instruction> m_instructions{}; // vector of Instruction object

	int m_servings{1}; //defaults the serving size to 1

};
