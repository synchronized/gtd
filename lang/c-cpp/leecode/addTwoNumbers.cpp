#include <iostream>
#include <vector>

/*
 * leetcode: 2. 两数相加
 * 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
 * 请你将两个数相加，并以相同形式返回一个表示和的链表。
 * 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
 */

using namespace std ;

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
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode** n1 = &l1;
    ListNode** n2 = &l2;
    bool carry = false;
    while(*n1 || carry) {
      if (!(*n1)) { //如果两个数字都没有下一个数需要进一位
        *n1 = new ListNode(0);
      }
      if (*n2) { //如果两个数都有当前位，需要相加
        (*n1)->val += (*n2)->val;
      }
      if (carry) { //如果进位需要加上上一位的进位
        (*n1)->val++;
        carry = false;
      }
      if ((*n1)->val > 9) { //如果大于9则需要进位到
        (*n1)->val %= 10;
        carry = true;
      }
      n1 = &(*n1)->next;
      if (*n2) { //如果第二个数有当前位,需要移动n2指针
        n2 = &(*n2)->next;
      }
      if (!(*n1) && *n2) { //如果n1为空则需要将n2赋值给n1
        *n1 = *n2;
        *n2 = nullptr;
      }
    }
    return l1;
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
  vector<int> num1;
  vector<int> num2;
};

int main() {
  Solution solution;
  vector<solutionItem> data {
                             {{1,3,5,7}, {2,4,6}},
                             {{1,3,5}, {2,4,6,9}},
  };

  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    ListNode *num1 = vectorToList(item.num1);
    ListNode *num2 = vectorToList(item.num2);
    cout << "solution.reverseList(" << listToString(num1) << ", " << listToString(num2) << ")" << endl ;
    auto result = solution.addTwoNumbers(num1, num2);
    cout << ", result:" << listToString(result) << endl;
  }
  return 0;
}
