#include <iostream>
#include <vector>

/*
 * leetcode: 4. 寻找两个正序数组的中位数
 * 给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。
 */
using namespace std;

std::string vectorToString(vector<int> nums);

//合并数组求中位数
class Solution {
public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size()+nums2.size() <= 0) {
      return 0;
    }
    vector<int> nums(0, nums1.size()+nums2.size());
    int p1 = 0;
    int p2 = 0;
    int m = nums1.size();
    int n = nums2.size();
    while (p1<m && p2<n) {
      if (nums1[p1] > nums2[p2]) {
        nums.push_back(nums2[p2]);
        p2++;
      } else {
        nums.push_back(nums1[p1]);
        p1++;
      }
    }
    for (;p1<m;p1++) {
      nums.push_back(nums1[p1]);
    }
    for (;p2<n;p2++) {
      nums.push_back(nums2[p2]);
    }
    int mid = nums.size() / 2;
    if (nums.size()%2 == 1) {
      return static_cast<double>(nums[mid]);
    }
    return (static_cast<double>(nums[mid-1])+static_cast<double>(nums[mid]))/2;
  }
};

//直接求中位数下标
class Solution1 {
public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int totallen = nums1.size()+nums2.size();
    if (totallen <= 0) {
      return 0;
    }
    int p1 = 0;
    int p2 = 0;
    int i = 0;
    int m = nums1.size();
    int n = nums2.size();
    int midbegin = totallen / 2;
    int midend = midbegin;
    if (totallen%2 == 0) {
      midbegin--;
    }
    double result[2];
    for (; i<=midend; i++) {
      int num = 0;
      do {
        if (p1 >= m) {
          num = nums2[p2];
          p2++;
          break;
        }
        if (p2 >= n) {
          num = nums1[p1];
          p1++;
          break;
        }
        if (nums1[p1] > nums2[p2]) {
          num = nums2[p2];
          p2++;
        } else {
          num = nums1[p1];
          p1++;
        }
      } while(0);

      if (i == midbegin) {
        result[0] = static_cast<double>(num);
      }
      if (i == midend) {
        result[1] = static_cast<double>(num);
      }
    }
    return (result[0]+result[1])/2;
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
  vector<int> nums1;
  vector<int> nums2;
};

int main() {
  Solution1 solution;
  vector<solutionItem> data {
                             {{1,3}, {2}},
                             {{1,2}, {3,4}},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    cout << "solution.reverseWords(" << vectorToString(item.nums1) << ", " << vectorToString(item.nums2) << ")" << endl;
    auto result = solution.findMedianSortedArrays(item.nums1, item.nums2);
    cout << ", result:" << result << "" << endl;
  }
  return 0;
}
