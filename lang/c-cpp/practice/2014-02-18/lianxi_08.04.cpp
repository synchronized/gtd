#include <iostream>
#include <string>
#include "Student.h"
using namespace std;

void Student::display()
{
	cout <<num <<","
		<<name <<","
		<<sex <<endl;
}

void Student::set_value(int num, string name, char sex)
{
	this->num = num;
	this->name = name;
	this->sex = sex;
}

int main() {
	int num;
	string name;
	char sex;
	Student stu;
	cin >>num >>name >>sex;
	stu.set_value(num, name, sex);
	stu.display();
	return 0;
}
