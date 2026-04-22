#include "MainFrame.h"
#include "CreateRecipeDialog.h"
#include "SearchRecipeDialog.h"
#include "ListManagerDialog.h"
#include "Theme.h"
#include"ModifyRecipeDialog.h"
#include"IngredientEditorDialog.h"

//This is what will run the app, not driver.cpp


enum
{
    ID_CreateRecipe = wxID_HIGHEST + 1,
    ID_SearchRecipe,
    ID_ManageLists,
};

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(ID_CreateRecipe, MainFrame::OnCreateRecipe)
EVT_BUTTON(ID_SearchRecipe, MainFrame::OnSearchRecipe)
EVT_BUTTON(ID_ManageLists, MainFrame::OnManageLists)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(900, 600))
{
    // Apply pastel theme to the frame
    PastelTheme::ApplyTheme(this);

    wxPanel* panel = new wxPanel(this);
    PastelTheme::StylePanel(panel);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // -------------------------
    // HEADER TITLE
    // -------------------------
    wxStaticText* header = new wxStaticText(panel, wxID_ANY, "Recipe Manager");
    PastelTheme::StyleHeader(header);
    mainSizer->Add(header, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 15);

    // -------------------------
    // BUTTON BAR
    // -------------------------
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* createBtn = new wxButton(panel, ID_CreateRecipe, "Create Recipe");
    wxButton* searchBtn = new wxButton(panel, ID_SearchRecipe, "Search Recipes");
    wxButton* listBtn = new wxButton(panel, ID_ManageLists, "Manage Lists");

    PastelTheme::StyleButton(createBtn);
    PastelTheme::StyleButton(searchBtn);
    PastelTheme::StyleButton(listBtn);

    buttonSizer->Add(createBtn, 0, wxALL, 10);
    buttonSizer->Add(searchBtn, 0, wxALL, 10);
    buttonSizer->Add(listBtn, 0, wxALL, 10);

    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    panel->SetSizer(mainSizer);
}

void MainFrame::OnCreateRecipe(wxCommandEvent&)
{
    CreateRecipeDialog dlg(this, m_recipeBook);
    dlg.ShowModal();
}

void MainFrame::OnSearchRecipe(wxCommandEvent&)
{
    SearchRecipeDialog dlg(this, m_recipeBook);
    dlg.ShowModal();
}

void MainFrame::OnManageLists(wxCommandEvent&)
{
    ListManagerDialog dlg(this, m_recipeBook, m_listManager);
    dlg.ShowModal();
}
