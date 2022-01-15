// : practice-05-06/main.cpp

#include <iostream>
using namespace std;

class Egg;
class Hen{
	public:
		class Nest;
		void display() {
			cout << "Hen.display()" << endl;
		}
		void display( Hen::Nest * hn);
		void display( Egg * e);
	private:
		int i;
};

class Egg{
	public:
		Egg( int i_){
			i = i_;
		}
		void display() {
			cout << "Egg.display()" << endl;
		}
		friend void Hen::display( Egg * e);
	private:
		int i;
};

class Hen::Nest{
	public:
		Nest( int i_){
			i = i_;
		}
		void display() {
			cout << "Hen::Nest.display()" << endl;
		}
		friend void Hen::display( Nest * h);
	private:
		int i;
};

void Hen::display( Hen::Nest * hn) {
	cout << "Hen::display( Nest * e) Nest.i:" << hn->i << endl;
}

void Hen::display( Egg * e) {
	cout << "Hen::display( Egg * e) Egg.i:" << e->i << endl;
}

int main() {
	Hen h;
	Hen::Nest hn(10);
	Egg e(20);
	h.display();
	hn.display();
	e.display();
	h.display( &hn);
	h.display( &e);
	return 0;
}
