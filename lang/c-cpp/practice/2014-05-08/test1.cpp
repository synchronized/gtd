#include <iostream>
#include <string>
using namespace std;

int main() {
	string a;
	string* b = new string("1234");
	a.assign(*b);
	delete b;
	cout << "a:" << a << endl;
	cout << "b:" << *b << endl;
	return 0;
}
