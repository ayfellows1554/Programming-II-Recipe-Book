#include "EGG.h"
#include "MainFrame.h"

// Main application class
bool EGG::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    MainFrame* frame = new MainFrame(wxT("Recipe Book"));
	frame->SetSize(800, 600); 
    frame->Center();
    frame->Show(true);
    SetTopWindow(frame);
    return true;
}

wxIMPLEMENT_APP(EGG);
