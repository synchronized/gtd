//:practice-06-08/main.cpp

#include <iostream>
#include <string>

using namespace std;

class Stack{
	struct Link{
		void* data;
		Link* next;
	public:
        Link( void* dt, Link* nxt): data(dt), next(nxt) {}
        ~Link() {}
	}* head;

public:
    Stack(): head(nullptr) {}
    ~Stack() {
        if(head != 0) {
            std::cout << "Stack::~Stack() error no empty:" << head << std::endl;
        } else {
            std::cout << "Stack::~Stack() ok" << std::endl;
        }
    }
    void push(void* data) {
        Link* next = new Link( data, head);
        head = next;
    }
    void* peek() {
        if(head == 0) {
            return 0;
        }
        return head->data;
    }
    void* pop() {
        if(head == 0) {
            return 0;
        }
        void* r = head->data;
        Link* l = head;
        head = l->next;
        delete l;
        return r;
    }
};

int main() {
	Stack s;
	string str[] = {"ZhangSan", "LiSi", "WangWu"};
	for(int i = 0; i < sizeof str / sizeof *str; i++) {
		cout << "s.push(" << str[i] << ")" << endl;
		s.push( reinterpret_cast<void*>(&(str[i])));
	}

	while( void* v = s.pop()) {
		//cout << "s.pop():" << *(reinterpret_cast<string*>(v)) << endl;
	}
	return 0;
}
