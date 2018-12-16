
#ifndef Sequenceh

#define Sequenceh
#include <iostream>
#include <string>
using namespace std;
using ItemType = std::string;
class Sequence
{
public:
	Sequence();
	~Sequence();
	Sequence(const Sequence& old);
	Sequence& operator=(const Sequence& old);
	bool empty() const;
	int size() const;
	bool insert(int pos, const ItemType& value);
	int insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);
	void dump()const;
private:
	struct node
	{
		node(ItemType value);
		ItemType data;
		node* next;
		node* prev;
	};
	node* m_head;
	int m_size;
};

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);
int subsequence(const Sequence& seq1, const Sequence& seq2);


#endif // !Sequenceh
