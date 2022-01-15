//: e0403: CppLib.h
// C-like library converted to c++

template <class T>
class Stash{
	int size;	// Size of each element
	int quantity;	// Number of storage spaces
	int next;	// Next empty space
	// Dynamically allocated array of bytes:
	unsigned char * storage;
	// Functions!
	void initialize( int size);
	void cleanup( );
	int add( const void* element);
	void* fetch( int index);
	int count();
	void inflate( int increase);
}; ///:~
