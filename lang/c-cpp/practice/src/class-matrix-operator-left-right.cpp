#include <iostream>
using namespace std;

class Matrix
{
	public:
		//Matrix( int * const p);
		Matrix * operator +(Matrix &m);
		int * getData();
		void setData( int * const p);
		void display();
	private:
		int data[2][3];

};

//Matrix::Matrix( int * const p)
//{
//	setData( p);
//}

int * Matrix::getData() {
	return data[0];
}

void Matrix::setData( int * const p) {
	int * p1, * p2, n;
	for(p1=p,p2=data[0],n=0; n<6; n++,p1++,p2++) {
		*p2 = *p1;
	}
}

Matrix * Matrix::operator +(Matrix &m) {
	Matrix * r = new Matrix;
	r->setData( this->getData());

	int * p1, * p2, n;
	p1=m.getData();
	p2=r->getData();
	for(n=0; n<6; n++,p1++,p2++) {
		*p2 += *p1;
	}
	return r;
}

void Matrix::display() {
	int * p1, n;
	p1=data[0];
	n=0;
	do{
		cout <<*p1;
		if((n+1)%3 ==0) {
			cout <<endl;
		} else if(n<5){
			cout <<",";
		}
		n++,p1++;
	} while(n<6);
	cout <<endl;
}

istream & operator >>(istream & input, Matrix &m) {
	int * p, n;
	int a[6];
	p=a;
	for(n=0; n<6; p++,n++) {
		input >> *p;
	}
	m.setData(a);
	return input;
}

ostream & operator <<(ostream & output, Matrix &m) {
	int * p, n;
	p=m.getData();
	for(n=0; n<6; p++,n++) {
		output << *p;
		if((n+1)%3 ==0) {
			output <<endl;
		} else if(n<5) {
			output <<",";
		}
	}
	output <<endl;
	return output;
}

int main() {
	Matrix m1, m2, * m3;
	//int a[6] = {1,2,3,4,5,6}, b[6] = {12,11,10,9,8,7};
	//m1.setData( a);
	//m2.setData( b);
	cout <<"please input Matrix m1:" <<endl;
	cin >>m1;
	cout <<"please input Matrix m2:" <<endl;
	cin >>m2;

	m3 = m1+m2;
	//cout <<"m1:"; m1.display();
	//cout <<"m2:"; m2.display();
	//cout <<"m3:"; m3.display();

	cout <<"m1:" <<endl; cout <<m1;
	cout <<"m2:" <<endl; cout <<m2;
	cout <<"m3:" <<endl; cout <<*m3;
	return 0;
}
