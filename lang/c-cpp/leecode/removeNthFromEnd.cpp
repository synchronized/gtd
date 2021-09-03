#include <vector>
#include <string>
#include <iostream>
#include <sstream>

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
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    int i = 0;
    if (n <= 0) {
      return head;
    }
    ListNode* fast = head;
    ListNode** find = &head;
    while (fast) {
      fast = fast->next;
      if (i>=n) {
        find = &(*find)->next;
      }
      i++;
    }
    *find = (*find)->next; //remove next
    return head;
  }
};

ListNode* vectorToListNode(vector<int> vec) {
  ListNode *head = nullptr;
  ListNode **curr = &head;
  for (vector<int>::size_type i=0; i<vec.size(); i++) {
    *curr = new ListNode(vec[i]);
    curr = &((*curr)->next);
  }
  return head;
}

std::string ListNodeToString(ListNode* head) {
  std::ostringstream out;
  out << "{";
  ListNode *curr = head;
  while (curr) {
    if (curr != head) {
      out << ", ";
    }
    out << curr->val;

    curr = curr->next;
  }
  out << "}";
  return out.str();
}

struct vectorItem {
  vector<int> nums;
  int rmidx;
};

int main() {
  Solution solution;
  vector<vectorItem> data {
                           {{1}, 1},
                           {{1,2,3,4,5}, 2},
                           {{1,2,3,4,5,6}, 2},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    vectorItem &item = *it;
    ListNode *head = vectorToListNode(item.nums);
    cout << "solution.reverseWords(" << ListNodeToString(head) << ")";
    auto result = solution.removeNthFromEnd(head, item.rmidx);
    cout << ", result:" << ListNodeToString(result) << "" << endl;
  }
  return 0;
}
