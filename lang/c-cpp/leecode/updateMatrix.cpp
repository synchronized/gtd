#include <vector>
#include <iostream>
#include <queue>

//542. 01 矩阵
//给定一个由 0 和 1 组成的矩阵 mat ，请输出一个大小相同的矩阵，其中每一个格子是 mat 中对应位置元素到最近的 0 的距离。
//两个相邻元素间的距离为 1 。

using namespace std;

class Solution {
public:
  const int dirx[4]{0, 1, 0, -1};
  const int diry[4]{1, 0, -1, 0};
  vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
    //TODO
    int m = mat.size();
    int n = mat[0].size();
    for (int i=0; i<m; i++) {
      for (int j=0; j<n; j++) {
        if (mat[i][j]) {
        }
      }
    }
    return mat;
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

std::string vector2ToString(vector<vector<int>> &nums2) {
  std::string buf = "{";
  for (auto it = nums2.begin(); it != nums2.end(); it++) {
    if (it != nums2.begin()) {
      buf += ", ";
    }
    buf += vectorToString(*it);
  }
  buf += "}";
  return buf;
}

struct solutionItem {
  vector<vector<int>> mat;
};


int main() {
  Solution solution;
  vector<solutionItem> data {
                             {{{0,0,0},{0,1,0},{0,0,0}}},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    cout << "solution.updateMatrix(" << vector2ToString(item.mat) << ")" << endl ;
    auto result = solution.updateMatrix(item.mat);
    cout << ", result:" << vector2ToString(result) << endl;
  }
  return 0;
}
