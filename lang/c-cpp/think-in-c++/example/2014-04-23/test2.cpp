//test.cpp

#include <iostream>
using namespace std;

class X{};

X f() {return X();}

void g1(X&) {}
void g2(const X&) {}


int main() {
	int j(10);
	cout << "int j(10):" << j << endl;
	int i();
	cout << "int i():" << i << endl;
	//g1(f()); //error
	g2(f());
	return 0;
}
