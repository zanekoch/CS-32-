/*#include <iostream>
#include <string>
#include <vector>

using namespace std;

class File
{
public:
	File(string nm) : m_name(nm) {}
	virtual ~File() {}
	string name() const { return m_name; }
	virtual bool add(File* f) = 0;
	virtual const vector<File*>* files() const = 0;
private:
	string m_name;
};

class PlainFile : public File
{
public:
	PlainFile(string nm) : File(nm) {}
	virtual bool add(File* f) { return false; }
	virtual const vector<File*>* files() const { return nullptr; }
};

class Directory : public File
{
public:
	Directory(string nm) : File(nm) {}
	virtual ~Directory();
	virtual bool add(File* f) { m_files.push_back(f); return true; }
	virtual const vector<File*>* files() const { return &m_files; }
private:
	vector<File*> m_files;
};

Directory::~Directory()
{
	for (int k = 0; k < m_files.size(); k++)
		delete m_files[k];
}
*/
void listAll(string path, const File* f)  // two-parameter overload
{
	if (f->files() == nullptr) //if is a file just print it and move on
	{
		cout << path + f->name() << endl;
		return;
	}
	cout << path + f->name() << endl;
	int w = f->files()->size();
	for (int i = 0; i < w; i++)
	{
		listAll(path + f->name() + '/', (*f->files())[i]); //if its a directory add its name to the path and recurisvely call with the first element of the 
	}
}
/*
void listAll(const File* f)  // one-parameter overload
{
	if (f != nullptr)
		listAll("", f);
}

/*
/ My Pictures
/ My Pictures / Fun
/ My Pictures / Fun / party.jpg
/ My Pictures / Fun / beach.jpg
/ My Pictures / Fun / skitrip.jpg
/ My Pictures / me.jpg
/ My Pictures / Miscellaneous
/ My Pictures / Work
/ My Pictures / Work / seaslab.jpg


int main()
{
	Directory* d1 = new Directory("Fun");
	d1->add(new PlainFile("party.jpg"));
	d1->add(new PlainFile("beach.jpg"));
	d1->add(new PlainFile("skitrip.jpg"));
	Directory* d2 = new Directory("Work");
	d2->add(new PlainFile("seaslab.jpg"));
	Directory* d3 = new Directory("My Pictures");
	d3->add(d1);
	d3->add(new PlainFile("me.jpg"));
	d3->add(new Directory("Miscellaneous"));
	d3->add(d2);
	listAll(d3);
	delete d3;

	/*Directory* testDirect = new Directory("test");
	Directory* innerDirect = new Directory("inner");
	innerDirect->add(new PlainFile("whattup.jpg"));
	innerDirect->add(new PlainFile("whattup2.jpg"));
	testDirect->add(innerDirect);
	testDirect->add(new PlainFile("hi.jpg"));
	testDirect->add(new PlainFile("Im.jpg"));
	testDirect->add(new PlainFile("zane.jpg"));
	listAll(testDirect);
	delete testDirect;

	//output should be
	test/inner/whattup.jpg
	test/inner/whattup2.jpg
	/test/hi.jpg
	/test/im.jpg
	test/zane.jpg
	
}

//You will write this code.

	//vector<File*>::const_iterator outer = f->files()->begin();
	vector<File*>::const_iterator inner = f->files()->begin();
	size_t outer = 0;
	for (outer; outer< f->files()->size();outer++)
	{
		vector<File*>::const_iterator inner = f->files()->begin()+outer;
		for(inner; ;inner++)
		{
			
		}
	}




if ((*f->files())[0]->files()->size() > 0)
		{
			cout << (*f->files())[0]->name() + '/';
			for (size_t i = 0; i < (*f->files())[0]->files()->size(); i++) //if file has a size bigger than 1 it means its a directory so iterate over all the elements in the directory
			{
				cout << (*(*f->files())[0]->files())[i]->name() + '/';
				
			}
		}
		cout << endl;
		listAll(path, f + 1); //recursively call again with the next element 
		*/
	