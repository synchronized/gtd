#include <iostream>
#include <vector>
using namespace std;

template<class _Type>
void decode(vector<_Type>& _array)
{}

template<class _Type>
//bool search( (vector<_TP>::iterator)& first, (vector<_TP>::iterator)& last, _TP search_)
bool search( (vector<_Type>& vec)
{
_Type search_ = 1;
	vector<_TP>::iterator first = vec.begin();
	vector<_TP>::iterator last = vec.end();
	while(first != last) {
		first++;
		if( search_ == *first) {
			return true;
		}
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
