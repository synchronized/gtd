#include <iostream>
using namespace std;

class Hen{
	public:
		static const int func1() {}
		const static int func2() {}
		const int func3() const {}
};

const int func1() {}
const int func2() {}
int func3() const {}

int main(){
	const unsigned int i = 10;
	unsigned const int j = 10;
	unsigned int const k = 10;
	//unsigned int k const = 10; //error 
	cout << "const unsigned int i:" << i << endl;
	cout << "unsigned const int j:" << j << endl;
	cout << "unsigned int const k:" << k << endl;

	const int * l = new int(10);
	delete l;
	l = new int(20);
	//*l = 30;  //error con't write to readonly memory
	cout << "const int * l:" << *l << endl;

	int const * m = new int(10);
	delete m;
	m = new int(20);
	//*m = 30;  // the same to "const int"
	cout << "int const * m:" << *m << endl;

	int * const n = new int(10);
	delete n;
	//n = new int(20); //error can't write to readonly var "n"
	*n = 30;  
	cout << "int * const n:" << *n << endl;

	const int (*o)() = func1;
	o = func2;  
	cout << "const int (*o)():" << reinterpret_cast<int>(o) << endl;

	const int (* const p)() = func1;
	//p = func2;  //error can't write to readonly var "p"
	cout << "const int (*p)():" << reinterpret_cast<int>(p) << endl;

	const int (* q) () = Hen::func1;
	q = Hen::func2;
	cout << "const int (*q)():" << reinterpret_cast<int>(q) << endl;

	Hen hen;
	const int (* r ) () ;
       	//r = hen.func3;
	//cout << "const int (*r)():" << reinterpret_cast<int>(r) << endl;
	return 0;
}
