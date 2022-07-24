#include <iostream>

using namespace std;

#define MYFUNCDECL( RETVAL, FUNCNAME) RETVAL FUNCNAME(...);
#define MYFUNCDEF(RETVAL, FUNCNAME) RETVAL FUNCNAME(...) {              \
        cout <<#RETVAL <<" " <<#FUNCNAME <<endl; return static_cast<RETVAL>(0);}

MYFUNCDECL(void, fvoid);
MYFUNCDECL(char, fchar);
MYFUNCDECL(int, fint);
MYFUNCDECL(float, ffloat);

MYFUNCDEF(void, fvoid);
MYFUNCDEF(char, fchar);
MYFUNCDEF(int, fint);
MYFUNCDEF(float, ffloat);


int main() {
	fvoid( 1);
	fchar( 1);
	fint( 1);
	ffloat( 1);
}
