#include <iostream>
using namespace std;

void pout (int i);
int main()
{
	int i;
	cin >>i;
	pout(i);
	cout <<endl;
	return 0;
}

void pout (int i)
{
	char m;
	if (i>9) {
		m = i%10+48;
		cout <<m;
		pout (i/10);
	}
	else
	{
		m = i+48;
		cout <<m;
	}
}
