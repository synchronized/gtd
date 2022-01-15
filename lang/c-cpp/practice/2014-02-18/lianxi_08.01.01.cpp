#include <iostream>
using namespace std;

class Time
{
	private:
		int hour;
		int minute;
		int sec;
	public:
		void set_time();
		void show_time();
};
Time t;

int main()
{
	t.set_time();
	t.show_time();
	return 0;
}

void Time::set_time()
{
	cin >>this->hour;
	cin >>this->minute;
	cin >>this->sec;
}

void Time::show_time()
{
	cout <<"use class" <<endl;
	cout <<this->hour <<":" 
		<<this->minute <<":"
		<<this->sec <<endl;
}
