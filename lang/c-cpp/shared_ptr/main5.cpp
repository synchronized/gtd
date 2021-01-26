#include <assert.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using std::string;

class Foo {
   private:
    std::string mName;

   public:
    Foo(std::string name) : mName(name) {
        std::cout << "Foo:" << mName << " created" << std::endl;
    }
    ~Foo() { std::cout << "Foo:" << mName << " destroy" << std::endl; }
};

std::unique_ptr<Foo> clone() { return std::unique_ptr<Foo>(new Foo("foo_inner")); }

int main() {
    std::unique_ptr<Foo> f1(new Foo("foo1"));
    std::unique_ptr<Foo> f2(new Foo("foo2"));

    // f1 = f2;//编译错误

    std::unique_ptr<Foo> f3 = clone();
    return 0;
}
