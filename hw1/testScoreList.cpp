#include <iostream>
using namespace std;
#include "ScoreList.h"
#include <assert.h>

int main()
{
	ScoreList test;
	for (int i = 0; i != 11; i++)
		test.add(i);
	test.remove(0);
	assert(test.minimum() == 1);
	assert(test.size() == 10);

	ScoreList test2 = test;
	assert(test2.minimum() == 1);
	assert(test2.size() == 10);

	ScoreList test3;
	test3 = test;
	assert(test3.minimum() == 1);
	assert(test3.size() == 10);


	cerr << "all assertions passed :)" << endl;
	return (0);
}