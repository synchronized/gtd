
/**
 * 二叉搜索树(C语言): C语言实现的二叉搜索树。
 *
 * @author sunday
 * @date 2019-03-28
 */

#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"

//前序遍历"二叉树"
void preorder_bstree(bstree *tree) {
  if (tree == NULL) {
    return;
  }

  printf("%d ", tree->key);
  preorder_bstree(tree->left);
  preorder_bstree(tree->right);
}

// 中序遍历"二叉树"
void inorder_bstree(bstree *tree) {
  if (tree == NULL) {
    return;
  }

  inorder_bstree(tree->left);
  printf("%d ", tree->key);
  inorder_bstree(tree->left);
}

// 后序遍历"二叉树"
void postorder_bstree(bstree *tree) {
  if (tree == NULL) {
    return;
  }

  postorder_bstree(tree->left);
  postorder_bstree(tree->right);
  printf("%d ", tree->key);
}

// (递归实现)查找"二叉树x"中键值为key的节点
node* bstree_search(bstree *tree, bs_type key) {
  node *pnode = NULL;
  if (tree == NULL || tree->key == key) {
    return tree;
  }
  if (key < tree->key) {
    pnode = bstree_search(tree->left, key);
  } else {
    pnode = bstree_search(tree->right, key);
  }
  return pnode;
}

// (非递归实现)查找"二叉树x"中键值为key的节点
node* iterative_bstree_search(bstree *tree, bs_type key) {
  node *pnode = tree;
  while (pnode != NULL && pnode->key != key) {
    if (key < pnode->key) {
      pnode = pnode->left;
    } else {
      pnode = pnode->right;
    }
  }
  return pnode;
}

// 查找最小结点：返回tree为根结点的二叉树的最小结点。
node* bstree_minimum(bstree *tree) {
  if (tree == NULL) {
    return NULL;
  }
  node *pnode = tree;
  while (pnode->left != NULL) {
    pnode = pnode->left;
  }
  return pnode;
}

// 查找最大结点：返回tree为根结点的二叉树的最大结点。
node* bstree_maximum(bstree *tree) {
  if (tree == NULL) {
    return NULL;
  }
  node *pnode = tree;
  while (pnode->right != NULL) {
    pnode = pnode->right;
  }
  return pnode;
}

// 找结点(x)的后继结点。即，查找"二叉树中数据值大于该结点"的"最小结点"。
node* bstree_successor(bstree *tree) {
  if (tree == NULL) {
    return NULL;
  }
  if (tree->right != NULL) {
    return bstree_minimum(tree->right);
  }
  node *x = tree;
  node *y = x->parent;
  while (x != NULL && x != y->left) {
    x = y;
    y = y->parent;
  }
  return y;
}

// 找结点(x)的前驱结点。即，查找"二叉树中数据值小于该结点"的"最大结点"。
node* bstree_predecessor(bstree *tree) {
  if (tree == NULL) {
    return NULL;
  }
  if (tree->left != NULL) {
    return bstree_maximum(tree->left);
  }
  node *x = tree;
  node *y = x->parent;
  while (y != NULL && x != y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

/*
 * 创建并返回二叉树结点。
 *
 * 参数说明：
 *     key 是键值。
 *     parent 是父结点。
 *     left 是左孩子。
 *     right 是右孩子。
 */
static node* create_bstree_node(bs_type key, node *parent, node *left, node *right) {
  node *pnode = (node*)malloc(sizeof(node));
  if (!pnode) {
    return NULL;
  }
  pnode->key = key;
  pnode->parent = parent;
  pnode->left = left;
  pnode->right = right;
  return pnode;
}

/*
 * 将结点插入到二叉树中
 *
 * 参数说明：
 *     tree 二叉树的根结点
 *     z 插入的结点
 * 返回值：
 *     根节点
 */
static node* bstree_insert(bstree *tree, node *pnode) {
  node* y = NULL;
  node* x = tree;
  while (x != NULL) {
    y = x;
    if (pnode->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  pnode->parent = y;
  if (y == NULL) {
    return pnode;
  } else if (pnode->key < y->key) {
    y->left = pnode;
  } else {
    y->right = pnode;
  }
  return tree;
}

// 将结点插入到二叉树中，并返回根节点
node* insert_bstree(bstree *tree, bs_type key) {
  node *pnode = create_bstree_node(key, NULL, NULL, NULL);
  if (pnode == NULL) {
    return tree;
  }
  return bstree_insert(tree, pnode);
}

/*
 * 删除结点(z)，并返回根节点
 *
 * 参数说明：
 *     tree 二叉树的根结点
 *     z 删除的结点
 * 返回值：
 *     根节点
 */
static node* bstree_delete(bstree *tree, node* pnode) {
  node* x = NULL;
  node* y = NULL;
  if (pnode->left == NULL || pnode->right == NULL) {
    y = pnode;
  } else {
    y = bstree_successor(pnode);
  }

  if (y->left != NULL) {
    x = y->left;
  } else {
    x = y->right;
  }

  if (x != NULL) {
    x->parent = y->parent;
  }

  if (y->parent == NULL) {
    tree = x;
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }

  if (y != pnode) {
    pnode->key = y->key;
  }

  if (y != NULL) {
    free(y);
  }
  return tree;
}

node* delete_bstree(bstree *tree, bs_type key) {
  node *pnode = bstree_search(tree, key);
  if (pnode != NULL) {
    tree = bstree_delete(tree, pnode);
  }
  return tree;
}

void print_bstree(bstree *tree, bs_type key, int direction) {
  if (tree == NULL) {
    return;
  }
  if (direction == 0) {
    printf("%2d is root\n", tree->key);
  } else {
    printf("%2d is %2d's %6s child\n", tree->key, key, direction==1?"right":"left");
  }
  print_bstree(tree->left, tree->key, -1);
  print_bstree(tree->right, tree->key, 1);
}

void destroy_bstree(bstree *tree) {
  if (tree == NULL) {
    return;
  }

  if (tree->left != NULL) {
    destroy_bstree(tree->left);
  }
  if (tree->right != NULL) {
    destroy_bstree(tree->right);
  }

  free(tree);
}
