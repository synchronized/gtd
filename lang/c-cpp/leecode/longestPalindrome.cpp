#include <iostream>
#include <vector>

/*
 * leetcode: 5. 最长回文子串
 * 给你一个字符串 s，找到 s 中最长的回文子串。
 * 输入：s = "babad"
 * 输出："bab"
 * 解释："aba" 同样是符合题意的答案。
 * 示例 2：

 * 输入：s = "cbbd"
 * 输出："bb"
 * 示例 3：

 * 输入：s = "a"
 * 输出："a"
 * 示例 4：

 * 输入：s = "ac"
 * 输出："a"
 */
using namespace std;

class Solution {
public:
  string longestPalindrome(string s) {
    int start = 0;
    int maxlength = 0;
    int n = s.size();
    for (int i=0; i<n;) {
      if (maxlength-i < maxlength/2) break;
      int left = i, right = i;
      while (right < n-1 && s[right] == s[right+1]) right++;
      i = right + 1;
      while (left > 0 && right < n-1 && s[left-1] == s[right+1]) {
        left--;
        right++;
      }
      if (maxlength < right-left+1) {
        start = left;
        maxlength = right-left+1;
      }
    }
    return s.substr(start, maxlength);
  }
};


struct solutionItem {
   string str;
};

int main() {
  Solution solution;
  vector<solutionItem> data {
                             {"babad"},
                             {"cbbd"},
                             {"a"},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    cout << "solution.reverseWords(\"" << item.str << "\")";
    auto result = solution.longestPalindrome(item.str);
    cout << ", result:\"" << result << "\"" << endl;
  }
  return 0;
}
