#include <iostream>
using namespace std;

class Matrix
{
	public:
		//Matrix( int * const p);
		Matrix operator +(Matrix &m);
		int * getData();
		void setData( int * const p);
		void display();
	private:
		int data[2][3];

};

/*
Matrix::Matrix( int * const p) 
{
	setData( p);
}
*/

int * Matrix::getData()
{
	return data[0];
}

void Matrix::setData( int * const p)
{
	int * p1, * p2, n;
	for(p1=p,p2=data[0],n=0; n<6; n++,p1++,p2++)
	{
		*p2 = *p1;
	}
}

Matrix Matrix::operator +(Matrix &m)
{
	Matrix r;
	r.setData( this->getData());

	int * p1, * p2, n;
	p1=m.getData();
	p2=r.getData();
	for(n=0; n<6; n++,p1++,p2++)
	{
		*p2 += *p1;
	}
	return r;
}

void Matrix::display() 
{
	int * p1, n;
	p1=data[0];
	n=0;
	do{
		cout <<*p1;
		if(n<5){
			cout <<",";
		}
		n++,p1++;
	}
	while(n<6);
	cout <<endl;
}

int main()
{
	Matrix m1, m2, m3;
	int a[6] = {1,2,3,4,5,6}, b[6] = {12,11,10,9,8,7};
	m1.setData( a);
	m2.setData( b);
	m3 = m1+m2;
	cout <<"m1:"; m1.display();
	cout <<"m2:"; m2.display();
	cout <<"m3:"; m3.display();
	return 0;
}
