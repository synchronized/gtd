#include <iostream>
#include <map>
using namespace std;

typedef int(*Func)(int);

int func1(int i) {
	cout << "func1(" << i << ")" << endl;
    return 0;
}

int main() {
	Func a = func1;
	a(10);
	return 0;
}
