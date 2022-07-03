#include <iostream>
using namespace std;

int main() {
	int a=12,n;
	a+=a; //24;
	cout <<"a+=a:" <<a <<endl;

	a-=3; //21
	cout <<"a-=3:" <<a <<endl;

	a*=2+3; //42
	cout <<"a*=2+3:" <<a <<endl;

	a/=a+a; //1
	cout <<"a/=a+a:" <<a <<endl;

	n = 5;
	a%=(n%=2); //0
	cout <<"a%=(n%=2):" <<a <<endl;

	a+=a-=a*=a; //0
	cout <<"a+=a-=a*=a:" <<a <<endl;

	return 0;
}
