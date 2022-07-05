#include <iostream>

using namespace std;

void printBinary(const unsigned char val) {
	for( int i = 7; i >= 0; i--) {
		if( val & (1 << i)) {
			cout << "1";
		}
		else {
			cout << "0";
		}
	}
}


int main() {
	float f = 12.32323;
	unsigned char * p = reinterpret_cast<unsigned char *>(&f);
	for( int i = 0; i < sizeof(f); i++) {
		printBinary( *(p+i));
	}
	return 0;
}
