#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template<typename iterator>
void ergodic(iterator first, iterator last, string contName);

int main() {
	list<int> ilist;
	list<int>::iterator ilist_iter;
	vector<int> ivec;
	vector<int>::iterator ivec_iter;
	int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
	int i;
	const int n = sizeof(ia)/sizeof(*ia);

	for( i=0; i<n; i++) {
		ilist.insert( ilist.end(), ia[i]);
		ivec.insert( ivec.end(), ia[i]);
	}

	cout << "=================== init ==================" << endl;
	ergodic( ilist.begin(), ilist.end(), "ilist");
	ergodic( ivec.begin(), ivec.end(), "ivec");

	ilist_iter = ilist.begin();
	for( ; ilist_iter != ilist.end(); /*ilist_iter++*/) {
		if( *ilist_iter % 2 == 0) {
			ilist_iter = ilist.erase( ilist_iter);
		}
		else {
			ilist_iter++;
		}
	}

	ivec_iter = ivec.begin();
	for( ; ivec_iter != ivec.end(); /*ivec_iter++*/) {
		if( *ivec_iter % 2 == 1) {
			ivec_iter = ivec.erase( ivec_iter);
		}
		else {
			ivec_iter++;
		}
	}

	cout << "=================== erase =================" << endl;
	ergodic( ilist.begin(), ilist.end(), "ilist");
	ergodic( ivec.begin(), ivec.end(), "ivec");
	return 0;
}

template<typename iterator>
void ergodic(iterator first, iterator last, string contName) {
	iterator iter = first;
	int i=0;
	for( ; iter!=last; iter++) {
		cout << contName << "[" << i << "]=" << *iter << endl;
		i++;
	}
	cout << "-------------------------------------------" << endl;
}
