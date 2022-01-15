#include <iostream>
#include <string>
using namespace std;

int main() 
{
	//char *xing = "*****";
	//char xing[] = "*****";
	string xing = "*****";
	int i,j;
	for(i=0;i<5;i++)
	{
		for(j=0;j<i;j++)
		{
			cout <<' ';
		}
		cout <<xing <<endl;
	}
	return 0;
}
