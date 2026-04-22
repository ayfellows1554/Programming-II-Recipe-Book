#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "IngredientBase.h"
#include "Ingredient.h"   // Your concrete ingredient class

class IngredientEditorDialog : public wxDialog
{
public:
    // If editing an existing ingredient, pass a pointer.
    // If creating a new one, pass nullptr.
    IngredientEditorDialog(wxWindow* parent, IngredientBase* existing);

    // Returns a newly created ingredient (caller takes ownership)
    std::unique_ptr<IngredientBase> GetResult();

private:
    IngredientBase* m_existing; // nullptr if creating new

    wxTextCtrl* txtName;
    wxTextCtrl* txtUnit;
    wxSpinCtrlDouble* spinAmount;

    std::unique_ptr<IngredientBase> m_result;

    void OnSave(wxCommandEvent& evt);
    void OnCancel(wxCommandEvent& evt);
};
