#include <iostream>
using namespace std;
#include "Sequence.h"





Sequence::Sequence()
{
	numChanges = 0;
}
// Create an empty sequence (i.e., one with no items)

bool Sequence::empty()const
{
	if (numChanges == 0)
		return true;
	return false;
}  // Return true if the sequence is empty, otherwise false.
int Sequence::size() const
{
	return numChanges;
}    // Return the number of items in the sequence.
bool Sequence::insert(int pos, const ItemType& value)
{
	if (this->size() == pos)//checks if pos is at the end then it can just insert there
	{
		seqArr[this->size()] = value;
		numChanges++;
		return true;
	}
	else if ((this->size() + 1) < sizeOfSeqArr)//if pos is not the end makes sure it won't go past max length of seqArr and shifts everything back and inserts at pos
	{
		for (int i = (sizeOfSeqArr - 1); i >pos; i--)
		{
			seqArr[i] = seqArr[i - 1];
		}
		seqArr[pos] = value;
		numChanges++;
		return true;
	}
	else //if both are false then return false bc either negative or too big
	{
		return false;
	}
}
// Insert value into the sequence so that it becomes the item at
// position pos.  The original item at position pos and those that
// follow it end up at positions one higher than they were at before.
// Return true if 0 <= pos <= size() and the value could be
// inserted.  (It might not be, if the sequence has a fixed capacity,
// e.g., because it's implemented using a fixed-size array.)  Otherwise,
// leave the sequence unchanged and return false.  Notice that
// if pos is equal to size(), the value is inserted at the end.

int Sequence::insert(const ItemType& value)
{
	int p = this->size();
	bool thereIsAThingSmaller = false;
	if (this->size() >= sizeOfSeqArr)//if  seqarr is full return -1
	{
		return -1;
	}
	else //if made it to this point it means there is space to insert another item
	{
		for (int i = 0; i <= this->size(); i++) //loop to check where a smaller item is
		{
			if (value < seqArr[i])
			{
				if (i < p)
				{
					p = i;
					thereIsAThingSmaller = true;
				}
			}
		}
		if (thereIsAThingSmaller) //if there is a smaller item...
		{
			for (int j = (sizeOfSeqArr - 1); j > p; j--)//...use this loop to shift everything back and add it to spot p
			{
				seqArr[j] = seqArr[j - 1];
			}
			seqArr[p] = value;
			numChanges++;
			return p;
		}
		else //if there is not a smaller item, add it to the end
		{
			p = this->size();
			seqArr[p] = value;
			numChanges++;
			return p;
		}
	}
}
// Let p be the smallest integer such that value <= the item at
// position p in the sequence; if no such item exists (i.e.,
// value > all items in the sequence), let p be size().  Insert
// value into the sequence so that it becomes the item at position
// p.  The original item at position p and those that follow it end
// up at positions one higher than before.  Return p if the value
// was actually inserted.  Return -1 if the value was not inserted
// (perhaps because the sequence has a fixed capacity and is full).

bool Sequence::erase(int pos)
{
	if (pos >= 0 && pos < this->size())//checks if it is a place that can/should be erased
	{
		for (int i = pos; i <this->size(); i++)//if it is then uses a loop that shifts every element starting a one past pos to the place before it
											   //including the last item (seqArr[this->size-1]) so now the seqArr is one smaller
		{
			seqArr[i] = seqArr[i + 1];
		}
		numChanges--; //makes sure size () knows that the array shrunk
		return true;
	}
	else //if cannot be changed return false
	{
		return false;
	}
}
// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.

int Sequence::remove(const ItemType& value)
{
	int z = 0;
	for (int i = 0; i < this->size(); i++) //loop to go through all the item in the array comparing size
	{
		if (seqArr[i] == value) //when find one that is the same size...
		{
			for (int w = i; w <this->size(); w++)//use this loop to take it out
			{
				seqArr[w] = seqArr[w + 1];
			}
			z++;
			numChanges--;//make sure size() knows how many items there are
			i--;//make sure don't skip any items in the seqArr
		}
	}
	return z;
}
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).

bool Sequence::get(int pos, ItemType& value)const
{
	if (pos >= 0 && pos < this->size())//checks if it is a place that can be copied
	{
		value = seqArr[pos];
		return true;
	}
	else
	{
		return false;
	}
}
// If 0 <= pos < size(), copy into value the item at position pos
// in the sequence and return true.  Otherwise, leave value unchanged
// and return false.

bool Sequence::set(int pos, const ItemType& value)
{
	if (pos >= 0 && pos < this->size())
	{
		seqArr[pos] = value;
		return true;
	}
	else
	{
		return false;
	}
}
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.

int Sequence::find(const ItemType& value)const
{
	for (int i = 0; i < this->size(); i++)
	{
		if (seqArr[i] == value)
		{
			return i;
		}
	}
	return -1;
}
// Let p be the smallest integer such that value == the item at
// position p in the sequence; if no such item exists, let p be -1.
// Return p.


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//have to change so that there are no loops (kinda)
void Sequence::swap(Sequence& other)
{
	using std::swap;
	swap(this->numChanges, other.numChanges);
	swap(this->seqArr, other.seqArr);
	swap(this->sizeOfSeqArr, other.sizeOfSeqArr);
}
// Exchange the contents of this sequence with the other one.

void Sequence::dump()const
{
	cerr << "max items: " << sizeOfSeqArr << endl;
	cerr << "numChanges/length: " << numChanges << endl;
	cerr << "contents of seqArr:";
	for (int i = 0; i < this->size(); i++)
	{
		cerr << seqArr[i] << ", ";
	}
}