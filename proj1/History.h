#pragma once
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include "globals.h"
using namespace std;

class History
{
private:
	int m_hrows;
	int m_hcols;
	char convLoc[MAXROWS][MAXCOLS];
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
};