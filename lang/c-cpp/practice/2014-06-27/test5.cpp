#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <string>
using namespace std;

template<typename iterator>
void ergodic(iterator first, iterator last, string contName);

int main() {
	int i;
	const int n=10;
	list<int> ilist;
	deque<int> ideq;
	vector<int> ivec;

	list<int>::iterator ilist_iter;
	deque<int>::iterator ideq_iter;
	vector<int>::iterator ivec_iter;

	//init
	for( i=0; i<n; i++){
		ilist.insert( ilist.end(), i);
		ideq.insert( ideq.end(), i);
		ivec.insert( ivec.end(), i);
	}

	cout << "================= init ====================" << endl;
	//erase
	ergodic<list<int>::iterator>(ilist.begin(), ilist.end(), "ilist");
	ergodic<deque<int>::iterator>(ideq.begin(), ideq.end(), "ideq");
	ergodic<vector<int>::iterator>(ivec.begin(), ivec.end(), "ivec");

	//erase
	ilist_iter = ilist.end();
	ilist.erase( --ilist_iter);
	//ilist.erase( ilist.end()); //illegal iterator
	ideq_iter = ideq.end();
	ideq.erase( --ideq_iter);
	ivec_iter = ivec.end();
	ivec.erase( --ivec_iter);
	
	cout << "================= erase ===================" << endl;
	//erase
	ergodic<list<int>::iterator>(ilist.begin(), ilist.end(), "ilist");
	ergodic<deque<int>::iterator>(ideq.begin(), ideq.end(), "ideq");
	ergodic<vector<int>::iterator>(ivec.begin(), ivec.end(), "ivec");

	ilist.pop_back();
	ilist.pop_front();
	ideq.pop_back();
	ideq.pop_front();
	ivec.pop_back();
	//ivec.pop_front(); //error vector unsupport pop_front

	cout << "================= pop_back/front ==========" << endl;
	//erase
	ergodic<list<int>::iterator>(ilist.begin(), ilist.end(), "ilist");
	ergodic<deque<int>::iterator>(ideq.begin(), ideq.end(), "ideq");
	ergodic<vector<int>::iterator>(ivec.begin(), ivec.end(), "ivec");
	
	ilist.clear();
	ideq.clear();
	ivec.clear();
	cout << "================= clear ===================" << endl;
	cout << "ilist.size()=" << ilist.size()
		//<< ",ilist.capacity()=" << ilist.capacity() 
		<< endl;
	cout << "ideq.size()=" << ideq.size()
		//<< ",ideq.capacity()=" << ideq.capacity() 
		<< endl;
	cout << "ivec.size()=" << ivec.size()
		<< ",ivec.capacity()=" << ivec.capacity() 
		<< endl;
	
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
