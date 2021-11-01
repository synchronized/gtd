#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
  int searchInsert(vector<int>& nums, int target) {
    int begin = 0;
    int end = nums.size();
    do {
      int mid = begin + (end - begin)/2;
      cout << "mid:" << mid << ",begin:" << begin << ", end:" << end << endl;
      //if (target == nums[mid]) {
      //  return mid;
      //}
      if (target > nums[mid]) {
        begin = mid + 1;
      } else {
        end = mid;
      }
    } while (begin < end);
    return begin;
  }
};

int main() {
  Solution solution;
  vector<int> nums {1,3,5,6};
  int idx = solution.searchInsert(nums, 0);
  cout << "solution.searchInsert():" << idx << endl;
  return 0;
}
