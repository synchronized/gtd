// : practice-05-09/Stash.h

#ifndef STASH_H
#define STASH_H
#include "Mem.h"

class Stash{
	int size;	// Size of each element space
	int quantity;	// Number of storage spaces
	int next;	// Next empty space
	// Dynamically allocated array of bytes:
	unsigned char* storage;
	Mem mem;
	void inflate(int increase);
public:
	void initialize(int size);
	void cleanup();
	int add(void * element);
	void * fetch(int index);
	int count();
};

#endif // STASH_H ///:~
