#include <iostream>
using namespace std;

int main()
{
	//int a[3][4] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23};
	//int *p;
	//for(p = a[0]; p<(a[0]+12); p++)
	//{
	//	cout <<*p;
	//	cout <<" ";
	//}
	//cout <<endl;
	//return 0;
	
	//int a[3][4] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23};
	//int (*p)[4];
	//int i;
	//for(p=a; p<a+3; p++)
	//{
	//	for(i=0; i<4; i++)
	//	{
	//		cout <<*(*p+i);
	//		cout <<" ";
	//	}
	//}
	//cout <<endl;
	//return 0;

	int a[3][4] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23};
	int x, y, (*p)[4];
	cin >>x >>y;
	
	p=a;
	cout <<*(*(p+x)+y);
	cout <<endl;
	return 0;
}
	
