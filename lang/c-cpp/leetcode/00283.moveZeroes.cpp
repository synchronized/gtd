#include <vector>
#include <iostream>

/*
 * leetcode: 283. 移动零
 * 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
 */

using namespace std;

class Solution {
public:
  void moveZeroes(vector<int>& nums) {
    vector<int>::size_type i = 0, j = 0;
    for (i=0; i<nums.size(); i++) {
      if (nums[i] == 0) {
        continue;
      }
      if (i != j) {
        nums[j] = nums[i];
      }
      j++;
    }
    for (; j<nums.size(); j++) {
      nums[j] = 0;
    }
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

int main() {
  Solution solution;
  vector<vector<int>> data {
                          {1,2,3,4},
                          {0,1,2,3,4},
                          {0,1,0,2,3,4},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    vector<int> nums = *it;
    cout << "solution.moveZeroes(" << vectorToString(nums) << "):";
    solution.moveZeroes(nums);
    cout << vectorToString(nums) << endl;
  }
  return 0;
}
