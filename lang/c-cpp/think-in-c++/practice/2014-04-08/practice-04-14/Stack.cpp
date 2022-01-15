//: Stack.cpp
//

#include "Stack.h"

template<class T>
Stack<T>::Stack() {
	_size = 0;
	head = 0;
}

template<class T>
void Stack<T>::push( T * element) {
	Element * e =  new Element( element, head);
	head = e;
	_size++;
}

template<class T>
T * Stack<T>::pop() {
	if( head == 0) {
		return 0;
	}
	Element * e = head;
	head = head->getNext();
	T * data = e->getData();
	delete e;
	_size--;
	return data;
}

template<class T>
T * Stack<T>::peek() {
	if( head == 0) {
		return 0;
	}
	return head->getData();
}

template<class T>
int Stack<T>::size() {
	return _size;
}

template<class T> 
Stack<T>::Element::Element( T * dt, typename Stack<T>::Element * nxt) {
	data = dt;
	next = nxt;
}

template<class T> 
Stack<T>::Element::~Element() {
	data = 0;
	next = 0;
}

template<class T>
T * Stack<T>::Element::getData() {
	return data;
}

template<class T>
typename Stack<T>::Element * Stack<T>::Element::getNext() {
	return next;
}
