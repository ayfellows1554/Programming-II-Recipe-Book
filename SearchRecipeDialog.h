#pragma once
#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/choice.h>
#include "RecipeBook.h"

class SearchRecipeDialog : public wxDialog
{
public:
    SearchRecipeDialog(wxWindow* parent, RecipeBook& book);

private:
    RecipeBook& m_book;

    wxTextCtrl* txtSearch;
    wxListBox* resultsList;
    wxChoice* searchMode; // name, ingredient, category

    void OnSearch(wxCommandEvent& evt);
    void OnView(wxCommandEvent& evt);
};
