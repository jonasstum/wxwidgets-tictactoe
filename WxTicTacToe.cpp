#include "WxTicTacToe.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(WxTicTacToe);

bool WxTicTacToe::OnInit()
{
	MainWindow* frame = new MainWindow();

	frame->SetIcon(wxICON(IDI_TTT_ICON));
	frame->Show();

	return true;
}

