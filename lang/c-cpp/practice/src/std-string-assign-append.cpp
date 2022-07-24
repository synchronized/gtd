#include <iostream>
#include <string>

using namespace std;

int main() {
	string q1("When lilacs last in the dooryard bloom'd");
	string q2("The child is father of the man");
	string sentence;

	sentence.assign(q2, 0, 13);
	sentence.append(q1, 17, 15);
	cout << sentence << endl;
	//string sentence("The child is in the dooryard");
	return 0;
}
