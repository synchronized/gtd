#include <vector>
#include <iostream>
#include <queue>

//leetCode: 116. 填充每个节点的下一个右侧节点指针

using namespace std;
/*
// Definition for a Node.
*/
class Node {
public:
  int val;
  Node* left;
  Node* right;
  Node* next;

  Node() : val(0), left(NULL), right(NULL), next(NULL) {}

  Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

  Node(int _val, Node* _left, Node* _right, Node* _next)
  : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
  Node* connect(Node* root) {
    if (!root) {
      return root;
    }
    queue<Node*> qu;
    qu.push(root);
    while(!qu.empty()) {
      int size = qu.size();
      for (int i=0; i<size; i++) {
        Node *node = qu.front();
        qu.pop();
        if (i < size-1) {
          node->next = qu.front();
        }
        if (node->left) qu.push(node->left);
        if (node->right) qu.push(node->right);
      }
    }
    return root;
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

Node* vectorToTreeNode(vector<int> &nums) {
  int l = nums.size();
  if (l<=0) {
    return nullptr;
  }
  Node *root = new Node(nums[0]);
  queue<Node*> qu;
  qu.push(root);
  for (int i=1; i<l; i+=2) {
    Node *node = qu.front();
    qu.pop();
    node->left = new Node(nums[i]);
    if (i+1 < l) {
      node->right = new Node(nums[i+1]);
      qu.push(node->left);
      qu.push(node->right);
    }
  }
  return root;
}

//tree node connect
std::string treeNodeToString(Node *root) {
  std::string buf = "{";
  Node *cur = root;
  while(cur) {
    Node *curcol = cur;
    while(curcol) {
      if (cur != root) {
        buf += ",";
      }
      buf += std::to_string(curcol->val);
      curcol = curcol->next;
    }
    buf += ",#";
    if (cur->left) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  buf += "}";
  return buf;
}

struct solutionItem {
  vector<int> nums;
};


int main() {
  Solution solution;
  vector<solutionItem> data {
                             {{1,2,3,4,5,6,7}},
  };
  for (auto it = data.begin(); it != data.end(); it++) {
    solutionItem &item = *it;
    Node *root = vectorToTreeNode(item.nums);
    cout << "solution.connect(" << vectorToString(item.nums) << ")" << endl ;
    auto result = solution.connect(root);
    cout << ", result:" << treeNodeToString(result) << endl;
  }
  return 0;
}
