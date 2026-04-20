#pragma once
#include <wx/wx.h>
#include "RecipeBook.h"
#include "ListManager.h"

class ListManagerDialog : public wxDialog
{
public:
    ListManagerDialog(wxWindow* parent, RecipeBook& book, ListManager& manager);

private:
    RecipeBook& m_book;
    ListManager& m_manager;

    wxListBox* listBox;

    void RefreshLists();

    void OnCreateList(wxCommandEvent& evt);
    void OnDeleteList(wxCommandEvent& evt);
    void OnViewList(wxCommandEvent& evt);
    void OnAddRecipe(wxCommandEvent& evt);
    void OnRemoveRecipe(wxCommandEvent& evt);
};

