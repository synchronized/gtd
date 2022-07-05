#include <iostream>

using namespace std;

class Handle{
	struct Cheshire;
	Cheshire* smile;
public:
	Handle();
	~Handle();
	int read();
	void change(int i);
};

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

int main() {
	Handle h1, h2;
	h1.change(10);
	h2.change(20);
	cout << "h1.read():" << h1.read() << endl;
	cout << "h2.read():" << h2.read() << endl;
	return 0;
}
