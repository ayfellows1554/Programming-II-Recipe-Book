#pragma once
#include <wx/wx.h>
#include "RecipeBook.h"
#include "ListManager.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    RecipeBook m_recipeBook;
    ListManager m_listManager;

    void OnCreateRecipe(wxCommandEvent& event);
    void OnSearchRecipe(wxCommandEvent& event);
    void OnManageLists(wxCommandEvent& event);

    wxDECLARE_EVENT_TABLE();
};
