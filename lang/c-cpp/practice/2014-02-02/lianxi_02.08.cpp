#include <iostream>
using namespace std;

int main() {
	char c[5]={'C','h','i','n','a'};
	int i;
	for (i=0;i<5;i++) {
		int x = c[i];
		if ((x>='a' && x<='z') || (x>='A' && x<='Z')) {
			if( x > 'w') c[i] += 4-26;
			else if (x > 'W' && x <= 'Z') c[i] += 4-26;
			else c[i] += 4;
		}
		cout << c[i];
	}
	cout <<endl;
	return 0;
}
