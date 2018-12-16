#include <iostream>
#include <vector>
#include <algorithm>
#include "UserInterface.h"
using namespace std;
#ifndef WELL_INCLUDED
#define WELL_INCLUDED

class Screen;

class Well
{
  public:
	Well();
    void display(Screen& screen, int x, int y);
	void displayStationary(Screen& screen);
	//getters
	int getStationaryPieces(int x, int y);
	//setters
	void setStationaryPieces(int x, int y);
	void clearStationaryPieces();
	void displayEmpty(Screen& screen);
	//zane code 
private:
	//maybe make a list of all the occupied spaces so when a piece is moving it can keep moving until it runs into another 
	int m_stationaryPieces[11][18];
//^^
};

#endif // WELL_INCLUDED
