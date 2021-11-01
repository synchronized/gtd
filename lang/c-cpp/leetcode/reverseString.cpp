#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
  void reverseString(vector<char>& s) {
    int left = 0;
    int right = s.size() - 1;
    while (left < right) {
      swap(s[left], s[right]);
      left++;
      right--;
    }
  }
};

std::string vectorToString(vector<char> nums) {
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

struct solutionItem {
  string str;
};


int main() {
  Solution solution;
  vector<solutionItem> data {
                             {"hello"},
                             {"allow"},
                             {"sunday"},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    vector<char> params(item.str.begin(), item.str.end());
    cout << "solution.reverseString(" << vectorToString(params) << ") ";
    solution.reverseString(params);
    cout << ", result:" << vectorToString(params) << endl;
  }
  return 0;
}
