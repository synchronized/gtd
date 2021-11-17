#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_set>

/*
 * leetcode: 3. 无重复字符的最长子串
 * 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
 */

using namespace std;

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    int m = s.size();
    int result = 0;
    int j = 0;
    unordered_set<char> occ;
    for (int i=0; i<m; i++) {
      if (i > 0) {
        occ.erase(s[i-1]);
      }
      for (; j<m; j++) {
        if (occ.count(s[j]) > 0) {
          break;
        }
        occ.insert(s[j]);
      }
      result = max(result, j-i);
    }
    return result;
  }
};

std::string vectorToString(vector<int> nums) {
  std::string buf = "{";
  for (auto it = nums.begin(); it!= nums.end(); it++) {
    if (it != nums.begin()) {
      buf += ", ";
    }
    buf += std::to_string(*it);
  }
  buf += "}";
  return buf;
}

struct vectorItem {
  string str;
};

int main() {
  Solution solution;
  vector<vectorItem> data {
                           {"abcabcbb"},
                           {"bbbbba"},
                           {"pwwkew"},
                           {"dvdf"},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    vectorItem &item = *it;
    cout << "solution.reverseWords(\"" << item.str << "\")";
    auto result = solution.lengthOfLongestSubstring(item.str);
    cout << ", result:" << result << "" << endl;
  }
  return 0;
}
