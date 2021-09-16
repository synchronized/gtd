#include <iostream>
#include <vector>
#include <map>
#include <climits>

/*
 * leetcode: 7. 整数反转
 * 给你一个 32 位的有符号整数 x ，返回将 x 中的数字部分反转后的结果。
 * 如果反转后整数超过 32 位的有符号整数的范围 [−231,  231 − 1] ，就返回 0。
 * 假设环境不允许存储 64 位整数（有符号或无符号）。
 */
using namespace std;

//中心扩散
class Solution {
public:
  int reverse(int x) {
    int result = 0;
    for (int y=x; y!=0; y/=10) {
      if (result > INT_MAX/10 || result < INT_MIN/10) {
        return 0;
      }
      int d = y%10;
      result = result*10+d;
    }
    return result;
  }
};

struct solutionItem {
  int x;
};

int main() {
  Solution solution;
  vector<solutionItem> data {
                             {1234},
                             {-1234},
                             {-1},
                             {2147483647},
                             {2143847412},
                             {2143847412},
                             {2147483646},
                             {2147483641},
                             {-2147483648},
                             {-2143847412},
                             {-2143847413},
                             {1463847412},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    cout << "solution.reverse(" << item.x << ")";
    auto result = solution.reverse(item.x);
    cout << ", result:\"" << result << "\"" << endl;
  }
  return 0;
}
