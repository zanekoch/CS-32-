#include "Game.h"
//stop the memory leaks

//implement the foam bomb

//display the next piece

//get rows left not to go to negative

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 0;
const int WELL_Y = 0;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
	: m_well(), m_well2(), m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_score(0), m_rowsLeft(5), m_newPiece(nullptr)
{

}

/*Game::~Game()
{
	delete m_newPiece;
}*/


void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y); //display the well
    displayStatus();  
	displayScoreAndRowsAndLevel(); //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]
    for( ;; )
    {	
		if (!playOneLevel())
		{
			//delete m_newPiece; //delete m_nextPiece;
			displayPrompt("Game Over!  Press the Enter key to exit!");
			waitForEnter();
			return;
		}
		else
		{
			//clear the board
			m_well.clearStationaryPieces();
			m_well.displayEmpty(m_screen);
			displayPrompt("Good job!  Press the Enter key to start next level!");
			waitForEnter();
			m_level++;
			m_rowsLeft = m_level * 5;
			m_newPiece = nullptr;
			continue;
		}
    }
}

bool Game::playOneLevel()
{
	//depending on what level, call a certain sequence of events
	
	for (int i = 0; i < 2; i++)
	{
		switch (chooseRandomPieceType())
		{
		case PIECE_VAPOR:
			if (m_newPiece != nullptr)
			{
				delete m_newPiece;
				m_newPiece = nullptr;
			}
			m_newPiece = new vapor_piece;
			break;
		case PIECE_I:
			if (m_newPiece != nullptr)
			{
				delete m_newPiece;
				m_newPiece = nullptr;
			}
			m_newPiece = new i_piece;
			break;
		case PIECE_L:
			if (m_newPiece != nullptr)
			{
				delete m_newPiece;
				m_newPiece = nullptr;
			}
			m_newPiece = new l_piece;
			break;
		case PIECE_J:
			if (m_newPiece != nullptr)
			{
				delete m_newPiece;
				m_newPiece = nullptr;
			}
			m_newPiece = new j_piece;
			break;
		case PIECE_T:
			if (m_newPiece != nullptr)
			{
				delete m_newPiece;
				m_newPiece = nullptr;
			}
			m_newPiece = new t_piece;
			break;
		case PIECE_O:
			if (m_newPiece != nullptr)
			{
				delete m_newPiece;
				m_newPiece = nullptr;
			}
			m_newPiece = new o_piece;
			break;
		case PIECE_S:
			if (m_newPiece != nullptr)
			{
				delete m_newPiece;
				m_newPiece = nullptr;
			}
			m_newPiece = new s_piece;
			break;
		case PIECE_Z:
			if (m_newPiece != nullptr)
			{
				delete m_newPiece;
				m_newPiece = nullptr;
			}
			m_newPiece = new z_piece;
			break;
		case PIECE_FOAM:
			if (m_newPiece != nullptr)
			{
				delete m_newPiece;
				m_newPiece = nullptr;
			}
			m_newPiece = new foam_piece;
			break;
		case PIECE_CRAZY:
			if (m_newPiece != nullptr)
			{
				delete m_newPiece;
				m_newPiece = nullptr;
			}
			m_newPiece = new crazy_piece;
			break;
		case NUM_PIECE_TYPES:
		default:
			if (m_newPiece != nullptr)
			{
				delete m_newPiece;
				m_newPiece = nullptr;
			}
			m_newPiece = new i_piece;
			break;
		}
		/*if (i == 0)
			m_newPiece = m_nextPiece;*/
	}
	if (m_newPiece->wellFullGameOver(m_well))
	{
		if (m_newPiece)
		{
			delete m_newPiece;
			m_newPiece = nullptr;
		}
		return false;
		return playOneLevel();
	}
	displayScoreAndRowsAndLevel();
	for (;;)//while haven't lost or won
	{
		m_newPiece->display();
		m_well.displayStationary(m_screen);
		if (!m_newPiece->move(m_level, m_well))
		{
			
			int temp = m_rowsLeft;
			m_rowsLeft -= checkDeleteRow(m_well, 1);
			if (temp > m_rowsLeft)
			{
				temp = temp - m_rowsLeft;
				m_score += pow(2, temp - 1) * 100;
			}
			displayScoreAndRowsAndLevel();
			if (m_rowsLeft <= 0)
			{
				m_screen.gotoXY(30, 3);
				delete m_newPiece;
				return true;
			}
			m_newPiece->display();
			m_well.displayStationary(m_screen);
			/*if (m_newPiece)*/
			//delete m_newPiece;
			return playOneLevel();
		}
	}
	m_well.clearStationaryPieces();
}

int Game::checkDeleteRow(Well& well, int yval)
{
	int counter = 0;
	if (yval == 18)
		return 0;

	for (int i = 1; i < 11; i++) //2-10
	{
		if (well.getStationaryPieces(i, yval) == 2)
		{
			counter++;
		}
		else
		{
			//reset counter and go out of the loop to try at next row
			counter = 0;
			break;
		}
		if (counter == 10)
		{
			
			//delete the row and move everything above down
			for (int w = 1; w < 11; w++)
				well.setStationaryPieces(w, yval);
			//move all the stuff above down
			for (int x = 1; x < 11; x++) //for all values
			{
				for (int z = yval; z >= 0; z--) //
				{
					if (well.getStationaryPieces(x, z) == 2) // 
					{
						well.setStationaryPieces(x, z + 1);
						well.setStationaryPieces(x, z);
					}
				}
			}
			return (1 + checkDeleteRow(well, yval + 1)); //call again with same y val cause
		}
	}
	return (0 + checkDeleteRow(well, yval + 1)); //if rows was not ready to be deleted check if the next one is
}

	
	
	
	/*int counter = 0;
	int rowsDeleted = 0;
	for (int j = 0; j < 18; j++)
	{
		if (well.getStationaryPieces(1, j) == 2) //if the first item in a row is filled check if the rest are
		{
			counter++; //counter is 1
			for (int i = 2; i < 11; i++) //2-10
			{
				if (well.getStationaryPieces(i, j) == 2)
				{
					counter++;
				}
				else
				{
					//reset counter and go out of the loop to try at next row
					counter = 0;
					break; 
				}
				if (counter == 10)
				{
					//delete the row
					rowsDeleted++;
					for (int w = 1; w < 11; w++)
						well.setStationaryPieces(w, j);
					//move all the stuff above down
					for (int x = 1; x < 11; x++) //for all values
					{
						for (int z = j; z >= 0; z--) //
						{
							if (well.getStationaryPieces(x, z) == 2) // 
							{
								well.setStationaryPieces(x, z + 1);
								well.setStationaryPieces(x, z);
							}
						}
					}
				}
			}
		}
	}
	if (rowsDeleted!=0)
		m_score = pow(2, (rowsDeleted - 1)) * 100;
	return rowsDeleted ;
}*/




void Game::displayStatus()
{
	// [Replace this with code to display the status.]
	//comments are what need to be added
	m_screen.gotoXY(16, 3);
	m_screen.printString("Next piece:");//next piece
	m_screen.gotoXY(16, 8);
	m_screen.printString("Score:     ");//score
	m_screen.gotoXY(16, 9);
	m_screen.printString("Rows left: "); //rows left
	m_screen.gotoXY(16, 10);
	m_screen.printString("Level:     "); //level number
}

void Game::displayPrompt(std::string s)
{
	m_screen.gotoXY(PROMPT_X, PROMPT_Y);
	m_screen.printStringClearLine(s);   // overwrites previous text
	m_screen.refresh();
}

void Game::displayScoreAndRowsAndLevel()
{
	m_screen.gotoXY(27+7, 8);
	m_screen.printStringClearLine(to_string(m_score));
	m_screen.gotoXY(27+7, 9);
	m_screen.printStringClearLine(to_string(m_rowsLeft));
	m_screen.gotoXY(27+7, 10);
	m_screen.printStringClearLine(to_string(m_level));
	m_screen.gotoXY(27+7, 3);
}