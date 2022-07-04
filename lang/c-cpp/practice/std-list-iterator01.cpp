#include <iostream>
#include <list>
using namespace std;

int main() {
	int i;
	const int n=10;
	list<int> ilist;
	list<int>::iterator iter;
	list<int>::reverse_iterator riter;

	for( i=0; i<n; i++) {
		ilist.push_back(i);
	}
	//ergodic
	cout << "ergodic" << endl;
	iter = ilist.begin();
	i=0;
	for( ; iter != ilist.end(); iter++) {
		cout << "    ilist[" << i << "]=" << *iter << endl;
		i++;
	}
	cout << "-------------------------------------" << endl;
	//reverse ergodic
	cout << "reverse ergodic" << endl;
	riter = ilist.rbegin();
	i=n;
	for( ; riter != ilist.rend(); riter++) {
		cout << "    ilist[" << i-1 << "]=" << *riter << endl;
		i--;
	}
	return 0;
}
