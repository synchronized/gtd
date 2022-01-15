#include "Video.h"
//#include "Stack.h"
// 如果使用上面的就会出现下面的错误
// main.o:main.cpp:(.text+0x18)：对‘Stack<Video>::Stack()’未定义的引用
// main.o:main.cpp:(.text+0xf0)：对‘Stack<Video>::push(Video*)’未定义的引用
// main.o:main.cpp:(.text+0x104)：对‘Stack<Video>::push(Video*)’未定义的引用
// main.o:main.cpp:(.text+0x110)：对‘Stack<Video>::pop()’未定义的引用
// main.o:main.cpp:(.text+0x124)：对‘Stack<Video>::pop()’未定义的引用
#include "Stack.cpp"

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
