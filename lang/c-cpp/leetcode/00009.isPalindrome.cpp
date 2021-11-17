#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>

/*
 * leetcode: 9. 回文数
 * 给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false 。
 * 回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。例如，121 是回文，而 123 不是。
 */

using namespace std;

//中心扩散
class Solution {
public:
  bool isPalindrome(int x) {
    if (x < 0 || (x%10==0 && x!=0)) {
      return false;
    }

    int r = 0;
    while(x > r) {
      r = r*10 + x%10;
      x /= 10;
    }
    cout << "    r:" << r << ", x:" << x;
    return x == r || x == r/10;
  }
};

struct solutionItem {
  int x;
};

int main() {
  Solution solution;
  vector<solutionItem> data {
                             {121},
                             {-121},
                             {123},
                             {1234567899},
                             {10},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    cout << "solution.isPalindrome(" << item.x << ")" << endl;
    auto result = solution.isPalindrome(item.x);
    cout << ", result:" << result << "" << endl;
  }
  return 0;
}
