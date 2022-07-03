#include <iostream>
using namespace std;

//选择排序
int main() {
	int array[] = {8,6,5,4,1};
	int i,j,m;
	for(i=0; i<4; i++) {
		for(j=i+1; j<5; j++) {
			if(array[i] > array[j]) {
				m = array[i];
				array[i] = array[j];
				array[j] = m;
			}
		}
	}
	for(i=0;i<5;i++) {
		cout <<array[i];
		cout <<" ";
	}
	cout <<endl;
	return 0;
}
