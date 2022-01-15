// : practice-05-13/Handle.cpp
// Handle implementation

#include "Handle.h"
#include <iostream>

struct Handle::Cheshire{
	int i;
	int j;
};

void Handle::initialize() {
	smile = new Cheshire;
	smile->i = 0;
	smile->j = 0;
}

void Handle::cleanup() {
	if( smile) {
		smile->i = 0;
		smile->j = 0;
		delete smile;
		std::cout << "Handle.cleanup()" << std::endl;
	}
}

int Handle::read() {
	return smile->i;
}

void Handle::change(int i_) {
	smile->i = i_;
	smile->j = i_;
}
