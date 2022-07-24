// : practice-05-05/main.cpp

#include <iostream>
using namespace std;

class ClassA;
class ClassB {
public:
    void func( ClassA * ca);
};
class ClassC {
public:
    void func( ClassA * ca);
};
class ClassA {
public:
    ClassA( int i_) {
        i = i_;
    }
    friend class ClassB;
    friend void ClassC::func( ClassA * ca);
private:
    int i;
};

void ClassB::func( ClassA * ca) {
	cout << "ClassB.func print ClassA.i :" << ca->i << endl;
}

void ClassC::func( ClassA * ca) {
	cout << "ClassC.func print ClassA.i :" << ca->i << endl;
}

int main() {
	ClassA ca(10);
	ClassB cb;
	ClassC cc;
	cb.func(&ca);
	cc.func(&ca);
	return 0;
}
