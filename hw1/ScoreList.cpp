#include "ScoreList.h"
#include <limits>

ScoreList::ScoreList()// Create an empty score list  //no for or while
{
	//nothing yet?
}
//edit
ScoreList& ScoreList::operator=(ScoreList& other)
{
	if (this != &other)
	{
		ScoreList temp(other); //call of the copy constructor
		this->gradeSeq.Sequence::swap(temp.gradeSeq);
	}
	return *this;
}

ScoreList::ScoreList(ScoreList& old)
{
	if (this != &old)
	{
		this->gradeSeq = old.gradeSeq;
	}
}
//!!

//copy constructor
Sequence::Sequence(const Sequence& old)
{
	if (this != &old)
	{
		for (int i = 0; i < old.size(); i++)
		{
			seqArr[i] = old.seqArr[i];
		}
		numChanges = old.numChanges;
		sizeOfSeqArr = old.sizeOfSeqArr;
	}

}

//edit


bool ScoreList::add(unsigned long score)
{
	if (score >= 0 && score <= 100)
	{
		if (gradeSeq.insert(score))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
// If the score is valid (a value from 0 to 100) and the score list
// has room for it, add it to the score list and return true.
// Otherwise, leave the score list unchanged and return false.
//no for or while


bool ScoreList::remove(unsigned long score)
{
	int location = gradeSeq.find(score);
	if (gradeSeq.erase(location))
	{
		return true;
	}
	else
	{
		return false;
	}
}
// Remove one instance of the specified score from the score list.
// Return true if a score was removed; otherwise false.
//no for or while


int ScoreList::size() const // Return the number of scores in the list. //no for or while
{
	return gradeSeq.size();
}

unsigned long ScoreList::minimum() const
{
	unsigned long smallestNum;
	unsigned long maybeNum;
	bool first = true;
	if ((gradeSeq.empty())!=true)
	{
		for (int i = 0; i < gradeSeq.size(); i++)
		{
			if (first)
			{
				gradeSeq.get(i, maybeNum);
				smallestNum = maybeNum;
				first = false;
			}
			else
			{
				gradeSeq.get(i, maybeNum);
				if (maybeNum < smallestNum)
				{
					smallestNum = maybeNum;
				}
			}
		}
		return smallestNum;
	}
	else
	{
		return NO_SCORE;
	}
}
// Return the lowest score in the score list.  If the list is
// empty, return NO_SCORE.

unsigned long ScoreList::maximum() const
{
	unsigned long biggestNum;
	unsigned long maybeNum;
	bool first = true;
	if (!(gradeSeq.empty()))
	{
		for (int i = 0; i < gradeSeq.size(); i++)
		{
			if (first)
			{
				gradeSeq.get(i, maybeNum);
				biggestNum = maybeNum;
				first = false;
			}
			else
			{
				gradeSeq.get(i, maybeNum);
				if (maybeNum > biggestNum)
				{
					biggestNum = maybeNum;
				}
			}
		}
		return biggestNum;
	}
	else
	{
		return NO_SCORE;
	}
}
// Return the highest score in the score list.  If the list is
// empty, return NO_SCORE.

