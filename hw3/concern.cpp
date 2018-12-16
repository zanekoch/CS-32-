/*#include <iostream>
#include <string>
using namespace std;
*/
/*Your declarations and implementations would go here*/
//concern
class Concern //must be pure virtual
{
public:	//constructor with one string parameter
	Concern(string name)
	{
		m_person = name;
	}
	//getters
	string person() const
	{
		return m_person;
	}
	string virtual description() const = 0
	{}
	bool virtual possibleFelony() const
	{
		return false;
	}
	//desctructor
	virtual ~Concern()
	{
		//why is it that the base class's desctructor must be virtual for the derived class desctructors to be called?
	}
private:
	string m_person;
	bool m_felonious;
};
//ethicsMatter
class EthicsMatter : public Concern
{
public:
	EthicsMatter(string name) 
		: Concern(name) //sets person
	{
		
	}
	string virtual description() const
	{
		return ("An ethics matter");
	}
	~EthicsMatter()
	{
		cout << "Destroying " << this->person() << "'s ethics matter" << endl;
	}
private:
};
//hushpayment
class HushPayment : public Concern
{
public:
	HushPayment(string name, int amount) 
		:Concern(name) //sets person
	{
		paymentAmount = amount; //sets payment amount
	}
	string virtual description() const
	{
		return("A $" + to_string(paymentAmount) + " payment");
	}
	~HushPayment()
	{
		cout << "Destroying " << this->person() << "'s hush payment" << endl;
	}
private:
	int paymentAmount;
};
//investigation
class Investigation : public Concern
{
public:
	Investigation(string name)
		: Concern(name) //sets person
	{
		
	}
	string virtual description() const
	{
		return("An investigation");
	}
	bool virtual possibleFelony() const
	{
		return true;
	}
	~Investigation()
	{
		cout << "Destroying " << this->person() << "'s investigation" << endl;
	}
private:
};

/*
void display(const Concern* c)
{
	cout << c->description() << " involving " << c->person();
	if (c->possibleFelony())
		cout << ", possibly felonious";
	cout << endl;
}

int main()
{
	Concern* concerns[4];
	concerns[0] = new EthicsMatter("Pruitt");
	// Hush payments have a person's name and an amount of money (an int).
	concerns[1] = new HushPayment("Clifford", 130000);
	concerns[2] = new HushPayment("McDougal", 150000);
	concerns[3] = new Investigation("Mueller");
	
	cout << "Here are the concerns:" << endl;
	for (int k = 0; k < 4; k++)
		display(concerns[k]);

	// Clean up the concerns before exiting
	cout << "Cleaning up:" << endl;
	for (int k = 0; k < 4; k++)
		delete concerns[k];
	//==============================
	/*cout << concerns[0]->person() << " " << concerns[0]->description() << endl;
	cout << concerns[1]->person() << " " << concerns[1]->description() << endl;
	cout << concerns[2]->person() << " " << concerns[2]->description() << endl;
	cout << concerns[3]->person() << " " << concerns[3]->description() << endl;*/
	
}*/