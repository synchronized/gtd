#include <iostream>
#include <list>
#include <deque>

using namespace std;

int main() {
	list<int> src(10, 0);
	deque<int> tr1;
	deque<int> tr2(5, 0);
	int i=0;
	for(list<int>::iterator iter = src.begin(); iter != src.end(); iter++, i++) {
		*iter = i;
	}
	i = 0;
	for(list<int>::iterator iter = src.begin(); iter != src.end(); iter++){
		int j = *iter;
		if( j%2 == 0) {
			tr1.push_back(j);
		}
		else {
			tr2[i] = j;
			i++;
		}
	}
	deque<int>::iterator dq_iter;
	for(dq_iter = tr1.begin(), i=0; dq_iter != tr1.end(); dq_iter++, i++) {
		cout << "tr1[" << i << "]=" << *dq_iter << endl;
	}
	for(dq_iter = tr2.begin(), i=0; dq_iter != tr2.end(); dq_iter++, i++) {
		cout << "tr2[" << i << "]=" << *dq_iter << endl;
	}
	return 0;
}
