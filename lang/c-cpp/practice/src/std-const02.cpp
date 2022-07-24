//:test.cpp

#include <iostream>
using namespace std;

int main() {
	const int i = 100; // Typical constant
	const int j = i + 10; // Value from const expr 
	long address = reinterpret_cast<long>(&j); // Forces storage
	char buf[j + 10]; // Still a const expression

	cout << "type a character & CR:";
	const char c = cin.get(); // Can't change
	const char c2 = c+'a';
	cout << c2;
	cout << "longyin address = reinterpret_cast<long>(&j)" << address << endl;
	return 0;
}
