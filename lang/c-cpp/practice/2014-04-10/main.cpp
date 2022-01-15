///:main.cpp

/**************************************************************
 * 父类的实例强制转换为子类的引用或者指针
 * 会导致访问子类的成员变量的时候超出对象的内存边界
 * 
 * output:
 * i:10,addr:0x28ac1c
 * f:20,addr:0x28ac18
 * Base b length:8,addr:0x28ac20
 * --------------------------------------------------------
 * Sub s length:16,addr:0x28ac28
 * Sub s.base_1:0,addr:0x28ac28
 * Sub s.base_2:2674276,addr:0x28ac2c
 * --------------------------------------------------------
 * static_cast<Sub&> s2 length:16,addr:0x28ac20
 * static_cast<Sub&> s2.sub_1:0,addr:0x28ac28
 * static_cast<Sub&> s2.sub_2:2674276,addr:0x28ac2c
 * --------------------------------------------------------
 * reinterpret_cast<Sub*> s3 length:16,addr:0x28ac20
 * reinterpret_cast<Sub*> s3.sub_1:0,addr:0x28ac28
 * reinterpret_cast<Sub*> s3.sub_2:2674276,addr:0x28ac2c
 * ************************************************************/

#include <iostream>
using namespace std;

class Base{
	public:
		int base_1;
		int base_2;
};

class Sub : public Base{
	public:
		int sub_1;
		int sub_2;
		Sub(){
			sub_1 = 1;
			//sub_2 = static_cast<float>(2);
			sub_2 = 2;
		}
};

int main() {
	Sub s;
	int i = 10;
	int f = 20;
	Base b;
	Sub& s2 = static_cast<Sub&>(b);
	Sub* s3 = reinterpret_cast<Sub*>(&b);
	cout << "i:" << i << ",addr:" << &i << endl;
	cout << "f:" << f << ",addr:" << &f << endl;
	cout << "Base b length:" << sizeof(b) << ",addr:" << &b << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Sub s length:" << sizeof(s) << ",addr:" << &s << endl;
	cout << "Sub s.base_1:" << s.base_1 << ",addr:" << &s.base_1 << endl;
	cout << "Sub s.base_2:" << s.base_2 << ",addr:" << &s.base_2 << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "static_cast<Sub&> s2 length:" << sizeof(s2) << ",addr:" << &s2 << endl;
	cout << "static_cast<Sub&> s2.sub_1:" << s2.sub_1 << ",addr:" << &s2.sub_1 << endl;
	cout << "static_cast<Sub&> s2.sub_2:" << s2.sub_2 << ",addr:" << &s2.sub_2 << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "reinterpret_cast<Sub*> s3 length:" << sizeof(*s3) << ",addr:" << s3 << endl;
	cout << "reinterpret_cast<Sub*> s3.sub_1:" << s3->sub_1 << ",addr:" << &(s3->sub_1) << endl;
	cout << "reinterpret_cast<Sub*> s3.sub_2:" << s3->sub_2 << ",addr:" << &s3->sub_2 << endl;
	return 0;
}

