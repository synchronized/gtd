//:practice-06-08/Stack.h

class Stack{
	struct Link{
		void* data;
		Link* next;
	public:
		Link( void* data, Link* next);
		~Link();
	}* head;
public:
	Stack();
	~Stack();
	void push( void* data);
	void* peek();
	void* pop();
};
