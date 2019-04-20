#ifndef _SPLAY_TREE_H
#define _SPLAY_TREE_H

typedef int splaytype;

typedef struct splaytree_node splaynode;

struct splaytree_node {
  splaytype key;                       // 关键字(键值)
  splaynode *left, *right;      // 左/孩子
};

// 前序遍历"伸展树"
void splaytree_preorder(splaynode *tree);
// 中序遍历"伸展树"
void splaytree_inorder(splaynode *tree);
// 后序遍历"伸展树"
void splaytree_postorder(splaynode *tree);

// (递归实现)查找"伸展树x"中键值为key的节点
splaynode* splaytree_search(splaynode *tree, splaytype key);
// (非递归实现)查找"伸展树x"中键值为key的节点
splaynode* splaytree_search_iterative(splaynode *tree, splaytype key);

// 查找最小结点：返回tree为根结点的伸展树的最小结点。
splaynode* splaytree_minimum(splaynode *tree);
// 查找最大结点：返回tree为根结点的伸展树的最大结点。
splaynode* splaytree_maximum(splaynode *tree);

// 旋转key对应的节点为根节点。
splaynode* splaytree_splay(splaynode *tree, splaytype key);

// 将结点插入到伸展树中，并返回根节点
splaynode* splaytree_insert(splaynode *tree, splaytype key);

// 删除结点(key为节点的值)，并返回根节点
splaynode* splaytree_delete(splaynode *tree, splaytype key);

// 销毁伸展树
void splaytree_destroy(splaynode *tree);

// 打印伸展树
void splaytree_print(splaynode *tree, splaytype key, int direction);


#endif
