/**
 * C语言实现的红黑树(Red Black Tree)
 *
 * @author skywang
 * @date 2013/11/18
 */

#include <stdio.h>
#include "rbtree.h"
#include "ascii_tree_print.h"

#define CHECK_INSERT 1    // "插入"动作的检测开关(0，关闭；1，打开)
#define CHECK_DELETE 1    // "删除"动作的检测开关(0，关闭；1，打开)
#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

static void print_build_handler(void *t, char *buf, void **left, void **right) {
  struct rbtree_node *node = (struct rbtree_node*)t;
  int color_char = node->color == RBTREE_RED ? 'R' : 'B';
  sprintf(buf, "%c:%d", color_char, node->key);
  *left = node->left;
  *right = node->right;
}

void main()
{
  int a[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
  int i, ilen=LENGTH(a);
  struct rbtree_root root_struct;
  struct rbtree_root *root = &root_struct;
  rbtree_init(root);
  printf("== 原始数据: ");
  for(i=0; i<ilen; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");

  for(i=0; i<ilen; i++) {
    rbtree_insert(root, a[i]);
#if CHECK_INSERT
    printf("== 添加节点: %d\n", a[i]);
    printf("== 树的详细信息: \n");
    ascii_tree_print(root->node, print_build_handler);
    printf("\n");
#endif
  }

  printf("== 前序遍历: ");
  rbtree_preorder(root);
  printf("\n");

  printf("\n== 中序遍历: ");
  rbtree_inorder(root);
  printf("\n");

  printf("\n== 后序遍历: ");
  rbtree_postorder(root);
  printf("\n");

  if (rbtree_minimum(root, &i)==0) {
    printf("== 最小值: %d\n", i);
  }
  if (rbtree_maximum(root, &i)==0) {
    printf("== 最大值: %d\n", i);
  }
  printf("== 树的详细信息: \n");
  ascii_tree_print(root->node, print_build_handler);
  printf("\n");

#if CHECK_DELETE
  for(i=0; i<ilen; i++) {
    rbtree_delete(root, a[i]);

    printf("== 删除节点: %d\n", a[i]);
    if (root) {
      printf("== 树的详细信息: \n");
      ascii_tree_print(root->node, print_build_handler);
      printf("\n");
    }
  }
#endif

  rbtree_destroy(root);
}
