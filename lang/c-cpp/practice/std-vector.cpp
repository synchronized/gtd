#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

int main() {
	int ia[7] = {0, 1, 1, 2, 3, 5, 8};
	string sa[6] = {
		"Fort Sumer", "Manassas", "Perryville",
		"Vicksburg", "Meridian", "Chancellorsville"
	};

	cout << "vector<string> svec(sa, sa+6)" << endl;
	vector<string> svec(sa, sa+6);
	cout << "list<int> ilist(ia+4, ia+8);" << endl;
	list<int> ilist(ia+4, ia+8);
	cout << "vector<int> ivec(ia, ia+8);" << endl;
	vector<int> ivec(ia, ia+8);
	cout << "list<string> slist(sa+6, sa);" << endl;
	list<string> slist( sa, sa+6);
	return 0;
}
