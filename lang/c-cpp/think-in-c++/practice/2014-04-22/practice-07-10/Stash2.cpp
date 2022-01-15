// : practice-05-09/Stash.cpp

#include "Stash.h"
#include <cassert>
#include <iostream>

const int increase = 100;

void Stash::inflate(int increase) {
	assert( increase > 0);
	int newQuantity = quantity + increase;
	int newBytes = newQuantity * size;
	storage = static_cast<unsigned char*>(mem.pointer(newBytes));
	quantity = newQuantity;
}

void Stash::initialize(int sz) {
	size = sz;
	quantity = 0;
	next = 0;
	storage = 0;
}

void Stash::cleanup() {
	delete [] storage;
	quantity = 0;
	next = 0;
	storage = 0;
	std::cout << "delete [] storage" << std::endl;
	std::cout << "storage addr:" << reinterpret_cast<int>(storage) << std::endl;
}

int Stash::add(void * element) {
	if( next >= quantity) {
		inflate( increase);
	}
	unsigned char * b = reinterpret_cast<unsigned char *>(element);
	int startIndex = next * size;
	for( int i = 0; i < size; i++) {
		storage[startIndex + i] = b[i];
	}
	next++;
	return (next - 1);
}

void * Stash::fetch(int index) {
	assert( index >= 0);
	if( index >= next) {
		return 0;
	}
	return (storage + index * size);
}

int Stash::count() {
	return next;
}
