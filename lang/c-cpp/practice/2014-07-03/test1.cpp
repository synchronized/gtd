#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main() {
	typedef std::vector<int> ivec;
	ivec iv;
	ivec::iterator iv_it;
	int i;
	const int n=10;

	fill_n( back_inserter(iv), n, 0);
	std::cout << "------------------ fill_n -------------------" << std::endl;
	iv_it = iv.begin();
	for( i=0; iv_it!=iv.end(); iv_it++, i++) {
		std::cout << "iv[" << i << "]=" << *iv_it << std::endl;
	}

	fill( iv.begin(), iv.end(), 10);
	std::cout << "------------------ fill   -------------------" << std::endl;
	iv_it = iv.begin();
	for( i=0; iv_it!=iv.end(); iv_it++, i++) {
		std::cout << "iv[" << i << "]=" << *iv_it << std::endl;
	}
	return 0;
}
