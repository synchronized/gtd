#include <iostream>
using namespace std;

void swap(int &a, int &b);
void swap(int *a, int *b);
void print(int a, int b);

void swap(int &a, int &b) {
	int m;
	m = a;
	a = b;
	b = m;
}

void swap(int *a, int *b) {
	int m;
	m = *a;
	*a = *b;
	*b = m;
}

void print(int a, int b) {
	cout <<"a=" <<a <<"b=" <<b <<endl;
}

int main() {
	int a,b;
	cin >>a >>b;
	print(a, b);

	swap(a, b);
	print(a, b);
	return 0;
}
