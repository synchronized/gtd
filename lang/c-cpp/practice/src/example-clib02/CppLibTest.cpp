//: e0401: CppLibTest.cpp
//{L} CLib
// Test the C-like library converted to c++

#include "CppLib.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main() {
	// Define variables at the beginning
	// of the block, as in C:
	Stash intStash, stringStash;
	int i, n=100;
	char* cp;
	ifstream in;
	string line;
	const int bufsize = 80;
	// Now remember to initialize the variables:
	intStash.initialize( sizeof( int));
	for( i = 0; i < n; i++) {
		intStash.add( &i);
	}
	for( i = 0; i < intStash.count( ); i++) {
		cout << "fetch( &intStash, " << i << ") = "
			<< *(int*)intStash.fetch( i)
			<< endl;
	}

	stringStash.initialize( sizeof(char)*bufsize);
	in.open("CppLibTest.cpp");
	assert( in);
	i = 0;
	while( getline( in, line) && i++ < n) {
		stringStash.add( line.c_str());

	}
	i = 0;
	while( (cp = (char*)stringStash.fetch( i)) != 0) {
		cout << "fetch( &stringStash, " << i << ") = "
			<< cp <<endl;
		i++;
	}
	intStash.cleanup();
	stringStash.cleanup();
	return 0;
}///:~
