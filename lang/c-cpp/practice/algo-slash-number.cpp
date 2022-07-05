#include <iostream>
using namespace std;

int main() {
	int i,j,end;
	cin >>end;
	for( i=2; i<end; i++) {
		for( j=2; i<=i; j++) {
			if( i==j) {
				cout <<i <<" ";
			}
			if( i%j == 0) {
				break;
			}
		}
	}
	cout <<endl;
}
