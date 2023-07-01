#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	MainFrame* mainFrame = new MainFrame("Jordan's C++ Calculator");
	mainFrame->SetClientSize(300, 300);
	mainFrame->Center(); //Centers window on screen
	mainFrame->Show();
	return true;
}
