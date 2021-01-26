
#include <stdlib.h>
#include "maxheap.h"

/* 创建最大堆 */
int maxheap_create(struct maxheap_struct *max_heap, int len)
{
  if (!max_heap) {
    return -1;
  }
  max_heap->root = (int*)malloc(sizeof(int)*len);
  if (max_heap->root == NULL) {
    return -2;
  }
  max_heap->len = len;
  max_heap->size = 0;
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
static int maxheap_fixup(struct maxheap_struct *max_heap, int start)
{
  if (!max_heap) {
    return -1;
  }
  if (max_heap->size <= start) {
    return -2;
  }
  int c = start; /* 当前结点 */
  int data = max_heap->root[c];
  while(c > 0) {
    int p = (c-1)/2; /* 父结点 */
    if (max_heap->root[p] > data)
      break;

    max_heap->root[c] = max_heap->root[p];
    c = p;
  }
  max_heap->root[c] = data;
  return 0;
}

/* 将data插入到二叉堆中 */
int maxheap_insert(struct maxheap_struct *max_heap, int data)
{
  if (!max_heap) {
    return -1;
  }
  if (max_heap->len <= max_heap->size) {
    int new_len = max_heap->size + MAXHEAP_INCRE_STEP;
    max_heap->root = (int*)realloc(max_heap->root, sizeof(int)*(new_len));
    if (max_heap->root == NULL) {
      return -2;
    }
    max_heap->len = new_len;
  }
  max_heap->root[max_heap->size++] = data;
  return maxheap_fixup(max_heap, max_heap->size-1);
}

/* 返回data在二叉堆中的索引 */
int maxheap_getindex(struct maxheap_struct *max_heap, int data)
{
  if (!max_heap) {
    return -2;
  }
  int i;
  for (i = 0; i<max_heap->size; i++) {
    if (data == max_heap->root[i]) {
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
static int maxheap_filterdown(struct maxheap_struct *max_heap, int start, int end)
{
  if (!max_heap)
    return -1;

  int c = start;
  int data = max_heap->root[c];
  int l;

  while((l = 2*c+1) <= end) {
    if (l < end && max_heap->root[l] < max_heap->root[l+1])
      l++;
    if (data >= max_heap->root[l])
      break;

    max_heap->root[c] = max_heap->root[l];
    c = l;
  }
  max_heap->root[c] = data;
  return 0;
}

int maxheap_remove(struct maxheap_struct *max_heap, int data)
{
  int index;
  // 如果"堆"已空，则返回-1
  if(max_heap == NULL || max_heap->size == 0)
    return -1;

  // 获取data在数组中的索引
  index = maxheap_getindex(max_heap, data);
  if (index < 0)
    return -1;

  max_heap->root[index] = max_heap->root[max_heap->size];        // 用最后元素填补
  max_heap->size -= 1;
  maxheap_filterdown(max_heap, index, max_heap->size-1);    // 从index位置开始自上向下调整为最大堆
  return 0;
}
