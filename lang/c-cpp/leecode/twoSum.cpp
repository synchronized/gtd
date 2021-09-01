#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int>& numbers, int target) {
    vector<int> result{0, 0};
    int left = 0;
    int right = numbers.size() - 1;
    while (left < right) {
      if (numbers[left] + numbers[right] == target) {
        result = {left+1, right+1};
        return result;
      }
      if (numbers[left] + numbers[right] > target) {
        right--;
      } else {
        left++;
      }
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

struct solutionItem {
  vector<int> numbers;
  vector<int> result;
  int target;
};


int main() {
  Solution solution;
  vector<solutionItem> data {
                             {{2,7,10,15}, {1,2}, 9},
                             {{1,2,3,4}, {1,4}, 5},
                             {{1,3,5,7}, {1,3}, 6},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    cout << "solution.twoSum(" << vectorToString(item.numbers) << "), target:" << item.target;
    auto result = solution.twoSum(item.numbers, item.target);
    cout << ", result:" << vectorToString(result) << ", origResult:" << vectorToString(item.result) << endl;
  }
  return 0;
}
