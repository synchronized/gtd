//: Stack.h
//

template<class T>
class Stack{
	public:
		class Element{
			public:
				Element( T * dt, Element * nxt);
				T * getData();
				Element * getNext();
				~Element();
			private:
				Element * next;
				T * data;
		};
		Stack();
		void push( T * dt);
		T * pop();
		T * peek();
		int size();
	private:
		Element * head;
		int _size;
};
