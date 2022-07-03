#include <iostream>
using namespace std;

int main() {
	void simple_sort(int, int, int);
	int x, y, z;

    cout << "read var x:";
    cin >> x;
    cout << "read var y:";
    cin >> y;
    cout << "read var z:";
    cin >> z;

	simple_sort(x, y, z);
	return 0;
}

void simple_sort(int x, int y, int z) {
	int temp;
	if (x > y) { temp = x; x = y; y = temp;}
	if (z < x) cout <<z <<',' <<x <<',' <<y <<endl;
	else if (z < y) cout <<x <<',' <<z <<',' <<y <<endl;
	else cout <<x <<',' <<y <<',' <<z <<endl;
}
