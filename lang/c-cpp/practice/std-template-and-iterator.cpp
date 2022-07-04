#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <string>
using namespace std;

template<typename iterator>
void ergodic( iterator first, iterator last, string contName) {
	iterator iter = first;
	int i=0;
	cout << "------------------------ start -------------------------" << endl;
	for( ; iter != last; iter++) {
		cout << contName << "[" << i << "]=" << *iter << ";" << endl;
	}
	cout << "------------------------ end ---------------------------" << endl;
}

int main() {
	list<int> ilist;
	deque<int> ideq;
	vector<int> ivec;

	ilist.push_back(1);
	ideq.push_back(2);
	ivec.push_back(3);

	ilist.push_front(4);
	ideq.push_front(5);
	//ivec.push_front(6); //error not support
	
	ilist.insert( ilist.begin(), 7);
	ideq.insert( ideq.begin(), 2, 8);
	ivec.insert( ivec.begin(), 9);

	ergodic<list<int>::iterator>( ilist.begin(), ilist.end(), "ilist");
	ergodic<deque<int>::iterator>( ideq.begin(), ideq.end(), "ideq");
	ergodic<vector<int>::iterator>( ivec.begin(), ivec.end(), "ivec");
	return 0;
}


