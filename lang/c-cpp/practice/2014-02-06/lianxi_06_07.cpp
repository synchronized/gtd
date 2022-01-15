#include <iostream>
using namespace std;

int main()
{
	char str[] = "I love China";
	char *p1, *p2, str2[20];
	int i;
	p1 = str;
	p2 = str2;
	for(; *p1!='\0'; p1++,p2++)
	{
		*p2 = *p1;
	}
	cout <<str <<endl;
	cout <<str2 <<endl;
	return 0;
}
