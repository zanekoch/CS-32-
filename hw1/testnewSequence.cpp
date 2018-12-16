
#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	ItemType waba = 1000;
	Sequence a(waba);   // a can hold at most 1000 items
	Sequence b(5);      // b can hold at most 5 items
	Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
	ItemType v = 20;//some value of the appropriate type;
	// No failures inserting 5 items into b
	ItemType get;
	for (int k = 0; k < 5; k++)
	{
		assert(b.insert(v) != -1);
		b.get(k, get);
		//cerr << get << endl;
		assert(get == v);
	}
	// Failure if we try to insert a sixth item into b
	assert(b.insert(v) == -1);

	// When two Sequences' contents are swapped, their capacities are
	// swapped as well:
	
	
	Sequence d(b);
	ItemType getter;
	d.get(1, getter);
	//cerr << getter << endl;
	assert(getter == 20);

	a.swap(b);
	assert(a.insert(v) == -1 && b.insert(v) != -1);
	
	//cerr << "c: " << endl;
	c = b;
	for (int k = 0; k < 5; k++)
	{
		c.get(k, get);
		//cerr << get << endl;
	}

	Sequence one(10);
	for (int k = 0; k < 5; k++)
	{
		one.insert(k);
	}
	Sequence two(10);
	for (int k = 0; k < 10; k++)
	{
		two.insert(k);
	}
	two.swap(one);
	for (int k = 0; k < 10; k++)
	{
		if (two.get(k, get))
		{
			two.get(k, get);
			cerr << get << endl;
		}
	}

}
