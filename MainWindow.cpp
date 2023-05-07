#include "MainWindow.h"
#include "Utils.h"

MainWindow::MainWindow()
	: wxFrame(NULL, wxID_ANY, "WxTicTacToe")
{
	this->SetSizeHints(540, 540);
	this->SetBackgroundColour(wxColor(*wxBLACK));

	m_mainMenuBar = new wxMenuBar();
	m_menuGame = new wxMenu();
	m_menuHelp = new wxMenu();
	m_subMenuGame = new wxMenu();

	m_mainMenuBar->Append(m_menuGame, "Game");
	m_mainMenuBar->Append(m_menuHelp, "Help");
	m_subMenuGame->Append(ID::SINGLE_PLAYER, "Play Alone\tCtrl+A", "Play the game alone");
	m_subMenuGame->Append(ID::VS_CPU, "Play VS CPU\tCtrl+N", "Play against the CPU");
	m_menuGame->AppendSubMenu(m_subMenuGame, "New Game\t", "Start a new game");
	m_menuGame->AppendSeparator();
	m_menuGame->Append(wxID_EXIT, "Quit\tAlt+F4");
	m_menuHelp->Append(wxID_ABOUT);

	wxFont font(50, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_SLANT, wxFONTWEIGHT_BOLD, false);

	this->SetMenuBar(m_mainMenuBar);

	wxGridSizer* gBoard = new wxGridSizer(3, 3, 0, 0);
	gBoard->SetMinSize(450, 450);

	for (auto& i : m_btn)
	{
		for (auto& j : i)
		{
			j = nullptr;
		}
	}

	int btnID{ 1 };

	for (auto& i : m_btn)
	{
		for (auto& j : i)
		{
			j = new wxButton(this, btnID, wxEmptyString, wxDefaultPosition, wxSize(40, 40), 0);
			j->SetFont(font);
			gBoard->Add(j, 0, wxALL | wxEXPAND, 5);

			btnID++;
		}
	}

	this->SetSizer(gBoard);
	this->Layout();

	m_statusBar = this->CreateStatusBar(1, wxST_SIZEGRIP, wxID_ANY);

	this->Centre(wxBOTH);

	DisableGrid();

	m_btn[0][0]->SetLabelText("T");
	m_btn[0][1]->SetLabelText("I");
	m_btn[0][2]->SetLabelText("C");
	m_btn[1][0]->SetLabelText("T");
	m_btn[1][1]->SetLabelText("A");
	m_btn[1][2]->SetLabelText("C");
	m_btn[2][0]->SetLabelText("T");
	m_btn[2][1]->SetLabelText("O");
	m_btn[2][2]->SetLabelText("E");

	SetStatusText("Go to -> Game -> New Game to start a new game!");

	Bind(wxEVT_MENU, &MainWindow::OnNewGame, this, ID::SINGLE_PLAYER);
	Bind(wxEVT_MENU, &MainWindow::OnNewGame, this, ID::VS_CPU);
	Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
	Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);

	btnID = 1;

	for (auto& i : m_btn)
	{
		for (auto& j : i)
		{
			j->Connect(btnID, wxEVT_COMMAND_BUTTON_CLICKED,
				wxCommandEventHandler(MainWindow::OnBtnClick), NULL, this);
			btnID++;
		}
	}

	for (auto& i : m_btn)
	{
		for (auto& j : i)
		{
			j->Connect(wxEVT_LEAVE_WINDOW,
				wxCommandEventHandler(MainWindow::OnBtnLeaveWindow), NULL, this);
		}
	}
}

void MainWindow::OnAbout(wxCommandEvent& event)
{
	wxMessageBox(R"(How To Play:
					
					- Player 1 (you/friend) are X and Player 2 (you/friend or the CPU) is O.
 
					- Players take turns putting their marks in empty squares.

					- The first Player to get 3 of her marks in a row (up, down, across, or 
					   diagonally) is the winner.

					- When all 9 squares are full, the game is over.
					
					Have Fun!
				
					)", "About WxTicTacToe", wxOK | wxICON_INFORMATION);
}

void MainWindow::OnNewGame(wxCommandEvent& event)
{
	switch (event.GetId())
	{
	case ID::SINGLE_PLAYER:
		m_bIsAlone = true;
		EnableGrid();
		InitBoard();
		SetStatusText("You are in the Single Player Mode. Mark a empty square to start the game!");
		break;

	case ID::VS_CPU:
		m_bIsAlone = false;
		EnableGrid();
		InitBoard();
		SetStatusText("You are in the Play VS CPU Mode. Mark a empty square to start the game!");
		break;
	}
}

void MainWindow::OnExit(wxCommandEvent& event)
{
	Destroy();
}

void MainWindow::EnableGrid()
{
	for (auto& i : m_btn)
	{
		for (auto& j : i)
		{
			j->Enable();
			j->SetLabelText("");

			m_row = 1;
			m_col = 1;
		}
	}
}

void MainWindow::DisableGrid()
{
	for (auto& i : m_btn)
	{
		for (auto& j : i)
		{
			j->Disable();
			j->SetLabelText("");
		}
	}
}

void MainWindow::InitBoard()
{
	m_clickCounter = 0;
	m_player = 1;
	m_winner = 0;

	for (auto& i : m_board)
	{
		for (auto& j : i)
		{
			j = 0;
		}
	}
}

void MainWindow::OnBtnEvent(const int& i, const int& j)
{
	if (m_bIsAlone)
	{
		switch (m_player)
		{
		case 1:
			PlayerMovement(i, j, "X");
			break;

		case 2:
			PlayerMovement(i, j, "O");
			break;
		}
	}
	else
	{
		if (m_player == 1)
		{
			PlayerMovement(i, j, "X");
			CpuPlays(GetXY(i, j));

			while (!m_btn[m_row][m_col]->IsEnabled())
			{
				m_row = Utils::RandomNumber();
				m_col = Utils::RandomNumber();
			}

			PlayerMovement(m_row, m_col, "O");
		}
	}
}

void MainWindow::OnBtnClick(wxCommandEvent& event)
{
	switch (event.GetId())
	{
	case 1:
		OnBtnEvent(0, 0);
		break;

	case 2:
		OnBtnEvent(0, 1);
		break;

	case 3:
		OnBtnEvent(0, 2);
		break;

	case 4:
		OnBtnEvent(1, 0);
		break;

	case 5:
		OnBtnEvent(1, 1);
		break;

	case 6:
		OnBtnEvent(1, 2);
		break;

	case 7:
		OnBtnEvent(2, 0);
		break;

	case 8:
		OnBtnEvent(2, 1);
		break;

	case 9:
		OnBtnEvent(2, 2);
		break;
	}
}

void MainWindow::PlayerMovement(const int& row, const int& col, const std::string& symbol)
{
	m_board[row][col] = m_player;
	m_btn[row][col]->Disable();
	m_btn[row][col]->SetLabelText(symbol);

	m_clickCounter++;
	CheckWinner();
}

int MainWindow::GetXY(const int& row, const int& col)
{
	int res{ 0 };

	switch (row)
	{
	case 0:
		res = row + col + 10;
		break;

	case 1:
		res = row + col + 100;
		break;

	case 2:
		res = row + col + 1000;
		break;
	}

	return res;
}

void MainWindow::CpuPlays(const int& pos)
{
	m_player = 2;

	if ((m_btn[0][0]->GetLabelText() == "X" && m_btn[0][2]->GetLabelText() == "X") ||
		(m_btn[0][2]->GetLabelText() == "X" && m_btn[0][0]->GetLabelText() == "X"))
	{
		m_row = 0;
		m_col = 1;
	}
	else if ((m_btn[0][0]->GetLabelText() == "X" && m_btn[2][0]->GetLabelText() == "X") ||
		(m_btn[2][0]->GetLabelText() == "X" && m_btn[0][0]->GetLabelText() == "X"))
	{
		m_row = 1;
		m_col = 0;
	}
	else if ((m_btn[0][2]->GetLabelText() == "X" && m_btn[2][2]->GetLabelText() == "X") ||
		(m_btn[2][2]->GetLabelText() == "X" && m_btn[0][2]->GetLabelText() == "X"))
	{
		m_row = 1;
		m_col = 2;
	}
	else if ((m_btn[2][0]->GetLabelText() == "X" && m_btn[2][2]->GetLabelText() == "X") ||
		(m_btn[2][2]->GetLabelText() == "X" && m_btn[2][0]->GetLabelText() == "X"))
	{
		m_row = 2;
		m_col = 1;
	}

	switch (pos)
	{
	case ID::X_0_0:
		if (m_btn[0][0]->GetLabelText() == "X" && m_btn[0][1]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 2;
		}
		else if (m_btn[0][0]->GetLabelText() == "X" && m_btn[1][0]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 0;
		}
		else if (m_btn[0][0]->GetLabelText() == "X" && m_btn[1][1]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 2;
		}
		break;

	case ID::X_0_1:
		if (m_btn[0][1]->GetLabelText() == "X" && m_btn[0][0]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 2;
		}
		else if (m_btn[0][1]->GetLabelText() == "X" && m_btn[0][2]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 0;
		}
		else if (m_btn[0][1]->GetLabelText() == "X" && m_btn[1][1]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 1;
		}
		break;

	case ID::X_0_2:
		if (m_btn[0][2]->GetLabelText() == "X" && m_btn[0][1]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 0;
		}
		else if (m_btn[0][2]->GetLabelText() == "X" && m_btn[1][2]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 2;
		}
		else if (m_btn[0][2]->GetLabelText() == "X" && m_btn[1][1]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 0;
		}
		break;

	case ID::X_1_0:
		if (m_btn[1][0]->GetLabelText() == "X" && m_btn[1][1]->GetLabelText() == "X")
		{
			m_row = 1;
			m_col = 2;
		}
		else if (m_btn[1][0]->GetLabelText() == "X" && m_btn[0][0]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 0;
		}
		else if (m_btn[1][0]->GetLabelText() == "X" && m_btn[2][0]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 0;
		}
		break;

	case ID::X_1_1:
		if (m_btn[1][1]->GetLabelText() == "X" && m_btn[1][0]->GetLabelText() == "X")
		{
			m_row = 1;
			m_col = 2;
		}
		else if (m_btn[1][1]->GetLabelText() == "X" && m_btn[1][2]->GetLabelText() == "X")
		{
			m_row = 1;
			m_col = 0;
		}
		else if (m_btn[1][1]->GetLabelText() == "X" && m_btn[0][0]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 2;
		}
		else if (m_btn[1][1]->GetLabelText() == "X" && m_btn[2][2]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 0;
		}
		else if (m_btn[1][1]->GetLabelText() == "X" && m_btn[0][2]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 0;
		}
		else if (m_btn[1][1]->GetLabelText() == "X" && m_btn[2][0]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 2;
		}
		else if (m_btn[1][1]->GetLabelText() == "X" && m_btn[0][1]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 1;
		}
		else if (m_btn[1][1]->GetLabelText() == "X" && m_btn[2][1]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 1;
		}
		break;

	case ID::X_1_2:
		if (m_btn[1][2]->GetLabelText() == "X" && m_btn[1][1]->GetLabelText() == "X")
		{
			m_row = 1;
			m_col = 0;
		}
		else if (m_btn[1][2]->GetLabelText() == "X" && m_btn[0][2]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 2;
		}
		else if (m_btn[1][2]->GetLabelText() == "X" && m_btn[2][2]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 2;
		}
		break;

	case ID::X_2_0:
		if (m_btn[2][0]->GetLabelText() == "X" && m_btn[1][0]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 0;
		}
		else if (m_btn[2][0]->GetLabelText() == "X" && m_btn[2][1]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 2;
		}
		else if (m_btn[2][0]->GetLabelText() == "X" && m_btn[1][1]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 2;
		}
		break;

	case ID::X_2_1:
		if (m_btn[2][1]->GetLabelText() == "X" && m_btn[2][0]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 2;
		}
		else if (m_btn[2][1]->GetLabelText() == "X" && m_btn[2][2]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 0;
		}
		else if (m_btn[2][1]->GetLabelText() == "X" && m_btn[1][1]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 1;
		}
		break;

	case ID::X_2_2:
		if (m_btn[2][2]->GetLabelText() == "X" && m_btn[2][1]->GetLabelText() == "X")
		{
			m_row = 2;
			m_col = 0;
		}
		else if (m_btn[2][2]->GetLabelText() == "X" && m_btn[1][2]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 2;
		}
		else if (m_btn[2][2]->GetLabelText() == "X" && m_btn[1][1]->GetLabelText() == "X")
		{
			m_row = 0;
			m_col = 0;
		}
		break;
	}
}

void MainWindow::OnBtnLeaveWindow(wxCommandEvent& event)
{
	std::string m_statusBarMsg;

	for (auto& i : m_btn)
	{
		for (auto& j : i)
		{
			if (j->IsEnabled())
			{
				if (m_player == 1)
				{
					m_statusBarMsg = "Playing Now: X - Player 1";
				}
				else
				{
					if (m_player == 2)
					{
						m_statusBarMsg = "Playing Now: O - Player 2";
					}
				}
			}

			SetStatusText(m_statusBarMsg);
		}
	}
}

int MainWindow::CheckBoard()
{
	int playerOneMoves;
	int playerTwoMoves;

	// Horizontal
	for (auto& i : m_board)
	{
		playerOneMoves = 0;
		playerTwoMoves = 0;

		for (auto& j : i)
		{
			if (j == 1)
			{
				playerOneMoves++;
			}
			else if (j == 2)
			{
				playerTwoMoves++;
			}
		}

		if (playerOneMoves == 3)
		{
			return 1;
		}
		else if (playerTwoMoves == 3)
		{
			return 2;
		}
	}

	// Vertical
	for (unsigned int j = 0; j < 3; ++j)
	{
		playerOneMoves = 0;
		playerTwoMoves = 0;

		for (unsigned int i = 0; i < 3; ++i)
		{
			if (m_board[i][j] == 1)
			{
				playerOneMoves++;
			}
			else if (m_board[i][j] == 2)
			{
				playerTwoMoves++;
			}
		}

		if (playerOneMoves == 3)
		{
			return 1;
		}
		else if (playerTwoMoves == 3)
		{
			return 2;
		}
	}

	// Main diagonal
	if (m_board[0][0] == 1 && m_board[1][1] == 1 && m_board[2][2] == 1)
	{
		return 1;
	}
	else if (m_board[0][0] == 2 && m_board[1][1] == 2 && m_board[2][2] == 2)
	{
		return 2;
	}

	// Antidiagonal
	if (m_board[0][2] == 1 && m_board[1][1] == 1 && m_board[2][0] == 1)
	{
		return 1;
	}
	else if (m_board[0][2] == 2 && m_board[1][1] == 2 && m_board[2][0] == 2)
	{
		return 2;
	}

	// If nobody wins...
	return 0;
}

void MainWindow::CheckWinner()
{
	m_winner = CheckBoard();

	if (m_winner != 0 || m_clickCounter >= 9)
	{
		EndGame();
	}
	else
	{
		switch (m_player)
		{
		case 1:
			m_player = 2;
			break;

		case 2:
			m_player = 1;
			break;
		}
	}
}

void MainWindow::EndGame()
{
	std::string message{ "" };

	switch (m_winner)
	{
	case 0:
		message = "Tied Game!";
		break;

	case 1:
		message = "X - Player 1 Wins!";
		break;

	case 2:
		message = "O - Player 2 Wins!";
		break;
	}

	message += " Play Again?";

	if (wxMessageBox(message, "Game Over!", wxYES_NO | wxICON_INFORMATION) == wxYES)
	{
		InitBoard();
		EnableGrid();
	}
	else
	{
		Destroy();
	}
}




