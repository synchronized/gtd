#include <iostream>
#include <set>


template <typename T, const char* STR> 
void printCells(const T& cell)
{
	std::cout << STR << std::endl;
	typename T::const_iterator it;
	for(it = cell.begin(); it != cell.end(); ++it)
		std::cout << *it << std::endl;
}

int main() {
	std::set<int> iset;
	const char c = 'b';
	const char* s = &c;
	
	//const char* str = new const char('c'); //&c;
	printCells< std::set<int>, s>(iset);
	return 0;
}
