
#include <stdio.h>
#include <stdlib.h>
#include "maxheap.h"

/*
 * 打印二叉堆
 *
 * 返回值：
 *     0，表示成功
 *    -1，表示失败
 */
static void maxheap_print(struct maxheap_struct *max_heap)
{
  if (max_heap == NULL)
    return;
  int i;
  printf(" len:%d, size:%d\n", max_heap->len, max_heap->size);
  for (i=0; i<max_heap->size; i++)
    printf(" %d,", max_heap->root[i]);
  printf("\n");
}

void main()
{

  int a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};
  int i, len=sizeof(a)/sizeof(a[0]);
  int ret = 0;
  struct maxheap_struct max_heap;
  ret = maxheap_create(&max_heap, len);
  printf("maxheap_create(&max_heap, %d) == %d\n", len, ret);
  if (ret != 0) {
    printf("maxheap_create failed ret:%d\n", ret);
    return;
  }

  printf("== 依次添加: \n");
  for(i=0; i<len; i++) {
    printf("    %d ", a[i]);
    ret = maxheap_insert(&max_heap, a[i]);
    if (ret != 0) {
      printf("maxheap_insert failed data:%d, ret:%d\n", a[i], ret);
      break;
    }
  }

  printf("\n== 最 大 堆: \n");
  maxheap_print(&max_heap);

  i=15;
  ret = maxheap_insert(&max_heap, i);
  printf("maxheap_insert(&max_heap, %d) == %d", i, ret);
  printf("\n== 添加元素: %d", i);
  printf("\n== 最 大 堆: \n");
  maxheap_print(&max_heap);

  i=10;
  ret = maxheap_remove(&max_heap, i);
  if (ret != 0) {
    printf("maxheap_remove failed ret:%d\n", ret);
  }
  printf("\n== 删除元素: %d", i);
  printf("\n== 最 大 堆: \n");
  maxheap_print(&max_heap);
}
