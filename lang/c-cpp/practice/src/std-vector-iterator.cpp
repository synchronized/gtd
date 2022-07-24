#include <iostream>
#include <list>
#include <vector>
#include <string>

using namespace std;

int main() {
	typedef const vector<int> vec_int;
	vec_int ivec(10);
	vector<string> svec(10);
	list<int> ilist(10);

	//vec_int::iterator it=ivec.begin();
	//list<int>::iterator il_iter = ilist.end()+2;
	list<int>::iterator il_iter = ilist.end();
	//vector<string>::iterator vstr_iter = &svec[0];
	vector<string>::iterator vstr_iter = svec.begin();
	for( vector<string>::iterator vstr_it = svec.begin(); vstr_it != svec.end(); ++vstr_it){
		cout << "item" << endl;
	}
	return 0;
}
