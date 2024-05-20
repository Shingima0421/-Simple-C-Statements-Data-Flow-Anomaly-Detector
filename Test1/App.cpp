#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("Simple C Statement Parser"); //Window Title
	mainFrame->SetClientSize(410, 700); //Window size
	mainFrame->Center();
	mainFrame->Show();
	return true;
}