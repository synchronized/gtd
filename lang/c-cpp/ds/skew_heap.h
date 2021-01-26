
#ifndef _SKEW_HEAP_H
#define _SKEW_HEAP_H

typedef int skew_heap_key;

struct skew_heap_node {
  skew_heap_key key; /* 关键字(键值) */
  struct skew_heap_node *left; /* 左孩子 */
  struct skew_heap_node *right; /* 右孩子 */
};

// 获取最小值(保存到pval中)，成功返回0，失败返回-1。
int skew_heap_minimum(struct skew_heap_node *heap, int *pval);
// 合并"斜堆堆x"和"斜堆堆y"，并返回合并后的新树
struct skew_heap_node* skew_heap_merge(struct skew_heap_node *x, struct skew_heap_node *y);
// 将结点插入到斜堆堆中，并返回根节点
struct skew_heap_node* skew_heap_insert(struct skew_heap_node *heap, skew_heap_key key);
// 删除结点(key为节点的值)，并返回根节点
struct skew_heap_node* skew_heap_delete(struct skew_heap_node *heap);

// 销毁斜堆堆
void skew_heap_destroy(struct skew_heap_node *heap);

#endif // _SKEW_HEAP_H
