#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

int main() {
	typedef std::vector<double> dvector;
	dvector v;
	dvector::iterator v_iter;
	int i;
	const int n=10;
	double sum;

	for(i=0; i<n; i++) {
		v.insert(v.end(), sqrt( i));
	}
	std::cout << "-------------------- init ---------------------" << std::endl;
	v_iter = v.begin();
	for( i=0; v_iter != v.end(); v_iter++,i++) {
		std::cout << "v[" << i << "]=" << *v_iter << std::endl;
	}

	//sum = std::accumulate<dvector::iterator, double>( v.begin(), v.end(), 0);
	sum = accumulate( v.begin(), v.end(), 0.0);
	std::cout << "-------------------- sum ----------------------" << std::endl;
	std::cout << "sum:" << sum << std::endl;
	return 0;
}
