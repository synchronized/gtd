// : practice-05-14/main.cpp

#include "StackOfInt.h"
//#include "StackImpOfArray.cpp"
#include <iostream>
#include <vector>
using namespace std;



int main() {
	StackOfInt soi;
	soi.initialize();
	int i, n=50;

	for( i = 0; i < n; i++) {
		cout << "StackOfInt.push():" << i << endl;
		soi.push(i);
	}
	for( i = 0; i < n; i++) {
		cout << "StackOfInt.pop():" << soi.pop() << endl;
	}
	return 0;
}
