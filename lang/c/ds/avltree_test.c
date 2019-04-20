/**
 * C 语言: AVL树
 *
 * @author sunday
 * @date 2019-04-10
 */

#include <stdio.h>
#include "avltree.h"
#include "ascii_tree_print.h"

static void print_build_handler(void *t, char *buf, void **left, void **right) {
  avltree *node = (avltree*)t;
  sprintf(buf, "%d", node->key);
  *left = node->left;
  *right = node->right;
}

void main() {
  int i,ilen;
  avltree *root=NULL;

  printf("\nAfter inserting element 10..\n");
  root = avltree_insert(root, 10);
  ascii_tree_print(root, print_build_handler);

  printf("\nAfter inserting element 5..\n");
  root = avltree_insert(root, 5);
  ascii_tree_print(root, print_build_handler);

  printf("\nAfter inserting element 15..\n");
  root = avltree_insert(root, 15);
  ascii_tree_print(root, print_build_handler);

  printf("\nAfter inserting elements 9, 13..\n");
  root = avltree_insert(root, 9);
  root = avltree_insert(root, 13);
  ascii_tree_print(root, print_build_handler);

  printf("\nAfter inserting elements 2, 6, 12, 14, ..\n");
  root = avltree_insert(root, 2);
  root = avltree_insert(root, 6);
  root = avltree_insert(root, 12);
  root = avltree_insert(root, 14);
  ascii_tree_print(root, print_build_handler);

  printf("\n== preorder:");
  avltree_preorder(root);

  printf("\n== inorder: ");
  avltree_inorder(root);

  printf("\n== postorder: ");
  avltree_postorder(root);

  printf("\n== 高度: %d\n", avltree_height(root));
  printf("\n== 最小值: %d\n", avltree_minimum(root)->key);
  printf("\n== 最大值: %d\n", avltree_maximum(root)->key);

  printf("\n\nAfter deleting a node (14) with no child..\n");
  root = avltree_delete(root, 14);
  ascii_tree_print(root, print_build_handler);

  printf("\n\nAfter deleting a node (13) with left child..\n");
  root = avltree_delete(root, 13);
  ascii_tree_print(root, print_build_handler);

  printf("\n\nAfter deleting a node (5) with left and right children..\n");
  root = avltree_delete(root, 5);
  ascii_tree_print(root, print_build_handler);

  printf("\n\nAfter deleting a node (10, root node) with left and right children..\n");
  root = avltree_delete(root, 10);
  ascii_tree_print(root, print_build_handler);

  // 销毁二叉树
  avltree_destroy(root);
}
