#include <iostream>
using namespace std;

//这里的声明和下面的定义的形式参数名称可以不一致，
//不知到是否所有编译器都允许
int f( int a, int b, int c);
int main()
{
	int a,b,c;
	cin >>a >>b >>c;

	cout << "a=" << a;
	cout << ",b=" << b;
	cout << ",c=" << c;
	cout << endl;

	c = f(a,b,c);
	cout << c << endl;
	return 0;
}

int f( int x, int y, int z)
{
	int m;
	if( x < y) m = x;
	else m = y;
	if( z < m) m = z;
	return m;
}
