/**
 * C语言实现的左倾堆
 *
 * @author skywang
 * @date 2014/03/31
 */

#include <stdio.h>
#include "leftist_tree.h"
#include "ascii_tree_print.h"

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

static void print_build_handler(void *t, char *buf, void **left, void **right) {
  struct leftist_tree_node *node = (struct leftist_tree_node*)t;
  sprintf(buf, "%d(%d)", node->key, node->npl);
  *left = node->left;
  *right = node->right;
}

void main()
{
    int i;
    int a[] = {10, 40, 24, 30, 36, 20, 12, 16};
    int b[] = {17, 13, 11, 15, 19, 21, 23};
    int alen = LENGTH(a);
    int blen = LENGTH(b);
    struct leftist_tree_node *heapa = NULL, *heapb = NULL;

    printf("== 左倾堆(heapa)中依次添加: ");
    for(i=0; i<alen; i++) {
        printf("%d ", a[i]);
        heapa = leftist_tree_insert(heapa, a[i]);
    }
    printf("\n== 左倾堆(heapa)的详细信息: \n");
    ascii_tree_print(heapa, print_build_handler);


    printf("\n== 左倾堆(heapb)中依次添加: ");
    for(i=0; i<blen; i++) {
        printf("%d ", b[i]);
        heapb = leftist_tree_insert(heapb, b[i]);
    }
    printf("\n== 左倾堆(heapb)的详细信息: \n");
    ascii_tree_print(heapb, print_build_handler);

    // 将"左倾堆hb"合并到"左倾堆ha"中。
    heapa = leftist_tree_merge(heapa, heapb);
    printf("\n== 合并ha和heapb后的详细信息: \n");
    ascii_tree_print(heapa, print_build_handler);


    // 销毁左倾堆
    leftist_tree_destroy(heapa);
}
