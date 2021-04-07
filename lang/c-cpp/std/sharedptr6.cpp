#include <str_blob_ptr.h>
#include <iostream>

int main() {
    std::cout << "begin ================" << std::endl;
    StrBlob sb{"a", "b", "c", "d"};

    std::cout << "StrBlob(sb)";
    auto sb_begin = sb.begin();
    for (size_t i=0; i<sb.size(); ++i) {
      std::cout << " " << sb_begin.deref();
      sb_begin.incr();
    }
    std::cout << std::endl;
    std::cout << "end ================" << std::endl;
    return 0;
}
