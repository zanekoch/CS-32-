#include "Well.h"


Well::Well()
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			m_stationaryPieces[i][j]=0;
		}
	}
}

void Well::display(Screen& screen, int x, int y)
{
	//screen.clear();
	for ( x; x < 10; x++)
	{
		screen.gotoXY(x+1, 18);
		screen.printChar('@');
	}
	for (y; y < 19; y++)
	{
		screen.gotoXY(0, y);
		screen.printChar('@');
		screen.gotoXY(10+1, y);
		screen.printChar('@');
	}

	for (int w = 0; w <18; w++)
	{
		for (int z = 0; z < 10; z++)
		{
			if (m_stationaryPieces[z][w] == 2) 
			{
				screen.gotoXY(z+1, w);
				screen.printChar('$');
			}
		}
	}
}
void Well::displayStationary(Screen& screen)
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			if (m_stationaryPieces[i][j] == 2)
			{
				screen.gotoXY(i, j);
				screen.printChar('$');
			}
			if (m_stationaryPieces[i][j] == 3)
			{
				screen.gotoXY(i, j);
				screen.printChar('*');
			}
		}
	}
}
void Well::displayEmpty(Screen& screen)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			if (m_stationaryPieces[i][j] == 0)
			{
				screen.gotoXY(i+1, j);
				screen.printChar(' ');
			}
		}
	}
}
void Well::clearStationaryPieces() 
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 18; j++)
		{
			m_stationaryPieces[i][j] = 0;
		}
	}
}
void Well::setStationaryPieces(int x, int y)
{
	if (m_stationaryPieces[x][y] == 0)
		m_stationaryPieces[x][y] = 2;
	else
		m_stationaryPieces[x][y] = 0;
}
int Well::getStationaryPieces(int x, int y)
{
	if (m_stationaryPieces[x][y] == 2)
		return 2;
	return (m_stationaryPieces[x][y]);
}