#include "Piece.h"
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;
//need to figure out how to have pointer to class as data membber 
Piece::Piece(int pounds)
	:m_x(4), m_y(0), m_orientation(1), m_screen2(SCREEN_WIDTH, SCREEN_HEIGHT)
{
	m_pounds = pounds;
	//resize
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			m_SpacesOccupiedByThisPiece[i][j] = 0;
		}
	}
}

Piece::~Piece()
{

}

bool Piece::wellFullGameOver(Well well)
{
	for (int i = 1; i < 11; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			if (well.getStationaryPieces(i, j) == 2 && m_SpacesOccupiedByThisPiece[i][j] != 0)
				return true;
		}
	}
	return false; //game continues because would not immedietely overlap
}

bool Piece::wouldOverlap(Well well)
{
	//check if the spots in well::m_stationary
	for (int w = 17; w >= 0; w--)
	{
		for (int z = 10; z > 0; z--)
		{
			if (m_SpacesOccupiedByThisPiece[z][w] == 1) //if a certain location is occupied, check if one below this item it allowed
			{
				if (w == 17)
					return true; //bc it is at the bottom 
				if (well.getStationaryPieces(z, w+1) == 2)//if there is a stationary piece below it
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Piece::wouldOverlapRight(Well well)
{
	for (int i = 1; i < 11; i++) //1-10
	{
		for (int j = 0; j < 18; j++)
		{
			if (m_SpacesOccupiedByThisPiece[i][j] == 1)
			{
				if (i == 10)
					return true; //bc it is already at the side
				if (well.getStationaryPieces(i + 1, j) == 2)
					return true;
			}
		}
	}
	return false;
}

bool Piece::wouldOverlapLeft(Well well)
{
	for (int i = 1; i < 11; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			if (m_SpacesOccupiedByThisPiece[i][j] == 1)
			{
				if (i == 1)
					return true; //bc it is already at the side
				if (well.getStationaryPieces(i - 1, j) == 2)
					return true;
			}
		}
	}
	return false;
}

bool Piece::timeToMove(int level, Well well)
{
	Timer t;
	char ch;
	t.start();
	while (t.elapsed() < max(1000 - (100 * (level -1)), 100)) //change the 0 to depend on level eventually
	{
		if (getCharIfAny(ch))
		{
			switch (ch)
			{
			case (' '): //does not quite work yet, when it moves down it is not recognized and having stopped moving
				while (SpaceBarMove(well));
				discardPendingKeys();
				return true;
				break;
			case ARROW_DOWN:
				return true;
				break;
			case ARROW_RIGHT:
				discardPendingKeys();
				moveRight(well);
				break;
			case ARROW_LEFT:
				discardPendingKeys();
				moveLeft(well);
				break;
			case ARROW_UP:
				rotate(well);
				break;
			case 'q':
			case 'Q':
			default:
				break;
			}
		}
	}
	return true;
}

bool Piece::SpaceBarMove(Well well)
{
	if (!wouldOverlap(well))
	{
		for (int w = 16; w >= 0; w--)
		{
			for (int z = 10; z > 0; z--)
			{
				if (m_SpacesOccupiedByThisPiece[z][w] == 1)
				{
					setSpaceOccupied(z, w, 0); //make old value 0 so it is not displayed
					setSpaceOccupied(z, w + 1, 1); //make the value one below it equal to old value
				}
			}
		}
		display();
		well.displayStationary(m_screen2);
		return true; //it stopped moving cause it moved lol
	}
	display();
	well.displayStationary(m_screen2);
	return false; //it stopped moving cause would overlap
}

bool Piece::move(int level, Well& well) //might need a move sideways function and a wouldoverlapsideways function
{	
	while ( ! timeToMove(level, well))
	{/*wait until the time has run out or a has been reset*/}
	
	//reaches this point because it has run out of time or space bar has been pressed
	if ( ! wouldOverlap(well))
	{
		for (int w = 16; w >= 0; w--)
		{
			for (int z = 10; z > 0; z--)
			{
				if (m_SpacesOccupiedByThisPiece[z][w] == 1)
				{
					setSpaceOccupied(z, w, 0); //make old value 0 so it is not displayed
					setSpaceOccupied(z, w + 1, 1); //make the value one below it equal to old value
				}
			}
		}
		display();
		well.displayStationary(m_screen2);
		return true; //it stopped moving cause it moved lol
	}

	//since it would overlap, make it not move and then change it to $'s

	for (int w = 17; w >= 0; w--)
	{
		for (int z = 10; z > 0; z--)
		{
			if (getSpaceOccupied(z, w) == 1)
			{
				switch (m_pounds)
				{
				
				case 2:
					if (w == 16)
					{
						setSpaceOccupied(z, w, 0);
						setSpaceOccupied(z, w - 2, 0);
						setSpaceOccupied(z, w - 1, 0);
						setSpaceOccupied(z, w + 1, 0);
						if (well.getStationaryPieces(z, w - 1) != 0)
							well.setStationaryPieces(z, w - 1);
						if (well.getStationaryPieces(z, w - 2) != 0)
							well.setStationaryPieces(z, w - 2);
						if (well.getStationaryPieces(z, w + 1) != 0)
							well.setStationaryPieces(z, w + 1);
					}
					else if (w == 17)
					{
						setSpaceOccupied(z, w, 0);
						setSpaceOccupied(z, w - 2, 0);
						setSpaceOccupied(z, w - 1, 0);
						if (well.getStationaryPieces(z, w-1) != 0)
							well.setStationaryPieces(z, w - 1);
						if (well.getStationaryPieces(z, w - 2) != 0)
							well.setStationaryPieces(z, w - 2);
					}
					else if (w == 0)
					{
						setSpaceOccupied(z, w, 0);
						setSpaceOccupied(z, w + 1, 0);
						setSpaceOccupied(z, w + 2, 0);
						if (well.getStationaryPieces(z, w + 1) != 0)
							well.setStationaryPieces(z, w + 1);
						if (well.getStationaryPieces(z, w + 2) != 0)
							well.setStationaryPieces(z, w + 2);
					}
					else if (w == 1)
					{
						setSpaceOccupied(z, w, 0);
						setSpaceOccupied(z, w - 1, 0);
						setSpaceOccupied(z, w + 1, 0);
						setSpaceOccupied(z, w + 2, 0);
						if (well.getStationaryPieces(z, w + 1) != 0)
							well.setStationaryPieces(z, w + 1);
						if (well.getStationaryPieces(z, w + 2) != 0)
							well.setStationaryPieces(z, w + 2);
						if (well.getStationaryPieces(z, w - 1) != 0)
							well.setStationaryPieces(z, w - 1);
					}
					else
					{
						setSpaceOccupied(z, w, 0);
						setSpaceOccupied(z, w - 2, 0);
						setSpaceOccupied(z, w - 1, 0);
						setSpaceOccupied(z, w + 1, 0);
						setSpaceOccupied(z, w + 2, 0);
						if (well.getStationaryPieces(z, w - 1) != 0)
							well.setStationaryPieces(z, w - 1);
						if (well.getStationaryPieces(z, w - 2) != 0)
							well.setStationaryPieces(z, w - 2);
						if (well.getStationaryPieces(z, w + 1) != 0)
							well.setStationaryPieces(z, w + 1);
						if (well.getStationaryPieces(z, w + 2) != 0)
							well.setStationaryPieces(z, w + 2);
					}
					break;
				case 1:
					//this->fill(z, w, well);
				default:
					setSpaceOccupied(z, w, 2); //make all values with a 1 a 2 so it is a $
					well.setStationaryPieces(z, w);
				}
			}
		}
	}
	display();
	well.displayStationary(m_screen2);
	return false; //it stopped moving cause would overlap
}

void Piece::moveRight(Well well) //might need a move sideways function and a wouldoverlapsideways function
{
	if ( ! wouldOverlapRight(well))
	{
		for (int z = 10; z > 0; z--) //1-9
		{
			for (int w = 0; w < 18; w++) //1-17
			{
				if (m_SpacesOccupiedByThisPiece[z][w] != 0) 
				{
					m_SpacesOccupiedByThisPiece[z][w] = 0;
					m_SpacesOccupiedByThisPiece[z + 1][w] = 1;
				}
			}
		}
		display();
		well.displayStationary(m_screen2);
		return; //it stopped moving cause it moved lol
	}
	display();
	well.displayStationary(m_screen2);
	return; //didn't move cause there were not open spaces
}

void Piece::moveLeft(Well well) //might need a move sideways function and a wouldoverlapsideways function
{
	if ( ! wouldOverlapLeft(well))
	{
		for (int w = 0; w < 18; w++) //0-17
		{
			for (int z = 2; z < 11; z++) //2-10
			{
				if (getSpaceOccupied(z, w) != 0)
				{
					m_SpacesOccupiedByThisPiece[z][w] = 0;
					m_SpacesOccupiedByThisPiece[z - 1][w] = 1;
				}
			}
		}
		display();
		well.displayStationary(m_screen2);
		return; //it stopped moving cause it moved lol
	}
	display();
	well.displayStationary(m_screen2);
	return;
}

void Piece::display()
{
	for (int i = 1; i < 11; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			switch (getSpaceOccupied(i, j))
			{
			case 0:
				//going to eventually need to check if this overlaps with the $ or something
				m_screen2.gotoXY(i, j);
				m_screen2.printChar(' ');
				break;
			case 1: //if its a one assume its part of a moving piece
				m_screen2.gotoXY(i, j);
				m_screen2.printChar('#');
				break;
			case 2: //if 2 assume its a stationary block and let well's display, display it
				//m_screen2.gotoXY(i, j);
				//m_screen2.printChar('$');
				break;
			default:
				m_screen2.gotoXY(i, j);
				m_screen2.printChar('!');
				break; //if 0 or any other number do nothing
			}
		}
	}
}
int Piece::getPounds() const
{
	return m_pounds;
}
int Piece::getM_X()
{
	return m_x;
}
int Piece::getM_Y()
{
	return m_y;
}
void Piece::setSpaceOccupied(int x, int y, int newnum)
{
	m_SpacesOccupiedByThisPiece[x][y] = newnum;
}
int Piece::getSpaceOccupied(int x, int y)
{
	return m_SpacesOccupiedByThisPiece[x][y];
}
int Piece::getOrientation()
{
	return m_orientation;
}
void Piece::setOrientation()
{
	if (m_orientation != 4)
		m_orientation++;
	else
		m_orientation = 1;
}

Screen Piece::getScreen()
{
	return m_screen2;
}

bool Piece::setPieceOccupiedIfNotOccupied(int x, int y, int newnum, Well well)
{
	if (well.getStationaryPieces(x, y) != 0)
		return false;
	else if (x < 1 || x > 11 || y > 17)
		return false;
	else
	{
		setSpaceOccupied(x, y, newnum);
		return true;
	}
}

t_piece::t_piece()
	:Piece(4) //set the m_x and m_y and m_pounds to 4(cause shifted one by well-side), 0, and 4
{
	//make the 2d vector big enough to put stuff in

	//set all the values to either 0 if the piece does not occupy those or 1 if it does
	for (int z = 1; z < 11; z++)
	{
		for (int w = 0; w < 18; w++)
		{
			if (z == getM_X() + 0 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 1 && w == getM_Y() + 0)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 1 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 2 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else
			{
				setSpaceOccupied(z, w, 0);
			}
		}
	}

}
void t_piece::rotate(Well well)
{
	switch (getOrientation())
	{
	case 1:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z,w) == 1) //find the top point
				{
					setSpaceOccupied(z - 1, w + 1, 0);
					if (!setPieceOccupiedIfNotOccupied(z, w + 2, 1, well))
					{
						setSpaceOccupied(z - 1, w + 1, 1); 
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 2:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					if (!setPieceOccupiedIfNotOccupied(z - 1, w + 1, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 3:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z +2, w, 0);
					if (!setPieceOccupiedIfNotOccupied(z + 1, w - 1, 1, well))
					{
						setSpaceOccupied(z + 2, w, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 4:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w+2, 0);
					if (!setPieceOccupiedIfNotOccupied(z + 1, w + 1, 1, well))
					{
						setSpaceOccupied(z, w + 2, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
	}
}


l_piece::l_piece()
	:Piece(4) //set the m_x and m_y and m_pounds to 4(cause shifted one by well-side), 0, and 4
{
	//make the 2d vector big enough to put stuff in

	//set all the values to either 0 if the piece does not occupy those or 1 if it does
	for (int z = 1; z < 11; z++)
	{
		for (int w = 0; w < 18; w++)
		{
			if (z == getM_X() + 0 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 0 && w == getM_Y() + 2)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 1 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 2 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else
			{
				setSpaceOccupied(z, w, 0);
			}
		}
	}

}

void l_piece::rotate(Well well)
{
	switch (getOrientation())
	{
	case 1:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					setSpaceOccupied(z, w + 1, 0);
					setSpaceOccupied(z +1, w , 0);
					if (!setPieceOccupiedIfNotOccupied(z + 2, w - 1, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 1, 1);
						setSpaceOccupied(z + 1, w, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 1, w - 1, 1, well))
					{
						setSpaceOccupied(z + 2, w - 1, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 1, 1);
						setSpaceOccupied(z + 1, w, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 2, w + 1, 1, well))
					{
						setSpaceOccupied(z + 2, w - 1, 0);
						setSpaceOccupied(z + 1, w - 1, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 1, 1);
						setSpaceOccupied(z + 1, w, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 2:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					setSpaceOccupied(z+1, w, 0);
					if (!setPieceOccupiedIfNotOccupied(z, w + 2, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 1, w, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z - 1, w + 2, 1, well))
					{
						setSpaceOccupied(z, w + 2, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 1, w, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 3:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					setSpaceOccupied(z, w+1, 0);
					setSpaceOccupied(z-2, w+1, 0);
					if (!setPieceOccupiedIfNotOccupied(z - 1, w, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 1, 1);
						setSpaceOccupied(z - 2, w + 1, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z - 1, w + 2, 1, well))
					{
						setSpaceOccupied(z - 1, w, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 1, 1);
						setSpaceOccupied(z - 2, w + 1, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z, w + 2, 1, well)) 
					{
						setSpaceOccupied(z - 1, w, 0);
						setSpaceOccupied(z - 1, w + 2, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 1, 1);
						setSpaceOccupied(z - 2, w + 1, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 4:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w+1, 0);
					setSpaceOccupied(z, w+2, 0);
					setSpaceOccupied(z+1, w+2, 0);
					if (!setPieceOccupiedIfNotOccupied(z + 1, w, 1, well))
					{
						setSpaceOccupied(z, w + 1, 1);
						setSpaceOccupied(z, w + 2, 1);
						setSpaceOccupied(z + 1, w + 2, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z - 1, w, 1, well))
					{
						setSpaceOccupied(z + 1, w, 0);
						setSpaceOccupied(z, w + 1, 1);
						setSpaceOccupied(z, w + 2, 1);
						setSpaceOccupied(z + 1, w + 2, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z - 1, w + 1, 1, well))
					{
						setSpaceOccupied(z + 1, w, 0);
						setSpaceOccupied(z - 1, w, 0);
						setSpaceOccupied(z, w + 1, 1);
						setSpaceOccupied(z, w + 2, 1);
						setSpaceOccupied(z + 1, w + 2, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
	}
}

j_piece::j_piece()
	:Piece(4) //set the m_x and m_y and m_pounds to 4(cause shifted one by well-side), 0, and 4
{
	//make the 2d vector big enough to put stuff in

	//set all the values to either 0 if the piece does not occupy those or 1 if it does
	for (int z = 1; z < 11; z++)
	{
		for (int w = 0; w < 18; w++)
		{
			if (z == getM_X() + 1 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1 );
			}
			else if (z == getM_X() + 2 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 3 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 3 && w == getM_Y() + 2)
			{
				setSpaceOccupied(z, w, 1);
			}
			else
			{
				setSpaceOccupied(z, w, 0);
			}
		}
	}
}

void j_piece::rotate(Well well)
{
	switch (getOrientation())
	{
	case 1:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					setSpaceOccupied(z + 2, w, 0);
					setSpaceOccupied(z + 2, w + 1, 0);
					if (!setPieceOccupiedIfNotOccupied(z + 1, w + 2, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 2, w, 1);
						setSpaceOccupied(z + 2, w + 1, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 1, w + 1, 1, well))
					{
						setSpaceOccupied(z + 1, w+2, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 2, w, 1);
						setSpaceOccupied(z + 2, w + 1, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z, w + 2, 1, well))
					{
						setSpaceOccupied(z + 1, w + 2, 0);
						setSpaceOccupied(z + 1, w + 1, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 2, w, 1);
						setSpaceOccupied(z + 2, w + 1, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 2:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					setSpaceOccupied(z, w + 2, 0);
					setSpaceOccupied(z - 1, w + 2, 0);
					if (!setPieceOccupiedIfNotOccupied(z - 1, w, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 2, 1);
						setSpaceOccupied(z - 1, w + 2, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z - 1, w + 1, 1, well))
					{
						setSpaceOccupied(z - 1, w, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 2, 1);
						setSpaceOccupied(z - 1, w + 2, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 1, w + 1, 1, well))
					{
						setSpaceOccupied(z - 1, w + 1, 0);
						setSpaceOccupied(z - 1, w, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 2, 1);
						setSpaceOccupied(z - 1, w + 2, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 3:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z + 1, w + 1, 0);
					setSpaceOccupied(z + 2, w + 1, 0);
					if(!setPieceOccupiedIfNotOccupied(z, w - 1, 1, well))
					{
						setSpaceOccupied(z + 1, w + 1, 1);
						setSpaceOccupied(z + 2, w + 1, 1);

						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 1, w - 1, 1, well))
					{
						setSpaceOccupied(z, w -1, 0);
						setSpaceOccupied(z + 1, w + 1, 1);
						setSpaceOccupied(z + 2, w + 1, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 4:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					setSpaceOccupied(z, w+2, 0);
					setSpaceOccupied(z+1, w, 0);

					if (!setPieceOccupiedIfNotOccupied(z + 1, w + 1, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 2, 1);
						setSpaceOccupied(z + 1, w, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 2, w + 1, 1, well))
					{
						setSpaceOccupied(z + 1, w + 1, 0);

						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 2, 1);
						setSpaceOccupied(z + 1, w, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 2, w + 2, 1, well))
					{
						setSpaceOccupied(z + 1, w + 1, 0);
						setSpaceOccupied(z + 2, w + 1, 0);

						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 2, 1);
						setSpaceOccupied(z + 1, w, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
	}
}

o_piece::o_piece()
	:Piece(4)
{
	for (int z = 1; z < 11; z++)
	{
		for (int w = 0; w < 18; w++)
		{
			if (z == getM_X() && w == getM_Y())
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 1 && w == getM_Y() )
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() +1 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else
			{
				setSpaceOccupied(z, w, 0);
			}
		}
	}
}
void o_piece::rotate(Well well)
{
	return;
}

s_piece::s_piece()
	:Piece(4)
{
	for (int z = 1; z < 11; z++)
	{
		for (int w = 0; w < 18; w++)
		{
			if (z == getM_X() && w == getM_Y() +2)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 1 && w == getM_Y()+1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() +1 && w == getM_Y() + 2)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 2 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else
			{
				setSpaceOccupied(z, w, 0);
			}
		}
	}
}
void s_piece::rotate(Well well)
{
	switch (getOrientation())
	{
	case 3:
	case 1:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z - 1, w + 1, 0);
					setSpaceOccupied(z, w + 1, 0);
					if (!setPieceOccupiedIfNotOccupied(z, w - 1, 1, well))
					{
						setSpaceOccupied(z - 1, w + 1, 1);
						setSpaceOccupied(z, w + 1, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 1, w + 1, 1, well))
					{
						setSpaceOccupied(z, w - 1, 0);
						setSpaceOccupied(z - 1, w + 1, 1);
						setSpaceOccupied(z, w + 1, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 4:
	case 2:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					setSpaceOccupied(z + 1, w + 2, 0);
					if (!setPieceOccupiedIfNotOccupied(z, w + 2, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 1, w + 2, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z - 1, w + 2, 1, well))
					{
						setSpaceOccupied(z, w + 2, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 1, w + 2, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	}
}

z_piece::z_piece()
	:Piece(4)
{
	for (int z = 1; z < 11; z++)
	{
		for (int w = 0; w < 18; w++)
		{
			if (z == getM_X() && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 1 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 1 && w == getM_Y() + 2)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 2 && w == getM_Y() + 2)
			{
				setSpaceOccupied(z, w, 1);
			}
			else
			{
				setSpaceOccupied(z, w, 0);
			}
		}
	}
}
void z_piece::rotate(Well well)
{
	switch (getOrientation())
	{
	case 3:
	case 1:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					setSpaceOccupied(z+2, w+1, 0);
					if (!setPieceOccupiedIfNotOccupied(z + 2, w, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 2, w + 1, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 2, w - 1, 1, well))
					{
						setSpaceOccupied(z + 2, w, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 2, w + 1, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 4:
	case 2:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					setSpaceOccupied(z, w+1, 0);
					if (!setPieceOccupiedIfNotOccupied(z, w + 2, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 1, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z - 2, w + 1, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 2, 0);
						setSpaceOccupied(z, w + 1, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	}
}


i_piece::i_piece()
	:Piece(4)
{
	for (int z = 1; z < 11; z++)
	{
		for (int w = 0; w < 18; w++)
		{
			if (z == getM_X() && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 1 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 2 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 3 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else
			{
				setSpaceOccupied(z, w, 0);
			}
		}
	}
}


void i_piece::rotate(Well well)
{
	switch (getOrientation())
	{
	case 3:
	case 1:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					setSpaceOccupied(z+2, w, 0);
					setSpaceOccupied(z+3, w, 0);
					if (!setPieceOccupiedIfNotOccupied(z + 1, w - 1, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 2, w, 1);
						setSpaceOccupied(z + 3, w, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 1, w + 1, 1, well))
					{
						setSpaceOccupied(z + 1, w - 1, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 2, w, 1);
						setSpaceOccupied(z + 3, w, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 1, w + 2, 1, well))
					{
						setSpaceOccupied(z + 1, w + 1, 0);
						setSpaceOccupied(z + 1, w - 1, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 2, w, 1);
						setSpaceOccupied(z + 3, w, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 4:
	case 2:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					setSpaceOccupied(z, w+2, 0);
					setSpaceOccupied(z, w+3, 0);
					if (!setPieceOccupiedIfNotOccupied(z - 1, w + 1, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 2, 1);
						setSpaceOccupied(z, w + 3, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 1, w + 1, 1, well))
					{
						setSpaceOccupied(z - 1, w + 1, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 2, 1);
						setSpaceOccupied(z, w + 3, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 2, w + 1, 1, well))
					{
						setSpaceOccupied(z + 1, w + 1, 0);
						setSpaceOccupied(z - 1, w + 1, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z, w + 2, 1);
						setSpaceOccupied(z, w + 3, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	}
}

/*i_piece::~i_piece()
{

}*/

crazy_piece::crazy_piece()
	:Piece(4), m_CrazyScreen(SCREEN_WIDTH, SCREEN_HEIGHT)
{
	for (int z = 1; z < 11; z++)
	{
		for (int w = 0; w < 18; w++)
		{
			if (z == getM_X() && w == getM_Y())
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 1 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 2 && w == getM_Y() + 1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 3 && w == getM_Y())
			{
				setSpaceOccupied(z, w, 1);
			}
			else
			{
				setSpaceOccupied(z, w, 0);
			}
		}
	}
}


void crazy_piece::rotate(Well well)
{
	switch (getOrientation())
	{
	case 1:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					setSpaceOccupied(z + 1, w +1, 0);
					if (!setPieceOccupiedIfNotOccupied(z + 2, w + 2, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 1, w + 1, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 3, w + 3, 1, well))
					{
						setSpaceOccupied(z + 2, w + 2, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z + 1, w + 1, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	
	case 2:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z, w, 0);
					setSpaceOccupied(z-1, w+1, 0);
					if (!setPieceOccupiedIfNotOccupied(z - 2, w + 2, 1, well))
					{
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z - 1, w + 1, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z - 3, w + 3, 1, well))
					{
						setSpaceOccupied(z - 2, w + 2, 0);
						setSpaceOccupied(z, w, 1);
						setSpaceOccupied(z - 1, w + 1, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 3:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z+1, w, 0);
					setSpaceOccupied(z+2, w+1, 0);
					if (!setPieceOccupiedIfNotOccupied(z, w - 1, 1, well))
					{
						setSpaceOccupied(z + 1, w, 1);
						setSpaceOccupied(z + 2, w + 1, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z - 1, w - 2, 1, well))
					{
						setSpaceOccupied(z, w - 1, 0);
						setSpaceOccupied(z + 1, w, 1);
						setSpaceOccupied(z + 2, w + 1, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	case 4:
		for (int w = 0; w < 18; w++)
		{
			for (int z = 1; z < 11; z++)
			{
				if (getSpaceOccupied(z, w) == 1) //find the top point
				{
					setSpaceOccupied(z+1, w+2, 0);
					setSpaceOccupied(z, w+3, 0);
					if (!setPieceOccupiedIfNotOccupied(z + 2, w + 1, 1, well))
					{
						setSpaceOccupied(z + 1, w + 2, 1);
						setSpaceOccupied(z, w + 3, 1);
						display();
						return;
					}
					if (!setPieceOccupiedIfNotOccupied(z + 3, w, 1, well))
					{
						setSpaceOccupied(z + 2, w + 1, 0);
						setSpaceOccupied(z + 1, w + 2, 1);
						setSpaceOccupied(z, w + 3, 1);
						display();
						return;
					}
					setOrientation();
					display();
					return;
				}
			}
		}
		break;
	}
}

bool crazy_piece::timeToMove(int level, Well well)
{
	Timer t;
	char ch;
	t.start();
	while (t.elapsed() < max(1000 - (100 * (level - 1)), 100)) //change the 0 to depend on level eventually
	{
		if (getCharIfAny(ch))
		{
			switch (ch)
			{
			case (' '): //does not quite work yet, when it moves down it is not recognized and having stopped moving
				while (SpaceBarMove(well));
				return true;
				break;
			case ARROW_DOWN:
				return true;
				break;
			case ARROW_RIGHT:
				discardPendingKeys();
				moveLeft(well);
				break;
			case ARROW_LEFT:
				discardPendingKeys();
				moveRight(well);
				break;
			case ARROW_UP:
				rotate(well);
				break;
			default:
				break;
			}
		}
	}
	return true;
}


bool crazy_piece::move(int level, Well& well) //might need a move sideways function and a wouldoverlapsideways function
{
	while (!timeToMove(level, well))
	{/*wait until the time has run out or a has been reset*/
	}

	//reaches this point because it has run out of time or space bar has been pressed
	if (!wouldOverlap(well))
	{
		for (int w = 16; w >= 0; w--)
		{
			for (int z = 10; z > 0; z--)
			{
				if (this->getSpaceOccupied(z,w) == 1)
				{
					setSpaceOccupied(z, w, 0); //make old value 0 so it is not displayed
					setSpaceOccupied(z, w + 1, 1); //make the value one below it equal to old value
				}
			}
		}
		display();
		well.displayStationary(m_CrazyScreen);
		return true; //it stopped moving cause it moved lol
	}

	//since it would overlap, make it not move and then change it to $'s

	for (int w = 17; w >= 0; w--)
	{
		for (int z = 10; z > 0; z--)
		{
			if (getSpaceOccupied(z, w) == 1)
			{
				setSpaceOccupied(z, w, 2); //make all values with a 1 a 2 so it is a $
				well.setStationaryPieces(z, w);
			}
		}
	}
	display();
	well.displayStationary(m_CrazyScreen);
	return false; //it stopped moving cause would overlap
}

vapor_piece::vapor_piece()
	:Piece(2)
{
	for (int z = 1; z < 11; z++)
	{
		for (int w = 0; w < 18; w++)
		{
			if (z == getM_X() +1 && w == getM_Y())
			{
				setSpaceOccupied(z, w, 1);
			}
			else if (z == getM_X() + 2 && w == getM_Y())
			{
				setSpaceOccupied(z, w, 1);
			}
			else
			{
				setSpaceOccupied(z, w, 0);
			}
		}
	}
}

void vapor_piece::rotate(Well well)
{
	return;
}

foam_piece::foam_piece()
	:Piece(1)
{
	for (int z = 1; z < 11; z++)
	{
		for (int w = 0; w < 18; w++)
		{
			if (z == getM_X() + 1 && w == getM_Y()+1)
			{
				setSpaceOccupied(z, w, 1);
			}
			else
			{
				setSpaceOccupied(z, w, 0);
			}
		}
	}
}

void foam_piece::rotate(Well well)
{
	return;
}/*
 void foam_piece::fill(int x, int y, Well well)
{
	for (int i = 1; i < 5; i++)
	{
		for (int j = 1; j < 5; j++)
		{
			if (well.getStationaryPieces(x+i,y+j) == 0)
			{
				well.setStationaryPieces(x + i, y + j);
			}
		}
	}
	
}*/