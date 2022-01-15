//:practice-05-01/main.cpp

#include <iostream>
using namespace std;

class MyClass{
	public:
		MyClass() {
			i=1;
			j=2;
			k=3;
		}
		int i;
	protected:
		int j;
	private:
		int k;
};

int main() {
	MyClass mc;
	cout << "mc.i:" << mc.i << endl;
	cout << "mc.j:" << mc.j << endl;
	cout << "mc.k:" << mc.k << endl;
	return 0;
}

