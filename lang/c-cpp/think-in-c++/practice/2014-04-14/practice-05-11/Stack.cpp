// : practice-05-11/Stack.cpp

#include "Stack.h"
#include <iostream>

void Stack::Link::initialize(void* dat, Stack::Link* nxt){
	data = dat;
	next = nxt;
}

void Stack::initialize() {
	head = 0;
}

void Stack::cleanup() {
	Link* l;
	while( head) {
		l = head;
		head = l->next;
		l->next = 0;
		//delete l->data;
		delete l;
	}
	std::cout << "cleanup" << std::endl;
}

void Stack::push(void* data) {
	Link* l = new Link;
	l->initialize( data, head);
	head = l;
}

void* Stack::peek() {
	if( !head) {
		return 0;
	}
	return head->data;
}

void* Stack::pop() {
	if( !head) {
		return 0;
	}
	Link* i = head;
	head = i->next;
	i->next = 0;
	void* r = i->data;
	i->data = 0;
	delete i;
	return r;
}
