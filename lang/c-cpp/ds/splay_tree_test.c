#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "splay_tree.h"
#include "ascii_tree_print.h"

static void print_build_handler(void *t, char *buf, void **left, void **right) {
  splaynode *node = (splaynode*)t;
  sprintf(buf, "%d", node->key);
  *left = node->left;
  *right = node->right;
}

int main() {
  splaynode *root = NULL;

  printf("\nAfter inserting element 10..\n");
  root = splaytree_insert(root, 10);
  ascii_tree_print(root, print_build_handler);

  printf("\nAfter inserting element 5..\n");
  root = splaytree_insert(root, 5);
  ascii_tree_print(root, print_build_handler);

  printf("\nAfter inserting element 15..\n");
  root = splaytree_insert(root, 15);
  ascii_tree_print(root, print_build_handler);

  printf("\nAfter inserting elements 9, 13..\n");
  root = splaytree_insert(root, 9);
  root = splaytree_insert(root, 13);
  ascii_tree_print(root, print_build_handler);

  printf("\nAfter inserting elements 2, 6, 12, 14, ..\n");
  root = splaytree_insert(root, 2);
  root = splaytree_insert(root, 6);
  root = splaytree_insert(root, 12);
  root = splaytree_insert(root, 14);
  ascii_tree_print(root, print_build_handler);

  printf("\n== preorder:");
  splaytree_preorder(root);

  printf("\n== inorder: ");
  splaytree_inorder(root);

  printf("\n== postorder: ");
  splaytree_postorder(root);

  //printf("\n== 高度: %d\n", splaytree_height(root));
  printf("\n== 最小值: %d\n", splaytree_minimum(root)->key);
  printf("\n== 最大值: %d\n", splaytree_maximum(root)->key);
}

