#include <iostream>
using namespace std;

void exchange( int *p1, int *p2, int *p3);
void swap( int *p1, int *p2);


void exchange( int *p1, int *p2, int *p3) {
	if( *p1 < *p2) swap( p1, p2);
	if( *p1 < *p3) swap( p1, p3);
	if( *p2 < *p3) swap( p2, p3);
}

void swap( int *p1, int *p2) {
	int m;
	m = *p1;
	*p1 = *p2;
	*p2 = m;
}

int main() {
	int a,b,c, *p1, *p2, *p3;
	cin >>a >>b >>c;
	p1=&a; p2=&b; p3=&c;
	exchange( p1, p2, p3);
	cout <<a <<" " <<b <<" " <<c <<endl;
	return 0;
}
