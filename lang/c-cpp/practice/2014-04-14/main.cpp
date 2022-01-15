#include <iostream>
using namespace std;

class MyClass{
	int i;
};

int main() {
	MyClass mc;
	cout << "object to int:" << static_cast<int>(mc) << endl;
	return 0;
}
