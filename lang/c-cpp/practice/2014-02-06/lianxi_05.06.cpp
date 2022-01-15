#include <iostream>
using namespace std;

int main() 
{
	int array[10] = {1,0,0,0,0,0,0,0,0,0}, 
	    array2[10] = {1,0,0,0,0,0,0,0,0,0}; 
	int i, j;
	for(i=1;i<=10;i++) 
	{
		for(j=0;j<i;j++)
		{
			cout <<array[j] <<'\t';
		}

		for(j=0;j<i;j++)
		{
			array[j+1] = array2[j]+array2[j+1];
			//array2[j+1] = array[j+1];
		}
		cout <<endl;
		//array[i] = array2[i-1]+array2[i];

		for(j=0;j<i;j++)
		{
			array2[j+1] = array[j+1];
		}
	}
	return 0;
}
			
