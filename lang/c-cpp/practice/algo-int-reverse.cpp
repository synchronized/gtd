#include <iostream>
using namespace std;

//将数字颠倒
void pout(int);
int main() {
	int i;
    cout << "please input the var i:";
	cin >>i;
	pout(i);
	cout <<endl;
	return 0;
}

void pout(int i) {
	char m;
	if (i>9) {m = i%10+48;
		cout <<m;
		pout (i/10);
	} else {
		m = i+48;
		cout <<m;
	}
}
