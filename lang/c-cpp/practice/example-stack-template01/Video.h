//: Video.h

#include <string>

class Video{
	public:
		Video(std::string n):name(n) {}
		void print();
	private:
		std::string name;
};
