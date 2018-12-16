#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include "History.h"
using namespace std;

History::History(int nRows, int nCols)  
{
	m_hrows = nRows;
	m_hcols = nCols;

	for (int row = 1; row <= m_hrows; row++)
	{
		for (int col = 1; col <= m_hcols; col++)
		{
			convLoc[row][col] = '.';
		}
	}
} 

bool History::record(int r, int c)
{
	
	if (r > 0 && r <= m_hrows)
	{
		if (c > 0 && c <= m_hcols)
		{
			if ((convLoc[r][c] >= 'A') && (convLoc[r][c] <= 'Z'))//moves up one letter
			{
				convLoc[r][c]++;
				return true;
			}
			else
			{
				convLoc[r][c] = 'A';
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

void History::display() const
{	
	clearScreen();
	for (int row = 1; row <= m_hrows; row++)
	{
		for (int col = 1; col <= m_hcols; col++)
		{
			cout << convLoc[row][col];
		}
		cout << endl;
	}
	cout << endl;
}

