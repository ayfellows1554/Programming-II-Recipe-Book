#pragma once
#include <wx/wx.h>
#include "RecipeBook.h"

class CreateRecipeDialog : public wxDialog
{
public:
    CreateRecipeDialog(wxWindow* parent, RecipeBook& book);

private:
    RecipeBook& m_book;

    wxTextCtrl* txtName;
    wxTextCtrl* txtCategory;
    wxSpinCtrl* spinServings;
    wxSpinCtrl* spinCookTime;

    wxListBox* ingredientList;
    wxListBox* instructionList;

    void OnAddIngredient(wxCommandEvent& evt);
    void OnAddInstruction(wxCommandEvent& evt);
    void OnSave(wxCommandEvent& evt);
};

