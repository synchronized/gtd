#include <iostream>
#include <str_blob.h>

int main() {
    std::cout << "begin ================" << std::endl;
    StrBlob sb1;
    {
        StrBlob sb{"a", "b", "c", "d", "e"};
        sb1 = sb;
    }
    sb1.print();

    std::cout << "end ================" << std::endl;
    return 0;
}
