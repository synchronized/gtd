#include <iostream>
using namespace std;

void sort(char *array[], int n);
void print(char *array[], int n);
int strcmp(char str1[], char str2[]);

void sort(char *array[], int n) {
	int i,j,k;
	char* temp;
	for(i=0; i<n; i++) {
		k=i;
		for(j=i+1; j<n; j++) {
			if( strcmp( array[k], array[j]) > 0) k = j;
		}
		if(k != i) {
			temp = array[k];
			array[k] = array[i];
			array[i] = temp;
		}
	}
}

void print(char *array[], int n) {
	int i;
	for(i=0; i<n; i++) {
		cout <<array[i];
		cout <<" ";
	}
	cout <<endl;
}

int strcmp(char str1[], char str2[]) {
	int i=0;
	while(str1[i]!='\0'&&str2[i]!='\0') {
		if( str1[i] > str2[i]) return 1;
		else if( str1[i] < str2[i]) return -1;
		i++;
	}
	if(str1[i]=='\0'&&str2[i]=='\0') return 0;
	if(str1[i]=='\0') return -1;
	else return -1;
}

int main() {
	char *name[] = {"BASIC", "FORTRAN", "C++", "Pascal", "COBOL"};
	int n = 5;
	sort( name, n);
	print( name, n);
	return 0;
}
