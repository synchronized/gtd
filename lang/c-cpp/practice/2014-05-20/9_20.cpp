#include <iostream>
#include <vector>
#include <list>

using namespace std;

bool operator==(list<int> first, vector<int> second) {
	if(first.size() != second.size()) {
		return false;
	}
	list<int>::iterator il_iter = first.begin();
	vector<int>::iterator iv_iter = second.begin();
	while(il_iter != first.end() && iv_iter != second.end()) {
		if( *il_iter != *iv_iter) {
			return false;
		}
		il_iter++;
		iv_iter++;
	}
	if( il_iter != first.end() || iv_iter != second.end()){
		return false;
	}
	return true;
}

bool operator==(vector<int> first, list<int> second) {
	return (second == first);
}

int main() {
	int n = 10, i=0;
	vector<int> iv(n, 0);
	list<int> il(n, 0);
	for(i=0; i<n; i++) {
		iv[i] = i;
	}
	i=0;
	for(list<int>::iterator il_iter = il.begin(); il_iter != il.end(); il_iter++) {
		*il_iter = i;
		i++;
	}
	i=0;
	for(vector<int>::iterator iv_iter = iv.begin(); iv_iter != iv.end(); iv_iter++, i++) {
		cout << "iv[" << i << "]=" << *iv_iter << endl;
	}
	i=0;
	for(list<int>::iterator il_iter = il.begin(); il_iter != il.end(); il_iter++, i++) {
		cout << "il[" << i << "]=" << *il_iter << endl;
	}
	if( iv == il) {
		cout << "iv == il" << endl;
	}else {
		cout << "iv != il" << endl;
	}
	if( il == iv) {
		cout << "il == iv" << endl;
	}else {
		cout << "il != iv" << endl;
	}
	return 0;
}
