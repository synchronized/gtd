//test4.cpp

class Z{
	int i;
	mutable int j;
public:
	Z( int i);
	void f() const;
};

Z::Z( int i):i(i),j(0) {}

void Z::f() const {
	//i++; //error
	((Z*)this)->i++;
	j++; //mutable
}

int main() {
	const Z zz(10);
	zz.f();
	return 0;
}
