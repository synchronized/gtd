//#include <iostream>
#include <string>
using namespace std;

class Student
{
	public:
		void display();
		void set_value(int num, string name, char sex);
		
	private:
		int num;
		string name;
		char sex;
};
