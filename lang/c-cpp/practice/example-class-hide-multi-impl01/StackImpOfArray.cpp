// : practice-05-14/StackImpOfArray.cpp

#include "StackOfInt.h"
#include <cassert>

const int stackSize = 100;
struct StackOfInt::StackImp {
	int data[stackSize];
	int top;
public:
	void initialize();
	void cleanup();
	void push(int i);
	int peek();
	int pop();
};

void StackOfInt::StackImp::initialize(){
	top = 0;
}

void StackOfInt::StackImp::cleanup() {
	top = 0;
}

void StackOfInt::StackImp::push(int i) {
	assert(top < stackSize);
	data[top++] = i;
}

int StackOfInt::StackImp::peek() {
	assert(top > 0);
	return data[top - 1];
}

int StackOfInt::StackImp::pop() {
	assert(top > 0);
	top--;
	return data[top];
}

void StackOfInt::initialize() {
	si = new StackImp;
	si->initialize();
}

void StackOfInt::cleanup() {
	si->cleanup();
}

void StackOfInt::push(int i) {
	si->push(i);
}

int StackOfInt::peek() {
	return si->peek();
}

int StackOfInt::pop() {
	return si->pop();
}
