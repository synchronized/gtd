//test3.cpp

#include <iostream>
using namespace std;

class Bunch{
	enum { size = 1000, a = 1000, b};
	int i[size];
public:
	void print() {
		cout << "Bunch.b:" << b << endl;
	}
};

int main() {
	Bunch b;
	b.print();
	cout << " sizeof(Bunch) = " << sizeof(Bunch)
		<< ", sizeof(i[1000]) = "
		<< sizeof(int[1000]) << endl;
	return 0;
}
