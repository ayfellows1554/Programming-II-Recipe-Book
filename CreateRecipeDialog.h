#pragma once
#include <memory>
#include <wx/spinctrl.h>
#include <wx/scrolwin.h>
#include <wx/listbox.h>
#include <wx/choice.h>

#include"Recipe.h"

//forward declaration
class RecipeBook;

class CreateRecipeDialog : public wxDialog
{
public:
    CreateRecipeDialog(wxWindow* parent, RecipeBook& book);

private:
    RecipeBook& m_book;
    Recipe m_recipe;

    wxTextCtrl* txtName;
    wxTextCtrl* txtCategory;
    wxSpinCtrl* spinServings;
    wxSpinCtrl* spinCookTime;

    wxTextCtrl* txtIngName;
    wxTextCtrl* txtIngAmount;
    wxTextCtrl* txtIngUnit;
    wxChoice* choiceIngredientType;

    wxListBox* ingredientList;
    wxListBox* instructionList;

    // Ingredient handlers
    void OnAddIngredient(wxCommandEvent& evt);
    void OnEditIngredient(wxCommandEvent& evt);     // ⭐ NEW
    void OnDeleteIngredient(wxCommandEvent& evt);   // ⭐ NEW

    // Instruction handlers
    void OnAddInstruction(wxCommandEvent& evt);

    // Save
    void OnSave(wxCommandEvent& evt);
};
