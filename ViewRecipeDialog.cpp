#include "ViewRecipeDialog.h"
#include "Theme.h"

// Constructor
ViewRecipeDialog::ViewRecipeDialog(wxWindow* parent, const Recipe& recipe)
    : wxDialog(parent, wxID_ANY, "View Recipe", wxDefaultPosition, wxSize(600, 600))
{
    BuildLayout(recipe);
}

// Build the dialog layout based on the recipe details 
void ViewRecipeDialog::BuildLayout(const Recipe& recipe)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Title
    wxStaticText* title = new wxStaticText(this, wxID_ANY,
        recipe.getRecipeName(), wxDefaultPosition, wxDefaultSize,
        wxALIGN_CENTER);
    title->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    mainSizer->Add(title, 0, wxALIGN_CENTER | wxALL, 10);

    // Basic info
    wxString info;
    info << "Category: " << recipe.getRecipeCategory() << "\n";
    info << "Servings: " << recipe.getServings() << "\n";
    info << "Cook Time: " << recipe.getCookTime() << " minutes\n";

    mainSizer->Add(new wxStaticText(this, wxID_ANY, info), 0, wxLEFT | wxRIGHT | wxBOTTOM, 10);

    // Ingredients
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Ingredients:"), 0, wxLEFT | wxTOP, 10);

    wxListBox* ingList = new wxListBox(this, wxID_ANY);
    for (const auto& ing : recipe.getIngredients())
    {
        wxString line;
        line << ing.getAmountValue() << " " << ing.getUnit() << " " << ing.getName();
        ingList->Append(line);
    }
    mainSizer->Add(ingList, 0, wxEXPAND | wxALL, 10);

    // Instructions
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Instructions:"), 0, wxLEFT | wxTOP, 10);

    wxListBox* stepList = new wxListBox(this, wxID_ANY);
    int stepNum = 1;
    for (const auto& step : recipe.getInstructions().getSteps())
    {
        wxString line;
        line << stepNum++ << ". " << step;
        stepList->Append(line);
    }
    mainSizer->Add(stepList, 1, wxEXPAND | wxALL, 10);

    // Close button
    mainSizer->Add(new wxButton(this, wxID_OK, "Close"), 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);
}
