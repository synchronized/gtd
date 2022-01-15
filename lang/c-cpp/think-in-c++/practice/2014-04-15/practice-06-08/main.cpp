//:practice-06-08/main.cpp

#include "Stack.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	Stack s;
	string str[] = {"ZhangSan", "LiSi", "WangWu"};
	for(int i = 0; i < sizeof str / sizeof *str; i++) {
		cout << "s.push(" << str[i] << ")" << endl;
		s.push( reinterpret_cast<void*>(&(str[i])));
	}

	while( void* v = s.pop()) {
		//cout << "s.pop():" << *(reinterpret_cast<string*>(v)) << endl;
	}
	return 0;
}

