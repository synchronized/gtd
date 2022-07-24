#include <iostream>
using namespace std;

template <class T>
class Compare {
public:
    Compare(T x, T y);
    T max();
    T min();
private:
    T x,y;
};

template <class T>
Compare<T>::Compare(T x, T y) {
	this->x = x;
	this->y = y;
}

template <class T>
T Compare<T>::max() {
	return this->x > this->y ? this->x : this-> y;
}

template <class T>
T Compare<T>::min() {
	return this->x < this->y ? this->x : this->y;
}

int main() {
	Compare<int> c1(3, 7);
	cout <<c1.max() <<" is the Maximum of two integer numbers." <<endl;
	cout <<c1.min() <<" is the Minimum of two integer numbers." <<endl;
	Compare<float> c2(45.78, 93.6);
	cout <<c2.max() <<" is the Maximum of two float numbers." <<endl;
	cout <<c2.min() <<" is the Minimum of two float numbers." <<endl;
	Compare<char> c3('a', 'A');
	cout <<c3.max() <<" is the Maximum of two characters numbers." <<endl;
	cout <<c3.min() <<" is the Minimum of two characters numbers." <<endl;
	return 0;
}
