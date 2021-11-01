#include <vector>
#include <iostream>
#include <queue>

using namespace std;

class Solution {
public:
  const int dirx[4]{0, 1, 0, -1};
  const int diry[4]{1, 0, -1, 0};
  int maxAreaOfIsland(vector<vector<int>>& grid) {
    int row = grid.size();
    int col = grid[0].size();
    int result = 0;
    for (int i=0; i<row; i++) {
      for (int j=0; j<col; j++) {
        if (!grid[i][j]) {
          continue;
        }
        int area = 1;
        queue<pair<int,int>> st;
        st.push(make_pair(i,j));
        grid[i][j] = 0;
        while(!st.empty()) {
          int x = st.front().first;
          int y = st.front().second;
          st.pop();

          for (int k=0; k<4; k++) {
            int mx = x+dirx[k];
            int my = y+diry[k];
            if (mx>=0 && mx<row && my>=0 && my<col && grid[mx][my]) {
              grid[mx][my] = 0;
              st.push(pair<int,int>(mx, my));
              area++;
            }
          }
        }
        result = max(result, area);
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

std::string vector2ToString(vector<vector<int>> &nums2) {
  std::string buf = "{\n";
  for (auto it = nums2.begin(); it != nums2.end(); it++) {
    if (it != nums2.begin()) {
      buf += ", \n";
    }
    buf += vectorToString(*it);
  }
  buf += "}";
  return buf;
}

struct solutionItem {
  vector<vector<int>> grid;
};


int main() {
  Solution solution;
  vector<solutionItem> data {
                             {{{0,0,1,0,0,0,0,1,0,0,0,0,0},
                               {0,0,0,0,0,0,0,1,1,1,0,0,0},
                               {0,1,1,0,1,0,0,0,0,0,0,0,0},
                               {0,1,0,0,1,1,0,0,1,0,1,0,0},
                               {0,1,0,0,1,1,0,0,1,1,1,0,0},
                               {0,0,0,0,0,0,0,0,0,0,1,0,0},
                               {0,0,0,0,0,0,0,1,1,1,0,0,0},
                               {0,0,0,0,0,0,0,1,1,0,0,0,0}}},
                             {{{0,0,0,0,0,0,0,0}}},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    cout << "solution.maxAreaOfIsland(" << vector2ToString(item.grid) << ")" ;
    auto result = solution.maxAreaOfIsland(item.grid);
    cout << ", result:" << result << endl;
  }
  return 0;
}
