#include "MainWindow.h"
#include "Utils.h"

MainWindow::MainWindow()
	: wxFrame(NULL, wxID_ANY, "Tic-Tac-Toe")
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
				
					)", "About Tic-Tac-Toe", wxOK | wxICON_INFORMATION);
}

void MainWindow::OnNewGame(wxCommandEvent& event)
{
	switch (event.GetId())
	{
	case ID::SINGLE_PLAYER:
		bIsAlone = true;
		EnableGrid();
		initBoard();
		SetStatusText("You are in the Single Player Mode. Mark a empty square to start the game!");
		break;

	case ID::VS_CPU:
		bIsAlone = false;
		EnableGrid();
		initBoard();
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

			row = 1;
			col = 1;
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

void MainWindow::initBoard()
{
	clickCounter = 0;
	player = 1;
	winner = 0;

	for (auto& i : board)
	{
		for (auto& j : i)
		{
			j = 0;
		}
	}
}

void MainWindow::OnBtnEvent(const int& i, const int& j)
{
	if (bIsAlone)
	{
		switch (player)
		{
		case 1:
			playerMovement(i, j, "X");
			break;

		case 2:
			playerMovement(i, j, "O");
			break;
		}
	}
	else
	{
		if (player == 1)
		{
			playerMovement(i, j, "X");
			CpuCheckMovs();

			while (!m_btn[row][col]->IsEnabled())
			{
				row = Utils::randomNumber();
				col = Utils::randomNumber();
			}

			playerMovement(row, col, "O");
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

void MainWindow::playerMovement(const int& row, const int& col, const std::string& symbol)
{
	board[row][col] = player;
	m_btn[row][col]->Disable();
	m_btn[row][col]->SetLabelText(symbol);

	clickCounter++;
	checkWinner();
}

void MainWindow::CpuCheckMovs()
{
	player = 2;

	if ((m_btn[0][1]->GetLabelText() == "X" && m_btn[0][2]->GetLabelText() == "X") ||
		(m_btn[1][0]->GetLabelText() == "X" && m_btn[2][0]->GetLabelText() == "X") ||
		(m_btn[1][1]->GetLabelText() == "X" && m_btn[2][2]->GetLabelText() == "X"))
	{
		row = 0;
		col = 0;
	}
	else if ((m_btn[1][1]->GetLabelText() == "X" && m_btn[2][1]->GetLabelText() == "X") ||
		(m_btn[0][0]->GetLabelText() == "X" && m_btn[0][2]->GetLabelText() == "X"))
	{
		row = 0;
		col = 1;
	}
	else if ((m_btn[0][0]->GetLabelText() == "X" && m_btn[0][1]->GetLabelText() == "X") ||
		(m_btn[1][1]->GetLabelText() == "X" && m_btn[2][0]->GetLabelText() == "X") ||
		(m_btn[1][2]->GetLabelText() == "X" && m_btn[2][2]->GetLabelText() == "X"))
	{
		row = 0;
		col = 2;
	}
	else if ((m_btn[0][0]->GetLabelText() == "X" && m_btn[2][0]->GetLabelText() == "X") ||
		(m_btn[1][1]->GetLabelText() == "X" && m_btn[1][2]->GetLabelText() == "X"))
	{
		row = 1;
		col = 0;
	}
	else if ((m_btn[0][2]->GetLabelText() == "X" && m_btn[2][2]->GetLabelText() == "X") ||
		(m_btn[1][0]->GetLabelText() == "X" && m_btn[1][1]->GetLabelText() == "X"))
	{
		row = 1;
		col = 2;
	}
	else if ((m_btn[0][0]->GetLabelText() == "X" && m_btn[1][0]->GetLabelText() == "X") ||
		(m_btn[0][2]->GetLabelText() == "X" && m_btn[1][1]->GetLabelText() == "X") ||
		(m_btn[2][1]->GetLabelText() == "X" && m_btn[2][2]->GetLabelText() == "X"))
	{
		row = 2;
		col = 0;
	}
	else if ((m_btn[0][1]->GetLabelText() == "X" && m_btn[1][1]->GetLabelText() == "X") ||
		(m_btn[2][0]->GetLabelText() == "X" && m_btn[2][2]->GetLabelText() == "X"))
	{
		row = 2;
		col = 1;
	}
	else if ((m_btn[0][0]->GetLabelText() == "X" && m_btn[1][1]->GetLabelText() == "X") ||
		(m_btn[0][2]->GetLabelText() == "X" && m_btn[1][2]->GetLabelText() == "X") ||
		(m_btn[2][0]->GetLabelText() == "X" && m_btn[2][1]->GetLabelText() == "X"))
	{
		row = 2;
		col = 2;
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
				if (player == 1)
				{
					m_statusBarMsg = "Playing Now: X - Player 1";
				}
				else
				{
					if (player == 2)
					{
						m_statusBarMsg = "Playing Now: O - Player 2";
					}
				}
			}

			SetStatusText(m_statusBarMsg);
		}
	}
}

int MainWindow::checkBoard()
{
	int playerOneMoves;
	int playerTwoMoves;

	// Horizontal
	for (auto& i : board)
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
			if (board[i][j] == 1)
			{
				playerOneMoves++;
			}
			else if (board[i][j] == 2)
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
	if (board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1)
	{
		return 1;
	}
	else if (board[0][0] == 2 && board[1][1] == 2 && board[2][2] == 2)
	{
		return 2;
	}

	// Antidiagonal
	if (board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1)
	{
		return 1;
	}
	else if (board[0][2] == 2 && board[1][1] == 2 && board[2][0] == 2)
	{
		return 2;
	}

	// If nobody wins...
	return 0;
}

void MainWindow::checkWinner()
{
	winner = checkBoard();

	if (winner != 0 || clickCounter >= 9)
	{
		EndGame();
	}
	else
	{
		switch (player)
		{
		case 1:
			player = 2;
			break;

		case 2:
			player = 1;
			break;
		}
	}
}

void MainWindow::EndGame()
{
	std::string message{ "" };

	switch (winner)
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
		initBoard();
		EnableGrid();
	}
	else
	{
		Destroy();
	}
}




