// : practice-05-13/main.cpp

#include "Handle.h"
#include "iostream"
using namespace std;

int main() {
	Handle h;
	h.initialize();
	h.change( 10);
	cout << "Handle.read():" << h.read() << endl;
	return 0;
}
