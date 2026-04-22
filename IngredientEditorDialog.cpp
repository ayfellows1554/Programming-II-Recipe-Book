#include "IngredientEditorDialog.h"
#include "Theme.h"

enum
{
    ID_SaveIng = 7001,
    ID_CancelIng
};

IngredientEditorDialog::IngredientEditorDialog(wxWindow* parent, IngredientBase* existing)
    : wxDialog(parent, wxID_ANY, existing ? "Edit Ingredient" : "Add Ingredient",
        wxDefaultPosition, wxSize(400, 300)),
    m_existing(existing)
{
    PastelTheme::ApplyTheme(this);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // -------------------------
    // NAME
    // -------------------------
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Ingredient Name:"), 0, wxLEFT | wxTOP, 10);
    txtName = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(txtName, 0, wxEXPAND | wxALL, 10);

    // -------------------------
    // AMOUNT
    // -------------------------
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Amount:"), 0, wxLEFT, 10);
    spinAmount = new wxSpinCtrlDouble(this, wxID_ANY);
    spinAmount->SetRange(0.0, 10000.0);
    spinAmount->SetIncrement(0.1);
    mainSizer->Add(spinAmount, 0, wxEXPAND | wxALL, 10);

    // -------------------------
    // UNIT
    // -------------------------
    mainSizer->Add(new wxStaticText(this, wxID_ANY, "Unit (g, ml, tbsp, etc.):"), 0, wxLEFT, 10);
    txtUnit = new wxTextCtrl(this, wxID_ANY);
    mainSizer->Add(txtUnit, 0, wxEXPAND | wxALL, 10);

    // -------------------------
    // BUTTONS
    // -------------------------
    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* btnSave = new wxButton(this, ID_SaveIng, "Save");
    wxButton* btnCancel = new wxButton(this, ID_CancelIng, "Cancel");

    PastelTheme::StyleButton(btnSave);
    PastelTheme::StyleButton(btnCancel);

    btnSizer->Add(btnSave, 1, wxALL, 5);
    btnSizer->Add(btnCancel, 1, wxALL, 5);

    mainSizer->Add(btnSizer, 0, wxEXPAND);

    // -------------------------
    // LOAD EXISTING INGREDIENT
    // -------------------------
    if (m_existing)
    {
        txtName->SetValue(m_existing->getName());
        txtUnit->SetValue(m_existing->getUnit());
        spinAmount->SetValue(m_existing->getAmountValue());
    }

    Bind(wxEVT_BUTTON, &IngredientEditorDialog::OnSave, this, ID_SaveIng);
    Bind(wxEVT_BUTTON, &IngredientEditorDialog::OnCancel, this, ID_CancelIng);

    SetSizer(mainSizer);
}

void IngredientEditorDialog::OnSave(wxCommandEvent&)
{
    std::string name = txtName->GetValue().ToStdString();
    std::string unit = txtUnit->GetValue().ToStdString();
    double amount = spinAmount->GetValue();

    if (name.empty() || unit.empty())
    {
        wxMessageBox("Name and unit cannot be empty.");
        return;
    }

    // Create new ingredient
    m_result = std::make_unique<Ingredient>(amount, unit, name);

    EndModal(wxID_OK);
}

void IngredientEditorDialog::OnCancel(wxCommandEvent&)
{
    EndModal(wxID_CANCEL);
}

std::unique_ptr<IngredientBase> IngredientEditorDialog::GetResult()
{
    return std::move(m_result);
}
