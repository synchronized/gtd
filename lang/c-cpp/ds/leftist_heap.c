#include <stdio.h>
#include <stdlib.h>
#include "leftist_heap.h"

// 获取最小值(保存到pval中)，成功返回0，失败返回-1。
int leftist_heap_minimum(struct leftist_heap_node *heap, int *pval)
{
  if (heap == NULL)
    return -1;

  *pval = heap->key;
  return 0;
}

// 合并"左倾堆x"和"左倾堆y"，并返回合并后的新树
struct leftist_heap_node* leftist_heap_create(
                                              leftist_heap_key key,
                                              int npl,
                                              struct leftist_heap_node *left,
                                              struct leftist_heap_node *right)
{
  struct leftist_heap_node *node = (struct leftist_heap_node*)malloc(sizeof(struct leftist_heap_node));
  if (node == NULL)
    return NULL;

  node->key = key;
  node->npl = npl;
  node->left = left;
  node->right = right;
  return node;
}
// 合并"左倾堆x"和"左倾堆y"，并返回合并后的新树
struct leftist_heap_node* leftist_heap_merge(struct leftist_heap_node *x, struct leftist_heap_node *y)
{
  if (x == NULL)
    return y;

  if (y == NULL)
    return x;

  // 合并x和y时，将x作为合并后的树的根；
  // 这里的操作是保证: x的key < y的key
  if (x->key > y->key)
    return leftist_heap_merge(y, x);

  // 将x的右孩子和y合并，"合并后的树的根"是x的右孩子。
  x->right = leftist_heap_merge(x->right, y);

  // 如果"x的左孩子为空" 或者 "x的左孩子的npl<右孩子的npl"
  // 则，交换x和y
  if (x->left == NULL || x->left->npl < x->right->npl) {
    struct leftist_heap_node *tmp = x->left;
    x->left = x->right;
    x->right = tmp;
  }

  if (x->left == NULL || x->right == NULL)
    x->npl = 0;
  else
    x->npl = (x->left->npl > x->right->npl) ? (x->right->npl + 1) : (x->left->npl + 1);

  return x;
}

// 将结点插入到左倾堆中，并返回根节点
struct leftist_heap_node* leftist_heap_insert(struct leftist_heap_node *heap, leftist_heap_key key)
{
  struct leftist_heap_node *node = leftist_heap_create(key, 0, NULL, NULL);
  return leftist_heap_merge(heap, node);
}

// 删除结点(key为节点的值)，并返回根节点
struct leftist_heap_node* leftist_heap_delete(struct leftist_heap_node *heap)
{
  if (heap == NULL)
    return NULL;
  struct leftist_heap_node *node = leftist_heap_merge(heap->left, heap->right);
  free(heap);
  return node;
}


// 销毁左倾堆
void leftist_heap_destroy(struct leftist_heap_node *heap) {
  if (heap == NULL) {
    return;
  }

  leftist_heap_destroy(heap->left);
  leftist_heap_destroy(heap->right);
  free(heap);
}
