#include <iostream>
#include <list>
using namespace std;

int main() {
	list<int> i_lt(10, 0);
	int i=0;
	for(list<int>::iterator iter=i_lt.begin(); iter != i_lt.end(); iter++) {
		i++;
		(*iter) = i;
	}
	i = 10;
	for(list<int>::reverse_iterator iter=i_lt.rbegin(); iter != i_lt.rend(); iter++) {
		cout << "item " << i << ":" << *iter << endl;
		i--;
	}
	return 0;
}
