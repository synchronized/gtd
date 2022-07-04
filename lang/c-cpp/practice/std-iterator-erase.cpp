#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
	string str1 = "aBcDeFgHiJkLmNoPqRsT";
	string::iterator str_iter;
	string str2(str1);
	vector<char> cvec(str1.begin(), str1.end());
	string str3(cvec.begin(), cvec.end());
	
	cout << "==================== init =================" << endl;
	cout << "str1=" << str1 << endl;
	cout << "str2=" << str2 << endl;
	cout << "str3=" << str3 << endl;

	str_iter = str1.begin();
	for( ; str_iter != str1.end(); str_iter++) {
		if( *str_iter >= 97 && *str_iter <= 122) {
			*str_iter -= 32;
		}
	}
	
	cout << "==================== ltou =================" << endl;
	cout << "str1=" << str1 << endl;

	str_iter = str2.begin();
	for( ; str_iter != str2.end(); ) {
		if( *str_iter >= 65 && *str_iter <= 90) {
			str_iter = str2.erase( str_iter);
		}
		else {
			str_iter++;
		}
	}

	cout << "==================== erase ================" << endl;
	cout << "str2=" << str2 << endl;
	return 0;
}
