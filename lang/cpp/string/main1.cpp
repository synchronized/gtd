#include <iostream>
#include <string>

//测试字符串初始化
void test_string_init() {
    std::string s1;       //默认初始化
    std::string s2(s1);   // s2是s1的副本
    std::string s3 = s1;  //等价于s3(s1),s3是s1的副本
    std::string s4(
        "value");  // s4是字面值"value"的副本，除了字面值最后的那个空字符外，直接初始化
    std::string s5 =
        "value";  //等价于s5("value"),s5是字面值"value"的副本,拷贝初始化
    std::string s6(10, 'c');  //把s6初始化为由连续10个字符c组成的串，直接初始化
}

int main() {
    test_string_init();
    return 0;
}
