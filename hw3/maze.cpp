/*#include <iostream>
#include <queue>
using namespace std;*/

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

class Coord
{
public:
	Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
	int r() const { return m_r; }
	int c() const { return m_c; }
private:
	int m_r;
	int m_c;
};
/*
int main()
{
	char maze[10][10] = {
	{ 'X','X','X','X','X','X','X','X','X','X' },
	{ 'X','.','.','.','.','.','.','.','.','X' },
	{ 'X','X','X','X','X','.','X','.','X','X' },
	{ 'X','.','.','.','X','.','X','.','.','X' },
	{ 'X','.','X','.','.','.','X','.','.','X' },
	{ 'X','.','X','X','X','.','X','X','X','X' },
	{ 'X','X','X','.','.','.','.','X','.','X' },
	{ 'X','.','X','X','.','X','X','X','.','X' },
	{ 'X','.','.','.','.','X','.','.','.','X' },
	{ 'X','X','X','X','X','X','X','X','X','X' }
	};

	if (pathExists(maze, 6, 5, 1, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}
*/

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	//initialize starting and ending points
	Coord endCoord = Coord(er, ec);
	Coord begCoord = Coord(sr, sc);
	//if they are equal return true
	cout << sr << "," << sc << endl;
	if (er == sr && ec == sc)
		return true;
	//mark start point as visited
	maze[sr][sc] = 'z';
	//for each of the four directions, if thte location
	//one step in that direction is unvisited, then:
	if (maze[begCoord.r() - 1][begCoord.c()] == '.')
	{
		if (pathExists(maze, begCoord.r() - 1, begCoord.c(), er, ec))
			return true;
	}
	if (maze[begCoord.r()][begCoord.c() - 1] == '.')
	{
		if (pathExists(maze, begCoord.r(), begCoord.c() - 1, er, ec))
			return true;
	}
	if (maze[begCoord.r() + 1][begCoord.c()] == '.')
	{
		if(pathExists(maze, begCoord.r() + 1, begCoord.c(), er, ec))
			return true;
	}
	if (maze[begCoord.r()][begCoord.c() + 1] == '.')
	{
		if (pathExists(maze, begCoord.r(), begCoord.c() + 1, er, ec))
			return true;
	}
	return false;
}