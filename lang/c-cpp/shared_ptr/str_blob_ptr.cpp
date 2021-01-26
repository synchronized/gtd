#include <str_blob_ptr.h>

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(
    size_t i, const std::string& msg) const {
    auto ret = wptr.lock();
    if (!ret) throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size()) throw std::out_of_range(msg);
    return ret;
}

std::string& StrBlobPtr::deref() const {
    auto sp = check(curr, "derefence pass end of StrBlobPtr");
    return (*sp)[curr];
}

StrBlobPtr& StrBlobPtr::incr() {
    check(curr, "increment pass end of StrBlobPtr");
    ++curr;
    return *this;
}
