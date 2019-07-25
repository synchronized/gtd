
#ifndef _RB_TREE_H
#define _RB_TREE_H

#define RB_TREE_RED   0 //红色
#define RB_TREE_BLACK 1 //黑色

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


#endif
