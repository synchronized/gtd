
#ifndef _RB_TREE_H
#define _RB_TREE_H

#define RBTREE_RED   0 //红色
#define RBTREE_BLACK 1 //黑色

typedef int rbtree_type;

//红黑树
struct rbtree_node {
  unsigned char color; //颜色(RED或者BLACK)
  rbtree_type key; //关键字(排序)
  struct rbtree_node *left; //左结点
  struct rbtree_node *right; //右结点
  struct rbtree_node *parent; //父结点
};

struct rbtree_root {
  struct rbtree_node *node; //根结点
};


// 创建红黑树，返回"红黑树的根"！
struct rbtree_root *rbtree_create();

// 初始化红黑树
void rbtree_init(struct rbtree_root *root);

// 销毁红黑树
void rbtree_destroy(struct rbtree_root *root);

// 将结点插入到红黑树中。插入成功，返回0；失败返回-1。
int rbtree_insert(struct rbtree_root *root, rbtree_type key);

// 删除结点(key为节点的值)
void rbtree_delete(struct rbtree_root *root, rbtree_type key);

// 前序遍历"红黑树"
void rbtree_preorder(struct rbtree_root *root);

// 中序遍历"红黑树"
void rbtree_inorder(struct rbtree_root *root);

// 后序遍历"红黑树"
void rbtree_postorder(struct rbtree_root *root);

// (递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
struct rbtree_node *rbtree_search(struct rbtree_root *root, rbtree_type key);

// (非递归实现)查找"红黑树"中键值为key的节点。找到的话，返回0；否则，返回-1。
struct rbtree_node *rbtree_search_iterative(struct rbtree_root *root, rbtree_type key);

// 最小结点
int rbtree_minimum(struct rbtree_root *root, int *key);

// 最大结点
int rbtree_maximum(struct rbtree_root *root, int *key);

#endif
