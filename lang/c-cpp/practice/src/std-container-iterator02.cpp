#include <iostream>
#include <algorithm>
#include <vector>

int main() {
	int i;
	const int n=10;
	std::vector<int> vec;
	std::vector<int>::iterator vec_it;
	std::vector<int>::iterator vec_uni_it;
	
	for( i=0; i<n; i++) {
		vec.insert( vec.end(), 2, i);
	}
	std::cout << "-------------------- init ---------------------" << std::endl;
	vec_it = vec.begin();
	for( i=0; vec_it != vec.end(); vec_it++, i++) {
		std::cout << "vec[" << i << "]=" << *vec_it << std::endl;
	}

	vec_uni_it = unique( vec.begin(), vec.end());
	std::cout << "-------------------- unique -------------------" << std::endl;
	vec_it = vec.begin();
	for( i=0; vec_it != vec.end(); vec_it++, i++) {
		std::cout << "vec[" << i << "]=" << *vec_it << std::endl;
	}

	std::cout << "-------------------- unique res ---------------" << std::endl;
	vec_it = vec.begin();
	for( i=0; vec_it != vec_uni_it; vec_it++, i++);
	for( ; vec_it != vec.end(); vec_it++, i++) {
		std::cout << "vec[" << i << "]=" << *vec_it << std::endl;
	}
	
	return 0;
}
