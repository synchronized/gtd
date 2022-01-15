#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	vector<string> svec;
	svec.reserve(1024);
	string text_word;
	//while(cin >>text_word) {
	int idxlist[] = {256, 512, 1000, 1048};
	for( int j=0; j<(sizeof(idxlist)/sizeof(*idxlist)); j++) {
		for( int i=0; i<idxlist[j]; i++) {
			text_word = "123";
			svec.push_back(text_word);
		}
		cout << "idxlist=" << idxlist[j] << ", "
		     << "svec.size()=" << svec.size() << ", "
		     << "svec.capacity()=" << svec.capacity() << endl;

		svec.resize(svec.size()+svec.size()/2);
		cout << "idxlist=" << idxlist[j] << ", "
		     << "svec.size()=" << svec.size() << ", "
		     << "svec.capacity()=" << svec.capacity() << endl;
		svec.clear();
		cout << "---------------------------------------------" << endl;
	}
	//svec.resize(svec.size()+svec.size()/2);
	return 0;
}
