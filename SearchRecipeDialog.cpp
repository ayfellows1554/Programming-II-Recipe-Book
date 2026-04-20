#include "SearchRecipeDialog.h"

enum
{
    ID_SearchButton = 2001
};

// Constructor for the search dialog
SearchRecipeDialog::SearchRecipeDialog(wxWindow* parent, RecipeBook& book)
    : wxDialog(parent, wxID_ANY, "Search Recipes", wxDefaultPosition, wxSize(500, 500)),
    m_book(book)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Enter recipe name:"), 0, wxALL, 5);
    txtSearch = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(txtSearch, 0, wxEXPAND | wxALL, 5);

    wxButton* btnSearch = new wxButton(this, ID_SearchButton, "Search");
    mainSizer->Add(btnSearch, 0, wxALIGN_CENTER | wxALL, 5);

    txtResult = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize,
        wxTE_MULTILINE | wxTE_READONLY | wxTE_RICH2);
    mainSizer->Add(txtResult, 1, wxEXPAND | wxALL, 5);

    Bind(wxEVT_BUTTON, &SearchRecipeDialog::OnSearch, this, ID_SearchButton);

    SetSizer(mainSizer);
}

// Event handler for searching a recipe
void SearchRecipeDialog::OnSearch(wxCommandEvent& evt)
{
    std::string name = txtSearch->GetValue().ToStdString();
    Recipe* r = m_book.findRecipe(name);

	//Error handling if recipe is not found
    if (!r)
    {
        txtResult->SetValue("Recipe not found.");
        return;
    }

    txtResult->SetValue(r->displayRecipe());
}
