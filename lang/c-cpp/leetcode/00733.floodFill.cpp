#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>

//leetCode: 733. 图像渲染

using namespace std;

class Solution {
public:
  const int dx[4] = {1, 0, 0, -1};
  const int dy[4] = {0, 1, -1, 0};

  void dofloodFill(vector<vector<int>>& image, int sr, int sc, int newColor, int oldColor) {
    if (image[sr][sc] != oldColor) {
      return;
    }
    image[sr][sc] = newColor;
    for (int i=0; i<4; i++) {
      int mr = sr+dx[i];
      int mc = sc+dy[i];
      if (mr>=0 && mr<image.size() && mc >=0 && mc < image[0].size()) {
        dofloodFill(image, mr, mc, newColor, oldColor);
      }
    }
  }

  vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
    int oldColor = image[sr][sc];
    if (newColor != oldColor) {
      dofloodFill(image, sr, sc, newColor, oldColor);
    }
    return image;
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


struct vectorItem {
  vector<vector<int>> image;
  int sr;
  int sc;
  int newColor;
};

int main() {
  Solution solution;
  vector<vectorItem> data {
                           {{{1,1,1},{1,1,0},{1,0,1}}, 1, 1, 2},
                           {{{0,0,0},{0,1,1}}, 1, 1, 1},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    vectorItem &item = *it;
    cout << "solution.floodFill("
         << vector2ToString(item.image) << ", "
         << item.sr << ", " << item.sc << "," << item.newColor << ")" << endl;
    auto result = solution.floodFill(item.image, item.sr, item.sc, item.newColor);
    cout << ", result:" << vector2ToString(result) << endl;
  }
  return 0;
}
