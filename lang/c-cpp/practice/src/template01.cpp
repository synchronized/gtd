//16_1.cpp

#include <iostream>
using namespace std;

template<class Type> class C1;
template<class Type, int *ptr> class C2;

template<class T> void foo1(T,T) {}

template<class T> inline T foo(T, unsigned int*);
template<class S> inline S foo(S, unsigned int*);

typedef char Ctype;
template <typename Ctype> Ctype f5(Ctype a);

template<typename T>
T jia(T t1, T t2) {
	T t3 = t1 + t2;
	return t1 + t2;
}


template<class S>
inline S foo(S s1, unsigned int*) {
	return  s1;
}


template <typename Ctype>
Ctype f5(Ctype a) {
	return a;
}


int main() {
	cout << "jia<int>(1, 2)=" << jia(1, 2) << endl;
	foo1( 1, 2);
	return 0;
}
