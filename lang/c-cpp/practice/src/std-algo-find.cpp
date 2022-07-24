#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template<typename iterator>
void ergodic(iterator first, iterator last, string contName);

int main() {
	int i;
	const int n=10;
	list<int> ilist;
	list<int>::iterator elem1, elem2;

	//deque<int> ideq;
	//vector<int> ivec;

	for( i=0; i<n; i++) {
		ilist.push_back(i);
	}
	cout << "================== init ===================" << endl;
	ergodic( ilist.begin(), ilist.end(), "ilist");

	elem1 = find( ilist.begin(), ilist.end(), 31);
	elem2 = find( elem1, ilist.end(), 31);
	ilist.erase( elem1, elem2);

	cout << "================== earse ==================" << endl;
	ergodic( ilist.begin(), ilist.end(), "ilist");
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
