#include <iostream>
using namespace std;

int main()
{
	int a;
	a = 3.5*3+2*7-'a'; //115.5
	cout <<"a = 3.5*3+2*7-'a'=" <<a <<endl;

	a = 26/3+34%3+2.5; //21.5
	cout <<"26/3+34%3+2.5=" <<a <<endl;

	a = 45/2+(int)3.1415926; //25
	cout <<"45/2+(int)3.1415926=" <<a <<endl;

	int b,c;
	a=3;
	a=b=(c=a+=6); //9
	cout <<"a=b=(c=a+=6)" <<a <<endl;

	a=(a=3*5,a=b=3*2);//6
	cout <<"a=3*5,a=b=3*2 =" <<a <<endl;

	a=3;
	a=(int)(a+6.5)%2+(a=b=5);//6
	cout <<"a=(int)(a+6.5)%2+(a=b=5)=" <<a <<endl;

	int x=2.5,y=4.7;
	a=7;
	a=x+a%3*(int)(x+y)%2/4; //2.75
	cout <<"a=x+a%3*(int)(x+y)%2/4=" <<a <<endl;

	a=2,b=3,x=3.5,y=2.5; //3.5
	a = (float)(a+b)/2+(int)x%(int)y;
	cout <<"(float)(a+b)/2+(int)x%(int)y=" <<a <<endl;
	return 0;
}
