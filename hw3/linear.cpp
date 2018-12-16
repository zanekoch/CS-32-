/*#include <iostream>
#include <string>
#include <assert.h>
using namespace std;*/


bool somePredicate(string s)
{
	return s.empty();
}

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const string a[], int n)
{
	if (n == 0)
		return true;
	if (!(somePredicate(a[0])))
		return false;
	return(allTrue(a + 1, n - 1));
}
//=======================================================================


// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const string a[], int n)
{
	if (n == 0)
	{
		return (0);
	}
	if (!somePredicate(a[0]))
	{
		return (1 + countFalse(a + 1, n - 1));
	}
	return countFalse(a + 1, n - 1);
}
//=======================================================================
// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.

int firstFalse(const string a[], int n)
{
	if (n <= 0)
	{
		return -1;
	}
	if (somePredicate(a[0]))
	{
		return ( 1 + firstFalse(a + 1, n - 1));
	}
	if ( ! somePredicate(a[0]))
	{
		return 0;
	}
	return (firstFalse(a + 1, n - 1));
}
//=======================================================================
// Return the subscript of the least string in the array (i.e.,
// the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the array has no elements to examine,
// return -1.

int indexOfLeast(const string a[], int n)
{
	if (n <= 0)
		return -1;
	int j = 1 + indexOfLeast(a + 1, n - 1);
	if (a[0] <= a[j])
		return 0;
	return j;
}
//=======================================================================
// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    "stan" "kyle" "cartman" "kenny" "kyle" "cartman" "butters"
// then the function should return true if a2 is
//    "kyle" "kenny" "butters"
// or
//    "kyle" "cartman" "cartman"
// and it should return false if a2 is
//    "kyle" "butters" "kenny"
// or
//    "stan" "kenny" "kenny"
bool includes(const string a1[], int n1, const string a2[], int n2)
{
	if (n2 == 0)
		return true;
	if (n1 == 0 && n2 != 0) //if a element of the second array does not appear before the first array runs out, return false
		return false;
	if (a2[0] == a1[0]) //if two elements are equal
		return (true && includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1)); //move both to next element, decrement size, and continue checking
	return (includes(a1 + 1, n1 - 1, a2, n2)); //if the two elements are not equal move the first array and keep checking against current elem of second
}
/*
int main()
{
	string arr[3] = { "hi", "me", "zane" };
	assert(allTrue(arr, 3) == false);
	string whattup[3] = { "", "hi","yyoo" };
	assert(countFalse(arr, 3) == 3);
	assert(countFalse(whattup, 3) == 2);
	assert(firstFalse(arr, 3) == 0);
	assert(firstFalse(whattup, 3) == 1);
	string arrTwo[4] = { "alpha","gamma","delta","beta"};
	assert(indexOfLeast(arrTwo, 4) == 0);
	assert(indexOfLeast(whattup, 3) == 0);
	string arrthree[3] = { "bb","cc","a" };
	assert(indexOfLeast(arrthree, 3) == 2);
	string last[7] = {"stan", "kyle", "cartman", "kenny", "kyle", "cartman", "butters"};
	string last2[3] = { "kyle", "butters", "kenny" };
	assert(includes(last, 7, last2, 3) == false);
	cout << "Passed all tests!" << endl;
}*/
