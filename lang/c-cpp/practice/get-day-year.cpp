#include <iostream>
using namespace std;

struct Date {
	int year;
	int month;
	int day;
};

bool isleap(int year);
int getdaybyyear(Date date);

bool isleap(int year) {
	bool r;
	if(year%4==0 && year%100!=0) r = true;
	else if(year%400==0) r = true;
	else r = false;
	return r;
}

int getdaybyyear(Date date) {
	int r=0;
	switch(date.month-1) {
		case 11: r+=30;
		case 10: r+=31;
		case 9: r+=30;
		case 8: r+=31;
		case 7: r+=31;
		case 6: r+=30;
		case 5: r+=31;
		case 4: r+=30;
		case 3: r+=31;
		case 2: r+=(isleap(date.year)?29:28);
		case 1: r+=31;
		case 0: break;
		default:
			 return -1;
	}
	cout <<"r=" <<r <<endl;
	r+=date.day;
	return r;
}

int main() {
	Date date = {2000,1,1};
	cout << "please input the year:";
	cin >> date.year;
	cout << "please input the month:";
    cin >> date.month;
	cout << "please input the day:";
    cin >> date.day;

	cout <<date.year <<"-" <<date.month <<"-" <<date.day <<endl;
	cout <<"the day is " <<getdaybyyear(date) <<" of year" <<endl;
	return 0;
}
