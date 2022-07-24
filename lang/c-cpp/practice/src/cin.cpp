#include <iostream>
using namespace std;

int min(int, int, int);

int min(int x, int y, int z) {
	int m;
	if( x < y) m = x;
	else m = y;
	if( z < m) m = z;
	return m;
}

int main() {
	int a,b,c;
    cout << "read var a:";
	cin >>a;
    cout << "read var b:";
    cin >>b;
    cout << "read var c:";
    cin >>c;

	cout << "a=" << a;
	cout << ",b=" << b;
	cout << ",c=" << c;
	cout << endl;

	c = min(a,b,c);
	cout << c << endl;
	return 0;
}
