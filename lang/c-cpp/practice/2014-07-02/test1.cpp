#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>


int main() {
	typedef std::vector<int> ivector;
	typedef ivector::iterator ivector_iter;
	ivector ivec;
	ivector_iter ivec_iter;
	int i;
	const int n=10;
	ivector_iter::difference_type ivec_cnt;
	//std::iterator_traits<ivector_iter>::difference_type ivec_cnt;
	//size_t ivec_cnt;
	int ivec_sum;
	int mem = 2;

	for( i=0; i<n*3; i++) {
		ivec.insert(ivec.end(), i%10);
	}
	std::cout << "------------- init --------------" << std::endl;
	ivec_iter = ivec.begin();
	for(i=0; ivec_iter!=ivec.end(); ivec_iter++, i++) {
		std::cout << "ivec[" << i << "]=" << *ivec_iter << std::endl;
	}
	ivec_cnt = std::count( ivec.begin(), ivec.end(), mem);

	std::cout << "------------- count -------------" << std::endl;
	std::cout << "member:" << mem << " found " << ivec_cnt << " times" << std::endl;

	ivec_sum = std::accumulate( ivec.begin(), ivec.end(), 0);
	std::cout << "------------- accumulate --------" << std::endl;
	std::cout << "sum:" << ivec_sum << std::endl;
	return 0;
}
