#include <iostream>

template <typename ...U>
void println(U ...u) {
    int const last_index = sizeof...(u)-1;
    int i = 0;
    auto printer = [i]<typename Arg>(Arg u) mutable {
        if (last_index != i++) std::cout << u << ", ";
        else std::cout << u << std::endl;
    };
    (printer(u), ...);
}


int main() {
    std::cout << "----------println---------" << std::endl;
    println(1, 2, 3.0, 4.5);
    return 0;
}
