#include <iostream>
using namespace std;

class MyClass {
	public:
		MyClass(int i_):i(i_){}
		int i;
};

MyClass * func() {
	MyClass myclass = 10;
	return &myclass;
}

int main() {
	MyClass* myclass = func(); 
	cout << "myclass.i:" << myclass->i <<endl;
	return 0;
}
