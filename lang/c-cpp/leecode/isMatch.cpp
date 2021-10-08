#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>

/*
 * leetcode: 10. 正则表达式匹配
 * 给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

 * '.' 匹配任意单个字符
 * '*' 匹配零个或多个前面的那一个元素
 * 所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。

 * 示例 1：
 * 输入：s = "aa" p = "a"
 * 输出：false
 * 解释："a" 无法匹配 "aa" 整个字符串。

 * 示例 2:
 * 输入：s = "aa" p = "a*"
 * 输出：true
 * 解释：因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。

 * 示例 3：
 * 输入：s = "ab" p = ".*"
 * 输出：true
 * 解释：".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。

 * 示例 4：
 * 输入：s = "aab" p = "c*a*b"
 * 输出：true
 * 解释：因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。

 * 示例 5：
 * 输入：s = "mississippi" p = "mis*is*p*."
 * 输出：false
 */

using namespace std;

//递归
class Solution {
public:
  bool isMatch(string s, string p) {
    return doMatch(s, 0, p, 0);
  }
  bool doMatch(string s, int i, string p, int j) {
    int lens = s.size()-i;
    int lenp = p.size()-j;
    if (lenp<=0) return lens <= 0;

    bool isFirstMatch = p[j] == '.';
    if (lens > 0) {
      isFirstMatch |= s[i] == p[j];
    }

    if (lenp >= 2 && p[j+1] == '*') {
      return doMatch(s, i, p, j+2) || (isFirstMatch && doMatch(s, i+1, p, j));
    } else {
      return isFirstMatch && doMatch(s, i+1, p, j+1);
    }
  }
};

//栈
class Solution1 {
public:
  bool isMatch(string s, string p) {
    int m = s.size();
    int n = p.size();

    auto matches = [&](int i, int j) {
                     if (i == 0) {
                       return false;
                     }
                     if (p[j-1] == '.') {
                       return true;
                     }
                     return s[i-1] == p[j-1];
                   };

    vector<vector<int>> f(m+1, vector<int>(n+1));
    f[0][0] = true;
    for (int i=0; i<=m; i++) {
      for (int j=1; j<=n; j++) {
        if (p[j-1] == '*') {
          f[i][j] |= f[i][j-2];
          if (matches(i, j-1)) {
            f[i][j] |= f[i-1][j];
          }
        } else {
          if (matches(i, j)) {
            f[i][j] |= f[i-1][j-1];
          }
        }
      }
    }
    return f[m][n];
  }
};

struct solutionItem {
  string s;
  string p;
};

int main() {
  Solution1 solution;
  vector<solutionItem> data {
                             {"pp", "p"},
                             {"pp", "p*"},
                             {"pp", "p.*"},
                             {"pp", "*"},
                             {"pp", "ppp"},
                             {"aab", "c*a*b"},
                             {"aaaaaaaaaaaaab", "a*a*a*a*a*a*a*a*a*a*c"},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    cout << "solution.isMatch(\"" << item.s << "\", \"" << item.p << "\")" << endl;
    auto result = solution.isMatch(item.s, item.p);
    cout << ", result:" << result << "" << endl;
  }
  return 0;
}
