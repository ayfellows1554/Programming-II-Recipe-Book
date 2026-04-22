#pragma once
#include <wx/wx.h>

namespace PastelTheme
{
	// Define theme colors
    static const wxColour WindowBg("#FAF7F2"); //warm cream
    static const wxColour SidebarBg("#E8E3F0");//lavender-gray
    static const wxColour ButtonBg("#D7E8FF"); //soft blue
    static const wxColour ButtonHover("#C9DFFF");
    static const wxColour TextColor("#4A4A4A");
    static const wxColour HeaderColor("#6E5A7A");
    static const wxColour BorderColor("#DADADA");

	// Apply the theme to a window
    static void ApplyTheme(wxWindow* window)
    {
        window->SetBackgroundColour(WindowBg);
        window->SetForegroundColour(TextColor);
        window->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM));
	}

	// Style static text
    static void StyleText(wxStaticText* txt)
    {
        txt->SetForegroundColour(TextColor);
        txt->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM));
	}
   
	// Style bold text
    static void StyleTextBold(wxStaticText* txt)
    {
        txt->SetForegroundColour(TextColor);
		txt->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	}

	// Style the menu bar
    static void StyleMenuBar(wxMenuBar* menuBar)
    {
        menuBar->SetBackgroundColour(SidebarBg);
        menuBar->SetForegroundColour(TextColor);
        menuBar->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_MEDIUM));
	}
    
	// Style the panel borders
    static void StylePanelBorder(wxPanel* panel)
    {
        panel->SetBackgroundColour(WindowBg);
        panel->SetForegroundColour(TextColor);
        panel->SetWindowStyleFlag(wxBORDER_SIMPLE);
		panel->Refresh();
        panel->Update();
		panel->SetBackgroundColour(WindowBg);

	}
    
	// Add hover effect to buttons
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

	// Style the main content panel
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


