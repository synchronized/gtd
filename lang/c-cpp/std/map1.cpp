#include <iostream>
#include <map>
#include <string>

class Person {
public:
  char data[64];
};

int main(int argc, char* argv[]) {
  std::map<int, Person> m1;
  std::cout << "sizeof(m1): " << sizeof(m1) << ";" << std::endl;

  int i;
  for (i=0; i<10; i++) {
    m1[i] = Person();
  }
  std::cout << "sizeof(m1): " << sizeof(m1) << ";" << std::endl;
  return 0;
}
