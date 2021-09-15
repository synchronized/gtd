#include <iostream>
#include <vector>
#include <map>

/*
 * leetcode: 6. Z 字形变换
 * 将一个给定字符串 s 根据给定的行数 numRows ，以从上往下、从左到右进行 Z 字形排列。
 *
 * 比如输入字符串为 "PAYPALISHIRING" 行数为 3 时，排列如下：

 */
using namespace std;

//中心扩散
class Solution {
public:
  string convert(string s, int numRows) {
    if (numRows < 2) {
      return s;
    }
    int n = s.size();
    string result;
    int step = numRows -2 + numRows -1 +1;
    for (int i=0; i<numRows; i++) {
      for (int j=i; j<n; j+=step) {
        result.push_back(s[j]);
        int next = j+step-2*i;
        if (i>0 && i<numRows-1 && next>0 && next<n) {
          result.push_back(s[next]);
        }
      }
    }
    return result;
  }
};


struct solutionItem {
  string str;
  int numRows;
};

int main() {
  Solution solution;
  vector<solutionItem> data {
                             {"a", 1},
                             {"PAYPALISHIRING", 2},
                             {"PAYPALISHIRING", 3},
                             {"PAYPALISHIRING", 4},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    cout << "solution.convert(\"" << item.str << "\", " << item.numRows << ")";
    auto result = solution.convert(item.str, item.numRows);
    cout << ", result:\"" << result << "\"" << endl;
  }
  return 0;
}
