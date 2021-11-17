#include <vector>
#include <iostream>
#include <sstream>

/*
 * leetcode: 557. 反转字符串中的单词 III
 * 给定一个字符串，你需要反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。
 * 示例：
 * 输入："Let's take LeetCode contest"
 * 输出："s'teL ekat edoCteeL tsetnoc"

 * 提示：
 * 在字符串中，每个单词由单个空格分隔，并且字符串中不会有任何额外的空格。
 */

using namespace std;

class Solution {
public:
  string reverseWords(string s) {
    string out;
    int begin = 0;
    int size = s.size();
    for (int i=0; i<size; i++) {
      if (s[i] != ' ') {
        continue;
      }

      reverseString(out, s, begin, i-1);
      begin = i+1;
      out.push_back(s[i]);
    }
    reverseString(out, s, begin, size-1);

    return out;
  }

  void reverseString(string &out, const string &s, int begin, int end) {
    if (begin > end) {
      return;
    }
    for (int i= end; i>=begin; i--) {
      out.push_back(s[i]);
    }
  }
};

std::string vectorToString(vector<string> nums) {
  std::ostringstream out;
  out << "{";
  for (auto it = nums.begin(); it!= nums.end(); it++) {
    if (it != nums.begin()) {
      out << ", ";
    }
    out << *it;
  }
  out << "}";
  return out.str();
}

int main() {
  Solution solution;
  vector<string> data {
                       "Let's take LeetCode contest",
                       "hello sunday, ",
                       " hello sunday , ",
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    string &item = *it;
    cout << "solution.reverseWords(\"" << item << "\")";
    auto result = solution.reverseWords(item);
    cout << ", result:\"" << result << "\"" << endl;
  }
  return 0;
}
