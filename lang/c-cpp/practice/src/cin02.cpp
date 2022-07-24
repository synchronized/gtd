#include <iostream>
#include <iomanip>
#include <cstdio>
using namespace std;

int main() {
	char c1,c2;
	c1 = getchar();
	c2 = getchar();
	cout <<"c1 by putchar:";
	putchar( c1);
	cout <<endl;
	cout <<"c2 by putchar:";
	putchar( c2);
	cout <<endl;

	cout <<"c1 by cout:" <<setw(10) <<c1 <<"-" <<endl;
	cout <<"c2 by cout:" <<setw(10) <<c2 <<"-" <<endl;
	return 0;
}
