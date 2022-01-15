#include <iostream>
using namespace std;

long p (long n);
int main() 
{
	long i,r,n = 20;
	for (i=0; i<n; i++) 
	{
		r += p(i+1);
	}
	cout <<"result:" <<r <<endl;
	return 0;
}

long p (long n)
{
	long i,r=1;
	for(i=0; i<n; i++)
	{
		r *= i+1;
	}
	cout <<n <<"p:" <<r <<endl;
	return r;
}
