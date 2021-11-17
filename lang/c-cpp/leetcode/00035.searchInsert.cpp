#include <vector>
#include <iostream>

/*
 * leetcode: 35. 搜索插入位置
 * 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
 * 请必须使用时间复杂度为 O(log n) 的算法。
 */

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
