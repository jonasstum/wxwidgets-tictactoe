#pragma once

#include <wx/wx.h>
#include <string>

enum ID
{
	SINGLE_PLAYER = 1,
	VS_CPU,
	X_0_0 = 10,
	X_0_1,
	X_0_2,
	X_1_0 = 101,
	X_1_1,
	X_1_2,
	X_2_0 = 1002,
	X_2_1,
	X_2_2
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
	void PlayerMovement(const int& row, const int& col, const std::string& symbol);
	int GetXY(const int& row, const int& col);
	void CpuPlays(const int& pos);
	void EnableGrid();
	void DisableGrid();
	void InitBoard();
	int CheckBoard();
	void CheckWinner();
	void EndGame();

	wxButton* m_btn[3][3];
	wxMenu* m_menuGame;
	wxMenu* m_menuHelp;
	wxMenu* m_subMenuGame;
	wxMenuBar* m_mainMenuBar;
	wxStatusBar* m_statusBar;
	bool m_bIsAlone{ false };
	int m_board[3][3];
	int m_clickCounter{ 0 };
	int m_row{ 0 };
	int m_col{ 0 };
	int m_player{ 0 };
	int m_winner{ 0 };
};

