#include <iostream>
#include <memory>
#include <assert.h>

class Resource {
public:
  Resource(int i):mInt(i){}
  void someMethod() {
    std::cout << "someMethod" << std::endl;
  }
private:
  int mInt;
};

int main() {
  std::shared_ptr<int> x = std::shared_ptr<int>(new int);
  std::shared_ptr<int> y = std::make_shared<int>();
  std::shared_ptr<Resource> obj = std::make_shared<Resource>(1);

  //赋值
  std::shared_ptr<int> z = x; //此时z和x共享同一个引用计数器
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
