//: practice-05-03/main.cpp

#include <iostream>
using namespace std;

class MyClass{
	public:
		MyClass() {
			i = 10;
		}
	private:
		int i;
	protected:
		friend void mcFriend( MyClass & mc);
};

void mcFriend( MyClass & mc) {
	cout << "mcFriend print mc.i:" << mc.i << endl;
}

int main() {
	MyClass mc;
	mcFriend( mc);
	return 0;
}
