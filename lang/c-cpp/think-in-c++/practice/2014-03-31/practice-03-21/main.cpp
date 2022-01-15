#include <iostream>
#include <string>
using namespace std;

int main(){
	string strarr[] = {"aaa", "bbb", "ccc"};
	int i, n=3;

	for( i=0; i<n; i++) {
		cout <<*(strarr+i) <<" ";
	}
	cout <<endl;
	return 0;
}
