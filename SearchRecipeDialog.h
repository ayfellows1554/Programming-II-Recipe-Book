#pragma once
#include <wx/wx.h>
#include "RecipeBook.h"

class SearchRecipeDialog : public wxDialog
{
public:
    SearchRecipeDialog(wxWindow* parent, RecipeBook& book);

private:
    RecipeBook& m_book;

    wxTextCtrl* txtSearch;
    wxTextCtrl* txtResult;

    void OnSearch(wxCommandEvent& evt);
};
