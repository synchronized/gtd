#include <iostream>
#include <vector>
#include <list>


int main() {
	std::vector<int> vec; std::list<int> lst; int i;
	std::vector<int>::iterator vec_it;
	std::list<int>::iterator lst_it;
	std::cout << "please input number:";
	while( std::cin >> i) {
		lst.push_back( i);
		std::cout << "please input number:";
	}
	std::cout << "--------------------- init ---------------------" << std::endl;
	lst_it = lst.begin();
	for( i=0; lst_it != lst.end(); lst_it++, i++) {
		std::cout << "lst[" << i << "]=" << *lst_it << std::endl;
	}

	//copy(lst.begin(), lst.end(), vec.begin()); //error
    std::copy(lst.begin(), lst.end(), back_inserter(vec));
	std::cout << "--------------------- copy ---------------------" << std::endl;
	vec_it = vec.begin();
	for( i=0; vec_it != vec.end(); vec_it++, i++) {
		std::cout << "vec[" << i << "]=" << *vec_it << std::endl;
	}
	lst_it = lst.begin();
	for( i=0; lst_it != lst.end(); lst_it++, i++) {
		std::cout << "lst[" << i << "]=" << *lst_it << std::endl;
	}
	return 0;
}
