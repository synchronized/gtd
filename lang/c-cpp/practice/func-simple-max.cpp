#include <iostream>
using namespace std;

int max(int a, int b);

int max(int a, int b) {
	if(a>b) return a;
	else return b;
}

int main() {
	int a, b, c;
	cin >>a >>b;
	int (*p)(int,int);
	p = max;

	c = p(a, b);
	cout <<"max=" <<c <<endl;
	return 0;
}
