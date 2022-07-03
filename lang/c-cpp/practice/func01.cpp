#include <iostream>
using namespace std;

int f (int);

int f (int x) {
	int y;
	if (x >= 10) y = 3*x-11;
	else if (x >= 1) y = 2*x-1;
	else y = x;
	return y;
}

int main() {
	int x;
	cin >>x;
	cout <<"input number:" <<x <<endl;

	cout <<"result:" <<f(x) <<endl;
	return 0;
}
