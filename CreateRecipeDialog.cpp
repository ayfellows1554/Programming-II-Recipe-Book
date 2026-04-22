#include<wx/wx.h>

#include "CreateRecipeDialog.h"
#include "Ingredient.h"
#include "Instructions.h"
#include "ProduceIngredient.h"
#include "MeatIngredient.h"
#include "SpiceIngredient.h"
#include "DryIngredient.h"
#include "DairyIngredient.h"
#include "IngredientBase.h"
#include "Recipe.h"
#include "RecipeBook.h"

enum
{
    ID_AddIngredient = 1001,
    ID_EditIngredient,
    ID_DeleteIngredient,
    ID_AddInstruction,
    ID_SaveRecipe
};

CreateRecipeDialog::CreateRecipeDialog(wxWindow* parent, RecipeBook& book)
    : wxDialog(parent, wxID_ANY, "Create Recipe", wxDefaultPosition, wxSize(500, 600)),
    m_book(book)
{
    wxBoxSizer* outerSizer = new wxBoxSizer(wxVERTICAL);

    // ============================================================
    // SCROLLABLE PANEL
    // ============================================================
    wxScrolledWindow* scroll = new wxScrolledWindow(this, wxID_ANY);
    scroll->SetScrollRate(5, 5);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // -------------------------
    // Name
    // -------------------------
    mainSizer->Add(new wxStaticText(scroll, wxID_ANY, "Recipe Name:"), 0, wxALL, 5);
    txtName = new wxTextCtrl(scroll, wxID_ANY);
    mainSizer->Add(txtName, 0, wxEXPAND | wxALL, 5);

    // -------------------------
    // Category
    // -------------------------
    mainSizer->Add(new wxStaticText(scroll, wxID_ANY, "Category:"), 0, wxALL, 5);
    txtCategory = new wxTextCtrl(scroll, wxID_ANY);
    mainSizer->Add(txtCategory, 0, wxEXPAND | wxALL, 5);

    // -------------------------
    // Servings
    // -------------------------
    mainSizer->Add(new wxStaticText(scroll, wxID_ANY, "Servings:"), 0, wxALL, 5);
    spinServings = new wxSpinCtrl(scroll, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, 1, 100, 1);
    mainSizer->Add(spinServings, 0, wxALL, 5);

    // -------------------------
    // Cook Time
    // -------------------------
    mainSizer->Add(new wxStaticText(scroll, wxID_ANY, "Cook Time (minutes):"), 0, wxALL, 5);
    spinCookTime = new wxSpinCtrl(scroll, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, 0, 0, 1000, 0);
    mainSizer->Add(spinCookTime, 0, wxALL, 5);

    // -------------------------
    // Ingredient input controls
    // -------------------------
    mainSizer->Add(new wxStaticText(scroll, wxID_ANY, "Ingredient Name:"), 0, wxALL, 5);
    txtIngName = new wxTextCtrl(scroll, wxID_ANY);
    mainSizer->Add(txtIngName, 0, wxEXPAND | wxALL, 5);

    mainSizer->Add(new wxStaticText(scroll, wxID_ANY, "Amount:"), 0, wxALL, 5);
    txtIngAmount = new wxTextCtrl(scroll, wxID_ANY);
    mainSizer->Add(txtIngAmount, 0, wxEXPAND | wxALL, 5);

    mainSizer->Add(new wxStaticText(scroll, wxID_ANY, "Unit:"), 0, wxALL, 5);
    txtIngUnit = new wxTextCtrl(scroll, wxID_ANY);
    mainSizer->Add(txtIngUnit, 0, wxEXPAND | wxALL, 5);

    // -------------------------
    // Ingredient Type
    // -------------------------
    mainSizer->Add(new wxStaticText(scroll, wxID_ANY, "Ingredient Type:"), 0, wxALL, 5);

    wxArrayString ingredientTypes;
    ingredientTypes.Add("Generic");
    ingredientTypes.Add("Produce");
    ingredientTypes.Add("Meat");
    ingredientTypes.Add("Spices");
    ingredientTypes.Add("Dry");
    ingredientTypes.Add("Dairy");

    choiceIngredientType = new wxChoice(scroll, wxID_ANY, wxDefaultPosition, wxDefaultSize, ingredientTypes);
    choiceIngredientType->SetSelection(0);
    mainSizer->Add(choiceIngredientType, 0, wxEXPAND | wxALL, 5);

    // -------------------------
    // Ingredients list
    // -------------------------
    mainSizer->Add(new wxStaticText(scroll, wxID_ANY, "Ingredients:"), 0, wxALL, 5);

    ingredientList = new wxListBox(scroll, wxID_ANY, wxDefaultPosition, wxSize(-1, 150));
    mainSizer->Add(ingredientList, 0, wxEXPAND | wxALL, 5);

    // ⭐ Add / Edit / Delete buttons
    wxBoxSizer* ingBtnSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* btnAddIng = new wxButton(scroll, ID_AddIngredient, "Add");
    wxButton* btnEditIng = new wxButton(scroll, ID_EditIngredient, "Edit");
    wxButton* btnDeleteIng = new wxButton(scroll, ID_DeleteIngredient, "Delete");

    ingBtnSizer->Add(btnAddIng, 1, wxALL, 5);
    ingBtnSizer->Add(btnEditIng, 1, wxALL, 5);
    ingBtnSizer->Add(btnDeleteIng, 1, wxALL, 5);

    mainSizer->Add(ingBtnSizer, 0, wxEXPAND);

    // -------------------------
    // Instructions
    // -------------------------
    mainSizer->Add(new wxStaticText(scroll, wxID_ANY, "Instructions:"), 0, wxALL, 5);

    instructionList = new wxListBox(scroll, wxID_ANY, wxDefaultPosition, wxSize(-1, 150));
    mainSizer->Add(instructionList, 0, wxEXPAND | wxALL, 5);

    mainSizer->Add(new wxButton(scroll, ID_AddInstruction, "Add Instruction"), 0, wxALL, 5);

    // ============================================================
    // FINALIZE SCROLL AREA
    // ============================================================
    scroll->SetSizer(mainSizer);
    scroll->FitInside();

    outerSizer->Add(scroll, 1, wxEXPAND);

    // ============================================================
    // SAVE BUTTON (OUTSIDE SCROLL)
    // ============================================================
    wxButton* btnSave = new wxButton(this, ID_SaveRecipe, "Save Recipe");
    outerSizer->Add(btnSave, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(outerSizer);

    // Event bindings
    Bind(wxEVT_BUTTON, &CreateRecipeDialog::OnAddIngredient, this, ID_AddIngredient);
    Bind(wxEVT_BUTTON, &CreateRecipeDialog::OnEditIngredient, this, ID_EditIngredient);
    Bind(wxEVT_BUTTON, &CreateRecipeDialog::OnDeleteIngredient, this, ID_DeleteIngredient);
    Bind(wxEVT_BUTTON, &CreateRecipeDialog::OnAddInstruction, this, ID_AddInstruction);
    Bind(wxEVT_BUTTON, &CreateRecipeDialog::OnSave, this, ID_SaveRecipe);
}

// ============================================================
// INGREDIENT HANDLERS
// ============================================================

void CreateRecipeDialog::OnAddIngredient(wxCommandEvent& evt)
{
    std::string ingName = txtIngName->GetValue().ToStdString();
    std::string unit = txtIngUnit->GetValue().ToStdString();
    double amount = std::stod(txtIngAmount->GetValue().ToStdString());

    std::unique_ptr<IngredientBase> ingredient;

    int type = choiceIngredientType->GetSelection();
    switch (type)
    {
    case 1: ingredient = std::make_unique<ProduceIngredient>(amount, unit, ingName); break;
    case 2: ingredient = std::make_unique<MeatIngredient>(amount, unit, ingName); break;
    case 3: ingredient = std::make_unique<SpiceIngredient>(amount, unit, ingName); break;
    case 4: ingredient = std::make_unique<DryIngredient>(amount, unit, ingName); break;
    case 5: ingredient = std::make_unique<DairyIngredient>(amount, unit, ingName); break;
    default: ingredient = std::make_unique<Ingredient>(amount, unit, ingName); break;
    }

    m_recipe.addIngredient(std::move(ingredient));
    ingredientList->Append(wxString::Format("%s %.2f %s", ingName, amount, unit));
}

void CreateRecipeDialog::OnEditIngredient(wxCommandEvent& evt)
{
    int sel = ingredientList->GetSelection();
    if (sel == wxNOT_FOUND)
    {
        wxMessageBox("Select an ingredient to edit.");
        return;
    }

    wxString line = ingredientList->GetString(sel);
    wxArrayString parts = wxSplit(line, ' ');

    if (parts.size() < 3)
    {
        wxMessageBox("Invalid ingredient format.");
        return;
    }

    txtIngName->SetValue(parts[0]);
    txtIngAmount->SetValue(parts[1]);
    txtIngUnit->SetValue(parts[2]);

    ingredientList->Delete(sel);

    auto& vec = m_recipe.getIngredients();
    vec.erase(vec.begin() + sel);
}

void CreateRecipeDialog::OnDeleteIngredient(wxCommandEvent& evt)
{
    int sel = ingredientList->GetSelection();
    if (sel == wxNOT_FOUND)
    {
        wxMessageBox("Select an ingredient to delete.");
        return;
    }

    ingredientList->Delete(sel);

    auto& vec = m_recipe.getIngredients();
    vec.erase(vec.begin() + sel);
}

// ============================================================
// INSTRUCTION HANDLER
// ============================================================

void CreateRecipeDialog::OnAddInstruction(wxCommandEvent& evt)
{
    wxTextEntryDialog dlg(this, "Enter instruction step:");
    if (dlg.ShowModal() == wxID_OK)
    {
        instructionList->Append(dlg.GetValue());
        m_recipe.addInstruction(dlg.GetValue().ToStdString());
    }
}

// ============================================================
// SAVE
// ============================================================

void CreateRecipeDialog::OnSave(wxCommandEvent& evt)
{
    try
    {
        m_recipe.setRecipeName(txtName->GetValue().ToStdString());
        m_recipe.setRecipeCategory(txtCategory->GetValue().ToStdString());
        m_recipe.setServings(spinServings->GetValue());
        m_recipe.setCookTime(spinCookTime->GetValue());

        m_recipe.validate();
        m_book.addRecipe(std::move(m_recipe));

        wxMessageBox("Recipe saved!");
        EndModal(wxID_OK);
    }
    catch (const std::exception& e)
    {
        wxMessageBox(e.what(), "Error");
    }
}

