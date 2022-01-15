#include <iostream>
using namespace std;

struct Student
{
	int num;
	char name[20];
	int score[3];
	int scoreavg;
};

void input(Student *p, int m, int n);
void print(Student *p, int m, int n);
//void print(Student stus[], int m, int n);
int main()
{
	Student *stus = new Student[5];
	int i,j,m=2,n=3;
	input(stus, m, n);
	print(stus, m, n);
	delete [] stus;
	return 0;
}

void input(Student *p, int m, int n)
{
	int i,j;
	for(i=0; i<m; i++,p++)
	{
		cin >>p->num >>p->name;
		p->scoreavg = 0;
		for(j=0; j<n; j++)
		{
			cin >>p->score[j];
			p->scoreavg += p->score[j];
		}
		p->scoreavg /= n;
	}
}

void print(Student *p, int m, int n)
{
	void printline(Student *p, int n);
	int i;
	Student *q = p;
	for(i=0; i<m; p++,i++)
	{
		printline(p, n);
		if(p->scoreavg > q->scoreavg)
		{
			q = p;
		}
	}
	cout <<"max score" <<endl;
	printline(q, n);
}

void printline(Student *p, int n)
{
	int j;
	cout <<p->num <<"\t"
		<<p->name <<"\t";
	for(j=0; j<n; j++)
	{
		cout <<p->score[j] <<"\t";
	}
	cout <<p->scoreavg;
	cout <<endl;
}
