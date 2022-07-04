#include <iostream>
using namespace std;

class Time {
public:
    Time(int, int, int);
    int hour;
    int minute;
    int sec;
    void get_time();
};

Time::Time(int h, int m, int s) {
	hour = h;
	minute = m;
	sec = s;
}

void Time::get_time() {
	cout <<hour <<":" <<minute <<":" <<sec <<endl;
}

int main() {
	Time t1(10, 12, 56);
	int *p1 = &t1.hour;
	cout <<"*p1:" <<*p1 <<endl;

	cout <<"t1.get_time():";
	t1.get_time();

	Time *p2 = &t1;
	cout <<"p2.get_time():";
	p2->get_time();

	void (Time::*p3)();
	p3 = &Time::get_time;
	cout <<"(t1.*p3)()";
	(t1.*p3)();
	return 0;
}
