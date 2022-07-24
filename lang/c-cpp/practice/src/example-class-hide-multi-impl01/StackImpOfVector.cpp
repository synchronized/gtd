// : practice-05-14/StackImpOfArray.cpp

#include "StackOfInt.h"
#include <cassert>
#include <vector>

const int stackAddition = 100;
struct StackOfInt::StackImp {
	std::vector<int> data;
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
	data.clear();
	top = 0;
}

void StackOfInt::StackImp::push(int i) {
	//if(data.size() >= top) {
		//data.resize(data.size() + stackAddition);
	//}
	data.push_back(i);
	top++;
}

int StackOfInt::StackImp::peek() {
	return *(data.end()-1);
}

int StackOfInt::StackImp::pop() {
	int r = *(data.end()-1);
	data.pop_back();
	return r;
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
