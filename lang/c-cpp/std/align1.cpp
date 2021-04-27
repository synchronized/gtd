#include <iostream>
#include <string>

#define PACKED //__attribute__( ( packed, aligned(2) ) )

struct Person1 {
  char a;
  char b;
  char c;
  char d;
} PACKED;

struct Person2 {
  char a;
  short b;
  char c;
  char d;
} PACKED;

int main() {
  struct Person1 p1;
  struct Person2 p2;
  std::cout << "sizeof(personal1):" << sizeof(p1) << std::endl;
  std::cout << "sizeof(personal2):" << sizeof(p2) << std::endl;
  std::cout << "&p2:" << (void*)&p2
            << ", &p2.a:" << (void*)&(p2.a)
            << ", &p2.b:" << (void*)&(p2.b)
            << ", &p2.c:" << (void*)&(p2.c)
            << ", &p2.d:" << (void*)&(p2.d)
            << std::endl;
  return 0;
}
