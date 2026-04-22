#pragma once
#include <wx/wx.h>
#include <wx/listbox.h>
#include <wx/spinctrl.h>
#include "Recipe.h"

class ModifyRecipeDialog : public wxDialog
{
public:
    ModifyRecipeDialog(wxWindow* parent, Recipe& recipe);

private:
    Recipe& m_recipe;

    wxTextCtrl* txtName;
    wxTextCtrl* txtCategory;
    wxSpinCtrl* spinCook;
    wxSpinCtrl* spinServings;

    wxListBox* ingList;
    wxListBox* instrList;

    void LoadRecipe();

    void OnAddIngredient(wxCommandEvent& evt);
    void OnRemoveIngredient(wxCommandEvent& evt);
    void OnEditIngredient(wxCommandEvent& evt); 

    void OnAddInstruction(wxCommandEvent& evt);
    void OnRemoveInstruction(wxCommandEvent& evt);

    void OnSave(wxCommandEvent& evt);
};
