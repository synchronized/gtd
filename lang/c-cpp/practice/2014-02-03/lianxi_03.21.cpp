#include <iostream>
using namespace std;

int main() 
{
	int i,j,m,n=10;
	i=j=1;
	for(m=1;m<n;m++)
	{
		j=i+j;
		i=j-i;
		cout <<"number:" <<n <<",item:" <<j <<'/' <<i <<endl;
	}
	return 0;
}
