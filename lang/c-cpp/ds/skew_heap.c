#include <stdlib.h>
#include "skew_heap.h"

// 获取最小值(保存到pval中)，成功返回0，失败返回-1。
int skew_heap_minimum(struct skew_heap_node *heap, int *pval)
{
  if (heap == NULL)
    return -1;
  *pval = heap->key;
  return 0;
}

// 合并"斜堆堆x"和"斜堆堆y"，并返回合并后的新树
struct skew_heap_node* skew_heap_merge(struct skew_heap_node *x, struct skew_heap_node *y)
{
  if (x == NULL)
    return y;
  if (y == NULL)
    return x;

  // 合并x和y时，将x作为合并后的树的根；
  // 这里的操作是保证: x的key < y的key
  if (x->key > y->key)
    return skew_heap_merge(y, x);

  // 将x的右孩子和y合并，
  // 合并后直接交换x的左右孩子，而不需要像左倾堆一样考虑它们的npl。
  struct skew_heap_node *tmp = skew_heap_merge(x->right, y);
  x->right = x->left;
  x->left = tmp;

  return x;
}
// 将结点插入到斜堆堆中，并返回根节点
struct skew_heap_node* skew_heap_insert(struct skew_heap_node *heap, skew_heap_key key)
{
  struct skew_heap_node *node = (struct skew_heap_node*)malloc(sizeof(struct skew_heap_node));
  if (node == NULL)
    return NULL;

  node->key = key;
  node->left = NULL;
  node->right = NULL;
  return skew_heap_merge(heap, node);
}
// 删除结点(key为节点的值)，并返回根节点
struct skew_heap_node* skew_heap_delete(struct skew_heap_node *heap)
{
  struct skew_heap_node *node = skew_heap_merge(heap->left, heap->right);
  free(heap);
  return node;
}

// 销毁斜堆堆
void skew_heap_destroy(struct skew_heap_node *heap) {
  if (heap == NULL)
    return;

  skew_heap_destroy(heap->left);
  skew_heap_destroy(heap->right);
  free(heap);
}
