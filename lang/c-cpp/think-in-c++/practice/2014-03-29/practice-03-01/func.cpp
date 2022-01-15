#include <iostream>
#include "func.h"
using namespace std;

#define MYFUNCDEF(RETVAL, FUNCNAME) RETVAL FUNCNAME(...) {\
	cout <<#RETVAL <<" " <<#FUNCNAME <<endl; return static_cast<RETVAL>(0);}

MYFUNCDEF(void, fvoid);
MYFUNCDEF(char, fchar);
MYFUNCDEF(int, fint);
MYFUNCDEF(float, ffloat);



