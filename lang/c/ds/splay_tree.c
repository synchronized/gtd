#include <stdio.h>
#include <malloc.h>
#include "splay_tree.h"

// 前序遍历"伸展树"
void splaytree_preorder(splaynode *tree) {
  if (tree == NULL) return;
  printf("%d ", tree->key);
  splaytree_preorder(tree->left);
  splaytree_preorder(tree->right);
}

// 中序遍历"伸展树"
void splaytree_inorder(splaynode *tree) {
  if (tree == NULL) return;
  splaytree_inorder(tree->left);
  printf("%d ", tree->key);
  splaytree_inorder(tree->right);
}

// 后序遍历"伸展树"
void splaytree_postorder(splaynode *tree) {
  if (tree == NULL) return;
  splaytree_postorder(tree->left);
  splaytree_postorder(tree->right);
  printf("%d ", tree->key);
}

// (递归实现)查找"伸展树x"中键值为key的节点
splaynode* splaytree_search(splaynode *tree, splaytype key) {
  if (tree == NULL && tree->key == key) {
    return tree;
  }
  if (key < tree->key) {
    return splaytree_search(tree->left, key);
  } else {
    return splaytree_search(tree->right, key);
  }
}

// (非递归实现)查找"伸展树x"中键值为key的节点
splaynode* splaytree_search_iterative(splaynode *tree, splaytype key) {
  splaynode *node = tree;
  while (node != NULL && key != node->key) {
    if (key < node->key) {
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return node;
}

// 查找最小结点：返回tree为根结点的伸展树的最小结点。
splaynode* splaytree_minimum(splaynode *tree) {
  if (tree == NULL) return NULL;
  splaynode *node = tree;
  while (node->left != NULL) {
    node = node->left;
  }
  return node;
}

// 查找最大结点：返回tree为根结点的伸展树的最大结点。
splaynode* splaytree_maximum(splaynode *tree) {
  if (tree == NULL) return NULL;
  splaynode *node = tree;
  while (node->right != NULL) {
    node = node->right;
  }
  return node;
}

/*
 * 旋转key对应的节点为根节点，并返回根节点。
 *
 * 注意：
 *   (a)：伸展树中存在"键值为key的节点"。
 *          将"键值为key的节点"旋转为根节点。
 *   (b)：伸展树中不存在"键值为key的节点"，并且key < tree->key。
 *      b-1 "键值为key的节点"的前驱节点存在的话，将"键值为key的节点"的前驱节点旋转为根节点。
 *      b-2 "键值为key的节点"的前驱节点存在的话，则意味着，key比树中任何键值都小，那么此时，将最小节点旋转为根节点。
 *   (c)：伸展树中不存在"键值为key的节点"，并且key > tree->key。
 *      c-1 "键值为key的节点"的后继节点存在的话，将"键值为key的节点"的后继节点旋转为根节点。
 *      c-2 "键值为key的节点"的后继节点不存在的话，则意味着，key比树中任何键值都大，那么此时，将最大节点旋转为根节点。
 */
splaynode* splaytree_splay(splaynode *tree, splaytype key) {
  splaynode N, *l, *r, *c;

  if (tree == NULL) return NULL;

  N.left = N.right = NULL;
  l = r = &N;

  for (;;) {
    if (key < tree->key) {
      if (tree->left == NULL) break;
      if (key < tree->left->key) {
        c = tree->left;                  // 01, rotate right
        tree->left = c->right;
        c->right = tree;
        tree = c;
        if (tree->left == NULL) break;
      }
      r->left = tree;                    // 02, link right
      r = tree;
      tree = tree->left;
    } else if (key > tree->key) {
      if (tree->right == NULL) break;
      if (key > tree->right->key) {
        c = tree->right;                 // 03, rotate left
        tree->right = c->left;
        c->left = tree;
        tree = c;
        if (tree->right == NULL) break;
      }
      l->right = tree;                   // 04, link left
      l = tree;
      tree = tree->right;
    } else {
      break;
    }
  }

  l->right = tree->left;
  r->left = tree->right;
  tree->left = N.right;
  tree->right = N.left;

  return tree;
}

static splaynode* splaytree_create_node(splaytype key, splaynode *left, splaynode *right) {
  splaynode *node = (splaynode*)malloc(sizeof(splaynode));
  node->key = key;
  node->left = left;
  node->right = right;
  return node;
}

// 将结点插入到伸展树中，并返回根节点
splaynode* splaytree_insert(splaynode *tree, splaytype key) {
  if (tree == NULL) {
    return splaytree_create_node(key, NULL, NULL);
  } else if (key < tree->key) {
    tree->left = splaytree_insert(tree->left, key);
  } else {
    tree->right = splaytree_insert(tree->right, key);
  }
  return tree;
}
