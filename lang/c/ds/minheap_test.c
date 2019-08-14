
#include <stdio.h>
#include <stdlib.h>
#include "minheap.h"

/*
 * 打印二叉堆
 *
 * 返回值：
 *     0，表示成功
 *    -1，表示失败
 */
static void minheap_print(struct minheap_struct *min_heap)
{
  if (min_heap == NULL)
    return;
  int i;
  printf(" len:%d, size:%d\n", min_heap->len, min_heap->size);
  for (i=0; i<min_heap->size; i++)
    printf(" %d,", min_heap->root[i]);
  printf("\n");
}

void main()
{

  int a[] = {80, 40, 30, 60, 90, 70, 10, 50, 20};
  int i, len=sizeof(a)/sizeof(a[0]);
  int ret = 0;
  struct minheap_struct min_heap;
  ret = minheap_create(&min_heap, len);
  printf("minheap_create(&min_heap, %d) == %d\n", len, ret);
  if (ret != 0) {
    printf("minheap_create failed ret:%d\n", ret);
    return;
  }

  printf("== 依次添加: \n");
  for(i=0; i<len; i++) {
    printf("    %d ", a[i]);
    ret = minheap_insert(&min_heap, a[i]);
    if (ret != 0) {
      printf("minheap_insert failed data:%d, ret:%d\n", a[i], ret);
      break;
    }
  }

  printf("\n== 最 小 堆: \n");
  minheap_print(&min_heap);

  i=15;
  ret = minheap_insert(&min_heap, i);
  printf("minheap_insert(&min_heap, %d) == %d", i, ret);
  printf("\n== 添加元素: %d", i);
  printf("\n== 最 小 堆: \n");
  minheap_print(&min_heap);

  i=10;
  ret = minheap_remove(&min_heap, i);
  if (ret != 0) {
    printf("minheap_remove failed ret:%d\n", ret);
  }
  printf("\n== 删除元素: %d", i);
  printf("\n== 最 小 堆: \n");
  minheap_print(&min_heap);
}
