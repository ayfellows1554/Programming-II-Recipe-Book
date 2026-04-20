#pragma once
#pragma once
#include <wx/wx.h>

namespace PastelTheme
{
    static const wxColour WindowBg("#FAF7F2");
    static const wxColour SidebarBg("#E8E3F0");
    static const wxColour ButtonBg("#D7E8FF");
    static const wxColour ButtonHover("#C9DFFF");
    static const wxColour TextColor("#4A4A4A");
    static const wxColour HeaderColor("#6E5A7A");
    static const wxColour BorderColor("#DADADA");

    inline void StyleButton(wxButton* btn)
    {
        btn->SetBackgroundColour(ButtonBg);
        btn->SetForegroundColour(TextColor);
        btn->SetFont(wxFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM));
        btn->SetWindowStyleFlag(wxBORDER_NONE);

        btn->Bind(wxEVT_ENTER_WINDOW, [=](wxMouseEvent&) {
            btn->SetBackgroundColour(ButtonHover);
            btn->Refresh();
            });

        btn->Bind(wxEVT_LEAVE_WINDOW, [=](wxMouseEvent&) {
            btn->SetBackgroundColour(ButtonBg);
            btn->Refresh();
            });
    }

    inline void StylePanel(wxPanel* panel)
    {
        panel->SetBackgroundColour(WindowBg);
    }

    inline void StyleSidebar(wxPanel* panel)
    {
        panel->SetBackgroundColour(SidebarBg);
    }

    inline void StyleHeader(wxStaticText* txt)
    {
        txt->SetForegroundColour(HeaderColor);
        txt->SetFont(wxFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
    }
}
