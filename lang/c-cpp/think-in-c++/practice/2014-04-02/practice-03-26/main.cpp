#include <iostream>
using namespace std;

void func1( void* arr, int n, int val);

int main() {
	int n=10, iArr[] = {1,2,3,4,5,6,7,8,9,0};
	func1( static_cast<void*>(iArr), sizeof(iArr), 1001);
	for( int i = 0; i < n; i++){
		cout << *(iArr + i) <<' ';
	}
	cout <<endl;
	return 0;
}

void func1( void* arr, int n, int val) {
	unsigned char * uchp = reinterpret_cast<unsigned char *>(arr);
	for( int i = 0; i < n; i++) {
		*(uchp + i) = val;
	}
}
