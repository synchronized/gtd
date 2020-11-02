#include <iostream>
#include <memory>
#include <assert.h>

using namespace std;

class Resource {
public:
    Resource(int i):mInt(i){}
    void someMethod() {
        cout << "someMethod" << endl;
    }
private:
    int mInt;
};

int main() {
    shared_ptr<int> x = shared_ptr<int>(new int);
    shared_ptr<int> y = make_shared<int>();
    shared_ptr<Resource> obj = make_shared<Resource>(1);

    //赋值
    shared_ptr<int> z = x; //此时z和x共享同一个引用计数器
    //想普通指针一样使用
    int val = *x;
    assert(x == z);
    assert(y != z);
    assert(x != nullptr);
    obj->someMethod();

    //其他辅助操作
    x.swap(z); //交换两个shared_ptr管理的裸指针(当然,包含他们的引用计数)
    obj.reset(); //重置该shared_ptr(引用计数减一)
}
