//:practice-06-05/main.cpp

#include <iostream>
using namespace std;

int main() {
	int i, n = 10;
	for(i = 0; i < n; i++) {
		cout << "first for:" << i << endl;
	}
	for(int i = 0; i < n; i++) {
		cout << "second for:" << i << endl;
	}
	return 0;
}
