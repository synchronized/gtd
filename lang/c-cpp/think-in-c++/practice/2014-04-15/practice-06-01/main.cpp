//:practice-06-01/main.cpp

#include <iostream>
using namespace std;

class Simple{
	int i;
public:
	Simple(int i_) {
		i = i_;
		cout << "Simple constructor:" << i << endl;
	}
	~Simple() {
		cout << "Simple distory:" << i << endl;
	}

};

int main() {
	cout << "main create Simple" << endl;
	Simple s(10), s2(20);
	return 0;
}
