#include <vector>
#include <iostream>
#include <queue>

//21. 合并两个有序链表

using namespace std;

/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    ListNode *result = nullptr;
    ListNode **cur = &result;
    while(l1 && l2) {
      ListNode **next = l1->val < l2->val ? &l1 : &l2;
      *cur = *next;
      *next = (*next)->next;
      cur = &(*cur)->next;
    }
    *cur = l1 ? l1 : l2;
    return result;
  }
};

ListNode* vectorToList(vector<int> &nums) {
  int l = nums.size();
  ListNode *result = nullptr;
  ListNode **curr = &result;
  for (int i=0; i<l; i++) {
    *curr = new ListNode(nums[i]);
    curr = &(*curr)->next;
  }
  return result;
}

//tree node connect
std::string listToString(ListNode *root) {
  std::string buf = "{";
  ListNode *cur = root;
  while(cur) {
    if (cur != root) {
      buf += ", ";
    }
    buf += std::to_string(cur->val);
    cur = cur->next;
  }
  buf += "}";
  return buf;
}

struct solutionItem {
  vector<int> l1;
  vector<int> l2;
};


int main() {
  Solution solution;
  vector<solutionItem> data {
                             {{1,3,5,7}, {2,4,6,7}},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    ListNode *l1 = vectorToList(item.l1);
    ListNode *l2 = vectorToList(item.l2);
    cout << "solution.connect(" << listToString(l1) << ", " << listToString(l2) << ")" << endl ;
    auto result = solution.mergeTwoLists(l1, l2);
    cout << ", result:" << listToString(result) << endl;
  }
  return 0;
}
