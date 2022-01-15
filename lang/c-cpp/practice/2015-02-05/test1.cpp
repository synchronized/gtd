#include <iostream>
#include <cstdio>
#include <cstring>

int main()
{
	char buf[100];
	memset(buf, 48, 100);
	buf[99] = 0;
	std::cout << buf << std::endl;
	sprintf(buf, "%d, %s", 1001, "sunday");
	std::cout << buf << std::endl;
	return 0;
}
