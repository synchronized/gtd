#include <iostream>
using namespace std;

template <typename T>
T max( T a, T b, T c) {
	T m;
	if (a > b) m = a;
	else m = b;
	if (c > m) m = c;
	return m;
}

int main() {
	int a,b,c;
	cin >>a >>b >>c;
	c=max(a, b, c);
	cout <<"max number:" <<c <<endl;
	return 0;
}
