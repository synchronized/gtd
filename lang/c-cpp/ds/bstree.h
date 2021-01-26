#ifndef _BINARY_SEARCH_TREE_H
#define _BINARY_SEARCH_TREE_H

typedef int bs_type;

typedef struct bstree_node {
  struct bstree_node *left, *right, *parent;
  bs_type key;
} node, bstree;

// 前序遍历"二叉树"
void preorder_bstree(bstree *tree);
// 中序遍历"二叉树"
void inorder_bstree(bstree *tree);
// 后序遍历"二叉树"
void postorder_bstree(bstree *tree);

// (递归实现)查找"二叉树x"中键值为key的节点
node* bstree_search(bstree *tree, bs_type key);
// (非递归实现)查找"二叉树x"中键值为key的节点
node* iterative_bstree_search(bstree *tree, bs_type key);

// 查找最小结点：返回tree为根结点的二叉树的最小结点。
node* bstree_minimum(bstree *tree);
// 查找最大结点：返回tree为根结点的二叉树的最大结点。
node* bstree_maximum(bstree *tree);

// 找结点(x)的后继结点。即，查找"二叉树中数据值大于该结点"的"最小结点"。
node* bstree_successor(node *pnode);
// 找结点(x)的前驱结点。即，查找"二叉树中数据值小于该结点"的"最大结点"。
node* bstree_predecessor(node *pnode);

// 将结点插入到二叉树中，并返回根节点
node* insert_bstree(bstree *tree, bs_type key);

// 删除结点(key为节点的值)，并返回根节点
node* delete_bstree(bstree *tree, bs_type key);

// 销毁二叉树
void destroy_bstree(bstree *tree);

// 打印二叉树
void print_bstree(bstree *tree, bs_type key, int direction);

#endif
