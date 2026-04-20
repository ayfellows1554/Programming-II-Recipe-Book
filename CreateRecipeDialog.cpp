#include "CreateRecipeDialog.h"
#include "ingredient.h"
#include "instructions.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <sstream>

enum
{
	// Start custom IDs from a high number to avoid conflicts with wxWidgets' built-in IDs
    ID_AddIngredient = 1001,
    ID_AddInstruction,
    ID_SaveRecipe
};

// Constructor
CreateRecipeDialog::CreateRecipeDialog(wxWindow* parent, RecipeBook& book)
    : wxDialog(parent, wxID_ANY, "Create Recipe", wxDefaultPosition, wxSize(500, 600)),
    m_book(book)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Name
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Recipe Name:"), 0, wxALL, 5);
    txtName = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(txtName, 0, wxEXPAND | wxALL, 5);

    // Category
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Category:"), 0, wxALL, 5);
    txtCategory = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(txtCategory, 0, wxEXPAND | wxALL, 5);

    // Servings
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Servings:"), 0, wxALL, 5);
    spinServings = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, 1, 100, 1);
    mainSizer->Add(spinServings, 0, wxALL, 5);

    // Cook Time
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Cook Time (minutes):"), 0, wxALL, 5);
    spinCookTime = new wxSpinCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0);
    mainSizer->Add(spinCookTime, 0, wxALL, 5);

    // Ingredients
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Ingredients:"), 0, wxALL, 5);
    ingredientList = new wxListBox(this, wxID_ANY);
    mainSizer->Add(ingredientList, 1, wxEXPAND | wxALL, 5);

    mainSizer->Add(new wxButton(this, ID_AddIngredient, "Add Ingredient"), 0, wxALL, 5);

    // Instructions
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Instructions:"), 0, wxALL, 5);
    instructionList = new wxListBox(this, wxID_ANY);
    mainSizer->Add(instructionList, 1, wxEXPAND | wxALL, 5);

    mainSizer->Add(new wxButton(this, ID_AddInstruction, "Add Instruction"), 0, wxALL, 5);

    // Save button
    mainSizer->Add(new wxButton(this, ID_SaveRecipe, "Save Recipe"), 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);

	// Event bindings
    Bind(wxEVT_BUTTON, &CreateRecipeDialog::OnAddIngredient, this, ID_AddIngredient);
    Bind(wxEVT_BUTTON, &CreateRecipeDialog::OnAddInstruction, this, ID_AddInstruction);
    Bind(wxEVT_BUTTON, &CreateRecipeDialog::OnSave, this, ID_SaveRecipe);
}

// Event handler for adding an ingredient
void CreateRecipeDialog::OnAddIngredient(wxCommandEvent& evt)
{
    wxTextEntryDialog dlg(this, "Enter ingredient (e.g., '2 cups flour'):");
    if (dlg.ShowModal() == wxID_OK)
        ingredientList->Append(dlg.GetValue());
}

// Event handler for adding an instruction
void CreateRecipeDialog::OnAddInstruction(wxCommandEvent& evt)
{
    wxTextEntryDialog dlg(this, "Enter instruction step:");
    if (dlg.ShowModal() == wxID_OK)
        instructionList->Append(dlg.GetValue());
}

// Event handler for saving the recipe
void CreateRecipeDialog::OnSave(wxCommandEvent& evt)
{
    try
    {
        Recipe r(txtName->GetValue().ToStdString(),
            txtCategory->GetValue().ToStdString());

        r.setServings(spinServings->GetValue());
        r.setCookTime(spinCookTime->GetValue());

        // Ingredients
        for (size_t i = 0; i < ingredientList->GetCount(); i++)
        {
            std::string line = ingredientList->GetString(i).ToStdString();
            double amount;
            std::string unit, name;

            std::stringstream ss(line);
            ss >> amount >> unit;
            std::getline(ss, name);
            r.addIngredient(Ingredient(amount, unit, name));
        }

        // Instructions
        for (size_t i = 0; i < instructionList->GetCount(); i++)
            r.addInstruction(instructionList->GetString(i).ToStdString());

        r.validate();
        m_book.addRecipe(r);

        wxMessageBox("Recipe saved!");
        EndModal(wxID_OK);
    }
	//Error handling for invalid input
    catch (const std::exception& e)
    {
        wxMessageBox(e.what(), "Error");
    }
}
