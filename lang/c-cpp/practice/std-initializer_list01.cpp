//:practice-06-07/main.cpp

#include <iostream>
using namespace std;

int main() {
	int i1[10] = {0};
	for(int i = 0; i < sizeof i1 / sizeof *i1; i++) {
		cout << "i1[" << i << "]:" << i1[i] << endl;
	}
	int i2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	for(int i = 0; i < sizeof i2 / sizeof *i2; i++) {
		cout << "i2[" << i << "]:" << i2[i] << endl;
	}
	return 0;
}
