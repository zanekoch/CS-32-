// Dictionary.cpp

// This is a correct but horribly inefficient implementation of Dictionary
// functionality.  Your job is to change DictionaryImpl to a more efficient
// correct implementation.  You can change it any way you like, subject to
// restrictions in the spec (e.g., that the only C++ library container you
// are allowed to use are vector, list, stack, and queue (and string); if you
// want anything fancier, implement it yourself).

#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
using namespace std;
#include <iostream>
#include <algorithm>
void removeNonLetters(string& s);
void generateNextPermutation(string& permutation);
//===============================================================================
//hash table
//===============================================================================
#define NUMBER_BUCKETS 50000
class hashTable
{
public:
	hashTable();
	~hashTable();
	void insert(string word);
	bool search(string word, void callback(string));
	//void findCollisionNumber();
private:
	long long int hashFunction(string word)
	{
		long long int seed = 131;
		unsigned long hash = 0;
		for (int i = 0; i < word.length(); i++)
		{
			hash = (hash * seed) + word[i];
		}
		return hash % NUMBER_BUCKETS;
	}
	list<string> **chain;
};

hashTable::hashTable()
{
	chain = new list<string>*[NUMBER_BUCKETS];
	for (int i = 0; i < NUMBER_BUCKETS; i++)
	{
		chain[i] = new list<string>;
	}
}

hashTable::~hashTable()
{
	for (int i = 0; i < NUMBER_BUCKETS; i++)
	{
		delete chain[i];
	}
	delete[] chain;
}

void hashTable::insert(string word)
{
	removeNonLetters(word); //remove the bad letters
	string temp = word;

	if (word.empty())
		return;
	sort(word.begin(), word.end()); //sort the word alphabetically
	long long int bucket = hashFunction(word); 
	chain[bucket]->push_back(temp); //push the word to its appropriate bucket
}

bool hashTable::search(string word, void callback(string))
{ 
	removeNonLetters(word); //remove the bad letters
	sort(word.begin(), word.end()); //sort the word alphabetically
	long long int bucket = hashFunction(word); //find the appropriate bucket
	if (chain[bucket]->empty()) 
	{
		return false;
	}
	else 
	{
		list<string>::iterator it = chain[bucket]->begin();
		while (it != chain[bucket]->end())
		{
			string temp = *it;
			sort(it->begin(), it->end());
			if (*it == word)
			{
				callback(temp);
			}
			*it = temp; 
			it++;
		}
		return true; //if none of the nodes are the word return false
	}

}

/*void hashTable::findCollisionNumber()
{
		
	int biggestNumber = 0;
	//cout << biggestNumber << endl;
	int bucket = 0;
	for (; bucket < 50000; bucket++)
	{
		//cout << "bucket: " << bucket << endl;
		int tempBiggest = 0;
		list<string>::iterator it = chain[bucket]->begin();
		while (it != chain[bucket]->end())
		{
			tempBiggest++;
			it++;
		}
		if (tempBiggest >= biggestNumber)
			biggestNumber = tempBiggest;
	}
	cout << biggestNumber << endl;
	cout << bucket << endl;
	//return true;
}*/



  // This class does the real work of the implementation.


class DictionaryImpl
{
  public:
    DictionaryImpl() 
	{
		m_words = new hashTable;
	}
    ~DictionaryImpl(){}
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
  private:
    hashTable* m_words;
};



void DictionaryImpl::insert(string word)
{
	m_words->insert(word);
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
	//cout << letters << endl;
	if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

	m_words->search(letters, callback);
	/*
	//cout << letters << endl;
    string permutation = letters;
    do
    {   
		if (m_words->search(permutation) == true)
		{
			callback(permutation);
		}
        generateNextPermutation(permutation);
    } while (permutation != letters);*/
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
} 

  // Each successive call to this function generates the next permutation of the
  // characters in the parameter.  For example,
  //    string s = "eel";
  //    generateNextPermutation(s);  // now s == "ele"
  //    generateNextPermutation(s);  // now s == "lee"
  //    generateNextPermutation(s);  // now s == "eel"
  // You don't have to understand this function's implementation.
void generateNextPermutation(string& permutation)
{
    string::iterator last = permutation.end() - 1;
    string::iterator p;

    for (p = last; p != permutation.begin()  &&  *p <= *(p-1); p--)
        ;
    if (p != permutation.begin())
    {
        string::iterator q;
        for (q = p+1; q <= last  &&  *q > *(p-1); q++)
            ;
        swap(*(p-1), *(q-1));
    }
    for ( ; p < last; p++, last--)
        swap(*p, *last);
}

//******************** Dictionary functions ********************************

// These functions simply delegate to DictionaryImpl's functions.
// You probably don't want to change any of this code

Dictionary::Dictionary()
{
    m_impl = new DictionaryImpl;
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
