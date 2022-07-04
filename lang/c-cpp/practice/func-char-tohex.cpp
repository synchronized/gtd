#include <iostream>
#include <cassert>
using namespace std;

void printHex(int i);
void printHexChar(char c);
void printHex_(char c);

int main() {
	int i = 33333333;
	printHex(i);
	return 0;
}

void printHex(int i) {
	char* v = reinterpret_cast<char*>(&i);
	for(int j = sizeof(i)-1; j >= 0; j--) {
		printHexChar(v[j]);
	}
}
void printHexChar(char c) {
	char l = c & 240;
	char r = c & 15;
	
	l = l >> 4;
	l = l & 15;
	printHex_(l);
	printHex_(r);
}

void printHex_(char h) {
	assert( h < 16);
	switch(h){
		case 10:
			cout << 'A';
			break;
		case 11:
			cout << 'B';
			break;
		case 12:
			cout << 'C';
			break;
		case 13:
			cout << 'D';
			break;
		case 14:
			cout << 'E';
			break;
		case 15:
			cout << 'F';
			break;
		default:
			cout << static_cast<int>(h);
	}
}
