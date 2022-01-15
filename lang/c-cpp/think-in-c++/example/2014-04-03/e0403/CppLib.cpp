// e0403: CppLib.cpp
//  C-like library converted to c++
//  Declare structure and functions:

#include "Cpplib.h"
#include <iostream>
#include <cassert>
using namespace std;
// Quantity of element to add
// when increasing storage:
const int increase = 100;


void Stash::initialize( int sz) {
	this->size = sz;
	this->quantity = 0;
	this->next = 0;
	this->storage = 0;
}

void Stash::cleanup() {
	if( this->storage != 0) {
		cout << "free storage" <<endl;
		delete [](this->storage);
	}
}

int Stash::add( const void* element) {
	if( this->next >= this->quantity) {
		this->inflate( increase);
	}
	// Copy element to storage
	// starting at next empty space:
	int elementStartIndex = this->next * this->size;
	unsigned char * ep = (unsigned char *)element;
	for( int i = 0; i < this->size; i++) {
		this->storage[elementStartIndex + i] = ep[i];
	}
	this->next++;
	return(this->next -1); // Index number
}

void* Stash::fetch( int index) {
	// Check index boundaries:
	assert( index >= 0);
	if( index >= this->next) {
		return 0; // To indicate the end
	}
	// Produce pointer to desired element:
	return this->storage + index * this->size;
}

int Stash::count() {
	return this->next; // Number of elements in CStash
}

void Stash::inflate( int inerease) {
	assert( increase > 0);
	int newQuantity = this->quantity + inerease;
	int newBytes = newQuantity * this->size;
	int oldBytes = this->quantity * this->size;
	unsigned char* b = new unsigned char[newBytes];
	// Copy old to new
	for( int i = 0; i < oldBytes; i++) {
		b[i] = this->storage[i];
	}
	delete [](this->storage); // Old storage
	this->storage = b;
	this->quantity = newQuantity;
}
