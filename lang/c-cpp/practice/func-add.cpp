#include <iostream>
using namespace std;

int add(int, int);

int add(int x, int y) {
	return x + y;
}

int main() {
	int a,b;
    cout << "read var a:";
    cin >>a;
    cout << "read var b:";
    cin >>b;

	cout << "a=" << a << ", b=" << b << endl;

	int c = add( a, b);
	cout << "a+b=" << c << endl;
	return 0;
}
