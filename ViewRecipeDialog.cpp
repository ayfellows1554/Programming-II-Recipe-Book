#include "ViewRecipeDialog.h"

ViewRecipeDialog::ViewRecipeDialog(wxWindow* parent, const Recipe& recipe)
    : wxDialog(parent, wxID_ANY, "View Recipe", wxDefaultPosition, wxSize(700, 500))
{
    // Pastel colors
    wxColour bg("#F7F3FF");      // soft lavender-cream
    wxColour panelBg("#FFFFFF"); // white panels
    wxColour header("#C8B6FF");  // pastel purple
    wxColour text("#4A4A4A");    // soft dark gray

    SetBackgroundColour(bg);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // -------------------------
    // HEADER: Name + Category
    // -------------------------
    wxPanel* headerPanel = new wxPanel(this);
    headerPanel->SetBackgroundColour(header);

    wxBoxSizer* headerSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* nameText = new wxStaticText(headerPanel, wxID_ANY, recipe.getRecipeName());
    nameText->SetFont(wxFontInfo(18).Bold());
    nameText->SetForegroundColour(*wxWHITE);

    wxStaticText* categoryText = new wxStaticText(
        headerPanel, wxID_ANY, "  [" + recipe.getRecipeCategory() + "]"
    );
    categoryText->SetFont(wxFontInfo(14).Bold());
    categoryText->SetForegroundColour(*wxWHITE);

    headerSizer->Add(nameText, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);
    headerSizer->Add(categoryText, 0, wxALL | wxALIGN_CENTER_VERTICAL, 10);

    headerPanel->SetSizer(headerSizer);
    mainSizer->Add(headerPanel, 0, wxEXPAND);

    // -------------------------
    // MAIN CONTENT AREA
    // Instructions (left)
    // Ingredients (right)
    // -------------------------
    wxBoxSizer* contentSizer = new wxBoxSizer(wxHORIZONTAL);

    // LEFT: Instructions
    wxScrolledWindow* instrPanel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    instrPanel->SetScrollRate(5, 5);
    instrPanel->SetBackgroundColour(panelBg);

    wxBoxSizer* instrSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* instrHeader = new wxStaticText(instrPanel, wxID_ANY, "Instructions");
    instrHeader->SetFont(wxFontInfo(14).Bold());
    instrHeader->SetForegroundColour(text);
    instrSizer->Add(instrHeader, 0, wxALL, 10);

    const auto& instructions = recipe.getInstructions().getSteps();
    for (size_t i = 0; i < instructions.size(); ++i)
    {
        wxString step = wxString::Format("%zu. %s", i + 1, instructions[i]);
        wxStaticText* stepText = new wxStaticText(instrPanel, wxID_ANY, step);
        stepText->SetForegroundColour(text);
        instrSizer->Add(stepText, 0, wxLEFT | wxRIGHT | wxBOTTOM, 8);
    }

    instrPanel->SetSizer(instrSizer);
    contentSizer->Add(instrPanel, 1, wxEXPAND | wxALL, 10);

    // RIGHT: Ingredients
    wxScrolledWindow* ingPanel = new wxScrolledWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxVSCROLL);
    ingPanel->SetScrollRate(5, 5);
    ingPanel->SetBackgroundColour(panelBg);

    wxBoxSizer* ingSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* ingHeader = new wxStaticText(ingPanel, wxID_ANY, "Ingredients");
    ingHeader->SetFont(wxFontInfo(14).Bold());
    ingHeader->SetForegroundColour(text);
    ingSizer->Add(ingHeader, 0, wxALL, 10);

    const auto& ingredients = recipe.getIngredients();
    for (const auto& ing : ingredients)
    {
        wxString bullet = wxString::Format(
            "• %.2f %s %s",
            ing->getAmountValue(),
            ing->getUnit(),
            ing->getName()
        );

        wxStaticText* ingText = new wxStaticText(ingPanel, wxID_ANY, bullet);
        ingText->SetForegroundColour(text);
        ingSizer->Add(ingText, 0, wxLEFT | wxRIGHT | wxBOTTOM, 8);
    }

    ingPanel->SetSizer(ingSizer);
    contentSizer->Add(ingPanel, 1, wxEXPAND | wxALL, 10);

    mainSizer->Add(contentSizer, 1, wxEXPAND);

    // -------------------------
    // CLOSE BUTTON
    // -------------------------
    wxButton* closeBtn = new wxButton(this, wxID_OK, "Close");
    mainSizer->Add(closeBtn, 0, wxALIGN_CENTER | wxALL, 10);

    SetSizer(mainSizer);
}
