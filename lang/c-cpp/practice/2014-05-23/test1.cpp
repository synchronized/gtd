#include <iostream>

using namespace std;

class A{
public:
	A() {
		cout << "A::A()" << endl;
	}
};

class B:public A{
public:
	B() {
		i = 0;
		cout << "B::B()" << endl;
	}
	const B& operator=( const B& b) {
		cout << "operator=( const B& b);" << endl;
		i = b.i;
		return *this;
	}
	int i;
};

int main() {
	B b1, b2;
	b2.i = 10;
	b1 = b2;
	
	B b3 = b1;
	cout << "b1.i:" << b1.i << endl;
	return 0;
}
