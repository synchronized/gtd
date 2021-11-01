#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
  vector<int> sortedSquares(vector<int>& nums) {
    vector<int> result(nums.size());
    int left = 0;
    int right = nums.size()-1;
    for (int i = right; i >= 0; i--) {
      int p = right;
      if (-nums[left] > nums[right]) {
        p = left;
        left++;
      } else {
        right--;
      }
      result[i] = nums[p]*nums[p];
    }
    return result;
  }
};

std::string vectorToString(vector<int> nums) {
  std::string buf = "{";
  for (auto it = nums.begin(); it!= nums.end(); it++) {
    buf += ", " + std::to_string(*it);
  }
  buf += "}";
  return buf;
}

int main() {
  Solution solution;
  vector<int> nums;
  nums = {-7,-4,-3,0,1,3,5,6};
  cout << "solution.sortedSquares(" << vectorToString(nums) << "):" <<
    vectorToString(solution.sortedSquares(nums)) << endl;
  nums = {1,3,5,6};
  cout << "solution.sortedSquares(" << vectorToString(nums) << "):" <<
    vectorToString(solution.sortedSquares(nums)) << endl;
  nums = {-9,-3,-1,0};
  cout << "solution.sortedSquares(" << vectorToString(nums) << "):" <<
    vectorToString(solution.sortedSquares(nums)) << endl;
  return 0;
}
