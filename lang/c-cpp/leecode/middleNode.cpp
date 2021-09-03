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
  ListNode* middleNode(ListNode* head) {
    ListNode* mid = head;
    ListNode* curr = head;
    int i = 0;
    while (curr) {
      curr = curr->next;
      i++;
      if (i % 2 == 0) {
        mid = mid->next;
      }
    }
    return mid;
  }
};

class Solution2 {
public:
  ListNode* middleNode(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
      slow = slow->next;
      fast = fast->next->next;
    }
    return slow;
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

int main() {
  Solution2 solution;
  vector<vector<int>> data {
                            {1,2,3,4,5},
                            {1,2,3,4,5,6},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    vector<int> &item = *it;
    ListNode *head = vectorToListNode(item);
    cout << "solution.reverseWords(" << ListNodeToString(head) << ")";
    auto result = solution.middleNode(head);
    cout << ", result:" << ListNodeToString(result) << "" << endl;
  }
  return 0;
}
