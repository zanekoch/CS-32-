#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include <string>
#include <string>
#include "Well.h"
#include "Piece.h"
#include <cmath>

// [Add other #include directives as necessary.]

class Game
{
  public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    // [Add other members as necessary.]
	int checkDeleteRow(Well& well, int yval);
	void displayScoreAndRowsAndLevel();
	//desctructor
	//~Game();
  private:
	  Well    m_well, m_well2;
	  Screen  m_screen;
	  int     m_level;
	  int     m_score;
	  int     m_rowsLeft;
	  Piece * m_newPiece;
	  //Piece * m_nextPiece;
    // [Add other members as necessary.]
};

#endif // GAME_INCLUDED
