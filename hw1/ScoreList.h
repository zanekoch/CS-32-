#pragma once
#include "Sequence.h"
#include <limits>
const unsigned long NO_SCORE = std::numeric_limits<unsigned long>::max();

#ifndef SCORELIST
#define SCORELIST



class ScoreList
{
public:
	ScoreList();       // Create an empty score list //no for or while
	ScoreList& operator=(ScoreList& other);
	ScoreList(ScoreList& old);

	bool add(unsigned long score);
	// If the score is valid (a value from 0 to 100) and the score list
	// has room for it, add it to the score list and return true.
	// Otherwise, leave the score list unchanged and return false.
	//no for or while


	bool remove(unsigned long score);
	// Remove one instance of the specified score from the score list.
	// Return true if a score was removed; otherwise false.
	//no for or while

	int size() const;  // Return the number of scores in the list.
	//no for or while

	unsigned long minimum() const;
	// Return the lowest score in the score list.  If the list is
	// empty, return NO_SCORE.

	unsigned long maximum() const;
	// Return the highest score in the score list.  If the list is
	// empty, return NO_SCORE.

	//no need for copy constructor, assignment operator defintions



private:
	// Some of your code goes here.
	Sequence gradeSeq;

};
#endif // !SCORELIST