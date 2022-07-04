#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main() {
	int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
	int i=0;
	list<int> ilist;
	vector<int> ivec;
	for(i=0; i< sizeof(ia)/sizeof(*ia); i++) {
		ilist.push_back( ia[i]);
		ivec.push_back( ia[i]);
	}
	
	i=0;
	for(list<int>::iterator il_iter = ilist.begin(); il_iter!= ilist.end(); il_iter++, i++) {
		cout << "ilist[" << i << "]=" << *il_iter << endl;
	}
	cout << "--------------------------------------------------------------" << endl;
	i=0;
	for(vector<int>::iterator iv_iter = ivec.begin(); iv_iter!= ivec.end(); iv_iter++, i++) {
		cout << "ivec[" << i << "]" << *iv_iter << endl;
	}
	cout << "--------------------------------------------------------------" << endl;
	typedef list<int>::iterator LIST_ITER;
	vector< LIST_ITER > ev_list;
	for(list<int>::iterator il_iter = ilist.begin(); il_iter != ilist.end(); il_iter++) {
		if( *il_iter % 2 != 0) {
			ev_list.push_back(il_iter);
		}
	}
	for( vector< LIST_ITER >::iterator li_iter = ev_list.begin(); li_iter != ev_list.end(); li_iter++) {
		ilist.erase( *li_iter);
	} 
	for(vector<int>::iterator iv_iter = ivec.begin(); iv_iter != ivec.end(); iv_iter++) {
		if( *iv_iter % 2 == 0) {
			ivec.erase(iv_iter);
		}
	}

	i=0;
	for(list<int>::iterator il_iter = ilist.begin(); il_iter!= ilist.end(); il_iter++, i++) {
		cout << "ilist[" << i << "]=" << *il_iter << endl;
	}
	cout << "--------------------------------------------------------------" << endl;
	i=0;
	for(vector<int>::iterator iv_iter = ivec.begin(); iv_iter!= ivec.end(); iv_iter++, i++) {
		cout << "ivec[" << i << "]" << *iv_iter << endl;
	}
	list<int>::value_type j= 20;
	cout << j << endl;
	return 0;
}
