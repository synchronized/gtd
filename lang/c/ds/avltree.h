#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#define HEIGHT(p)     ( (p==NULL) ? 0 : ((avlnode*)(p))->height )

typedef int avltype;

typedef struct avltree_node{
  avltype key;                    // 关键字(键值)
  int height;
  struct avltree_node *left, *right;    // 左,右子结点
}avlnode, avltree;

// 获取AVL树的高度
int avltree_height(avltree *tree);

// 前序遍历"AVL树"
void avltree_preorder(avltree *tree);
// 中序遍历"AVL树"
void avltree_inorder(avltree *tree);
// 后序遍历"AVL树"
void avltree_postorder(avltree *tree);

// (递归实现)查找"AVL树x"中键值为key的节点
avlnode* avltree_search(avltree *tree, avltype key);
// (非递归实现)查找"AVL树x"中键值为key的节点
avlnode* avltree_search_iterative(avltree *tree, avltype key);

// 查找最小结点：返回tree为根结点的AVL树的最小结点。
avlnode* avltree_minimum(avltree *tree);
// 查找最大结点：返回tree为根结点的AVL树的最大结点。
avlnode* avltree_maximum(avltree *tree);

// 将结点插入到AVL树中，返回根节点
avlnode* avltree_insert(avltree *tree, avltype key);

// 删除结点(key是节点值)，返回根节点
avlnode* avltree_delete(avltree *tree, avltype key);

// 销毁AVL树
void avltree_destroy(avltree *tree);

void avltree_print(avltree *tree, avltype key, int direction);

#endif
