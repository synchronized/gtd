// : practice-05-11/main.cpp

#include "Stack.h"
#include <iostream>
#include <string>
using namespace std;

class Hen{
	string name;
public:
	Hen(string name_);
	void print();
};

Hen::Hen(string name_) {
	name = name_;
}

void Hen::print() {
	cout << "Hen.name:" << name << endl;
}

int main() {
	Stack s;
	Hen h1("h1"), h2("h2"), h3("h3"), h4("h4");
	s.initialize();
	s.push(reinterpret_cast<void*>(&h1));
	s.push(reinterpret_cast<void*>(&h2));
	s.push(reinterpret_cast<void*>(&h3));
	s.push(reinterpret_cast<void*>(&h4));
	while( void* dt = s.pop()) {
		reinterpret_cast<Hen*>(dt)->print();
	}
	s.cleanup();
	return 0;
}
