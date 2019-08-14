
#include <stdlib.h>
#include "minheap.h"

/* 创建最大堆 */
int minheap_create(struct minheap_struct *min_heap, int len)
{
  if (!min_heap) {
    return -1;
  }
  min_heap->root = (int*)malloc(sizeof(int)*len);
  if (min_heap->root == NULL) {
    return -2;
  }
  min_heap->len = len;
  min_heap->size = 0;
  return 0;
}

/*
 * 最大堆的向上调整算法(从start开始向上直到0，调整堆)
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被上调节点的起始位置(一般为数组中最后一个元素的索引)
 */
static int minheap_fixup(struct minheap_struct *min_heap, int start)
{
  if (!min_heap) {
    return -1;
  }
  if (min_heap->size <= start) {
    return -2;
  }
  int c = start; /* 当前结点 */
  int data = min_heap->root[c];
  while(c > 0) {
    int p = (c-1)/2; /* 父结点 */
    if (min_heap->root[p] < data)
      break;

    min_heap->root[c] = min_heap->root[p];
    c = p;
  }
  min_heap->root[c] = data;
  return 0;
}

/* 将data插入到二叉堆中 */
int minheap_insert(struct minheap_struct *min_heap, int data)
{
  if (!min_heap) {
    return -1;
  }
  if (min_heap->len <= min_heap->size) {
    int new_len = min_heap->size + MINHEAP_INCRE_STEP;
    min_heap->root = (int*)realloc(min_heap->root, sizeof(int)*(new_len));
    if (min_heap->root == NULL) {
      return -2;
    }
    min_heap->len = new_len;
  }
  min_heap->root[min_heap->size++] = data;
  return minheap_fixup(min_heap, min_heap->size-1);
}

/* 返回data在二叉堆中的索引 */
int minheap_getindex(struct minheap_struct *min_heap, int data)
{
  if (!min_heap) {
    return -2;
  }
  int i;
  for (i = 0; i<min_heap->size; i++) {
    if (data == min_heap->root[i]) {
      return i;
    }
  }
  return -1;
}

/*
 * 最大堆的向下调整算法
 *
 * 注：数组实现的堆中，第N个节点的左孩子的索引值是(2N+1)，右孩子的索引是(2N+2)。
 *
 * 参数说明：
 *     start -- 被下调节点的起始位置(一般为0，表示从第1个开始)
 *     end   -- 截至范围(一般为数组中最后一个元素的索引)
 */
static int minheap_filterdown(struct minheap_struct *min_heap, int start, int end)
{
  if (!min_heap)
    return -1;

  int c = start;
  int data = min_heap->root[c];
  int l;

  while((l = 2*c+1) <= end) {
    if (l < end && min_heap->root[l] > min_heap->root[l+1])
      l++;
    if (data <= min_heap->root[l])
      break;

    min_heap->root[c] = min_heap->root[l];
    c = l;
  }
  min_heap->root[c] = data;
  return 0;
}

int minheap_remove(struct minheap_struct *min_heap, int data)
{
  int index;
  // 如果"堆"已空，则返回-1
  if(min_heap == NULL || min_heap->size == 0)
    return -1;

  // 获取data在数组中的索引
  index = minheap_getindex(min_heap, data);
  if (index < 0)
    return -1;

  min_heap->root[index] = min_heap->root[min_heap->size];        // 用最后元素填补
  min_heap->size -= 1;
  minheap_filterdown(min_heap, index, min_heap->size-1);    // 从index位置开始自上向下调整为最大堆
  return 0;
}
