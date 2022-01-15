// : practice-05-11/Stach.h
// Nested structs via linked list

#ifndef STACK2_H
#define STACK2_H

class Stack{
	struct Link {
		void* data;
		Link* next;
		void initialize(void* dat, Link* nxt);
	}* head;
public:
	void initialize();
	void cleanup();
	void push(void* dat);
	void* peek();
	void* pop();
};

#endif  //STACK2_H ///:~
