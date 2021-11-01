#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <climits>

/*
 * leetcode: 11. 盛最多水的容器
 *
 * 给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点(i,ai) 。
 * 在坐标内画 n 条垂直线，垂直线 i的两个端点分别为(i,ai) 和 (i, 0) 。找出其中的两条线，使得它们与x轴共同构成的容器可以容纳最多的水。
 *
 * 示例 1：
 * 输入：[1,8,6,2,5,4,8,3,7]
 * 输出：49
 * 解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
 *
 * 示例 2：
 * 输入：height = [1,1]
 * 输出：1
 *
 * 示例 3：
 * 输入：height = [4,3,2,1,4]
 * 输出：16
 *
 * 示例 4：
 * 输入：height = [1,2,1]
 * 输出：2
 *
 * 提示：
 *     n == height.length
 *     2 <= n <= 105
 *     0 <= height[i] <= 104
 */
using namespace std;

class Solution {
public:
  int maxArea(vector<int>& height) {
    if (height.size() < 2) {
      return 0;
    }
    int i = 0;
    int j = height.size()-1;
    int result = 0;
    while(i < j) {
      int h = min(height[i], height[j]);
      int w = j - i;
      int area = h*w;
      if (area > result) {
        result = area;
      }
      if (height[i] > height[j]) {
        j--;
      } else {
        i++;
      }
    }
    return result;
  }
};

std::string vectorToString(vector<int> &nums) {
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
  vector<int> s;
  int result;
};

int main() {
  Solution solution;
  vector<solutionItem> data {
                             {{1,8,6,2,5,4,8,3,7}, 49},
                             {{1,1}, 1},
                             {{4,3,2,1,4}, 16},
                             {{1,2,1}, 2},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    cout << "solution.maxArea(" << vectorToString(item.s) << ")" << endl;
    auto result = solution.maxArea(item.s);
    cout << ", result:" << result << ", " << item.result << endl;
  }
  return 0;
}
