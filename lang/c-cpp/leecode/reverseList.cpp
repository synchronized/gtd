#include <vector>
#include <iostream>
#include <queue>

//206. 反转链表

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

//递归
class Solution {
public:
  ListNode* reverseList(ListNode* head) {
    ListNode* next = head->next;
    head->next = nullptr;
    return doReverseList(head, next);
  }

  ListNode* doReverseList(ListNode* curr, ListNode* next) {
    if (!next) return curr;
    ListNode* nnext = next->next;
    next->next = curr;
    return doReverseList(next, nnext);
  }
};

class Solution1 {
public:
  //{{1 => 3 => 5 => 7}},
  ListNode* reverseList(ListNode* head) {
    if (!head) return head;
    ListNode* curr = head;
    ListNode* prev = head;
    ListNode* next = head->next;
    while(next) {
      curr = next;
      next = next->next;
      curr->next = prev;
      prev = curr;
    }
    head->next = nullptr;
    return curr;
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
  vector<int> nums;
};


int main() {
  Solution1 solution;
  vector<solutionItem> data {
                             {{1,3,5,7}},
                             {{2,4,6,8}},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    ListNode *head = vectorToList(item.nums);
    cout << "solution.reverseList(" << listToString(head) << ")" << endl ;
    auto result = solution.reverseList(head);
    cout << ", result:" << listToString(result) << endl;
  }
  return 0;
}
