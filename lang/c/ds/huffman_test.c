#include <stdio.h>
#include "huffman.h"
#include "ascii_tree_print.h"

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

static void print_build_handler(void *t, char *buf, void **left, void **right) {
  struct huffman_node *node = (struct huffman_node*)t;
  sprintf(buf, "%d", node->key);
  *left = node->left;
  *right = node->right;
}

void main()
{
	int a[] = {5, 6, 8, 7, 15, 101, 12 ,9, 5, 48};
	int i, len = LENGTH(a);
	struct huffman_node *root = NULL;

	printf("== 添加数组: ");
	for (i = 0; i < len; i++)
		printf(" %d,", a[i]);
  printf("\n");

	// 创建数组a对应的Huffman树
	root = huffman_create(a, len);

	printf("== 树的详细信息: \n");
  ascii_tree_print(root, print_build_handler);

	// 销毁二叉树
	huffman_destroy(root);
}
