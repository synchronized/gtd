#include "Video.h"
#include "Stack.h"

int main() {
	Stack<Video> stack;
	Video * v1 = new Video("v1");
	Video * v2 = new Video("v2");
	stack.push( v1);
	stack.push( v2);

	stack.pop()->print();
	stack.pop()->print();
	return 0;
}
