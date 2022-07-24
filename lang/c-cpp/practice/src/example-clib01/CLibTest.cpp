//: e0401: CLibTest.cpp
//{L} CLib
// Test the C-like library

#include "CLib.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main() {
	// Define variables at the beginning
	// of the block, as in C:
	CStash intStash, stringStash;
	int i, n=100;
	char* cp;
	ifstream in;
	string line;
	const int bufsize = 80;
	// Now remember to initialize the variables:
	initialize( &intStash, sizeof( int));
	for( i = 0; i < n; i++) {
		add( &intStash, &i);
	}
	for( i = 0; i < count( &intStash); i++) {
		cout << "fetch( &intStash, " << i << ") = "
			<< *(int*)fetch( &intStash, i)
			<< endl;
	}
	initialize( &stringStash, sizeof(char)*bufsize);
	in.open("CLibTest.cpp");
	assert( in);
	i = 0;
	while( getline( in, line) && i++ < n) {
		add( &stringStash, line.c_str());

	}
	i = 0;
	while( (cp = (char*)fetch( &stringStash, i)) != 0) {
		cout << "fetch( &stringStash, " << i << ") = "
			<< cp <<endl;
		i++;
	}
	cleanup( &intStash);
	cleanup( &stringStash);
	return 0;
}///:~
