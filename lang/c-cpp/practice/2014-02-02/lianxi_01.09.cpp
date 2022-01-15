#include <iostream>
using namespace std;

int add( int x, int y);
int main()
{
	int a,b;
	cin >>a >>b;
	cout << "a=" << a;
	cout << ", b=" << b;
	cout << endl;

	int c = add( a, b);
	cout << "a+b=" << c << endl;
	return 0;
}

int add( int x, int y)
{
	int z = x + y;
	return z;
}
