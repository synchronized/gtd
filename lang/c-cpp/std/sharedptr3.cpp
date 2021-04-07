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

int main() {
    std::shared_ptr<Foo> f1(new Foo("foo1"));
    std::shared_ptr<Foo> f2(new Foo("foo2"));

    f1 = f2;
    return 0;
}
