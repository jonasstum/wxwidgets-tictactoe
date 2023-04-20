#pragma once

#include <wx/wx.h>
#include <string>

enum ID
{
	SINGLE_PLAYER = 1,
	VS_CPU
};

class MainWindow : public wxFrame
{
public:
	MainWindow();

private:
	void OnAbout(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnNewGame(wxCommandEvent& event);
	void OnBtnClick(wxCommandEvent& event);
	void OnBtnLeaveWindow(wxCommandEvent& event);
	void OnBtnEvent(const int& i, const int& j);
	void playerMovement(const int& row, const int& col, const std::string& symbol);
	void EnableGrid();
	void DisableGrid();
	void initBoard();
	int checkBoard();
	void CpuCheckMovs();
	void checkWinner();
	void EndGame();

	wxButton* m_btn[3][3];
	wxMenu* m_menuGame;
	wxMenu* m_menuHelp;
	wxMenu* m_subMenuGame;
	wxMenuBar* m_mainMenuBar;
	wxStatusBar* m_statusBar;
	bool bIsAlone{ false };
	int board[3][3];
	int clickCounter{ 0 };
	int row{ 0 };
	int col{ 0 };
	int player{ 0 };
	int winner{ 0 };
};

