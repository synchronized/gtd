#include <iostream>
#include <list>
#include <deque>
#include <vector>
#include <string>

using namespace std;

int main() {
	list<int> ilist;
	deque<int> ideq;
	vector<int> ivec;

	ilist.push_back(1);
	ideq.push_back(2);
	ivec.push_back(3);

	cout << "ilist.back()=" << ilist.back() << endl;
	cout << "ideq.back()=" << ideq.back() << endl;
	cout << "ivec.back()=" << ivec.back() << endl;
	cout << "-----------------------------" << endl;

	cout << "ilist.front()=" << ilist.front() << endl;
	cout << "ideq.front()=" << ideq.front() << endl;
	cout << "ivec.front()=" << ivec.front() << endl;
	cout << "-----------------------------" << endl;

	//cout << "ilist[0]=" << ilist[0] << endl; //error list not support
	cout << "ideq[0]=" << ideq[0] << endl;
	cout << "ivec[0]=" << ivec[0] << endl;
	cout << "-----------------------------" << endl;

	//cout << "ilist.at(0)=" << ilist.at(0) << endl; //error list not support
	cout << "ideq.at(0)=" << ideq.at(0) << endl;
	cout << "ivec.at(0)=" << ivec.at(0) << endl;
	cout << "-----------------------------" << endl;
	return 0;
}
