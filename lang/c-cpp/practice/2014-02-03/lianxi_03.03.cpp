#include <iostream>
#include <iomanip>
using namespace std;

float ctempl( float i);
int main() 
{
	float i,h;
	cin >>i;
	cout <<"input i:" <<i <<endl;
	h = ctempl( i);
	cout <<"calc h:" <<h <<endl;
	cout <<"template:" 
		<<setiosflags(ios::fixed)
		<<setprecision(2)
		<<h <<endl;
	return 0;
}

float ctempl( float i)
{
	float h;
	h = 5/(float)9*(i-32);
	return h;
}
