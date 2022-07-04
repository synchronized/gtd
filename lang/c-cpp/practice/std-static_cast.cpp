#include <iostream>
using namespace std;

class MyClass{
	int i;
};

int main() {
	MyClass mc;
    //error: invalid ‘static_cast’ from type ‘MyClass’ to type ‘int’
	//cout << "object to int:" << static_cast<int>(mc) << endl;
	return 0;
}
