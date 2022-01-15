//: practice-05-04/main.cpp

#include <iostream>
using namespace std;

class Class2;

class Class1{
	Class2 * c2;
	int i;
	public:
		Class1( int i_) {
			i = i_;
		}
		void setPoint( Class2 * c2_) {
			c2 = c2_;
		}
		void print();
		friend class Class2;
};

class Class2{
	Class1 * c1;
	int i;
	public:
		Class2( int i_) {
			i = i_;
		}
		void setPoint( Class1 * c1_) {
			c1 = c1_;
		}
		void print();
		friend class Class1;
};


void Class1::print(){
	cout << "Class1.i:" << i << endl;
	cout << "Class1.c2.i:" << c2->i << endl;
}

void Class2::print(){
	cout << "Class2.i:" << i << endl;
	cout << "Class2.c1.i:" << c1->i << endl;
}

int main() {
	Class1 c1(1);
	Class2 c2(2);
	c1.setPoint( &c2);
	c2.setPoint( &c1);
	c1.print();
	c2.print();
	return 0;
}
