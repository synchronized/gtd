#include <iostream>
#include <string>
using namespace std;

int main()
{
	union myUni {
		//string aa;    //有构造函数或者析构函数的成员不能再共用体中
		char carr[10];  //and int is 12 only char[] is 10
		//int iarr[10];   //40
		//int i;            //4
		long long l;    //8
	};
	char carr2[10];
	cout <<"sizeof( myUni):" <<sizeof( myUni) <<endl;
	cout <<"sizeof( carr2):" <<sizeof( carr2) <<endl;
	return 0;
}
