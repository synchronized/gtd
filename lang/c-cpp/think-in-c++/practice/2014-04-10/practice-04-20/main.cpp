//:main.cpp

#include <iostream>
using namespace std;

struct Stru1{
	int a[10];
	long b;
	char c[10];
	int f() {
	}
};

int main() {
	cout << "Stru1.length:" <<sizeof(Stru1) << endl;
	// output 56 = 40+10+4+2(?)
	return 0;
}
