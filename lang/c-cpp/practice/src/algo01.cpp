#include <iostream>
using namespace std;

//水仙花数
int main() {
	int i,b,s,g;
	for(i=100; i<1000; i++) {
		b=i/100;
		s=(i/10)%10;
		g=i%10;
		if( b*b*b+s*s*s+g*g*g == i) {
			cout <<i <<'='
				<<b <<'x' <<b <<'x' <<b <<'+'
				<<s <<'x' <<s <<'x' <<s <<'+'
				<<g <<'x' <<g <<'x' <<g
				<<endl;
		} else {
			//cout <<'.';
		}
	}
	cout <<endl;
	return 0;
}
