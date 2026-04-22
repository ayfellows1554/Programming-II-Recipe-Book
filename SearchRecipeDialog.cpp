#include "SearchRecipeDialog.h"
#include "ViewRecipeDialog.h"
#include "Theme.h"


enum
{
    ID_SearchButton = wxID_HIGHEST + 200,
    ID_ViewButton
};

SearchRecipeDialog::SearchRecipeDialog(wxWindow* parent, RecipeBook& book)
    : wxDialog(parent, wxID_ANY, "Search Recipes", wxDefaultPosition, wxSize(550, 550)),
    m_book(book)
{
    PastelTheme::ApplyTheme(this);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // -------------------------
    // Search Mode + Search Bar
    // -------------------------
    wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);

    searchMode = new wxChoice(this, wxID_ANY);
    searchMode->Append("Name");
    searchMode->Append("Ingredient");
    searchMode->Append("Category");
    searchMode->SetSelection(0);

    txtSearch = new wxTextCtrl(this, wxID_ANY);

    wxButton* btnSearch = new wxButton(this, ID_SearchButton, "Search");
    PastelTheme::StyleButton(btnSearch);

    topSizer->Add(searchMode, 0, wxALL, 8);
    topSizer->Add(txtSearch, 1, wxALL | wxEXPAND, 8);
    topSizer->Add(btnSearch, 0, wxALL, 8);

    mainSizer->Add(topSizer, 0, wxEXPAND);

    // -------------------------
    // Results List
    // -------------------------
    resultsList = new wxListBox(this, wxID_ANY);
    mainSizer->Add(resultsList, 1, wxALL | wxEXPAND, 10);

    // -------------------------
    // View Button
    // -------------------------
    wxButton* btnView = new wxButton(this, ID_ViewButton, "View Recipe");
    PastelTheme::StyleButton(btnView);

    mainSizer->Add(btnView, 0, wxALIGN_CENTER | wxALL, 10);

    // Bind events
    Bind(wxEVT_BUTTON, &SearchRecipeDialog::OnSearch, this, ID_SearchButton);
    Bind(wxEVT_BUTTON, &SearchRecipeDialog::OnView, this, ID_ViewButton);

    SetSizer(mainSizer);
}

void SearchRecipeDialog::OnSearch(wxCommandEvent&)
{
    resultsList->Clear();

    std::string query = txtSearch->GetValue().ToStdString();
    if (query.empty())
        return;

    int mode = searchMode->GetSelection();

    // -------------------------
    // SEARCH BY NAME
    // -------------------------
    if (mode == 0)
    {
        for (auto& recipe : m_book.getAllRecipes())
        {
            if (recipe.getRecipeName().find(query) != std::string::npos)
                resultsList->Append(recipe.getRecipeName());
        }
    }

    // -------------------------
    // SEARCH BY INGREDIENT
    // -------------------------
    else if (mode == 1)
    {
        for (auto& recipe : m_book.getAllRecipes())
        {
            for (auto& ing : recipe.getIngredients())
            {
                if (ing->getName().find(query) != std::string::npos)
                {
                    resultsList->Append(recipe.getRecipeName());
                    break;
                }
            }
        }
    }

    // -------------------------
    // SEARCH BY CATEGORY
    // -------------------------
    else if (mode == 2)
    {
        for (auto& recipe : m_book.getAllRecipes())
        {
            if (recipe.getRecipeCategory().find(query) != std::string::npos)
                resultsList->Append(recipe.getRecipeName());
        }
    }

    if (resultsList->IsEmpty())
        resultsList->Append("No recipes found.");
}

void SearchRecipeDialog::OnView(wxCommandEvent&)
{
    int sel = resultsList->GetSelection();
    if (sel == wxNOT_FOUND)
        return;

    wxString name = resultsList->GetString(sel);

    Recipe* r = m_book.findRecipe(name.ToStdString());
    if (!r)
        return;

    ViewRecipeDialog dlg(this, *r);
    dlg.ShowModal();
}
