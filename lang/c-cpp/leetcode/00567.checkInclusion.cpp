#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>

/*
 * leetcode: 567. 字符串的排列
 * 给你两个字符串 s1 和 s2 ，写一个函数来判断 s2 是否包含 s1 的排列。如果是，返回 true ；否则，返回 false 。
 * 换句话说，s1 的排列之一是 s2 的 子串 。
 */

using namespace std;

std::string mapToString(const unordered_map<char, int> &m);

class Solution {
public:
  bool checkInclusion(string s1, string s2) {
    int m = s1.size();
    int n = s2.size();
    if (m > n) {
      return false;
    }
    unordered_map<char, int> mapM;
    for (int i=0; i<m; i++) {
      mapM[s1[i]]--;
    }
    int left = 0;
    for (int j=0; j<n; j++) {
      char x = s2[j];
      mapM[x]++;
      while (mapM[x] > 0) {
        mapM[s2[left]]--;
        left++;
      }
      if (j - left +1 == m) {
        return true;
      }
    }
    return false;
  }

  bool zeroMap(const unordered_map<char, int> &m) {
    cout << "    + m:" << mapToString(m) << endl;
    if (m.size() == 0) {
      return true;
    }
    for (auto it = m.cbegin(); it != m.cend(); it++) {
      if (it->second != 0) {
        return false;
      }
    }
    return true;
  }
};

std::string mapToString(const unordered_map<char, int> &m) {
  ostringstream out;
  out << "{";
  for (auto it = m.cbegin(); it!= m.cend(); it++) {
    if (it != m.cbegin()) {
      out << ", ";
    }
    out << it->first << ":" << it->second;
  }
  out << "}";
  return out.str();
}

struct vectorItem {
  string str1;
  string str2;
};

int main() {
  Solution solution;
  vector<vectorItem> data {
                           {"ab", "eidbaooo"},
                           {"ab", "eidboaoo"},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    vectorItem &item = *it;
    cout << "solution.reverseWords(\"" << item.str1 << "\", \"" << item.str2 << "\")" << endl;
    auto result = solution.checkInclusion(item.str1, item.str2);
    cout << ", result:" << result << "" << endl;
  }
  return 0;
}
