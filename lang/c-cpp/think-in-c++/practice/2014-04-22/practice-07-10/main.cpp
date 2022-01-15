// : practice-05-09/main.cpp

#include "Stash.h"
#include <iostream>
#include <string>
using namespace std;

class Hen{
	string name;
public:
	Hen( string name_):name(name_){}
	void print() {
		cout << "Hen.name:" << name << endl;
	}
	string getName() {
		return name;
	}
};

int main() {
	Stash s;
	Hen h1("h1"), h2("h2"), h3("h3"), h4("h4");
	s.initialize( sizeof(Hen));
	cout << "Stash.add( h1) index:" <<s.add(static_cast<void *>(&h1)) << endl;
	cout << "Stash.add( h2) index:" <<s.add(static_cast<void *>(&h2)) << endl;
	cout << "Stash.add( h3) index:" <<s.add(static_cast<void *>(&h3)) << endl;
	cout << "Stash.add( h4) index:" <<s.add(static_cast<void *>(&h4)) << endl;
	for(int i = 0; i < s.count(); i++) {
		Hen *h =  reinterpret_cast<Hen *>(s.fetch(i));
		cout << "Stash.fetch(" << i << ")=" << h->getName() << endl;
		h->print();
	}
	s.cleanup();
}
