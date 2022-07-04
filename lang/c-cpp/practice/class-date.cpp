#include <iostream>
using namespace std;

class Time {
private:
    int hour;
    int minute;
    int sec;
public:
    void set_time();
    void show_time();
};

void Time::set_time() {
    cout << "please input the hour:";
	cin >> this->hour;
    cout << "please input the minute:";
	cin >> this->minute;
    cout << "please input the sec:";
	cin >> this->sec;
}

void Time::show_time() {
	cout << "use class" << endl;
	cout << this->hour << ":" << this->minute << ":" << this->sec <<endl;
}

Time t;

int main() {
	t.set_time();
	t.show_time();
	return 0;
}
