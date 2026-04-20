#include "ListManagerDialog.h"

enum
{
	// Unique IDs for the buttons in the list manager dialog
    ID_CreateList = 3001,
    ID_DeleteList,
    ID_ViewList,
    ID_AddRecipe,
    ID_RemoveRecipe
};

// Constructor for the list manager dialog
ListManagerDialog::ListManagerDialog(wxWindow* parent, RecipeBook& book, ListManager& manager)
    : wxDialog(parent, wxID_ANY, "List Manager", wxDefaultPosition, wxSize(600, 500)),
    m_book(book), m_manager(manager)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    listBox = new wxListBox(this, wxID_ANY);
    mainSizer->Add(listBox, 1, wxEXPAND | wxALL, 5);

    wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

	// Create buttons for list management and add them to the button sizer
    btnSizer->Add(new wxButton(this, ID_CreateList, "Create List"), 1, wxALL, 5);
    btnSizer->Add(new wxButton(this, ID_DeleteList, "Delete List"), 1, wxALL, 5);
    btnSizer->Add(new wxButton(this, ID_ViewList, "View Contents"), 1, wxALL, 5);
    btnSizer->Add(new wxButton(this, ID_AddRecipe, "Add Recipe"), 1, wxALL, 5);
    btnSizer->Add(new wxButton(this, ID_RemoveRecipe, "Remove Recipe"), 1, wxALL, 5);

    mainSizer->Add(btnSizer, 0, wxEXPAND);

	// Bind button events to their respective handlers
    Bind(wxEVT_BUTTON, &ListManagerDialog::OnCreateList, this, ID_CreateList);
    Bind(wxEVT_BUTTON, &ListManagerDialog::OnDeleteList, this, ID_DeleteList);
    Bind(wxEVT_BUTTON, &ListManagerDialog::OnViewList, this, ID_ViewList);
    Bind(wxEVT_BUTTON, &ListManagerDialog::OnAddRecipe, this, ID_AddRecipe);
    Bind(wxEVT_BUTTON, &ListManagerDialog::OnRemoveRecipe, this, ID_RemoveRecipe);

    SetSizer(mainSizer);

    RefreshLists();
}

// Refresh the list box with the current lists from the ListManager
void ListManagerDialog::RefreshLists()
{
    listBox->Clear();

    const auto& lists = m_manager.getLists();
    for (size_t i = 0; i < lists.size(); ++i)
        listBox->Append(lists[i].getListName());
}

// Event handler for creating a new list
void ListManagerDialog::OnCreateList(wxCommandEvent& evt)
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

// Event handler for deleting the selected list
void ListManagerDialog::OnDeleteList(wxCommandEvent& evt)
{
    int sel = listBox->GetSelection();
    if (sel == wxNOT_FOUND) return;

    std::string name = listBox->GetString(sel).ToStdString();
    m_manager.deleteList(name);
    RefreshLists();
}

// Event handler for viewing the contents of the selected list
void ListManagerDialog::OnViewList(wxCommandEvent& evt)
{
    int sel = listBox->GetSelection();
    if (sel == wxNOT_FOUND) return;

    std::string name = listBox->GetString(sel).ToStdString();
    List* list = m_manager.getList(name);

    if (!list) {
        wxMessageBox("List not found.");
        return;
    }

    wxString output = "List: " + wxString::FromUTF8(list->getListName().c_str()) + "\n\n";
    for (int i = 0; i < list->size(); i++)
        output += "- " + wxString::FromUTF8(list->getRecipe(i).c_str()) + "\n";

    wxMessageBox(output);
}

// Event handler for adding a recipe to the selected list
void ListManagerDialog::OnAddRecipe(wxCommandEvent& evt)
{
    int sel = listBox->GetSelection();
    if (sel == wxNOT_FOUND) return;

    std::string listName = listBox->GetString(sel).ToStdString();
    List* list = m_manager.getList(listName);

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

// Event handler for removing a recipe from the selected list
 void ListManagerDialog::OnRemoveRecipe(wxCommandEvent& evt)                     
{
    int sel = listBox->GetSelection();
    if (sel == wxNOT_FOUND) return;

    std::string listName = listBox->GetString(sel).ToStdString();
    List* list = m_manager.getList(listName);

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

		// Error handling if recipe is not found in the list
        wxMessageBox("Recipe not found in this list.");
    }
}
