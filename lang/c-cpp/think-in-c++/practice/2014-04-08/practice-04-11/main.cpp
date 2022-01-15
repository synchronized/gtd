#include <iostream>
using namespace std;


void printMsg();

//#define __DEBUG__ 1


#ifdef __DEBUG__
void printMsg() {
	cout << "__DEBUG__ is def" << endl;
}
#else
void printMsg() {
	cout << "__DEBUG__ is not def" << endl;
}
#endif

int main() {
	printMsg();
	return 0;
}
