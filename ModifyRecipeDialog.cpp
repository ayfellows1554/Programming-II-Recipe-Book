#include "ModifyRecipeDialog.h"
#include "IngredientEditorDialog.h"
#include "Theme.h"
#include <wx/scrolwin.h>

enum
{
    ID_AddIng = 5001,
    ID_RemoveIng,
    ID_EditIng,
    ID_AddInstr,
    ID_RemoveInstr,
    ID_Save
};

ModifyRecipeDialog::ModifyRecipeDialog(wxWindow* parent, Recipe& recipe)
    : wxDialog(parent, wxID_ANY, "Modify Recipe", wxDefaultPosition, wxSize(650, 700)),
    m_recipe(recipe)
{
    PastelTheme::ApplyTheme(this);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // -------------------------
    // NAME + CATEGORY
    // -------------------------
    txtName = new wxTextCtrl(this, wxID_ANY, recipe.getRecipeName());
    txtCategory = new wxTextCtrl(this, wxID_ANY, recipe.getRecipeCategory());

    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Name:"), 0, wxLEFT | wxTOP, 10);
    mainSizer->Add(txtName, 0, wxEXPAND | wxALL, 10);

    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Category:"), 0, wxLEFT, 10);
    mainSizer->Add(txtCategory, 0, wxEXPAND | wxALL, 10);

    // -------------------------
    // COOK TIME + SERVINGS
    // -------------------------
    spinCook = new wxSpinCtrl(this, wxID_ANY);
    spinCook->SetValue(recipe.getCookTime());

    spinServings = new wxSpinCtrl(this, wxID_ANY);
    spinServings->SetValue(recipe.getServings());

    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Cook Time (min):"), 0, wxLEFT, 10);
    mainSizer->Add(spinCook, 0, wxEXPAND | wxALL, 10);

    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Servings:"), 0, wxLEFT, 10);
    mainSizer->Add(spinServings, 0, wxEXPAND | wxALL, 10);

    // ============================================================
    // INGREDIENTS (SCROLLABLE)
    // ============================================================

    wxStaticText* ingLabel = new wxStaticText(this, wxID_ANY, "Ingredients:");
    mainSizer->Add(ingLabel, 0, wxLEFT | wxTOP, 10);

    wxScrolledWindow* ingPanel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 200));
    ingPanel->SetScrollRate(5, 5);

    wxBoxSizer* ingSizer = new wxBoxSizer(wxVERTICAL);
    ingList = new wxListBox(ingPanel, wxID_ANY);

    for (auto& ing : recipe.getIngredients())
    {
        wxString line = wxString::Format("%.2f %s %s",
            ing->getAmountValue(),
            ing->getUnit(),
            ing->getName());
        ingList->Append(line);
    }

    ingSizer->Add(ingList, 1, wxEXPAND | wxALL, 5);
    ingPanel->SetSizer(ingSizer);
    ingPanel->FitInside();

    mainSizer->Add(ingPanel, 0, wxEXPAND | wxALL, 10);

    wxBoxSizer* ingBtnSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* btnAddIng = new wxButton(this, ID_AddIng, "Add Ingredient");
    wxButton* btnRemoveIng = new wxButton(this, ID_RemoveIng, "Remove Ingredient");
    wxButton* btnEditIng = new wxButton(this, ID_EditIng, "Edit Ingredient");

    PastelTheme::StyleButton(btnAddIng);
    PastelTheme::StyleButton(btnRemoveIng);
    PastelTheme::StyleButton(btnEditIng);

    ingBtnSizer->Add(btnAddIng, 1, wxALL, 5);
    ingBtnSizer->Add(btnRemoveIng, 1, wxALL, 5);
    ingBtnSizer->Add(btnEditIng, 1, wxALL, 5);

    mainSizer->Add(ingBtnSizer, 0, wxEXPAND);

    // ============================================================
    // INSTRUCTIONS (SCROLLABLE)
    // ============================================================

    wxStaticText* instrLabel = new wxStaticText(this, wxID_ANY, "Instructions:");
    mainSizer->Add(instrLabel, 0, wxLEFT | wxTOP, 10);

    wxScrolledWindow* instrPanel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxSize(-1, 200));
    instrPanel->SetScrollRate(5, 5);

    wxBoxSizer* instrSizer = new wxBoxSizer(wxVERTICAL);
    instrList = new wxListBox(instrPanel, wxID_ANY);

    for (auto& step : recipe.getInstructions().getSteps())
        instrList->Append(step);

    instrSizer->Add(instrList, 1, wxEXPAND | wxALL, 5);
    instrPanel->SetSizer(instrSizer);
    instrPanel->FitInside();

    mainSizer->Add(instrPanel, 0, wxEXPAND | wxALL, 10);

    wxBoxSizer* instrBtnSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* btnAddInstr = new wxButton(this, ID_AddInstr, "Add Step");
    wxButton* btnRemoveInstr = new wxButton(this, ID_RemoveInstr, "Remove Step");

    PastelTheme::StyleButton(btnAddInstr);
    PastelTheme::StyleButton(btnRemoveInstr);

    instrBtnSizer->Add(btnAddInstr, 1, wxALL, 5);
    instrBtnSizer->Add(btnRemoveInstr, 1, wxALL, 5);

    mainSizer->Add(instrBtnSizer, 0, wxEXPAND);

    // ============================================================
    // SAVE BUTTON
    // ============================================================

    wxButton* btnSave = new wxButton(this, ID_Save, "Save Changes");
    PastelTheme::StyleButton(btnSave);
    mainSizer->Add(btnSave, 0, wxALIGN_CENTER | wxALL, 10);

    // ============================================================
    // EVENT BINDINGS
    // ============================================================

    Bind(wxEVT_BUTTON, &ModifyRecipeDialog::OnAddIngredient, this, ID_AddIng);
    Bind(wxEVT_BUTTON, &ModifyRecipeDialog::OnRemoveIngredient, this, ID_RemoveIng);
    Bind(wxEVT_BUTTON, &ModifyRecipeDialog::OnEditIngredient, this, ID_EditIng);
    Bind(wxEVT_BUTTON, &ModifyRecipeDialog::OnAddInstruction, this, ID_AddInstr);
    Bind(wxEVT_BUTTON, &ModifyRecipeDialog::OnRemoveInstruction, this, ID_RemoveInstr);
    Bind(wxEVT_BUTTON, &ModifyRecipeDialog::OnSave, this, ID_Save);

    SetSizer(mainSizer);
}

// ============================================================
// INGREDIENT HANDLERS
// ============================================================

void ModifyRecipeDialog::OnAddIngredient(wxCommandEvent&)
{
    IngredientEditorDialog dlg(this, nullptr);
    if (dlg.ShowModal() == wxID_OK)
    {
        auto ing = dlg.GetResult();

        wxString line = wxString::Format("%.2f %s %s",
            ing->getAmountValue(),
            ing->getUnit(),
            ing->getName());

        ingList->Append(line);
        m_recipe.addIngredient(std::move(ing));
    }
}

void ModifyRecipeDialog::OnEditIngredient(wxCommandEvent&)
{
    int sel = ingList->GetSelection();
    if (sel == wxNOT_FOUND) return;

    auto& ingPtr = m_recipe.getIngredients()[sel];

    IngredientEditorDialog dlg(this, ingPtr.get());
    if (dlg.ShowModal() == wxID_OK)
    {
        ingPtr = dlg.GetResult();

        wxString line = wxString::Format("%.2f %s %s",
            ingPtr->getAmountValue(),
            ingPtr->getUnit(),
            ingPtr->getName());

        ingList->SetString(sel, line);
    }
}

void ModifyRecipeDialog::OnRemoveIngredient(wxCommandEvent&)
{
    int sel = ingList->GetSelection();
    if (sel == wxNOT_FOUND) return;

    ingList->Delete(sel);

    auto& vec = m_recipe.getIngredients();
    vec.erase(vec.begin() + sel);
}

// ============================================================
// INSTRUCTION HANDLERS
// ============================================================

void ModifyRecipeDialog::OnAddInstruction(wxCommandEvent&)
{
    wxTextEntryDialog dlg(this, "Enter new instruction:");
    if (dlg.ShowModal() == wxID_OK)
        instrList->Append(dlg.GetValue());
}

void ModifyRecipeDialog::OnRemoveInstruction(wxCommandEvent&)
{
    int sel = instrList->GetSelection();
    if (sel != wxNOT_FOUND)
        instrList->Delete(sel);
}

// ============================================================
// SAVE
// ============================================================

void ModifyRecipeDialog::OnSave(wxCommandEvent&)
{
    m_recipe.setRecipeName(txtName->GetValue().ToStdString());
    m_recipe.setRecipeCategory(txtCategory->GetValue().ToStdString());
    m_recipe.setCookTime(spinCook->GetValue());
    m_recipe.setServings(spinServings->GetValue());

    m_recipe.clearInstructions();
    for (unsigned i = 0; i < instrList->GetCount(); i++)
        m_recipe.addInstruction(instrList->GetString(i).ToStdString());

    EndModal(wxID_OK);
}
