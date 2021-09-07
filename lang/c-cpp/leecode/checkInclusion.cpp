#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

std::string mapToString(const unordered_map<char, int> &m);

class Solution {
public:
  bool checkInclusion(string s1, string s2) {
    int m = s1.size();
    int n = s2.size();
    if (m > n) {
      return false;
    }
    unordered_map<char, int> mapM;
    int i;
    for (i=0; i<m; i++) {
      mapM[s1[i]]--;
      mapM[s2[i]]++;
    }
    if (zeroMap(mapM)) {
      return true;
    }
    for (int j=m; j<n; j++) {
      mapM[s2[j-m]]--;
      mapM[s2[j]]++;

      if (zeroMap(mapM)) {
        return true;
      }
    }
    return false;
  }

  bool zeroMap(const unordered_map<char, int> &m) {
    cout << "    + m:" << mapToString(m) << endl;
    if (m.size() == 0) {
      return true;
    }
    for (auto it = m.cbegin(); it != m.cend(); it++) {
      if (it->second != 0) {
        return false;
      }
    }
    return true;
  }
};

std::string mapToString(const unordered_map<char, int> &m) {
  ostringstream out;
  out << "{";
  for (auto it = m.cbegin(); it!= m.cend(); it++) {
    if (it != m.cbegin()) {
      out << ", ";
    }
    out << it->first << ":" << it->second;
  }
  out << "}";
  return out.str();
}

struct vectorItem {
  string str1;
  string str2;
};

int main() {
  Solution solution;
  vector<vectorItem> data {
                           {"ab", "eidbaooo"},
                           {"ab", "eidboaoo"},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    vectorItem &item = *it;
    cout << "solution.reverseWords(\"" << item.str1 << "\", \"" << item.str2 << "\")" << endl;
    auto result = solution.checkInclusion(item.str1, item.str2);
    cout << ", result:" << result << "" << endl;
  }
  return 0;
}
