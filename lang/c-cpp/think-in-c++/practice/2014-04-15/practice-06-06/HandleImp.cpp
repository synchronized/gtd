//:practice-06-06/HandleImp.cpp

#include "Handle.h"

struct Handle::Cheshire{
	int i;
public:
	Cheshire(int i_) {
		i = i_;
	}
};

Handle::Handle() {
	smile = new Cheshire(0);
}

Handle::~Handle() {
	delete smile;
}

int Handle::read() {
	return smile->i;
}

void Handle::change(int i) {
	smile->i = i;
}
