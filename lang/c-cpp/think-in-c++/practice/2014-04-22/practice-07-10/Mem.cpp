//practice-07-10/Mem.cpp

#include "Mem.h"
#include <cstring>
using namespace std;

Mem::Mem() {
	mem = 0;
	size = 0;
}

Mem::Mem( int sz) {
	mem = 0;
	size = 0;
	ensureMinSize( sz);
}

Mem::~Mem(){
	delete [] mem;
}

byte* Mem::pointer() {
	return mem;
}

byte* Mem::pointer( int minSize) {
	ensureMinSize( minSize);
	return mem;
}

void Mem::ensureMinSize(int minSize) {
	if( size < minSize) {
		byte* b = new byte[minSize];
		memset( b + size, 0, minSize - size);
		memcpy( b, mem, size);
		delete [] mem;
		mem = b;
		size = minSize;
	}
}
