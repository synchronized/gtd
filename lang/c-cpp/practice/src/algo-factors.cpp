#include <iostream>
using namespace std;

//因式分解
int main() {
	int i,j,m,b,n = 1000;
	bool k;
	for(i=1; i<n; i++) {
		m = 0;
		k = false;
		b = i/2+1;
		for(j=1; j<b; j++) {
			if(i%j==0) m+=j;
		}
		if(m==i) {
			cout <<i <<",its factors are ";
			for(j=1; j<b; j++) {
				if(i%j==0) {
					if(k) cout <<',';
					cout <<j;
					k = true;
				}
			}
			cout <<endl;
		}

	}
	return 0;
}
