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

    // Trim
    auto trim = [&](std::string s) {
        size_t start = s.find_first_not_of(" \t\n\r");
        size_t end   = s.find_last_not_of(" \t\n\r");
        return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
    };

    query = trim(query);
    if (query.empty())
        return;

    // Lowercase query
    std::transform(query.begin(), query.end(), query.begin(),
                   [](unsigned char c){ return std::tolower(c); });

    int mode = searchMode->GetSelection();

    // -------------------------
    // GENERIC PREDICATE SEARCH
    // -------------------------
    auto results = m_book.findRecipesWhere(
        [&](const Recipe& r)
        {
            std::string field;

            if (mode == 0)          // Name
                field = r.getRecipeName();
            else if (mode == 1)     // Ingredient
            {
                for (auto& ing : r.getIngredients())
                {
                    std::string ingName = ing->getName();
                    std::transform(ingName.begin(), ingName.end(), ingName.begin(),
                                   [](unsigned char c){ return std::tolower(c); });

                    if (ingName.find(query) != std::string::npos)
                        return true;
                }
                return false;
            }
            else if (mode == 2)     // Category
                field = r.getRecipeCategory();

            // Lowercase field
            std::transform(field.begin(), field.end(), field.begin(),
                           [](unsigned char c){ return std::tolower(c); });

            return field.find(query) != std::string::npos;
        }
    );

    // Populate results
    for (auto* r : results)
        resultsList->Append(r->getRecipeName());
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
