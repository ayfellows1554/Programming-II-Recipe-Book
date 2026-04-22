#include "ListManagerDialog.h"
#include "Theme.h"
#include "ModifyRecipeDialog.h"

enum
{
    ID_CreateList = 3001,
    ID_DeleteList,
    ID_ViewList,
    ID_AddRecipe,
    ID_RemoveRecipe,
    ID_ModifyRecipe   // ⭐ NEW
};

ListManagerDialog::ListManagerDialog(wxWindow* parent, RecipeBook& book, ListManager& manager)
    : wxDialog(parent, wxID_ANY, "List Manager", wxDefaultPosition, wxSize(600, 500)),
    m_book(book), m_manager(manager)
{
    PastelTheme::ApplyTheme(this);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* header = new wxStaticText(this, wxID_ANY, "Manage Your Lists");
    PastelTheme::StyleHeader(header);
    mainSizer->Add(header, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    listBox = new wxListBox(this, wxID_ANY);
    mainSizer->Add(listBox, 1, wxEXPAND | wxALL, 10);

    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

    wxButton* btnCreate = new wxButton(this, ID_CreateList, "Create List");
    wxButton* btnDelete = new wxButton(this, ID_DeleteList, "Delete List");
    wxButton* btnView = new wxButton(this, ID_ViewList, "View Contents");
    wxButton* btnAdd = new wxButton(this, ID_AddRecipe, "Add Recipe");
    wxButton* btnRemove = new wxButton(this, ID_RemoveRecipe, "Remove Recipe");
    wxButton* btnModify = new wxButton(this, ID_ModifyRecipe, "Modify Recipe"); // ⭐ NEW

    PastelTheme::StyleButton(btnCreate);
    PastelTheme::StyleButton(btnDelete);
    PastelTheme::StyleButton(btnView);
    PastelTheme::StyleButton(btnAdd);
    PastelTheme::StyleButton(btnRemove);
    PastelTheme::StyleButton(btnModify);

    btnSizer->Add(btnCreate, 1, wxALL, 5);
    btnSizer->Add(btnDelete, 1, wxALL, 5);
    btnSizer->Add(btnView, 1, wxALL, 5);
    btnSizer->Add(btnAdd, 1, wxALL, 5);
    btnSizer->Add(btnRemove, 1, wxALL, 5);
    btnSizer->Add(btnModify, 1, wxALL, 5); // ⭐ NEW

    mainSizer->Add(btnSizer, 0, wxEXPAND);

    Bind(wxEVT_BUTTON, &ListManagerDialog::OnCreateList, this, ID_CreateList);
    Bind(wxEVT_BUTTON, &ListManagerDialog::OnDeleteList, this, ID_DeleteList);
    Bind(wxEVT_BUTTON, &ListManagerDialog::OnViewList, this, ID_ViewList);
    Bind(wxEVT_BUTTON, &ListManagerDialog::OnAddRecipe, this, ID_AddRecipe);
    Bind(wxEVT_BUTTON, &ListManagerDialog::OnRemoveRecipe, this, ID_RemoveRecipe);
    Bind(wxEVT_BUTTON, &ListManagerDialog::OnModifyRecipe, this, ID_ModifyRecipe); // ⭐ NEW

    SetSizer(mainSizer);
    RefreshLists();
}

void ListManagerDialog::RefreshLists()
{
    listBox->Clear();
    const auto& lists = m_manager.getLists();
    for (const auto& list : lists)
        listBox->Append(list.getListName());
}

void ListManagerDialog::OnCreateList(wxCommandEvent&)
{
    wxTextEntryDialog dlg(this, "Enter new list name:");
    if (dlg.ShowModal() == wxID_OK)
    {
        try {
            m_manager.createList(dlg.GetValue().ToStdString());
            RefreshLists();
        }
        catch (const std::exception& e) {
            wxMessageBox(e.what(), "Error");
        }
    }
}

void ListManagerDialog::OnDeleteList(wxCommandEvent&)
{
    int sel = listBox->GetSelection();
    if (sel == wxNOT_FOUND) return;

    m_manager.deleteList(listBox->GetString(sel).ToStdString());
    RefreshLists();
}

void ListManagerDialog::OnViewList(wxCommandEvent&)
{
    int sel = listBox->GetSelection();
    if (sel == wxNOT_FOUND) return;

    List* list = m_manager.getList(listBox->GetString(sel).ToStdString());
    if (!list) return;

    wxString output = "List: " + list->getListName() + "\n\n";
    for (int i = 0; i < list->size(); i++)
        output += "- " + list->getRecipe(i) + "\n";

    wxMessageBox(output, "List Contents");
}

void ListManagerDialog::OnAddRecipe(wxCommandEvent&)
{
    int sel = listBox->GetSelection();
    if (sel == wxNOT_FOUND) return;

    List* list = m_manager.getList(listBox->GetString(sel).ToStdString());

    wxTextEntryDialog dlg(this, "Enter recipe name to add:");
    if (dlg.ShowModal() == wxID_OK)
    {
        std::string recipeName = dlg.GetValue().ToStdString();

        if (!m_book.findRecipe(recipeName))
        {
            wxMessageBox("Recipe not found in RecipeBook.");
            return;
        }

        try {
            list->createList(recipeName);
        }
        catch (const std::exception& e) {
            wxMessageBox(e.what(), "Error");
        }
    }
}

void ListManagerDialog::OnRemoveRecipe(wxCommandEvent&)
{
    int sel = listBox->GetSelection();
    if (sel == wxNOT_FOUND) return;

    List* list = m_manager.getList(listBox->GetString(sel).ToStdString());

    wxTextEntryDialog dlg(this, "Enter recipe name to remove:");
    if (dlg.ShowModal() == wxID_OK)
    {
        std::string recipeName = dlg.GetValue().ToStdString();

        for (int i = 0; i < list->size(); i++)
        {
            if (list->getRecipe(i) == recipeName)
            {
                list->deleteList(i);
                return;
            }
        }

        wxMessageBox("Recipe not found in this list.");
    }
}

void ListManagerDialog::OnModifyRecipe(wxCommandEvent&)   // ⭐ NEW
{
    int sel = listBox->GetSelection();
    if (sel == wxNOT_FOUND) return;

    wxTextEntryDialog dlg(this, "Enter recipe name to modify:");
    if (dlg.ShowModal() != wxID_OK)
        return;

    std::string recipeName = dlg.GetValue().ToStdString();
    Recipe* recipe = m_book.findRecipe(recipeName);

    if (!recipe)
    {
        wxMessageBox("Recipe not found in RecipeBook.");
        return;
    }

    ModifyRecipeDialog modifyDlg(this, *recipe);
    if (modifyDlg.ShowModal() == wxID_OK)
        wxMessageBox("Recipe updated successfully.");
}
