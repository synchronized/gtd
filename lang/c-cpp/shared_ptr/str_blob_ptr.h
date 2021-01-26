#include <string>
#include <memory>
#include <vector>
#include <str_blob.h>

#ifndef _STR_BLOB_PTR_H_
#define _STR_BLOB_PTR_H_

class StrBlobPtr {
public:
  StrBlobPtr():curr(0){}
  StrBlobPtr(StrBlob& a,size_t sz =0):wptr(a.data),curr(sz){}
  std::string& deref() const;
  StrBlobPtr& incr();
private:
  //若检查成功，check返回一个指向vector的shared_ptr
  std::shared_ptr<std::vector<std::string>> check(size_t, const std::string&) const;
  //保存一个weak_ptr，意味着低层vector可能会被销毁
  std::weak_ptr<std::vector<std::string>> wptr;
  size_t curr;//数组中当前的位置
};


#endif //_STR_BLOB_PTR_H_
