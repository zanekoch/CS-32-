#include "Sequence.h"

Sequence::node::node(ItemType value)//node constructor
{
	data = value;
	next = nullptr;
	prev = nullptr;
}
Sequence::Sequence()//constructor
{
	m_head = nullptr;
	m_size = 0;
}
Sequence::~Sequence() //desctructor
{
	if (m_head == nullptr);
	else if (m_head->next == nullptr)
		delete m_head;
	else
	{
		node* temp = m_head->next;
		node* removeThis = m_head;
		while (temp != nullptr)
		{
			delete removeThis;
			removeThis = temp;
			temp = temp->next;
		}
		delete removeThis;
	}
}
Sequence::Sequence(const Sequence& old)//copy constructor
{
	if (this != &old)
	{
		this->m_head=nullptr;
		//cerr << "init head: " << m_head;
		m_size = 0;
		for (int i = 0; i < old.m_size; i++)
		{
			ItemType value;
			old.get(i, value); //get the value of the i-th node in the old LL
			this->insert(i, value);
			//cerr << "head: " << m_head;
			//cerr << "value: " << value;
		}
		this->m_size = old.m_size;
	}
}
Sequence& Sequence::operator=(const Sequence& old)//assignment operator
{
	if (this != &old)
	{
		Sequence temp(old);//call copy constructor
		this->swap(temp);
	}
	return *this;
}
bool Sequence::empty() const
{
	if (m_head == nullptr)
		return true;
	return false;
}
int Sequence::size() const //size is 0 if there are no nodes and only a head pointer, size is 1+ once there is a node
{
	return m_size;
}
bool Sequence::insert(int pos, const ItemType& value)
{
	if (pos < 0 || pos > m_size)
	{
		cerr << "pos: " << pos << "m_size: " << m_size;
		cerr << "position bad";
		return false;
	}
	else if (pos == 0 && m_head == nullptr)//case where this is the first node added
	{
		node* newnode = new node(value);
		m_head = newnode; //cerr << "pos 1 adding head: " << m_head;
		m_size++;
		//cerr << "adding node spot 1" << endl;
		return true;
	}
	else if (pos == 0 && m_head != nullptr) //case where inserting as first node but not first node inserted
	{
		node* newnode = new node(value);
		newnode->next = m_head;
		m_head->prev = newnode;
		m_head = newnode;
		m_size++;
		//cerr << "adding node spot 1., not for first time" << endl;
		return true;
	}
	else if (pos == m_size)//when inserting into end
	{
		node* newnode = new node(value);
		node* runner;
		int counter = 0;
		for (runner = m_head; runner->next != nullptr; runner = runner->next)
		{
			counter++;
		} //now the runner is pointing at the last node, the node before the one being inserted
		runner->next = newnode;
		newnode->prev = runner;
		newnode->next = nullptr;
		m_size++;
		//cerr << "adding node spot end" << endl;

		return true;
	}
	else //case where in the middle of the linked list
	{
		node* newnode = new node(value);
		node* runner;
		int counter = 0;
		for (runner = m_head; counter < pos-1; runner = runner->next)
		{
			counter++;
		}//hopefully moves the pointer runner to the node before the place its supposed to be insertednode* fastrunner = runner->next;
		newnode->prev = runner;
		newnode->next = runner->next;
		runner->next->prev = newnode;
		runner->next = newnode;
		m_size++;
		//cerr << "adding node spot middle" << endl;

		return true;
	}
	return false; //just in case
}
int Sequence::insert(const ItemType& value)
{
	ItemType val;
	int counter = 0;
	for (int i = 0; i <= m_size; i++)
	{
		this->get(i, val);
		if (val == value)
		{
			this->insert(i, value);
			return i;
		}
		else if (val > value)
		{
			this->insert(i, value);
			return i;
		}
		counter++;
	}
	if (counter-1== m_size)
	{
		this->insert(m_size, value);
		return m_size;
	}
	return -1;
}
bool Sequence::erase(int pos)
{
	if (pos > this->size()-1 || pos < 0 ||this->size()==0)//if the position is bigger than the size, if position is negative, or if there is nothing to delete return false
		return false;
	if (pos == 0 && m_size != 0) //case where deleting first item
	{
		if (m_size == 1) //when deleting only item
		{
			delete m_head;
			m_head = nullptr;
			m_size--;
			return true;
		}
		else //when deleting first item
		{
			node* temp = m_head->next;
			temp->prev = nullptr;
			delete m_head;
			m_head = temp;
			m_size--;
			return true;
		}
	}
	int counter = 0;
	node* runner = m_head;
	while (counter != pos)
	{
		runner = runner->next;
		counter++;
	}
	if (pos == m_size-1)//deleting last node
	{
		runner->prev->next = nullptr;
		delete runner;
		m_size--;
		return true;
	}
	else //deleting in the middle
	{
		node* tempNew = runner->prev;
		node* tempNew2 = runner->next;
		tempNew->next = tempNew2;
		tempNew2->prev = tempNew;
		delete runner;
		m_size--;
		return true;
	}
}
int Sequence::remove(const ItemType& value)
{
	int removed = 0;
	while (find(value) != -1)
	{
		erase(find(value));
		removed++;
	}
	return removed;
}
bool Sequence::get(int pos, ItemType& value) const
{
	if (pos > m_size-1 || pos < 0 || this->size() == 0)//if the position is bigger than the size, if position is negative, or if there is nothing to delete return false
		return false;
	node* runner=m_head;
	int counter = 0;
	while (counter!=pos)
	{
		if (runner->next == nullptr)
			return false;
		else
		{
			counter++;
			runner = runner->next;
		}
	}
	//now runner is moved
	value = runner->data;
	return true;
}
bool Sequence::set(int pos, const ItemType& value)//not super duper confident
{
	if (pos > this->size() || pos < 0 || this->size() == 0)//if the position is bigger than the size, if position is negative, or if there is nothing to delete return false
		return false;
	node* runner = m_head;
	int counter = 0;
	while (counter != pos)
	{
		if (runner->next == nullptr)
			return false;
		else
		{
			counter++;
			runner = runner->next;
		}
	}
	//now runner is moved
	runner->data=value;
	return true;
}
int Sequence::find(const ItemType& value) const //double check this
{
	int counter = 0;
	if (m_size == 0 && m_head == nullptr)//case where list is empty
		return -1;
	else if (m_head->data == value)//case where first node is value
		return 0;
	else //cases where list is not empty and first node does not have right value
	{
		node* runner = m_head;
		while (runner->data!=value)
		{
			if (runner->next == nullptr)
				return -1;
			else
			{
				counter++;
				runner = runner->next;
			}
		}
		return counter;
	}

}
void Sequence::swap(Sequence& other)
{
	using std::swap;
	swap(this->m_size, other.m_size);
	swap(this->m_head, other.m_head);
}
void Sequence::dump() const
{
	node* temp = m_head;
	while (temp != nullptr)
	{
		cerr << temp->data << ", ";
		temp = temp->next;
	}
}


//---------------------------------------------------------
//algs
//---------------------------------------------------------
int subsequence(const Sequence& seq1, const Sequence& seq2)
{
	//if seq2 is a consecutive subsequence of seq1, the function returns the earliest place in seq1 where that subsequence starts
	//If no such k exists or if seq2 is empty, the function returns -1. 
	//cerr << seq2.size();
	if (seq2.size() <= 0)
		return -1;
	//getters
	ItemType firstVal;
	ItemType secondVal;
	int numberMatching = 0;
	int numberNeeded = seq2.size();
	int i = 0;
	int w = 0;
	//cerr << seq2.size();
	while (i < seq2.size())
	{
		while (w < seq1.size())
		{
			//cout << "i: " << i << endl;
			//cout << "w: " << w << endl;
			seq2.get(i, secondVal);
			seq1.get(w, firstVal);
			//cout << "secondVal: " << secondVal << endl;
			//cout << "firstVal: " << firstVal << endl;
			if (firstVal == secondVal)//if the values match then add to number matching and check if the next values match
			{
				i++;
				w++;
				numberMatching++;
				if (numberMatching == numberNeeded)
				{
					return (w-numberNeeded);
				}
			}
			else if (firstVal!=secondVal && numberMatching != 0) //when a value matched but the next value does not
			{

				numberMatching = 0; 
				i = 0; //move i back to start of seq2

			}
			else
			{
				//gets stuck here? idk why
				w++;
			}
		}
		i++;
	}
	return -1;

}
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
	if (!result.empty())
	{
		int z = 0;
		while (z < result.size())
		{
			result.erase(z);
			z++;
		}
	}
	if (seq1.empty())
		result = seq2;
	else if (seq2.empty())
		result = seq1;
	else
	{
		int i = 0; //number of  place to insert
		int j = 0; //number of node to get value from
		ItemType value; //place to store value of node
		int biggerSize; 
		if (seq1.size() > seq2.size()) //whicheve size is bigger iterate over it
			biggerSize = seq1.size();
		else
			biggerSize = seq2.size();
		while (j < biggerSize) //iterate
		{
			if (j < seq1.size()) //while i is not bigger than the seq1 insert node of seq1 
			{
				seq1.get(j, value);
				result.insert(i, value);
				i++;
				if (j < seq2.size())//check if i is bigger than seq2 and if not insert its node after seq1's
				{
					seq2.get(j, value);
					result.insert(i, value); //insert one after the node from seq1
					i++; //since added another iterate further;
				}
				j++;
			}
			else if(j<seq2.size())//in the case where seq1 is shorter than seq2
			{
				seq2.get(j, value);
				result.insert(i, value);
				i++; 
				j++;
			}
		}
	}

}