#include <iostream>
#include <vector>
#include <map>
#include <climits>

/*
 * leetcode: 8. 字符串转换整数 (atoi)
 * 请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32 位有符号整数（类似 C/C++ 中的 atoi 函数）。

 * 函数 myAtoi(string s) 的算法如下：

 * 读入字符串并丢弃无用的前导空格
 * 检查下一个字符（假设还未到字符末尾）为正还是负号，读取该字符（如果有）。 确定最终结果是负数还是正数。 如果两者都不存在，则假定结果为正。
 * 读入下一个字符，直到到达下一个非数字字符或到达输入的结尾。字符串的其余部分将被忽略。
 * 将前面步骤读入的这些数字转换为整数（即，"123" -> 123， "0032" -> 32）。如果没有读入数字，则整数为 0 。必要时更改符号（从步骤 2 开始）。
 * 如果整数数超过 32 位有符号整数范围 [−231,  231 − 1] ，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −231 的整数应该被固定为 −231 ，大于 231 − 1 的整数应该被固定为 231 − 1 。
 * 返回整数作为最终结果。
 * 注意：

 * 本题中的空白字符只包括空格字符 ' ' 。
 * 除前导空格或数字后的其余字符串外，请勿忽略 任何其他字符。
 */

using namespace std;

//中心扩散
class Solution {
public:
  int myAtoi(string s) {
    int result = 0;
    int unit = 1;
    int state = 0; //0:处理前导空格, 1:处理符号, 2:处理数字
    for (char c : s) {
      if (state == 0) {
        if (c == ' ') {
          continue; //忽略前导空格
        }
        state = 1;
      }
      if (state == 1) {
        state = 2;
        if (c == '-') {
          unit = -1;
          continue; //处理负号
        } else if (c == '+') {
          unit = 1;
          continue; //处理正号
        }
      }
      if (c < 48 || c > 57) {
        break; //已经到数字末尾
      }
      int d = c-48;
      if (result > INT_MAX/10 || (result == INT_MAX/10 && d > 7)) return INT_MAX;
      if (result < INT_MIN/10 || (result == INT_MIN/10 && d > 8)) return INT_MIN;
      result = result*10 + d*unit;
    }
    return result;
  }
};

struct solutionItem {
  string s;
};

int main() {
  Solution solution;
  vector<solutionItem> data {
                             {"  1234"},
                             {"00234"},
                             {"-00234"},
                             {"-00234aaa"},
                             {"-1234-"},
                             {"   2147483646abc"},
                             {"2147483647"},
                             {"2147483648"},
                             {"  -2147483647 "},
                             {"-2147483647"},
                             {"-2147483648"},
                             {"-2147483649"},
                             {"+1"},
                             {"+-12"}
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    cout << "solution.myAtoi(" << item.s << ")" << endl;
    auto result = solution.myAtoi(item.s);
    cout << ", result:" << result << "" << endl;
  }
  return 0;
}
