#include <iostream>
#include <stack>
using namespace std;

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


bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
	stack<Coord> coordinateStack;
	Coord endCoord = Coord(er, ec);

	coordinateStack.push(Coord(sr, sc));
	maze[sr][sc] = 'z';

	while (!coordinateStack.empty())
	{
		Coord currLoc = coordinateStack.top();
		coordinateStack.pop();
		if (currLoc.r() == endCoord.r()&& currLoc.c() == endCoord.c())
		{
			return true;
		}
		if (maze[currLoc.r() - 1][currLoc.c()] == '.')
		{
			coordinateStack.push(Coord(currLoc.r() - 1, currLoc.c()));
			maze[currLoc.r() - 1][currLoc.c()] = 'z';
		}
		if (maze[currLoc.r()][currLoc.c()-1] == '.')
		{
			coordinateStack.push(Coord(currLoc.r(), currLoc.c()-1));
			maze[currLoc.r()][currLoc.c()-1] = 'z';
		}
		if (maze[currLoc.r()+1][currLoc.c()] == '.')
		{
			coordinateStack.push(Coord(currLoc.r()+1, currLoc.c()));
			maze[currLoc.r()+1][currLoc.c()] = 'z';
		}
		if (maze[currLoc.r()][currLoc.c() + 1] == '.')
		{
			coordinateStack.push(Coord(currLoc.r(), currLoc.c() + 1));
			maze[currLoc.r()][currLoc.c() + 1] = 'z';
		}
	}
	return false;
}