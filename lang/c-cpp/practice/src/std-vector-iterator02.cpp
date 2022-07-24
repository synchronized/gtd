#include <iostream>
#include <vector>
using namespace std;

template<class _Type>
void decode(vector<_Type>& _array) {}

//bool search( (vector<_TP>::iterator)& first, (vector<_TP>::iterator)& last, _TP search_)
template<typename _Type>
bool search(vector<_Type>& vec, _Type seachv) {
    using type_iterator = typename vector<_Type>::iterator;
	type_iterator first = vec.begin();
	type_iterator last = vec.end();
	while(first != last) {
		if(seachv == *first) {
			return true;
		}
		first++;
	}
	return false;
}

int main() {
    vector<int> ivec(10, 0);
	for( int i=0; i< 10; i++){
		ivec[i] = i+1;
	}

	//bool ret = search<int>(ivec.begin(), ivec.end(), 5);
	bool ret = search<int>(ivec, 5);
	if( ret) {
		cout << "foud" << endl;
	}
	else {
		cout << "not foud" << endl;
	}
}
/*
template<typename TYPE>
bool search( vector<TYPE>::iterator& first, vector<TYPE>::iterator& last, TYPE& search) {
	while(first != last) {
		if( search == *first) {
			return true;
		}
	}
	return false;
}
*/
