#include <iostream>
#include <string>

using namespace std;

int main() {
	string str1 = "ab2c3d7R4E6";
	string num;
	string letter;
	string::size_type pos;
	char i;

	for( i=48; i<=57; i++) {
		num.append( 1, i);
	}
	for( i=65; i<=90; i++) {
		letter.append( 1, i);
		letter.append( 1, i+32);
	}
	cout << "------------------- init -------------------" << endl;
	cout << "str1=" << str1 << endl;
	cout << "num=" << num << endl;
	cout << "letter=" << letter << endl;

	cout << "------------------- find -------------------" << endl;
	cout << "str1 num pos:";
	pos = str1.find_first_of( num);
	while(1) {
		pos = str1.find_first_of( num, pos+1);
		if(pos != string::npos) {
			cout << pos << " ";
		}
		else {
			break;
		}
	}
	cout << endl;

	cout << "------------------- find last --------------" << endl;
	cout << "str1 letter pos:";
	pos = str1.find_last_of( letter);
	while(1) {
		if( pos-1 > pos) {
			break;
		}
		pos = str1.find_last_of( letter, pos-1);
		if(pos != string::npos) {
			cout << pos << " ";
		}
		else {
			break;
		}
	}
	cout << endl;
	return 0;
}
