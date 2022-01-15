#include "printBinary.h"

int main() {
	float f = 12.32323;
	unsigned char * p = reinterpret_cast<unsigned char *>(&f);
	for( int i = 0; i < sizeof(f); i++) {
		printBinary( *(p+i));
	}
	return 0;
}
