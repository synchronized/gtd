#include <iostream>
#include <string>

//测试字符串初始化
void test_string_init() {
    std::string s1;       //默认初始化
    std::string s2(s1);   // s2是s1的副本
    std::string s3 = s1;  //等价于s3(s1),s3是s1的副本
    // s4是字面值"value"的副本，除了字面值最后的那个空字符外，直接初始化
    std::string s4("value");
    //等价于s5("value"),s5是字面值"value"的副本,拷贝初始化
    std::string s5 = "value";
    //把s6初始化为由连续10个字符c组成的串，直接初始化
    std::string s6(10, 'c');

    std::cout << "s1             : " << s1 << std::endl;
    std::cout << "s2(s1)         : " << s2 << std::endl;
    std::cout << "s3 = s1        : " << s3 << std::endl;
    std::cout << "s4(\"value\")    : " << s4 << std::endl;
    std::cout << "s5 = \"value\"   : " << s5 << std::endl;
    std::cout << "s6(10, 'c')    : " << s6 << std::endl;
}

int main() {
    test_string_init();
    return 0;
}
