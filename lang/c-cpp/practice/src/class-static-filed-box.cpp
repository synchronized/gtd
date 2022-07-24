#include <iostream>
using namespace std;

class Box {
public:
    Box(int, int);
    int volume();
    int width;
    int length;

    static int height;
};

Box::Box(int w, int len) {
	width = w;
	length = len;
}

int Box::volume() {
	return (width*length*height);
}

int Box::height = 10;

int main() {
	Box a(15,20), b(20,30);
	cout <<a.height <<endl;
	cout <<b.height <<endl;
	cout <<Box::height <<endl;
	cout <<a.volume() <<endl;
	Box::height = 15;

	cout <<Box::height <<endl;
	return 0;
}
