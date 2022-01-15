#include <iostream>
using namespace std;

void swap(int *p1, int *p2);
int main()
{
	int *pointer_1, *pointer_2;
	int a,b;
	cin >>a >>b;
	pointer_1 = &a;
	pointer_2 = &b;
	if(a<b) swap(pointer_1, pointer_2);
	cout <<"max=" <<a <<"," <<"min=" <<b <<endl;
	return 0;
}
void swap(int *p1, int *p2)
{
	int m;
	m = *p1;
	*p1 = *p2;
	*p2 = m;
}
