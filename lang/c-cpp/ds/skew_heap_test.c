/**
 * C语言实现的斜堆
 *
 * @author sunday
 * @date 2019/08/15
 */

#include <stdio.h>
#include "skew_heap.h"
#include "ascii_tree_print.h"

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

static void print_build_handler(void *t, char *buf, void **left, void **right) {
  struct skew_heap_node *node = (struct skew_heap_node*)t;
  sprintf(buf, "%d", node->key);
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
    struct skew_heap_node *ha, *hb;

    ha=hb=NULL;

    printf("== 斜堆(ha)中依次添加: ");
    for(i=0; i<alen; i++)
    {
        printf("%d ", a[i]);
        ha = skew_heap_insert(ha, a[i]);
    }
    printf("\n== 斜堆(ha)的详细信息: \n");
    ascii_tree_print(ha, print_build_handler);


    printf("\n== 斜堆(hb)中依次添加: ");
    for(i=0; i<blen; i++)
    {
        printf("%d ", b[i]);
        hb = skew_heap_insert(hb, b[i]);
    }
    printf("\n== 斜堆(hb)的详细信息: \n");
    ascii_tree_print(hb, print_build_handler);

    // 将"斜堆hb"合并到"斜堆ha"中。
    ha = skew_heap_merge(ha, hb);
    printf("\n== 合并ha和hb后的详细信息: \n");
    ascii_tree_print(hb, print_build_handler);

    // 销毁斜堆
    skew_heap_destroy(ha);
}
