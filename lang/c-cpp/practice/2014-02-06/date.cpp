#include <iostream>
using namespace std;

int getalldays(int year);
int getdays(int year, int month);
int getdaysbyyear(int year, int month, int day);
int getweekday( int year, int month, int day);
void outputday( int day, char sday[]);
bool yeartype( int year);
int main()
{
	int year,month,weekday,days,i;
	char sday[3];
	cin >>year;
	cout <<"============================" <<endl;
	cout <<"            " <<year <<"            " <<endl;
	cout <<"============================" <<endl;

	weekday = getweekday( year, 1, 1);
	for(month=1;month<=12;month++)
	{
		outputday(month, sday);
		days = getdays(year, month);
		cout <<"----------------------------" <<endl;
		cout <<"            " <<sday <<endl;
		cout <<"----------------------------" <<endl;
		cout <<"SUN MON TUE WEN THU FRI SAT " <<endl;
		
		if(weekday%7==0)weekday=0;
		for(i=0; i<weekday; i++)
		{
			cout <<"    ";
		}
		for(i=1; i<=days; i++,weekday++) 
		{
			if(weekday%7==0 && weekday!=0)
			{
				weekday=0;
				cout <<endl;
			}
			outputday(i, sday);
			cout <<' ';
			cout <<sday;
			cout <<' ';
		}
		if(weekday%7!=0)
		{
			for(i=weekday; i<7; i++)
			{
				cout <<"    ";
			}
			cout <<endl;
		}
		else
		{
			weekday=0;
			cout <<endl;
		}
	}
	return 0;
}

int getdays(int year, int month)
{
	int r;
	switch(month)
	{
		case 2: r = yeartype(year)?29:28;break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12: r = 31;break;
		default:r = 30;
	}
	return r;
}

int getdaysbyyear(int year, int month, int day)
{
	int r=0,i;
	for(i=1; i<month; i++)
	{
		r+=getdays(year, month);
	}
	r+=day;
	return r;
}

int getalldays(int year)
{
	return yeartype(year)?366:365;
}

bool yeartype( int year)
{
	if( year%4==0 && year%100!=0)
	{	
		return true;
	}
	else if( year%400==0) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

int getweekday( int year, int month, int day)
{
	int baseyear = 1970;
	int basemonth = 1;
	int baseday = 1;
	int baseweekday = 4;
	int i,r,days=0;
	if(year < baseyear)
	{
		for(i=year+1;i<baseyear;i++)
		{
			days += getalldays(i);
		}
		days += getalldays(year) - getdaysbyyear(year, month, day);
	}
	else
	{
		for(i=baseyear;i<year;i++)
		{
			days += getalldays(i);
		}
		days+=getdaysbyyear(year, month, day);

	}
	r = (days+3)%7;
	return r;
}

void outputday( int day, char sday[])
{
	if(day > 9)
	{
		sday[0] = day/10+48;
		sday[1] = day%10+48;
	}
	else 
	{
		sday[0] = '0';
		sday[1] = day+48;
	}
	sday[2]='\0';
}
