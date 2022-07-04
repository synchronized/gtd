#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>

using namespace std;

int main() {
	typedef vector<int>::iterator iviter;
	typedef list<int>::iterator iliter;
	typedef pair<int, string> ispair;
	map<iviter, int> map1;
	map<iliter, int> map2;
	map<ispair, int> map3;
	return 0;
}
