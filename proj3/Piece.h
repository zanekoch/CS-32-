#include <algorithm>
#include <vector>
#include "UserInterface.h"
#include "Well.h"
using namespace std;
#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z,
    PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY, NUM_PIECE_TYPES
};

PieceType chooseRandomPieceType();

class Screen;
class Well;

class Piece
{
public:
	Piece(int pounds);
	bool wouldOverlap(Well well);
	bool wouldOverlapRight(Well well);
	bool wouldOverlapLeft(Well well);
	
	bool timeToMove(int level, Well well);
	void display();
	//movers
	virtual bool move(int level, Well& well); //all pieces should move in the same way except for the crazy one which will have an overload of this function
	void moveRight(Well well);
	void moveLeft(Well well);
	bool SpaceBarMove(Well well);
	virtual void rotate(Well well) =0;
	//getters
	int getPounds() const;
	int getM_X(); int getM_Y();
	int getSpaceOccupied(int x, int y);
	int getOrientation();
	Screen getScreen();
	//setters
	void setSpaceOccupied(int x, int y, int newnum);
	void setOrientation();

	bool setPieceOccupiedIfNotOccupied(int x, int y, int newnum, Well well);

	bool wellFullGameOver(Well well);
	//destructor
	virtual ~Piece();
private:
	int m_x, m_y; //everypiece has an upperleft corner of their 4X4 bounding box
	int m_pounds; //this might not actually be that useful, we'll see
	int m_SpacesOccupiedByThisPiece[11][18];
	int m_orientation;
	Screen m_screen2;
};

class t_piece : public Piece
{
public:
	t_piece();
	virtual void rotate(Well well);
private:
};

class l_piece : public Piece
{
public:
	l_piece();
	virtual void rotate(Well well);
private:
};

class j_piece : public Piece
{
public:
	j_piece();
	virtual void rotate(Well well);
private:
};

class o_piece : public Piece
{
public:
	o_piece();
	virtual void rotate(Well well);
private:
};

class s_piece : public Piece
{
public:
	s_piece();
	virtual void rotate(Well well);
private:
};

class z_piece: public Piece
{
public:
	z_piece();
	virtual void rotate(Well well);
private:
};

class i_piece : public Piece
{
public:
	i_piece();
	//~i_piece();
	virtual void rotate(Well well);
private:
};

class crazy_piece : public Piece
{
public:
	crazy_piece();
	virtual void rotate(Well well);
	virtual bool timeToMove(int level, Well well);
	virtual bool move(int level, Well& well);
private:
	Screen m_CrazyScreen;
};

class vapor_piece : public Piece
{
public:
	vapor_piece();
	virtual void rotate(Well well);
private:
};

class foam_piece : public Piece
{
public:
	foam_piece();
	virtual void rotate(Well well);
	//void fill(int x, int y, Well well);
private:
};

#endif // PIECE_INCLUDED
