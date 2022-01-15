#include <iostream>
using namespace std;

class Complex
{
	public:
		Complex();
		Complex(double r);
		Complex(double r, double i);
		void display();
		operator double();
	private:
		double real;
		double imag;
};

Complex::Complex()
{
	real = 0;
	imag = 0;
}

Complex::Complex(double r)
{
	real = r;
	imag = 0;
}

Complex::Complex(double r, double i)
{
	real = r;
	imag = i;
}

void Complex::display()
{
	cout <<"real=" <<real <<",imag=" <<imag <<endl;
}

Complex::operator double()
{
	return real;
}

int main() 
{
	Complex c1=Complex(1.2, 2.3), c2, c3;
	double d1 = 4.5;
	c2 = c1 + d1;
	c3 = d1 + c2;
	cout <<"c1:"; c1.display();
	cout <<"c2:"; c2.display();
	cout <<"c3:"; c3.display();

	return 0;
}
