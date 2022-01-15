#include <iostream>
#include <iomanip>
#include "stdio.h"
using namespace std;

/*
 * 编译不同过，提示getchar/putchar 
 * 函数未定义
 * 不知到是否是教材太老了
 */
int main()
{
	char c1,c2;
	c1 = getchar();
	c2 = getchar();
	cout <<"c1 by putchar:";
	putchar( c1);
	cout <<endl;
	cout <<"c2 by putchar:";
	putchar( c2);
	cout <<endl;

	cout <<"c1 by cout:" <<setw(10) <<c1 <<"-" <<endl;
	cout <<"c2 by cout:" <<setw(10) <<c2 <<"-" <<endl;
	return 0;
}

