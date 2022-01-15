// : practice-05-14/StackOfInt.h

#ifndef STACKOFINT_H
#define STACKOFINT_H

class StackOfInt{
public:
	struct StackImp;
	StackImp* si;
public:
	void initialize();
	void cleanup();
	void push(int i);
	int peek();
	int pop();
};

#endif //STACKOFINT_H
