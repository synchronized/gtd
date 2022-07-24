// : practice-05-09/main.cpp

#include <iostream>
#include <string>
#include <cassert>
#include <cstring>

using namespace std;

class Hen{
	string name;
public:
	Hen( string name_):name(name_){}
	void print() {
		cout << "Hen.name:" << name << endl;
	}
	string getName() {
		return name;
	}
};

class Mem{
    void ensureMinSize(int minSize) {
        if( _size < minSize) {
            byte* b = new byte[minSize];
            memset( b + _size, 0, minSize - _size);
            memcpy( b, _mem, _size);
            delete [] _mem;
            _mem = b;
            _size = minSize;
        }
    }
public:
    Mem(): _mem(nullptr), _size(0) {
    }
    Mem( int sz): _mem(nullptr), _size(0) {
        ensureMinSize(sz);
    }
    ~Mem(){delete [] _mem;}
	int size() {return _size;}
    byte* pointer() {return _mem;}
    byte* pointer(int minSize) {
        ensureMinSize( minSize);
        return _mem;
    }
private:
	byte* _mem;
	int _size;
};

const int increase = 100;
class Stash{
	int size;	// Size of each element space
	int quantity;	// Number of storage spaces
	int next;	// Next empty space
	// Dynamically allocated array of bytes:
	unsigned char* storage;
	Mem mem;
	void inflate(int increase) {
        assert( increase > 0);
        int newQuantity = quantity + increase;
        int newBytes = newQuantity * size;
        int oldBytes = quantity * size;
        unsigned char * b = new unsigned char[newBytes];
        for(int i = 0; i < next * size; i++) {
            b[i] = storage[i];
        }
        delete [] storage;
        storage = b;
        quantity = newQuantity;
    }
public:
    void initialize(int sz) {
        size = sz;
        quantity = 0;
        next = 0;
        storage = 0;
    }
    void cleanup() {
        delete [] storage;
        quantity = 0;
        next = 0;
        storage = 0;
        std::cout << "delete [] storage" << std::endl;
        std::cout << "storage addr:" << static_cast<const void*>(storage) << std::endl;
    }
    int add(void * element) {
        if( next >= quantity) {
            inflate( increase);
        }
        unsigned char * b = reinterpret_cast<unsigned char *>(element);
        int startIndex = next * size;
        for( int i = 0; i < size; i++) {
            storage[startIndex + i] = b[i];
        }
        next++;
        return (next - 1);
    }
    void * fetch(int index) {
        assert( index >= 0);
        if( index >= next) {
            return 0;
        }
        return (storage + index * size);
    }
    int count() {
        return next;
    }
};

int main() {
	Stash s;
	Hen h1("h1"), h2("h2"), h3("h3"), h4("h4");
	s.initialize( sizeof(Hen));
	cout << "Stash.add( h1) index:" <<s.add(static_cast<void *>(&h1)) << endl;
	cout << "Stash.add( h2) index:" <<s.add(static_cast<void *>(&h2)) << endl;
	cout << "Stash.add( h3) index:" <<s.add(static_cast<void *>(&h3)) << endl;
	cout << "Stash.add( h4) index:" <<s.add(static_cast<void *>(&h4)) << endl;
	for(int i = 0; i < s.count(); i++) {
		Hen *h =  reinterpret_cast<Hen *>(s.fetch(i));
		cout << "Stash.fetch(" << i << ")=" << h->getName() << endl;
		h->print();
	}
	s.cleanup();
}
