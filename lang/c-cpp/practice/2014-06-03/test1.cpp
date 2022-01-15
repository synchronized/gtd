#include <iostream>
using namespace std;

void printHex( int input);
void printBinary( int input);
char numToHex( char input);

int main() {
	int t = 0x12345678;
	printBinary( t);
	printHex( t);
	return 0;
}

void printHex(int input) {
	unsigned char* tp  = reinterpret_cast<unsigned char*>(&input);
	unsigned char h = 255, d = 255;
	h = h<<4;
	d = d>>4;

	for(unsigned char* i = tp + sizeof(input)-1; i >=tp; i--) {
		
		char item_h = static_cast<char>((*i&h) >> 4);
		char item_d = static_cast<char>((*i&d));

		cout << numToHex( item_h);
		cout << numToHex( item_d);
	}
	cout << endl;
}

char numToHex( char input) {
	char ret = 'X';
	do{
		if( input > 15) {
			break;
		}
		if( input > 9) {
			ret = input + 65-10;
		}
		else {
			ret = input + 48;
		}
	}while(0);
	return ret;
}

void printBinary(int input) {
	char* tp  = reinterpret_cast<char*>(&input);

	for(char* ip = tp + sizeof(input)-1; ip >=tp; ip--) {
		int base = 1;
		for( int i =7; i>=0; i--) {
			if( *ip & (base << i)) {
				cout << '1';
			}
			else {
				cout << '0';
			}
		}
	}
	cout << endl;
}

