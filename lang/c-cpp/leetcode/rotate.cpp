#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
  void rotate(vector<int>& nums, int _k) {
    vector<int>::size_type k = _k;
    if (k <=0 || k >= nums.size()) {
      return;
    }
    int kvalue = nums[k];
    vector<int>::size_type j = k;
    int lastj;
    for (vector<int>::size_type idx = 0; idx < nums.size(); idx++) {
      int next = j-k;
      if (next < 0) next += nums.size();
      nums[j] = nums[next];
      lastj = j;
      j = next;
    }
    nums[lastj] = kvalue;
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

struct dataItem {
  vector<int> nums;
  int k;
};

int main() {
  Solution solution;
  vector<dataItem> dataList = {
                               {{1,2,3,4,5,6,7,8}, 1},
                               {{1,2,3,4,5,6}, 2},
                               {{1,2,3,4,5,6,7}, 3},
                               {{1,2,3,4,5,6,7}, 4},
                               {{1,2,3,4,5,6,7}, 7},
                               {{1,2,3,4,5,6,7}, 0},
                               {{1,2,3,4,5,6,7}, -1},
  };
  for (auto it = dataList.begin(); it != dataList.end(); it++) {
    cout << "solution.rotate(" << vectorToString((*it).nums) << "," << (*it).k << "):";
    solution.rotate((*it).nums, (*it).k);
    cout << vectorToString((*it).nums) << endl;
  }
  return 0;
}
