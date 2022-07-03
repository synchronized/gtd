#include <iostream>
using namespace std;

int main() {
	int a=3,b=4,c=5;
	bool r;

	r =( a+b>c && b==c); //0
	cout <<"a+b>c && b==c:" <<r <<endl;

	r = (a||b+c&&b-c); //1
	cout <<"a||b+c&&b-c:" <<r <<endl;

	r = (!(a>b)&&!c||1); //1
	cout <<"!(a>b)&&!c||1:" <<r <<endl;

	int x,y;
	r = (!(x=a)&&(y=b)&&0); //0
	cout <<"!(x=a)&&(y=b)&&0:" <<r <<endl;

	r = (!(a+b)+c-1&&b+c/2); //1
	cout <<"!(a+b)+c-1&&b+c/2:" <<r <<endl;
	return 0;
}
