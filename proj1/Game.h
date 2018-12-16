#pragma once
#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include "City.h"
#include "Player.h"
using namespace std;

class Game
{
public:
	// Constructor/destructor
	Game(int rows, int cols, int nFlatulans);
	~Game();

	// Mutators
	void play();

private:
	City * m_city;
};

