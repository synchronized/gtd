#include <iostream>
using namespace std;

int main() {
	int i,j,n=4;
	for(i=1; i<=n; i++) {
		for(j=1; j<=i*2-1; j++) {
			cout <<'*';
		}
		cout <<endl;
	}
	for(i=n-1; i>0; i--) {
		for(j=1; j<=i*2-1; j++) {
			cout <<'*';
		}
		cout <<endl;
	}
	return 0;
}
