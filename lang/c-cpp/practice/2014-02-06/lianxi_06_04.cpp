#include <iostream>
using namespace std;

int main()
{
	int a[3];
	int i,*p;
	p = a;
	for(i=0; i<3; i++)
	{
		cin >>*(a+i);
	}
	cout <<endl;
	for(p=a; p<(a+3); p++)
	{
		cout <<*p;
		cout <<" ";
	}
	cout <<endl;
	for(i=0; i<3; i++)
	{
		cout <<*(a+i);
		cout <<" ";
	}
	cout <<endl;
	return 0;
}
