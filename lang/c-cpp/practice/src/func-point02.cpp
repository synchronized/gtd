#include <iostream>
using namespace std;

int func1(double);
int main() {
	int (*fp)(double);
	fp = func1;
	(*fp)( 1.1);
	return 0;
}

int func1(double d) {
	cout <<"func1( " <<d <<")" <<endl;
	return 1;
}
