#include "MainFrame.h"
#include "CreateRecipeDialog.h"
#include "ListManagerDialog.h"
#include "SearchRecipeDialog.h"
#include "Theme.h"   // Theme header for styling

enum
{
    ID_CreateRecipe = 1,
    ID_SearchRecipe,
    ID_ManageLists
};

// Event table for MainFrame
wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(ID_CreateRecipe, MainFrame::OnCreateRecipe)
    EVT_MENU(ID_SearchRecipe, MainFrame::OnSearchRecipe)
    EVT_MENU(ID_ManageLists, MainFrame::OnManageLists)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title)
    : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(900, 600))
{
    // Create menu
    wxMenuBar* menuBar = new wxMenuBar();
    wxMenu* menuFile = new wxMenu();
    menuFile->Append(ID_CreateRecipe, "&Create Recipe");
    menuFile->Append(ID_SearchRecipe, "&Search Recipe");
    menuFile->Append(ID_ManageLists, "&Manage Lists");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT, "E&xit");
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    // Main content panel
    contentPanel = new wxPanel(this);
    PastelTheme::StylePanel(contentPanel);

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	// Header
    wxStaticText* header = new wxStaticText(contentPanel, wxID_ANY, "Recipe Book");
    PastelTheme::StyleHeader(header);
    sizer->Add(header, 0, wxALIGN_CENTER | wxALL, 10);

	// Buttons
    wxButton* btnCreate = new wxButton(contentPanel, ID_CreateRecipe, "Create Recipe");
    PastelTheme::StyleButton(btnCreate);
    sizer->Add(btnCreate, 0, wxALIGN_CENTER | wxALL, 5);

	// Search button
    wxButton* btnSearch = new wxButton(contentPanel, ID_SearchRecipe, "Search Recipes");
    PastelTheme::StyleButton(btnSearch);
    sizer->Add(btnSearch, 0, wxALIGN_CENTER | wxALL, 5);

	// Manage Lists button
    wxButton* btnLists = new wxButton(contentPanel, ID_ManageLists, "Manage Lists");
    PastelTheme::StyleButton(btnLists);
    sizer->Add(btnLists, 0, wxALIGN_CENTER | wxALL, 5);

    contentPanel->SetSizer(sizer);

    Centre();
}

//Event handler for creating a new recipe
void MainFrame::OnCreateRecipe(wxCommandEvent& evt)
{
    CreateRecipeDialog dlg(this, m_recipeBook);
    dlg.ShowModal();
}

// Event handler for searching recipes
void MainFrame::OnSearchRecipe(wxCommandEvent & evt)
{
    SearchRecipeDialog dlg(this, m_recipeBook);
    dlg.ShowModal();
}

//Event handler for managing lists
void MainFrame::OnManageLists(wxCommandEvent& evt)
{
    ListManagerDialog dlg(this, m_recipeBook, m_listManager);
    dlg.ShowModal();
}

// Event handler for exiting the application
void MainFrame::OnExit(wxCommandEvent & evt)
{
    Close(true);
}
