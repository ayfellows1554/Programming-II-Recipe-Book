#pragma once
#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include "Recipe.h"

class ViewRecipeDialog : public wxDialog
{
public:
    ViewRecipeDialog(wxWindow* parent, const Recipe& recipe);
};
