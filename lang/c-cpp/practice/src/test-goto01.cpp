//:practice-06-04/main.cpp

#include <iostream>
using namespace std;

class Simple{
	int i;
public:
	Simple(int i_) {
		i = i_;
	}
	~Simple() {
		cout << "Simple::~Simple():" << i << endl;
	}
};

int main() {
	int i=0;
	while(1) {
		i++;
		Simple s1(i);
		if(i>2){
			cout << "goto mark:" << i << endl;
			goto mark;
		}
	}
mark:
	return 0;
}
