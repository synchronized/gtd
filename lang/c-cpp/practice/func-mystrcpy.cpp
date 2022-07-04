#include <iostream>
using namespace std;

int strcpy(const char* input, char* output, int i_size);

int strcpy(const char* input, char* output, int i_size) {
	int r_size = 0;
	for( int i=0; i< i_size; i++) {
		cout << static_cast<int>(input[i]) << endl;
		output[i] = input[i];
	}
	return r_size;
}

int main() {
	char input[100];
	char output[100];
	int i_size = 0;
	cout << "input chars:";
	cin >> input;
	cout << "input char length:";
	cin >> i_size;

	strcpy(input, output, i_size);
	return 0;
}
