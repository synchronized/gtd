#include <iostream>
using namespace std;

class Complex
{
public:
    Complex();
    Complex(double r, double i);
    Complex * setReal(double r);
    double getReal();
    Complex * setImag(double i);
    double getImag();
    void display();
private:
    double real;
    double imag;
};

Complex::Complex() {
	real = 0;
	imag = 0;
}

Complex::Complex(double r, double i) {
	real = r;
	imag = i;
}

Complex * Complex::setReal(double r) {
	real = r;
	return this;
}

double Complex::getReal() {
	return real;
}

Complex * Complex::setImag(double i) {
	imag = i;
	return this;
}

double Complex::getImag() {
	return imag;
}

void Complex::display() {
	cout <<"real=" <<real <<",imag=" <<imag <<endl;
}

Complex operator +(Complex a, Complex b) {
	return Complex(a.getReal()+b.getReal(), a.getImag()+b.getImag());
}

int main() {
	Complex c1=Complex(1.2, 3.4), c2=Complex(5.6, 7.8), c3;
	c3 = c1 + c2;
	cout <<"c1:"; c1.display();
	cout <<"c2:"; c2.display();
	cout <<"c3:"; c3.display();

	return 0;
}
