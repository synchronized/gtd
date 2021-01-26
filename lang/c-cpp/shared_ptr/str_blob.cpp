#include <str_blob.h>
#include <str_blob_ptr.h>
#include <iostream>

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}
StrBlob::StrBlob(std::initializer_list<std::string> il)
    : data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlob::pop_back() {
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

std::string& StrBlob::front() {
    check(0, "front on empty StrBlob");
    return data->front();
}

std::string& StrBlob::back() {
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::check(size_type i, const std::string& msg) const {
    if (i >= data->size()) {
        throw std::out_of_range(msg);
    }
}

void StrBlob::print() const {
    std::cout << "StrBlob:";
    auto it = data->cbegin();
    for (; it != data->cend(); ++it) {
        std::cout << " " << *it;
    }
    std::cout << std::endl;
}

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end() {
    auto ret = StrBlobPtr(*this, data->size());
    return ret;
}
