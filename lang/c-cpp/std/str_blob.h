#include <initializer_list>
#include <memory>
#include <string>
#include <vector>

#ifndef _STR_BLOB_H_
#define _STR_BLOB_H_

class StrBlobPtr;

class StrBlob {
    friend class StrBlobPtr;

   public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    //接受一个列表初始化的构造函数将其参数传递给对应的vector构造函数
    StrBlob(std::initializer_list<std::string> il);
    //此构造函数通过拷贝列表中的值来初始化vector中的元素
    // C++11允许构造函数和其他函数把初始化列表当做参数
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    //添加和删除元素
    void push_back(const std::string& t) { data->push_back(t); }
    void pop_back();
    //元素访问
    std::string& front();
    std::string& back();
    void print() const;

    StrBlobPtr begin();
    StrBlobPtr end();

   private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string& msg) const;
};

#endif  //_STR_BLOB_H_
