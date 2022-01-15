#

#include "Handle.h"
#include <iostream>
using namespace std;

int main() {
	Handle h1, h2;
	h1.change(10);
	h2.change(20);
	cout << "h1.read():" << h1.read() << endl;
	cout << "h2.read():" << h2.read() << endl;
	return 0;
}
