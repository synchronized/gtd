#include <iostream>
#include <cstdint>

class MyClass{
public:
	MyClass(char _m_v)
	{
		m_v = _m_v;
	}
	operator char(){std::cout << "cx:" << m_v << "operator char()" << std::endl;return m_v; }
	operator uint32_t(){std::cout << "cx:" << m_v << "operator uint32_t()" << std::endl;return m_v; }
	bool operator ==(MyClass& b)
	{
		return this->m_v == b.m_v;
	}
private:
	char m_v;
};

int main() {
	MyClass c1(1),c2(1);
	if(c1 == c2)
	{
		std::cout << "c1 == c2" << std::endl;
	}
	else
	{
		std::cout << "c1 != c2" << std::endl;
	}
	return 0;
}
