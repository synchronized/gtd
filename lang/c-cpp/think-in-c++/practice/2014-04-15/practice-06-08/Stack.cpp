//:practice-06-08/Stack.cpp

#include "Stack.h"
#include <iostream>

Stack::Link::Link( void* dt, Link* nxt) {
	data = dt;
	next = nxt;
}

Stack::Link::~Link() {

}

Stack::Stack() {
	head = 0;
}

Stack::~Stack() {
	if(head != 0) {
		std::cout << "Stack::~Stack() error no empty:" << head << std::endl;
	}
	else {
		std::cout << "Stack::~Stack() ok" << std::endl;
	}
}

void Stack::push(void* data) {
	Link* next = new Link( data, head);
	head = next;
}

void* Stack::peek() {
	if(head == 0) {
		return 0;
	}
	return head->data;
}

void* Stack::pop() {
	if(head == 0) {
		return 0;
	}
	void* r = head->data;
	Link* l = head;
	head = l->next;
	delete l;
	//std::cout << "Stack::pop() head:" << reinterpret_cast<int>(head) << std::endl;
	return r;
}
