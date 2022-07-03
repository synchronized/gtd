#include <iostream>
using namespace std;

//void select_sort(int *p, int n);
void select_sort(int a[], int n);

/*
void select_sort(int *p, int n)
{
	int i,j,m;
	for(i=0; i<n; i++)
	{
		for(j=i+1; j<n; j++)
		{
			if(*(p+i) > *(p+j))
			{
				m = *(p+i);
				*(p+i) = *(p+j);
				*(p+j) = m;
			}
		}
	}
}
*/
void select_sort(int a[], int n) {
	int i,j,m;
	int *p;
	p=a;
	for(i=0; i<n; i++) {
		for(j=i+1; j<n; j++) {
			if(*(p+i) > *(p+j)) {
				m = *(p+i);
				*(p+i) = *(p+j);
				*(p+j) = m;
			}
		}
	}
}

int main() {
	int a[3];
	int i;
	int *p;
	p = a;
	cout <<"please input 10 integers:" <<endl;
	for(i=0; i<3; i++) {
        cin >>a[i];
    }

	cout <<endl;
	select_sort( p, 3);
	for(i=0; i<3; i++) {
        cout <<a[i];
        cout <<" ";
    }
	cout <<endl;
	return 0;
}
