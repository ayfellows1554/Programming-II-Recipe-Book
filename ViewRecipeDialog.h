#pragma once
#include <wx/wx.h>
#include "Recipe.h"

class ViewRecipeDialog : public wxDialog
{
public:
    ViewRecipeDialog(wxWindow* parent, const Recipe& recipe);

private:
    void BuildLayout(const Recipe& recipe);
};
